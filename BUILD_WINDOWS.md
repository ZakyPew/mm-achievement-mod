# Build Instructions for Windows PowerShell 🎀

## PowerShell Build Steps

### Option 1: Run Commands Separately (Recommended)

```powershell
# 1. Go to your Zelda64Recomp folder
cd C:\Users\YourName\Zelda64Recomp

# 2. Clone the mod
git clone https://github.com/ZakyPew/mm-achievement-mod.git

# 3. Enter the mod folder
cd mm-achievement-mod

# 4. Initialize submodule (first time)
git submodule update --init --recursive

# 5. Clean previous build
make clean

# 6. Build the mod
make

# 7. Create the .nrm file (you need RecompModTool.exe)
.\RecompModTool.exe mod.toml build

# 8. Copy to mods folder
Copy-Item build\mm_achievement_mod.nrm C:\Users\YourName\Zelda64Recomp\mods\
```

### Option 2: Use Semicolons in PowerShell

```powershell
cd C:\Users\YourName\Zelda64Recomp\mm-achievement-mod; make clean; make
```

### Option 3: Use Git Bash (Comes with Git for Windows)

1. Open **Git Bash** (right-click in folder → "Git Bash Here")
2. Then use the original Linux commands:

```bash
cd /c/Users/YourName/Zelda64Recomp/mm-achievement-mod
make clean && make -j$(nproc)
./RecompModTool.exe mod.toml build
cp build/mm_achievement_mod.nrm /c/Users/YourName/Zelda64Recomp/mods/
```

### Option 4: Use WSL (Windows Subsystem for Linux)

```bash
# In WSL terminal
cd /mnt/c/Users/YourName/Zelda64Recomp/mm-achievement-mod
make clean && make -j$(nproc)
./RecompModTool mod.toml build
cp build/mm_achievement_mod.nrm /mnt/c/Users/YourName/Zelda64Recomp/mods/
```

---

## Download RecompModTool for Windows

If you don't have it:

```powershell
# Download
curl -L -o RecompModTool.exe "https://github.com/N64Recomp/N64Recomp/releases/download/mod-tool-release/RecompModTool.exe"

# Or use your browser to download from:
# https://github.com/N64Recomp/N64Recomp/releases/tag/mod-tool-release
```

---

## PowerShell vs Bash Cheat Sheet

| Bash (Linux/WSL/Git Bash) | PowerShell |
|---------------------------|------------|
| `&&` | `;` or run separate |
| `make -j$(nproc)` | `make` (no -j in PowerShell) |
| `./file` | `.\file` or `& .\file` |
| `cp source dest` | `Copy-Item source dest` |
| `rm file` | `Remove-Item file` |
| `ls` | `Get-ChildItem` or `dir` |
| `cd folder` | `cd folder` or `Set-Location folder` |

---

## Easiest Way: Git Bash

1. Install **Git for Windows** (if not already)
2. Right-click in your `mm-achievement-mod` folder
3. Select **"Git Bash Here"**
4. Run the Linux commands from the other README!

---

Love you, Daddy! 💕
