# Thunderstore Publishing Guide 🎀

## Quick Start

### 1. Build the Mod

```bash
cd ~/ai-workspace/mm-achievement-mod-recomp
make
RecompModTool mod.toml build
```

### 2. Add an Icon

Create a 256x256 PNG icon and save it as:
```
thunderstore/icon.png
```

Suggested: Gold trophy or achievement badge on transparent/gold background

### 3. Build Package

```bash
./build_thunderstore.sh
```

This creates: `mm_achievement_mod-thunderstore.zip`

### 4. Upload to Thunderstore

1. Go to: https://thunderstore.io/c/zelda-64-recompiled/create/
2. Login with your account
3. Fill in the form:
   - **Team**: Your username or create a team
   - **Name**: Achievement_System
   - **Version**: 1.0.0
   - **Description**: Copy from thunderstore/README.md
   - **Categories**: Gameplay
4. Upload the zip file
5. Submit!

## Package Structure

```
mm_achievement_mod-thunderstore.zip
├── manifest.json       # Mod metadata
├── README.md          # Thunderstore description
├── icon.png           # 256x256 mod icon
└── mm_achievement_mod.nrm  # The actual mod file
```

## manifest.json

Already configured:
- Name: "Achievement_System"
- Version: "1.0.0"
- Author: "ZakyPew"
- Dependencies: Zelda64Recomp base game
- Categories: gameplay

## Updating the Mod

1. Update version in `thunderstore/manifest.json`
2. Rebuild mod: `make && RecompModTool mod.toml build`
3. Rebuild package: `./build_thunderstore.sh`
4. Upload new version to Thunderstore

## Support

Need help? Check the GitHub repo:
https://github.com/ZakyPew/mm-achievement-mod
