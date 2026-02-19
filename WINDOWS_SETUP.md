# Windows Build Setup Guide 🎀

## Install Build Tools (One-Time Setup)

### Step 1: Install Chocolatey (Package Manager)

**Run PowerShell as Administrator**, then:

```powershell
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
```

Close and reopen PowerShell after this.

### Step 2: Install Required Tools

```powershell
# Install make
choco install make

# Install LLVM/Clang (version 18.1.8 - the one that works!)
choco install llvm --version=18.1.8

# Install Git (if not already)
choco install git
```

**Close and reopen PowerShell after installing!**

### Step 3: Verify Installation

```powershell
# Check versions
make --version
clang --version
```

You should see version numbers. If not, restart your computer.

---

## Alternative: Manual Installation (No Chocolatey)

### Download LLVM/Clang Manually

1. Go to: https://github.com/llvm/llvm-project/releases
2. Download: `LLVM-18.1.8-win64.exe`
3. Run the installer
4. **IMPORTANT**: Check "Add to PATH" during installation

### Download Make for Windows

1. Go to: https://gnuwin32.sourceforge.net/packages/make.htm
2. Download: `Complete package, except sources`
3. Install it
4. Add `C:\Program Files (x86)\GnuWin32\bin` to your PATH

---

## Download RecompModTool

1. Go to: https://github.com/N64Recomp/N64Recomp/releases/tag/mod-tool-release
2. Download: `RecompModTool.exe`
3. Put it in your `mm-achievement-mod` folder

---

## Now Build the Mod!

```powershell
# Go to your mod folder
cd C:\Users\YourName\Zelda64Recomp\mm-achievement-mod

# Initialize submodule
git submodule update --init --recursive

# Build
make clean
make

# Create .nrm file
.\RecompModTool.exe mod.toml build

# Copy to mods folder
Copy-Item build\mm_achievement_mod.nrm C:\Users\YourName\Zelda64Recomp\mods\
```

---

## Common Issues

### "clang not recognized"
Restart PowerShell or your computer after installing LLVM.

### "make not recognized"
Make sure `C:\Program Files (x86)\GnuWin32\bin` is in your PATH.

To check:
```powershell
$env:Path
```

To add (temporary):
```powershell
$env:Path += ";C:\Program Files (x86)\GnuWin32\bin"
```

### "RecompModTool.exe not found"
Make sure you downloaded it and it's in the same folder as mod.toml.

---

## Easiest Alternative: Use WSL

If you have Windows Subsystem for Linux:

```bash
# In WSL
cd /mnt/c/Users/YourName/Zelda64Recomp/mm-achievement-mod
sudo apt-get install clang lld make
git submodule update --init --recursive
make clean && make -j$(nproc)
curl -L -o RecompModTool https://github.com/N64Recomp/N64Recomp/releases/download/mod-tool-release/RecompModTool
chmod +x RecompModTool
./RecompModTool mod.toml build
cp build/mm_achievement_mod.nrm /mnt/c/Users/YourName/Zelda64Recomp/mods/
```

---

Need help, Daddy? 💕
