#!/usr/bin/env python3
"""
Generate follower sprite strips and palettes for pokeemerald from HGSS mmodel NSBTX data.

Each mmodel NSBTX contains 8 sequential sprite frames in NDS 4bpp tiled format:
  Standard Pokémon:  4096 bytes total → 8 × 512 bytes → 8 × 32×32 pixels
  Large Pokémon:    16384 bytes total → 8 × 2048 bytes → 8 × 64×64 pixels

  Frame ordering:
    0 = south step A    1 = south step B
    2 = north step A    3 = north step B
    4 = east step A     5 = east step B
    6 = west step A     7 = west step B  (west unused; engine hFlips east)

  Palette 0: normal colors (BGR555, n×8 scaling)
  Palette 1: shiny colors

Outputs per Pokémon:
  pokeemerald/graphics/object_events/pics/pokemon/{name}.png         — 4bpp indexed strip
  pokeemerald/graphics/object_events/palettes/follower_{name}.pal    — normal palette
  pokeemerald/graphics/object_events/palettes/follower_{name}_shiny.pal — shiny palette

Usage:
  python3 gen_follower_sprites.py
"""

import math
import re
import struct
from pathlib import Path

import numpy as np
from PIL import Image

MMODEL_DIR = Path('../pokeheartgold/files/data/mmodel/mmodel')
MMODEL_H   = Path('../pokeheartgold/include/constants/mmodel.h')
PICS_DIR   = Path('./graphics/object_events/pics/pokemon')
PAL_DIR    = Path('./graphics/object_events/palettes')

# NDS NSBTX frame indices for each of the 6 output animation frames
FRAME_SOUTH_A = 0
FRAME_SOUTH_B = 1
FRAME_NORTH_A = 2
FRAME_NORTH_B = 3
FRAME_EAST_A  = 4
FRAME_EAST_B  = 5
SLOT_FRAMES = [FRAME_SOUTH_A, FRAME_SOUTH_B, FRAME_NORTH_A, FRAME_NORTH_B, FRAME_EAST_A, FRAME_EAST_B]

NUM_FRAMES = 8  # every NSBTX has exactly 8 frames

# name → mmodel key when name differs from constant (all lower-case)
MMODEL_NAME_OVERRIDES: dict[str, str] = {}


# ---------------------------------------------------------------------------
# mmodel.h lookup
# ---------------------------------------------------------------------------

def load_mmodel_map(path: Path) -> dict[str, int]:
    pattern = re.compile(r'#define\s+MMODEL_FOLLOWER_MON_(\w+)\s+(\d+)')
    result: dict[str, int] = {}
    for line in path.read_text().splitlines():
        m = pattern.match(line.strip())
        if m:
            name, idx = m.group(1).lower(), int(m.group(2))
            if name != 'base':
                result[name] = idx
    return result


# ---------------------------------------------------------------------------
# NSBTX parsing
# ---------------------------------------------------------------------------

def parse_nsbtx(path: Path):
    """Return (palettes, frames_bytes, frame_px) or None on failure.

    palettes[0] = normal, palettes[1] = shiny — each a list of 16 (r,g,b) tuples.
    frames_bytes: raw bytes for all NUM_FRAMES sequential tiled frames.
    frame_px: pixel dimension of one square frame (32 for standard, 64 for large).
    """
    data = path.read_bytes()
    if data[:4] != b'BTX0':
        return None
    t = struct.unpack_from('<I', data, 0x10)[0]
    if data[t:t+4] != b'TEX0':
        return None

    tex_abs  = t + struct.unpack_from('<I', data, t + 0x14)[0]
    pal_size = struct.unpack_from('<I', data, t + 0x30)[0] * 8
    pal_abs  = t + struct.unpack_from('<I', data, t + 0x38)[0]

    num_palettes = pal_size // 32  # 16 colors × 2 bytes each
    palettes = []
    for p in range(num_palettes):
        colors = []
        for c in range(16):
            raw = struct.unpack_from('<H', data, pal_abs + p*32 + c*2)[0]
            colors.append(((raw & 0x1F)*8, ((raw >> 5) & 0x1F)*8, ((raw >> 10) & 0x1F)*8))
        palettes.append(colors)

    frames_bytes = data[tex_abs:pal_abs]
    frame_size   = len(frames_bytes) // NUM_FRAMES   # bytes per frame
    frame_px     = int(math.isqrt(frame_size * 2))   # square frames: px² = bytes*2

    return palettes, frames_bytes, frame_px


