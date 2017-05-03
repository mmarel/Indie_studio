#! /bin/sh

# Clean
rm -rf irrlicht*
# Download Irrlicht
wget http://downloads.sourceforge.net/irrlicht/irrlicht-1.8.4.zip -q --show-progress &&
# Unzip the target
unzip irrlicht-1.8.4.zip &&
# Compile and create the library
make -C irrlicht-1.8.4/source/Irrlicht/ &&
# Copy Library .a and headers in the project
rm -rf ../lib/Linux ../lib/MacOSX ../lib/Win32-gcc ../lib/Win32-visualstudio ../lib/Win64-visualStudio &&
mkdir -p ../lib &&
cp -r irrlicht-1.8.4/lib/* ../lib/ &&
rm -rf ../includes/irr &&
mkdir -p ../includes/irr &&
cp -r irrlicht-1.8.4/include/* ../includes/irr &&
# Erase the tarball and the irrlicht folder
rm -rf irrlicht-1.8.4.zip irrlicht-1.8.4 &&

echo "Install Complete"