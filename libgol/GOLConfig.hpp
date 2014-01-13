// --------------------------------------------------------------
// Configures prerequisits for the game of life library package
// --------------------------------------------------------------

#ifndef __LIB_GOL_CONFIG_HPP__
#	define __LIB_GOL_CONFIG_HPP__

	// --------------------------------------------------------------
	// Identify the operating system
	// --------------------------------------------------------------

#	if defined(_WIN32) || defined(__WIN32__)
#		define LIB_GOL_PLATFORM_WINDOWS
#	elif defined(linux) || defined(__linux)
#		define LIB_GOL_PLATFORM_LINUX
#	elif defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)
#		define LIB_GOL_PLATFORM_MAC
#	else
#		error This operating system is not supported by libgol
#	endif

	// --------------------------------------------------------------
	// define import/export macros for gol modules
	// --------------------------------------------------------------

#	if defined(LIB_GOL_DYNAMIC)
#		if defined(LIB_GOL_PLATFORM_WINDOWS)

			// windows compilers need specific (and different) keywords for export and import
#			define LIB_GOL_EXPORT __declspec(dllexport)
#			define LIB_GOL_IMPORT __declspec(dllimport)

			// disable annoying warnings in MSVC
#			ifdef _MSC_VER
#				pragma warning(disable:4251)	// needs to have dll-interface to be used by clients of class
#				pragma warning(disable:4275)	// non dll-interface class 'OIS::KeyListener' used as base for dll-interface class
#			endif

		// linux and mac
#		else
#			if __GNUC__ >= 4

				// GCC 4 has special keywords for showing/hidding symbols,
				// the same keyword is used for both importing and exporting
#				define LIB_GOL_EXPORT __attribute__ ((__visibility__ ("default")))
#				define LIB_GOL_IMPORT __attribute__ ((__visibility__ ("default")))
#			else

				// GCC < 4 has no mechanism to explicitely hide symbols, everything's exported
#				define LIB_GOL_EXPORT
#				define LIB_GOL_IMPORT
#			endif
#		endif
#	elif defined(LIB_GOL_STATIC)

		// static build doesn't need import/export macros
#		define LIB_GOL_EXPORT
#		define LIB_GOL_IMPORT
#	else

		// dynamic or static build wasn't defined
#		error Please define LIB_GOL_DYNAMIC OR LIB_GOL_STATIC
#	endif

namespace GOL {

    // --------------------------------------------------------------
	// define fixed-type sizes
	// --------------------------------------------------------------

	// All "common" platforms use the same size for char, short and int
    // (basically there are 3 types for 3 sizes, so no other match is possible),
    // we can use them without doing any kind of check

	// 8 bits integer types
    typedef signed   char Int8;
    typedef unsigned char Uint8;

    // 16 bits integer types
    typedef signed   short Int16;
    typedef unsigned short Uint16;

    // 32 bits integer types
    typedef signed   int Int32;
    typedef unsigned int Uint32;

    // 64 bits integer types
#	if defined(_MSC_VER)
        typedef signed   __int64 Int64;
        typedef unsigned __int64 Uint64;
#	else
        typedef signed   long long Int64;
        typedef unsigned long long Uint64;
#	endif

} // namespace GOL

#endif // __LIB_GOL_CONFIG_HPP__
