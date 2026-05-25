#include "global.h"
#include "task.h"
#include "palette.h"
#include "sprite.h"
#include "fieldmap.h"
#include "field_player_avatar.h"
#include "event_object_movement.h"
#include "overworld.h"
#include "field_door.h"
#include "field_effect.h"
#include "constants/event_objects.h"
#include "constants/event_object_movement.h"
#include "constants/map_types.h"
#include "constants/species.h"
#include "follower_pokemon.h"
#include "field_effect_helpers.h"
#include "pokemon.h"
#include "sound.h"
#include "constants/songs.h"
#include "script.h"

// ---------------------------------------------------------------------------
// Per-species tile/palette arrays (defined in object_event_graphics.h, included
// by event_object_movement.c — they have external linkage so we can extern them).
// ---------------------------------------------------------------------------

extern const u32 gObjectEventPic_FollowerBulbasaur[];
extern const u16 gObjectEventPal_FollowerBulbasaur[];
extern const u32 gObjectEventPic_FollowerCharmander[];
extern const u16 gObjectEventPal_FollowerCharmander[];
extern const u32 gObjectEventPic_FollowerSquirtle[];
extern const u16 gObjectEventPal_FollowerSquirtle[];
extern const u32 gObjectEventPic_FollowerChikorita[];
extern const u16 gObjectEventPal_FollowerChikorita[];
extern const u32 gObjectEventPic_FollowerCyndaquil[];
extern const u16 gObjectEventPal_FollowerCyndaquil[];
extern const u32 gObjectEventPic_FollowerTotodile[];
extern const u16 gObjectEventPal_FollowerTotodile[];
extern const u32 gObjectEventPic_FollowerTreecko[];
extern const u16 gObjectEventPal_FollowerTreecko[];
extern const u32 gObjectEventPic_FollowerTorchic[];
extern const u16 gObjectEventPal_FollowerTorchic[];
extern const u32 gObjectEventPic_FollowerMudkip[];
extern const u16 gObjectEventPal_FollowerMudkip[];
extern const u32 gObjectEventPic_FollowerIvysaur[];
extern const u16 gObjectEventPal_FollowerIvysaur[];
extern const u32 gObjectEventPic_FollowerVenusaur[];
extern const u16 gObjectEventPal_FollowerVenusaur[];
extern const u32 gObjectEventPic_FollowerCharmeleon[];
extern const u16 gObjectEventPal_FollowerCharmeleon[];
extern const u32 gObjectEventPic_FollowerCharizard[];
extern const u16 gObjectEventPal_FollowerCharizard[];
extern const u32 gObjectEventPic_FollowerWartortle[];
extern const u16 gObjectEventPal_FollowerWartortle[];
extern const u32 gObjectEventPic_FollowerBlastoise[];
extern const u16 gObjectEventPal_FollowerBlastoise[];
extern const u32 gObjectEventPic_FollowerCaterpie[];
extern const u16 gObjectEventPal_FollowerCaterpie[];
extern const u32 gObjectEventPic_FollowerMetapod[];
extern const u16 gObjectEventPal_FollowerMetapod[];
extern const u32 gObjectEventPic_FollowerButterfree[];
extern const u16 gObjectEventPal_FollowerButterfree[];
extern const u32 gObjectEventPic_FollowerWeedle[];
extern const u16 gObjectEventPal_FollowerWeedle[];
extern const u32 gObjectEventPic_FollowerKakuna[];
extern const u16 gObjectEventPal_FollowerKakuna[];
extern const u32 gObjectEventPic_FollowerBeedrill[];
extern const u16 gObjectEventPal_FollowerBeedrill[];
extern const u32 gObjectEventPic_FollowerPidgey[];
extern const u16 gObjectEventPal_FollowerPidgey[];
extern const u32 gObjectEventPic_FollowerPidgeotto[];
extern const u16 gObjectEventPal_FollowerPidgeotto[];
extern const u32 gObjectEventPic_FollowerPidgeot[];
extern const u16 gObjectEventPal_FollowerPidgeot[];
extern const u32 gObjectEventPic_FollowerRattata[];
extern const u16 gObjectEventPal_FollowerRattata[];
extern const u32 gObjectEventPic_FollowerRaticate[];
extern const u16 gObjectEventPal_FollowerRaticate[];
extern const u32 gObjectEventPic_FollowerSpearow[];
extern const u16 gObjectEventPal_FollowerSpearow[];
extern const u32 gObjectEventPic_FollowerFearow[];
extern const u16 gObjectEventPal_FollowerFearow[];
extern const u32 gObjectEventPic_FollowerEkans[];
extern const u16 gObjectEventPal_FollowerEkans[];
extern const u32 gObjectEventPic_FollowerArbok[];
extern const u16 gObjectEventPal_FollowerArbok[];
extern const u32 gObjectEventPic_FollowerPikachu[];
extern const u16 gObjectEventPal_FollowerPikachu[];
extern const u32 gObjectEventPic_FollowerRaichu[];
extern const u16 gObjectEventPal_FollowerRaichu[];
extern const u32 gObjectEventPic_FollowerSandshrew[];
extern const u16 gObjectEventPal_FollowerSandshrew[];
extern const u32 gObjectEventPic_FollowerSandslash[];
extern const u16 gObjectEventPal_FollowerSandslash[];
extern const u32 gObjectEventPic_FollowerNidoranF[];
extern const u16 gObjectEventPal_FollowerNidoranF[];
extern const u32 gObjectEventPic_FollowerNidorina[];
extern const u16 gObjectEventPal_FollowerNidorina[];
extern const u32 gObjectEventPic_FollowerNidoqueen[];
extern const u16 gObjectEventPal_FollowerNidoqueen[];
extern const u32 gObjectEventPic_FollowerNidoranM[];
extern const u16 gObjectEventPal_FollowerNidoranM[];
extern const u32 gObjectEventPic_FollowerNidorino[];
extern const u16 gObjectEventPal_FollowerNidorino[];
extern const u32 gObjectEventPic_FollowerNidoking[];
extern const u16 gObjectEventPal_FollowerNidoking[];
extern const u32 gObjectEventPic_FollowerClefairy[];
extern const u16 gObjectEventPal_FollowerClefairy[];
extern const u32 gObjectEventPic_FollowerClefable[];
extern const u16 gObjectEventPal_FollowerClefable[];
extern const u32 gObjectEventPic_FollowerVulpix[];
extern const u16 gObjectEventPal_FollowerVulpix[];
extern const u32 gObjectEventPic_FollowerNinetales[];
extern const u16 gObjectEventPal_FollowerNinetales[];
extern const u32 gObjectEventPic_FollowerJigglypuff[];
extern const u16 gObjectEventPal_FollowerJigglypuff[];
extern const u32 gObjectEventPic_FollowerWigglytuff[];
extern const u16 gObjectEventPal_FollowerWigglytuff[];
extern const u32 gObjectEventPic_FollowerZubat[];
extern const u16 gObjectEventPal_FollowerZubat[];
extern const u32 gObjectEventPic_FollowerGolbat[];
extern const u16 gObjectEventPal_FollowerGolbat[];
extern const u32 gObjectEventPic_FollowerOddish[];
extern const u16 gObjectEventPal_FollowerOddish[];
extern const u32 gObjectEventPic_FollowerGloom[];
extern const u16 gObjectEventPal_FollowerGloom[];
extern const u32 gObjectEventPic_FollowerVileplume[];
extern const u16 gObjectEventPal_FollowerVileplume[];
extern const u32 gObjectEventPic_FollowerParas[];
extern const u16 gObjectEventPal_FollowerParas[];
extern const u32 gObjectEventPic_FollowerParasect[];
extern const u16 gObjectEventPal_FollowerParasect[];
extern const u32 gObjectEventPic_FollowerVenonat[];
extern const u16 gObjectEventPal_FollowerVenonat[];
extern const u32 gObjectEventPic_FollowerVenomoth[];
extern const u16 gObjectEventPal_FollowerVenomoth[];
extern const u32 gObjectEventPic_FollowerDiglett[];
extern const u16 gObjectEventPal_FollowerDiglett[];
extern const u32 gObjectEventPic_FollowerDugtrio[];
extern const u16 gObjectEventPal_FollowerDugtrio[];
extern const u32 gObjectEventPic_FollowerMeowth[];
extern const u16 gObjectEventPal_FollowerMeowth[];
extern const u32 gObjectEventPic_FollowerPersian[];
extern const u16 gObjectEventPal_FollowerPersian[];
extern const u32 gObjectEventPic_FollowerPsyduck[];
extern const u16 gObjectEventPal_FollowerPsyduck[];
extern const u32 gObjectEventPic_FollowerGolduck[];
extern const u16 gObjectEventPal_FollowerGolduck[];
extern const u32 gObjectEventPic_FollowerMankey[];
extern const u16 gObjectEventPal_FollowerMankey[];
extern const u32 gObjectEventPic_FollowerPrimeape[];
extern const u16 gObjectEventPal_FollowerPrimeape[];
extern const u32 gObjectEventPic_FollowerGrowlithe[];
extern const u16 gObjectEventPal_FollowerGrowlithe[];
extern const u32 gObjectEventPic_FollowerArcanine[];
extern const u16 gObjectEventPal_FollowerArcanine[];
extern const u32 gObjectEventPic_FollowerPoliwag[];
extern const u16 gObjectEventPal_FollowerPoliwag[];
extern const u32 gObjectEventPic_FollowerPoliwhirl[];
extern const u16 gObjectEventPal_FollowerPoliwhirl[];
extern const u32 gObjectEventPic_FollowerPoliwrath[];
extern const u16 gObjectEventPal_FollowerPoliwrath[];
extern const u32 gObjectEventPic_FollowerAbra[];
extern const u16 gObjectEventPal_FollowerAbra[];
extern const u32 gObjectEventPic_FollowerKadabra[];
extern const u16 gObjectEventPal_FollowerKadabra[];
extern const u32 gObjectEventPic_FollowerAlakazam[];
extern const u16 gObjectEventPal_FollowerAlakazam[];
extern const u32 gObjectEventPic_FollowerMachop[];
extern const u16 gObjectEventPal_FollowerMachop[];
extern const u32 gObjectEventPic_FollowerMachoke[];
extern const u16 gObjectEventPal_FollowerMachoke[];
extern const u32 gObjectEventPic_FollowerMachamp[];
extern const u16 gObjectEventPal_FollowerMachamp[];
extern const u32 gObjectEventPic_FollowerBellsprout[];
extern const u16 gObjectEventPal_FollowerBellsprout[];
extern const u32 gObjectEventPic_FollowerWeepinbell[];
extern const u16 gObjectEventPal_FollowerWeepinbell[];
extern const u32 gObjectEventPic_FollowerVictreebel[];
extern const u16 gObjectEventPal_FollowerVictreebel[];
extern const u32 gObjectEventPic_FollowerTentacool[];
extern const u16 gObjectEventPal_FollowerTentacool[];
extern const u32 gObjectEventPic_FollowerTentacruel[];
extern const u16 gObjectEventPal_FollowerTentacruel[];
extern const u32 gObjectEventPic_FollowerGeodude[];
extern const u16 gObjectEventPal_FollowerGeodude[];
extern const u32 gObjectEventPic_FollowerGraveler[];
extern const u16 gObjectEventPal_FollowerGraveler[];
extern const u32 gObjectEventPic_FollowerGolem[];
extern const u16 gObjectEventPal_FollowerGolem[];
extern const u32 gObjectEventPic_FollowerPonyta[];
extern const u16 gObjectEventPal_FollowerPonyta[];
extern const u32 gObjectEventPic_FollowerRapidash[];
extern const u16 gObjectEventPal_FollowerRapidash[];
extern const u32 gObjectEventPic_FollowerSlowpoke[];
extern const u16 gObjectEventPal_FollowerSlowpoke[];
extern const u32 gObjectEventPic_FollowerSlowbro[];
extern const u16 gObjectEventPal_FollowerSlowbro[];
extern const u32 gObjectEventPic_FollowerMagnemite[];
extern const u16 gObjectEventPal_FollowerMagnemite[];
extern const u32 gObjectEventPic_FollowerMagneton[];
extern const u16 gObjectEventPal_FollowerMagneton[];
extern const u32 gObjectEventPic_FollowerFarfetchd[];
extern const u16 gObjectEventPal_FollowerFarfetchd[];
extern const u32 gObjectEventPic_FollowerDoduo[];
extern const u16 gObjectEventPal_FollowerDoduo[];
extern const u32 gObjectEventPic_FollowerDodrio[];
extern const u16 gObjectEventPal_FollowerDodrio[];
extern const u32 gObjectEventPic_FollowerSeel[];
extern const u16 gObjectEventPal_FollowerSeel[];
extern const u32 gObjectEventPic_FollowerDewgong[];
extern const u16 gObjectEventPal_FollowerDewgong[];
extern const u32 gObjectEventPic_FollowerGrimer[];
extern const u16 gObjectEventPal_FollowerGrimer[];
extern const u32 gObjectEventPic_FollowerMuk[];
extern const u16 gObjectEventPal_FollowerMuk[];
extern const u32 gObjectEventPic_FollowerShellder[];
extern const u16 gObjectEventPal_FollowerShellder[];
extern const u32 gObjectEventPic_FollowerCloyster[];
extern const u16 gObjectEventPal_FollowerCloyster[];
extern const u32 gObjectEventPic_FollowerGastly[];
extern const u16 gObjectEventPal_FollowerGastly[];
extern const u32 gObjectEventPic_FollowerHaunter[];
extern const u16 gObjectEventPal_FollowerHaunter[];
extern const u32 gObjectEventPic_FollowerGengar[];
extern const u16 gObjectEventPal_FollowerGengar[];
extern const u32 gObjectEventPic_FollowerOnix[];
extern const u16 gObjectEventPal_FollowerOnix[];
extern const u32 gObjectEventPic_FollowerDrowzee[];
extern const u16 gObjectEventPal_FollowerDrowzee[];
extern const u32 gObjectEventPic_FollowerHypno[];
extern const u16 gObjectEventPal_FollowerHypno[];
extern const u32 gObjectEventPic_FollowerKrabby[];
extern const u16 gObjectEventPal_FollowerKrabby[];
extern const u32 gObjectEventPic_FollowerKingler[];
extern const u16 gObjectEventPal_FollowerKingler[];
extern const u32 gObjectEventPic_FollowerVoltorb[];
extern const u16 gObjectEventPal_FollowerVoltorb[];
extern const u32 gObjectEventPic_FollowerElectrode[];
extern const u16 gObjectEventPal_FollowerElectrode[];
extern const u32 gObjectEventPic_FollowerExeggcute[];
extern const u16 gObjectEventPal_FollowerExeggcute[];
extern const u32 gObjectEventPic_FollowerExeggutor[];
extern const u16 gObjectEventPal_FollowerExeggutor[];
extern const u32 gObjectEventPic_FollowerCubone[];
extern const u16 gObjectEventPal_FollowerCubone[];
extern const u32 gObjectEventPic_FollowerMarowak[];
extern const u16 gObjectEventPal_FollowerMarowak[];
extern const u32 gObjectEventPic_FollowerHitmonlee[];
extern const u16 gObjectEventPal_FollowerHitmonlee[];
extern const u32 gObjectEventPic_FollowerHitmonchan[];
extern const u16 gObjectEventPal_FollowerHitmonchan[];
extern const u32 gObjectEventPic_FollowerLickitung[];
extern const u16 gObjectEventPal_FollowerLickitung[];
extern const u32 gObjectEventPic_FollowerKoffing[];
extern const u16 gObjectEventPal_FollowerKoffing[];
extern const u32 gObjectEventPic_FollowerWeezing[];
extern const u16 gObjectEventPal_FollowerWeezing[];
extern const u32 gObjectEventPic_FollowerRhyhorn[];
extern const u16 gObjectEventPal_FollowerRhyhorn[];
extern const u32 gObjectEventPic_FollowerRhydon[];
extern const u16 gObjectEventPal_FollowerRhydon[];
extern const u32 gObjectEventPic_FollowerChansey[];
extern const u16 gObjectEventPal_FollowerChansey[];
extern const u32 gObjectEventPic_FollowerTangela[];
extern const u16 gObjectEventPal_FollowerTangela[];
extern const u32 gObjectEventPic_FollowerKangaskhan[];
extern const u16 gObjectEventPal_FollowerKangaskhan[];
extern const u32 gObjectEventPic_FollowerHorsea[];
extern const u16 gObjectEventPal_FollowerHorsea[];
extern const u32 gObjectEventPic_FollowerSeadra[];
extern const u16 gObjectEventPal_FollowerSeadra[];
extern const u32 gObjectEventPic_FollowerGoldeen[];
extern const u16 gObjectEventPal_FollowerGoldeen[];
extern const u32 gObjectEventPic_FollowerSeaking[];
extern const u16 gObjectEventPal_FollowerSeaking[];
extern const u32 gObjectEventPic_FollowerStaryu[];
extern const u16 gObjectEventPal_FollowerStaryu[];
extern const u32 gObjectEventPic_FollowerStarmie[];
extern const u16 gObjectEventPal_FollowerStarmie[];
extern const u32 gObjectEventPic_FollowerMrMime[];
extern const u16 gObjectEventPal_FollowerMrMime[];
extern const u32 gObjectEventPic_FollowerScyther[];
extern const u16 gObjectEventPal_FollowerScyther[];
extern const u32 gObjectEventPic_FollowerJynx[];
extern const u16 gObjectEventPal_FollowerJynx[];
extern const u32 gObjectEventPic_FollowerElectabuzz[];
extern const u16 gObjectEventPal_FollowerElectabuzz[];
extern const u32 gObjectEventPic_FollowerMagmar[];
extern const u16 gObjectEventPal_FollowerMagmar[];
extern const u32 gObjectEventPic_FollowerPinsir[];
extern const u16 gObjectEventPal_FollowerPinsir[];
extern const u32 gObjectEventPic_FollowerTauros[];
extern const u16 gObjectEventPal_FollowerTauros[];
extern const u32 gObjectEventPic_FollowerMagikarp[];
extern const u16 gObjectEventPal_FollowerMagikarp[];
extern const u32 gObjectEventPic_FollowerGyarados[];
extern const u16 gObjectEventPal_FollowerGyarados[];
extern const u32 gObjectEventPic_FollowerLapras[];
extern const u16 gObjectEventPal_FollowerLapras[];
extern const u32 gObjectEventPic_FollowerDitto[];
extern const u16 gObjectEventPal_FollowerDitto[];
extern const u32 gObjectEventPic_FollowerEevee[];
extern const u16 gObjectEventPal_FollowerEevee[];
extern const u32 gObjectEventPic_FollowerVaporeon[];
extern const u16 gObjectEventPal_FollowerVaporeon[];
extern const u32 gObjectEventPic_FollowerJolteon[];
extern const u16 gObjectEventPal_FollowerJolteon[];
extern const u32 gObjectEventPic_FollowerFlareon[];
extern const u16 gObjectEventPal_FollowerFlareon[];
extern const u32 gObjectEventPic_FollowerPorygon[];
extern const u16 gObjectEventPal_FollowerPorygon[];
extern const u32 gObjectEventPic_FollowerOmanyte[];
extern const u16 gObjectEventPal_FollowerOmanyte[];
extern const u32 gObjectEventPic_FollowerOmastar[];
extern const u16 gObjectEventPal_FollowerOmastar[];
extern const u32 gObjectEventPic_FollowerKabuto[];
extern const u16 gObjectEventPal_FollowerKabuto[];
extern const u32 gObjectEventPic_FollowerKabutops[];
extern const u16 gObjectEventPal_FollowerKabutops[];
extern const u32 gObjectEventPic_FollowerAerodactyl[];
extern const u16 gObjectEventPal_FollowerAerodactyl[];
extern const u32 gObjectEventPic_FollowerSnorlax[];
extern const u16 gObjectEventPal_FollowerSnorlax[];
extern const u32 gObjectEventPic_FollowerArticuno[];
extern const u16 gObjectEventPal_FollowerArticuno[];
extern const u32 gObjectEventPic_FollowerZapdos[];
extern const u16 gObjectEventPal_FollowerZapdos[];
extern const u32 gObjectEventPic_FollowerMoltres[];
extern const u16 gObjectEventPal_FollowerMoltres[];
extern const u32 gObjectEventPic_FollowerDratini[];
extern const u16 gObjectEventPal_FollowerDratini[];
extern const u32 gObjectEventPic_FollowerDragonair[];
extern const u16 gObjectEventPal_FollowerDragonair[];
extern const u32 gObjectEventPic_FollowerDragonite[];
extern const u16 gObjectEventPal_FollowerDragonite[];
extern const u32 gObjectEventPic_FollowerMewtwo[];
extern const u16 gObjectEventPal_FollowerMewtwo[];
extern const u32 gObjectEventPic_FollowerMew[];
extern const u16 gObjectEventPal_FollowerMew[];
extern const u32 gObjectEventPic_FollowerBayleef[];
extern const u16 gObjectEventPal_FollowerBayleef[];
extern const u32 gObjectEventPic_FollowerMeganium[];
extern const u16 gObjectEventPal_FollowerMeganium[];
extern const u32 gObjectEventPic_FollowerQuilava[];
extern const u16 gObjectEventPal_FollowerQuilava[];
extern const u32 gObjectEventPic_FollowerTyphlosion[];
extern const u16 gObjectEventPal_FollowerTyphlosion[];
extern const u32 gObjectEventPic_FollowerCroconaw[];
extern const u16 gObjectEventPal_FollowerCroconaw[];
extern const u32 gObjectEventPic_FollowerFeraligatr[];
extern const u16 gObjectEventPal_FollowerFeraligatr[];
extern const u32 gObjectEventPic_FollowerSentret[];
extern const u16 gObjectEventPal_FollowerSentret[];
extern const u32 gObjectEventPic_FollowerFurret[];
extern const u16 gObjectEventPal_FollowerFurret[];
extern const u32 gObjectEventPic_FollowerHoothoot[];
extern const u16 gObjectEventPal_FollowerHoothoot[];
extern const u32 gObjectEventPic_FollowerNoctowl[];
extern const u16 gObjectEventPal_FollowerNoctowl[];
extern const u32 gObjectEventPic_FollowerLedyba[];
extern const u16 gObjectEventPal_FollowerLedyba[];
extern const u32 gObjectEventPic_FollowerLedian[];
extern const u16 gObjectEventPal_FollowerLedian[];
extern const u32 gObjectEventPic_FollowerSpinarak[];
extern const u16 gObjectEventPal_FollowerSpinarak[];
extern const u32 gObjectEventPic_FollowerAriados[];
extern const u16 gObjectEventPal_FollowerAriados[];
extern const u32 gObjectEventPic_FollowerCrobat[];
extern const u16 gObjectEventPal_FollowerCrobat[];
extern const u32 gObjectEventPic_FollowerChinchou[];
extern const u16 gObjectEventPal_FollowerChinchou[];
extern const u32 gObjectEventPic_FollowerLanturn[];
extern const u16 gObjectEventPal_FollowerLanturn[];
extern const u32 gObjectEventPic_FollowerPichu[];
extern const u16 gObjectEventPal_FollowerPichu[];
extern const u32 gObjectEventPic_FollowerCleffa[];
extern const u16 gObjectEventPal_FollowerCleffa[];
extern const u32 gObjectEventPic_FollowerIgglybuff[];
extern const u16 gObjectEventPal_FollowerIgglybuff[];
extern const u32 gObjectEventPic_FollowerTogepi[];
extern const u16 gObjectEventPal_FollowerTogepi[];
extern const u32 gObjectEventPic_FollowerTogetic[];
extern const u16 gObjectEventPal_FollowerTogetic[];
extern const u32 gObjectEventPic_FollowerNatu[];
extern const u16 gObjectEventPal_FollowerNatu[];
extern const u32 gObjectEventPic_FollowerXatu[];
extern const u16 gObjectEventPal_FollowerXatu[];
extern const u32 gObjectEventPic_FollowerMareep[];
extern const u16 gObjectEventPal_FollowerMareep[];
extern const u32 gObjectEventPic_FollowerFlaaffy[];
extern const u16 gObjectEventPal_FollowerFlaaffy[];
extern const u32 gObjectEventPic_FollowerAmpharos[];
extern const u16 gObjectEventPal_FollowerAmpharos[];
extern const u32 gObjectEventPic_FollowerBellossom[];
extern const u16 gObjectEventPal_FollowerBellossom[];
extern const u32 gObjectEventPic_FollowerMarill[];
extern const u16 gObjectEventPal_FollowerMarill[];
extern const u32 gObjectEventPic_FollowerAzumarill[];
extern const u16 gObjectEventPal_FollowerAzumarill[];
extern const u32 gObjectEventPic_FollowerSudowoodo[];
extern const u16 gObjectEventPal_FollowerSudowoodo[];
extern const u32 gObjectEventPic_FollowerPolitoed[];
extern const u16 gObjectEventPal_FollowerPolitoed[];
extern const u32 gObjectEventPic_FollowerHoppip[];
extern const u16 gObjectEventPal_FollowerHoppip[];
extern const u32 gObjectEventPic_FollowerSkiploom[];
extern const u16 gObjectEventPal_FollowerSkiploom[];
extern const u32 gObjectEventPic_FollowerJumpluff[];
extern const u16 gObjectEventPal_FollowerJumpluff[];
extern const u32 gObjectEventPic_FollowerAipom[];
extern const u16 gObjectEventPal_FollowerAipom[];
extern const u32 gObjectEventPic_FollowerSunkern[];
extern const u16 gObjectEventPal_FollowerSunkern[];
extern const u32 gObjectEventPic_FollowerSunflora[];
extern const u16 gObjectEventPal_FollowerSunflora[];
extern const u32 gObjectEventPic_FollowerYanma[];
extern const u16 gObjectEventPal_FollowerYanma[];
extern const u32 gObjectEventPic_FollowerWooper[];
extern const u16 gObjectEventPal_FollowerWooper[];
extern const u32 gObjectEventPic_FollowerQuagsire[];
extern const u16 gObjectEventPal_FollowerQuagsire[];
extern const u32 gObjectEventPic_FollowerEspeon[];
extern const u16 gObjectEventPal_FollowerEspeon[];
extern const u32 gObjectEventPic_FollowerUmbreon[];
extern const u16 gObjectEventPal_FollowerUmbreon[];
extern const u32 gObjectEventPic_FollowerMurkrow[];
extern const u16 gObjectEventPal_FollowerMurkrow[];
extern const u32 gObjectEventPic_FollowerSlowking[];
extern const u16 gObjectEventPal_FollowerSlowking[];
extern const u32 gObjectEventPic_FollowerMisdreavus[];
extern const u16 gObjectEventPal_FollowerMisdreavus[];
extern const u32 gObjectEventPic_FollowerWobbuffet[];
extern const u16 gObjectEventPal_FollowerWobbuffet[];
extern const u32 gObjectEventPic_FollowerGirafarig[];
extern const u16 gObjectEventPal_FollowerGirafarig[];
extern const u32 gObjectEventPic_FollowerPineco[];
extern const u16 gObjectEventPal_FollowerPineco[];
extern const u32 gObjectEventPic_FollowerForretress[];
extern const u16 gObjectEventPal_FollowerForretress[];
extern const u32 gObjectEventPic_FollowerDunsparce[];
extern const u16 gObjectEventPal_FollowerDunsparce[];
extern const u32 gObjectEventPic_FollowerGligar[];
extern const u16 gObjectEventPal_FollowerGligar[];
extern const u32 gObjectEventPic_FollowerSnubbull[];
extern const u16 gObjectEventPal_FollowerSnubbull[];
extern const u32 gObjectEventPic_FollowerGranbull[];
extern const u16 gObjectEventPal_FollowerGranbull[];
extern const u32 gObjectEventPic_FollowerQwilfish[];
extern const u16 gObjectEventPal_FollowerQwilfish[];
extern const u32 gObjectEventPic_FollowerScizor[];
extern const u16 gObjectEventPal_FollowerScizor[];
extern const u32 gObjectEventPic_FollowerShuckle[];
extern const u16 gObjectEventPal_FollowerShuckle[];
extern const u32 gObjectEventPic_FollowerHeracross[];
extern const u16 gObjectEventPal_FollowerHeracross[];
extern const u32 gObjectEventPic_FollowerSneasel[];
extern const u16 gObjectEventPal_FollowerSneasel[];
extern const u32 gObjectEventPic_FollowerTeddiursa[];
extern const u16 gObjectEventPal_FollowerTeddiursa[];
extern const u32 gObjectEventPic_FollowerUrsaring[];
extern const u16 gObjectEventPal_FollowerUrsaring[];
extern const u32 gObjectEventPic_FollowerSlugma[];
extern const u16 gObjectEventPal_FollowerSlugma[];
extern const u32 gObjectEventPic_FollowerMagcargo[];
extern const u16 gObjectEventPal_FollowerMagcargo[];
extern const u32 gObjectEventPic_FollowerSwinub[];
extern const u16 gObjectEventPal_FollowerSwinub[];
extern const u32 gObjectEventPic_FollowerPiloswine[];
extern const u16 gObjectEventPal_FollowerPiloswine[];
extern const u32 gObjectEventPic_FollowerCorsola[];
extern const u16 gObjectEventPal_FollowerCorsola[];
extern const u32 gObjectEventPic_FollowerRemoraid[];
extern const u16 gObjectEventPal_FollowerRemoraid[];
extern const u32 gObjectEventPic_FollowerOctillery[];
extern const u16 gObjectEventPal_FollowerOctillery[];
extern const u32 gObjectEventPic_FollowerDelibird[];
extern const u16 gObjectEventPal_FollowerDelibird[];
extern const u32 gObjectEventPic_FollowerMantine[];
extern const u16 gObjectEventPal_FollowerMantine[];
extern const u32 gObjectEventPic_FollowerSkarmory[];
extern const u16 gObjectEventPal_FollowerSkarmory[];
extern const u32 gObjectEventPic_FollowerHoundour[];
extern const u16 gObjectEventPal_FollowerHoundour[];
extern const u32 gObjectEventPic_FollowerHoundoom[];
extern const u16 gObjectEventPal_FollowerHoundoom[];
extern const u32 gObjectEventPic_FollowerKingdra[];
extern const u16 gObjectEventPal_FollowerKingdra[];
extern const u32 gObjectEventPic_FollowerPhanpy[];
extern const u16 gObjectEventPal_FollowerPhanpy[];
extern const u32 gObjectEventPic_FollowerDonphan[];
extern const u16 gObjectEventPal_FollowerDonphan[];
extern const u32 gObjectEventPic_FollowerPorygon2[];
extern const u16 gObjectEventPal_FollowerPorygon2[];
extern const u32 gObjectEventPic_FollowerStantler[];
extern const u16 gObjectEventPal_FollowerStantler[];
extern const u32 gObjectEventPic_FollowerSmeargle[];
extern const u16 gObjectEventPal_FollowerSmeargle[];
extern const u32 gObjectEventPic_FollowerTyrogue[];
extern const u16 gObjectEventPal_FollowerTyrogue[];
extern const u32 gObjectEventPic_FollowerHitmontop[];
extern const u16 gObjectEventPal_FollowerHitmontop[];
extern const u32 gObjectEventPic_FollowerSmoochum[];
extern const u16 gObjectEventPal_FollowerSmoochum[];
extern const u32 gObjectEventPic_FollowerElekid[];
extern const u16 gObjectEventPal_FollowerElekid[];
extern const u32 gObjectEventPic_FollowerMagby[];
extern const u16 gObjectEventPal_FollowerMagby[];
extern const u32 gObjectEventPic_FollowerMiltank[];
extern const u16 gObjectEventPal_FollowerMiltank[];
extern const u32 gObjectEventPic_FollowerBlissey[];
extern const u16 gObjectEventPal_FollowerBlissey[];
extern const u32 gObjectEventPic_FollowerRaikou[];
extern const u16 gObjectEventPal_FollowerRaikou[];
extern const u32 gObjectEventPic_FollowerEntei[];
extern const u16 gObjectEventPal_FollowerEntei[];
extern const u32 gObjectEventPic_FollowerSuicune[];
extern const u16 gObjectEventPal_FollowerSuicune[];
extern const u32 gObjectEventPic_FollowerLarvitar[];
extern const u16 gObjectEventPal_FollowerLarvitar[];
extern const u32 gObjectEventPic_FollowerPupitar[];
extern const u16 gObjectEventPal_FollowerPupitar[];
extern const u32 gObjectEventPic_FollowerTyranitar[];
extern const u16 gObjectEventPal_FollowerTyranitar[];
extern const u32 gObjectEventPic_FollowerCelebi[];
extern const u16 gObjectEventPal_FollowerCelebi[];
extern const u32 gObjectEventPic_FollowerGrovyle[];
extern const u16 gObjectEventPal_FollowerGrovyle[];
extern const u32 gObjectEventPic_FollowerSceptile[];
extern const u16 gObjectEventPal_FollowerSceptile[];
extern const u32 gObjectEventPic_FollowerCombusken[];
extern const u16 gObjectEventPal_FollowerCombusken[];
extern const u32 gObjectEventPic_FollowerBlaziken[];
extern const u16 gObjectEventPal_FollowerBlaziken[];
extern const u32 gObjectEventPic_FollowerMarshtomp[];
extern const u16 gObjectEventPal_FollowerMarshtomp[];
extern const u32 gObjectEventPic_FollowerSwampert[];
extern const u16 gObjectEventPal_FollowerSwampert[];
extern const u32 gObjectEventPic_FollowerPoochyena[];
extern const u16 gObjectEventPal_FollowerPoochyena[];
extern const u32 gObjectEventPic_FollowerMightyena[];
extern const u16 gObjectEventPal_FollowerMightyena[];
extern const u32 gObjectEventPic_FollowerZigzagoon[];
extern const u16 gObjectEventPal_FollowerZigzagoon[];
extern const u32 gObjectEventPic_FollowerLinoone[];
extern const u16 gObjectEventPal_FollowerLinoone[];
extern const u32 gObjectEventPic_FollowerWurmple[];
extern const u16 gObjectEventPal_FollowerWurmple[];
extern const u32 gObjectEventPic_FollowerSilcoon[];
extern const u16 gObjectEventPal_FollowerSilcoon[];
extern const u32 gObjectEventPic_FollowerBeautifly[];
extern const u16 gObjectEventPal_FollowerBeautifly[];
extern const u32 gObjectEventPic_FollowerCascoon[];
extern const u16 gObjectEventPal_FollowerCascoon[];
extern const u32 gObjectEventPic_FollowerDustox[];
extern const u16 gObjectEventPal_FollowerDustox[];
extern const u32 gObjectEventPic_FollowerLotad[];
extern const u16 gObjectEventPal_FollowerLotad[];
extern const u32 gObjectEventPic_FollowerLombre[];
extern const u16 gObjectEventPal_FollowerLombre[];
extern const u32 gObjectEventPic_FollowerLudicolo[];
extern const u16 gObjectEventPal_FollowerLudicolo[];
extern const u32 gObjectEventPic_FollowerSeedot[];
extern const u16 gObjectEventPal_FollowerSeedot[];
extern const u32 gObjectEventPic_FollowerNuzleaf[];
extern const u16 gObjectEventPal_FollowerNuzleaf[];
extern const u32 gObjectEventPic_FollowerShiftry[];
extern const u16 gObjectEventPal_FollowerShiftry[];
extern const u32 gObjectEventPic_FollowerNincada[];
extern const u16 gObjectEventPal_FollowerNincada[];
extern const u32 gObjectEventPic_FollowerNinjask[];
extern const u16 gObjectEventPal_FollowerNinjask[];
extern const u32 gObjectEventPic_FollowerShedinja[];
extern const u16 gObjectEventPal_FollowerShedinja[];
extern const u32 gObjectEventPic_FollowerTaillow[];
extern const u16 gObjectEventPal_FollowerTaillow[];
extern const u32 gObjectEventPic_FollowerSwellow[];
extern const u16 gObjectEventPal_FollowerSwellow[];
extern const u32 gObjectEventPic_FollowerShroomish[];
extern const u16 gObjectEventPal_FollowerShroomish[];
extern const u32 gObjectEventPic_FollowerBreloom[];
extern const u16 gObjectEventPal_FollowerBreloom[];
extern const u32 gObjectEventPic_FollowerSpinda[];
extern const u16 gObjectEventPal_FollowerSpinda[];
extern const u32 gObjectEventPic_FollowerWingull[];
extern const u16 gObjectEventPal_FollowerWingull[];
extern const u32 gObjectEventPic_FollowerPelipper[];
extern const u16 gObjectEventPal_FollowerPelipper[];
extern const u32 gObjectEventPic_FollowerSurskit[];
extern const u16 gObjectEventPal_FollowerSurskit[];
extern const u32 gObjectEventPic_FollowerMasquerain[];
extern const u16 gObjectEventPal_FollowerMasquerain[];
extern const u32 gObjectEventPic_FollowerWailmer[];
extern const u16 gObjectEventPal_FollowerWailmer[];
extern const u32 gObjectEventPic_FollowerSkitty[];
extern const u16 gObjectEventPal_FollowerSkitty[];
extern const u32 gObjectEventPic_FollowerDelcatty[];
extern const u16 gObjectEventPal_FollowerDelcatty[];
extern const u32 gObjectEventPic_FollowerKecleon[];
extern const u16 gObjectEventPal_FollowerKecleon[];
extern const u32 gObjectEventPic_FollowerBaltoy[];
extern const u16 gObjectEventPal_FollowerBaltoy[];
extern const u32 gObjectEventPic_FollowerClaydol[];
extern const u16 gObjectEventPal_FollowerClaydol[];
extern const u32 gObjectEventPic_FollowerNosepass[];
extern const u16 gObjectEventPal_FollowerNosepass[];
extern const u32 gObjectEventPic_FollowerTorkoal[];
extern const u16 gObjectEventPal_FollowerTorkoal[];
extern const u32 gObjectEventPic_FollowerSableye[];
extern const u16 gObjectEventPal_FollowerSableye[];
extern const u32 gObjectEventPic_FollowerBarboach[];
extern const u16 gObjectEventPal_FollowerBarboach[];
extern const u32 gObjectEventPic_FollowerWhiscash[];
extern const u16 gObjectEventPal_FollowerWhiscash[];
extern const u32 gObjectEventPic_FollowerLuvdisc[];
extern const u16 gObjectEventPal_FollowerLuvdisc[];
extern const u32 gObjectEventPic_FollowerCorphish[];
extern const u16 gObjectEventPal_FollowerCorphish[];
extern const u32 gObjectEventPic_FollowerCrawdaunt[];
extern const u16 gObjectEventPal_FollowerCrawdaunt[];
extern const u32 gObjectEventPic_FollowerFeebas[];
extern const u16 gObjectEventPal_FollowerFeebas[];
extern const u32 gObjectEventPic_FollowerMilotic[];
extern const u16 gObjectEventPal_FollowerMilotic[];
extern const u32 gObjectEventPic_FollowerCarvanha[];
extern const u16 gObjectEventPal_FollowerCarvanha[];
extern const u32 gObjectEventPic_FollowerSharpedo[];
extern const u16 gObjectEventPal_FollowerSharpedo[];
extern const u32 gObjectEventPic_FollowerTrapinch[];
extern const u16 gObjectEventPal_FollowerTrapinch[];
extern const u32 gObjectEventPic_FollowerVibrava[];
extern const u16 gObjectEventPal_FollowerVibrava[];
extern const u32 gObjectEventPic_FollowerFlygon[];
extern const u16 gObjectEventPal_FollowerFlygon[];
extern const u32 gObjectEventPic_FollowerMakuhita[];
extern const u16 gObjectEventPal_FollowerMakuhita[];
extern const u32 gObjectEventPic_FollowerHariyama[];
extern const u16 gObjectEventPal_FollowerHariyama[];
extern const u32 gObjectEventPic_FollowerElectrike[];
extern const u16 gObjectEventPal_FollowerElectrike[];
extern const u32 gObjectEventPic_FollowerManectric[];
extern const u16 gObjectEventPal_FollowerManectric[];
extern const u32 gObjectEventPic_FollowerNumel[];
extern const u16 gObjectEventPal_FollowerNumel[];
extern const u32 gObjectEventPic_FollowerCamerupt[];
extern const u16 gObjectEventPal_FollowerCamerupt[];
extern const u32 gObjectEventPic_FollowerSpheal[];
extern const u16 gObjectEventPal_FollowerSpheal[];
extern const u32 gObjectEventPic_FollowerSealeo[];
extern const u16 gObjectEventPal_FollowerSealeo[];
extern const u32 gObjectEventPic_FollowerWalrein[];
extern const u16 gObjectEventPal_FollowerWalrein[];
extern const u32 gObjectEventPic_FollowerCacnea[];
extern const u16 gObjectEventPal_FollowerCacnea[];
extern const u32 gObjectEventPic_FollowerCacturne[];
extern const u16 gObjectEventPal_FollowerCacturne[];
extern const u32 gObjectEventPic_FollowerSnorunt[];
extern const u16 gObjectEventPal_FollowerSnorunt[];
extern const u32 gObjectEventPic_FollowerGlalie[];
extern const u16 gObjectEventPal_FollowerGlalie[];
extern const u32 gObjectEventPic_FollowerLunatone[];
extern const u16 gObjectEventPal_FollowerLunatone[];
extern const u32 gObjectEventPic_FollowerSolrock[];
extern const u16 gObjectEventPal_FollowerSolrock[];
extern const u32 gObjectEventPic_FollowerAzurill[];
extern const u16 gObjectEventPal_FollowerAzurill[];
extern const u32 gObjectEventPic_FollowerSpoink[];
extern const u16 gObjectEventPal_FollowerSpoink[];
extern const u32 gObjectEventPic_FollowerGrumpig[];
extern const u16 gObjectEventPal_FollowerGrumpig[];
extern const u32 gObjectEventPic_FollowerPlusle[];
extern const u16 gObjectEventPal_FollowerPlusle[];
extern const u32 gObjectEventPic_FollowerMinun[];
extern const u16 gObjectEventPal_FollowerMinun[];
extern const u32 gObjectEventPic_FollowerMawile[];
extern const u16 gObjectEventPal_FollowerMawile[];
extern const u32 gObjectEventPic_FollowerMeditite[];
extern const u16 gObjectEventPal_FollowerMeditite[];
extern const u32 gObjectEventPic_FollowerMedicham[];
extern const u16 gObjectEventPal_FollowerMedicham[];
extern const u32 gObjectEventPic_FollowerSwablu[];
extern const u16 gObjectEventPal_FollowerSwablu[];
extern const u32 gObjectEventPic_FollowerAltaria[];
extern const u16 gObjectEventPal_FollowerAltaria[];
extern const u32 gObjectEventPic_FollowerWynaut[];
extern const u16 gObjectEventPal_FollowerWynaut[];
extern const u32 gObjectEventPic_FollowerDuskull[];
extern const u16 gObjectEventPal_FollowerDuskull[];
extern const u32 gObjectEventPic_FollowerDusclops[];
extern const u16 gObjectEventPal_FollowerDusclops[];
extern const u32 gObjectEventPic_FollowerRoselia[];
extern const u16 gObjectEventPal_FollowerRoselia[];
extern const u32 gObjectEventPic_FollowerSlakoth[];
extern const u16 gObjectEventPal_FollowerSlakoth[];
extern const u32 gObjectEventPic_FollowerVigoroth[];
extern const u16 gObjectEventPal_FollowerVigoroth[];
extern const u32 gObjectEventPic_FollowerSlaking[];
extern const u16 gObjectEventPal_FollowerSlaking[];
extern const u32 gObjectEventPic_FollowerGulpin[];
extern const u16 gObjectEventPal_FollowerGulpin[];
extern const u32 gObjectEventPic_FollowerSwalot[];
extern const u16 gObjectEventPal_FollowerSwalot[];
extern const u32 gObjectEventPic_FollowerTropius[];
extern const u16 gObjectEventPal_FollowerTropius[];
extern const u32 gObjectEventPic_FollowerWhismur[];
extern const u16 gObjectEventPal_FollowerWhismur[];
extern const u32 gObjectEventPic_FollowerLoudred[];
extern const u16 gObjectEventPal_FollowerLoudred[];
extern const u32 gObjectEventPic_FollowerExploud[];
extern const u16 gObjectEventPal_FollowerExploud[];
extern const u32 gObjectEventPic_FollowerClamperl[];
extern const u16 gObjectEventPal_FollowerClamperl[];
extern const u32 gObjectEventPic_FollowerHuntail[];
extern const u16 gObjectEventPal_FollowerHuntail[];
extern const u32 gObjectEventPic_FollowerGorebyss[];
extern const u16 gObjectEventPal_FollowerGorebyss[];
extern const u32 gObjectEventPic_FollowerAbsol[];
extern const u16 gObjectEventPal_FollowerAbsol[];
extern const u32 gObjectEventPic_FollowerShuppet[];
extern const u16 gObjectEventPal_FollowerShuppet[];
extern const u32 gObjectEventPic_FollowerBanette[];
extern const u16 gObjectEventPal_FollowerBanette[];
extern const u32 gObjectEventPic_FollowerSeviper[];
extern const u16 gObjectEventPal_FollowerSeviper[];
extern const u32 gObjectEventPic_FollowerZangoose[];
extern const u16 gObjectEventPal_FollowerZangoose[];
extern const u32 gObjectEventPic_FollowerRelicanth[];
extern const u16 gObjectEventPal_FollowerRelicanth[];
extern const u32 gObjectEventPic_FollowerAron[];
extern const u16 gObjectEventPal_FollowerAron[];
extern const u32 gObjectEventPic_FollowerLairon[];
extern const u16 gObjectEventPal_FollowerLairon[];
extern const u32 gObjectEventPic_FollowerAggron[];
extern const u16 gObjectEventPal_FollowerAggron[];
extern const u32 gObjectEventPic_FollowerCastform[];
extern const u16 gObjectEventPal_FollowerCastform[];
extern const u32 gObjectEventPic_FollowerVolbeat[];
extern const u16 gObjectEventPal_FollowerVolbeat[];
extern const u32 gObjectEventPic_FollowerIllumise[];
extern const u16 gObjectEventPal_FollowerIllumise[];
extern const u32 gObjectEventPic_FollowerLileep[];
extern const u16 gObjectEventPal_FollowerLileep[];
extern const u32 gObjectEventPic_FollowerCradily[];
extern const u16 gObjectEventPal_FollowerCradily[];
extern const u32 gObjectEventPic_FollowerAnorith[];
extern const u16 gObjectEventPal_FollowerAnorith[];
extern const u32 gObjectEventPic_FollowerArmaldo[];
extern const u16 gObjectEventPal_FollowerArmaldo[];
extern const u32 gObjectEventPic_FollowerRalts[];
extern const u16 gObjectEventPal_FollowerRalts[];
extern const u32 gObjectEventPic_FollowerKirlia[];
extern const u16 gObjectEventPal_FollowerKirlia[];
extern const u32 gObjectEventPic_FollowerGardevoir[];
extern const u16 gObjectEventPal_FollowerGardevoir[];
extern const u32 gObjectEventPic_FollowerBagon[];
extern const u16 gObjectEventPal_FollowerBagon[];
extern const u32 gObjectEventPic_FollowerShelgon[];
extern const u16 gObjectEventPal_FollowerShelgon[];
extern const u32 gObjectEventPic_FollowerSalamence[];
extern const u16 gObjectEventPal_FollowerSalamence[];
extern const u32 gObjectEventPic_FollowerBeldum[];
extern const u16 gObjectEventPal_FollowerBeldum[];
extern const u32 gObjectEventPic_FollowerMetang[];
extern const u16 gObjectEventPal_FollowerMetang[];
extern const u32 gObjectEventPic_FollowerMetagross[];
extern const u16 gObjectEventPal_FollowerMetagross[];
extern const u32 gObjectEventPic_FollowerRegirock[];
extern const u16 gObjectEventPal_FollowerRegirock[];
extern const u32 gObjectEventPic_FollowerRegice[];
extern const u16 gObjectEventPal_FollowerRegice[];
extern const u32 gObjectEventPic_FollowerRegisteel[];
extern const u16 gObjectEventPal_FollowerRegisteel[];
extern const u32 gObjectEventPic_FollowerLatias[];
extern const u16 gObjectEventPal_FollowerLatias[];
extern const u32 gObjectEventPic_FollowerLatios[];
extern const u16 gObjectEventPal_FollowerLatios[];
extern const u32 gObjectEventPic_FollowerJirachi[];
extern const u16 gObjectEventPal_FollowerJirachi[];
extern const u32 gObjectEventPic_FollowerDeoxys[];
extern const u16 gObjectEventPal_FollowerDeoxys[];
extern const u32 gObjectEventPic_FollowerChimecho[];
extern const u16 gObjectEventPal_FollowerChimecho[];
extern const u32 gObjectEventPic_FollowerUnownA[];
extern const u32 gObjectEventPic_FollowerUnownB[];
extern const u32 gObjectEventPic_FollowerUnownC[];
extern const u32 gObjectEventPic_FollowerUnownD[];
extern const u32 gObjectEventPic_FollowerUnownE[];
extern const u32 gObjectEventPic_FollowerUnownF[];
extern const u32 gObjectEventPic_FollowerUnownG[];
extern const u32 gObjectEventPic_FollowerUnownH[];
extern const u32 gObjectEventPic_FollowerUnownI[];
extern const u32 gObjectEventPic_FollowerUnownJ[];
extern const u32 gObjectEventPic_FollowerUnownK[];
extern const u32 gObjectEventPic_FollowerUnownL[];
extern const u32 gObjectEventPic_FollowerUnownM[];
extern const u32 gObjectEventPic_FollowerUnownN[];
extern const u32 gObjectEventPic_FollowerUnownO[];
extern const u32 gObjectEventPic_FollowerUnownP[];
extern const u32 gObjectEventPic_FollowerUnownQ[];
extern const u32 gObjectEventPic_FollowerUnownR[];
extern const u32 gObjectEventPic_FollowerUnownS[];
extern const u32 gObjectEventPic_FollowerUnownT[];
extern const u32 gObjectEventPic_FollowerUnownU[];
extern const u32 gObjectEventPic_FollowerUnownV[];
extern const u32 gObjectEventPic_FollowerUnownW[];
extern const u32 gObjectEventPic_FollowerUnownX[];
extern const u32 gObjectEventPic_FollowerUnownY[];
extern const u32 gObjectEventPic_FollowerUnownZ[];
extern const u32 gObjectEventPic_FollowerUnownExclamation[];
extern const u32 gObjectEventPic_FollowerUnownQuestion[];
extern const u16 gObjectEventPal_FollowerUnown1[];
extern const u16 gObjectEventPal_FollowerUnown2[];
extern const u32 gObjectEventPic_FollowerSteelix[];
extern const u16 gObjectEventPal_FollowerSteelix[];
extern const u32 gObjectEventPic_FollowerLugia[];
extern const u16 gObjectEventPal_FollowerLugia[];
extern const u32 gObjectEventPic_FollowerHoOh[];
extern const u16 gObjectEventPal_FollowerHoOh[];
extern const u32 gObjectEventPic_FollowerWailord[];
extern const u16 gObjectEventPal_FollowerWailord[];
extern const u32 gObjectEventPic_FollowerKyogre[];
extern const u16 gObjectEventPal_FollowerKyogre[];
extern const u32 gObjectEventPic_FollowerGroudon[];
extern const u16 gObjectEventPal_FollowerGroudon[];
extern const u32 gObjectEventPic_FollowerRayquaza[];
extern const u16 gObjectEventPal_FollowerRayquaza[];

// Shiny palette externs.
extern const u16 gObjectEventPal_FollowerBulbasaurShiny[];
extern const u16 gObjectEventPal_FollowerCharmanderShiny[];
extern const u16 gObjectEventPal_FollowerSquirtleShiny[];
extern const u16 gObjectEventPal_FollowerChikoritaShiny[];
extern const u16 gObjectEventPal_FollowerCyndaquilShiny[];
extern const u16 gObjectEventPal_FollowerTotodileShiny[];
extern const u16 gObjectEventPal_FollowerTreeckoShiny[];
extern const u16 gObjectEventPal_FollowerTorchicShiny[];
extern const u16 gObjectEventPal_FollowerMudkipShiny[];
extern const u16 gObjectEventPal_FollowerIvysaurShiny[];
extern const u16 gObjectEventPal_FollowerVenusaurShiny[];
extern const u16 gObjectEventPal_FollowerCharmeleonShiny[];
extern const u16 gObjectEventPal_FollowerCharizardShiny[];
extern const u16 gObjectEventPal_FollowerWartortleShiny[];
extern const u16 gObjectEventPal_FollowerBlastoiseShiny[];
extern const u16 gObjectEventPal_FollowerCaterpieShiny[];
extern const u16 gObjectEventPal_FollowerMetapodShiny[];
extern const u16 gObjectEventPal_FollowerButterfreeShiny[];
extern const u16 gObjectEventPal_FollowerWeedleShiny[];
extern const u16 gObjectEventPal_FollowerKakunaShiny[];
extern const u16 gObjectEventPal_FollowerBeedrillShiny[];
extern const u16 gObjectEventPal_FollowerPidgeyShiny[];
extern const u16 gObjectEventPal_FollowerPidgeottoShiny[];
extern const u16 gObjectEventPal_FollowerPidgeotShiny[];
extern const u16 gObjectEventPal_FollowerRattataShiny[];
extern const u16 gObjectEventPal_FollowerRaticateShiny[];
extern const u16 gObjectEventPal_FollowerSpearowShiny[];
extern const u16 gObjectEventPal_FollowerFearowShiny[];
extern const u16 gObjectEventPal_FollowerEkansShiny[];
extern const u16 gObjectEventPal_FollowerArbokShiny[];
extern const u16 gObjectEventPal_FollowerPikachuShiny[];
extern const u16 gObjectEventPal_FollowerRaichuShiny[];
extern const u16 gObjectEventPal_FollowerSandshrewShiny[];
extern const u16 gObjectEventPal_FollowerSandslashShiny[];
extern const u16 gObjectEventPal_FollowerNidoranFShiny[];
extern const u16 gObjectEventPal_FollowerNidorinaShiny[];
extern const u16 gObjectEventPal_FollowerNidoqueenShiny[];
extern const u16 gObjectEventPal_FollowerNidoranMShiny[];
extern const u16 gObjectEventPal_FollowerNidorinoShiny[];
extern const u16 gObjectEventPal_FollowerNidokingShiny[];
extern const u16 gObjectEventPal_FollowerClefairyShiny[];
extern const u16 gObjectEventPal_FollowerClefableShiny[];
extern const u16 gObjectEventPal_FollowerVulpixShiny[];
extern const u16 gObjectEventPal_FollowerNinetalesShiny[];
extern const u16 gObjectEventPal_FollowerJigglypuffShiny[];
extern const u16 gObjectEventPal_FollowerWigglytuffShiny[];
extern const u16 gObjectEventPal_FollowerZubatShiny[];
extern const u16 gObjectEventPal_FollowerGolbatShiny[];
extern const u16 gObjectEventPal_FollowerOddishShiny[];
extern const u16 gObjectEventPal_FollowerGloomShiny[];
extern const u16 gObjectEventPal_FollowerVileplumeShiny[];
extern const u16 gObjectEventPal_FollowerParasShiny[];
extern const u16 gObjectEventPal_FollowerParasectShiny[];
extern const u16 gObjectEventPal_FollowerVenonatShiny[];
extern const u16 gObjectEventPal_FollowerVenomothShiny[];
extern const u16 gObjectEventPal_FollowerDiglettShiny[];
extern const u16 gObjectEventPal_FollowerDugtrioShiny[];
extern const u16 gObjectEventPal_FollowerMeowthShiny[];
extern const u16 gObjectEventPal_FollowerPersianShiny[];
extern const u16 gObjectEventPal_FollowerPsyduckShiny[];
extern const u16 gObjectEventPal_FollowerGolduckShiny[];
extern const u16 gObjectEventPal_FollowerMankeyShiny[];
extern const u16 gObjectEventPal_FollowerPrimeapeShiny[];
extern const u16 gObjectEventPal_FollowerGrowlitheShiny[];
extern const u16 gObjectEventPal_FollowerArcanineShiny[];
extern const u16 gObjectEventPal_FollowerPoliwagShiny[];
extern const u16 gObjectEventPal_FollowerPoliwhirlShiny[];
extern const u16 gObjectEventPal_FollowerPoliwrathShiny[];
extern const u16 gObjectEventPal_FollowerAbraShiny[];
extern const u16 gObjectEventPal_FollowerKadabraShiny[];
extern const u16 gObjectEventPal_FollowerAlakazamShiny[];
extern const u16 gObjectEventPal_FollowerMachopShiny[];
extern const u16 gObjectEventPal_FollowerMachokeShiny[];
extern const u16 gObjectEventPal_FollowerMachampShiny[];
extern const u16 gObjectEventPal_FollowerBellsproutShiny[];
extern const u16 gObjectEventPal_FollowerWeepinbellShiny[];
extern const u16 gObjectEventPal_FollowerVictreebelShiny[];
extern const u16 gObjectEventPal_FollowerTentacoolShiny[];
extern const u16 gObjectEventPal_FollowerTentacruelShiny[];
extern const u16 gObjectEventPal_FollowerGeodudeShiny[];
extern const u16 gObjectEventPal_FollowerGravelerShiny[];
extern const u16 gObjectEventPal_FollowerGolemShiny[];
extern const u16 gObjectEventPal_FollowerPonytaShiny[];
extern const u16 gObjectEventPal_FollowerRapidashShiny[];
extern const u16 gObjectEventPal_FollowerSlowpokeShiny[];
extern const u16 gObjectEventPal_FollowerSlowbroShiny[];
extern const u16 gObjectEventPal_FollowerMagnemiteShiny[];
extern const u16 gObjectEventPal_FollowerMagnetonShiny[];
extern const u16 gObjectEventPal_FollowerFarfetchdShiny[];
extern const u16 gObjectEventPal_FollowerDoduoShiny[];
extern const u16 gObjectEventPal_FollowerDodrioShiny[];
extern const u16 gObjectEventPal_FollowerSeelShiny[];
extern const u16 gObjectEventPal_FollowerDewgongShiny[];
extern const u16 gObjectEventPal_FollowerGrimerShiny[];
extern const u16 gObjectEventPal_FollowerMukShiny[];
extern const u16 gObjectEventPal_FollowerShellderShiny[];
extern const u16 gObjectEventPal_FollowerCloysterShiny[];
extern const u16 gObjectEventPal_FollowerGastlyShiny[];
extern const u16 gObjectEventPal_FollowerHaunterShiny[];
extern const u16 gObjectEventPal_FollowerGengarShiny[];
extern const u16 gObjectEventPal_FollowerOnixShiny[];
extern const u16 gObjectEventPal_FollowerDrowzeeShiny[];
extern const u16 gObjectEventPal_FollowerHypnoShiny[];
extern const u16 gObjectEventPal_FollowerKrabbyShiny[];
extern const u16 gObjectEventPal_FollowerKinglerShiny[];
extern const u16 gObjectEventPal_FollowerVoltorbShiny[];
extern const u16 gObjectEventPal_FollowerElectrodeShiny[];
extern const u16 gObjectEventPal_FollowerExeggcuteShiny[];
extern const u16 gObjectEventPal_FollowerExeggutorShiny[];
extern const u16 gObjectEventPal_FollowerCuboneShiny[];
extern const u16 gObjectEventPal_FollowerMarowakShiny[];
extern const u16 gObjectEventPal_FollowerHitmonleeShiny[];
extern const u16 gObjectEventPal_FollowerHitmonchanShiny[];
extern const u16 gObjectEventPal_FollowerLickitungShiny[];
extern const u16 gObjectEventPal_FollowerKoffingShiny[];
extern const u16 gObjectEventPal_FollowerWeezingShiny[];
extern const u16 gObjectEventPal_FollowerRhyhornShiny[];
extern const u16 gObjectEventPal_FollowerRhydonShiny[];
extern const u16 gObjectEventPal_FollowerChanseyShiny[];
extern const u16 gObjectEventPal_FollowerTangelaShiny[];
extern const u16 gObjectEventPal_FollowerKangaskhanShiny[];
extern const u16 gObjectEventPal_FollowerHorseaShiny[];
extern const u16 gObjectEventPal_FollowerSeadraShiny[];
extern const u16 gObjectEventPal_FollowerGoldeenShiny[];
extern const u16 gObjectEventPal_FollowerSeakingShiny[];
extern const u16 gObjectEventPal_FollowerStaryuShiny[];
extern const u16 gObjectEventPal_FollowerStarmieShiny[];
extern const u16 gObjectEventPal_FollowerMrMimeShiny[];
extern const u16 gObjectEventPal_FollowerScytherShiny[];
extern const u16 gObjectEventPal_FollowerJynxShiny[];
extern const u16 gObjectEventPal_FollowerElectabuzzShiny[];
extern const u16 gObjectEventPal_FollowerMagmarShiny[];
extern const u16 gObjectEventPal_FollowerPinsirShiny[];
extern const u16 gObjectEventPal_FollowerTaurosShiny[];
extern const u16 gObjectEventPal_FollowerMagikarpShiny[];
extern const u16 gObjectEventPal_FollowerGyaradosShiny[];
extern const u16 gObjectEventPal_FollowerLaprasShiny[];
extern const u16 gObjectEventPal_FollowerDittoShiny[];
extern const u16 gObjectEventPal_FollowerEeveeShiny[];
extern const u16 gObjectEventPal_FollowerVaporeonShiny[];
extern const u16 gObjectEventPal_FollowerJolteonShiny[];
extern const u16 gObjectEventPal_FollowerFlareonShiny[];
extern const u16 gObjectEventPal_FollowerPorygonShiny[];
extern const u16 gObjectEventPal_FollowerOmanyteShiny[];
extern const u16 gObjectEventPal_FollowerOmastarShiny[];
extern const u16 gObjectEventPal_FollowerKabutoShiny[];
extern const u16 gObjectEventPal_FollowerKabutopsShiny[];
extern const u16 gObjectEventPal_FollowerAerodactylShiny[];
extern const u16 gObjectEventPal_FollowerSnorlaxShiny[];
extern const u16 gObjectEventPal_FollowerArticunoShiny[];
extern const u16 gObjectEventPal_FollowerZapdosShiny[];
extern const u16 gObjectEventPal_FollowerMoltresShiny[];
extern const u16 gObjectEventPal_FollowerDratiniShiny[];
extern const u16 gObjectEventPal_FollowerDragonairShiny[];
extern const u16 gObjectEventPal_FollowerDragoniteShiny[];
extern const u16 gObjectEventPal_FollowerMewtwoShiny[];
extern const u16 gObjectEventPal_FollowerMewShiny[];
extern const u16 gObjectEventPal_FollowerBayleefShiny[];
extern const u16 gObjectEventPal_FollowerMeganiumShiny[];
extern const u16 gObjectEventPal_FollowerQuilavaShiny[];
extern const u16 gObjectEventPal_FollowerTyphlosionShiny[];
extern const u16 gObjectEventPal_FollowerCroconawShiny[];
extern const u16 gObjectEventPal_FollowerFeraligatrShiny[];
extern const u16 gObjectEventPal_FollowerSentretShiny[];
extern const u16 gObjectEventPal_FollowerFurretShiny[];
extern const u16 gObjectEventPal_FollowerHoothootShiny[];
extern const u16 gObjectEventPal_FollowerNoctowlShiny[];
extern const u16 gObjectEventPal_FollowerLedybaShiny[];
extern const u16 gObjectEventPal_FollowerLedianShiny[];
extern const u16 gObjectEventPal_FollowerSpinarakShiny[];
extern const u16 gObjectEventPal_FollowerAriadosShiny[];
extern const u16 gObjectEventPal_FollowerCrobatShiny[];
extern const u16 gObjectEventPal_FollowerChinchouShiny[];
extern const u16 gObjectEventPal_FollowerLanturnShiny[];
extern const u16 gObjectEventPal_FollowerPichuShiny[];
extern const u16 gObjectEventPal_FollowerCleffaShiny[];
extern const u16 gObjectEventPal_FollowerIgglybuffShiny[];
extern const u16 gObjectEventPal_FollowerTogepiShiny[];
extern const u16 gObjectEventPal_FollowerTogeticShiny[];
extern const u16 gObjectEventPal_FollowerNatuShiny[];
extern const u16 gObjectEventPal_FollowerXatuShiny[];
extern const u16 gObjectEventPal_FollowerMareepShiny[];
extern const u16 gObjectEventPal_FollowerFlaaffyShiny[];
extern const u16 gObjectEventPal_FollowerAmpharosShiny[];
extern const u16 gObjectEventPal_FollowerBellossomShiny[];
extern const u16 gObjectEventPal_FollowerMarillShiny[];
extern const u16 gObjectEventPal_FollowerAzumarillShiny[];
extern const u16 gObjectEventPal_FollowerSudowoodoShiny[];
extern const u16 gObjectEventPal_FollowerPolitoedShiny[];
extern const u16 gObjectEventPal_FollowerHoppipShiny[];
extern const u16 gObjectEventPal_FollowerSkiploomShiny[];
extern const u16 gObjectEventPal_FollowerJumpluffShiny[];
extern const u16 gObjectEventPal_FollowerAipomShiny[];
extern const u16 gObjectEventPal_FollowerSunkernShiny[];
extern const u16 gObjectEventPal_FollowerSunfloraShiny[];
extern const u16 gObjectEventPal_FollowerYanmaShiny[];
extern const u16 gObjectEventPal_FollowerWooperShiny[];
extern const u16 gObjectEventPal_FollowerQuagsireShiny[];
extern const u16 gObjectEventPal_FollowerEspeonShiny[];
extern const u16 gObjectEventPal_FollowerUmbreonShiny[];
extern const u16 gObjectEventPal_FollowerMurkrowShiny[];
extern const u16 gObjectEventPal_FollowerSlowkingShiny[];
extern const u16 gObjectEventPal_FollowerMisdreavusShiny[];
extern const u16 gObjectEventPal_FollowerWobbuffetShiny[];
extern const u16 gObjectEventPal_FollowerGirafarigShiny[];
extern const u16 gObjectEventPal_FollowerPinecoShiny[];
extern const u16 gObjectEventPal_FollowerForretressShiny[];
extern const u16 gObjectEventPal_FollowerDunsparceShiny[];
extern const u16 gObjectEventPal_FollowerGligarShiny[];
extern const u16 gObjectEventPal_FollowerSnubbullShiny[];
extern const u16 gObjectEventPal_FollowerGranbullShiny[];
extern const u16 gObjectEventPal_FollowerQwilfishShiny[];
extern const u16 gObjectEventPal_FollowerScizorShiny[];
extern const u16 gObjectEventPal_FollowerShuckleShiny[];
extern const u16 gObjectEventPal_FollowerHeracrossShiny[];
extern const u16 gObjectEventPal_FollowerSneaselShiny[];
extern const u16 gObjectEventPal_FollowerTeddiursaShiny[];
extern const u16 gObjectEventPal_FollowerUrsaringShiny[];
extern const u16 gObjectEventPal_FollowerSlugmaShiny[];
extern const u16 gObjectEventPal_FollowerMagcargoShiny[];
extern const u16 gObjectEventPal_FollowerSwinubShiny[];
extern const u16 gObjectEventPal_FollowerPiloswineShiny[];
extern const u16 gObjectEventPal_FollowerCorsolaShiny[];
extern const u16 gObjectEventPal_FollowerRemoraidShiny[];
extern const u16 gObjectEventPal_FollowerOctilleryShiny[];
extern const u16 gObjectEventPal_FollowerDelibirdShiny[];
extern const u16 gObjectEventPal_FollowerMantineShiny[];
extern const u16 gObjectEventPal_FollowerSkarmoryShiny[];
extern const u16 gObjectEventPal_FollowerHoundourShiny[];
extern const u16 gObjectEventPal_FollowerHoundoomShiny[];
extern const u16 gObjectEventPal_FollowerKingdraShiny[];
extern const u16 gObjectEventPal_FollowerPhanpyShiny[];
extern const u16 gObjectEventPal_FollowerDonphanShiny[];
extern const u16 gObjectEventPal_FollowerPorygon2Shiny[];
extern const u16 gObjectEventPal_FollowerStantlerShiny[];
extern const u16 gObjectEventPal_FollowerSmeargleShiny[];
extern const u16 gObjectEventPal_FollowerTyrogueShiny[];
extern const u16 gObjectEventPal_FollowerHitmontopShiny[];
extern const u16 gObjectEventPal_FollowerSmoochumShiny[];
extern const u16 gObjectEventPal_FollowerElekidShiny[];
extern const u16 gObjectEventPal_FollowerMagbyShiny[];
extern const u16 gObjectEventPal_FollowerMiltankShiny[];
extern const u16 gObjectEventPal_FollowerBlisseyShiny[];
extern const u16 gObjectEventPal_FollowerRaikouShiny[];
extern const u16 gObjectEventPal_FollowerEnteiShiny[];
extern const u16 gObjectEventPal_FollowerSuicuneShiny[];
extern const u16 gObjectEventPal_FollowerLarvitarShiny[];
extern const u16 gObjectEventPal_FollowerPupitarShiny[];
extern const u16 gObjectEventPal_FollowerTyranitarShiny[];
extern const u16 gObjectEventPal_FollowerCelebiShiny[];
extern const u16 gObjectEventPal_FollowerGrovyleShiny[];
extern const u16 gObjectEventPal_FollowerSceptileShiny[];
extern const u16 gObjectEventPal_FollowerCombuskenShiny[];
extern const u16 gObjectEventPal_FollowerBlazikenShiny[];
extern const u16 gObjectEventPal_FollowerMarshtompShiny[];
extern const u16 gObjectEventPal_FollowerSwampertShiny[];
extern const u16 gObjectEventPal_FollowerPoochyenaShiny[];
extern const u16 gObjectEventPal_FollowerMightyenaShiny[];
extern const u16 gObjectEventPal_FollowerZigzagoonShiny[];
extern const u16 gObjectEventPal_FollowerLinooneShiny[];
extern const u16 gObjectEventPal_FollowerWurmpleShiny[];
extern const u16 gObjectEventPal_FollowerSilcoonShiny[];
extern const u16 gObjectEventPal_FollowerBeautiflyShiny[];
extern const u16 gObjectEventPal_FollowerCascoonShiny[];
extern const u16 gObjectEventPal_FollowerDustoxShiny[];
extern const u16 gObjectEventPal_FollowerLotadShiny[];
extern const u16 gObjectEventPal_FollowerLombreShiny[];
extern const u16 gObjectEventPal_FollowerLudicoloShiny[];
extern const u16 gObjectEventPal_FollowerSeedotShiny[];
extern const u16 gObjectEventPal_FollowerNuzleafShiny[];
extern const u16 gObjectEventPal_FollowerShiftryShiny[];
extern const u16 gObjectEventPal_FollowerNincadaShiny[];
extern const u16 gObjectEventPal_FollowerNinjaskShiny[];
extern const u16 gObjectEventPal_FollowerShedinjaShiny[];
extern const u16 gObjectEventPal_FollowerTaillowShiny[];
extern const u16 gObjectEventPal_FollowerSwellowShiny[];
extern const u16 gObjectEventPal_FollowerShroomishShiny[];
extern const u16 gObjectEventPal_FollowerBreloomShiny[];
extern const u16 gObjectEventPal_FollowerSpindaShiny[];
extern const u16 gObjectEventPal_FollowerWingullShiny[];
extern const u16 gObjectEventPal_FollowerPelipperShiny[];
extern const u16 gObjectEventPal_FollowerSurskitShiny[];
extern const u16 gObjectEventPal_FollowerMasquerainShiny[];
extern const u16 gObjectEventPal_FollowerWailmerShiny[];
extern const u16 gObjectEventPal_FollowerSkittyShiny[];
extern const u16 gObjectEventPal_FollowerDelcattyShiny[];
extern const u16 gObjectEventPal_FollowerKecleonShiny[];
extern const u16 gObjectEventPal_FollowerBaltoyShiny[];
extern const u16 gObjectEventPal_FollowerClaydolShiny[];
extern const u16 gObjectEventPal_FollowerNosepassShiny[];
extern const u16 gObjectEventPal_FollowerTorkoalShiny[];
extern const u16 gObjectEventPal_FollowerSableyeShiny[];
extern const u16 gObjectEventPal_FollowerBarboachShiny[];
extern const u16 gObjectEventPal_FollowerWhiscashShiny[];
extern const u16 gObjectEventPal_FollowerLuvdiscShiny[];
extern const u16 gObjectEventPal_FollowerCorphishShiny[];
extern const u16 gObjectEventPal_FollowerCrawdauntShiny[];
extern const u16 gObjectEventPal_FollowerFeebasShiny[];
extern const u16 gObjectEventPal_FollowerMiloticShiny[];
extern const u16 gObjectEventPal_FollowerCarvanhaShiny[];
extern const u16 gObjectEventPal_FollowerSharpedoShiny[];
extern const u16 gObjectEventPal_FollowerTrapinchShiny[];
extern const u16 gObjectEventPal_FollowerVibravaShiny[];
extern const u16 gObjectEventPal_FollowerFlygonShiny[];
extern const u16 gObjectEventPal_FollowerMakuhitaShiny[];
extern const u16 gObjectEventPal_FollowerHariyamaShiny[];
extern const u16 gObjectEventPal_FollowerElectrikeShiny[];
extern const u16 gObjectEventPal_FollowerManectricShiny[];
extern const u16 gObjectEventPal_FollowerNumelShiny[];
extern const u16 gObjectEventPal_FollowerCameruptShiny[];
extern const u16 gObjectEventPal_FollowerSphealShiny[];
extern const u16 gObjectEventPal_FollowerSealeoShiny[];
extern const u16 gObjectEventPal_FollowerWalreinShiny[];
extern const u16 gObjectEventPal_FollowerCacneaShiny[];
extern const u16 gObjectEventPal_FollowerCacturneShiny[];
extern const u16 gObjectEventPal_FollowerSnoruntShiny[];
extern const u16 gObjectEventPal_FollowerGlalieShiny[];
extern const u16 gObjectEventPal_FollowerLunatoneShiny[];
extern const u16 gObjectEventPal_FollowerSolrockShiny[];
extern const u16 gObjectEventPal_FollowerAzurillShiny[];
extern const u16 gObjectEventPal_FollowerSpoinkShiny[];
extern const u16 gObjectEventPal_FollowerGrumpigShiny[];
extern const u16 gObjectEventPal_FollowerPlusleShiny[];
extern const u16 gObjectEventPal_FollowerMinunShiny[];
extern const u16 gObjectEventPal_FollowerMawileShiny[];
extern const u16 gObjectEventPal_FollowerMedititeShiny[];
extern const u16 gObjectEventPal_FollowerMedichamShiny[];
extern const u16 gObjectEventPal_FollowerSwabluShiny[];
extern const u16 gObjectEventPal_FollowerAltariaShiny[];
extern const u16 gObjectEventPal_FollowerWynautShiny[];
extern const u16 gObjectEventPal_FollowerDuskullShiny[];
extern const u16 gObjectEventPal_FollowerDusclopsShiny[];
extern const u16 gObjectEventPal_FollowerRoseliaShiny[];
extern const u16 gObjectEventPal_FollowerSlakothShiny[];
extern const u16 gObjectEventPal_FollowerVigorothShiny[];
extern const u16 gObjectEventPal_FollowerSlakingShiny[];
extern const u16 gObjectEventPal_FollowerGulpinShiny[];
extern const u16 gObjectEventPal_FollowerSwalotShiny[];
extern const u16 gObjectEventPal_FollowerTropiusShiny[];
extern const u16 gObjectEventPal_FollowerWhismurShiny[];
extern const u16 gObjectEventPal_FollowerLoudredShiny[];
extern const u16 gObjectEventPal_FollowerExploudShiny[];
extern const u16 gObjectEventPal_FollowerClamperlShiny[];
extern const u16 gObjectEventPal_FollowerHuntailShiny[];
extern const u16 gObjectEventPal_FollowerGorebyssShiny[];
extern const u16 gObjectEventPal_FollowerAbsolShiny[];
extern const u16 gObjectEventPal_FollowerShuppetShiny[];
extern const u16 gObjectEventPal_FollowerBanetteShiny[];
extern const u16 gObjectEventPal_FollowerSeviperShiny[];
extern const u16 gObjectEventPal_FollowerZangooseShiny[];
extern const u16 gObjectEventPal_FollowerRelicanthShiny[];
extern const u16 gObjectEventPal_FollowerAronShiny[];
extern const u16 gObjectEventPal_FollowerLaironShiny[];
extern const u16 gObjectEventPal_FollowerAggronShiny[];
extern const u16 gObjectEventPal_FollowerCastformShiny[];
extern const u16 gObjectEventPal_FollowerVolbeatShiny[];
extern const u16 gObjectEventPal_FollowerIllumiseShiny[];
extern const u16 gObjectEventPal_FollowerLileepShiny[];
extern const u16 gObjectEventPal_FollowerCradilyShiny[];
extern const u16 gObjectEventPal_FollowerAnorithShiny[];
extern const u16 gObjectEventPal_FollowerArmaldoShiny[];
extern const u16 gObjectEventPal_FollowerRaltsShiny[];
extern const u16 gObjectEventPal_FollowerKirliaShiny[];
extern const u16 gObjectEventPal_FollowerGardevoirShiny[];
extern const u16 gObjectEventPal_FollowerBagonShiny[];
extern const u16 gObjectEventPal_FollowerShelgonShiny[];
extern const u16 gObjectEventPal_FollowerSalamenceShiny[];
extern const u16 gObjectEventPal_FollowerBeldumShiny[];
extern const u16 gObjectEventPal_FollowerMetangShiny[];
extern const u16 gObjectEventPal_FollowerMetagrossShiny[];
extern const u16 gObjectEventPal_FollowerRegirockShiny[];
extern const u16 gObjectEventPal_FollowerRegiceShiny[];
extern const u16 gObjectEventPal_FollowerRegisteelShiny[];
extern const u16 gObjectEventPal_FollowerLatiasShiny[];
extern const u16 gObjectEventPal_FollowerLatiosShiny[];
extern const u16 gObjectEventPal_FollowerJirachiShiny[];
extern const u16 gObjectEventPal_FollowerDeoxysShiny[];
extern const u16 gObjectEventPal_FollowerChimechoShiny[];
extern const u16 gObjectEventPal_FollowerSteelixShiny[];
extern const u16 gObjectEventPal_FollowerLugiaShiny[];
extern const u16 gObjectEventPal_FollowerHoOhShiny[];
extern const u16 gObjectEventPal_FollowerWailordShiny[];
extern const u16 gObjectEventPal_FollowerKyogreShiny[];
extern const u16 gObjectEventPal_FollowerGroudonShiny[];
extern const u16 gObjectEventPal_FollowerRayquazaShiny[];
extern const u16 gObjectEventPal_FollowerUnown1Shiny[];
extern const u16 gObjectEventPal_FollowerUnown2Shiny[];

// Pic tables (6-frame strips: northA, northB, southA, southB, westA, westB).
// Defined here using overworld_frame so they're local to this translation unit.
// The matching static pic tables in event_object_movement.c are not used for
// SetFollowerSpecies — those exist only for the initial gObjectEventGraphicsInfo_Follower.
static const struct SpriteFrameImage sPicTable_Follower_Bulbasaur[] = {
    overworld_frame(gObjectEventPic_FollowerBulbasaur, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerBulbasaur, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerBulbasaur, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerBulbasaur, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerBulbasaur, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerBulbasaur, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Charmander[] = {
    overworld_frame(gObjectEventPic_FollowerCharmander, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerCharmander, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerCharmander, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerCharmander, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerCharmander, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerCharmander, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Squirtle[] = {
    overworld_frame(gObjectEventPic_FollowerSquirtle, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSquirtle, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSquirtle, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSquirtle, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSquirtle, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSquirtle, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Chikorita[] = {
    overworld_frame(gObjectEventPic_FollowerChikorita, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerChikorita, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerChikorita, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerChikorita, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerChikorita, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerChikorita, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Cyndaquil[] = {
    overworld_frame(gObjectEventPic_FollowerCyndaquil, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerCyndaquil, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerCyndaquil, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerCyndaquil, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerCyndaquil, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerCyndaquil, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Totodile[] = {
    overworld_frame(gObjectEventPic_FollowerTotodile, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerTotodile, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerTotodile, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerTotodile, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerTotodile, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerTotodile, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Treecko[] = {
    overworld_frame(gObjectEventPic_FollowerTreecko, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerTreecko, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerTreecko, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerTreecko, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerTreecko, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerTreecko, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Torchic[] = {
    overworld_frame(gObjectEventPic_FollowerTorchic, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerTorchic, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerTorchic, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerTorchic, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerTorchic, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerTorchic, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Mudkip[] = {
    overworld_frame(gObjectEventPic_FollowerMudkip, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMudkip, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMudkip, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMudkip, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMudkip, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMudkip, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Ivysaur[] = {
    overworld_frame(gObjectEventPic_FollowerIvysaur, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerIvysaur, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerIvysaur, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerIvysaur, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerIvysaur, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerIvysaur, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Venusaur[] = {
    overworld_frame(gObjectEventPic_FollowerVenusaur, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerVenusaur, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerVenusaur, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerVenusaur, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerVenusaur, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerVenusaur, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Charmeleon[] = {
    overworld_frame(gObjectEventPic_FollowerCharmeleon, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerCharmeleon, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerCharmeleon, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerCharmeleon, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerCharmeleon, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerCharmeleon, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Charizard[] = {
    overworld_frame(gObjectEventPic_FollowerCharizard, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerCharizard, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerCharizard, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerCharizard, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerCharizard, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerCharizard, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Wartortle[] = {
    overworld_frame(gObjectEventPic_FollowerWartortle, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerWartortle, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerWartortle, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerWartortle, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerWartortle, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerWartortle, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Blastoise[] = {
    overworld_frame(gObjectEventPic_FollowerBlastoise, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerBlastoise, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerBlastoise, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerBlastoise, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerBlastoise, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerBlastoise, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Caterpie[] = {
    overworld_frame(gObjectEventPic_FollowerCaterpie, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerCaterpie, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerCaterpie, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerCaterpie, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerCaterpie, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerCaterpie, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Metapod[] = {
    overworld_frame(gObjectEventPic_FollowerMetapod, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMetapod, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMetapod, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMetapod, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMetapod, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMetapod, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Butterfree[] = {
    overworld_frame(gObjectEventPic_FollowerButterfree, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerButterfree, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerButterfree, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerButterfree, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerButterfree, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerButterfree, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Weedle[] = {
    overworld_frame(gObjectEventPic_FollowerWeedle, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerWeedle, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerWeedle, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerWeedle, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerWeedle, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerWeedle, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Kakuna[] = {
    overworld_frame(gObjectEventPic_FollowerKakuna, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerKakuna, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerKakuna, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerKakuna, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerKakuna, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerKakuna, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Beedrill[] = {
    overworld_frame(gObjectEventPic_FollowerBeedrill, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerBeedrill, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerBeedrill, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerBeedrill, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerBeedrill, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerBeedrill, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Pidgey[] = {
    overworld_frame(gObjectEventPic_FollowerPidgey, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerPidgey, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerPidgey, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerPidgey, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerPidgey, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerPidgey, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Pidgeotto[] = {
    overworld_frame(gObjectEventPic_FollowerPidgeotto, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerPidgeotto, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerPidgeotto, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerPidgeotto, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerPidgeotto, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerPidgeotto, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Pidgeot[] = {
    overworld_frame(gObjectEventPic_FollowerPidgeot, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerPidgeot, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerPidgeot, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerPidgeot, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerPidgeot, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerPidgeot, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Rattata[] = {
    overworld_frame(gObjectEventPic_FollowerRattata, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerRattata, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerRattata, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerRattata, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerRattata, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerRattata, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Raticate[] = {
    overworld_frame(gObjectEventPic_FollowerRaticate, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerRaticate, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerRaticate, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerRaticate, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerRaticate, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerRaticate, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Spearow[] = {
    overworld_frame(gObjectEventPic_FollowerSpearow, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSpearow, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSpearow, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSpearow, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSpearow, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSpearow, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Fearow[] = {
    overworld_frame(gObjectEventPic_FollowerFearow, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerFearow, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerFearow, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerFearow, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerFearow, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerFearow, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Ekans[] = {
    overworld_frame(gObjectEventPic_FollowerEkans, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerEkans, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerEkans, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerEkans, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerEkans, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerEkans, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Arbok[] = {
    overworld_frame(gObjectEventPic_FollowerArbok, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerArbok, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerArbok, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerArbok, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerArbok, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerArbok, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Pikachu[] = {
    overworld_frame(gObjectEventPic_FollowerPikachu, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerPikachu, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerPikachu, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerPikachu, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerPikachu, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerPikachu, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Raichu[] = {
    overworld_frame(gObjectEventPic_FollowerRaichu, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerRaichu, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerRaichu, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerRaichu, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerRaichu, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerRaichu, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Sandshrew[] = {
    overworld_frame(gObjectEventPic_FollowerSandshrew, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSandshrew, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSandshrew, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSandshrew, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSandshrew, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSandshrew, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Sandslash[] = {
    overworld_frame(gObjectEventPic_FollowerSandslash, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSandslash, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSandslash, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSandslash, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSandslash, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSandslash, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_NidoranF[] = {
    overworld_frame(gObjectEventPic_FollowerNidoranF, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerNidoranF, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerNidoranF, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerNidoranF, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerNidoranF, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerNidoranF, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Nidorina[] = {
    overworld_frame(gObjectEventPic_FollowerNidorina, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerNidorina, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerNidorina, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerNidorina, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerNidorina, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerNidorina, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Nidoqueen[] = {
    overworld_frame(gObjectEventPic_FollowerNidoqueen, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerNidoqueen, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerNidoqueen, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerNidoqueen, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerNidoqueen, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerNidoqueen, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_NidoranM[] = {
    overworld_frame(gObjectEventPic_FollowerNidoranM, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerNidoranM, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerNidoranM, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerNidoranM, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerNidoranM, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerNidoranM, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Nidorino[] = {
    overworld_frame(gObjectEventPic_FollowerNidorino, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerNidorino, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerNidorino, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerNidorino, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerNidorino, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerNidorino, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Nidoking[] = {
    overworld_frame(gObjectEventPic_FollowerNidoking, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerNidoking, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerNidoking, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerNidoking, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerNidoking, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerNidoking, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Clefairy[] = {
    overworld_frame(gObjectEventPic_FollowerClefairy, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerClefairy, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerClefairy, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerClefairy, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerClefairy, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerClefairy, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Clefable[] = {
    overworld_frame(gObjectEventPic_FollowerClefable, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerClefable, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerClefable, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerClefable, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerClefable, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerClefable, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Vulpix[] = {
    overworld_frame(gObjectEventPic_FollowerVulpix, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerVulpix, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerVulpix, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerVulpix, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerVulpix, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerVulpix, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Ninetales[] = {
    overworld_frame(gObjectEventPic_FollowerNinetales, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerNinetales, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerNinetales, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerNinetales, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerNinetales, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerNinetales, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Jigglypuff[] = {
    overworld_frame(gObjectEventPic_FollowerJigglypuff, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerJigglypuff, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerJigglypuff, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerJigglypuff, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerJigglypuff, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerJigglypuff, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Wigglytuff[] = {
    overworld_frame(gObjectEventPic_FollowerWigglytuff, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerWigglytuff, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerWigglytuff, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerWigglytuff, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerWigglytuff, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerWigglytuff, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Zubat[] = {
    overworld_frame(gObjectEventPic_FollowerZubat, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerZubat, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerZubat, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerZubat, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerZubat, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerZubat, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Golbat[] = {
    overworld_frame(gObjectEventPic_FollowerGolbat, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerGolbat, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerGolbat, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerGolbat, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerGolbat, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerGolbat, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Oddish[] = {
    overworld_frame(gObjectEventPic_FollowerOddish, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerOddish, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerOddish, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerOddish, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerOddish, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerOddish, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Gloom[] = {
    overworld_frame(gObjectEventPic_FollowerGloom, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerGloom, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerGloom, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerGloom, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerGloom, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerGloom, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Vileplume[] = {
    overworld_frame(gObjectEventPic_FollowerVileplume, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerVileplume, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerVileplume, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerVileplume, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerVileplume, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerVileplume, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Paras[] = {
    overworld_frame(gObjectEventPic_FollowerParas, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerParas, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerParas, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerParas, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerParas, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerParas, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Parasect[] = {
    overworld_frame(gObjectEventPic_FollowerParasect, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerParasect, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerParasect, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerParasect, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerParasect, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerParasect, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Venonat[] = {
    overworld_frame(gObjectEventPic_FollowerVenonat, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerVenonat, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerVenonat, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerVenonat, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerVenonat, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerVenonat, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Venomoth[] = {
    overworld_frame(gObjectEventPic_FollowerVenomoth, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerVenomoth, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerVenomoth, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerVenomoth, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerVenomoth, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerVenomoth, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Diglett[] = {
    overworld_frame(gObjectEventPic_FollowerDiglett, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerDiglett, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerDiglett, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerDiglett, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerDiglett, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerDiglett, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Dugtrio[] = {
    overworld_frame(gObjectEventPic_FollowerDugtrio, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerDugtrio, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerDugtrio, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerDugtrio, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerDugtrio, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerDugtrio, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Meowth[] = {
    overworld_frame(gObjectEventPic_FollowerMeowth, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMeowth, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMeowth, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMeowth, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMeowth, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMeowth, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Persian[] = {
    overworld_frame(gObjectEventPic_FollowerPersian, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerPersian, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerPersian, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerPersian, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerPersian, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerPersian, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Psyduck[] = {
    overworld_frame(gObjectEventPic_FollowerPsyduck, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerPsyduck, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerPsyduck, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerPsyduck, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerPsyduck, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerPsyduck, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Golduck[] = {
    overworld_frame(gObjectEventPic_FollowerGolduck, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerGolduck, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerGolduck, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerGolduck, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerGolduck, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerGolduck, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Mankey[] = {
    overworld_frame(gObjectEventPic_FollowerMankey, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMankey, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMankey, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMankey, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMankey, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMankey, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Primeape[] = {
    overworld_frame(gObjectEventPic_FollowerPrimeape, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerPrimeape, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerPrimeape, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerPrimeape, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerPrimeape, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerPrimeape, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Growlithe[] = {
    overworld_frame(gObjectEventPic_FollowerGrowlithe, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerGrowlithe, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerGrowlithe, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerGrowlithe, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerGrowlithe, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerGrowlithe, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Arcanine[] = {
    overworld_frame(gObjectEventPic_FollowerArcanine, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerArcanine, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerArcanine, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerArcanine, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerArcanine, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerArcanine, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Poliwag[] = {
    overworld_frame(gObjectEventPic_FollowerPoliwag, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerPoliwag, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerPoliwag, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerPoliwag, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerPoliwag, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerPoliwag, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Poliwhirl[] = {
    overworld_frame(gObjectEventPic_FollowerPoliwhirl, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerPoliwhirl, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerPoliwhirl, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerPoliwhirl, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerPoliwhirl, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerPoliwhirl, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Poliwrath[] = {
    overworld_frame(gObjectEventPic_FollowerPoliwrath, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerPoliwrath, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerPoliwrath, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerPoliwrath, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerPoliwrath, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerPoliwrath, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Abra[] = {
    overworld_frame(gObjectEventPic_FollowerAbra, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerAbra, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerAbra, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerAbra, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerAbra, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerAbra, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Kadabra[] = {
    overworld_frame(gObjectEventPic_FollowerKadabra, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerKadabra, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerKadabra, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerKadabra, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerKadabra, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerKadabra, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Alakazam[] = {
    overworld_frame(gObjectEventPic_FollowerAlakazam, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerAlakazam, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerAlakazam, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerAlakazam, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerAlakazam, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerAlakazam, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Machop[] = {
    overworld_frame(gObjectEventPic_FollowerMachop, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMachop, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMachop, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMachop, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMachop, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMachop, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Machoke[] = {
    overworld_frame(gObjectEventPic_FollowerMachoke, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMachoke, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMachoke, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMachoke, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMachoke, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMachoke, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Machamp[] = {
    overworld_frame(gObjectEventPic_FollowerMachamp, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMachamp, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMachamp, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMachamp, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMachamp, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMachamp, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Bellsprout[] = {
    overworld_frame(gObjectEventPic_FollowerBellsprout, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerBellsprout, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerBellsprout, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerBellsprout, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerBellsprout, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerBellsprout, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Weepinbell[] = {
    overworld_frame(gObjectEventPic_FollowerWeepinbell, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerWeepinbell, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerWeepinbell, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerWeepinbell, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerWeepinbell, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerWeepinbell, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Victreebel[] = {
    overworld_frame(gObjectEventPic_FollowerVictreebel, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerVictreebel, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerVictreebel, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerVictreebel, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerVictreebel, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerVictreebel, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Tentacool[] = {
    overworld_frame(gObjectEventPic_FollowerTentacool, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerTentacool, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerTentacool, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerTentacool, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerTentacool, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerTentacool, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Tentacruel[] = {
    overworld_frame(gObjectEventPic_FollowerTentacruel, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerTentacruel, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerTentacruel, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerTentacruel, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerTentacruel, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerTentacruel, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Geodude[] = {
    overworld_frame(gObjectEventPic_FollowerGeodude, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerGeodude, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerGeodude, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerGeodude, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerGeodude, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerGeodude, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Graveler[] = {
    overworld_frame(gObjectEventPic_FollowerGraveler, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerGraveler, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerGraveler, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerGraveler, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerGraveler, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerGraveler, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Golem[] = {
    overworld_frame(gObjectEventPic_FollowerGolem, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerGolem, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerGolem, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerGolem, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerGolem, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerGolem, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Ponyta[] = {
    overworld_frame(gObjectEventPic_FollowerPonyta, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerPonyta, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerPonyta, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerPonyta, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerPonyta, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerPonyta, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Rapidash[] = {
    overworld_frame(gObjectEventPic_FollowerRapidash, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerRapidash, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerRapidash, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerRapidash, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerRapidash, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerRapidash, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Slowpoke[] = {
    overworld_frame(gObjectEventPic_FollowerSlowpoke, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSlowpoke, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSlowpoke, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSlowpoke, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSlowpoke, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSlowpoke, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Slowbro[] = {
    overworld_frame(gObjectEventPic_FollowerSlowbro, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSlowbro, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSlowbro, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSlowbro, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSlowbro, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSlowbro, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Magnemite[] = {
    overworld_frame(gObjectEventPic_FollowerMagnemite, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMagnemite, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMagnemite, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMagnemite, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMagnemite, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMagnemite, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Magneton[] = {
    overworld_frame(gObjectEventPic_FollowerMagneton, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMagneton, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMagneton, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMagneton, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMagneton, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMagneton, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Farfetchd[] = {
    overworld_frame(gObjectEventPic_FollowerFarfetchd, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerFarfetchd, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerFarfetchd, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerFarfetchd, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerFarfetchd, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerFarfetchd, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Doduo[] = {
    overworld_frame(gObjectEventPic_FollowerDoduo, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerDoduo, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerDoduo, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerDoduo, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerDoduo, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerDoduo, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Dodrio[] = {
    overworld_frame(gObjectEventPic_FollowerDodrio, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerDodrio, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerDodrio, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerDodrio, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerDodrio, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerDodrio, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Seel[] = {
    overworld_frame(gObjectEventPic_FollowerSeel, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSeel, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSeel, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSeel, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSeel, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSeel, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Dewgong[] = {
    overworld_frame(gObjectEventPic_FollowerDewgong, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerDewgong, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerDewgong, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerDewgong, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerDewgong, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerDewgong, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Grimer[] = {
    overworld_frame(gObjectEventPic_FollowerGrimer, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerGrimer, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerGrimer, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerGrimer, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerGrimer, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerGrimer, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Muk[] = {
    overworld_frame(gObjectEventPic_FollowerMuk, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMuk, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMuk, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMuk, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMuk, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMuk, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Shellder[] = {
    overworld_frame(gObjectEventPic_FollowerShellder, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerShellder, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerShellder, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerShellder, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerShellder, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerShellder, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Cloyster[] = {
    overworld_frame(gObjectEventPic_FollowerCloyster, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerCloyster, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerCloyster, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerCloyster, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerCloyster, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerCloyster, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Gastly[] = {
    overworld_frame(gObjectEventPic_FollowerGastly, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerGastly, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerGastly, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerGastly, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerGastly, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerGastly, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Haunter[] = {
    overworld_frame(gObjectEventPic_FollowerHaunter, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerHaunter, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerHaunter, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerHaunter, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerHaunter, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerHaunter, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Gengar[] = {
    overworld_frame(gObjectEventPic_FollowerGengar, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerGengar, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerGengar, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerGengar, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerGengar, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerGengar, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Onix[] = {
    overworld_frame(gObjectEventPic_FollowerOnix, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerOnix, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerOnix, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerOnix, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerOnix, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerOnix, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Drowzee[] = {
    overworld_frame(gObjectEventPic_FollowerDrowzee, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerDrowzee, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerDrowzee, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerDrowzee, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerDrowzee, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerDrowzee, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Hypno[] = {
    overworld_frame(gObjectEventPic_FollowerHypno, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerHypno, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerHypno, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerHypno, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerHypno, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerHypno, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Krabby[] = {
    overworld_frame(gObjectEventPic_FollowerKrabby, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerKrabby, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerKrabby, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerKrabby, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerKrabby, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerKrabby, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Kingler[] = {
    overworld_frame(gObjectEventPic_FollowerKingler, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerKingler, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerKingler, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerKingler, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerKingler, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerKingler, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Voltorb[] = {
    overworld_frame(gObjectEventPic_FollowerVoltorb, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerVoltorb, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerVoltorb, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerVoltorb, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerVoltorb, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerVoltorb, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Electrode[] = {
    overworld_frame(gObjectEventPic_FollowerElectrode, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerElectrode, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerElectrode, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerElectrode, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerElectrode, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerElectrode, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Exeggcute[] = {
    overworld_frame(gObjectEventPic_FollowerExeggcute, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerExeggcute, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerExeggcute, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerExeggcute, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerExeggcute, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerExeggcute, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Exeggutor[] = {
    overworld_frame(gObjectEventPic_FollowerExeggutor, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerExeggutor, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerExeggutor, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerExeggutor, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerExeggutor, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerExeggutor, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Cubone[] = {
    overworld_frame(gObjectEventPic_FollowerCubone, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerCubone, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerCubone, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerCubone, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerCubone, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerCubone, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Marowak[] = {
    overworld_frame(gObjectEventPic_FollowerMarowak, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMarowak, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMarowak, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMarowak, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMarowak, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMarowak, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Hitmonlee[] = {
    overworld_frame(gObjectEventPic_FollowerHitmonlee, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerHitmonlee, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerHitmonlee, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerHitmonlee, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerHitmonlee, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerHitmonlee, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Hitmonchan[] = {
    overworld_frame(gObjectEventPic_FollowerHitmonchan, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerHitmonchan, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerHitmonchan, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerHitmonchan, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerHitmonchan, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerHitmonchan, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Lickitung[] = {
    overworld_frame(gObjectEventPic_FollowerLickitung, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerLickitung, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerLickitung, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerLickitung, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerLickitung, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerLickitung, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Koffing[] = {
    overworld_frame(gObjectEventPic_FollowerKoffing, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerKoffing, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerKoffing, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerKoffing, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerKoffing, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerKoffing, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Weezing[] = {
    overworld_frame(gObjectEventPic_FollowerWeezing, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerWeezing, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerWeezing, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerWeezing, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerWeezing, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerWeezing, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Rhyhorn[] = {
    overworld_frame(gObjectEventPic_FollowerRhyhorn, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerRhyhorn, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerRhyhorn, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerRhyhorn, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerRhyhorn, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerRhyhorn, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Rhydon[] = {
    overworld_frame(gObjectEventPic_FollowerRhydon, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerRhydon, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerRhydon, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerRhydon, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerRhydon, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerRhydon, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Chansey[] = {
    overworld_frame(gObjectEventPic_FollowerChansey, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerChansey, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerChansey, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerChansey, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerChansey, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerChansey, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Tangela[] = {
    overworld_frame(gObjectEventPic_FollowerTangela, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerTangela, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerTangela, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerTangela, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerTangela, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerTangela, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Kangaskhan[] = {
    overworld_frame(gObjectEventPic_FollowerKangaskhan, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerKangaskhan, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerKangaskhan, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerKangaskhan, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerKangaskhan, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerKangaskhan, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Horsea[] = {
    overworld_frame(gObjectEventPic_FollowerHorsea, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerHorsea, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerHorsea, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerHorsea, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerHorsea, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerHorsea, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Seadra[] = {
    overworld_frame(gObjectEventPic_FollowerSeadra, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSeadra, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSeadra, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSeadra, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSeadra, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSeadra, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Goldeen[] = {
    overworld_frame(gObjectEventPic_FollowerGoldeen, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerGoldeen, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerGoldeen, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerGoldeen, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerGoldeen, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerGoldeen, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Seaking[] = {
    overworld_frame(gObjectEventPic_FollowerSeaking, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSeaking, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSeaking, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSeaking, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSeaking, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSeaking, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Staryu[] = {
    overworld_frame(gObjectEventPic_FollowerStaryu, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerStaryu, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerStaryu, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerStaryu, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerStaryu, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerStaryu, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Starmie[] = {
    overworld_frame(gObjectEventPic_FollowerStarmie, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerStarmie, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerStarmie, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerStarmie, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerStarmie, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerStarmie, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_MrMime[] = {
    overworld_frame(gObjectEventPic_FollowerMrMime, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMrMime, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMrMime, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMrMime, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMrMime, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMrMime, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Scyther[] = {
    overworld_frame(gObjectEventPic_FollowerScyther, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerScyther, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerScyther, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerScyther, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerScyther, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerScyther, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Jynx[] = {
    overworld_frame(gObjectEventPic_FollowerJynx, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerJynx, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerJynx, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerJynx, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerJynx, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerJynx, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Electabuzz[] = {
    overworld_frame(gObjectEventPic_FollowerElectabuzz, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerElectabuzz, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerElectabuzz, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerElectabuzz, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerElectabuzz, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerElectabuzz, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Magmar[] = {
    overworld_frame(gObjectEventPic_FollowerMagmar, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMagmar, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMagmar, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMagmar, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMagmar, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMagmar, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Pinsir[] = {
    overworld_frame(gObjectEventPic_FollowerPinsir, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerPinsir, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerPinsir, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerPinsir, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerPinsir, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerPinsir, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Tauros[] = {
    overworld_frame(gObjectEventPic_FollowerTauros, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerTauros, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerTauros, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerTauros, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerTauros, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerTauros, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Magikarp[] = {
    overworld_frame(gObjectEventPic_FollowerMagikarp, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMagikarp, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMagikarp, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMagikarp, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMagikarp, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMagikarp, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Gyarados[] = {
    overworld_frame(gObjectEventPic_FollowerGyarados, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerGyarados, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerGyarados, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerGyarados, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerGyarados, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerGyarados, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Lapras[] = {
    overworld_frame(gObjectEventPic_FollowerLapras, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerLapras, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerLapras, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerLapras, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerLapras, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerLapras, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Ditto[] = {
    overworld_frame(gObjectEventPic_FollowerDitto, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerDitto, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerDitto, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerDitto, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerDitto, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerDitto, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Eevee[] = {
    overworld_frame(gObjectEventPic_FollowerEevee, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerEevee, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerEevee, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerEevee, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerEevee, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerEevee, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Vaporeon[] = {
    overworld_frame(gObjectEventPic_FollowerVaporeon, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerVaporeon, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerVaporeon, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerVaporeon, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerVaporeon, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerVaporeon, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Jolteon[] = {
    overworld_frame(gObjectEventPic_FollowerJolteon, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerJolteon, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerJolteon, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerJolteon, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerJolteon, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerJolteon, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Flareon[] = {
    overworld_frame(gObjectEventPic_FollowerFlareon, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerFlareon, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerFlareon, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerFlareon, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerFlareon, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerFlareon, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Porygon[] = {
    overworld_frame(gObjectEventPic_FollowerPorygon, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerPorygon, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerPorygon, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerPorygon, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerPorygon, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerPorygon, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Omanyte[] = {
    overworld_frame(gObjectEventPic_FollowerOmanyte, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerOmanyte, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerOmanyte, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerOmanyte, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerOmanyte, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerOmanyte, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Omastar[] = {
    overworld_frame(gObjectEventPic_FollowerOmastar, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerOmastar, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerOmastar, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerOmastar, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerOmastar, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerOmastar, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Kabuto[] = {
    overworld_frame(gObjectEventPic_FollowerKabuto, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerKabuto, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerKabuto, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerKabuto, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerKabuto, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerKabuto, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Kabutops[] = {
    overworld_frame(gObjectEventPic_FollowerKabutops, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerKabutops, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerKabutops, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerKabutops, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerKabutops, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerKabutops, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Aerodactyl[] = {
    overworld_frame(gObjectEventPic_FollowerAerodactyl, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerAerodactyl, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerAerodactyl, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerAerodactyl, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerAerodactyl, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerAerodactyl, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Snorlax[] = {
    overworld_frame(gObjectEventPic_FollowerSnorlax, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSnorlax, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSnorlax, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSnorlax, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSnorlax, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSnorlax, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Articuno[] = {
    overworld_frame(gObjectEventPic_FollowerArticuno, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerArticuno, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerArticuno, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerArticuno, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerArticuno, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerArticuno, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Zapdos[] = {
    overworld_frame(gObjectEventPic_FollowerZapdos, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerZapdos, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerZapdos, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerZapdos, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerZapdos, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerZapdos, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Moltres[] = {
    overworld_frame(gObjectEventPic_FollowerMoltres, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMoltres, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMoltres, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMoltres, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMoltres, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMoltres, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Dratini[] = {
    overworld_frame(gObjectEventPic_FollowerDratini, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerDratini, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerDratini, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerDratini, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerDratini, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerDratini, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Dragonair[] = {
    overworld_frame(gObjectEventPic_FollowerDragonair, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerDragonair, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerDragonair, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerDragonair, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerDragonair, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerDragonair, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Dragonite[] = {
    overworld_frame(gObjectEventPic_FollowerDragonite, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerDragonite, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerDragonite, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerDragonite, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerDragonite, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerDragonite, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Mewtwo[] = {
    overworld_frame(gObjectEventPic_FollowerMewtwo, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMewtwo, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMewtwo, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMewtwo, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMewtwo, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMewtwo, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Mew[] = {
    overworld_frame(gObjectEventPic_FollowerMew, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMew, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMew, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMew, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMew, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMew, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Bayleef[] = {
    overworld_frame(gObjectEventPic_FollowerBayleef, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerBayleef, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerBayleef, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerBayleef, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerBayleef, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerBayleef, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Meganium[] = {
    overworld_frame(gObjectEventPic_FollowerMeganium, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMeganium, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMeganium, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMeganium, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMeganium, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMeganium, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Quilava[] = {
    overworld_frame(gObjectEventPic_FollowerQuilava, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerQuilava, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerQuilava, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerQuilava, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerQuilava, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerQuilava, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Typhlosion[] = {
    overworld_frame(gObjectEventPic_FollowerTyphlosion, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerTyphlosion, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerTyphlosion, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerTyphlosion, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerTyphlosion, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerTyphlosion, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Croconaw[] = {
    overworld_frame(gObjectEventPic_FollowerCroconaw, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerCroconaw, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerCroconaw, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerCroconaw, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerCroconaw, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerCroconaw, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Feraligatr[] = {
    overworld_frame(gObjectEventPic_FollowerFeraligatr, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerFeraligatr, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerFeraligatr, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerFeraligatr, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerFeraligatr, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerFeraligatr, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Sentret[] = {
    overworld_frame(gObjectEventPic_FollowerSentret, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSentret, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSentret, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSentret, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSentret, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSentret, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Furret[] = {
    overworld_frame(gObjectEventPic_FollowerFurret, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerFurret, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerFurret, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerFurret, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerFurret, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerFurret, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Hoothoot[] = {
    overworld_frame(gObjectEventPic_FollowerHoothoot, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerHoothoot, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerHoothoot, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerHoothoot, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerHoothoot, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerHoothoot, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Noctowl[] = {
    overworld_frame(gObjectEventPic_FollowerNoctowl, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerNoctowl, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerNoctowl, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerNoctowl, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerNoctowl, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerNoctowl, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Ledyba[] = {
    overworld_frame(gObjectEventPic_FollowerLedyba, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerLedyba, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerLedyba, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerLedyba, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerLedyba, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerLedyba, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Ledian[] = {
    overworld_frame(gObjectEventPic_FollowerLedian, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerLedian, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerLedian, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerLedian, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerLedian, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerLedian, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Spinarak[] = {
    overworld_frame(gObjectEventPic_FollowerSpinarak, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSpinarak, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSpinarak, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSpinarak, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSpinarak, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSpinarak, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Ariados[] = {
    overworld_frame(gObjectEventPic_FollowerAriados, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerAriados, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerAriados, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerAriados, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerAriados, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerAriados, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Crobat[] = {
    overworld_frame(gObjectEventPic_FollowerCrobat, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerCrobat, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerCrobat, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerCrobat, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerCrobat, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerCrobat, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Chinchou[] = {
    overworld_frame(gObjectEventPic_FollowerChinchou, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerChinchou, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerChinchou, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerChinchou, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerChinchou, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerChinchou, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Lanturn[] = {
    overworld_frame(gObjectEventPic_FollowerLanturn, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerLanturn, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerLanturn, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerLanturn, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerLanturn, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerLanturn, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Pichu[] = {
    overworld_frame(gObjectEventPic_FollowerPichu, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerPichu, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerPichu, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerPichu, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerPichu, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerPichu, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Cleffa[] = {
    overworld_frame(gObjectEventPic_FollowerCleffa, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerCleffa, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerCleffa, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerCleffa, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerCleffa, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerCleffa, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Igglybuff[] = {
    overworld_frame(gObjectEventPic_FollowerIgglybuff, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerIgglybuff, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerIgglybuff, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerIgglybuff, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerIgglybuff, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerIgglybuff, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Togepi[] = {
    overworld_frame(gObjectEventPic_FollowerTogepi, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerTogepi, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerTogepi, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerTogepi, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerTogepi, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerTogepi, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Togetic[] = {
    overworld_frame(gObjectEventPic_FollowerTogetic, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerTogetic, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerTogetic, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerTogetic, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerTogetic, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerTogetic, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Natu[] = {
    overworld_frame(gObjectEventPic_FollowerNatu, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerNatu, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerNatu, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerNatu, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerNatu, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerNatu, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Xatu[] = {
    overworld_frame(gObjectEventPic_FollowerXatu, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerXatu, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerXatu, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerXatu, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerXatu, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerXatu, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Mareep[] = {
    overworld_frame(gObjectEventPic_FollowerMareep, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMareep, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMareep, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMareep, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMareep, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMareep, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Flaaffy[] = {
    overworld_frame(gObjectEventPic_FollowerFlaaffy, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerFlaaffy, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerFlaaffy, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerFlaaffy, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerFlaaffy, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerFlaaffy, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Ampharos[] = {
    overworld_frame(gObjectEventPic_FollowerAmpharos, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerAmpharos, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerAmpharos, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerAmpharos, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerAmpharos, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerAmpharos, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Bellossom[] = {
    overworld_frame(gObjectEventPic_FollowerBellossom, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerBellossom, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerBellossom, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerBellossom, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerBellossom, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerBellossom, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Marill[] = {
    overworld_frame(gObjectEventPic_FollowerMarill, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMarill, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMarill, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMarill, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMarill, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMarill, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Azumarill[] = {
    overworld_frame(gObjectEventPic_FollowerAzumarill, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerAzumarill, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerAzumarill, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerAzumarill, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerAzumarill, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerAzumarill, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Sudowoodo[] = {
    overworld_frame(gObjectEventPic_FollowerSudowoodo, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSudowoodo, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSudowoodo, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSudowoodo, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSudowoodo, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSudowoodo, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Politoed[] = {
    overworld_frame(gObjectEventPic_FollowerPolitoed, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerPolitoed, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerPolitoed, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerPolitoed, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerPolitoed, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerPolitoed, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Hoppip[] = {
    overworld_frame(gObjectEventPic_FollowerHoppip, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerHoppip, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerHoppip, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerHoppip, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerHoppip, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerHoppip, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Skiploom[] = {
    overworld_frame(gObjectEventPic_FollowerSkiploom, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSkiploom, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSkiploom, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSkiploom, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSkiploom, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSkiploom, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Jumpluff[] = {
    overworld_frame(gObjectEventPic_FollowerJumpluff, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerJumpluff, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerJumpluff, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerJumpluff, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerJumpluff, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerJumpluff, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Aipom[] = {
    overworld_frame(gObjectEventPic_FollowerAipom, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerAipom, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerAipom, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerAipom, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerAipom, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerAipom, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Sunkern[] = {
    overworld_frame(gObjectEventPic_FollowerSunkern, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSunkern, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSunkern, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSunkern, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSunkern, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSunkern, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Sunflora[] = {
    overworld_frame(gObjectEventPic_FollowerSunflora, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSunflora, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSunflora, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSunflora, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSunflora, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSunflora, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Yanma[] = {
    overworld_frame(gObjectEventPic_FollowerYanma, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerYanma, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerYanma, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerYanma, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerYanma, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerYanma, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Wooper[] = {
    overworld_frame(gObjectEventPic_FollowerWooper, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerWooper, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerWooper, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerWooper, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerWooper, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerWooper, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Quagsire[] = {
    overworld_frame(gObjectEventPic_FollowerQuagsire, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerQuagsire, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerQuagsire, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerQuagsire, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerQuagsire, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerQuagsire, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Espeon[] = {
    overworld_frame(gObjectEventPic_FollowerEspeon, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerEspeon, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerEspeon, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerEspeon, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerEspeon, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerEspeon, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Umbreon[] = {
    overworld_frame(gObjectEventPic_FollowerUmbreon, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerUmbreon, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerUmbreon, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerUmbreon, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerUmbreon, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerUmbreon, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Murkrow[] = {
    overworld_frame(gObjectEventPic_FollowerMurkrow, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMurkrow, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMurkrow, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMurkrow, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMurkrow, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMurkrow, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Slowking[] = {
    overworld_frame(gObjectEventPic_FollowerSlowking, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSlowking, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSlowking, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSlowking, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSlowking, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSlowking, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Misdreavus[] = {
    overworld_frame(gObjectEventPic_FollowerMisdreavus, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMisdreavus, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMisdreavus, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMisdreavus, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMisdreavus, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMisdreavus, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Wobbuffet[] = {
    overworld_frame(gObjectEventPic_FollowerWobbuffet, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerWobbuffet, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerWobbuffet, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerWobbuffet, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerWobbuffet, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerWobbuffet, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Girafarig[] = {
    overworld_frame(gObjectEventPic_FollowerGirafarig, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerGirafarig, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerGirafarig, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerGirafarig, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerGirafarig, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerGirafarig, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Pineco[] = {
    overworld_frame(gObjectEventPic_FollowerPineco, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerPineco, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerPineco, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerPineco, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerPineco, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerPineco, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Forretress[] = {
    overworld_frame(gObjectEventPic_FollowerForretress, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerForretress, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerForretress, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerForretress, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerForretress, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerForretress, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Dunsparce[] = {
    overworld_frame(gObjectEventPic_FollowerDunsparce, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerDunsparce, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerDunsparce, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerDunsparce, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerDunsparce, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerDunsparce, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Gligar[] = {
    overworld_frame(gObjectEventPic_FollowerGligar, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerGligar, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerGligar, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerGligar, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerGligar, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerGligar, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Snubbull[] = {
    overworld_frame(gObjectEventPic_FollowerSnubbull, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSnubbull, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSnubbull, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSnubbull, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSnubbull, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSnubbull, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Granbull[] = {
    overworld_frame(gObjectEventPic_FollowerGranbull, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerGranbull, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerGranbull, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerGranbull, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerGranbull, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerGranbull, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Qwilfish[] = {
    overworld_frame(gObjectEventPic_FollowerQwilfish, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerQwilfish, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerQwilfish, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerQwilfish, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerQwilfish, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerQwilfish, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Scizor[] = {
    overworld_frame(gObjectEventPic_FollowerScizor, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerScizor, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerScizor, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerScizor, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerScizor, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerScizor, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Shuckle[] = {
    overworld_frame(gObjectEventPic_FollowerShuckle, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerShuckle, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerShuckle, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerShuckle, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerShuckle, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerShuckle, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Heracross[] = {
    overworld_frame(gObjectEventPic_FollowerHeracross, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerHeracross, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerHeracross, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerHeracross, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerHeracross, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerHeracross, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Sneasel[] = {
    overworld_frame(gObjectEventPic_FollowerSneasel, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSneasel, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSneasel, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSneasel, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSneasel, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSneasel, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Teddiursa[] = {
    overworld_frame(gObjectEventPic_FollowerTeddiursa, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerTeddiursa, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerTeddiursa, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerTeddiursa, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerTeddiursa, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerTeddiursa, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Ursaring[] = {
    overworld_frame(gObjectEventPic_FollowerUrsaring, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerUrsaring, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerUrsaring, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerUrsaring, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerUrsaring, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerUrsaring, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Slugma[] = {
    overworld_frame(gObjectEventPic_FollowerSlugma, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSlugma, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSlugma, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSlugma, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSlugma, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSlugma, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Magcargo[] = {
    overworld_frame(gObjectEventPic_FollowerMagcargo, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMagcargo, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMagcargo, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMagcargo, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMagcargo, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMagcargo, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Swinub[] = {
    overworld_frame(gObjectEventPic_FollowerSwinub, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSwinub, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSwinub, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSwinub, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSwinub, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSwinub, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Piloswine[] = {
    overworld_frame(gObjectEventPic_FollowerPiloswine, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerPiloswine, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerPiloswine, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerPiloswine, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerPiloswine, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerPiloswine, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Corsola[] = {
    overworld_frame(gObjectEventPic_FollowerCorsola, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerCorsola, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerCorsola, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerCorsola, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerCorsola, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerCorsola, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Remoraid[] = {
    overworld_frame(gObjectEventPic_FollowerRemoraid, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerRemoraid, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerRemoraid, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerRemoraid, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerRemoraid, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerRemoraid, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Octillery[] = {
    overworld_frame(gObjectEventPic_FollowerOctillery, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerOctillery, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerOctillery, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerOctillery, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerOctillery, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerOctillery, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Delibird[] = {
    overworld_frame(gObjectEventPic_FollowerDelibird, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerDelibird, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerDelibird, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerDelibird, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerDelibird, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerDelibird, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Mantine[] = {
    overworld_frame(gObjectEventPic_FollowerMantine, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMantine, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMantine, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMantine, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMantine, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMantine, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Skarmory[] = {
    overworld_frame(gObjectEventPic_FollowerSkarmory, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSkarmory, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSkarmory, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSkarmory, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSkarmory, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSkarmory, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Houndour[] = {
    overworld_frame(gObjectEventPic_FollowerHoundour, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerHoundour, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerHoundour, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerHoundour, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerHoundour, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerHoundour, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Houndoom[] = {
    overworld_frame(gObjectEventPic_FollowerHoundoom, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerHoundoom, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerHoundoom, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerHoundoom, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerHoundoom, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerHoundoom, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Kingdra[] = {
    overworld_frame(gObjectEventPic_FollowerKingdra, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerKingdra, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerKingdra, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerKingdra, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerKingdra, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerKingdra, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Phanpy[] = {
    overworld_frame(gObjectEventPic_FollowerPhanpy, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerPhanpy, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerPhanpy, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerPhanpy, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerPhanpy, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerPhanpy, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Donphan[] = {
    overworld_frame(gObjectEventPic_FollowerDonphan, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerDonphan, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerDonphan, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerDonphan, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerDonphan, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerDonphan, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Porygon2[] = {
    overworld_frame(gObjectEventPic_FollowerPorygon2, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerPorygon2, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerPorygon2, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerPorygon2, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerPorygon2, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerPorygon2, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Stantler[] = {
    overworld_frame(gObjectEventPic_FollowerStantler, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerStantler, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerStantler, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerStantler, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerStantler, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerStantler, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Smeargle[] = {
    overworld_frame(gObjectEventPic_FollowerSmeargle, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSmeargle, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSmeargle, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSmeargle, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSmeargle, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSmeargle, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Tyrogue[] = {
    overworld_frame(gObjectEventPic_FollowerTyrogue, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerTyrogue, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerTyrogue, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerTyrogue, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerTyrogue, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerTyrogue, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Hitmontop[] = {
    overworld_frame(gObjectEventPic_FollowerHitmontop, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerHitmontop, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerHitmontop, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerHitmontop, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerHitmontop, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerHitmontop, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Smoochum[] = {
    overworld_frame(gObjectEventPic_FollowerSmoochum, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSmoochum, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSmoochum, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSmoochum, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSmoochum, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSmoochum, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Elekid[] = {
    overworld_frame(gObjectEventPic_FollowerElekid, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerElekid, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerElekid, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerElekid, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerElekid, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerElekid, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Magby[] = {
    overworld_frame(gObjectEventPic_FollowerMagby, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMagby, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMagby, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMagby, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMagby, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMagby, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Miltank[] = {
    overworld_frame(gObjectEventPic_FollowerMiltank, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMiltank, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMiltank, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMiltank, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMiltank, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMiltank, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Blissey[] = {
    overworld_frame(gObjectEventPic_FollowerBlissey, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerBlissey, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerBlissey, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerBlissey, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerBlissey, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerBlissey, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Raikou[] = {
    overworld_frame(gObjectEventPic_FollowerRaikou, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerRaikou, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerRaikou, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerRaikou, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerRaikou, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerRaikou, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Entei[] = {
    overworld_frame(gObjectEventPic_FollowerEntei, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerEntei, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerEntei, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerEntei, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerEntei, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerEntei, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Suicune[] = {
    overworld_frame(gObjectEventPic_FollowerSuicune, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSuicune, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSuicune, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSuicune, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSuicune, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSuicune, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Larvitar[] = {
    overworld_frame(gObjectEventPic_FollowerLarvitar, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerLarvitar, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerLarvitar, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerLarvitar, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerLarvitar, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerLarvitar, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Pupitar[] = {
    overworld_frame(gObjectEventPic_FollowerPupitar, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerPupitar, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerPupitar, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerPupitar, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerPupitar, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerPupitar, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Tyranitar[] = {
    overworld_frame(gObjectEventPic_FollowerTyranitar, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerTyranitar, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerTyranitar, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerTyranitar, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerTyranitar, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerTyranitar, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Celebi[] = {
    overworld_frame(gObjectEventPic_FollowerCelebi, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerCelebi, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerCelebi, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerCelebi, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerCelebi, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerCelebi, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Grovyle[] = {
    overworld_frame(gObjectEventPic_FollowerGrovyle, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerGrovyle, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerGrovyle, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerGrovyle, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerGrovyle, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerGrovyle, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Sceptile[] = {
    overworld_frame(gObjectEventPic_FollowerSceptile, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSceptile, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSceptile, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSceptile, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSceptile, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSceptile, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Combusken[] = {
    overworld_frame(gObjectEventPic_FollowerCombusken, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerCombusken, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerCombusken, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerCombusken, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerCombusken, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerCombusken, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Blaziken[] = {
    overworld_frame(gObjectEventPic_FollowerBlaziken, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerBlaziken, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerBlaziken, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerBlaziken, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerBlaziken, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerBlaziken, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Marshtomp[] = {
    overworld_frame(gObjectEventPic_FollowerMarshtomp, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMarshtomp, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMarshtomp, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMarshtomp, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMarshtomp, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMarshtomp, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Swampert[] = {
    overworld_frame(gObjectEventPic_FollowerSwampert, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSwampert, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSwampert, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSwampert, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSwampert, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSwampert, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Poochyena[] = {
    overworld_frame(gObjectEventPic_FollowerPoochyena, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerPoochyena, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerPoochyena, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerPoochyena, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerPoochyena, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerPoochyena, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Mightyena[] = {
    overworld_frame(gObjectEventPic_FollowerMightyena, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMightyena, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMightyena, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMightyena, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMightyena, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMightyena, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Zigzagoon[] = {
    overworld_frame(gObjectEventPic_FollowerZigzagoon, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerZigzagoon, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerZigzagoon, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerZigzagoon, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerZigzagoon, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerZigzagoon, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Linoone[] = {
    overworld_frame(gObjectEventPic_FollowerLinoone, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerLinoone, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerLinoone, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerLinoone, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerLinoone, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerLinoone, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Wurmple[] = {
    overworld_frame(gObjectEventPic_FollowerWurmple, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerWurmple, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerWurmple, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerWurmple, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerWurmple, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerWurmple, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Silcoon[] = {
    overworld_frame(gObjectEventPic_FollowerSilcoon, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSilcoon, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSilcoon, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSilcoon, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSilcoon, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSilcoon, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Beautifly[] = {
    overworld_frame(gObjectEventPic_FollowerBeautifly, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerBeautifly, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerBeautifly, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerBeautifly, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerBeautifly, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerBeautifly, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Cascoon[] = {
    overworld_frame(gObjectEventPic_FollowerCascoon, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerCascoon, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerCascoon, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerCascoon, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerCascoon, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerCascoon, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Dustox[] = {
    overworld_frame(gObjectEventPic_FollowerDustox, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerDustox, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerDustox, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerDustox, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerDustox, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerDustox, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Lotad[] = {
    overworld_frame(gObjectEventPic_FollowerLotad, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerLotad, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerLotad, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerLotad, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerLotad, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerLotad, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Lombre[] = {
    overworld_frame(gObjectEventPic_FollowerLombre, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerLombre, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerLombre, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerLombre, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerLombre, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerLombre, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Ludicolo[] = {
    overworld_frame(gObjectEventPic_FollowerLudicolo, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerLudicolo, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerLudicolo, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerLudicolo, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerLudicolo, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerLudicolo, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Seedot[] = {
    overworld_frame(gObjectEventPic_FollowerSeedot, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSeedot, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSeedot, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSeedot, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSeedot, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSeedot, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Nuzleaf[] = {
    overworld_frame(gObjectEventPic_FollowerNuzleaf, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerNuzleaf, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerNuzleaf, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerNuzleaf, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerNuzleaf, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerNuzleaf, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Shiftry[] = {
    overworld_frame(gObjectEventPic_FollowerShiftry, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerShiftry, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerShiftry, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerShiftry, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerShiftry, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerShiftry, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Nincada[] = {
    overworld_frame(gObjectEventPic_FollowerNincada, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerNincada, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerNincada, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerNincada, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerNincada, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerNincada, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Ninjask[] = {
    overworld_frame(gObjectEventPic_FollowerNinjask, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerNinjask, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerNinjask, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerNinjask, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerNinjask, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerNinjask, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Shedinja[] = {
    overworld_frame(gObjectEventPic_FollowerShedinja, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerShedinja, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerShedinja, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerShedinja, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerShedinja, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerShedinja, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Taillow[] = {
    overworld_frame(gObjectEventPic_FollowerTaillow, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerTaillow, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerTaillow, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerTaillow, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerTaillow, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerTaillow, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Swellow[] = {
    overworld_frame(gObjectEventPic_FollowerSwellow, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSwellow, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSwellow, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSwellow, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSwellow, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSwellow, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Shroomish[] = {
    overworld_frame(gObjectEventPic_FollowerShroomish, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerShroomish, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerShroomish, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerShroomish, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerShroomish, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerShroomish, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Breloom[] = {
    overworld_frame(gObjectEventPic_FollowerBreloom, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerBreloom, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerBreloom, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerBreloom, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerBreloom, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerBreloom, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Spinda[] = {
    overworld_frame(gObjectEventPic_FollowerSpinda, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSpinda, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSpinda, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSpinda, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSpinda, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSpinda, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Wingull[] = {
    overworld_frame(gObjectEventPic_FollowerWingull, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerWingull, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerWingull, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerWingull, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerWingull, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerWingull, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Pelipper[] = {
    overworld_frame(gObjectEventPic_FollowerPelipper, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerPelipper, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerPelipper, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerPelipper, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerPelipper, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerPelipper, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Surskit[] = {
    overworld_frame(gObjectEventPic_FollowerSurskit, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSurskit, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSurskit, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSurskit, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSurskit, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSurskit, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Masquerain[] = {
    overworld_frame(gObjectEventPic_FollowerMasquerain, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMasquerain, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMasquerain, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMasquerain, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMasquerain, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMasquerain, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Wailmer[] = {
    overworld_frame(gObjectEventPic_FollowerWailmer, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerWailmer, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerWailmer, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerWailmer, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerWailmer, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerWailmer, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Skitty[] = {
    overworld_frame(gObjectEventPic_FollowerSkitty, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSkitty, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSkitty, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSkitty, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSkitty, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSkitty, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Delcatty[] = {
    overworld_frame(gObjectEventPic_FollowerDelcatty, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerDelcatty, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerDelcatty, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerDelcatty, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerDelcatty, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerDelcatty, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Kecleon[] = {
    overworld_frame(gObjectEventPic_FollowerKecleon, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerKecleon, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerKecleon, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerKecleon, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerKecleon, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerKecleon, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Baltoy[] = {
    overworld_frame(gObjectEventPic_FollowerBaltoy, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerBaltoy, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerBaltoy, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerBaltoy, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerBaltoy, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerBaltoy, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Claydol[] = {
    overworld_frame(gObjectEventPic_FollowerClaydol, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerClaydol, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerClaydol, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerClaydol, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerClaydol, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerClaydol, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Nosepass[] = {
    overworld_frame(gObjectEventPic_FollowerNosepass, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerNosepass, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerNosepass, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerNosepass, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerNosepass, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerNosepass, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Torkoal[] = {
    overworld_frame(gObjectEventPic_FollowerTorkoal, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerTorkoal, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerTorkoal, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerTorkoal, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerTorkoal, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerTorkoal, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Sableye[] = {
    overworld_frame(gObjectEventPic_FollowerSableye, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSableye, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSableye, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSableye, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSableye, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSableye, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Barboach[] = {
    overworld_frame(gObjectEventPic_FollowerBarboach, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerBarboach, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerBarboach, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerBarboach, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerBarboach, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerBarboach, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Whiscash[] = {
    overworld_frame(gObjectEventPic_FollowerWhiscash, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerWhiscash, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerWhiscash, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerWhiscash, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerWhiscash, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerWhiscash, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Luvdisc[] = {
    overworld_frame(gObjectEventPic_FollowerLuvdisc, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerLuvdisc, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerLuvdisc, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerLuvdisc, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerLuvdisc, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerLuvdisc, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Corphish[] = {
    overworld_frame(gObjectEventPic_FollowerCorphish, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerCorphish, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerCorphish, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerCorphish, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerCorphish, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerCorphish, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Crawdaunt[] = {
    overworld_frame(gObjectEventPic_FollowerCrawdaunt, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerCrawdaunt, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerCrawdaunt, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerCrawdaunt, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerCrawdaunt, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerCrawdaunt, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Feebas[] = {
    overworld_frame(gObjectEventPic_FollowerFeebas, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerFeebas, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerFeebas, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerFeebas, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerFeebas, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerFeebas, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Milotic[] = {
    overworld_frame(gObjectEventPic_FollowerMilotic, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMilotic, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMilotic, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMilotic, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMilotic, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMilotic, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Carvanha[] = {
    overworld_frame(gObjectEventPic_FollowerCarvanha, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerCarvanha, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerCarvanha, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerCarvanha, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerCarvanha, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerCarvanha, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Sharpedo[] = {
    overworld_frame(gObjectEventPic_FollowerSharpedo, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSharpedo, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSharpedo, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSharpedo, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSharpedo, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSharpedo, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Trapinch[] = {
    overworld_frame(gObjectEventPic_FollowerTrapinch, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerTrapinch, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerTrapinch, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerTrapinch, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerTrapinch, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerTrapinch, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Vibrava[] = {
    overworld_frame(gObjectEventPic_FollowerVibrava, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerVibrava, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerVibrava, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerVibrava, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerVibrava, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerVibrava, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Flygon[] = {
    overworld_frame(gObjectEventPic_FollowerFlygon, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerFlygon, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerFlygon, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerFlygon, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerFlygon, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerFlygon, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Makuhita[] = {
    overworld_frame(gObjectEventPic_FollowerMakuhita, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMakuhita, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMakuhita, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMakuhita, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMakuhita, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMakuhita, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Hariyama[] = {
    overworld_frame(gObjectEventPic_FollowerHariyama, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerHariyama, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerHariyama, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerHariyama, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerHariyama, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerHariyama, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Electrike[] = {
    overworld_frame(gObjectEventPic_FollowerElectrike, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerElectrike, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerElectrike, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerElectrike, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerElectrike, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerElectrike, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Manectric[] = {
    overworld_frame(gObjectEventPic_FollowerManectric, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerManectric, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerManectric, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerManectric, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerManectric, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerManectric, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Numel[] = {
    overworld_frame(gObjectEventPic_FollowerNumel, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerNumel, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerNumel, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerNumel, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerNumel, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerNumel, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Camerupt[] = {
    overworld_frame(gObjectEventPic_FollowerCamerupt, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerCamerupt, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerCamerupt, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerCamerupt, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerCamerupt, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerCamerupt, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Spheal[] = {
    overworld_frame(gObjectEventPic_FollowerSpheal, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSpheal, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSpheal, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSpheal, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSpheal, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSpheal, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Sealeo[] = {
    overworld_frame(gObjectEventPic_FollowerSealeo, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSealeo, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSealeo, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSealeo, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSealeo, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSealeo, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Walrein[] = {
    overworld_frame(gObjectEventPic_FollowerWalrein, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerWalrein, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerWalrein, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerWalrein, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerWalrein, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerWalrein, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Cacnea[] = {
    overworld_frame(gObjectEventPic_FollowerCacnea, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerCacnea, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerCacnea, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerCacnea, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerCacnea, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerCacnea, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Cacturne[] = {
    overworld_frame(gObjectEventPic_FollowerCacturne, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerCacturne, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerCacturne, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerCacturne, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerCacturne, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerCacturne, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Snorunt[] = {
    overworld_frame(gObjectEventPic_FollowerSnorunt, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSnorunt, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSnorunt, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSnorunt, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSnorunt, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSnorunt, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Glalie[] = {
    overworld_frame(gObjectEventPic_FollowerGlalie, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerGlalie, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerGlalie, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerGlalie, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerGlalie, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerGlalie, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Lunatone[] = {
    overworld_frame(gObjectEventPic_FollowerLunatone, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerLunatone, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerLunatone, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerLunatone, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerLunatone, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerLunatone, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Solrock[] = {
    overworld_frame(gObjectEventPic_FollowerSolrock, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSolrock, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSolrock, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSolrock, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSolrock, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSolrock, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Azurill[] = {
    overworld_frame(gObjectEventPic_FollowerAzurill, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerAzurill, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerAzurill, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerAzurill, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerAzurill, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerAzurill, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Spoink[] = {
    overworld_frame(gObjectEventPic_FollowerSpoink, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSpoink, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSpoink, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSpoink, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSpoink, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSpoink, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Grumpig[] = {
    overworld_frame(gObjectEventPic_FollowerGrumpig, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerGrumpig, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerGrumpig, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerGrumpig, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerGrumpig, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerGrumpig, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Plusle[] = {
    overworld_frame(gObjectEventPic_FollowerPlusle, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerPlusle, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerPlusle, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerPlusle, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerPlusle, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerPlusle, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Minun[] = {
    overworld_frame(gObjectEventPic_FollowerMinun, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMinun, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMinun, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMinun, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMinun, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMinun, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Mawile[] = {
    overworld_frame(gObjectEventPic_FollowerMawile, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMawile, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMawile, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMawile, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMawile, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMawile, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Meditite[] = {
    overworld_frame(gObjectEventPic_FollowerMeditite, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMeditite, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMeditite, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMeditite, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMeditite, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMeditite, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Medicham[] = {
    overworld_frame(gObjectEventPic_FollowerMedicham, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMedicham, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMedicham, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMedicham, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMedicham, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMedicham, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Swablu[] = {
    overworld_frame(gObjectEventPic_FollowerSwablu, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSwablu, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSwablu, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSwablu, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSwablu, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSwablu, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Altaria[] = {
    overworld_frame(gObjectEventPic_FollowerAltaria, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerAltaria, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerAltaria, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerAltaria, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerAltaria, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerAltaria, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Wynaut[] = {
    overworld_frame(gObjectEventPic_FollowerWynaut, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerWynaut, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerWynaut, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerWynaut, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerWynaut, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerWynaut, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Duskull[] = {
    overworld_frame(gObjectEventPic_FollowerDuskull, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerDuskull, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerDuskull, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerDuskull, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerDuskull, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerDuskull, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Dusclops[] = {
    overworld_frame(gObjectEventPic_FollowerDusclops, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerDusclops, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerDusclops, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerDusclops, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerDusclops, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerDusclops, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Roselia[] = {
    overworld_frame(gObjectEventPic_FollowerRoselia, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerRoselia, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerRoselia, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerRoselia, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerRoselia, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerRoselia, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Slakoth[] = {
    overworld_frame(gObjectEventPic_FollowerSlakoth, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSlakoth, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSlakoth, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSlakoth, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSlakoth, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSlakoth, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Vigoroth[] = {
    overworld_frame(gObjectEventPic_FollowerVigoroth, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerVigoroth, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerVigoroth, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerVigoroth, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerVigoroth, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerVigoroth, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Slaking[] = {
    overworld_frame(gObjectEventPic_FollowerSlaking, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSlaking, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSlaking, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSlaking, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSlaking, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSlaking, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Gulpin[] = {
    overworld_frame(gObjectEventPic_FollowerGulpin, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerGulpin, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerGulpin, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerGulpin, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerGulpin, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerGulpin, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Swalot[] = {
    overworld_frame(gObjectEventPic_FollowerSwalot, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSwalot, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSwalot, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSwalot, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSwalot, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSwalot, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Tropius[] = {
    overworld_frame(gObjectEventPic_FollowerTropius, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerTropius, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerTropius, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerTropius, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerTropius, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerTropius, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Whismur[] = {
    overworld_frame(gObjectEventPic_FollowerWhismur, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerWhismur, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerWhismur, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerWhismur, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerWhismur, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerWhismur, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Loudred[] = {
    overworld_frame(gObjectEventPic_FollowerLoudred, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerLoudred, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerLoudred, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerLoudred, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerLoudred, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerLoudred, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Exploud[] = {
    overworld_frame(gObjectEventPic_FollowerExploud, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerExploud, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerExploud, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerExploud, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerExploud, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerExploud, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Clamperl[] = {
    overworld_frame(gObjectEventPic_FollowerClamperl, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerClamperl, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerClamperl, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerClamperl, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerClamperl, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerClamperl, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Huntail[] = {
    overworld_frame(gObjectEventPic_FollowerHuntail, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerHuntail, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerHuntail, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerHuntail, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerHuntail, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerHuntail, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Gorebyss[] = {
    overworld_frame(gObjectEventPic_FollowerGorebyss, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerGorebyss, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerGorebyss, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerGorebyss, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerGorebyss, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerGorebyss, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Absol[] = {
    overworld_frame(gObjectEventPic_FollowerAbsol, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerAbsol, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerAbsol, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerAbsol, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerAbsol, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerAbsol, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Shuppet[] = {
    overworld_frame(gObjectEventPic_FollowerShuppet, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerShuppet, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerShuppet, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerShuppet, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerShuppet, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerShuppet, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Banette[] = {
    overworld_frame(gObjectEventPic_FollowerBanette, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerBanette, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerBanette, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerBanette, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerBanette, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerBanette, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Seviper[] = {
    overworld_frame(gObjectEventPic_FollowerSeviper, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSeviper, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSeviper, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSeviper, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSeviper, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSeviper, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Zangoose[] = {
    overworld_frame(gObjectEventPic_FollowerZangoose, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerZangoose, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerZangoose, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerZangoose, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerZangoose, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerZangoose, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Relicanth[] = {
    overworld_frame(gObjectEventPic_FollowerRelicanth, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerRelicanth, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerRelicanth, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerRelicanth, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerRelicanth, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerRelicanth, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Aron[] = {
    overworld_frame(gObjectEventPic_FollowerAron, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerAron, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerAron, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerAron, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerAron, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerAron, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Lairon[] = {
    overworld_frame(gObjectEventPic_FollowerLairon, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerLairon, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerLairon, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerLairon, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerLairon, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerLairon, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Aggron[] = {
    overworld_frame(gObjectEventPic_FollowerAggron, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerAggron, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerAggron, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerAggron, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerAggron, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerAggron, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Castform[] = {
    overworld_frame(gObjectEventPic_FollowerCastform, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerCastform, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerCastform, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerCastform, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerCastform, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerCastform, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Volbeat[] = {
    overworld_frame(gObjectEventPic_FollowerVolbeat, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerVolbeat, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerVolbeat, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerVolbeat, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerVolbeat, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerVolbeat, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Illumise[] = {
    overworld_frame(gObjectEventPic_FollowerIllumise, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerIllumise, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerIllumise, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerIllumise, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerIllumise, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerIllumise, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Lileep[] = {
    overworld_frame(gObjectEventPic_FollowerLileep, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerLileep, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerLileep, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerLileep, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerLileep, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerLileep, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Cradily[] = {
    overworld_frame(gObjectEventPic_FollowerCradily, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerCradily, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerCradily, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerCradily, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerCradily, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerCradily, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Anorith[] = {
    overworld_frame(gObjectEventPic_FollowerAnorith, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerAnorith, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerAnorith, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerAnorith, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerAnorith, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerAnorith, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Armaldo[] = {
    overworld_frame(gObjectEventPic_FollowerArmaldo, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerArmaldo, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerArmaldo, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerArmaldo, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerArmaldo, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerArmaldo, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Ralts[] = {
    overworld_frame(gObjectEventPic_FollowerRalts, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerRalts, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerRalts, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerRalts, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerRalts, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerRalts, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Kirlia[] = {
    overworld_frame(gObjectEventPic_FollowerKirlia, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerKirlia, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerKirlia, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerKirlia, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerKirlia, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerKirlia, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Gardevoir[] = {
    overworld_frame(gObjectEventPic_FollowerGardevoir, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerGardevoir, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerGardevoir, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerGardevoir, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerGardevoir, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerGardevoir, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Bagon[] = {
    overworld_frame(gObjectEventPic_FollowerBagon, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerBagon, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerBagon, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerBagon, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerBagon, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerBagon, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Shelgon[] = {
    overworld_frame(gObjectEventPic_FollowerShelgon, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerShelgon, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerShelgon, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerShelgon, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerShelgon, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerShelgon, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Salamence[] = {
    overworld_frame(gObjectEventPic_FollowerSalamence, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerSalamence, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerSalamence, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerSalamence, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerSalamence, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerSalamence, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Beldum[] = {
    overworld_frame(gObjectEventPic_FollowerBeldum, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerBeldum, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerBeldum, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerBeldum, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerBeldum, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerBeldum, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Metang[] = {
    overworld_frame(gObjectEventPic_FollowerMetang, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMetang, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMetang, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMetang, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMetang, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMetang, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Metagross[] = {
    overworld_frame(gObjectEventPic_FollowerMetagross, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerMetagross, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerMetagross, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerMetagross, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerMetagross, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerMetagross, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Regirock[] = {
    overworld_frame(gObjectEventPic_FollowerRegirock, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerRegirock, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerRegirock, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerRegirock, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerRegirock, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerRegirock, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Regice[] = {
    overworld_frame(gObjectEventPic_FollowerRegice, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerRegice, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerRegice, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerRegice, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerRegice, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerRegice, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Registeel[] = {
    overworld_frame(gObjectEventPic_FollowerRegisteel, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerRegisteel, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerRegisteel, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerRegisteel, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerRegisteel, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerRegisteel, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Latias[] = {
    overworld_frame(gObjectEventPic_FollowerLatias, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerLatias, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerLatias, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerLatias, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerLatias, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerLatias, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Latios[] = {
    overworld_frame(gObjectEventPic_FollowerLatios, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerLatios, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerLatios, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerLatios, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerLatios, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerLatios, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Jirachi[] = {
    overworld_frame(gObjectEventPic_FollowerJirachi, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerJirachi, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerJirachi, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerJirachi, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerJirachi, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerJirachi, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Deoxys[] = {
    overworld_frame(gObjectEventPic_FollowerDeoxys, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerDeoxys, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerDeoxys, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerDeoxys, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerDeoxys, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerDeoxys, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Chimecho[] = {
    overworld_frame(gObjectEventPic_FollowerChimecho, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerChimecho, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerChimecho, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerChimecho, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerChimecho, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerChimecho, 4, 4, 5),
};

static const struct SpriteFrameImage sPicTable_Follower_UnownA[] = {
    overworld_frame(gObjectEventPic_FollowerUnownA, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerUnownA, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerUnownA, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerUnownA, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerUnownA, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerUnownA, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_UnownB[] = {
    overworld_frame(gObjectEventPic_FollowerUnownB, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerUnownB, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerUnownB, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerUnownB, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerUnownB, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerUnownB, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_UnownC[] = {
    overworld_frame(gObjectEventPic_FollowerUnownC, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerUnownC, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerUnownC, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerUnownC, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerUnownC, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerUnownC, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_UnownD[] = {
    overworld_frame(gObjectEventPic_FollowerUnownD, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerUnownD, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerUnownD, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerUnownD, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerUnownD, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerUnownD, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_UnownE[] = {
    overworld_frame(gObjectEventPic_FollowerUnownE, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerUnownE, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerUnownE, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerUnownE, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerUnownE, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerUnownE, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_UnownF[] = {
    overworld_frame(gObjectEventPic_FollowerUnownF, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerUnownF, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerUnownF, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerUnownF, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerUnownF, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerUnownF, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_UnownG[] = {
    overworld_frame(gObjectEventPic_FollowerUnownG, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerUnownG, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerUnownG, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerUnownG, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerUnownG, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerUnownG, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_UnownH[] = {
    overworld_frame(gObjectEventPic_FollowerUnownH, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerUnownH, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerUnownH, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerUnownH, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerUnownH, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerUnownH, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_UnownI[] = {
    overworld_frame(gObjectEventPic_FollowerUnownI, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerUnownI, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerUnownI, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerUnownI, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerUnownI, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerUnownI, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_UnownJ[] = {
    overworld_frame(gObjectEventPic_FollowerUnownJ, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerUnownJ, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerUnownJ, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerUnownJ, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerUnownJ, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerUnownJ, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_UnownK[] = {
    overworld_frame(gObjectEventPic_FollowerUnownK, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerUnownK, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerUnownK, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerUnownK, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerUnownK, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerUnownK, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_UnownL[] = {
    overworld_frame(gObjectEventPic_FollowerUnownL, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerUnownL, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerUnownL, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerUnownL, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerUnownL, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerUnownL, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_UnownM[] = {
    overworld_frame(gObjectEventPic_FollowerUnownM, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerUnownM, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerUnownM, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerUnownM, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerUnownM, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerUnownM, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_UnownN[] = {
    overworld_frame(gObjectEventPic_FollowerUnownN, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerUnownN, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerUnownN, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerUnownN, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerUnownN, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerUnownN, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_UnownO[] = {
    overworld_frame(gObjectEventPic_FollowerUnownO, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerUnownO, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerUnownO, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerUnownO, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerUnownO, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerUnownO, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_UnownP[] = {
    overworld_frame(gObjectEventPic_FollowerUnownP, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerUnownP, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerUnownP, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerUnownP, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerUnownP, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerUnownP, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_UnownQ[] = {
    overworld_frame(gObjectEventPic_FollowerUnownQ, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerUnownQ, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerUnownQ, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerUnownQ, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerUnownQ, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerUnownQ, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_UnownR[] = {
    overworld_frame(gObjectEventPic_FollowerUnownR, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerUnownR, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerUnownR, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerUnownR, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerUnownR, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerUnownR, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_UnownS[] = {
    overworld_frame(gObjectEventPic_FollowerUnownS, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerUnownS, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerUnownS, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerUnownS, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerUnownS, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerUnownS, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_UnownT[] = {
    overworld_frame(gObjectEventPic_FollowerUnownT, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerUnownT, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerUnownT, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerUnownT, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerUnownT, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerUnownT, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_UnownU[] = {
    overworld_frame(gObjectEventPic_FollowerUnownU, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerUnownU, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerUnownU, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerUnownU, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerUnownU, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerUnownU, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_UnownV[] = {
    overworld_frame(gObjectEventPic_FollowerUnownV, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerUnownV, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerUnownV, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerUnownV, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerUnownV, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerUnownV, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_UnownW[] = {
    overworld_frame(gObjectEventPic_FollowerUnownW, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerUnownW, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerUnownW, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerUnownW, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerUnownW, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerUnownW, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_UnownX[] = {
    overworld_frame(gObjectEventPic_FollowerUnownX, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerUnownX, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerUnownX, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerUnownX, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerUnownX, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerUnownX, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_UnownY[] = {
    overworld_frame(gObjectEventPic_FollowerUnownY, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerUnownY, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerUnownY, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerUnownY, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerUnownY, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerUnownY, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_UnownZ[] = {
    overworld_frame(gObjectEventPic_FollowerUnownZ, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerUnownZ, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerUnownZ, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerUnownZ, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerUnownZ, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerUnownZ, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_UnownExclamation[] = {
    overworld_frame(gObjectEventPic_FollowerUnownExclamation, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerUnownExclamation, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerUnownExclamation, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerUnownExclamation, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerUnownExclamation, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerUnownExclamation, 4, 4, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_UnownQuestion[] = {
    overworld_frame(gObjectEventPic_FollowerUnownQuestion, 4, 4, 0),
    overworld_frame(gObjectEventPic_FollowerUnownQuestion, 4, 4, 1),
    overworld_frame(gObjectEventPic_FollowerUnownQuestion, 4, 4, 2),
    overworld_frame(gObjectEventPic_FollowerUnownQuestion, 4, 4, 3),
    overworld_frame(gObjectEventPic_FollowerUnownQuestion, 4, 4, 4),
    overworld_frame(gObjectEventPic_FollowerUnownQuestion, 4, 4, 5),
};

// Large follower pic tables (64x64 OBJ, 8x8 tile grid, 2048 bytes/frame).
#define large_frame(pic, n) overworld_frame(pic, 8, 8, n)
static const struct SpriteFrameImage sPicTable_Follower_Steelix[] = {
    large_frame(gObjectEventPic_FollowerSteelix, 0), large_frame(gObjectEventPic_FollowerSteelix, 1),
    large_frame(gObjectEventPic_FollowerSteelix, 2), large_frame(gObjectEventPic_FollowerSteelix, 3),
    large_frame(gObjectEventPic_FollowerSteelix, 4), large_frame(gObjectEventPic_FollowerSteelix, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Lugia[] = {
    large_frame(gObjectEventPic_FollowerLugia, 0), large_frame(gObjectEventPic_FollowerLugia, 1),
    large_frame(gObjectEventPic_FollowerLugia, 2), large_frame(gObjectEventPic_FollowerLugia, 3),
    large_frame(gObjectEventPic_FollowerLugia, 4), large_frame(gObjectEventPic_FollowerLugia, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_HoOh[] = {
    large_frame(gObjectEventPic_FollowerHoOh, 0), large_frame(gObjectEventPic_FollowerHoOh, 1),
    large_frame(gObjectEventPic_FollowerHoOh, 2), large_frame(gObjectEventPic_FollowerHoOh, 3),
    large_frame(gObjectEventPic_FollowerHoOh, 4), large_frame(gObjectEventPic_FollowerHoOh, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Wailord[] = {
    large_frame(gObjectEventPic_FollowerWailord, 0), large_frame(gObjectEventPic_FollowerWailord, 1),
    large_frame(gObjectEventPic_FollowerWailord, 2), large_frame(gObjectEventPic_FollowerWailord, 3),
    large_frame(gObjectEventPic_FollowerWailord, 4), large_frame(gObjectEventPic_FollowerWailord, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Kyogre[] = {
    large_frame(gObjectEventPic_FollowerKyogre, 0), large_frame(gObjectEventPic_FollowerKyogre, 1),
    large_frame(gObjectEventPic_FollowerKyogre, 2), large_frame(gObjectEventPic_FollowerKyogre, 3),
    large_frame(gObjectEventPic_FollowerKyogre, 4), large_frame(gObjectEventPic_FollowerKyogre, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Groudon[] = {
    large_frame(gObjectEventPic_FollowerGroudon, 0), large_frame(gObjectEventPic_FollowerGroudon, 1),
    large_frame(gObjectEventPic_FollowerGroudon, 2), large_frame(gObjectEventPic_FollowerGroudon, 3),
    large_frame(gObjectEventPic_FollowerGroudon, 4), large_frame(gObjectEventPic_FollowerGroudon, 5),
};
static const struct SpriteFrameImage sPicTable_Follower_Rayquaza[] = {
    large_frame(gObjectEventPic_FollowerRayquaza, 0), large_frame(gObjectEventPic_FollowerRayquaza, 1),
    large_frame(gObjectEventPic_FollowerRayquaza, 2), large_frame(gObjectEventPic_FollowerRayquaza, 3),
    large_frame(gObjectEventPic_FollowerRayquaza, 4), large_frame(gObjectEventPic_FollowerRayquaza, 5),
};
#undef large_frame

// Subsprite table for 64x64 followers (mirrors sOamTables_64x64 in object_event_subsprites.h).
// Defined locally so follower_pokemon.c doesn't depend on the static internals of event_object_movement.c.
// Subsprite y = -48 bakes in the 15px upward shift so y2 stays free for jump arcs.
// (sprite->y + sprite->y2 + subsprite->y + 64 = tile_center + 16, matching normal followers.)
static const struct Subsprite sFollowerLargeSubsprite_Bg[] = {{
    .x = -32, .y = -48, .shape = SPRITE_SHAPE(64x64), .size = SPRITE_SIZE(64x64), .tileOffset = 0, .priority = 2
}};
static const struct Subsprite sFollowerLargeSubsprite_Fg[] = {{
    .x = -32, .y = -48, .shape = SPRITE_SHAPE(64x64), .size = SPRITE_SIZE(64x64), .tileOffset = 0, .priority = 1
}};
static const struct SubspriteTable sOamTables_FollowerLarge[] = {
    {},
    {1, sFollowerLargeSubsprite_Bg},
    {1, sFollowerLargeSubsprite_Bg},
    {1, sFollowerLargeSubsprite_Fg},
    {1, sFollowerLargeSubsprite_Bg},
    {1, sFollowerLargeSubsprite_Bg},
};

static bool8 IsLargeFollowerSpecies(u16 species)
{
    switch (species)
    {
    case SPECIES_STEELIX:
    case SPECIES_LUGIA:
    case SPECIES_HO_OH:
    case SPECIES_WAILORD:
    case SPECIES_KYOGRE:
    case SPECIES_GROUDON:
    case SPECIES_RAYQUAZA:
        return TRUE;
    default:
        return FALSE;
    }
}

// Returns pal and picTable for a given species, or FALSE if unknown.
static bool8 GetFollowerSpriteInfo(u16 species,
                                    const u16 **palOut,
                                    const struct SpriteFrameImage **picOut)
{
    switch (species)
    {
    case SPECIES_BULBASAUR:
        *palOut = gObjectEventPal_FollowerBulbasaur;
        *picOut = sPicTable_Follower_Bulbasaur;
        return TRUE;
    case SPECIES_CHARMANDER:
        *palOut = gObjectEventPal_FollowerCharmander;
        *picOut = sPicTable_Follower_Charmander;
        return TRUE;
    case SPECIES_SQUIRTLE:
        *palOut = gObjectEventPal_FollowerSquirtle;
        *picOut = sPicTable_Follower_Squirtle;
        return TRUE;
    case SPECIES_CHIKORITA:
        *palOut = gObjectEventPal_FollowerChikorita;
        *picOut = sPicTable_Follower_Chikorita;
        return TRUE;
    case SPECIES_CYNDAQUIL:
        *palOut = gObjectEventPal_FollowerCyndaquil;
        *picOut = sPicTable_Follower_Cyndaquil;
        return TRUE;
    case SPECIES_TOTODILE:
        *palOut = gObjectEventPal_FollowerTotodile;
        *picOut = sPicTable_Follower_Totodile;
        return TRUE;
    case SPECIES_TREECKO:
        *palOut = gObjectEventPal_FollowerTreecko;
        *picOut = sPicTable_Follower_Treecko;
        return TRUE;
    case SPECIES_TORCHIC:
        *palOut = gObjectEventPal_FollowerTorchic;
        *picOut = sPicTable_Follower_Torchic;
        return TRUE;
    case SPECIES_MUDKIP:
        *palOut = gObjectEventPal_FollowerMudkip;
        *picOut = sPicTable_Follower_Mudkip;
        return TRUE;
    case SPECIES_IVYSAUR:
        *palOut = gObjectEventPal_FollowerIvysaur;
        *picOut = sPicTable_Follower_Ivysaur;
        return TRUE;
    case SPECIES_VENUSAUR:
        *palOut = gObjectEventPal_FollowerVenusaur;
        *picOut = sPicTable_Follower_Venusaur;
        return TRUE;
    case SPECIES_CHARMELEON:
        *palOut = gObjectEventPal_FollowerCharmeleon;
        *picOut = sPicTable_Follower_Charmeleon;
        return TRUE;
    case SPECIES_CHARIZARD:
        *palOut = gObjectEventPal_FollowerCharizard;
        *picOut = sPicTable_Follower_Charizard;
        return TRUE;
    case SPECIES_WARTORTLE:
        *palOut = gObjectEventPal_FollowerWartortle;
        *picOut = sPicTable_Follower_Wartortle;
        return TRUE;
    case SPECIES_BLASTOISE:
        *palOut = gObjectEventPal_FollowerBlastoise;
        *picOut = sPicTable_Follower_Blastoise;
        return TRUE;
    case SPECIES_CATERPIE:
        *palOut = gObjectEventPal_FollowerCaterpie;
        *picOut = sPicTable_Follower_Caterpie;
        return TRUE;
    case SPECIES_METAPOD:
        *palOut = gObjectEventPal_FollowerMetapod;
        *picOut = sPicTable_Follower_Metapod;
        return TRUE;
    case SPECIES_BUTTERFREE:
        *palOut = gObjectEventPal_FollowerButterfree;
        *picOut = sPicTable_Follower_Butterfree;
        return TRUE;
    case SPECIES_WEEDLE:
        *palOut = gObjectEventPal_FollowerWeedle;
        *picOut = sPicTable_Follower_Weedle;
        return TRUE;
    case SPECIES_KAKUNA:
        *palOut = gObjectEventPal_FollowerKakuna;
        *picOut = sPicTable_Follower_Kakuna;
        return TRUE;
    case SPECIES_BEEDRILL:
        *palOut = gObjectEventPal_FollowerBeedrill;
        *picOut = sPicTable_Follower_Beedrill;
        return TRUE;
    case SPECIES_PIDGEY:
        *palOut = gObjectEventPal_FollowerPidgey;
        *picOut = sPicTable_Follower_Pidgey;
        return TRUE;
    case SPECIES_PIDGEOTTO:
        *palOut = gObjectEventPal_FollowerPidgeotto;
        *picOut = sPicTable_Follower_Pidgeotto;
        return TRUE;
    case SPECIES_PIDGEOT:
        *palOut = gObjectEventPal_FollowerPidgeot;
        *picOut = sPicTable_Follower_Pidgeot;
        return TRUE;
    case SPECIES_RATTATA:
        *palOut = gObjectEventPal_FollowerRattata;
        *picOut = sPicTable_Follower_Rattata;
        return TRUE;
    case SPECIES_RATICATE:
        *palOut = gObjectEventPal_FollowerRaticate;
        *picOut = sPicTable_Follower_Raticate;
        return TRUE;
    case SPECIES_SPEAROW:
        *palOut = gObjectEventPal_FollowerSpearow;
        *picOut = sPicTable_Follower_Spearow;
        return TRUE;
    case SPECIES_FEAROW:
        *palOut = gObjectEventPal_FollowerFearow;
        *picOut = sPicTable_Follower_Fearow;
        return TRUE;
    case SPECIES_EKANS:
        *palOut = gObjectEventPal_FollowerEkans;
        *picOut = sPicTable_Follower_Ekans;
        return TRUE;
    case SPECIES_ARBOK:
        *palOut = gObjectEventPal_FollowerArbok;
        *picOut = sPicTable_Follower_Arbok;
        return TRUE;
    case SPECIES_PIKACHU:
        *palOut = gObjectEventPal_FollowerPikachu;
        *picOut = sPicTable_Follower_Pikachu;
        return TRUE;
    case SPECIES_RAICHU:
        *palOut = gObjectEventPal_FollowerRaichu;
        *picOut = sPicTable_Follower_Raichu;
        return TRUE;
    case SPECIES_SANDSHREW:
        *palOut = gObjectEventPal_FollowerSandshrew;
        *picOut = sPicTable_Follower_Sandshrew;
        return TRUE;
    case SPECIES_SANDSLASH:
        *palOut = gObjectEventPal_FollowerSandslash;
        *picOut = sPicTable_Follower_Sandslash;
        return TRUE;
    case SPECIES_NIDORAN_F:
        *palOut = gObjectEventPal_FollowerNidoranF;
        *picOut = sPicTable_Follower_NidoranF;
        return TRUE;
    case SPECIES_NIDORINA:
        *palOut = gObjectEventPal_FollowerNidorina;
        *picOut = sPicTable_Follower_Nidorina;
        return TRUE;
    case SPECIES_NIDOQUEEN:
        *palOut = gObjectEventPal_FollowerNidoqueen;
        *picOut = sPicTable_Follower_Nidoqueen;
        return TRUE;
    case SPECIES_NIDORAN_M:
        *palOut = gObjectEventPal_FollowerNidoranM;
        *picOut = sPicTable_Follower_NidoranM;
        return TRUE;
    case SPECIES_NIDORINO:
        *palOut = gObjectEventPal_FollowerNidorino;
        *picOut = sPicTable_Follower_Nidorino;
        return TRUE;
    case SPECIES_NIDOKING:
        *palOut = gObjectEventPal_FollowerNidoking;
        *picOut = sPicTable_Follower_Nidoking;
        return TRUE;
    case SPECIES_CLEFAIRY:
        *palOut = gObjectEventPal_FollowerClefairy;
        *picOut = sPicTable_Follower_Clefairy;
        return TRUE;
    case SPECIES_CLEFABLE:
        *palOut = gObjectEventPal_FollowerClefable;
        *picOut = sPicTable_Follower_Clefable;
        return TRUE;
    case SPECIES_VULPIX:
        *palOut = gObjectEventPal_FollowerVulpix;
        *picOut = sPicTable_Follower_Vulpix;
        return TRUE;
    case SPECIES_NINETALES:
        *palOut = gObjectEventPal_FollowerNinetales;
        *picOut = sPicTable_Follower_Ninetales;
        return TRUE;
    case SPECIES_JIGGLYPUFF:
        *palOut = gObjectEventPal_FollowerJigglypuff;
        *picOut = sPicTable_Follower_Jigglypuff;
        return TRUE;
    case SPECIES_WIGGLYTUFF:
        *palOut = gObjectEventPal_FollowerWigglytuff;
        *picOut = sPicTable_Follower_Wigglytuff;
        return TRUE;
    case SPECIES_ZUBAT:
        *palOut = gObjectEventPal_FollowerZubat;
        *picOut = sPicTable_Follower_Zubat;
        return TRUE;
    case SPECIES_GOLBAT:
        *palOut = gObjectEventPal_FollowerGolbat;
        *picOut = sPicTable_Follower_Golbat;
        return TRUE;
    case SPECIES_ODDISH:
        *palOut = gObjectEventPal_FollowerOddish;
        *picOut = sPicTable_Follower_Oddish;
        return TRUE;
    case SPECIES_GLOOM:
        *palOut = gObjectEventPal_FollowerGloom;
        *picOut = sPicTable_Follower_Gloom;
        return TRUE;
    case SPECIES_VILEPLUME:
        *palOut = gObjectEventPal_FollowerVileplume;
        *picOut = sPicTable_Follower_Vileplume;
        return TRUE;
    case SPECIES_PARAS:
        *palOut = gObjectEventPal_FollowerParas;
        *picOut = sPicTable_Follower_Paras;
        return TRUE;
    case SPECIES_PARASECT:
        *palOut = gObjectEventPal_FollowerParasect;
        *picOut = sPicTable_Follower_Parasect;
        return TRUE;
    case SPECIES_VENONAT:
        *palOut = gObjectEventPal_FollowerVenonat;
        *picOut = sPicTable_Follower_Venonat;
        return TRUE;
    case SPECIES_VENOMOTH:
        *palOut = gObjectEventPal_FollowerVenomoth;
        *picOut = sPicTable_Follower_Venomoth;
        return TRUE;
    case SPECIES_DIGLETT:
        *palOut = gObjectEventPal_FollowerDiglett;
        *picOut = sPicTable_Follower_Diglett;
        return TRUE;
    case SPECIES_DUGTRIO:
        *palOut = gObjectEventPal_FollowerDugtrio;
        *picOut = sPicTable_Follower_Dugtrio;
        return TRUE;
    case SPECIES_MEOWTH:
        *palOut = gObjectEventPal_FollowerMeowth;
        *picOut = sPicTable_Follower_Meowth;
        return TRUE;
    case SPECIES_PERSIAN:
        *palOut = gObjectEventPal_FollowerPersian;
        *picOut = sPicTable_Follower_Persian;
        return TRUE;
    case SPECIES_PSYDUCK:
        *palOut = gObjectEventPal_FollowerPsyduck;
        *picOut = sPicTable_Follower_Psyduck;
        return TRUE;
    case SPECIES_GOLDUCK:
        *palOut = gObjectEventPal_FollowerGolduck;
        *picOut = sPicTable_Follower_Golduck;
        return TRUE;
    case SPECIES_MANKEY:
        *palOut = gObjectEventPal_FollowerMankey;
        *picOut = sPicTable_Follower_Mankey;
        return TRUE;
    case SPECIES_PRIMEAPE:
        *palOut = gObjectEventPal_FollowerPrimeape;
        *picOut = sPicTable_Follower_Primeape;
        return TRUE;
    case SPECIES_GROWLITHE:
        *palOut = gObjectEventPal_FollowerGrowlithe;
        *picOut = sPicTable_Follower_Growlithe;
        return TRUE;
    case SPECIES_ARCANINE:
        *palOut = gObjectEventPal_FollowerArcanine;
        *picOut = sPicTable_Follower_Arcanine;
        return TRUE;
    case SPECIES_POLIWAG:
        *palOut = gObjectEventPal_FollowerPoliwag;
        *picOut = sPicTable_Follower_Poliwag;
        return TRUE;
    case SPECIES_POLIWHIRL:
        *palOut = gObjectEventPal_FollowerPoliwhirl;
        *picOut = sPicTable_Follower_Poliwhirl;
        return TRUE;
    case SPECIES_POLIWRATH:
        *palOut = gObjectEventPal_FollowerPoliwrath;
        *picOut = sPicTable_Follower_Poliwrath;
        return TRUE;
    case SPECIES_ABRA:
        *palOut = gObjectEventPal_FollowerAbra;
        *picOut = sPicTable_Follower_Abra;
        return TRUE;
    case SPECIES_KADABRA:
        *palOut = gObjectEventPal_FollowerKadabra;
        *picOut = sPicTable_Follower_Kadabra;
        return TRUE;
    case SPECIES_ALAKAZAM:
        *palOut = gObjectEventPal_FollowerAlakazam;
        *picOut = sPicTable_Follower_Alakazam;
        return TRUE;
    case SPECIES_MACHOP:
        *palOut = gObjectEventPal_FollowerMachop;
        *picOut = sPicTable_Follower_Machop;
        return TRUE;
    case SPECIES_MACHOKE:
        *palOut = gObjectEventPal_FollowerMachoke;
        *picOut = sPicTable_Follower_Machoke;
        return TRUE;
    case SPECIES_MACHAMP:
        *palOut = gObjectEventPal_FollowerMachamp;
        *picOut = sPicTable_Follower_Machamp;
        return TRUE;
    case SPECIES_BELLSPROUT:
        *palOut = gObjectEventPal_FollowerBellsprout;
        *picOut = sPicTable_Follower_Bellsprout;
        return TRUE;
    case SPECIES_WEEPINBELL:
        *palOut = gObjectEventPal_FollowerWeepinbell;
        *picOut = sPicTable_Follower_Weepinbell;
        return TRUE;
    case SPECIES_VICTREEBEL:
        *palOut = gObjectEventPal_FollowerVictreebel;
        *picOut = sPicTable_Follower_Victreebel;
        return TRUE;
    case SPECIES_TENTACOOL:
        *palOut = gObjectEventPal_FollowerTentacool;
        *picOut = sPicTable_Follower_Tentacool;
        return TRUE;
    case SPECIES_TENTACRUEL:
        *palOut = gObjectEventPal_FollowerTentacruel;
        *picOut = sPicTable_Follower_Tentacruel;
        return TRUE;
    case SPECIES_GEODUDE:
        *palOut = gObjectEventPal_FollowerGeodude;
        *picOut = sPicTable_Follower_Geodude;
        return TRUE;
    case SPECIES_GRAVELER:
        *palOut = gObjectEventPal_FollowerGraveler;
        *picOut = sPicTable_Follower_Graveler;
        return TRUE;
    case SPECIES_GOLEM:
        *palOut = gObjectEventPal_FollowerGolem;
        *picOut = sPicTable_Follower_Golem;
        return TRUE;
    case SPECIES_PONYTA:
        *palOut = gObjectEventPal_FollowerPonyta;
        *picOut = sPicTable_Follower_Ponyta;
        return TRUE;
    case SPECIES_RAPIDASH:
        *palOut = gObjectEventPal_FollowerRapidash;
        *picOut = sPicTable_Follower_Rapidash;
        return TRUE;
    case SPECIES_SLOWPOKE:
        *palOut = gObjectEventPal_FollowerSlowpoke;
        *picOut = sPicTable_Follower_Slowpoke;
        return TRUE;
    case SPECIES_SLOWBRO:
        *palOut = gObjectEventPal_FollowerSlowbro;
        *picOut = sPicTable_Follower_Slowbro;
        return TRUE;
    case SPECIES_MAGNEMITE:
        *palOut = gObjectEventPal_FollowerMagnemite;
        *picOut = sPicTable_Follower_Magnemite;
        return TRUE;
    case SPECIES_MAGNETON:
        *palOut = gObjectEventPal_FollowerMagneton;
        *picOut = sPicTable_Follower_Magneton;
        return TRUE;
    case SPECIES_FARFETCHD:
        *palOut = gObjectEventPal_FollowerFarfetchd;
        *picOut = sPicTable_Follower_Farfetchd;
        return TRUE;
    case SPECIES_DODUO:
        *palOut = gObjectEventPal_FollowerDoduo;
        *picOut = sPicTable_Follower_Doduo;
        return TRUE;
    case SPECIES_DODRIO:
        *palOut = gObjectEventPal_FollowerDodrio;
        *picOut = sPicTable_Follower_Dodrio;
        return TRUE;
    case SPECIES_SEEL:
        *palOut = gObjectEventPal_FollowerSeel;
        *picOut = sPicTable_Follower_Seel;
        return TRUE;
    case SPECIES_DEWGONG:
        *palOut = gObjectEventPal_FollowerDewgong;
        *picOut = sPicTable_Follower_Dewgong;
        return TRUE;
    case SPECIES_GRIMER:
        *palOut = gObjectEventPal_FollowerGrimer;
        *picOut = sPicTable_Follower_Grimer;
        return TRUE;
    case SPECIES_MUK:
        *palOut = gObjectEventPal_FollowerMuk;
        *picOut = sPicTable_Follower_Muk;
        return TRUE;
    case SPECIES_SHELLDER:
        *palOut = gObjectEventPal_FollowerShellder;
        *picOut = sPicTable_Follower_Shellder;
        return TRUE;
    case SPECIES_CLOYSTER:
        *palOut = gObjectEventPal_FollowerCloyster;
        *picOut = sPicTable_Follower_Cloyster;
        return TRUE;
    case SPECIES_GASTLY:
        *palOut = gObjectEventPal_FollowerGastly;
        *picOut = sPicTable_Follower_Gastly;
        return TRUE;
    case SPECIES_HAUNTER:
        *palOut = gObjectEventPal_FollowerHaunter;
        *picOut = sPicTable_Follower_Haunter;
        return TRUE;
    case SPECIES_GENGAR:
        *palOut = gObjectEventPal_FollowerGengar;
        *picOut = sPicTable_Follower_Gengar;
        return TRUE;
    case SPECIES_ONIX:
        *palOut = gObjectEventPal_FollowerOnix;
        *picOut = sPicTable_Follower_Onix;
        return TRUE;
    case SPECIES_DROWZEE:
        *palOut = gObjectEventPal_FollowerDrowzee;
        *picOut = sPicTable_Follower_Drowzee;
        return TRUE;
    case SPECIES_HYPNO:
        *palOut = gObjectEventPal_FollowerHypno;
        *picOut = sPicTable_Follower_Hypno;
        return TRUE;
    case SPECIES_KRABBY:
        *palOut = gObjectEventPal_FollowerKrabby;
        *picOut = sPicTable_Follower_Krabby;
        return TRUE;
    case SPECIES_KINGLER:
        *palOut = gObjectEventPal_FollowerKingler;
        *picOut = sPicTable_Follower_Kingler;
        return TRUE;
    case SPECIES_VOLTORB:
        *palOut = gObjectEventPal_FollowerVoltorb;
        *picOut = sPicTable_Follower_Voltorb;
        return TRUE;
    case SPECIES_ELECTRODE:
        *palOut = gObjectEventPal_FollowerElectrode;
        *picOut = sPicTable_Follower_Electrode;
        return TRUE;
    case SPECIES_EXEGGCUTE:
        *palOut = gObjectEventPal_FollowerExeggcute;
        *picOut = sPicTable_Follower_Exeggcute;
        return TRUE;
    case SPECIES_EXEGGUTOR:
        *palOut = gObjectEventPal_FollowerExeggutor;
        *picOut = sPicTable_Follower_Exeggutor;
        return TRUE;
    case SPECIES_CUBONE:
        *palOut = gObjectEventPal_FollowerCubone;
        *picOut = sPicTable_Follower_Cubone;
        return TRUE;
    case SPECIES_MAROWAK:
        *palOut = gObjectEventPal_FollowerMarowak;
        *picOut = sPicTable_Follower_Marowak;
        return TRUE;
    case SPECIES_HITMONLEE:
        *palOut = gObjectEventPal_FollowerHitmonlee;
        *picOut = sPicTable_Follower_Hitmonlee;
        return TRUE;
    case SPECIES_HITMONCHAN:
        *palOut = gObjectEventPal_FollowerHitmonchan;
        *picOut = sPicTable_Follower_Hitmonchan;
        return TRUE;
    case SPECIES_LICKITUNG:
        *palOut = gObjectEventPal_FollowerLickitung;
        *picOut = sPicTable_Follower_Lickitung;
        return TRUE;
    case SPECIES_KOFFING:
        *palOut = gObjectEventPal_FollowerKoffing;
        *picOut = sPicTable_Follower_Koffing;
        return TRUE;
    case SPECIES_WEEZING:
        *palOut = gObjectEventPal_FollowerWeezing;
        *picOut = sPicTable_Follower_Weezing;
        return TRUE;
    case SPECIES_RHYHORN:
        *palOut = gObjectEventPal_FollowerRhyhorn;
        *picOut = sPicTable_Follower_Rhyhorn;
        return TRUE;
    case SPECIES_RHYDON:
        *palOut = gObjectEventPal_FollowerRhydon;
        *picOut = sPicTable_Follower_Rhydon;
        return TRUE;
    case SPECIES_CHANSEY:
        *palOut = gObjectEventPal_FollowerChansey;
        *picOut = sPicTable_Follower_Chansey;
        return TRUE;
    case SPECIES_TANGELA:
        *palOut = gObjectEventPal_FollowerTangela;
        *picOut = sPicTable_Follower_Tangela;
        return TRUE;
    case SPECIES_KANGASKHAN:
        *palOut = gObjectEventPal_FollowerKangaskhan;
        *picOut = sPicTable_Follower_Kangaskhan;
        return TRUE;
    case SPECIES_HORSEA:
        *palOut = gObjectEventPal_FollowerHorsea;
        *picOut = sPicTable_Follower_Horsea;
        return TRUE;
    case SPECIES_SEADRA:
        *palOut = gObjectEventPal_FollowerSeadra;
        *picOut = sPicTable_Follower_Seadra;
        return TRUE;
    case SPECIES_GOLDEEN:
        *palOut = gObjectEventPal_FollowerGoldeen;
        *picOut = sPicTable_Follower_Goldeen;
        return TRUE;
    case SPECIES_SEAKING:
        *palOut = gObjectEventPal_FollowerSeaking;
        *picOut = sPicTable_Follower_Seaking;
        return TRUE;
    case SPECIES_STARYU:
        *palOut = gObjectEventPal_FollowerStaryu;
        *picOut = sPicTable_Follower_Staryu;
        return TRUE;
    case SPECIES_STARMIE:
        *palOut = gObjectEventPal_FollowerStarmie;
        *picOut = sPicTable_Follower_Starmie;
        return TRUE;
    case SPECIES_MR_MIME:
        *palOut = gObjectEventPal_FollowerMrMime;
        *picOut = sPicTable_Follower_MrMime;
        return TRUE;
    case SPECIES_SCYTHER:
        *palOut = gObjectEventPal_FollowerScyther;
        *picOut = sPicTable_Follower_Scyther;
        return TRUE;
    case SPECIES_JYNX:
        *palOut = gObjectEventPal_FollowerJynx;
        *picOut = sPicTable_Follower_Jynx;
        return TRUE;
    case SPECIES_ELECTABUZZ:
        *palOut = gObjectEventPal_FollowerElectabuzz;
        *picOut = sPicTable_Follower_Electabuzz;
        return TRUE;
    case SPECIES_MAGMAR:
        *palOut = gObjectEventPal_FollowerMagmar;
        *picOut = sPicTable_Follower_Magmar;
        return TRUE;
    case SPECIES_PINSIR:
        *palOut = gObjectEventPal_FollowerPinsir;
        *picOut = sPicTable_Follower_Pinsir;
        return TRUE;
    case SPECIES_TAUROS:
        *palOut = gObjectEventPal_FollowerTauros;
        *picOut = sPicTable_Follower_Tauros;
        return TRUE;
    case SPECIES_MAGIKARP:
        *palOut = gObjectEventPal_FollowerMagikarp;
        *picOut = sPicTable_Follower_Magikarp;
        return TRUE;
    case SPECIES_GYARADOS:
        *palOut = gObjectEventPal_FollowerGyarados;
        *picOut = sPicTable_Follower_Gyarados;
        return TRUE;
    case SPECIES_LAPRAS:
        *palOut = gObjectEventPal_FollowerLapras;
        *picOut = sPicTable_Follower_Lapras;
        return TRUE;
    case SPECIES_DITTO:
        *palOut = gObjectEventPal_FollowerDitto;
        *picOut = sPicTable_Follower_Ditto;
        return TRUE;
    case SPECIES_EEVEE:
        *palOut = gObjectEventPal_FollowerEevee;
        *picOut = sPicTable_Follower_Eevee;
        return TRUE;
    case SPECIES_VAPOREON:
        *palOut = gObjectEventPal_FollowerVaporeon;
        *picOut = sPicTable_Follower_Vaporeon;
        return TRUE;
    case SPECIES_JOLTEON:
        *palOut = gObjectEventPal_FollowerJolteon;
        *picOut = sPicTable_Follower_Jolteon;
        return TRUE;
    case SPECIES_FLAREON:
        *palOut = gObjectEventPal_FollowerFlareon;
        *picOut = sPicTable_Follower_Flareon;
        return TRUE;
    case SPECIES_PORYGON:
        *palOut = gObjectEventPal_FollowerPorygon;
        *picOut = sPicTable_Follower_Porygon;
        return TRUE;
    case SPECIES_OMANYTE:
        *palOut = gObjectEventPal_FollowerOmanyte;
        *picOut = sPicTable_Follower_Omanyte;
        return TRUE;
    case SPECIES_OMASTAR:
        *palOut = gObjectEventPal_FollowerOmastar;
        *picOut = sPicTable_Follower_Omastar;
        return TRUE;
    case SPECIES_KABUTO:
        *palOut = gObjectEventPal_FollowerKabuto;
        *picOut = sPicTable_Follower_Kabuto;
        return TRUE;
    case SPECIES_KABUTOPS:
        *palOut = gObjectEventPal_FollowerKabutops;
        *picOut = sPicTable_Follower_Kabutops;
        return TRUE;
    case SPECIES_AERODACTYL:
        *palOut = gObjectEventPal_FollowerAerodactyl;
        *picOut = sPicTable_Follower_Aerodactyl;
        return TRUE;
    case SPECIES_SNORLAX:
        *palOut = gObjectEventPal_FollowerSnorlax;
        *picOut = sPicTable_Follower_Snorlax;
        return TRUE;
    case SPECIES_ARTICUNO:
        *palOut = gObjectEventPal_FollowerArticuno;
        *picOut = sPicTable_Follower_Articuno;
        return TRUE;
    case SPECIES_ZAPDOS:
        *palOut = gObjectEventPal_FollowerZapdos;
        *picOut = sPicTable_Follower_Zapdos;
        return TRUE;
    case SPECIES_MOLTRES:
        *palOut = gObjectEventPal_FollowerMoltres;
        *picOut = sPicTable_Follower_Moltres;
        return TRUE;
    case SPECIES_DRATINI:
        *palOut = gObjectEventPal_FollowerDratini;
        *picOut = sPicTable_Follower_Dratini;
        return TRUE;
    case SPECIES_DRAGONAIR:
        *palOut = gObjectEventPal_FollowerDragonair;
        *picOut = sPicTable_Follower_Dragonair;
        return TRUE;
    case SPECIES_DRAGONITE:
        *palOut = gObjectEventPal_FollowerDragonite;
        *picOut = sPicTable_Follower_Dragonite;
        return TRUE;
    case SPECIES_MEWTWO:
        *palOut = gObjectEventPal_FollowerMewtwo;
        *picOut = sPicTable_Follower_Mewtwo;
        return TRUE;
    case SPECIES_MEW:
        *palOut = gObjectEventPal_FollowerMew;
        *picOut = sPicTable_Follower_Mew;
        return TRUE;
    case SPECIES_BAYLEEF:
        *palOut = gObjectEventPal_FollowerBayleef;
        *picOut = sPicTable_Follower_Bayleef;
        return TRUE;
    case SPECIES_MEGANIUM:
        *palOut = gObjectEventPal_FollowerMeganium;
        *picOut = sPicTable_Follower_Meganium;
        return TRUE;
    case SPECIES_QUILAVA:
        *palOut = gObjectEventPal_FollowerQuilava;
        *picOut = sPicTable_Follower_Quilava;
        return TRUE;
    case SPECIES_TYPHLOSION:
        *palOut = gObjectEventPal_FollowerTyphlosion;
        *picOut = sPicTable_Follower_Typhlosion;
        return TRUE;
    case SPECIES_CROCONAW:
        *palOut = gObjectEventPal_FollowerCroconaw;
        *picOut = sPicTable_Follower_Croconaw;
        return TRUE;
    case SPECIES_FERALIGATR:
        *palOut = gObjectEventPal_FollowerFeraligatr;
        *picOut = sPicTable_Follower_Feraligatr;
        return TRUE;
    case SPECIES_SENTRET:
        *palOut = gObjectEventPal_FollowerSentret;
        *picOut = sPicTable_Follower_Sentret;
        return TRUE;
    case SPECIES_FURRET:
        *palOut = gObjectEventPal_FollowerFurret;
        *picOut = sPicTable_Follower_Furret;
        return TRUE;
    case SPECIES_HOOTHOOT:
        *palOut = gObjectEventPal_FollowerHoothoot;
        *picOut = sPicTable_Follower_Hoothoot;
        return TRUE;
    case SPECIES_NOCTOWL:
        *palOut = gObjectEventPal_FollowerNoctowl;
        *picOut = sPicTable_Follower_Noctowl;
        return TRUE;
    case SPECIES_LEDYBA:
        *palOut = gObjectEventPal_FollowerLedyba;
        *picOut = sPicTable_Follower_Ledyba;
        return TRUE;
    case SPECIES_LEDIAN:
        *palOut = gObjectEventPal_FollowerLedian;
        *picOut = sPicTable_Follower_Ledian;
        return TRUE;
    case SPECIES_SPINARAK:
        *palOut = gObjectEventPal_FollowerSpinarak;
        *picOut = sPicTable_Follower_Spinarak;
        return TRUE;
    case SPECIES_ARIADOS:
        *palOut = gObjectEventPal_FollowerAriados;
        *picOut = sPicTable_Follower_Ariados;
        return TRUE;
    case SPECIES_CROBAT:
        *palOut = gObjectEventPal_FollowerCrobat;
        *picOut = sPicTable_Follower_Crobat;
        return TRUE;
    case SPECIES_CHINCHOU:
        *palOut = gObjectEventPal_FollowerChinchou;
        *picOut = sPicTable_Follower_Chinchou;
        return TRUE;
    case SPECIES_LANTURN:
        *palOut = gObjectEventPal_FollowerLanturn;
        *picOut = sPicTable_Follower_Lanturn;
        return TRUE;
    case SPECIES_PICHU:
        *palOut = gObjectEventPal_FollowerPichu;
        *picOut = sPicTable_Follower_Pichu;
        return TRUE;
    case SPECIES_CLEFFA:
        *palOut = gObjectEventPal_FollowerCleffa;
        *picOut = sPicTable_Follower_Cleffa;
        return TRUE;
    case SPECIES_IGGLYBUFF:
        *palOut = gObjectEventPal_FollowerIgglybuff;
        *picOut = sPicTable_Follower_Igglybuff;
        return TRUE;
    case SPECIES_TOGEPI:
        *palOut = gObjectEventPal_FollowerTogepi;
        *picOut = sPicTable_Follower_Togepi;
        return TRUE;
    case SPECIES_TOGETIC:
        *palOut = gObjectEventPal_FollowerTogetic;
        *picOut = sPicTable_Follower_Togetic;
        return TRUE;
    case SPECIES_NATU:
        *palOut = gObjectEventPal_FollowerNatu;
        *picOut = sPicTable_Follower_Natu;
        return TRUE;
    case SPECIES_XATU:
        *palOut = gObjectEventPal_FollowerXatu;
        *picOut = sPicTable_Follower_Xatu;
        return TRUE;
    case SPECIES_MAREEP:
        *palOut = gObjectEventPal_FollowerMareep;
        *picOut = sPicTable_Follower_Mareep;
        return TRUE;
    case SPECIES_FLAAFFY:
        *palOut = gObjectEventPal_FollowerFlaaffy;
        *picOut = sPicTable_Follower_Flaaffy;
        return TRUE;
    case SPECIES_AMPHAROS:
        *palOut = gObjectEventPal_FollowerAmpharos;
        *picOut = sPicTable_Follower_Ampharos;
        return TRUE;
    case SPECIES_BELLOSSOM:
        *palOut = gObjectEventPal_FollowerBellossom;
        *picOut = sPicTable_Follower_Bellossom;
        return TRUE;
    case SPECIES_MARILL:
        *palOut = gObjectEventPal_FollowerMarill;
        *picOut = sPicTable_Follower_Marill;
        return TRUE;
    case SPECIES_AZUMARILL:
        *palOut = gObjectEventPal_FollowerAzumarill;
        *picOut = sPicTable_Follower_Azumarill;
        return TRUE;
    case SPECIES_SUDOWOODO:
        *palOut = gObjectEventPal_FollowerSudowoodo;
        *picOut = sPicTable_Follower_Sudowoodo;
        return TRUE;
    case SPECIES_POLITOED:
        *palOut = gObjectEventPal_FollowerPolitoed;
        *picOut = sPicTable_Follower_Politoed;
        return TRUE;
    case SPECIES_HOPPIP:
        *palOut = gObjectEventPal_FollowerHoppip;
        *picOut = sPicTable_Follower_Hoppip;
        return TRUE;
    case SPECIES_SKIPLOOM:
        *palOut = gObjectEventPal_FollowerSkiploom;
        *picOut = sPicTable_Follower_Skiploom;
        return TRUE;
    case SPECIES_JUMPLUFF:
        *palOut = gObjectEventPal_FollowerJumpluff;
        *picOut = sPicTable_Follower_Jumpluff;
        return TRUE;
    case SPECIES_AIPOM:
        *palOut = gObjectEventPal_FollowerAipom;
        *picOut = sPicTable_Follower_Aipom;
        return TRUE;
    case SPECIES_SUNKERN:
        *palOut = gObjectEventPal_FollowerSunkern;
        *picOut = sPicTable_Follower_Sunkern;
        return TRUE;
    case SPECIES_SUNFLORA:
        *palOut = gObjectEventPal_FollowerSunflora;
        *picOut = sPicTable_Follower_Sunflora;
        return TRUE;
    case SPECIES_YANMA:
        *palOut = gObjectEventPal_FollowerYanma;
        *picOut = sPicTable_Follower_Yanma;
        return TRUE;
    case SPECIES_WOOPER:
        *palOut = gObjectEventPal_FollowerWooper;
        *picOut = sPicTable_Follower_Wooper;
        return TRUE;
    case SPECIES_QUAGSIRE:
        *palOut = gObjectEventPal_FollowerQuagsire;
        *picOut = sPicTable_Follower_Quagsire;
        return TRUE;
    case SPECIES_ESPEON:
        *palOut = gObjectEventPal_FollowerEspeon;
        *picOut = sPicTable_Follower_Espeon;
        return TRUE;
    case SPECIES_UMBREON:
        *palOut = gObjectEventPal_FollowerUmbreon;
        *picOut = sPicTable_Follower_Umbreon;
        return TRUE;
    case SPECIES_MURKROW:
        *palOut = gObjectEventPal_FollowerMurkrow;
        *picOut = sPicTable_Follower_Murkrow;
        return TRUE;
    case SPECIES_SLOWKING:
        *palOut = gObjectEventPal_FollowerSlowking;
        *picOut = sPicTable_Follower_Slowking;
        return TRUE;
    case SPECIES_MISDREAVUS:
        *palOut = gObjectEventPal_FollowerMisdreavus;
        *picOut = sPicTable_Follower_Misdreavus;
        return TRUE;
    case SPECIES_WOBBUFFET:
        *palOut = gObjectEventPal_FollowerWobbuffet;
        *picOut = sPicTable_Follower_Wobbuffet;
        return TRUE;
    case SPECIES_GIRAFARIG:
        *palOut = gObjectEventPal_FollowerGirafarig;
        *picOut = sPicTable_Follower_Girafarig;
        return TRUE;
    case SPECIES_PINECO:
        *palOut = gObjectEventPal_FollowerPineco;
        *picOut = sPicTable_Follower_Pineco;
        return TRUE;
    case SPECIES_FORRETRESS:
        *palOut = gObjectEventPal_FollowerForretress;
        *picOut = sPicTable_Follower_Forretress;
        return TRUE;
    case SPECIES_DUNSPARCE:
        *palOut = gObjectEventPal_FollowerDunsparce;
        *picOut = sPicTable_Follower_Dunsparce;
        return TRUE;
    case SPECIES_GLIGAR:
        *palOut = gObjectEventPal_FollowerGligar;
        *picOut = sPicTable_Follower_Gligar;
        return TRUE;
    case SPECIES_SNUBBULL:
        *palOut = gObjectEventPal_FollowerSnubbull;
        *picOut = sPicTable_Follower_Snubbull;
        return TRUE;
    case SPECIES_GRANBULL:
        *palOut = gObjectEventPal_FollowerGranbull;
        *picOut = sPicTable_Follower_Granbull;
        return TRUE;
    case SPECIES_QWILFISH:
        *palOut = gObjectEventPal_FollowerQwilfish;
        *picOut = sPicTable_Follower_Qwilfish;
        return TRUE;
    case SPECIES_SCIZOR:
        *palOut = gObjectEventPal_FollowerScizor;
        *picOut = sPicTable_Follower_Scizor;
        return TRUE;
    case SPECIES_SHUCKLE:
        *palOut = gObjectEventPal_FollowerShuckle;
        *picOut = sPicTable_Follower_Shuckle;
        return TRUE;
    case SPECIES_HERACROSS:
        *palOut = gObjectEventPal_FollowerHeracross;
        *picOut = sPicTable_Follower_Heracross;
        return TRUE;
    case SPECIES_SNEASEL:
        *palOut = gObjectEventPal_FollowerSneasel;
        *picOut = sPicTable_Follower_Sneasel;
        return TRUE;
    case SPECIES_TEDDIURSA:
        *palOut = gObjectEventPal_FollowerTeddiursa;
        *picOut = sPicTable_Follower_Teddiursa;
        return TRUE;
    case SPECIES_URSARING:
        *palOut = gObjectEventPal_FollowerUrsaring;
        *picOut = sPicTable_Follower_Ursaring;
        return TRUE;
    case SPECIES_SLUGMA:
        *palOut = gObjectEventPal_FollowerSlugma;
        *picOut = sPicTable_Follower_Slugma;
        return TRUE;
    case SPECIES_MAGCARGO:
        *palOut = gObjectEventPal_FollowerMagcargo;
        *picOut = sPicTable_Follower_Magcargo;
        return TRUE;
    case SPECIES_SWINUB:
        *palOut = gObjectEventPal_FollowerSwinub;
        *picOut = sPicTable_Follower_Swinub;
        return TRUE;
    case SPECIES_PILOSWINE:
        *palOut = gObjectEventPal_FollowerPiloswine;
        *picOut = sPicTable_Follower_Piloswine;
        return TRUE;
    case SPECIES_CORSOLA:
        *palOut = gObjectEventPal_FollowerCorsola;
        *picOut = sPicTable_Follower_Corsola;
        return TRUE;
    case SPECIES_REMORAID:
        *palOut = gObjectEventPal_FollowerRemoraid;
        *picOut = sPicTable_Follower_Remoraid;
        return TRUE;
    case SPECIES_OCTILLERY:
        *palOut = gObjectEventPal_FollowerOctillery;
        *picOut = sPicTable_Follower_Octillery;
        return TRUE;
    case SPECIES_DELIBIRD:
        *palOut = gObjectEventPal_FollowerDelibird;
        *picOut = sPicTable_Follower_Delibird;
        return TRUE;
    case SPECIES_MANTINE:
        *palOut = gObjectEventPal_FollowerMantine;
        *picOut = sPicTable_Follower_Mantine;
        return TRUE;
    case SPECIES_SKARMORY:
        *palOut = gObjectEventPal_FollowerSkarmory;
        *picOut = sPicTable_Follower_Skarmory;
        return TRUE;
    case SPECIES_HOUNDOUR:
        *palOut = gObjectEventPal_FollowerHoundour;
        *picOut = sPicTable_Follower_Houndour;
        return TRUE;
    case SPECIES_HOUNDOOM:
        *palOut = gObjectEventPal_FollowerHoundoom;
        *picOut = sPicTable_Follower_Houndoom;
        return TRUE;
    case SPECIES_KINGDRA:
        *palOut = gObjectEventPal_FollowerKingdra;
        *picOut = sPicTable_Follower_Kingdra;
        return TRUE;
    case SPECIES_PHANPY:
        *palOut = gObjectEventPal_FollowerPhanpy;
        *picOut = sPicTable_Follower_Phanpy;
        return TRUE;
    case SPECIES_DONPHAN:
        *palOut = gObjectEventPal_FollowerDonphan;
        *picOut = sPicTable_Follower_Donphan;
        return TRUE;
    case SPECIES_PORYGON2:
        *palOut = gObjectEventPal_FollowerPorygon2;
        *picOut = sPicTable_Follower_Porygon2;
        return TRUE;
    case SPECIES_STANTLER:
        *palOut = gObjectEventPal_FollowerStantler;
        *picOut = sPicTable_Follower_Stantler;
        return TRUE;
    case SPECIES_SMEARGLE:
        *palOut = gObjectEventPal_FollowerSmeargle;
        *picOut = sPicTable_Follower_Smeargle;
        return TRUE;
    case SPECIES_TYROGUE:
        *palOut = gObjectEventPal_FollowerTyrogue;
        *picOut = sPicTable_Follower_Tyrogue;
        return TRUE;
    case SPECIES_HITMONTOP:
        *palOut = gObjectEventPal_FollowerHitmontop;
        *picOut = sPicTable_Follower_Hitmontop;
        return TRUE;
    case SPECIES_SMOOCHUM:
        *palOut = gObjectEventPal_FollowerSmoochum;
        *picOut = sPicTable_Follower_Smoochum;
        return TRUE;
    case SPECIES_ELEKID:
        *palOut = gObjectEventPal_FollowerElekid;
        *picOut = sPicTable_Follower_Elekid;
        return TRUE;
    case SPECIES_MAGBY:
        *palOut = gObjectEventPal_FollowerMagby;
        *picOut = sPicTable_Follower_Magby;
        return TRUE;
    case SPECIES_MILTANK:
        *palOut = gObjectEventPal_FollowerMiltank;
        *picOut = sPicTable_Follower_Miltank;
        return TRUE;
    case SPECIES_BLISSEY:
        *palOut = gObjectEventPal_FollowerBlissey;
        *picOut = sPicTable_Follower_Blissey;
        return TRUE;
    case SPECIES_RAIKOU:
        *palOut = gObjectEventPal_FollowerRaikou;
        *picOut = sPicTable_Follower_Raikou;
        return TRUE;
    case SPECIES_ENTEI:
        *palOut = gObjectEventPal_FollowerEntei;
        *picOut = sPicTable_Follower_Entei;
        return TRUE;
    case SPECIES_SUICUNE:
        *palOut = gObjectEventPal_FollowerSuicune;
        *picOut = sPicTable_Follower_Suicune;
        return TRUE;
    case SPECIES_LARVITAR:
        *palOut = gObjectEventPal_FollowerLarvitar;
        *picOut = sPicTable_Follower_Larvitar;
        return TRUE;
    case SPECIES_PUPITAR:
        *palOut = gObjectEventPal_FollowerPupitar;
        *picOut = sPicTable_Follower_Pupitar;
        return TRUE;
    case SPECIES_TYRANITAR:
        *palOut = gObjectEventPal_FollowerTyranitar;
        *picOut = sPicTable_Follower_Tyranitar;
        return TRUE;
    case SPECIES_CELEBI:
        *palOut = gObjectEventPal_FollowerCelebi;
        *picOut = sPicTable_Follower_Celebi;
        return TRUE;
    case SPECIES_GROVYLE:
        *palOut = gObjectEventPal_FollowerGrovyle;
        *picOut = sPicTable_Follower_Grovyle;
        return TRUE;
    case SPECIES_SCEPTILE:
        *palOut = gObjectEventPal_FollowerSceptile;
        *picOut = sPicTable_Follower_Sceptile;
        return TRUE;
    case SPECIES_COMBUSKEN:
        *palOut = gObjectEventPal_FollowerCombusken;
        *picOut = sPicTable_Follower_Combusken;
        return TRUE;
    case SPECIES_BLAZIKEN:
        *palOut = gObjectEventPal_FollowerBlaziken;
        *picOut = sPicTable_Follower_Blaziken;
        return TRUE;
    case SPECIES_MARSHTOMP:
        *palOut = gObjectEventPal_FollowerMarshtomp;
        *picOut = sPicTable_Follower_Marshtomp;
        return TRUE;
    case SPECIES_SWAMPERT:
        *palOut = gObjectEventPal_FollowerSwampert;
        *picOut = sPicTable_Follower_Swampert;
        return TRUE;
    case SPECIES_POOCHYENA:
        *palOut = gObjectEventPal_FollowerPoochyena;
        *picOut = sPicTable_Follower_Poochyena;
        return TRUE;
    case SPECIES_MIGHTYENA:
        *palOut = gObjectEventPal_FollowerMightyena;
        *picOut = sPicTable_Follower_Mightyena;
        return TRUE;
    case SPECIES_ZIGZAGOON:
        *palOut = gObjectEventPal_FollowerZigzagoon;
        *picOut = sPicTable_Follower_Zigzagoon;
        return TRUE;
    case SPECIES_LINOONE:
        *palOut = gObjectEventPal_FollowerLinoone;
        *picOut = sPicTable_Follower_Linoone;
        return TRUE;
    case SPECIES_WURMPLE:
        *palOut = gObjectEventPal_FollowerWurmple;
        *picOut = sPicTable_Follower_Wurmple;
        return TRUE;
    case SPECIES_SILCOON:
        *palOut = gObjectEventPal_FollowerSilcoon;
        *picOut = sPicTable_Follower_Silcoon;
        return TRUE;
    case SPECIES_BEAUTIFLY:
        *palOut = gObjectEventPal_FollowerBeautifly;
        *picOut = sPicTable_Follower_Beautifly;
        return TRUE;
    case SPECIES_CASCOON:
        *palOut = gObjectEventPal_FollowerCascoon;
        *picOut = sPicTable_Follower_Cascoon;
        return TRUE;
    case SPECIES_DUSTOX:
        *palOut = gObjectEventPal_FollowerDustox;
        *picOut = sPicTable_Follower_Dustox;
        return TRUE;
    case SPECIES_LOTAD:
        *palOut = gObjectEventPal_FollowerLotad;
        *picOut = sPicTable_Follower_Lotad;
        return TRUE;
    case SPECIES_LOMBRE:
        *palOut = gObjectEventPal_FollowerLombre;
        *picOut = sPicTable_Follower_Lombre;
        return TRUE;
    case SPECIES_LUDICOLO:
        *palOut = gObjectEventPal_FollowerLudicolo;
        *picOut = sPicTable_Follower_Ludicolo;
        return TRUE;
    case SPECIES_SEEDOT:
        *palOut = gObjectEventPal_FollowerSeedot;
        *picOut = sPicTable_Follower_Seedot;
        return TRUE;
    case SPECIES_NUZLEAF:
        *palOut = gObjectEventPal_FollowerNuzleaf;
        *picOut = sPicTable_Follower_Nuzleaf;
        return TRUE;
    case SPECIES_SHIFTRY:
        *palOut = gObjectEventPal_FollowerShiftry;
        *picOut = sPicTable_Follower_Shiftry;
        return TRUE;
    case SPECIES_NINCADA:
        *palOut = gObjectEventPal_FollowerNincada;
        *picOut = sPicTable_Follower_Nincada;
        return TRUE;
    case SPECIES_NINJASK:
        *palOut = gObjectEventPal_FollowerNinjask;
        *picOut = sPicTable_Follower_Ninjask;
        return TRUE;
    case SPECIES_SHEDINJA:
        *palOut = gObjectEventPal_FollowerShedinja;
        *picOut = sPicTable_Follower_Shedinja;
        return TRUE;
    case SPECIES_TAILLOW:
        *palOut = gObjectEventPal_FollowerTaillow;
        *picOut = sPicTable_Follower_Taillow;
        return TRUE;
    case SPECIES_SWELLOW:
        *palOut = gObjectEventPal_FollowerSwellow;
        *picOut = sPicTable_Follower_Swellow;
        return TRUE;
    case SPECIES_SHROOMISH:
        *palOut = gObjectEventPal_FollowerShroomish;
        *picOut = sPicTable_Follower_Shroomish;
        return TRUE;
    case SPECIES_BRELOOM:
        *palOut = gObjectEventPal_FollowerBreloom;
        *picOut = sPicTable_Follower_Breloom;
        return TRUE;
    case SPECIES_SPINDA:
        *palOut = gObjectEventPal_FollowerSpinda;
        *picOut = sPicTable_Follower_Spinda;
        return TRUE;
    case SPECIES_WINGULL:
        *palOut = gObjectEventPal_FollowerWingull;
        *picOut = sPicTable_Follower_Wingull;
        return TRUE;
    case SPECIES_PELIPPER:
        *palOut = gObjectEventPal_FollowerPelipper;
        *picOut = sPicTable_Follower_Pelipper;
        return TRUE;
    case SPECIES_SURSKIT:
        *palOut = gObjectEventPal_FollowerSurskit;
        *picOut = sPicTable_Follower_Surskit;
        return TRUE;
    case SPECIES_MASQUERAIN:
        *palOut = gObjectEventPal_FollowerMasquerain;
        *picOut = sPicTable_Follower_Masquerain;
        return TRUE;
    case SPECIES_WAILMER:
        *palOut = gObjectEventPal_FollowerWailmer;
        *picOut = sPicTable_Follower_Wailmer;
        return TRUE;
    case SPECIES_SKITTY:
        *palOut = gObjectEventPal_FollowerSkitty;
        *picOut = sPicTable_Follower_Skitty;
        return TRUE;
    case SPECIES_DELCATTY:
        *palOut = gObjectEventPal_FollowerDelcatty;
        *picOut = sPicTable_Follower_Delcatty;
        return TRUE;
    case SPECIES_KECLEON:
        *palOut = gObjectEventPal_FollowerKecleon;
        *picOut = sPicTable_Follower_Kecleon;
        return TRUE;
    case SPECIES_BALTOY:
        *palOut = gObjectEventPal_FollowerBaltoy;
        *picOut = sPicTable_Follower_Baltoy;
        return TRUE;
    case SPECIES_CLAYDOL:
        *palOut = gObjectEventPal_FollowerClaydol;
        *picOut = sPicTable_Follower_Claydol;
        return TRUE;
    case SPECIES_NOSEPASS:
        *palOut = gObjectEventPal_FollowerNosepass;
        *picOut = sPicTable_Follower_Nosepass;
        return TRUE;
    case SPECIES_TORKOAL:
        *palOut = gObjectEventPal_FollowerTorkoal;
        *picOut = sPicTable_Follower_Torkoal;
        return TRUE;
    case SPECIES_SABLEYE:
        *palOut = gObjectEventPal_FollowerSableye;
        *picOut = sPicTable_Follower_Sableye;
        return TRUE;
    case SPECIES_BARBOACH:
        *palOut = gObjectEventPal_FollowerBarboach;
        *picOut = sPicTable_Follower_Barboach;
        return TRUE;
    case SPECIES_WHISCASH:
        *palOut = gObjectEventPal_FollowerWhiscash;
        *picOut = sPicTable_Follower_Whiscash;
        return TRUE;
    case SPECIES_LUVDISC:
        *palOut = gObjectEventPal_FollowerLuvdisc;
        *picOut = sPicTable_Follower_Luvdisc;
        return TRUE;
    case SPECIES_CORPHISH:
        *palOut = gObjectEventPal_FollowerCorphish;
        *picOut = sPicTable_Follower_Corphish;
        return TRUE;
    case SPECIES_CRAWDAUNT:
        *palOut = gObjectEventPal_FollowerCrawdaunt;
        *picOut = sPicTable_Follower_Crawdaunt;
        return TRUE;
    case SPECIES_FEEBAS:
        *palOut = gObjectEventPal_FollowerFeebas;
        *picOut = sPicTable_Follower_Feebas;
        return TRUE;
    case SPECIES_MILOTIC:
        *palOut = gObjectEventPal_FollowerMilotic;
        *picOut = sPicTable_Follower_Milotic;
        return TRUE;
    case SPECIES_CARVANHA:
        *palOut = gObjectEventPal_FollowerCarvanha;
        *picOut = sPicTable_Follower_Carvanha;
        return TRUE;
    case SPECIES_SHARPEDO:
        *palOut = gObjectEventPal_FollowerSharpedo;
        *picOut = sPicTable_Follower_Sharpedo;
        return TRUE;
    case SPECIES_TRAPINCH:
        *palOut = gObjectEventPal_FollowerTrapinch;
        *picOut = sPicTable_Follower_Trapinch;
        return TRUE;
    case SPECIES_VIBRAVA:
        *palOut = gObjectEventPal_FollowerVibrava;
        *picOut = sPicTable_Follower_Vibrava;
        return TRUE;
    case SPECIES_FLYGON:
        *palOut = gObjectEventPal_FollowerFlygon;
        *picOut = sPicTable_Follower_Flygon;
        return TRUE;
    case SPECIES_MAKUHITA:
        *palOut = gObjectEventPal_FollowerMakuhita;
        *picOut = sPicTable_Follower_Makuhita;
        return TRUE;
    case SPECIES_HARIYAMA:
        *palOut = gObjectEventPal_FollowerHariyama;
        *picOut = sPicTable_Follower_Hariyama;
        return TRUE;
    case SPECIES_ELECTRIKE:
        *palOut = gObjectEventPal_FollowerElectrike;
        *picOut = sPicTable_Follower_Electrike;
        return TRUE;
    case SPECIES_MANECTRIC:
        *palOut = gObjectEventPal_FollowerManectric;
        *picOut = sPicTable_Follower_Manectric;
        return TRUE;
    case SPECIES_NUMEL:
        *palOut = gObjectEventPal_FollowerNumel;
        *picOut = sPicTable_Follower_Numel;
        return TRUE;
    case SPECIES_CAMERUPT:
        *palOut = gObjectEventPal_FollowerCamerupt;
        *picOut = sPicTable_Follower_Camerupt;
        return TRUE;
    case SPECIES_SPHEAL:
        *palOut = gObjectEventPal_FollowerSpheal;
        *picOut = sPicTable_Follower_Spheal;
        return TRUE;
    case SPECIES_SEALEO:
        *palOut = gObjectEventPal_FollowerSealeo;
        *picOut = sPicTable_Follower_Sealeo;
        return TRUE;
    case SPECIES_WALREIN:
        *palOut = gObjectEventPal_FollowerWalrein;
        *picOut = sPicTable_Follower_Walrein;
        return TRUE;
    case SPECIES_CACNEA:
        *palOut = gObjectEventPal_FollowerCacnea;
        *picOut = sPicTable_Follower_Cacnea;
        return TRUE;
    case SPECIES_CACTURNE:
        *palOut = gObjectEventPal_FollowerCacturne;
        *picOut = sPicTable_Follower_Cacturne;
        return TRUE;
    case SPECIES_SNORUNT:
        *palOut = gObjectEventPal_FollowerSnorunt;
        *picOut = sPicTable_Follower_Snorunt;
        return TRUE;
    case SPECIES_GLALIE:
        *palOut = gObjectEventPal_FollowerGlalie;
        *picOut = sPicTable_Follower_Glalie;
        return TRUE;
    case SPECIES_LUNATONE:
        *palOut = gObjectEventPal_FollowerLunatone;
        *picOut = sPicTable_Follower_Lunatone;
        return TRUE;
    case SPECIES_SOLROCK:
        *palOut = gObjectEventPal_FollowerSolrock;
        *picOut = sPicTable_Follower_Solrock;
        return TRUE;
    case SPECIES_AZURILL:
        *palOut = gObjectEventPal_FollowerAzurill;
        *picOut = sPicTable_Follower_Azurill;
        return TRUE;
    case SPECIES_SPOINK:
        *palOut = gObjectEventPal_FollowerSpoink;
        *picOut = sPicTable_Follower_Spoink;
        return TRUE;
    case SPECIES_GRUMPIG:
        *palOut = gObjectEventPal_FollowerGrumpig;
        *picOut = sPicTable_Follower_Grumpig;
        return TRUE;
    case SPECIES_PLUSLE:
        *palOut = gObjectEventPal_FollowerPlusle;
        *picOut = sPicTable_Follower_Plusle;
        return TRUE;
    case SPECIES_MINUN:
        *palOut = gObjectEventPal_FollowerMinun;
        *picOut = sPicTable_Follower_Minun;
        return TRUE;
    case SPECIES_MAWILE:
        *palOut = gObjectEventPal_FollowerMawile;
        *picOut = sPicTable_Follower_Mawile;
        return TRUE;
    case SPECIES_MEDITITE:
        *palOut = gObjectEventPal_FollowerMeditite;
        *picOut = sPicTable_Follower_Meditite;
        return TRUE;
    case SPECIES_MEDICHAM:
        *palOut = gObjectEventPal_FollowerMedicham;
        *picOut = sPicTable_Follower_Medicham;
        return TRUE;
    case SPECIES_SWABLU:
        *palOut = gObjectEventPal_FollowerSwablu;
        *picOut = sPicTable_Follower_Swablu;
        return TRUE;
    case SPECIES_ALTARIA:
        *palOut = gObjectEventPal_FollowerAltaria;
        *picOut = sPicTable_Follower_Altaria;
        return TRUE;
    case SPECIES_WYNAUT:
        *palOut = gObjectEventPal_FollowerWynaut;
        *picOut = sPicTable_Follower_Wynaut;
        return TRUE;
    case SPECIES_DUSKULL:
        *palOut = gObjectEventPal_FollowerDuskull;
        *picOut = sPicTable_Follower_Duskull;
        return TRUE;
    case SPECIES_DUSCLOPS:
        *palOut = gObjectEventPal_FollowerDusclops;
        *picOut = sPicTable_Follower_Dusclops;
        return TRUE;
    case SPECIES_ROSELIA:
        *palOut = gObjectEventPal_FollowerRoselia;
        *picOut = sPicTable_Follower_Roselia;
        return TRUE;
    case SPECIES_SLAKOTH:
        *palOut = gObjectEventPal_FollowerSlakoth;
        *picOut = sPicTable_Follower_Slakoth;
        return TRUE;
    case SPECIES_VIGOROTH:
        *palOut = gObjectEventPal_FollowerVigoroth;
        *picOut = sPicTable_Follower_Vigoroth;
        return TRUE;
    case SPECIES_SLAKING:
        *palOut = gObjectEventPal_FollowerSlaking;
        *picOut = sPicTable_Follower_Slaking;
        return TRUE;
    case SPECIES_GULPIN:
        *palOut = gObjectEventPal_FollowerGulpin;
        *picOut = sPicTable_Follower_Gulpin;
        return TRUE;
    case SPECIES_SWALOT:
        *palOut = gObjectEventPal_FollowerSwalot;
        *picOut = sPicTable_Follower_Swalot;
        return TRUE;
    case SPECIES_TROPIUS:
        *palOut = gObjectEventPal_FollowerTropius;
        *picOut = sPicTable_Follower_Tropius;
        return TRUE;
    case SPECIES_WHISMUR:
        *palOut = gObjectEventPal_FollowerWhismur;
        *picOut = sPicTable_Follower_Whismur;
        return TRUE;
    case SPECIES_LOUDRED:
        *palOut = gObjectEventPal_FollowerLoudred;
        *picOut = sPicTable_Follower_Loudred;
        return TRUE;
    case SPECIES_EXPLOUD:
        *palOut = gObjectEventPal_FollowerExploud;
        *picOut = sPicTable_Follower_Exploud;
        return TRUE;
    case SPECIES_CLAMPERL:
        *palOut = gObjectEventPal_FollowerClamperl;
        *picOut = sPicTable_Follower_Clamperl;
        return TRUE;
    case SPECIES_HUNTAIL:
        *palOut = gObjectEventPal_FollowerHuntail;
        *picOut = sPicTable_Follower_Huntail;
        return TRUE;
    case SPECIES_GOREBYSS:
        *palOut = gObjectEventPal_FollowerGorebyss;
        *picOut = sPicTable_Follower_Gorebyss;
        return TRUE;
    case SPECIES_ABSOL:
        *palOut = gObjectEventPal_FollowerAbsol;
        *picOut = sPicTable_Follower_Absol;
        return TRUE;
    case SPECIES_SHUPPET:
        *palOut = gObjectEventPal_FollowerShuppet;
        *picOut = sPicTable_Follower_Shuppet;
        return TRUE;
    case SPECIES_BANETTE:
        *palOut = gObjectEventPal_FollowerBanette;
        *picOut = sPicTable_Follower_Banette;
        return TRUE;
    case SPECIES_SEVIPER:
        *palOut = gObjectEventPal_FollowerSeviper;
        *picOut = sPicTable_Follower_Seviper;
        return TRUE;
    case SPECIES_ZANGOOSE:
        *palOut = gObjectEventPal_FollowerZangoose;
        *picOut = sPicTable_Follower_Zangoose;
        return TRUE;
    case SPECIES_RELICANTH:
        *palOut = gObjectEventPal_FollowerRelicanth;
        *picOut = sPicTable_Follower_Relicanth;
        return TRUE;
    case SPECIES_ARON:
        *palOut = gObjectEventPal_FollowerAron;
        *picOut = sPicTable_Follower_Aron;
        return TRUE;
    case SPECIES_LAIRON:
        *palOut = gObjectEventPal_FollowerLairon;
        *picOut = sPicTable_Follower_Lairon;
        return TRUE;
    case SPECIES_AGGRON:
        *palOut = gObjectEventPal_FollowerAggron;
        *picOut = sPicTable_Follower_Aggron;
        return TRUE;
    case SPECIES_CASTFORM:
        *palOut = gObjectEventPal_FollowerCastform;
        *picOut = sPicTable_Follower_Castform;
        return TRUE;
    case SPECIES_VOLBEAT:
        *palOut = gObjectEventPal_FollowerVolbeat;
        *picOut = sPicTable_Follower_Volbeat;
        return TRUE;
    case SPECIES_ILLUMISE:
        *palOut = gObjectEventPal_FollowerIllumise;
        *picOut = sPicTable_Follower_Illumise;
        return TRUE;
    case SPECIES_LILEEP:
        *palOut = gObjectEventPal_FollowerLileep;
        *picOut = sPicTable_Follower_Lileep;
        return TRUE;
    case SPECIES_CRADILY:
        *palOut = gObjectEventPal_FollowerCradily;
        *picOut = sPicTable_Follower_Cradily;
        return TRUE;
    case SPECIES_ANORITH:
        *palOut = gObjectEventPal_FollowerAnorith;
        *picOut = sPicTable_Follower_Anorith;
        return TRUE;
    case SPECIES_ARMALDO:
        *palOut = gObjectEventPal_FollowerArmaldo;
        *picOut = sPicTable_Follower_Armaldo;
        return TRUE;
    case SPECIES_RALTS:
        *palOut = gObjectEventPal_FollowerRalts;
        *picOut = sPicTable_Follower_Ralts;
        return TRUE;
    case SPECIES_KIRLIA:
        *palOut = gObjectEventPal_FollowerKirlia;
        *picOut = sPicTable_Follower_Kirlia;
        return TRUE;
    case SPECIES_GARDEVOIR:
        *palOut = gObjectEventPal_FollowerGardevoir;
        *picOut = sPicTable_Follower_Gardevoir;
        return TRUE;
    case SPECIES_BAGON:
        *palOut = gObjectEventPal_FollowerBagon;
        *picOut = sPicTable_Follower_Bagon;
        return TRUE;
    case SPECIES_SHELGON:
        *palOut = gObjectEventPal_FollowerShelgon;
        *picOut = sPicTable_Follower_Shelgon;
        return TRUE;
    case SPECIES_SALAMENCE:
        *palOut = gObjectEventPal_FollowerSalamence;
        *picOut = sPicTable_Follower_Salamence;
        return TRUE;
    case SPECIES_BELDUM:
        *palOut = gObjectEventPal_FollowerBeldum;
        *picOut = sPicTable_Follower_Beldum;
        return TRUE;
    case SPECIES_METANG:
        *palOut = gObjectEventPal_FollowerMetang;
        *picOut = sPicTable_Follower_Metang;
        return TRUE;
    case SPECIES_METAGROSS:
        *palOut = gObjectEventPal_FollowerMetagross;
        *picOut = sPicTable_Follower_Metagross;
        return TRUE;
    case SPECIES_REGIROCK:
        *palOut = gObjectEventPal_FollowerRegirock;
        *picOut = sPicTable_Follower_Regirock;
        return TRUE;
    case SPECIES_REGICE:
        *palOut = gObjectEventPal_FollowerRegice;
        *picOut = sPicTable_Follower_Regice;
        return TRUE;
    case SPECIES_REGISTEEL:
        *palOut = gObjectEventPal_FollowerRegisteel;
        *picOut = sPicTable_Follower_Registeel;
        return TRUE;
    case SPECIES_LATIAS:
        *palOut = gObjectEventPal_FollowerLatias;
        *picOut = sPicTable_Follower_Latias;
        return TRUE;
    case SPECIES_LATIOS:
        *palOut = gObjectEventPal_FollowerLatios;
        *picOut = sPicTable_Follower_Latios;
        return TRUE;
    case SPECIES_JIRACHI:
        *palOut = gObjectEventPal_FollowerJirachi;
        *picOut = sPicTable_Follower_Jirachi;
        return TRUE;
    case SPECIES_DEOXYS:
        *palOut = gObjectEventPal_FollowerDeoxys;
        *picOut = sPicTable_Follower_Deoxys;
        return TRUE;
    case SPECIES_CHIMECHO:
        *palOut = gObjectEventPal_FollowerChimecho;
        *picOut = sPicTable_Follower_Chimecho;
        return TRUE;
    case SPECIES_UNOWN:
    {
        // Palette 1: A B E I J K L M N P Q S T U V W X Y Z ! ?
        // Palette 2: C D F G H O R
#define P1 gObjectEventPal_FollowerUnown1
#define P2 gObjectEventPal_FollowerUnown2
        static const u16 *const sPals[NUM_UNOWN_FORMS] = {
            P1, P1, P2, P2, P1, P2, P2, P2, P1, P1, P1, P1, P1, P1, P2, P1, P1, P2, P1, P1, P1, P1, P1, P1, P1, P1, P1, P1
        };
#undef P1
#undef P2
        static const struct SpriteFrameImage *const sPics[NUM_UNOWN_FORMS] = {
            sPicTable_Follower_UnownA, sPicTable_Follower_UnownB, sPicTable_Follower_UnownC, sPicTable_Follower_UnownD, sPicTable_Follower_UnownE, sPicTable_Follower_UnownF, sPicTable_Follower_UnownG, sPicTable_Follower_UnownH, sPicTable_Follower_UnownI, sPicTable_Follower_UnownJ, sPicTable_Follower_UnownK, sPicTable_Follower_UnownL, sPicTable_Follower_UnownM, sPicTable_Follower_UnownN, sPicTable_Follower_UnownO, sPicTable_Follower_UnownP, sPicTable_Follower_UnownQ, sPicTable_Follower_UnownR, sPicTable_Follower_UnownS, sPicTable_Follower_UnownT, sPicTable_Follower_UnownU, sPicTable_Follower_UnownV, sPicTable_Follower_UnownW, sPicTable_Follower_UnownX, sPicTable_Follower_UnownY, sPicTable_Follower_UnownZ, sPicTable_Follower_UnownExclamation, sPicTable_Follower_UnownQuestion
        };
        u32 personality = GetMonData(&gPlayerParty[0], MON_DATA_PERSONALITY);
        u16 form = GET_UNOWN_LETTER(personality);
        *palOut = sPals[form];
        *picOut = sPics[form];
        return TRUE;
    }
    case SPECIES_STEELIX:
        *palOut = gObjectEventPal_FollowerSteelix;
        *picOut = sPicTable_Follower_Steelix;
        return TRUE;
    case SPECIES_LUGIA:
        *palOut = gObjectEventPal_FollowerLugia;
        *picOut = sPicTable_Follower_Lugia;
        return TRUE;
    case SPECIES_HO_OH:
        *palOut = gObjectEventPal_FollowerHoOh;
        *picOut = sPicTable_Follower_HoOh;
        return TRUE;
    case SPECIES_WAILORD:
        *palOut = gObjectEventPal_FollowerWailord;
        *picOut = sPicTable_Follower_Wailord;
        return TRUE;
    case SPECIES_KYOGRE:
        *palOut = gObjectEventPal_FollowerKyogre;
        *picOut = sPicTable_Follower_Kyogre;
        return TRUE;
    case SPECIES_GROUDON:
        *palOut = gObjectEventPal_FollowerGroudon;
        *picOut = sPicTable_Follower_Groudon;
        return TRUE;
    case SPECIES_RAYQUAZA:
        *palOut = gObjectEventPal_FollowerRayquaza;
        *picOut = sPicTable_Follower_Rayquaza;
        return TRUE;
    default:
        return FALSE;
    }
}


static bool8 GetFollowerShinyPal(u16 species, const u16 **palOut)
{
    switch (species)
    {
    case SPECIES_BULBASAUR:
        *palOut = gObjectEventPal_FollowerBulbasaurShiny;
        return TRUE;
    case SPECIES_CHARMANDER:
        *palOut = gObjectEventPal_FollowerCharmanderShiny;
        return TRUE;
    case SPECIES_SQUIRTLE:
        *palOut = gObjectEventPal_FollowerSquirtleShiny;
        return TRUE;
    case SPECIES_CHIKORITA:
        *palOut = gObjectEventPal_FollowerChikoritaShiny;
        return TRUE;
    case SPECIES_CYNDAQUIL:
        *palOut = gObjectEventPal_FollowerCyndaquilShiny;
        return TRUE;
    case SPECIES_TOTODILE:
        *palOut = gObjectEventPal_FollowerTotodileShiny;
        return TRUE;
    case SPECIES_TREECKO:
        *palOut = gObjectEventPal_FollowerTreeckoShiny;
        return TRUE;
    case SPECIES_TORCHIC:
        *palOut = gObjectEventPal_FollowerTorchicShiny;
        return TRUE;
    case SPECIES_MUDKIP:
        *palOut = gObjectEventPal_FollowerMudkipShiny;
        return TRUE;
    case SPECIES_IVYSAUR:
        *palOut = gObjectEventPal_FollowerIvysaurShiny;
        return TRUE;
    case SPECIES_VENUSAUR:
        *palOut = gObjectEventPal_FollowerVenusaurShiny;
        return TRUE;
    case SPECIES_CHARMELEON:
        *palOut = gObjectEventPal_FollowerCharmeleonShiny;
        return TRUE;
    case SPECIES_CHARIZARD:
        *palOut = gObjectEventPal_FollowerCharizardShiny;
        return TRUE;
    case SPECIES_WARTORTLE:
        *palOut = gObjectEventPal_FollowerWartortleShiny;
        return TRUE;
    case SPECIES_BLASTOISE:
        *palOut = gObjectEventPal_FollowerBlastoiseShiny;
        return TRUE;
    case SPECIES_CATERPIE:
        *palOut = gObjectEventPal_FollowerCaterpieShiny;
        return TRUE;
    case SPECIES_METAPOD:
        *palOut = gObjectEventPal_FollowerMetapodShiny;
        return TRUE;
    case SPECIES_BUTTERFREE:
        *palOut = gObjectEventPal_FollowerButterfreeShiny;
        return TRUE;
    case SPECIES_WEEDLE:
        *palOut = gObjectEventPal_FollowerWeedleShiny;
        return TRUE;
    case SPECIES_KAKUNA:
        *palOut = gObjectEventPal_FollowerKakunaShiny;
        return TRUE;
    case SPECIES_BEEDRILL:
        *palOut = gObjectEventPal_FollowerBeedrillShiny;
        return TRUE;
    case SPECIES_PIDGEY:
        *palOut = gObjectEventPal_FollowerPidgeyShiny;
        return TRUE;
    case SPECIES_PIDGEOTTO:
        *palOut = gObjectEventPal_FollowerPidgeottoShiny;
        return TRUE;
    case SPECIES_PIDGEOT:
        *palOut = gObjectEventPal_FollowerPidgeotShiny;
        return TRUE;
    case SPECIES_RATTATA:
        *palOut = gObjectEventPal_FollowerRattataShiny;
        return TRUE;
    case SPECIES_RATICATE:
        *palOut = gObjectEventPal_FollowerRaticateShiny;
        return TRUE;
    case SPECIES_SPEAROW:
        *palOut = gObjectEventPal_FollowerSpearowShiny;
        return TRUE;
    case SPECIES_FEAROW:
        *palOut = gObjectEventPal_FollowerFearowShiny;
        return TRUE;
    case SPECIES_EKANS:
        *palOut = gObjectEventPal_FollowerEkansShiny;
        return TRUE;
    case SPECIES_ARBOK:
        *palOut = gObjectEventPal_FollowerArbokShiny;
        return TRUE;
    case SPECIES_PIKACHU:
        *palOut = gObjectEventPal_FollowerPikachuShiny;
        return TRUE;
    case SPECIES_RAICHU:
        *palOut = gObjectEventPal_FollowerRaichuShiny;
        return TRUE;
    case SPECIES_SANDSHREW:
        *palOut = gObjectEventPal_FollowerSandshrewShiny;
        return TRUE;
    case SPECIES_SANDSLASH:
        *palOut = gObjectEventPal_FollowerSandslashShiny;
        return TRUE;
    case SPECIES_NIDORAN_F:
        *palOut = gObjectEventPal_FollowerNidoranFShiny;
        return TRUE;
    case SPECIES_NIDORINA:
        *palOut = gObjectEventPal_FollowerNidorinaShiny;
        return TRUE;
    case SPECIES_NIDOQUEEN:
        *palOut = gObjectEventPal_FollowerNidoqueenShiny;
        return TRUE;
    case SPECIES_NIDORAN_M:
        *palOut = gObjectEventPal_FollowerNidoranMShiny;
        return TRUE;
    case SPECIES_NIDORINO:
        *palOut = gObjectEventPal_FollowerNidorinoShiny;
        return TRUE;
    case SPECIES_NIDOKING:
        *palOut = gObjectEventPal_FollowerNidokingShiny;
        return TRUE;
    case SPECIES_CLEFAIRY:
        *palOut = gObjectEventPal_FollowerClefairyShiny;
        return TRUE;
    case SPECIES_CLEFABLE:
        *palOut = gObjectEventPal_FollowerClefableShiny;
        return TRUE;
    case SPECIES_VULPIX:
        *palOut = gObjectEventPal_FollowerVulpixShiny;
        return TRUE;
    case SPECIES_NINETALES:
        *palOut = gObjectEventPal_FollowerNinetalesShiny;
        return TRUE;
    case SPECIES_JIGGLYPUFF:
        *palOut = gObjectEventPal_FollowerJigglypuffShiny;
        return TRUE;
    case SPECIES_WIGGLYTUFF:
        *palOut = gObjectEventPal_FollowerWigglytuffShiny;
        return TRUE;
    case SPECIES_ZUBAT:
        *palOut = gObjectEventPal_FollowerZubatShiny;
        return TRUE;
    case SPECIES_GOLBAT:
        *palOut = gObjectEventPal_FollowerGolbatShiny;
        return TRUE;
    case SPECIES_ODDISH:
        *palOut = gObjectEventPal_FollowerOddishShiny;
        return TRUE;
    case SPECIES_GLOOM:
        *palOut = gObjectEventPal_FollowerGloomShiny;
        return TRUE;
    case SPECIES_VILEPLUME:
        *palOut = gObjectEventPal_FollowerVileplumeShiny;
        return TRUE;
    case SPECIES_PARAS:
        *palOut = gObjectEventPal_FollowerParasShiny;
        return TRUE;
    case SPECIES_PARASECT:
        *palOut = gObjectEventPal_FollowerParasectShiny;
        return TRUE;
    case SPECIES_VENONAT:
        *palOut = gObjectEventPal_FollowerVenonatShiny;
        return TRUE;
    case SPECIES_VENOMOTH:
        *palOut = gObjectEventPal_FollowerVenomothShiny;
        return TRUE;
    case SPECIES_DIGLETT:
        *palOut = gObjectEventPal_FollowerDiglettShiny;
        return TRUE;
    case SPECIES_DUGTRIO:
        *palOut = gObjectEventPal_FollowerDugtrioShiny;
        return TRUE;
    case SPECIES_MEOWTH:
        *palOut = gObjectEventPal_FollowerMeowthShiny;
        return TRUE;
    case SPECIES_PERSIAN:
        *palOut = gObjectEventPal_FollowerPersianShiny;
        return TRUE;
    case SPECIES_PSYDUCK:
        *palOut = gObjectEventPal_FollowerPsyduckShiny;
        return TRUE;
    case SPECIES_GOLDUCK:
        *palOut = gObjectEventPal_FollowerGolduckShiny;
        return TRUE;
    case SPECIES_MANKEY:
        *palOut = gObjectEventPal_FollowerMankeyShiny;
        return TRUE;
    case SPECIES_PRIMEAPE:
        *palOut = gObjectEventPal_FollowerPrimeapeShiny;
        return TRUE;
    case SPECIES_GROWLITHE:
        *palOut = gObjectEventPal_FollowerGrowlitheShiny;
        return TRUE;
    case SPECIES_ARCANINE:
        *palOut = gObjectEventPal_FollowerArcanineShiny;
        return TRUE;
    case SPECIES_POLIWAG:
        *palOut = gObjectEventPal_FollowerPoliwagShiny;
        return TRUE;
    case SPECIES_POLIWHIRL:
        *palOut = gObjectEventPal_FollowerPoliwhirlShiny;
        return TRUE;
    case SPECIES_POLIWRATH:
        *palOut = gObjectEventPal_FollowerPoliwrathShiny;
        return TRUE;
    case SPECIES_ABRA:
        *palOut = gObjectEventPal_FollowerAbraShiny;
        return TRUE;
    case SPECIES_KADABRA:
        *palOut = gObjectEventPal_FollowerKadabraShiny;
        return TRUE;
    case SPECIES_ALAKAZAM:
        *palOut = gObjectEventPal_FollowerAlakazamShiny;
        return TRUE;
    case SPECIES_MACHOP:
        *palOut = gObjectEventPal_FollowerMachopShiny;
        return TRUE;
    case SPECIES_MACHOKE:
        *palOut = gObjectEventPal_FollowerMachokeShiny;
        return TRUE;
    case SPECIES_MACHAMP:
        *palOut = gObjectEventPal_FollowerMachampShiny;
        return TRUE;
    case SPECIES_BELLSPROUT:
        *palOut = gObjectEventPal_FollowerBellsproutShiny;
        return TRUE;
    case SPECIES_WEEPINBELL:
        *palOut = gObjectEventPal_FollowerWeepinbellShiny;
        return TRUE;
    case SPECIES_VICTREEBEL:
        *palOut = gObjectEventPal_FollowerVictreebelShiny;
        return TRUE;
    case SPECIES_TENTACOOL:
        *palOut = gObjectEventPal_FollowerTentacoolShiny;
        return TRUE;
    case SPECIES_TENTACRUEL:
        *palOut = gObjectEventPal_FollowerTentacruelShiny;
        return TRUE;
    case SPECIES_GEODUDE:
        *palOut = gObjectEventPal_FollowerGeodudeShiny;
        return TRUE;
    case SPECIES_GRAVELER:
        *palOut = gObjectEventPal_FollowerGravelerShiny;
        return TRUE;
    case SPECIES_GOLEM:
        *palOut = gObjectEventPal_FollowerGolemShiny;
        return TRUE;
    case SPECIES_PONYTA:
        *palOut = gObjectEventPal_FollowerPonytaShiny;
        return TRUE;
    case SPECIES_RAPIDASH:
        *palOut = gObjectEventPal_FollowerRapidashShiny;
        return TRUE;
    case SPECIES_SLOWPOKE:
        *palOut = gObjectEventPal_FollowerSlowpokeShiny;
        return TRUE;
    case SPECIES_SLOWBRO:
        *palOut = gObjectEventPal_FollowerSlowbroShiny;
        return TRUE;
    case SPECIES_MAGNEMITE:
        *palOut = gObjectEventPal_FollowerMagnemiteShiny;
        return TRUE;
    case SPECIES_MAGNETON:
        *palOut = gObjectEventPal_FollowerMagnetonShiny;
        return TRUE;
    case SPECIES_FARFETCHD:
        *palOut = gObjectEventPal_FollowerFarfetchdShiny;
        return TRUE;
    case SPECIES_DODUO:
        *palOut = gObjectEventPal_FollowerDoduoShiny;
        return TRUE;
    case SPECIES_DODRIO:
        *palOut = gObjectEventPal_FollowerDodrioShiny;
        return TRUE;
    case SPECIES_SEEL:
        *palOut = gObjectEventPal_FollowerSeelShiny;
        return TRUE;
    case SPECIES_DEWGONG:
        *palOut = gObjectEventPal_FollowerDewgongShiny;
        return TRUE;
    case SPECIES_GRIMER:
        *palOut = gObjectEventPal_FollowerGrimerShiny;
        return TRUE;
    case SPECIES_MUK:
        *palOut = gObjectEventPal_FollowerMukShiny;
        return TRUE;
    case SPECIES_SHELLDER:
        *palOut = gObjectEventPal_FollowerShellderShiny;
        return TRUE;
    case SPECIES_CLOYSTER:
        *palOut = gObjectEventPal_FollowerCloysterShiny;
        return TRUE;
    case SPECIES_GASTLY:
        *palOut = gObjectEventPal_FollowerGastlyShiny;
        return TRUE;
    case SPECIES_HAUNTER:
        *palOut = gObjectEventPal_FollowerHaunterShiny;
        return TRUE;
    case SPECIES_GENGAR:
        *palOut = gObjectEventPal_FollowerGengarShiny;
        return TRUE;
    case SPECIES_ONIX:
        *palOut = gObjectEventPal_FollowerOnixShiny;
        return TRUE;
    case SPECIES_DROWZEE:
        *palOut = gObjectEventPal_FollowerDrowzeeShiny;
        return TRUE;
    case SPECIES_HYPNO:
        *palOut = gObjectEventPal_FollowerHypnoShiny;
        return TRUE;
    case SPECIES_KRABBY:
        *palOut = gObjectEventPal_FollowerKrabbyShiny;
        return TRUE;
    case SPECIES_KINGLER:
        *palOut = gObjectEventPal_FollowerKinglerShiny;
        return TRUE;
    case SPECIES_VOLTORB:
        *palOut = gObjectEventPal_FollowerVoltorbShiny;
        return TRUE;
    case SPECIES_ELECTRODE:
        *palOut = gObjectEventPal_FollowerElectrodeShiny;
        return TRUE;
    case SPECIES_EXEGGCUTE:
        *palOut = gObjectEventPal_FollowerExeggcuteShiny;
        return TRUE;
    case SPECIES_EXEGGUTOR:
        *palOut = gObjectEventPal_FollowerExeggutorShiny;
        return TRUE;
    case SPECIES_CUBONE:
        *palOut = gObjectEventPal_FollowerCuboneShiny;
        return TRUE;
    case SPECIES_MAROWAK:
        *palOut = gObjectEventPal_FollowerMarowakShiny;
        return TRUE;
    case SPECIES_HITMONLEE:
        *palOut = gObjectEventPal_FollowerHitmonleeShiny;
        return TRUE;
    case SPECIES_HITMONCHAN:
        *palOut = gObjectEventPal_FollowerHitmonchanShiny;
        return TRUE;
    case SPECIES_LICKITUNG:
        *palOut = gObjectEventPal_FollowerLickitungShiny;
        return TRUE;
    case SPECIES_KOFFING:
        *palOut = gObjectEventPal_FollowerKoffingShiny;
        return TRUE;
    case SPECIES_WEEZING:
        *palOut = gObjectEventPal_FollowerWeezingShiny;
        return TRUE;
    case SPECIES_RHYHORN:
        *palOut = gObjectEventPal_FollowerRhyhornShiny;
        return TRUE;
    case SPECIES_RHYDON:
        *palOut = gObjectEventPal_FollowerRhydonShiny;
        return TRUE;
    case SPECIES_CHANSEY:
        *palOut = gObjectEventPal_FollowerChanseyShiny;
        return TRUE;
    case SPECIES_TANGELA:
        *palOut = gObjectEventPal_FollowerTangelaShiny;
        return TRUE;
    case SPECIES_KANGASKHAN:
        *palOut = gObjectEventPal_FollowerKangaskhanShiny;
        return TRUE;
    case SPECIES_HORSEA:
        *palOut = gObjectEventPal_FollowerHorseaShiny;
        return TRUE;
    case SPECIES_SEADRA:
        *palOut = gObjectEventPal_FollowerSeadraShiny;
        return TRUE;
    case SPECIES_GOLDEEN:
        *palOut = gObjectEventPal_FollowerGoldeenShiny;
        return TRUE;
    case SPECIES_SEAKING:
        *palOut = gObjectEventPal_FollowerSeakingShiny;
        return TRUE;
    case SPECIES_STARYU:
        *palOut = gObjectEventPal_FollowerStaryuShiny;
        return TRUE;
    case SPECIES_STARMIE:
        *palOut = gObjectEventPal_FollowerStarmieShiny;
        return TRUE;
    case SPECIES_MR_MIME:
        *palOut = gObjectEventPal_FollowerMrMimeShiny;
        return TRUE;
    case SPECIES_SCYTHER:
        *palOut = gObjectEventPal_FollowerScytherShiny;
        return TRUE;
    case SPECIES_JYNX:
        *palOut = gObjectEventPal_FollowerJynxShiny;
        return TRUE;
    case SPECIES_ELECTABUZZ:
        *palOut = gObjectEventPal_FollowerElectabuzzShiny;
        return TRUE;
    case SPECIES_MAGMAR:
        *palOut = gObjectEventPal_FollowerMagmarShiny;
        return TRUE;
    case SPECIES_PINSIR:
        *palOut = gObjectEventPal_FollowerPinsirShiny;
        return TRUE;
    case SPECIES_TAUROS:
        *palOut = gObjectEventPal_FollowerTaurosShiny;
        return TRUE;
    case SPECIES_MAGIKARP:
        *palOut = gObjectEventPal_FollowerMagikarpShiny;
        return TRUE;
    case SPECIES_GYARADOS:
        *palOut = gObjectEventPal_FollowerGyaradosShiny;
        return TRUE;
    case SPECIES_LAPRAS:
        *palOut = gObjectEventPal_FollowerLaprasShiny;
        return TRUE;
    case SPECIES_DITTO:
        *palOut = gObjectEventPal_FollowerDittoShiny;
        return TRUE;
    case SPECIES_EEVEE:
        *palOut = gObjectEventPal_FollowerEeveeShiny;
        return TRUE;
    case SPECIES_VAPOREON:
        *palOut = gObjectEventPal_FollowerVaporeonShiny;
        return TRUE;
    case SPECIES_JOLTEON:
        *palOut = gObjectEventPal_FollowerJolteonShiny;
        return TRUE;
    case SPECIES_FLAREON:
        *palOut = gObjectEventPal_FollowerFlareonShiny;
        return TRUE;
    case SPECIES_PORYGON:
        *palOut = gObjectEventPal_FollowerPorygonShiny;
        return TRUE;
    case SPECIES_OMANYTE:
        *palOut = gObjectEventPal_FollowerOmanyteShiny;
        return TRUE;
    case SPECIES_OMASTAR:
        *palOut = gObjectEventPal_FollowerOmastarShiny;
        return TRUE;
    case SPECIES_KABUTO:
        *palOut = gObjectEventPal_FollowerKabutoShiny;
        return TRUE;
    case SPECIES_KABUTOPS:
        *palOut = gObjectEventPal_FollowerKabutopsShiny;
        return TRUE;
    case SPECIES_AERODACTYL:
        *palOut = gObjectEventPal_FollowerAerodactylShiny;
        return TRUE;
    case SPECIES_SNORLAX:
        *palOut = gObjectEventPal_FollowerSnorlaxShiny;
        return TRUE;
    case SPECIES_ARTICUNO:
        *palOut = gObjectEventPal_FollowerArticunoShiny;
        return TRUE;
    case SPECIES_ZAPDOS:
        *palOut = gObjectEventPal_FollowerZapdosShiny;
        return TRUE;
    case SPECIES_MOLTRES:
        *palOut = gObjectEventPal_FollowerMoltresShiny;
        return TRUE;
    case SPECIES_DRATINI:
        *palOut = gObjectEventPal_FollowerDratiniShiny;
        return TRUE;
    case SPECIES_DRAGONAIR:
        *palOut = gObjectEventPal_FollowerDragonairShiny;
        return TRUE;
    case SPECIES_DRAGONITE:
        *palOut = gObjectEventPal_FollowerDragoniteShiny;
        return TRUE;
    case SPECIES_MEWTWO:
        *palOut = gObjectEventPal_FollowerMewtwoShiny;
        return TRUE;
    case SPECIES_MEW:
        *palOut = gObjectEventPal_FollowerMewShiny;
        return TRUE;
    case SPECIES_BAYLEEF:
        *palOut = gObjectEventPal_FollowerBayleefShiny;
        return TRUE;
    case SPECIES_MEGANIUM:
        *palOut = gObjectEventPal_FollowerMeganiumShiny;
        return TRUE;
    case SPECIES_QUILAVA:
        *palOut = gObjectEventPal_FollowerQuilavaShiny;
        return TRUE;
    case SPECIES_TYPHLOSION:
        *palOut = gObjectEventPal_FollowerTyphlosionShiny;
        return TRUE;
    case SPECIES_CROCONAW:
        *palOut = gObjectEventPal_FollowerCroconawShiny;
        return TRUE;
    case SPECIES_FERALIGATR:
        *palOut = gObjectEventPal_FollowerFeraligatrShiny;
        return TRUE;
    case SPECIES_SENTRET:
        *palOut = gObjectEventPal_FollowerSentretShiny;
        return TRUE;
    case SPECIES_FURRET:
        *palOut = gObjectEventPal_FollowerFurretShiny;
        return TRUE;
    case SPECIES_HOOTHOOT:
        *palOut = gObjectEventPal_FollowerHoothootShiny;
        return TRUE;
    case SPECIES_NOCTOWL:
        *palOut = gObjectEventPal_FollowerNoctowlShiny;
        return TRUE;
    case SPECIES_LEDYBA:
        *palOut = gObjectEventPal_FollowerLedybaShiny;
        return TRUE;
    case SPECIES_LEDIAN:
        *palOut = gObjectEventPal_FollowerLedianShiny;
        return TRUE;
    case SPECIES_SPINARAK:
        *palOut = gObjectEventPal_FollowerSpinarakShiny;
        return TRUE;
    case SPECIES_ARIADOS:
        *palOut = gObjectEventPal_FollowerAriadosShiny;
        return TRUE;
    case SPECIES_CROBAT:
        *palOut = gObjectEventPal_FollowerCrobatShiny;
        return TRUE;
    case SPECIES_CHINCHOU:
        *palOut = gObjectEventPal_FollowerChinchouShiny;
        return TRUE;
    case SPECIES_LANTURN:
        *palOut = gObjectEventPal_FollowerLanturnShiny;
        return TRUE;
    case SPECIES_PICHU:
        *palOut = gObjectEventPal_FollowerPichuShiny;
        return TRUE;
    case SPECIES_CLEFFA:
        *palOut = gObjectEventPal_FollowerCleffaShiny;
        return TRUE;
    case SPECIES_IGGLYBUFF:
        *palOut = gObjectEventPal_FollowerIgglybuffShiny;
        return TRUE;
    case SPECIES_TOGEPI:
        *palOut = gObjectEventPal_FollowerTogepiShiny;
        return TRUE;
    case SPECIES_TOGETIC:
        *palOut = gObjectEventPal_FollowerTogeticShiny;
        return TRUE;
    case SPECIES_NATU:
        *palOut = gObjectEventPal_FollowerNatuShiny;
        return TRUE;
    case SPECIES_XATU:
        *palOut = gObjectEventPal_FollowerXatuShiny;
        return TRUE;
    case SPECIES_MAREEP:
        *palOut = gObjectEventPal_FollowerMareepShiny;
        return TRUE;
    case SPECIES_FLAAFFY:
        *palOut = gObjectEventPal_FollowerFlaaffyShiny;
        return TRUE;
    case SPECIES_AMPHAROS:
        *palOut = gObjectEventPal_FollowerAmpharosShiny;
        return TRUE;
    case SPECIES_BELLOSSOM:
        *palOut = gObjectEventPal_FollowerBellossomShiny;
        return TRUE;
    case SPECIES_MARILL:
        *palOut = gObjectEventPal_FollowerMarillShiny;
        return TRUE;
    case SPECIES_AZUMARILL:
        *palOut = gObjectEventPal_FollowerAzumarillShiny;
        return TRUE;
    case SPECIES_SUDOWOODO:
        *palOut = gObjectEventPal_FollowerSudowoodoShiny;
        return TRUE;
    case SPECIES_POLITOED:
        *palOut = gObjectEventPal_FollowerPolitoedShiny;
        return TRUE;
    case SPECIES_HOPPIP:
        *palOut = gObjectEventPal_FollowerHoppipShiny;
        return TRUE;
    case SPECIES_SKIPLOOM:
        *palOut = gObjectEventPal_FollowerSkiploomShiny;
        return TRUE;
    case SPECIES_JUMPLUFF:
        *palOut = gObjectEventPal_FollowerJumpluffShiny;
        return TRUE;
    case SPECIES_AIPOM:
        *palOut = gObjectEventPal_FollowerAipomShiny;
        return TRUE;
    case SPECIES_SUNKERN:
        *palOut = gObjectEventPal_FollowerSunkernShiny;
        return TRUE;
    case SPECIES_SUNFLORA:
        *palOut = gObjectEventPal_FollowerSunfloraShiny;
        return TRUE;
    case SPECIES_YANMA:
        *palOut = gObjectEventPal_FollowerYanmaShiny;
        return TRUE;
    case SPECIES_WOOPER:
        *palOut = gObjectEventPal_FollowerWooperShiny;
        return TRUE;
    case SPECIES_QUAGSIRE:
        *palOut = gObjectEventPal_FollowerQuagsireShiny;
        return TRUE;
    case SPECIES_ESPEON:
        *palOut = gObjectEventPal_FollowerEspeonShiny;
        return TRUE;
    case SPECIES_UMBREON:
        *palOut = gObjectEventPal_FollowerUmbreonShiny;
        return TRUE;
    case SPECIES_MURKROW:
        *palOut = gObjectEventPal_FollowerMurkrowShiny;
        return TRUE;
    case SPECIES_SLOWKING:
        *palOut = gObjectEventPal_FollowerSlowkingShiny;
        return TRUE;
    case SPECIES_MISDREAVUS:
        *palOut = gObjectEventPal_FollowerMisdreavusShiny;
        return TRUE;
    case SPECIES_WOBBUFFET:
        *palOut = gObjectEventPal_FollowerWobbuffetShiny;
        return TRUE;
    case SPECIES_GIRAFARIG:
        *palOut = gObjectEventPal_FollowerGirafarigShiny;
        return TRUE;
    case SPECIES_PINECO:
        *palOut = gObjectEventPal_FollowerPinecoShiny;
        return TRUE;
    case SPECIES_FORRETRESS:
        *palOut = gObjectEventPal_FollowerForretressShiny;
        return TRUE;
    case SPECIES_DUNSPARCE:
        *palOut = gObjectEventPal_FollowerDunsparceShiny;
        return TRUE;
    case SPECIES_GLIGAR:
        *palOut = gObjectEventPal_FollowerGligarShiny;
        return TRUE;
    case SPECIES_SNUBBULL:
        *palOut = gObjectEventPal_FollowerSnubbullShiny;
        return TRUE;
    case SPECIES_GRANBULL:
        *palOut = gObjectEventPal_FollowerGranbullShiny;
        return TRUE;
    case SPECIES_QWILFISH:
        *palOut = gObjectEventPal_FollowerQwilfishShiny;
        return TRUE;
    case SPECIES_SCIZOR:
        *palOut = gObjectEventPal_FollowerScizorShiny;
        return TRUE;
    case SPECIES_SHUCKLE:
        *palOut = gObjectEventPal_FollowerShuckleShiny;
        return TRUE;
    case SPECIES_HERACROSS:
        *palOut = gObjectEventPal_FollowerHeracrossShiny;
        return TRUE;
    case SPECIES_SNEASEL:
        *palOut = gObjectEventPal_FollowerSneaselShiny;
        return TRUE;
    case SPECIES_TEDDIURSA:
        *palOut = gObjectEventPal_FollowerTeddiursaShiny;
        return TRUE;
    case SPECIES_URSARING:
        *palOut = gObjectEventPal_FollowerUrsaringShiny;
        return TRUE;
    case SPECIES_SLUGMA:
        *palOut = gObjectEventPal_FollowerSlugmaShiny;
        return TRUE;
    case SPECIES_MAGCARGO:
        *palOut = gObjectEventPal_FollowerMagcargoShiny;
        return TRUE;
    case SPECIES_SWINUB:
        *palOut = gObjectEventPal_FollowerSwinubShiny;
        return TRUE;
    case SPECIES_PILOSWINE:
        *palOut = gObjectEventPal_FollowerPiloswineShiny;
        return TRUE;
    case SPECIES_CORSOLA:
        *palOut = gObjectEventPal_FollowerCorsolaShiny;
        return TRUE;
    case SPECIES_REMORAID:
        *palOut = gObjectEventPal_FollowerRemoraidShiny;
        return TRUE;
    case SPECIES_OCTILLERY:
        *palOut = gObjectEventPal_FollowerOctilleryShiny;
        return TRUE;
    case SPECIES_DELIBIRD:
        *palOut = gObjectEventPal_FollowerDelibirdShiny;
        return TRUE;
    case SPECIES_MANTINE:
        *palOut = gObjectEventPal_FollowerMantineShiny;
        return TRUE;
    case SPECIES_SKARMORY:
        *palOut = gObjectEventPal_FollowerSkarmoryShiny;
        return TRUE;
    case SPECIES_HOUNDOUR:
        *palOut = gObjectEventPal_FollowerHoundourShiny;
        return TRUE;
    case SPECIES_HOUNDOOM:
        *palOut = gObjectEventPal_FollowerHoundoomShiny;
        return TRUE;
    case SPECIES_KINGDRA:
        *palOut = gObjectEventPal_FollowerKingdraShiny;
        return TRUE;
    case SPECIES_PHANPY:
        *palOut = gObjectEventPal_FollowerPhanpyShiny;
        return TRUE;
    case SPECIES_DONPHAN:
        *palOut = gObjectEventPal_FollowerDonphanShiny;
        return TRUE;
    case SPECIES_PORYGON2:
        *palOut = gObjectEventPal_FollowerPorygon2Shiny;
        return TRUE;
    case SPECIES_STANTLER:
        *palOut = gObjectEventPal_FollowerStantlerShiny;
        return TRUE;
    case SPECIES_SMEARGLE:
        *palOut = gObjectEventPal_FollowerSmeargleShiny;
        return TRUE;
    case SPECIES_TYROGUE:
        *palOut = gObjectEventPal_FollowerTyrogueShiny;
        return TRUE;
    case SPECIES_HITMONTOP:
        *palOut = gObjectEventPal_FollowerHitmontopShiny;
        return TRUE;
    case SPECIES_SMOOCHUM:
        *palOut = gObjectEventPal_FollowerSmoochumShiny;
        return TRUE;
    case SPECIES_ELEKID:
        *palOut = gObjectEventPal_FollowerElekidShiny;
        return TRUE;
    case SPECIES_MAGBY:
        *palOut = gObjectEventPal_FollowerMagbyShiny;
        return TRUE;
    case SPECIES_MILTANK:
        *palOut = gObjectEventPal_FollowerMiltankShiny;
        return TRUE;
    case SPECIES_BLISSEY:
        *palOut = gObjectEventPal_FollowerBlisseyShiny;
        return TRUE;
    case SPECIES_RAIKOU:
        *palOut = gObjectEventPal_FollowerRaikouShiny;
        return TRUE;
    case SPECIES_ENTEI:
        *palOut = gObjectEventPal_FollowerEnteiShiny;
        return TRUE;
    case SPECIES_SUICUNE:
        *palOut = gObjectEventPal_FollowerSuicuneShiny;
        return TRUE;
    case SPECIES_LARVITAR:
        *palOut = gObjectEventPal_FollowerLarvitarShiny;
        return TRUE;
    case SPECIES_PUPITAR:
        *palOut = gObjectEventPal_FollowerPupitarShiny;
        return TRUE;
    case SPECIES_TYRANITAR:
        *palOut = gObjectEventPal_FollowerTyranitarShiny;
        return TRUE;
    case SPECIES_CELEBI:
        *palOut = gObjectEventPal_FollowerCelebiShiny;
        return TRUE;
    case SPECIES_GROVYLE:
        *palOut = gObjectEventPal_FollowerGrovyleShiny;
        return TRUE;
    case SPECIES_SCEPTILE:
        *palOut = gObjectEventPal_FollowerSceptileShiny;
        return TRUE;
    case SPECIES_COMBUSKEN:
        *palOut = gObjectEventPal_FollowerCombuskenShiny;
        return TRUE;
    case SPECIES_BLAZIKEN:
        *palOut = gObjectEventPal_FollowerBlazikenShiny;
        return TRUE;
    case SPECIES_MARSHTOMP:
        *palOut = gObjectEventPal_FollowerMarshtompShiny;
        return TRUE;
    case SPECIES_SWAMPERT:
        *palOut = gObjectEventPal_FollowerSwampertShiny;
        return TRUE;
    case SPECIES_POOCHYENA:
        *palOut = gObjectEventPal_FollowerPoochyenaShiny;
        return TRUE;
    case SPECIES_MIGHTYENA:
        *palOut = gObjectEventPal_FollowerMightyenaShiny;
        return TRUE;
    case SPECIES_ZIGZAGOON:
        *palOut = gObjectEventPal_FollowerZigzagoonShiny;
        return TRUE;
    case SPECIES_LINOONE:
        *palOut = gObjectEventPal_FollowerLinooneShiny;
        return TRUE;
    case SPECIES_WURMPLE:
        *palOut = gObjectEventPal_FollowerWurmpleShiny;
        return TRUE;
    case SPECIES_SILCOON:
        *palOut = gObjectEventPal_FollowerSilcoonShiny;
        return TRUE;
    case SPECIES_BEAUTIFLY:
        *palOut = gObjectEventPal_FollowerBeautiflyShiny;
        return TRUE;
    case SPECIES_CASCOON:
        *palOut = gObjectEventPal_FollowerCascoonShiny;
        return TRUE;
    case SPECIES_DUSTOX:
        *palOut = gObjectEventPal_FollowerDustoxShiny;
        return TRUE;
    case SPECIES_LOTAD:
        *palOut = gObjectEventPal_FollowerLotadShiny;
        return TRUE;
    case SPECIES_LOMBRE:
        *palOut = gObjectEventPal_FollowerLombreShiny;
        return TRUE;
    case SPECIES_LUDICOLO:
        *palOut = gObjectEventPal_FollowerLudicoloShiny;
        return TRUE;
    case SPECIES_SEEDOT:
        *palOut = gObjectEventPal_FollowerSeedotShiny;
        return TRUE;
    case SPECIES_NUZLEAF:
        *palOut = gObjectEventPal_FollowerNuzleafShiny;
        return TRUE;
    case SPECIES_SHIFTRY:
        *palOut = gObjectEventPal_FollowerShiftryShiny;
        return TRUE;
    case SPECIES_NINCADA:
        *palOut = gObjectEventPal_FollowerNincadaShiny;
        return TRUE;
    case SPECIES_NINJASK:
        *palOut = gObjectEventPal_FollowerNinjaskShiny;
        return TRUE;
    case SPECIES_SHEDINJA:
        *palOut = gObjectEventPal_FollowerShedinjaShiny;
        return TRUE;
    case SPECIES_TAILLOW:
        *palOut = gObjectEventPal_FollowerTaillowShiny;
        return TRUE;
    case SPECIES_SWELLOW:
        *palOut = gObjectEventPal_FollowerSwellowShiny;
        return TRUE;
    case SPECIES_SHROOMISH:
        *palOut = gObjectEventPal_FollowerShroomishShiny;
        return TRUE;
    case SPECIES_BRELOOM:
        *palOut = gObjectEventPal_FollowerBreloomShiny;
        return TRUE;
    case SPECIES_SPINDA:
        *palOut = gObjectEventPal_FollowerSpindaShiny;
        return TRUE;
    case SPECIES_WINGULL:
        *palOut = gObjectEventPal_FollowerWingullShiny;
        return TRUE;
    case SPECIES_PELIPPER:
        *palOut = gObjectEventPal_FollowerPelipperShiny;
        return TRUE;
    case SPECIES_SURSKIT:
        *palOut = gObjectEventPal_FollowerSurskitShiny;
        return TRUE;
    case SPECIES_MASQUERAIN:
        *palOut = gObjectEventPal_FollowerMasquerainShiny;
        return TRUE;
    case SPECIES_WAILMER:
        *palOut = gObjectEventPal_FollowerWailmerShiny;
        return TRUE;
    case SPECIES_SKITTY:
        *palOut = gObjectEventPal_FollowerSkittyShiny;
        return TRUE;
    case SPECIES_DELCATTY:
        *palOut = gObjectEventPal_FollowerDelcattyShiny;
        return TRUE;
    case SPECIES_KECLEON:
        *palOut = gObjectEventPal_FollowerKecleonShiny;
        return TRUE;
    case SPECIES_BALTOY:
        *palOut = gObjectEventPal_FollowerBaltoyShiny;
        return TRUE;
    case SPECIES_CLAYDOL:
        *palOut = gObjectEventPal_FollowerClaydolShiny;
        return TRUE;
    case SPECIES_NOSEPASS:
        *palOut = gObjectEventPal_FollowerNosepassShiny;
        return TRUE;
    case SPECIES_TORKOAL:
        *palOut = gObjectEventPal_FollowerTorkoalShiny;
        return TRUE;
    case SPECIES_SABLEYE:
        *palOut = gObjectEventPal_FollowerSableyeShiny;
        return TRUE;
    case SPECIES_BARBOACH:
        *palOut = gObjectEventPal_FollowerBarboachShiny;
        return TRUE;
    case SPECIES_WHISCASH:
        *palOut = gObjectEventPal_FollowerWhiscashShiny;
        return TRUE;
    case SPECIES_LUVDISC:
        *palOut = gObjectEventPal_FollowerLuvdiscShiny;
        return TRUE;
    case SPECIES_CORPHISH:
        *palOut = gObjectEventPal_FollowerCorphishShiny;
        return TRUE;
    case SPECIES_CRAWDAUNT:
        *palOut = gObjectEventPal_FollowerCrawdauntShiny;
        return TRUE;
    case SPECIES_FEEBAS:
        *palOut = gObjectEventPal_FollowerFeebasShiny;
        return TRUE;
    case SPECIES_MILOTIC:
        *palOut = gObjectEventPal_FollowerMiloticShiny;
        return TRUE;
    case SPECIES_CARVANHA:
        *palOut = gObjectEventPal_FollowerCarvanhaShiny;
        return TRUE;
    case SPECIES_SHARPEDO:
        *palOut = gObjectEventPal_FollowerSharpedoShiny;
        return TRUE;
    case SPECIES_TRAPINCH:
        *palOut = gObjectEventPal_FollowerTrapinchShiny;
        return TRUE;
    case SPECIES_VIBRAVA:
        *palOut = gObjectEventPal_FollowerVibravaShiny;
        return TRUE;
    case SPECIES_FLYGON:
        *palOut = gObjectEventPal_FollowerFlygonShiny;
        return TRUE;
    case SPECIES_MAKUHITA:
        *palOut = gObjectEventPal_FollowerMakuhitaShiny;
        return TRUE;
    case SPECIES_HARIYAMA:
        *palOut = gObjectEventPal_FollowerHariyamaShiny;
        return TRUE;
    case SPECIES_ELECTRIKE:
        *palOut = gObjectEventPal_FollowerElectrikeShiny;
        return TRUE;
    case SPECIES_MANECTRIC:
        *palOut = gObjectEventPal_FollowerManectricShiny;
        return TRUE;
    case SPECIES_NUMEL:
        *palOut = gObjectEventPal_FollowerNumelShiny;
        return TRUE;
    case SPECIES_CAMERUPT:
        *palOut = gObjectEventPal_FollowerCameruptShiny;
        return TRUE;
    case SPECIES_SPHEAL:
        *palOut = gObjectEventPal_FollowerSphealShiny;
        return TRUE;
    case SPECIES_SEALEO:
        *palOut = gObjectEventPal_FollowerSealeoShiny;
        return TRUE;
    case SPECIES_WALREIN:
        *palOut = gObjectEventPal_FollowerWalreinShiny;
        return TRUE;
    case SPECIES_CACNEA:
        *palOut = gObjectEventPal_FollowerCacneaShiny;
        return TRUE;
    case SPECIES_CACTURNE:
        *palOut = gObjectEventPal_FollowerCacturneShiny;
        return TRUE;
    case SPECIES_SNORUNT:
        *palOut = gObjectEventPal_FollowerSnoruntShiny;
        return TRUE;
    case SPECIES_GLALIE:
        *palOut = gObjectEventPal_FollowerGlalieShiny;
        return TRUE;
    case SPECIES_LUNATONE:
        *palOut = gObjectEventPal_FollowerLunatoneShiny;
        return TRUE;
    case SPECIES_SOLROCK:
        *palOut = gObjectEventPal_FollowerSolrockShiny;
        return TRUE;
    case SPECIES_AZURILL:
        *palOut = gObjectEventPal_FollowerAzurillShiny;
        return TRUE;
    case SPECIES_SPOINK:
        *palOut = gObjectEventPal_FollowerSpoinkShiny;
        return TRUE;
    case SPECIES_GRUMPIG:
        *palOut = gObjectEventPal_FollowerGrumpigShiny;
        return TRUE;
    case SPECIES_PLUSLE:
        *palOut = gObjectEventPal_FollowerPlusleShiny;
        return TRUE;
    case SPECIES_MINUN:
        *palOut = gObjectEventPal_FollowerMinunShiny;
        return TRUE;
    case SPECIES_MAWILE:
        *palOut = gObjectEventPal_FollowerMawileShiny;
        return TRUE;
    case SPECIES_MEDITITE:
        *palOut = gObjectEventPal_FollowerMedititeShiny;
        return TRUE;
    case SPECIES_MEDICHAM:
        *palOut = gObjectEventPal_FollowerMedichamShiny;
        return TRUE;
    case SPECIES_SWABLU:
        *palOut = gObjectEventPal_FollowerSwabluShiny;
        return TRUE;
    case SPECIES_ALTARIA:
        *palOut = gObjectEventPal_FollowerAltariaShiny;
        return TRUE;
    case SPECIES_WYNAUT:
        *palOut = gObjectEventPal_FollowerWynautShiny;
        return TRUE;
    case SPECIES_DUSKULL:
        *palOut = gObjectEventPal_FollowerDuskullShiny;
        return TRUE;
    case SPECIES_DUSCLOPS:
        *palOut = gObjectEventPal_FollowerDusclopsShiny;
        return TRUE;
    case SPECIES_ROSELIA:
        *palOut = gObjectEventPal_FollowerRoseliaShiny;
        return TRUE;
    case SPECIES_SLAKOTH:
        *palOut = gObjectEventPal_FollowerSlakothShiny;
        return TRUE;
    case SPECIES_VIGOROTH:
        *palOut = gObjectEventPal_FollowerVigorothShiny;
        return TRUE;
    case SPECIES_SLAKING:
        *palOut = gObjectEventPal_FollowerSlakingShiny;
        return TRUE;
    case SPECIES_GULPIN:
        *palOut = gObjectEventPal_FollowerGulpinShiny;
        return TRUE;
    case SPECIES_SWALOT:
        *palOut = gObjectEventPal_FollowerSwalotShiny;
        return TRUE;
    case SPECIES_TROPIUS:
        *palOut = gObjectEventPal_FollowerTropiusShiny;
        return TRUE;
    case SPECIES_WHISMUR:
        *palOut = gObjectEventPal_FollowerWhismurShiny;
        return TRUE;
    case SPECIES_LOUDRED:
        *palOut = gObjectEventPal_FollowerLoudredShiny;
        return TRUE;
    case SPECIES_EXPLOUD:
        *palOut = gObjectEventPal_FollowerExploudShiny;
        return TRUE;
    case SPECIES_CLAMPERL:
        *palOut = gObjectEventPal_FollowerClamperlShiny;
        return TRUE;
    case SPECIES_HUNTAIL:
        *palOut = gObjectEventPal_FollowerHuntailShiny;
        return TRUE;
    case SPECIES_GOREBYSS:
        *palOut = gObjectEventPal_FollowerGorebyssShiny;
        return TRUE;
    case SPECIES_ABSOL:
        *palOut = gObjectEventPal_FollowerAbsolShiny;
        return TRUE;
    case SPECIES_SHUPPET:
        *palOut = gObjectEventPal_FollowerShuppetShiny;
        return TRUE;
    case SPECIES_BANETTE:
        *palOut = gObjectEventPal_FollowerBanetteShiny;
        return TRUE;
    case SPECIES_SEVIPER:
        *palOut = gObjectEventPal_FollowerSeviperShiny;
        return TRUE;
    case SPECIES_ZANGOOSE:
        *palOut = gObjectEventPal_FollowerZangooseShiny;
        return TRUE;
    case SPECIES_RELICANTH:
        *palOut = gObjectEventPal_FollowerRelicanthShiny;
        return TRUE;
    case SPECIES_ARON:
        *palOut = gObjectEventPal_FollowerAronShiny;
        return TRUE;
    case SPECIES_LAIRON:
        *palOut = gObjectEventPal_FollowerLaironShiny;
        return TRUE;
    case SPECIES_AGGRON:
        *palOut = gObjectEventPal_FollowerAggronShiny;
        return TRUE;
    case SPECIES_CASTFORM:
        *palOut = gObjectEventPal_FollowerCastformShiny;
        return TRUE;
    case SPECIES_VOLBEAT:
        *palOut = gObjectEventPal_FollowerVolbeatShiny;
        return TRUE;
    case SPECIES_ILLUMISE:
        *palOut = gObjectEventPal_FollowerIllumiseShiny;
        return TRUE;
    case SPECIES_LILEEP:
        *palOut = gObjectEventPal_FollowerLileepShiny;
        return TRUE;
    case SPECIES_CRADILY:
        *palOut = gObjectEventPal_FollowerCradilyShiny;
        return TRUE;
    case SPECIES_ANORITH:
        *palOut = gObjectEventPal_FollowerAnorithShiny;
        return TRUE;
    case SPECIES_ARMALDO:
        *palOut = gObjectEventPal_FollowerArmaldoShiny;
        return TRUE;
    case SPECIES_RALTS:
        *palOut = gObjectEventPal_FollowerRaltsShiny;
        return TRUE;
    case SPECIES_KIRLIA:
        *palOut = gObjectEventPal_FollowerKirliaShiny;
        return TRUE;
    case SPECIES_GARDEVOIR:
        *palOut = gObjectEventPal_FollowerGardevoirShiny;
        return TRUE;
    case SPECIES_BAGON:
        *palOut = gObjectEventPal_FollowerBagonShiny;
        return TRUE;
    case SPECIES_SHELGON:
        *palOut = gObjectEventPal_FollowerShelgonShiny;
        return TRUE;
    case SPECIES_SALAMENCE:
        *palOut = gObjectEventPal_FollowerSalamenceShiny;
        return TRUE;
    case SPECIES_BELDUM:
        *palOut = gObjectEventPal_FollowerBeldumShiny;
        return TRUE;
    case SPECIES_METANG:
        *palOut = gObjectEventPal_FollowerMetangShiny;
        return TRUE;
    case SPECIES_METAGROSS:
        *palOut = gObjectEventPal_FollowerMetagrossShiny;
        return TRUE;
    case SPECIES_REGIROCK:
        *palOut = gObjectEventPal_FollowerRegirockShiny;
        return TRUE;
    case SPECIES_REGICE:
        *palOut = gObjectEventPal_FollowerRegiceShiny;
        return TRUE;
    case SPECIES_REGISTEEL:
        *palOut = gObjectEventPal_FollowerRegisteelShiny;
        return TRUE;
    case SPECIES_LATIAS:
        *palOut = gObjectEventPal_FollowerLatiasShiny;
        return TRUE;
    case SPECIES_LATIOS:
        *palOut = gObjectEventPal_FollowerLatiosShiny;
        return TRUE;
    case SPECIES_JIRACHI:
        *palOut = gObjectEventPal_FollowerJirachiShiny;
        return TRUE;
    case SPECIES_DEOXYS:
        *palOut = gObjectEventPal_FollowerDeoxysShiny;
        return TRUE;
    case SPECIES_CHIMECHO:
        *palOut = gObjectEventPal_FollowerChimechoShiny;
        return TRUE;
    case SPECIES_STEELIX:
        *palOut = gObjectEventPal_FollowerSteelixShiny;
        return TRUE;
    case SPECIES_LUGIA:
        *palOut = gObjectEventPal_FollowerLugiaShiny;
        return TRUE;
    case SPECIES_HO_OH:
        *palOut = gObjectEventPal_FollowerHoOhShiny;
        return TRUE;
    case SPECIES_WAILORD:
        *palOut = gObjectEventPal_FollowerWailordShiny;
        return TRUE;
    case SPECIES_KYOGRE:
        *palOut = gObjectEventPal_FollowerKyogreShiny;
        return TRUE;
    case SPECIES_GROUDON:
        *palOut = gObjectEventPal_FollowerGroudonShiny;
        return TRUE;
    case SPECIES_RAYQUAZA:
        *palOut = gObjectEventPal_FollowerRayquazaShiny;
        return TRUE;
    case SPECIES_UNOWN:
    {
#define P1 gObjectEventPal_FollowerUnown1Shiny
#define P2 gObjectEventPal_FollowerUnown2Shiny
        static const u16 *const sShinyPals[NUM_UNOWN_FORMS] = {
            P1, P1, P2, P2, P1, P2, P2, P2, P1, P1, P1, P1, P1, P1, P2, P1, P1, P2, P1, P1, P1, P1, P1, P1, P1, P1, P1, P1
        };
#undef P1
#undef P2
        u32 personality = GetMonData(&gPlayerParty[0], MON_DATA_PERSONALITY);
        *palOut = sShinyPals[GET_UNOWN_LETTER(personality)];
        return TRUE;
    }
    default:
        return FALSE;
    }
}
bool8 GetFollowerSpriteData(u16 species,
                             const u16 **palOut,
                             const struct SpriteFrameImage **picOut)
{
    if (!GetFollowerSpriteInfo(species, palOut, picOut))
        return FALSE;
    {
        const u16 *shinyPal;
        if (gPlayerPartyCount > 0 && IsMonShiny(&gPlayerParty[0]) && GetFollowerShinyPal(species, &shinyPal))
            *palOut = shinyPal;
    }
    return TRUE;
}

// ---------------------------------------------------------------------------
// State
// ---------------------------------------------------------------------------

// All zero-initialized (.bss) — no non-zero static initializers, which would go
// into .data and be discarded by the GBA linker script.
static EWRAM_DATA bool8 sFollowerActive;
static EWRAM_DATA u8    sFollowerObjectEventId;
static EWRAM_DATA u16   sFollowerSpecies;
static EWRAM_DATA u8    sFollowerTaskId;
static EWRAM_DATA bool8 sFollowerNeedsReveal;
static EWRAM_DATA u8    sFollowerRevealDelayTimer;
static EWRAM_DATA bool8 sFollowerDoorNeedsClose;

// Player position tracking for coord-change-based step detection.
// currentCoords updates at the start of each movement action (the tile is
// claimed), so comparing against sLastPlayerX/Y detects any step — both
// player-input and applymovement-scripted — one VDraw frame after it begins.
static EWRAM_DATA s16 sLastPlayerX;
static EWRAM_DATA s16 sLastPlayerY;
// Guard for ledge-jump coord changes.  FollowerJumpLedge pushes its own
// entries and records the post-jump destination here so the coord-change
// detector can skip the jump coord-change without re-queuing it.
static EWRAM_DATA bool8 sFollowerJumpPending;
static EWRAM_DATA s16   sFollowerJumpDestX;
static EWRAM_DATA s16   sFollowerJumpDestY;
// Set when the follower jumps simultaneously with the player (side-by-side).
// The first player step after a simultaneous jump would otherwise drag the
// follower onto the player's row/column, so that one coord-change is skipped.
static EWRAM_DATA bool8 sFollowerJumpSimultaneous;
// Set while Task_FollowerTeleport is active so Task_FollowerUpdate returns
// early and DespawnFollower knows to clean up the ball sprite and task.
static EWRAM_DATA bool8 sFollowerTeleporting;
static EWRAM_DATA u8    sFollowerTeleportTaskId;
// Set while Task_FollowerRecall is playing the recall-into-ball animation
// (player mounted bike/surf).  Prevents re-triggering each frame.
static EWRAM_DATA bool8 sFollowerRecalling;
static EWRAM_DATA u8    sFollowerRecallTaskId;
// Set while on bike/surf so that dismounting triggers the teleport-ball
// respawn.  Kept separate from sFollowerNeedsReveal (which is the indoor
// door-reveal countdown) so the two paths don't collide.
static EWRAM_DATA bool8 sFollowerNeedsRespawn;
// Set by SpawnFollower so the first player step triggers a pokeball-open
// animation at the follower's spawn tile instead of a silent pop-in.
static EWRAM_DATA bool8 sFollowerNeedsBallReveal;
static EWRAM_DATA u8    sFollowerSpawnBallTaskId;
// Set by SpawnFollowerFromLeadMonOnLoad for large followers so the ball reveal
// fires only on the first player-input step, skipping the scripted door-exit walk.
static EWRAM_DATA bool8 sFollowerNeedsInputBallReveal;
// Set while Task_FollowerPkmnCenterRecall is animating the follower into the counter ball.
static EWRAM_DATA bool8 sFollowerPkmnCenterRecalling;
static EWRAM_DATA u8    sFollowerPkmnCenterRecallTaskId;
// Set after the counter ball is removed and the follower is hidden; cleared by FollowerPkmnCenterRelease.
static EWRAM_DATA bool8 sFollowerPkmnCenterInBall;

// Movement queue: buffers target tile positions fed by FollowerStep/JumpLedge.
// Storing tile coords instead of actions lets the follower trace the player's
// actual path — direction is computed at dequeue time from the position delta.
#define FOLLOWER_STEP_WALK_NORMAL 0
#define FOLLOWER_STEP_WALK_FAST   1
#define FOLLOWER_STEP_WALK_FASTER 2
#define FOLLOWER_STEP_RUN         3
#define FOLLOWER_STEP_JUMP2       4  // 2-tile ledge jump, walk speed
#define FOLLOWER_STEP_JUMP2_FAST  5  // 2-tile ledge jump, run speed (16 frames)

struct FollowerQueueEntry {
    s16 x;
    s16 y;
    u8  kind; // FOLLOWER_STEP_*
};

// Capacity=8: ledge jumps push 2 entries at once, so the extra headroom
// prevents drops when the player runs into consecutive ledges.
#define FOLLOWER_QUEUE_CAP 8
static struct FollowerQueueEntry sFollowerQueue[FOLLOWER_QUEUE_CAP];
static u8 sFollowerQueueHead;
static u8 sFollowerQueueSize;

// Teleport: local ID for the Pokéball effect sprite, gap threshold (Chebyshev),
// and how long (frames) the ball lingers at departure and arrival.
#define LOCAL_ID_FOLLOWER_BALL              0xFD
#define FOLLOWER_TELEPORT_DIST              3
#define FOLLOWER_BALL_FRAMES                7
// Frames for the sprite arc animation toward the ball.
#define FOLLOWER_PKMNCENTER_ARC_FRAMES      16
// Peak upward pixel offset of the arc at its midpoint.
#define FOLLOWER_PKMNCENTER_ARC_HEIGHT      12
// Frames to hold at the ball position before vanishing.
#define FOLLOWER_PKMNCENTER_DELAY_FRAMES    20

// Forward declarations for static functions used before their definitions.
static void Task_FollowerUpdate(u8 taskId);
static void Task_FollowerTeleport(u8 taskId);
static void Task_FollowerSpawnBall(u8 taskId);
static void Task_FollowerRecall(u8 taskId);
static void Task_FollowerPkmnCenterRecall(u8 taskId);
static void RevealFollower(void);
static void DoSpawnFollower(u16 species, s16 spawnX, s16 spawnY);

// Spawn offset: follower appears one tile behind the player's facing direction.
// Index by DIR_* (1=south,2=north,3=west,4=east); index 0 unused.
static const s8 sSpawnOffsetX[5] = {0,  0,  0,  1, -1};
static const s8 sSpawnOffsetY[5] = {0, -1,  1,  0,  0};

// 2-tile jump delta: movement from the ledge tile in each direction.
static const s8 sJump2DeltaX[5] = {0,  0,  0, -2,  2};
static const s8 sJump2DeltaY[5] = {0,  2, -2,  0,  0};

// ---------------------------------------------------------------------------
// Internal helpers
// ---------------------------------------------------------------------------

static struct ObjectEvent *GetFollowerObjEvent(void)
{
    if (!sFollowerActive)
        return NULL;
    if (sFollowerObjectEventId >= OBJECT_EVENTS_COUNT)
        return NULL;
    if (!gObjectEvents[sFollowerObjectEventId].active)
        return NULL;
    // Guard against the slot being recycled for a map NPC: object events that
    // drift out of camera range are deactivated by the map system, freeing the
    // slot for reuse.  Without this check Task_FollowerUpdate would force walk
    // actions onto whichever NPC inherited the slot.
    if (gObjectEvents[sFollowerObjectEventId].localId != LOCAL_ID_FOLLOWER)
        return NULL;
    return &gObjectEvents[sFollowerObjectEventId];
}

static void QueueClear(void)
{
    sFollowerQueueHead = 0;
    sFollowerQueueSize = 0;
}

static void QueuePush(struct FollowerQueueEntry entry)
{
    if (sFollowerQueueSize >= FOLLOWER_QUEUE_CAP)
        return; // drop if full; player is moving faster than follower can process
    sFollowerQueue[(sFollowerQueueHead + sFollowerQueueSize) % FOLLOWER_QUEUE_CAP] = entry;
    sFollowerQueueSize++;
}

static bool8 QueuePop(struct FollowerQueueEntry *entryOut)
{
    if (sFollowerQueueSize == 0)
        return FALSE;
    *entryOut = sFollowerQueue[sFollowerQueueHead];
    sFollowerQueueHead = (sFollowerQueueHead + 1) % FOLLOWER_QUEUE_CAP;
    sFollowerQueueSize--;
    return TRUE;
}

// ---------------------------------------------------------------------------
// Speed tier helpers
// ---------------------------------------------------------------------------

static u8 ClassifyStepKind(u8 action)
{
    if (action >= MOVEMENT_ACTION_WALK_NORMAL_DOWN && action <= MOVEMENT_ACTION_WALK_NORMAL_RIGHT)
        return FOLLOWER_STEP_WALK_NORMAL;
    if (action >= MOVEMENT_ACTION_WALK_FAST_DOWN && action <= MOVEMENT_ACTION_WALK_FAST_RIGHT)
        return FOLLOWER_STEP_WALK_FAST;
    if (action >= MOVEMENT_ACTION_WALK_FASTER_DOWN && action <= MOVEMENT_ACTION_WALK_FASTER_RIGHT)
        return FOLLOWER_STEP_WALK_FASTER;
    if (action >= MOVEMENT_ACTION_PLAYER_RUN_DOWN && action <= MOVEMENT_ACTION_PLAYER_RUN_RIGHT)
        return FOLLOWER_STEP_RUN;
    return FOLLOWER_STEP_WALK_NORMAL;
}

typedef u8 (*SpeedGetter)(u32);
static const SpeedGetter sSpeedGetters[4] = {
    GetWalkNormalMovementAction,
    GetWalkFastMovementAction,
    GetWalkFasterMovementAction,
    GetWalkFastMovementAction, // RUN: PLAYER_RUN sets animNums only valid on the player sprite; WALK_FAST matches run speed for NPCs
};

// ---------------------------------------------------------------------------
// Per-frame update task
// ---------------------------------------------------------------------------

static void Task_FollowerUpdate(u8 taskId)
{
    struct FollowerQueueEntry entry;
    s16 dx, dy;
    u8 dir, action;
    struct ObjectEvent *follower = GetFollowerObjEvent();

    // Bike/surf/dive block comes BEFORE the follower-NULL guard.
    // After a seamless connection crossing, RemoveObjectEventsOutsideView can
    // cull the follower's ObjEvent slot while the player is still on the bike.
    // We must still arm sFollowerNeedsRespawn so the dismount teleport fires
    // once the player returns on foot, even if follower == NULL here.
    if (!(gPlayerAvatar.flags & PLAYER_AVATAR_FLAG_ON_FOOT))
    {
        struct ObjectEvent *player = &gObjectEvents[gPlayerAvatar.objectEventId];

        // Remounted while a dismount-teleport was waiting: cancel it so
        // sLastPlayerX/Y can be updated below, then re-arm the respawn flag.
        if (sFollowerTeleporting)
        {
            if (sFollowerTeleportTaskId != TASK_NONE
             && gTasks[sFollowerTeleportTaskId].isActive
             && gTasks[sFollowerTeleportTaskId].func == Task_FollowerTeleport)
                DestroyTask(sFollowerTeleportTaskId);
            RemoveObjectEventByLocalId(LOCAL_ID_FOLLOWER_BALL);
            sFollowerTeleporting    = FALSE;
            sFollowerTeleportTaskId = TASK_NONE;
        }

        // First frame on bike/surf with a visible follower: recall into ball.
        if (follower != NULL && !sFollowerRecalling && !follower->invisible)
        {
            sFollowerRecalling    = TRUE;
            sFollowerRecallTaskId = CreateTask(Task_FollowerRecall, 9);
        }
        // While the recall task runs it controls follower->invisible.
        // Once done (or already hidden), keep the follower hidden.
        if (follower != NULL && !sFollowerRecalling)
            follower->invisible = TRUE;
        QueueClear();
        sFollowerJumpPending      = FALSE;
        sFollowerJumpSimultaneous = FALSE;
        sLastPlayerX              = player->currentCoords.x;
        sLastPlayerY              = player->currentCoords.y;
        // Signal the dismount path to spawn via ball animation rather than
        // direct reveal.  Use a dedicated flag to avoid colliding with the
        // indoor door-reveal (sFollowerNeedsReveal) countdown.
        sFollowerNeedsRespawn    = TRUE;
        sFollowerNeedsReveal          = FALSE;
        sFollowerNeedsBallReveal      = FALSE;
        sFollowerNeedsInputBallReveal = FALSE;
        return;
    }

    // On-foot from here.

    // Yield to the teleport/spawn-ball task while it drives the follower.
    if (sFollowerTeleporting)
        return;

    // Yield to the Pokemon Center recall task while it walks the follower into the ball.
    if (sFollowerPkmnCenterRecalling)
        return;

    // First frame on foot after dismounting: spawn the follower via the same
    // ball animation used by gap-triggered teleports.  This check precedes the
    // follower-NULL guard because the ObjEvent may have been culled from view
    // during the bike ride; Task_FollowerTeleport will re-create it.
    if (sFollowerNeedsRespawn)
    {
        sFollowerNeedsRespawn   = FALSE;
        QueueClear();
        sFollowerJumpPending      = FALSE;
        sFollowerJumpSimultaneous = FALSE;
        sFollowerTeleporting      = TRUE;
        sFollowerTeleportTaskId   = CreateTask(Task_FollowerTeleport, 9);
        return;
    }

    // SpawnFollower armed this flag; FollowerStep fires the ball task on input
    // steps.  This fallback catches applymovement-scripted steps that bypass
    // FollowerStep, using sLastPlayerX/Y (the origin tile) for the ball position.
    if (sFollowerNeedsBallReveal)
    {
        struct ObjectEvent *player = &gObjectEvents[gPlayerAvatar.objectEventId];
        if (player->currentCoords.x != sLastPlayerX || player->currentCoords.y != sLastPlayerY)
        {
            sFollowerNeedsBallReveal = FALSE;
            // Do not update sLastPlayerX/Y here — Task_FollowerSpawnBall state 0
            // reads them as the origin tile for the ball position, then syncs.
            sFollowerTeleporting     = TRUE;
            sFollowerSpawnBallTaskId = CreateTask(Task_FollowerSpawnBall, 9);
        }
        return;
    }

    if (follower == NULL)
        return;

    if (sFollowerRevealDelayTimer > 0 && --sFollowerRevealDelayTimer == 0)
        ShowFollowerForEscalator();

    // Scripted sequences (lockall, cutscenes) call FreezeObjectEvents, which sets
    // the frozen flag and pauses sprite animations on all non-player object events.
    // The follower uses MOVEMENT_TYPE_NONE so it won't wander when unfrozen —
    // unfreeze it every frame so held movement and sprite animation always process.
    UnfreezeObjectEvent(follower);

    // Detect any player step — input-driven OR applymovement-scripted.
    // AnimateSprites (which updates currentCoords) runs after RunTasks in the
    // same VDraw frame, so this fires one frame after the step begins — the
    // slight lag is invisible since the follower is already one tile behind.
    {
        struct ObjectEvent *player;
        struct FollowerQueueEntry stepEntry;
        bool8 isJumpDest;

        player = &gObjectEvents[gPlayerAvatar.objectEventId];
        if (player->currentCoords.x != sLastPlayerX || player->currentCoords.y != sLastPlayerY)
        {
            // The player's jump destination was already pushed by FollowerJumpLedge;
            // suppress it here to avoid double-queuing the post-jump coord change.
            isJumpDest = (sFollowerJumpPending &&
                          player->currentCoords.x == sFollowerJumpDestX &&
                          player->currentCoords.y == sFollowerJumpDestY);
            if (isJumpDest)
                sFollowerJumpPending = FALSE;
            if (!isJumpDest)
            {
                // After a simultaneous jump the follower and player land on
                // different rows/columns.  The first player step would push the
                // player's landing tile as the walk target, pulling the follower
                // onto the player's row.  Skip that one entry so the follower
                // stays on its own path; subsequent steps resume normal trailing.
                if (sFollowerJumpSimultaneous)
                    sFollowerJumpSimultaneous = FALSE;
                else
                {
                    RevealFollower();
                    stepEntry.x    = sLastPlayerX;
                    stepEntry.y    = sLastPlayerY;
                    stepEntry.kind = ClassifyStepKind(ObjectEventGetHeldMovementActionId(player));
                    QueuePush(stepEntry);
                }
            }
            // Large follower on map entry: the scripted door-exit step just
            // completed.  Close the door the player walked out of — sLastPlayerX/Y
            // still points at the door tile before the coord update below.
            if (sFollowerNeedsInputBallReveal)
                FieldAnimateDoorClose(sLastPlayerX, sLastPlayerY);
            sLastPlayerX = player->currentCoords.x;
            sLastPlayerY = player->currentCoords.y;
        }
    }

    // If the gap (Chebyshev distance) exceeds the threshold, teleport the follower
    // behind the player with a Pokéball visual rather than letting it fall further behind.
    {
        struct ObjectEvent *player;
        s16 gapDx, gapDy, chebyshev;

        player  = &gObjectEvents[gPlayerAvatar.objectEventId];
        gapDx   = player->currentCoords.x - follower->currentCoords.x;
        gapDy   = player->currentCoords.y - follower->currentCoords.y;
        if (gapDx < 0) gapDx = -gapDx;
        if (gapDy < 0) gapDy = -gapDy;
        chebyshev = (gapDx > gapDy) ? gapDx : gapDy;
        {
            u8 heldAction = ObjectEventGetHeldMovementActionId(follower);
            bool8 midJump = (heldAction >= MOVEMENT_ACTION_JUMP_2_DOWN
                          && heldAction <= MOVEMENT_ACTION_JUMP_2_RIGHT);
            if (!midJump && chebyshev > FOLLOWER_TELEPORT_DIST)
            {
                QueueClear();
                sFollowerJumpPending      = FALSE;
                sFollowerJumpSimultaneous = FALSE;
                sFollowerTeleporting      = TRUE;
                sFollowerTeleportTaskId   = CreateTask(Task_FollowerTeleport, 9);
                return;
            }
        }
    }

    // If the follower is idling in walk-in-place and a queued step just arrived,
    // abort the animation early so the queue is processed this frame rather than
    // waiting up to 16 frames for the walk-in-place to expire naturally.
    {
        u8 actionId = follower->movementActionId;
        if (sFollowerQueueSize > 0
         && actionId >= MOVEMENT_ACTION_WALK_IN_PLACE_NORMAL_DOWN
         && actionId <= MOVEMENT_ACTION_WALK_IN_PLACE_NORMAL_RIGHT)
            ObjectEventClearHeldMovementIfActive(follower);
    }

    if (ObjectEventClearHeldMovementIfFinished(follower))
    {
        if (QueuePop(&entry))
        {
            // Compute direction from follower's current tile to the target tile.
            dx = entry.x - follower->currentCoords.x;
            dy = entry.y - follower->currentCoords.y;
            if      (dx > 0) dir = DIR_EAST;
            else if (dx < 0) dir = DIR_WEST;
            else if (dy > 0) dir = DIR_SOUTH;
            else if (dy < 0) dir = DIR_NORTH;
            else             dir = follower->facingDirection;

            if (dx == 0 && dy == 0)
            {
                action = GetWalkInPlaceNormalMovementAction(dir);
            }
            else
            {
                // Follower is moving away from its current tile — close any door
                // it was standing in (set open by RevealFollower for the entry).
                if (sFollowerDoorNeedsClose)
                {
                    FieldAnimateDoorClose(follower->currentCoords.x,
                                         follower->currentCoords.y);
                    sFollowerDoorNeedsClose = FALSE;
                }
                {
                    bool8 implicitLedge =
                        (((dx == 2 || dx == -2) && dy == 0) && GetLedgeJumpDirection(follower->currentCoords.x + dx / 2, follower->currentCoords.y, dir) != DIR_NONE)
                     || ((dx == 0 && (dy == 2 || dy == -2)) && GetLedgeJumpDirection(follower->currentCoords.x, follower->currentCoords.y + dy / 2, dir) != DIR_NONE);
                    bool8 useFast = (entry.kind == FOLLOWER_STEP_JUMP2_FAST)
                                 || (entry.kind == FOLLOWER_STEP_RUN && implicitLedge);
                    bool8 useJump = useFast || (entry.kind == FOLLOWER_STEP_JUMP2) || implicitLedge;
                    if (useJump)
                        action = useFast ? GetJump2FastMovementAction(dir) : GetJump2MovementAction(dir);
                    else
                        action = sSpeedGetters[entry.kind](dir);
                }
            }
            ObjectEventForceSetHeldMovement(follower, action);
        }
        // get if the player is taking a step
        else
        {
            // No pending movement — hold the follower's own last facing direction.
            // Using player->facingDirection here would snap the follower to face
            // whatever direction the player turned to, even without a step.
            ObjectEventForceSetHeldMovement(follower,
                GetWalkInPlaceNormalMovementAction(follower->facingDirection));
        }
    }
}

// ---------------------------------------------------------------------------
// Teleport task: snaps the follower to the player when the gap grows too large.
// State machine stored in gTasks[taskId].data[]:
//   [0] = current state (0-3)
//   [1] = frame countdown (state 2)
//
// State 0: silently respawn follower at the player's exact tile, invisible.
// State 1: wait for the player to take their next step, then flash the ball.
// State 2: track additional player steps into the queue; count down ball timer.
// State 3: remove ball, reveal follower, done.
// ---------------------------------------------------------------------------

static void Task_FollowerTeleport(u8 taskId)
{
    struct ObjectEvent *follower;
    struct ObjectEvent *player;
    struct FollowerQueueEntry stepEntry;
    u16 savedSpecies;

    switch (gTasks[taskId].data[0])
    {
    case 0:
        // Silently reposition the follower to the player's current tile.
        // No visual at this stage — the ball only appears on the next player step.
        savedSpecies = sFollowerSpecies;
        // Clear the flag so DespawnFollower doesn't kill this task, then restore it.
        sFollowerTeleporting = FALSE;
        DespawnFollower();
        player = &gObjectEvents[gPlayerAvatar.objectEventId];
        DoSpawnFollower(savedSpecies, player->currentCoords.x, player->currentCoords.y);
        sFollowerNeedsReveal = FALSE;
        follower = GetFollowerObjEvent();
        if (follower != NULL)
            follower->invisible = TRUE;
        sFollowerTeleporting    = TRUE;
        sFollowerTeleportTaskId = taskId;
        gTasks[taskId].data[0] = 1;
        break;

    case 1:
        // Wait for the player to begin their next step. The ball spawns at the
        // follower's tile (the player's pre-step position) so it appears at the
        // player's feet, then the follower materialises as they arrive.
        player = &gObjectEvents[gPlayerAvatar.objectEventId];
        if (player->currentCoords.x != sLastPlayerX || player->currentCoords.y != sLastPlayerY)
        {
            SpawnSpecialObjectEventParameterized(
                OBJ_EVENT_GFX_ITEM_BALL,
                MOVEMENT_TYPE_NONE,
                LOCAL_ID_FOLLOWER_BALL,
                sLastPlayerX, sLastPlayerY,
                player->currentElevation);
            PlaySE(SE_BALL_OPEN);
            PlayCry_Normal(sFollowerSpecies, 0);
            sLastPlayerX = player->currentCoords.x;
            sLastPlayerY = player->currentCoords.y;
            gTasks[taskId].data[1] = FOLLOWER_BALL_FRAMES;
            gTasks[taskId].data[0] = 2;
        }
        break;

    case 2:
        // Track any extra player steps so the follower can catch up tile-by-tile
        // after being revealed rather than jumping across a multi-tile gap.
        player = &gObjectEvents[gPlayerAvatar.objectEventId];
        if (player->currentCoords.x != sLastPlayerX || player->currentCoords.y != sLastPlayerY)
        {
            stepEntry.x    = sLastPlayerX;
            stepEntry.y    = sLastPlayerY;
            stepEntry.kind = ClassifyStepKind(ObjectEventGetHeldMovementActionId(player));
            QueuePush(stepEntry);
            sLastPlayerX = player->currentCoords.x;
            sLastPlayerY = player->currentCoords.y;
        }
        if (--gTasks[taskId].data[1] == 0)
            gTasks[taskId].data[0] = 3;
        break;

    case 3:
        RemoveObjectEventByLocalId(LOCAL_ID_FOLLOWER_BALL);
        follower = GetFollowerObjEvent();
        if (follower != NULL)
            follower->invisible = FALSE;
        sFollowerTeleporting    = FALSE;
        sFollowerTeleportTaskId = TASK_NONE;
        DestroyTask(taskId);
        break;
    }
}

// ---------------------------------------------------------------------------
// Spawn-ball task: plays the pokeball-open animation at the follower's spawn
// tile (used by SpawnFollower on field return / party switch).  Unlike the
// teleport task it does NOT reposition the follower — it just hides behind the
// ball, waits FOLLOWER_BALL_FRAMES, then reveals.  Player steps queued during
// the wait let the follower catch up normally once revealed.
// ---------------------------------------------------------------------------
static void Task_FollowerSpawnBall(u8 taskId)
{
    struct ObjectEvent *follower;
    struct ObjectEvent *player;
    struct FollowerQueueEntry stepEntry;

    switch (gTasks[taskId].data[0])
    {
    case 0:
        // Ball spawns at sLastPlayerX/Y — the player's origin tile at the moment
        // FollowerStep fired (before AnimateSprites updated currentCoords).
        // After spawning, sync sLastPlayerX/Y to the player's new position so
        // step-tracking in state 1 starts fresh from the correct tile.
        follower = GetFollowerObjEvent();
        SpawnSpecialObjectEventParameterized(
            OBJ_EVENT_GFX_ITEM_BALL, MOVEMENT_TYPE_NONE, LOCAL_ID_FOLLOWER_BALL,
            sLastPlayerX, sLastPlayerY,
            (follower != NULL) ? follower->currentElevation : 3);
        PlaySE(SE_BALL_OPEN);
        PlayCry_Normal(sFollowerSpecies, 0);
        {
            struct ObjectEvent *p = &gObjectEvents[gPlayerAvatar.objectEventId];
            sLastPlayerX = p->currentCoords.x;
            sLastPlayerY = p->currentCoords.y;
        }
        gTasks[taskId].data[1] = FOLLOWER_BALL_FRAMES;
        gTasks[taskId].data[0] = 1;
        break;

    case 1:
        // Track player steps during the wait so the follower can catch up.
        player = &gObjectEvents[gPlayerAvatar.objectEventId];
        if (player->currentCoords.x != sLastPlayerX || player->currentCoords.y != sLastPlayerY)
        {
            stepEntry.x    = sLastPlayerX;
            stepEntry.y    = sLastPlayerY;
            stepEntry.kind = ClassifyStepKind(ObjectEventGetHeldMovementActionId(player));
            QueuePush(stepEntry);
            sLastPlayerX = player->currentCoords.x;
            sLastPlayerY = player->currentCoords.y;
        }
        if (--gTasks[taskId].data[1] == 0)
            gTasks[taskId].data[0] = 2;
        break;

    case 2:
        RemoveObjectEventByLocalId(LOCAL_ID_FOLLOWER_BALL);
        follower = GetFollowerObjEvent();
        if (follower != NULL)
            follower->invisible = FALSE;
        sFollowerTeleporting     = FALSE;
        sFollowerSpawnBallTaskId = TASK_NONE;
        DestroyTask(taskId);
        break;
    }
}

// ---------------------------------------------------------------------------
// Public API
// ---------------------------------------------------------------------------

bool8 IsFollowerSpawned(void)
{
    return GetFollowerObjEvent() != NULL;
}

u16 GetFollowerSpecies(void)
{
    return sFollowerSpecies;
}

bool8 IsLargeFollower(void)
{
    return sFollowerActive && IsLargeFollowerSpecies(sFollowerSpecies);
}

void SetFollowerSpecies(u16 species)
{
    const u16 *pal;
    const struct SpriteFrameImage *picTable;
    struct ObjectEvent *follower;

    if (!GetFollowerSpriteInfo(species, &pal, &picTable))
        return;

    sFollowerSpecies = species;
    {
        const u16 *shinyPal;
        if (gPlayerPartyCount > 0 && IsMonShiny(&gPlayerParty[0]) && GetFollowerShinyPal(species, &shinyPal))
            pal = shinyPal;
    }
    LoadPalette(pal, OBJ_PLTT_ID(PALSLOT_FOLLOWER), PLTT_SIZE_4BPP);

    // Swap the sprite's image pointer in EWRAM so new tiles load on next frame.
    follower = GetFollowerObjEvent();
    if (follower != NULL)
    {
        gSprites[follower->spriteId].images = picTable;
        gSprites[follower->spriteId].oam.paletteNum = PALSLOT_FOLLOWER;
        if (follower->hasReflection)
            RefreshFollowerReflectionPalette();
        ObjectEventForceSetHeldMovement(follower,
            GetWalkInPlaceNormalMovementAction(follower->facingDirection));
    }
}

// Core spawn: places the follower at (spawnX, spawnY), invisible, queued for reveal.
// Caller must call DespawnFollower() and validate species before calling this.
static void DoSpawnFollower(u16 species, s16 spawnX, s16 spawnY)
{
    const u16 *pal;
    const struct SpriteFrameImage *picTable;
    struct ObjectEvent *player;
    struct ObjectEvent *follower;

    if (!GetFollowerSpriteInfo(species, &pal, &picTable))
        return;
    sFollowerSpecies = species;

    player = &gObjectEvents[gPlayerAvatar.objectEventId];
    sFollowerObjectEventId = SpawnSpecialObjectEventParameterized(
        OBJ_EVENT_GFX_FOLLOWER,
        MOVEMENT_TYPE_NONE,
        LOCAL_ID_FOLLOWER,
        spawnX,
        spawnY,
        player->currentElevation);

    // Must be TRUE before GetFollowerObjEvent() is called below.
    sFollowerActive = TRUE;

    follower = GetFollowerObjEvent();
    if (follower != NULL)
    {
        struct Sprite *spr = &gSprites[follower->spriteId];
        if (IsLargeFollowerSpecies(species))
        {
            // Spawned with 32x32 graphics info; upgrade to 64x64 before first frame.
            // Free the 16-tile allocation and replace with 64 tiles.
            ReallocSpriteTilesIfNotSheet(spr, 64);
            spr->oam.size = SPRITE_SIZE(64x64);
            CalcCenterToCornerVec(spr, spr->oam.shape, spr->oam.size, spr->oam.affineMode);
            SetSubspriteTables(spr, sOamTables_FollowerLarge);
            spr->y2 = 1;
        }
        else
        {
            spr->y2 = 1;
        }
        spr->images = picTable;
        spr->oam.paletteNum = PALSLOT_FOLLOWER;
        follower->invisible = TRUE;
    }
    // Load after spawn so TrySetupObjectEventSprite can't overwrite with the static Bulbasaur entry.
    {
        const u16 *shinyPal;
        if (gPlayerPartyCount > 0 && IsMonShiny(&gPlayerParty[0]) && GetFollowerShinyPal(species, &shinyPal))
            pal = shinyPal;
    }
    LoadPalette(pal, OBJ_PLTT_ID(PALSLOT_FOLLOWER), PLTT_SIZE_4BPP);

    QueueClear();
    sLastPlayerX = player->currentCoords.x;
    sLastPlayerY = player->currentCoords.y;
    sFollowerJumpPending = FALSE;
    sFollowerJumpSimultaneous = FALSE;
    sFollowerNeedsReveal = TRUE;
    sFollowerTaskId = CreateTask(Task_FollowerUpdate, 10);
}

// ---------------------------------------------------------------------------
// Recall task: plays the into-Pokéball animation when the player mounts a
// bike, surfs, or dives.  Spawns the ball at the follower's last tile,
// plays the ball-open sound and cry, hides the follower, then removes the
// ball after FOLLOWER_BALL_FRAMES frames.
// ---------------------------------------------------------------------------
static void Task_FollowerRecall(u8 taskId)
{
    struct ObjectEvent *follower;

    switch (gTasks[taskId].data[0])
    {
    case 0:
        follower = GetFollowerObjEvent();
        if (follower != NULL)
        {
            SpawnSpecialObjectEventParameterized(
                OBJ_EVENT_GFX_ITEM_BALL, MOVEMENT_TYPE_NONE, LOCAL_ID_FOLLOWER_BALL,
                follower->currentCoords.x, follower->currentCoords.y,
                follower->currentElevation);
            PlaySE(SE_BALL_OPEN);
            PlayCry_Normal(sFollowerSpecies, 0);
            follower->invisible = TRUE;
        }
        gTasks[taskId].data[1] = FOLLOWER_BALL_FRAMES;
        gTasks[taskId].data[0] = 1;
        break;
    case 1:
        if (--gTasks[taskId].data[1] == 0)
            gTasks[taskId].data[0] = 2;
        break;
    case 2:
        RemoveObjectEventByLocalId(LOCAL_ID_FOLLOWER_BALL);
        sFollowerRecalling    = FALSE;
        sFollowerRecallTaskId = TASK_NONE;
        DestroyTask(taskId);
        break;
    }
}

// ---------------------------------------------------------------------------
// Pokemon Center recall task: walks/turns the follower toward the counter
// ball, lerps its sprite to the ball's pixel position, then hides it before
// the healing field effect begins.
//
// task data layout:
//   [0] current state
//   [1] ball objectEvent index (for sprite lookup during lerp)
//   [2] multi-use: left-step flag (state 1) | lerp step counter (state 2)
//                | hold-timer (state 3)
//   [3] x pixel delta: ball_eff_x − follower_eff_x at lerp start
// State 0: spawn ball on counter; walk left if follower is directly behind
//          the player (same x), otherwise just face up.
// State 1: wait for walk/face-up; then freeze follower, fix OAM priority so
//          the sprite sorts above counter tiles, calculate pixel delta to ball,
//          play cry, and begin arc.
// State 2: parabolic arc — lerp follower sprite x2/y2 toward ball with an
//          upward bow, over FOLLOWER_PKMNCENTER_ARC_FRAMES frames.
// State 3: hold at ball position for FOLLOWER_PKMNCENTER_DELAY_FRAMES, then
//          hide follower, remove ball, and re-enable the script.
// ---------------------------------------------------------------------------
static void Task_FollowerPkmnCenterRecall(u8 taskId)
{
    struct ObjectEvent *follower = GetFollowerObjEvent();
    struct ObjectEvent *player   = &gObjectEvents[gPlayerAvatar.objectEventId];
    struct Sprite      *follSpr  = (follower != NULL)
                                 ? &gSprites[follower->spriteId] : NULL;

    // Unfreeze only during movement states so held movements can execute.
    // During arc/hold (states 2-3) the follower is frozen to lock its facing.
    if (follower != NULL && gTasks[taskId].data[0] < 2)
        UnfreezeObjectEvent(follower);

    switch (gTasks[taskId].data[0])
    {
    case 0:
    {
        u8 ballObjId = SpawnSpecialObjectEventParameterized(
            OBJ_EVENT_GFX_ITEM_BALL, MOVEMENT_TYPE_NONE, LOCAL_ID_FOLLOWER_BALL,
            player->currentCoords.x,
            player->currentCoords.y - 1,
            player->currentElevation);
        if (ballObjId < OBJECT_EVENTS_COUNT)
        {
            struct ObjectEvent *ballObj = &gObjectEvents[ballObjId];
            struct Sprite *ballSpr = &gSprites[ballObj->spriteId];
            ballSpr->y2 = -12;
            ballSpr->subpriority = 4;
            ballSpr->oam.priority = 0;
            ballSpr->subspriteMode = SUBSPRITES_IGNORE_PRIORITY;
            ballObj->fixedPriority = TRUE;
        }
        gTasks[taskId].data[1] = (s16)ballObjId;

        if (follower != NULL)
        {
            // Behind player (same column): walk left then up to reach the player's row.
            // Already to the side (left or right): face up immediately so state 1 waits for it.
            if (follower->currentCoords.x == player->currentCoords.x)
            {
                // Directly behind: walk left then up, then face up (data[2] counts steps).
                ObjectEventForceSetHeldMovement(follower, MOVEMENT_ACTION_WALK_NORMAL_LEFT);
                gTasks[taskId].data[2] = 2;
            }
            else if (follower->currentCoords.x < player->currentCoords.x)
            {
                // Already left: face up, then arc immediately (data[2]=0 skips extra steps).
                ObjectEventForceSetHeldMovement(follower, MOVEMENT_ACTION_FACE_UP);
                gTasks[taskId].data[2] = 0;
            }
            else
            {
                // Already right: face left, then arc immediately.
                ObjectEventForceSetHeldMovement(follower, MOVEMENT_ACTION_FACE_LEFT);
                gTasks[taskId].data[2] = 0;
            }
        }
        gTasks[taskId].data[0] = 1;
        break;
    }

    case 1:
        if (follower == NULL || ObjectEventClearHeldMovementIfFinished(follower))
        {
            if (gTasks[taskId].data[2] == 2)
            {
                // Walk-left done — walk up to reach the player's row.
                if (follower != NULL)
                    ObjectEventForceSetHeldMovement(follower, MOVEMENT_ACTION_WALK_NORMAL_UP);
                gTasks[taskId].data[2] = 1;
            }
            else if (gTasks[taskId].data[2] == 1)
            {
                // Walk-up done (or already beside player) — face up toward ball.
                if (follower != NULL)
                    ObjectEventForceSetHeldMovement(follower, MOVEMENT_ACTION_FACE_UP);
                gTasks[taskId].data[2] = 0;
            }
            else
            {
                u8 ballObjId = (u8)gTasks[taskId].data[1];
                // Facing done — lock follower, raise OAM priority, compute arc delta.
                if (follower != NULL && follSpr != NULL)
                {
                    follower->fixedPriority = TRUE;
                    follSpr->oam.priority = 0;
                    follSpr->subpriority = 0;
                    follSpr->subspriteMode = SUBSPRITES_IGNORE_PRIORITY;
                    FreezeObjectEvent(follower);
                }
                if (follSpr != NULL && ballObjId < OBJECT_EVENTS_COUNT)
                {
                    struct Sprite *ballSpr = &gSprites[gObjectEvents[ballObjId].spriteId];
                    gTasks[taskId].data[3] =
                        (s16)((ballSpr->x + ballSpr->x2) - (follSpr->x + follSpr->x2));
                    gTasks[taskId].data[4] =
                        (s16)((ballSpr->y + ballSpr->y2) - (follSpr->y + follSpr->y2) - 8);
                }
                else
                {
                    gTasks[taskId].data[3] = 0;
                    gTasks[taskId].data[4] = -16;
                }
                gTasks[taskId].data[2] = 0;
                PlaySE(SE_BALL_OPEN);
                PlayCry_Normal(sFollowerSpecies, 0);
                gTasks[taskId].data[0] = 2;
            }
        }
        break;

    case 2:
    {
        // Parabolic arc toward the ball.
        s16 step = ++gTasks[taskId].data[2];
        s16 n    = FOLLOWER_PKMNCENTER_ARC_FRAMES;
        if (step >= n)
        {
            // Arc done — immediately hide follower so ball is visible during the hold.
            if (follower != NULL)
            {
                follower->invisible = TRUE;
                follower->fixedPriority = FALSE;
            }
            if (follSpr != NULL)
            {
                follSpr->x2 = 0;
                follSpr->y2 = 0;
                follSpr->subspriteMode = SUBSPRITES_ON;
            }
            gTasks[taskId].data[2] = FOLLOWER_PKMNCENTER_DELAY_FRAMES;
            gTasks[taskId].data[0] = 3;
        }
        else if (follSpr != NULL)
        {
            s16 dx  = gTasks[taskId].data[3];
            s16 dy  = gTasks[taskId].data[4];
            s16 arc = (s16)(4 * step * (n - step) * FOLLOWER_PKMNCENTER_ARC_HEIGHT / (n * n));
            follSpr->x2 = (s16)((dx * step) / n);
            follSpr->y2 = (s16)((dy * step) / n - arc);
        }
        break;
    }

    case 3:
        // Hold — ball visible, follower already hidden. Then start healing.
        if (--gTasks[taskId].data[2] == 0)
        {
            RemoveObjectEventByLocalId(LOCAL_ID_FOLLOWER_BALL);
            sFollowerPkmnCenterRecalling    = FALSE;
            sFollowerPkmnCenterRecallTaskId = TASK_NONE;
            sFollowerPkmnCenterInBall       = TRUE;
            ScriptContext_Enable();
            DestroyTask(taskId);
        }
        break;
    }
}

// Starts the Pokemon Center recall animation for the follower.
// Call via `special FollowerPkmnCenterRecall` followed by `waitstate`
// (only when IsFollowerSpawned returned TRUE — the caller is responsible for
// checking so that the waitstate is not emitted when there is no follower).
void FollowerPkmnCenterRecall(void)
{
    if (!IsFollowerSpawned())
        return;
    sFollowerPkmnCenterRecalling    = TRUE;
    sFollowerPkmnCenterRecallTaskId = CreateTask(Task_FollowerPkmnCenterRecall, 9);
}

// Re-queues the follower to appear via Pokéball on the player's next step.
// Safe to call even if no follower was recalled.
void FollowerPkmnCenterRelease(void)
{
    u16 species;
    if (!sFollowerPkmnCenterInBall)
        return;
    sFollowerPkmnCenterInBall = FALSE;
    if (!sFollowerActive)
        return;
    species = sFollowerSpecies;
    SpawnFollower(species);
}

void SpawnFollower(u16 species)
{
    struct ObjectEvent *player;
    // Always despawn first — handles stale EWRAM after soft-reset.
    DespawnFollower();
    // Large followers are suppressed on maps where cycling is not allowed.
    if (IsLargeFollowerSpecies(species) && !Overworld_IsBikingAllowed())
        return;
    player = &gObjectEvents[gPlayerAvatar.objectEventId];
    // Spawn at the player's own tile (invisible), same as SpawnFollowerFromLeadMonOnLoad.
    // The first input step fires FollowerStep which triggers the pokeball-open animation
    // at the player's tile; the follower is then revealed there after the ball plays.
    DoSpawnFollower(species, player->currentCoords.x, player->currentCoords.y);
    sFollowerNeedsReveal     = FALSE;
    sFollowerNeedsBallReveal = TRUE;
}

void DespawnFollower(void)
{
    // Cancel any in-progress recall animation and remove its ball sprite.
    if (sFollowerRecalling)
    {
        if (sFollowerRecallTaskId != TASK_NONE
         && gTasks[sFollowerRecallTaskId].isActive
         && gTasks[sFollowerRecallTaskId].func == Task_FollowerRecall)
            DestroyTask(sFollowerRecallTaskId);
        RemoveObjectEventByLocalId(LOCAL_ID_FOLLOWER_BALL);
        sFollowerRecalling    = FALSE;
        sFollowerRecallTaskId = TASK_NONE;
    }

    // Cancel any in-progress Pokemon Center recall animation.
    if (sFollowerPkmnCenterRecalling || sFollowerPkmnCenterInBall)
    {
        if (sFollowerPkmnCenterRecalling
         && sFollowerPkmnCenterRecallTaskId != TASK_NONE
         && gTasks[sFollowerPkmnCenterRecallTaskId].isActive
         && gTasks[sFollowerPkmnCenterRecallTaskId].func == Task_FollowerPkmnCenterRecall)
            DestroyTask(sFollowerPkmnCenterRecallTaskId);
        // Ball only exists while the task is still running (states 0–2).
        if (sFollowerPkmnCenterRecalling)
            RemoveObjectEventByLocalId(LOCAL_ID_FOLLOWER_BALL);
        sFollowerPkmnCenterRecalling    = FALSE;
        sFollowerPkmnCenterRecallTaskId = TASK_NONE;
        sFollowerPkmnCenterInBall       = FALSE;
    }

    // Cancel any in-progress teleport or spawn-ball and remove the ball sprite.
    if (sFollowerTeleporting)
    {
        if (sFollowerTeleportTaskId != TASK_NONE
         && gTasks[sFollowerTeleportTaskId].isActive
         && gTasks[sFollowerTeleportTaskId].func == Task_FollowerTeleport)
            DestroyTask(sFollowerTeleportTaskId);
        if (sFollowerSpawnBallTaskId != TASK_NONE
         && gTasks[sFollowerSpawnBallTaskId].isActive
         && gTasks[sFollowerSpawnBallTaskId].func == Task_FollowerSpawnBall)
            DestroyTask(sFollowerSpawnBallTaskId);
        RemoveObjectEventByLocalId(LOCAL_ID_FOLLOWER_BALL);
        sFollowerTeleporting     = FALSE;
        sFollowerTeleportTaskId  = TASK_NONE;
        sFollowerSpawnBallTaskId = TASK_NONE;
    }
    sFollowerNeedsBallReveal      = FALSE;
    sFollowerNeedsInputBallReveal = FALSE;

    // Only destroy the task if it is confirmed to be ours — avoids clobbering
    // unrelated tasks when sFollowerTaskId is stale after a soft reset.
    if (sFollowerTaskId != TASK_NONE
     && gTasks[sFollowerTaskId].isActive
     && gTasks[sFollowerTaskId].func == Task_FollowerUpdate)
    {
        DestroyTask(sFollowerTaskId);
    }
    sFollowerTaskId = TASK_NONE;

    // Scan by localId only — avoids mapNum/mapGroup mismatch and the FlagSet
    // side-effect of RemoveObjectEventByLocalIdAndMap.
    RemoveObjectEventByLocalId(LOCAL_ID_FOLLOWER);

    sFollowerActive = FALSE;
    sFollowerObjectEventId = 0;
    sFollowerSpecies = SPECIES_NONE;
    sFollowerNeedsReveal = FALSE;
    sFollowerRevealDelayTimer = 0;
    sFollowerNeedsRespawn = FALSE;
    sFollowerDoorNeedsClose = FALSE;
    sFollowerJumpPending = FALSE;
    sFollowerJumpSimultaneous = FALSE;
    sFollowerPkmnCenterRecalling    = FALSE;
    sFollowerPkmnCenterRecallTaskId = TASK_NONE;
    sFollowerPkmnCenterInBall       = FALSE;
    QueueClear();
}

static void RevealFollower(void)
{
    struct ObjectEvent *follower;
    u32 x, y;
    if (!sFollowerNeedsReveal)
        return;
    // Values > 1 act as a step countdown — decrement and wait.  Used by
    // indoor entry spawns so the follower stays hidden while it crosses the
    // entrance tile, avoiding z-sort glitches with staircase walls.
    if (sFollowerNeedsReveal > 1)
    {
        sFollowerNeedsReveal--;
        return;
    }
    follower = GetFollowerObjEvent();
    if (follower != NULL)
    {
        x = follower->currentCoords.x;
        y = follower->currentCoords.y;
        // Instantly flip the door metatile to its open state so the follower
        // appears to be standing in an open doorway.  The close animation will
        // fire in Task_FollowerUpdate the moment the follower takes its first
        // step away.  Both calls are no-ops on non-door tiles.
        FieldSetDoorOpened(x, y);
        follower->invisible = FALSE;
        sFollowerDoorNeedsClose = TRUE;
    }
    sFollowerNeedsReveal = FALSE;
}

// Called by PlayerWalk* hooks when the player starts an input-driven step.
// Queuing is now handled by the coord-change detector in Task_FollowerUpdate,
// which also covers applymovement-scripted steps that bypass this hook.
// This call is kept only to trigger RevealFollower promptly on the same frame
// as the first input step (so the follower appears immediately, not one frame late).
void FollowerStep(u8 movementActionId)
{
    (void)movementActionId;
    if (!IsFollowerSpawned())
        return;
    // Mach Bike speed callbacks (PlayerWalkNormal/Fast/Faster) call FollowerStep,
    // so guard here to prevent revealing the follower while on bike/surf/dive.
    if (!(gPlayerAvatar.flags & PLAYER_AVATAR_FLAG_ON_FOOT))
        return;
    // Large-follower map-load: ball fires only on the first player-input step,
    // not the scripted door-exit walk.  sLastPlayerX/Y was updated during the
    // scripted step, so the ball spawns at the correct post-door tile.
    if (sFollowerNeedsInputBallReveal)
    {
        sFollowerNeedsInputBallReveal = FALSE;
        sFollowerTeleporting          = TRUE;
        sFollowerTeleportTaskId       = CreateTask(Task_FollowerTeleport, 9);
        return;
    }
    // SpawnFollower (field return / party switch) arms this flag.  Fire the ball
    // here — before AnimateSprites updates currentCoords — so the animation starts
    // exactly when the step begins.  sLastPlayerX/Y still holds the origin tile.
    if (sFollowerNeedsBallReveal)
    {
        sFollowerNeedsBallReveal = FALSE;
        sFollowerTeleporting     = TRUE;
        sFollowerSpawnBallTaskId = CreateTask(Task_FollowerSpawnBall, 9);
        return;
    }
    RevealFollower();
}

// Called by PlayerJumpLedge / PlayerLedgeHoppingWheelie when the player clears a ledge.
// Simultaneous case: follower is directly adjacent behind the player with no queued
// movement — push only a jump from the follower's own position so both air-time together.
// General case: follower is further back — push walk-to-ledge-tile then jump.
void FollowerJumpLedge(u8 direction)
{
    struct FollowerQueueEntry entry;
    struct ObjectEvent *player;
    struct ObjectEvent *follower;
    s16 dx;
    s16 dy;
    bool8 simultaneous;

    if (!IsFollowerSpawned())
        return;
    if (direction == DIR_NONE || direction > 4)
        return;
    // PlayerLedgeHoppingWheelie (Acro Bike) calls FollowerJumpLedge; skip it
    // entirely while on any non-foot mode so no queue entries or reveal fires.
    if (!(gPlayerAvatar.flags & PLAYER_AVATAR_FLAG_ON_FOOT))
        return;

    RevealFollower();

    player   = &gObjectEvents[gPlayerAvatar.objectEventId];
    follower = GetFollowerObjEvent();

    dx = follower->currentCoords.x - player->currentCoords.x;
    dy = follower->currentCoords.y - player->currentCoords.y;

    // Simultaneous jump only when the follower is directly beside the player
    // (perpendicular to the ledge) with no queued movement.  Must be evaluated
    // BEFORE the approach-step flush below, which would otherwise inflate
    // sFollowerQueueSize and prevent the sFollowerQueueSize == 0 check from firing.
    if (sJump2DeltaY[direction] != 0)
        simultaneous = (sFollowerQueueSize == 0 && dy == 0 && dx != 0 && dx >= -1 && dx <= 1);
    else
        simultaneous = (sFollowerQueueSize == 0 && dx == 0 && dy != 0 && dy >= -1 && dy <= 1);

    // Only jump simultaneously if the tile one step ahead of the follower is a valid
    // ledge — the adjacent position might be a tree, boulder, open ground, etc.
    // Use direction (the actual jump direction) not player->facingDirection, which
    // still holds the previous walk direction until AnimateSprites updates it.
    // Use sJump2DeltaX/Y divided by 2 to get the ledge tile (one step ahead), matching
    // how ShouldJumpLedge checks the tile ahead of the player.
    if (simultaneous && GetLedgeJumpDirection(
            follower->currentCoords.x + (sJump2DeltaX[direction] / 2),
            follower->currentCoords.y + (sJump2DeltaY[direction] / 2),
            direction) == DIR_NONE)
        simultaneous = FALSE;

    // Flush the approach step so it lands in the queue before any jump entries.
    // Skipped for the simultaneous case — the follower is already at the ledge
    // and has no trailing approach step to replay.
    if (!simultaneous && (sLastPlayerX != player->currentCoords.x || sLastPlayerY != player->currentCoords.y))
    {
        entry.x    = sLastPlayerX;
        entry.y    = sLastPlayerY;
        entry.kind = ClassifyStepKind(ObjectEventGetHeldMovementActionId(player));
        QueuePush(entry);
    }
    sLastPlayerX = player->currentCoords.x;
    sLastPlayerY = player->currentCoords.y;

    if (simultaneous)
    {
        entry.x    = follower->currentCoords.x + sJump2DeltaX[direction];
        entry.y    = follower->currentCoords.y + sJump2DeltaY[direction];
        entry.kind = (ClassifyStepKind(ObjectEventGetHeldMovementActionId(player)) == FOLLOWER_STEP_RUN)
                   ? FOLLOWER_STEP_JUMP2_FAST : FOLLOWER_STEP_JUMP2;
        QueuePush(entry);
        // Mark that the follower jumped in tandem with the player.
        // The first player step after the landing would otherwise pull the
        // follower onto the player's row/column; that entry is skipped in
        // Task_FollowerUpdate to let the follower stay on its own path.
        sFollowerJumpSimultaneous = TRUE;
    }
    else
    {
        // General case (follower trailing): walk to the ledge tile and stop.
        // The jump fires automatically when the next player step creates a
        // 2-tile delta — detected at dequeue time in Task_FollowerUpdate.
        entry.x    = player->currentCoords.x;
        entry.y    = player->currentCoords.y;
        entry.kind = ClassifyStepKind(ObjectEventGetHeldMovementActionId(player));
        QueuePush(entry);
        sFollowerJumpSimultaneous = FALSE;
    }

    // Record the player's post-jump tile so the coord-change detector in
    // Task_FollowerUpdate can suppress the jump coord-change.
    sFollowerJumpPending = TRUE;
    sFollowerJumpDestX = player->currentCoords.x + sJump2DeltaX[direction];
    sFollowerJumpDestY = player->currentCoords.y + sJump2DeltaY[direction];
}

void SpawnFollowerFromLeadMon(void)
{
    u16 species;

    if (gPlayerPartyCount == 0)
        return;
    if (GetMonData(&gPlayerParty[0], MON_DATA_SANITY_IS_EGG))
        return;
    species = GetMonData(&gPlayerParty[0], MON_DATA_SPECIES);
    if (species == SPECIES_NONE)
        return;
    SpawnFollower(species);
}

// Queues a single walk-normal step to the given tile.  Used by Task_DoDoorWarp
// to guide the follower into the door before the map warp fires.
void QueueFollowerTileEntry(s16 x, s16 y)
{
    struct FollowerQueueEntry entry;
    if (!IsFollowerSpawned())
        return;
    entry.x    = x;
    entry.y    = y;
    entry.kind = FOLLOWER_STEP_WALK_NORMAL;
    QueuePush(entry);
}

// Returns TRUE once the follower has fully arrived at (x, y) — i.e. the walk
// animation is complete.  previousCoords catches up to currentCoords only after
// the sprite finishes sliding, so this avoids hiding the follower mid-step.
bool8 IsFollowerAtTile(s16 x, s16 y)
{
    struct ObjectEvent *follower = GetFollowerObjEvent();
    if (follower == NULL)
        return FALSE;
    return (follower->previousCoords.x == x && follower->previousCoords.y == y);
}

// Hides the follower sprite without despawning it.
void HideFollower(void)
{
    struct ObjectEvent *follower = GetFollowerObjEvent();
    if (follower != NULL)
        follower->invisible = TRUE;
}

u8 GetFollowerSpriteId(void)
{
    struct ObjectEvent *follower = GetFollowerObjEvent();
    if (follower == NULL)
        return MAX_SPRITES;
    return follower->spriteId;
}

void ShowFollowerForEscalator(void)
{
    struct ObjectEvent *follower = GetFollowerObjEvent();
    if (follower == NULL)
        return;
    follower->invisible = FALSE;
    sFollowerNeedsReveal = FALSE;
}

// Called on fresh map loads (warps and connections).
// Spawns the follower at the player's current tile on every map load (warps,
// connections, door/staircase entries).  The follower is invisible until the
// player's first step, at which point RevealFollower() makes it appear at the
// player's previous tile — one step behind, which is correct for every entry
// type including the scripted walk-down that fires after a door warp:
//
//   frame 0  (map loads)    : follower invisible at player tile P
//   frame 1  (scripted step): player walks to P+1; follower revealed at P
//   frame 2+ (player moves) : follower walks P → P+1 → P+2 …
//
// This avoids the earlier approach of spawning one tile behind with a two-step
// delay, which placed the follower at the staircase-wall tile (z-sort in front
// of the sprite) and prevented reveal during the single scripted entry step.
void SpawnFollowerFromLeadMonOnLoad(void)
{
    u16 species;
    bool8 isLarge;
    struct ObjectEvent *player;

    if (gPlayerPartyCount == 0)
        return;
    if (GetMonData(&gPlayerParty[0], MON_DATA_SANITY_IS_EGG))
        return;
    species = GetMonData(&gPlayerParty[0], MON_DATA_SPECIES);
    if (species == SPECIES_NONE)
        return;

    DespawnFollower();
    isLarge = IsLargeFollowerSpecies(species);
    // Large followers are suppressed on maps where cycling is not allowed.
    if (isLarge && !Overworld_IsBikingAllowed())
        return;

    player = &gObjectEvents[gPlayerAvatar.objectEventId];
    if (IsEscalatorWarpIn())
    {
        // Spawn one tile west: the escalator animation slides in from the left
        // (x2 starts at ~-16px), so this base offset makes the follower appear
        // one step behind the player when it becomes visible.
        DoSpawnFollower(species, player->currentCoords.x - 1, player->currentCoords.y);
        sFollowerRevealDelayTimer = 24;
        {
            struct ObjectEvent *escFollower = GetFollowerObjEvent();
            if (escFollower != NULL)
                escFollower->facingDirection = DIR_EAST;
        }
    }
    else
    {
        DoSpawnFollower(species, player->currentCoords.x, player->currentCoords.y);
    }
    // Large followers reveal with the ball on the first player-input step.
    // sFollowerNeedsInputBallReveal is consumed by FollowerStep (input only),
    // so the scripted door-exit walk is skipped and the ball fires one step later.
    if (isLarge)
    {
        sFollowerNeedsReveal          = FALSE;
        sFollowerNeedsBallReveal      = FALSE;
        sFollowerNeedsInputBallReveal = TRUE;
    }
}
