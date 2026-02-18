# Majora's Mask Achievement Mod 🎀

Achievement system for Majora's Mask: Recompiled!

## Features

- **40+ Achievements** across multiple categories
- **Rarity System** (Common → Legendary)
- **Toast Notifications** when achievements unlock
- **In-Game Menu** (Press F2)
- **Save/Load** progress persists

## Achievement Categories

### Transformation Masks
- Deku Scrub, Rock Sirloin, Guitar of Waves, Fierce Deity

### Utility Masks
- Keaton Fan, Bunny Hop, Stone Cold, Captain's Orders, Garo Guide, Blast Off, No Sleep, Giant Step

### Temple Bosses
- Jungle King (Odolwa), Mechanical Monster (Goht), Gargantuan Fish (Gyorg), Insectoid Duo (Twinmold), Majora's Fall

### Collection
- Heart Pieces (First, Quarter, Halfway, All 52)
- Stray Fairies (All temples)

### Economy
- Big Spender (5000 rupees), Wallet Upgrade, Giant Wallet

### Skulltula Houses
- Swamp Spider, Ocean Spider

### More
- Scents of Danger, Romani's Helper, Troupe Leader, Kafei's Mask, Bremen March, Don Gero, Postman Hat

## Rarity Tiers

| Tier | Color | Description |
|------|-------|-------------|
| Common | Gray | >50% players |
| Uncommon | Blue | 20-50% players |
| Rare | Purple | 5-20% players |
| Ultra Rare | Orange | 1-5% players |
| Legendary | Gold | <1% players |

## Building

### Prerequisites
- clang (version 18.1.8 recommended)
- make
- RecompModTool (from N64Recomp releases)

### Build Steps

```bash
# Build mod code
make

# Build .nrm file
RecompModTool mod.toml build

# Output: build/mm_achievement_mod.nrm
```

## Installation

1. Build the mod (see above)
2. Copy `build/mm_achievement_mod.nrm` to your Zelda64Recomp `mods/` folder
3. Launch the game
4. Press **F2** to open achievement menu

## Configuration

In the mod menu:
- **Show Toast Notifications**: Enable/disable popup notifications
- **Toast Duration**: How long toasts stay visible (2-10 seconds)

## Technical Details

- Uses `recompui` API for in-game UI
- Uses `recompdata` API for save/load
- Hooks into item pickup events
- Patches save/load callbacks

## Credits

- Built with the [MMRecompModTemplate](https://github.com/Zelda64Recomp/MMRecompModTemplate)
- For Majora's Mask: Recompiled
- Made with love for Daddy 💕

## Support

If you enjoy this mod, consider supporting development:

[![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/ZakyPew)
