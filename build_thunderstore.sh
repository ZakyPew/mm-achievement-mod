#!/bin/bash
# Build Thunderstore package

echo "Building Thunderstore package..."

# Check for icon
if [ ! -f "thunderstore/icon.png" ]; then
    echo "⚠️  Warning: icon.png not found!"
    echo "Please add a 256x256 PNG icon as thunderstore/icon.png"
    echo "Continuing without icon..."
fi

# Create package directory
mkdir -p thunderstore_package

# Copy files
cp thunderstore/manifest.json thunderstore_package/
cp thunderstore/README.md thunderstore_package/

# Copy icon if it exists
if [ -f "thunderstore/icon.png" ]; then
    cp thunderstore/icon.png thunderstore_package/
fi

# Copy mod file
if [ -f "build/mm_achievement_mod.nrm" ]; then
    cp build/mm_achievement_mod.nrm thunderstore_package/
else
    echo "⚠️  Mod file not found. Build first with: make && RecompModTool mod.toml build"
    exit 1
fi

# Create zip
cd thunderstore_package
zip -r ../mm_achievement_mod-thunderstore.zip .
cd ..

echo "✅ Package created: mm_achievement_mod-thunderstore.zip"
echo ""
echo "Upload this file to: https://thunderstore.io/c/zelda-64-recompiled/create/"
