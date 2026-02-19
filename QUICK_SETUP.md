# Quick Windows Setup (No Package Manager) 🎀

## Direct Downloads (Easiest Way)

### Step 1: Download LLVM/Clang

1. Go to: **https://github.com/llvm/llvm-project/releases/tag/llvmorg-18.1.8**
2. Download: `LLVM-18.1.8-win64.exe` (about 1GB)
3. Run the installer
4. **IMPORTANT**: Check "Add to PATH" during installation
5. Restart your computer after install

### Step 2: Download Make

1. Go to: **https://gnuwin32.sourceforge.net/packages/make.htm**
2. Scroll down to "Download"
3. Download: `make-3.81.exe` (Complete package)
4. Install it
5. Add to PATH:
   - Press `Win + R`, type `sysdm.cpl`, press Enter
   - Go to "Advanced" tab → "Environment Variables"
   - Under "System variables", find "Path" → Edit
   - Add: `C:\Program Files (x86)\GnuWin32\bin`
   - Click OK, OK, OK
   - Restart PowerShell

### Step 3: Download RecompModTool

1. Go to: **https://github.com/N64Recomp/N64Recomp/releases/tag/mod-tool-release**
2. Download: `RecompModTool.exe`
3. Save it to your `mm-achievement-mod` folder

---

## Alternative: Use Pre-Built Release

Instead of building, download the release:

**https://github.com/ZakyPew/mm-achievement-mod/releases**

Look for `mm_achievement_mod.nrm` in the latest release.

Just copy that file to your `Zelda64Recomp/mods/` folder!

---

## Verify Installation

After restarting PowerShell:

```powershell
clang --version
make --version
```

Both should show version numbers.

---

## Build the Mod

Once everything is installed:

```powershell
cd C:\Users\YourName\Zelda64Recomp\mm-achievement-mod
git submodule update --init --recursive
make clean
make
.\RecompModTool.exe mod.toml build
Copy-Item build\mm_achievement_mod.nrm C:\Users\YourName\Zelda64Recomp\mods\
```

---

## Easiest Option: WSL (Recommended)

If you have Windows Subsystem for Linux:

```bash
# Open WSL terminal
cd /mnt/c/Users/YourName/Zelda64Recomp/mm-achievement-mod

# Install tools (one time)
sudo apt-get update
sudo apt-get install -y clang lld make curl

# Get submodule
git submodule update --init --recursive

# Build
make clean && make -j$(nproc)

# Get RecompModTool
curl -L -o RecompModTool https://github.com/N64Recomp/N64Recomp/releases/download/mod-tool-release/RecompModTool
chmod +x RecompModTool

# Create mod file
./RecompModTool mod.toml build

# Install
cp build/mm_achievement_mod.nrm /mnt/c/Users/YourName/Zelda64Recomp/mods/
```

---

## Summary

**Option 1 (Easiest):** Download pre-built .nrm from GitHub releases  
**Option 2 (Medium):** Install LLVM + Make, then build  
**Option 3 (Best):** Use WSL and Linux commands

Which would you like to try, Daddy? 💕