# ---------------------------------------------------------------------------
# NDS 4bpp tiled frame decode
# ---------------------------------------------------------------------------

def decode_frame(frame_bytes: bytes, frame_px: int, palette: list) -> np.ndarray:
    """Decode one NDS 4bpp tiled frame to RGBA (frame_px × frame_px × 4).

    NDS 2D tile format (sub_020145B4 / sub_02013FDC confirmed):
      tiles_wide = frame_px // 8
      tile (tc, tr), pixel row kr:
        byte offset = tr * tiles_wide * 32 + kr * tiles_wide * 4 + tc * 4
      Each byte holds 2 pixels (lo=left, hi=right nibble).
      Index 0 → transparent (alpha=0).
    """
    tiles_w = frame_px // 8
    arr = np.zeros((frame_px, frame_px, 4), dtype=np.uint8)
    for tr in range(tiles_w):          # tile row (same count as tiles_w since square)
        for tc in range(tiles_w):      # tile col
            for kr in range(8):        # pixel row within tile
                row_base = tr * tiles_w * 32 + kr * tiles_w * 4 + tc * 4
                for kc in range(8):    # pixel col within tile
                    pal_idx = (frame_bytes[row_base + kc // 2] >> ((kc & 1) * 4)) & 0xF
                    px, py = tc * 8 + kc, tr * 8 + kr
                    if pal_idx != 0:
                        r, g, b = palette[pal_idx]
                        arr[py, px] = (r, g, b, 255)
    return arr


def build_strip(frames_bytes: bytes, frame_px: int,
                palette: list) -> np.ndarray:
    """Decode the 6 SLOT_FRAMES and concatenate into a horizontal strip."""
    frame_size = frame_px * frame_px // 2
    decoded = [
        decode_frame(frames_bytes[i * frame_size:(i + 1) * frame_size], frame_px, palette)
        for i in SLOT_FRAMES
    ]
    return np.concatenate(decoded, axis=1)  # (frame_px, 6*frame_px, 4)


# ---------------------------------------------------------------------------
# Indexed PNG encoding using the NDS palette directly
# ---------------------------------------------------------------------------

def encode_indexed(strip_rgba: np.ndarray,
                   palette: list) -> Image.Image:
    """Build a 4bpp (P-mode) PIL image from an RGBA strip, using the given
    16-color palette.  Transparent pixels (alpha=0) → index 0."""
    H, W = strip_rgba.shape[:2]
    idx = np.zeros((H, W), dtype=np.uint8)

    for i in range(1, 16):
        r, g, b = palette[i]
        mask = (
            (strip_rgba[:, :, 0] == r) &
            (strip_rgba[:, :, 1] == g) &
            (strip_rgba[:, :, 2] == b) &
            (strip_rgba[:, :, 3] == 255)
        )
        idx[mask] = i

    img = Image.fromarray(idx, 'P')
    flat: list[int] = [0, 0, 0]  # index 0 = transparent placeholder
    for r, g, b in palette[1:]:
        flat.extend([r, g, b])
    flat.extend([0] * ((256 - 16) * 3))
    img.putpalette(flat)
    return img


# ---------------------------------------------------------------------------
# JASC-PAL I/O
# ---------------------------------------------------------------------------

def write_jasc(path: Path, palette: list) -> None:
    lines = ['JASC-PAL', '0100', '16', '0 0 0']  # index 0 = transparent placeholder
    lines += [f'{r} {g} {b}' for r, g, b in palette[1:]]
    path.write_text('\n'.join(lines) + '\n')


# ---------------------------------------------------------------------------
# Per-Pokémon processing
# ---------------------------------------------------------------------------

def process(name: str, dex: int, mmodel_map: dict[str, int],
            large: bool = False) -> str:
    """Generate sprite strip and both palettes for one Pokémon.
    Returns a short status string."""

    mkey = MMODEL_NAME_OVERRIDES.get(name, name)
    mmodel_idx = mmodel_map.get(mkey)
    if mmodel_idx is None:
        return 'SKIP (no mmodel)'

    nsbtx_path = MMODEL_DIR / f'mmodel_{mmodel_idx:08d}.NSBTX'
    if not nsbtx_path.exists():
        return f'SKIP (no NSBTX: {nsbtx_path.name})'

    parsed = parse_nsbtx(nsbtx_path)
    if parsed is None:
        return 'SKIP (parse failed)'
    palettes, frames_bytes, frame_px = parsed

    if len(palettes) < 2:
        return f'SKIP (only {len(palettes)} palette(s))'

    normal_pal = palettes[0]
    shiny_pal  = palettes[1]

    strip   = build_strip(frames_bytes, frame_px, normal_pal)
    img_out = encode_indexed(strip, normal_pal)

    pic_name = f'follower_{name}' if large else name
    img_out.save(PICS_DIR / f'{pic_name}.png')

    write_jasc(PAL_DIR / f'follower_{name}.pal',       normal_pal)
    write_jasc(PAL_DIR / f'follower_{name}_shiny.pal', shiny_pal)

    return f'ok ({frame_px}px)'


# ---------------------------------------------------------------------------
# Pokémon list  (name, national_dex)
# ---------------------------------------------------------------------------

POKEMON: list[tuple[str, int]] = [
    ("bulbasaur",    1),
    ("ivysaur",      2),
    ("venusaur",     3),
    ("charmander",   4),
    ("charmeleon",   5),
    ("charizard",    6),
    ("squirtle",     7),
    ("wartortle",    8),
    ("blastoise",    9),
    ("caterpie",     10),
    ("metapod",      11),
    ("butterfree",   12),
    ("weedle",       13),
    ("kakuna",       14),
    ("beedrill",     15),
    ("pidgey",       16),
    ("pidgeotto",    17),
    ("pidgeot",      18),
    ("rattata",      19),
    ("raticate",     20),
    ("spearow",      21),
    ("fearow",       22),
    ("ekans",        23),
    ("arbok",        24),
    ("pikachu",      25),
    ("raichu",       26),
    ("sandshrew",    27),
    ("sandslash",    28),
    ("nidoran_f",    29),
    ("nidorina",     30),
    ("nidoqueen",    31),
    ("nidoran_m",    32),
    ("nidorino",     33),
    ("nidoking",     34),
    ("clefairy",     35),
    ("clefable",     36),
    ("vulpix",       37),
    ("ninetales",    38),
    ("jigglypuff",   39),
    ("wigglytuff",   40),
    ("zubat",        41),
    ("golbat",       42),
    ("oddish",       43),
    ("gloom",        44),
    ("vileplume",    45),
    ("paras",        46),
    ("parasect",     47),
    ("venonat",      48),
    ("venomoth",     49),
    ("diglett",      50),
    ("dugtrio",      51),
    ("meowth",       52),
    ("persian",      53),
    ("psyduck",      54),
    ("golduck",      55),
    ("mankey",       56),
    ("primeape",     57),
    ("growlithe",    58),
    ("arcanine",     59),
    ("poliwag",      60),
    ("poliwhirl",    61),
    ("poliwrath",    62),
    ("abra",         63),
    ("kadabra",      64),
    ("alakazam",     65),
    ("machop",       66),
    ("machoke",      67),
    ("machamp",      68),
    ("bellsprout",   69),
    ("weepinbell",   70),
    ("victreebel",   71),
    ("tentacool",    72),
    ("tentacruel",   73),
    ("geodude",      74),
    ("graveler",     75),
    ("golem",        76),
    ("ponyta",       77),
    ("rapidash",     78),
    ("slowpoke",     79),
    ("slowbro",      80),
    ("magnemite",    81),
    ("magneton",     82),
    ("farfetchd",    83),
    ("doduo",        84),
    ("dodrio",       85),
    ("seel",         86),
    ("dewgong",      87),
    ("grimer",       88),
    ("muk",          89),
    ("shellder",     90),
    ("cloyster",     91),
    ("gastly",       92),
    ("haunter",      93),
    ("gengar",       94),
    ("onix",         95),
    ("drowzee",      96),
    ("hypno",        97),
    ("krabby",       98),
    ("kingler",      99),
    ("voltorb",      100),
    ("electrode",    101),
    ("exeggcute",    102),
    ("exeggutor",    103),
    ("cubone",       104),
    ("marowak",      105),
    ("hitmonlee",    106),
    ("hitmonchan",   107),
    ("lickitung",    108),
    ("koffing",      109),
    ("weezing",      110),
    ("rhyhorn",      111),
    ("rhydon",       112),
    ("chansey",      113),
    ("tangela",      114),
    ("kangaskhan",   115),
    ("horsea",       116),
    ("seadra",       117),
    ("goldeen",      118),
    ("seaking",      119),
    ("staryu",       120),
    ("starmie",      121),
    ("mr_mime",      122),
    ("scyther",      123),
    ("jynx",         124),
    ("electabuzz",   125),
    ("magmar",       126),
    ("pinsir",       127),
    ("tauros",       128),
    ("magikarp",     129),
    ("gyarados",     130),
    ("lapras",       131),
    ("ditto",        132),
    ("eevee",        133),
    ("vaporeon",     134),
    ("jolteon",      135),
    ("flareon",      136),
    ("porygon",      137),
    ("omanyte",      138),
    ("omastar",      139),
    ("kabuto",       140),
    ("kabutops",     141),
    ("aerodactyl",   142),
    ("snorlax",      143),
    ("articuno",     144),
    ("zapdos",       145),
    ("moltres",      146),
    ("dratini",      147),
    ("dragonair",    148),
    ("dragonite",    149),
    ("mewtwo",       150),
    ("mew",          151),
    ("chikorita",    152),
    ("bayleef",      153),
    ("meganium",     154),
    ("cyndaquil",    155),
    ("quilava",      156),
    ("typhlosion",   157),
    ("totodile",     158),
    ("croconaw",     159),
    ("feraligatr",   160),
    ("sentret",      161),
    ("furret",       162),
    ("hoothoot",     163),
    ("noctowl",      164),
    ("ledyba",       165),
    ("ledian",       166),
    ("spinarak",     167),
    ("ariados",      168),
    ("crobat",       169),
    ("chinchou",     170),
    ("lanturn",      171),
    ("pichu",        172),
    ("cleffa",       173),
    ("igglybuff",    174),
    ("togepi",       175),
    ("togetic",      176),
    ("natu",         177),
    ("xatu",         178),
    ("mareep",       179),
    ("flaaffy",      180),
    ("ampharos",     181),
    ("bellossom",    182),
    ("marill",       183),
    ("azumarill",    184),
    ("sudowoodo",    185),
    ("politoed",     186),
    ("hoppip",       187),
    ("skiploom",     188),
    ("jumpluff",     189),
    ("aipom",        190),
    ("sunkern",      191),
    ("sunflora",     192),
    ("yanma",        193),
    ("wooper",       194),
    ("quagsire",     195),
    ("espeon",       196),
    ("umbreon",      197),
    ("murkrow",      198),
    ("slowking",     199),
    ("misdreavus",   200),
    ("wobbuffet",    202),
    ("girafarig",    203),
    ("pineco",       204),
    ("forretress",   205),
    ("dunsparce",    206),
    ("gligar",       207),
    ("snubbull",     209),
    ("granbull",     210),
    ("qwilfish",     211),
    ("scizor",       212),
    ("shuckle",      213),
    ("heracross",    214),
    ("sneasel",      215),
    ("teddiursa",    216),
    ("ursaring",     217),
    ("slugma",       218),
    ("magcargo",     219),
    ("swinub",       220),
    ("piloswine",    221),
    ("corsola",      222),
    ("remoraid",     223),
    ("octillery",    224),
    ("delibird",     225),
    ("mantine",      226),
    ("skarmory",     227),
    ("houndour",     228),
    ("houndoom",     229),
    ("kingdra",      230),
    ("phanpy",       231),
    ("donphan",      232),
    ("porygon2",     233),
    ("stantler",     234),
    ("smeargle",     235),
    ("tyrogue",      236),
    ("hitmontop",    237),
    ("smoochum",     238),
    ("elekid",       239),
    ("magby",        240),
    ("miltank",      241),
    ("blissey",      242),
    ("raikou",       243),
    ("entei",        244),
    ("suicune",      245),
    ("larvitar",     246),
    ("pupitar",      247),
    ("tyranitar",    248),
    ("celebi",       251),
    ("treecko",      252),
    ("grovyle",      253),
    ("sceptile",     254),
    ("torchic",      255),
    ("combusken",    256),
    ("blaziken",     257),
    ("mudkip",       258),
    ("marshtomp",    259),
    ("swampert",     260),
    ("poochyena",    261),
    ("mightyena",    262),
    ("zigzagoon",    263),
    ("linoone",      264),
    ("wurmple",      265),
    ("silcoon",      266),
    ("beautifly",    267),
    ("cascoon",      268),
    ("dustox",       269),
    ("lotad",        270),
    ("lombre",       271),
    ("ludicolo",     272),
    ("seedot",       273),
    ("nuzleaf",      274),
    ("shiftry",      275),
    ("taillow",      276),
    ("swellow",      277),
    ("wingull",      278),
    ("pelipper",     279),
    ("ralts",        280),
    ("kirlia",       281),
    ("gardevoir",    282),
    ("surskit",      283),
    ("masquerain",   284),
    ("shroomish",    285),
    ("breloom",      286),
    ("slakoth",      287),
    ("vigoroth",     288),
    ("slaking",      289),
    ("nincada",      290),
    ("ninjask",      291),
    ("shedinja",     292),
    ("whismur",      293),
    ("loudred",      294),
    ("exploud",      295),
    ("makuhita",     296),
    ("hariyama",     297),
    ("azurill",      298),
    ("nosepass",     299),
    ("skitty",       300),
    ("delcatty",     301),
    ("sableye",      302),
    ("mawile",       303),
    ("aron",         304),
    ("lairon",       305),
    ("aggron",       306),
    ("meditite",     307),
    ("medicham",     308),
    ("electrike",    309),
    ("manectric",    310),
    ("plusle",       311),
    ("minun",        312),
    ("volbeat",      313),
    ("illumise",     314),
    ("roselia",      315),
    ("gulpin",       316),
    ("swalot",       317),
    ("carvanha",     318),
    ("sharpedo",     319),
    ("wailmer",      320),
    ("numel",        322),
    ("camerupt",     323),
    ("torkoal",      324),
    ("spoink",       325),
    ("grumpig",      326),
    ("spinda",       327),
    ("trapinch",     328),
    ("vibrava",      329),
    ("flygon",       330),
    ("cacnea",       331),
    ("cacturne",     332),
    ("swablu",       333),
    ("altaria",      334),
    ("zangoose",     335),
    ("seviper",      336),
    ("lunatone",     337),
    ("solrock",      338),
    ("barboach",     339),
    ("whiscash",     340),
    ("corphish",     341),
    ("crawdaunt",    342),
    ("baltoy",       343),
    ("claydol",      344),
    ("lileep",       345),
    ("cradily",      346),
    ("anorith",      347),
    ("armaldo",      348),
    ("feebas",       349),
    ("milotic",      350),
    ("castform",     351),
    ("kecleon",      352),
    ("shuppet",      353),
    ("banette",      354),
    ("duskull",      355),
    ("dusclops",     356),
    ("tropius",      357),
    ("chimecho",     358),
    ("absol",        359),
    ("wynaut",       360),
    ("snorunt",      361),
    ("glalie",       362),
    ("spheal",       363),
    ("sealeo",       364),
    ("walrein",      365),
    ("clamperl",     366),
    ("huntail",      367),
    ("gorebyss",     368),
    ("relicanth",    369),
    ("luvdisc",      370),
    ("bagon",        371),
    ("shelgon",      372),
    ("salamence",    373),
    ("beldum",       374),
    ("metang",       375),
    ("metagross",    376),
    ("regirock",     377),
    ("regice",       378),
    ("registeel",    379),
    ("latias",       380),
    ("latios",       381),
    ("jirachi",      385),
    ("deoxys",       386),
]

POKEMON_LARGE: list[tuple[str, int]] = [
    ("steelix",  208),
    ("lugia",    249),
    ("ho_oh",    250),
    ("wailord",  321),
    ("kyogre",   382),
    ("groudon",  383),
    ("rayquaza", 384),
]


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------

def main() -> None:
    PICS_DIR.mkdir(parents=True, exist_ok=True)
    PAL_DIR.mkdir(parents=True, exist_ok=True)

    mmodel_map = load_mmodel_map(MMODEL_H)
    print(f"Loaded {len(mmodel_map)} mmodel entries")

    ok = skipped = 0

    for name, dex in POKEMON:
        status = process(name, dex, mmodel_map, large=False)
        flag = '' if status.startswith('ok') else '  *** '
        print(f"  {flag}{name:16s} (#{dex:3d})  {status}")
        if status.startswith('ok'):
            ok += 1
        else:
            skipped += 1

    print("--- large sprites ---")
    for name, dex in POKEMON_LARGE:
        status = process(name, dex, mmodel_map, large=True)
        flag = '' if status.startswith('ok') else '  *** '
        print(f"  {flag}{name:16s} (#{dex:3d})  {status}")
        if status.startswith('ok'):
            ok += 1
        else:
            skipped += 1

    total = ok + skipped
    print(f"\nDone: {ok}/{total} generated, {skipped} skipped")


if __name__ == '__main__':
    main()
