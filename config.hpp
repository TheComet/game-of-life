// --------------------------------------------------------------
// Configures prerequisits for the pony library package
// --------------------------------------------------------------

#ifndef __PONY_LIB_CONFIG_HPP__
#	define __PONY_LIB_CONFIG_HPP__

	// --------------------------------------------------------------
	// Identify the operating system
	// --------------------------------------------------------------

#	if defined(_WIN32) || defined(__WIN32__)
#		define PONY_LIB_PLATFORM_WINDOWS
#	elif defined(linux) || defined(__linux)
#		define PONY_LIB_PLATFORM_LINUX
#	elif defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)
#		define PONY_LIB_PLATFORM_MAC
#	else
#		error This operating system is not supported by ponylib
#	endif

	// --------------------------------------------------------------
	// define import/export macros for ponylib modules
	// --------------------------------------------------------------

#	if defined(PONY_LIB_DYNAMIC)
#		if defined(PONY_LIB_PLATFORM_WINDOWS)

			// windows compilers need specific (and different) keywords for export and import
#			define PONY_LIB_EXPORT __declspec(dllexport)
#			define PONY_LIB_IMPORT __declspec(dllimport)

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
#				define PONY_LIB_EXPORT __attribute__ ((__visibility__ ("default")))
#				define PONY_LIB_IMPORT __attribute__ ((__visibility__ ("default")))
#			else

				// GCC < 4 has no mechanism to explicitely hide symbols, everything's exported
#				define PONY_LIB_EXPORT
#				define PONY_LIB_IMPORT
#			endif
#		endif
#	elif defined(PONY_LIB_STATIC)

		// static build doesn't need import/export macros
#		define PONY_LIB_EXPORT
#		define PONY_LIB_IMPORT
#	else

		// dynamic or static build wasn't defined
#		error Please define PONY_LIB_DYNAMIC OR PONY_LIB_STATIC
#	endif

namespace Pony {

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

} // namespace pony

#endif // __PONY_LIB_CONFIG_HPP__
