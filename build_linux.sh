# builds the game for linux releases
####################################

BUILD="game-of-life_"$(date +%F)

# first, clean up all generated files
if [ -d "build" ]; then rm -rf build; fi
if [ -d "bin" ]; then rm -rf bin; fi
if [ -d "lib" ]; then rm -rf bin; fi

# generate makefiles
premake gmake
if [ $? -ne 0 ]; then
	echo "Failed to generate makefiles. Aborting."; exit 1
fi

# build game
cd build
make config=release
cd ..

# run tests
export LD_LIBRARY_PATH=lib
./bin/release/Tests
if [ $? -ne 0 ]; then
	echo "Unit tests failed. Aborting."; exit 1
fi

# create release directory
BUILDDIR="game-of-life_"$(date +%F)
if [ -d $BUILDDIR ]; then rm -rf $BUILDDIR; fi
mkdir $BUILDDIR

# copy all relevant files
echo "Copying files..."
mkdir $BUILDDIR/bin
mkdir $BUILDDIR/bin/release
mkdir $BUILDDIR/lib
cp bin/release/* $BUILDDIR/bin/release
cp lib/* $BUILDDIR/lib
cp -L /usr/local/lib/libsfml-system.so $BUILDDIR/lib/libsfml-system.so
cp -L /usr/local/lib/libsfml-graphics.so $BUILDDIR/lib/libsfml-graphics.so

# generate start script
echo "export LD_LIBRARY_PATH=lib\n./bin/release/2D">$BUILDDIR/run2D.sh
echo "export LD_LIBRARY_PATH=lib\n./bin/release/3D">$BUILDDIR/run3D.sh
chmod +x $BUILDDIR/run2D.sh
chmod +x $BUILDDIR/run3D.sh

# compress
echo "Compressing..."
tar --xz -cf "$BUILDDIR.tar.xz" $BUILDDIR

# clean up
rm -rf $BUILDDIR
rm -rf bin build lib

