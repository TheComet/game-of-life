# builds the game for linux releases
####################################

#########################################################
# copies all dependencies of file arg1 to location arg2
#########################################################
copy_dependencies() {

        # extracts dependency paths from the application specified
        DEPENDENCY_PATHS=$(ldd $1 | cut -d "=" -f2 | cut -d ">" -f2 | cut -d "(" -f1 | cut -d " " -f 2)

        # creates a list of REQUIRED dependency files. ldd specifies more than only the required ones
        DEPENDENCY_NAMES=$(readelf -Wa $1 | grep NEEDED | cut -d "[" -f2 | cut -d "]" -f1 )

        # filter out the required ones and copy them
        for A in $DEPENDENCY_PATHS; do
                FOUND=false
                for B in $DEPENDENCY_NAMES; do
                        if echo $A | grep -q $B>/dev/null; then
                                FOUND=true
                        fi
                done
                if $FOUND; then
			# copy without overwriting
                        cp -n $A $2
                fi
        done
}

# create build name
BUILD="game-of-life_"$(date +%F)
echo "building "$BUILD"..."

# first, clean up all generated files
if [ -d "build" ]; then rm -rf build; fi
if [ -d "bin" ]; then rm -rf bin; fi
if [ -d "lib" ]; then rm -rf bin; fi

# generate makefiles
premake gmake>/dev/null
if [ $? -ne 0 ]; then
	echo "Failed to generate makefiles. Aborting."; exit 1
fi

# build game
echo "building game..."
cd build
make config=release>/dev/null
cd ..

# run tests
export LD_LIBRARY_PATH=lib
./bin/release/Tests>tests.out
if [ $? -ne 0 ]; then
	echo "Unit tests failed. See file \"tests.out\" for more information. Aborting."; exit 1
fi
rm tests.out

# create release directory
BUILDDIR="game-of-life_"$(date +%F)
if [ -d $BUILDDIR ]; then rm -rf $BUILDDIR; fi
mkdir $BUILDDIR

# copy all relevant files
echo "copying files..."
mkdir $BUILDDIR/bin
mkdir $BUILDDIR/bin/release
mkdir $BUILDDIR/lib
cp bin/release/* $BUILDDIR/bin/release
cp lib/* $BUILDDIR/lib

# copy all dependencies to lib folder
echo "copying dependencies..."
copy_dependencies $BUILDDIR/bin/release/2D $BUILDDIR/lib
copy_dependencies $BUILDDIR/bin/release/3D $BUILDDIR/lib

# generate start script
echo "generating start scripts..."
echo "export LD_LIBRARY_PATH=lib\n./bin/release/2D">$BUILDDIR/run2D.sh
echo "export LD_LIBRARY_PATH=lib\n./bin/release/3D">$BUILDDIR/run3D.sh
chmod +x $BUILDDIR/run2D.sh
chmod +x $BUILDDIR/run3D.sh

# compress
echo "compressing..."
tar --xz -cf "$BUILDDIR.tar.xz" $BUILDDIR

# clean up
rm -rf $BUILDDIR
rm -rf bin build lib

echo "done."

exit 0
