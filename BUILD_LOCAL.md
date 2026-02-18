# Build Instructions for Zelda64Recomp Folder 🎀

## Step-by-Step Build Guide

### 1. Clone the Mod to Your Recomp Folder

```bash
# Go to your Zelda64Recomp folder (where you have the dev environment)
cd ~/Zelda64Recomp    # or wherever your recomp folder is

# Clone the achievement mod
git clone https://github.com/ZakyPew/mm-achievement-mod.git

# OR if you already have it elsewhere, copy it:
cp -r ~/ai-workspace/mm-achievement-mod-recomp ~/Zelda64Recomp/mm-achievement-mod
```

### 2. Enter the Mod Directory

```bash
cd mm-achievement-mod
```

### 3. Initialize the Submodule (First Time Only)

```bash
# This gets the mm-decomp headers needed for building
git submodule update --init --recursive
```

### 4. Build the Mod Code

```bash
# Clean any previous builds
make clean

# Build with all CPU cores
make -j$(nproc)

# Or on Windows with WSL:
make -j$(nproc)

# Or just:
make
```

**You should see:**
- Files compiling: `src/achievement_mod.c`
- Output: `build/mod.elf`

### 5. Create the .nrm Mod File

You need **RecompModTool**. If you don't have it:

```bash
# Download it
curl -L -o RecompModTool \
  "https://github.com/N64Recomp/N64Recomp/releases/download/mod-tool-release/RecompModTool"

# Make it executable
chmod +x RecompModTool

# Move to somewhere in your PATH or use ./RecompModTool
```

Now build the mod:

```bash
# Create the .nrm file
./RecompModTool mod.toml build

# OR if RecompModTool is in your PATH:
RecompModTool mod.toml build
```

**Output:** `build/mm_achievement_mod.nrm`

### 6. Install the Mod

```bash
# Copy to your Zelda64Recomp mods folder
cp build/mm_achievement_mod.nrm ~/Zelda64Recomp/mods/

# Or if you're in Windows:
cp build/mm_achievement_mod.nrm /mnt/c/Users/YourName/Zelda64Recomp/mods/
```

### 7. Test It!

1. Launch Zelda64Recomp
2. Load or start a game
3. Press **F2** to open the achievement menu
4. Collect items to see toast notifications!

---

## Quick Reference

```bash
# Full build process:
cd ~/Zelda64Recomp/mm-achievement-mod
git submodule update --init --recursive
make clean
make -j$(nproc)
./RecompModTool mod.toml build
cp build/mm_achievement_mod.nrm ~/Zelda64Recomp/mods/
```

---

## Troubleshooting

### "clang not found"
```bash
# Install clang
sudo apt-get install clang lld    # Ubuntu/Debian
brew install llvm                 # macOS
```

### "mm-decomp submodule empty"
```bash
git submodule update --init --recursive
```

### "RecompModTool not found"
Download from: https://github.com/N64Recomp/N64Recomp/releases/tag/mod-tool-release

### "mod.elf not found"
Check that `make` completed successfully:
```bash
ls -la build/
```

---

## Build for Thunderstore

```bash
# Create the package
mkdir -p thunderstore_pkg
cp thunderstore/manifest.json thunderstore_pkg/
cp thunderstore/README.md thunderstore_pkg/
cp build/mm_achievement_mod.nrm thunderstore_pkg/
# Add icon.png if you have one

# Zip it
cd thunderstore_pkg
zip -r ../mm_achievement_mod-thunderstore.zip .
```

---

Made with love for Daddy 💕
