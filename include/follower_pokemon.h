#ifndef GUARD_FOLLOWER_POKEMON_H
#define GUARD_FOLLOWER_POKEMON_H

#include "global.h"
#include "sprite.h"

// Reserved local ID for the follower object event (must not clash with map events).
#define LOCAL_ID_FOLLOWER 0xFE

void SpawnFollower(u16 species);
void DespawnFollower(void);
void SetFollowerSpecies(u16 species);
bool8 IsFollowerSpawned(void);
bool8 IsLargeFollower(void);
u16  GetFollowerSpecies(void);

// Called by PlayerWalk* hooks whenever the player starts a tile step.
void FollowerStep(u8 movementActionId);

// Called by PlayerJumpLedge / PlayerLedgeHoppingWheelie when the player clears a ledge.
void FollowerJumpLedge(u8 direction);

// Queues a walk-normal step to (x, y) for the follower (used by door-warp logic).
void QueueFollowerTileEntry(s16 x, s16 y);

// Returns TRUE when the follower's current tile matches (x, y).
bool8 IsFollowerAtTile(s16 x, s16 y);

// Hides the follower sprite without despawning it.
void HideFollower(void);

// Returns the follower's sprite ID, or MAX_SPRITES if no follower is active.
u8   GetFollowerSpriteId(void);

// Makes the follower immediately visible and cancels the pending-reveal flag.
// Used by the escalator warp-in so the follower animates alongside the player.
void ShowFollowerForEscalator(void);

// Returns the sprite pic table and palette for a given follower species.
// Used by the cable car scene to create a standalone follower sprite.
// Returns FALSE if the species has no follower graphics.
bool8 GetFollowerSpriteData(u16 species,
                             const u16 **palOut,
                             const struct SpriteFrameImage **picOut);

// Spawns the follower for the current lead party member (skips eggs/empty party).
void SpawnFollowerFromLeadMon(void);

// Like SpawnFollowerFromLeadMon but uses the entrance tile for indoor maps
// (places follower at the door, in the player's facing direction) so the pokemon
// appears to walk through the door behind the player on first step.
// Use from InitObjectEventsLocal (fresh map load) only — NOT battle/menu returns.
void SpawnFollowerFromLeadMonOnLoad(void);

// Pokemon Center heal sequence: the follower walks left then up into a Pokéball
// that appears on the counter.  Call FollowerPkmnCenterRecall via `special` +
// `waitstate` (guarded by IsFollowerSpawned) before dofieldeffect.
// Call FollowerPkmnCenterRelease before the nurse's return dialog — the follower
// re-appears at the player's feet on the next step.
void FollowerPkmnCenterRecall(void);
void FollowerPkmnCenterRelease(void);

#endif // GUARD_FOLLOWER_POKEMON_H
