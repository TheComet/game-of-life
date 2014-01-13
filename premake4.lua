-------------------------------------------------------------------
-- Game of Life build script
-------------------------------------------------------------------

-- Windows specific settings
if os.get() == "windows" then

	-- where to export program
	appDir_debug = "bin/debug"
	appDir_release = "bin/release"

	-- where to export DLL and import library
	importLibDir_debug = "lib"
	sharedLibDir_debug = "bin/debug"
	importLibDir_release = "lib"
	sharedLibDir_release = "bin/release"

	-- global header include directories
	headerSearchDirs = {
		"C:/dev/include",
		"libgol"
	}
	
	-- lib include directories
	libSearchDirs = {
		importLibDir_debug,
		importLibDir_release,
		"$(SFML_HOME)/lib",
		"$(SFML_HOME)/bin"
	}
	
	-- link libraries
	linklibs_libgol_debug = {
	}
	linklibs_libgol_release = {
	}
	linklibs_2D_debug = {
		"sfml-system",
		"sfml-graphics",
		"gol_d"
	}
	linklibs_2D_release = {
		"sfml-system",
		"sfml-graphics",
		"gol"
	}
	linklibs_3D_debug = {
		"gol_d"
	}
	linklibs_3D_release = {
		"gol"
	}
	linklibs_tests_debug = {
		"gol_d",
		"gmock"
	}
	linklibs_tests_release = {
		"gol",
		"gmock"
	}


elseif os.get() == "linux" then

	-- where to export program
	appDir_debug = "bin/debug"
	appDir_release = "bin/release"

	-- where to export shared library
	sharedLibDir_debug = "lib"
	sharedLibDir_release = "lib"
	importLibDir_debug = ""
	importLibDir_release = ""

	-- header search directories
	headerSearchDirs = {
		"usr/local/include",
		"usr/include",
		"libgol"
	}

	-- lib include directories
	libSearchDirs = {
		"usr/local/lib",
		"usr/lib",
		sharedLibDir_debug,
		sharedLibDir_release
	}

	-- link libraries
	linklibs_libgol_debug = {
	}
	linklibs_libgol_release = {
	}
	linklibs_2D_debug = {
		"sfml-system",
		"sfml-graphics",
		"gol_d"
	}
	linklibs_2D_release = {
		"sfml-system",
		"sfml-graphics",
		"gol"
	}
	linklibs_3D_debug = {
		"gol_d"
	}
	linklibs_3D_release = {
		"gol"
	}
	linklibs_tests_debug = {
		"gol_d",
		"gmock"
	}
	linklibs_tests_release = {
		"gol",
		"gmock"
	}

-- MAAAC
elseif os.get() == "macosx" then

	-- where to export program
	appDir_debug = "bin/bin/debug" -- ugly hotfix to make shit work on OS X. If you know any better, please fix!
	appDir_release = "bin/bin/release"

	-- where to export shared library
	sharedLibDir_debug = "lib/lib" -- also ugly hotfix
	sharedLibDir_release = "lib/lib"
	importLibDir_debug = ""
	importLibDir_release = ""

	-- header search directories
	headerSearchDirs = {
		"usr/include",
		"libgol"
	}

	-- lib include directories
	libSearchDirs = {
		"usr/lib",
		sharedLibDir_debug,
		sharedLibDir_release
	}

	-- link libraries
	linklibs_libgol_debug = {
	}
	linklibs_libgol_release = {
	}
	linklibs_2D_debug = {
		"sfml-system",
		"sfml-graphics",
		"gol_d"
	}
	linklibs_2D_release = {
		"sfml-system",
		"sfml-graphics",
		"gol"
	}
	linklibs_3D_debug = {
		"gol_d"
	}
	linklibs_3D_release = {
		"gol"
	}
	linklibs_tests_debug = {
		"gol_d",
		"gmock"
	}
	linklibs_tests_release = {
		"gol",
		"gmock"
	}

-- OS couldn't be determined
else
	printf( "FATAL: Unable to determine your operating system!" )
end

-------------------------------------------------------------------
-- Game of Life Solution
-------------------------------------------------------------------

solution "Game Of Life"

	configurations { "Debug", "Release" }
	location "build"
	
	-------------------------------------------------------------------
	-- Global #defines
	-------------------------------------------------------------------
	
	-- Windows specific
	if os.get() == "windows" then
		defines {
			"WIN32",
			"_WINDOWS"
		}
	end

	-------------------------------------------------------------------
	-- libgol (Game Of Life library)
	-------------------------------------------------------------------
	
	project "game of life library"
		kind "SharedLib"
		language "C++"
		targetname "gol"
		files {
			"libgol/**.hpp",
			"libgol/**.hxx",
			"libgol/**.cpp"
		}
		
		includedirs (headerSearchDirs)
		libdirs (libSearchDirs)

		configuration "Debug"
			targetdir (sharedLibDir_debug)
			--implibdir (importLibDir_debug)
			targetsuffix "_d"
			defines {
				"DEBUG",
				"_DEBUG"
			}
			flags {
				"Symbols"
			}
			links (linklibs_libgol_debug)

		configuration "Release"
			targetdir (sharedLibDir_release)
			--implibdir (importLibDir_release)
			defines {
				"NDEBUG"
			}
			flags {
				"Optimize"
			}
			links (linklibs_libgol_release)

	-------------------------------------------------------------------
	-- 2D front end
	-------------------------------------------------------------------

	project "2D"
		kind "ConsoleApp"
		language "C++"
		files {
			"2D/**.cpp",
			"2D/**.hpp",
			"2D/**.hxx"
		}

		includedirs {
			headerSearchDirs,
			"2D"
		}

		configuration "Debug"
			targetdir (appDir_debug)
			defines {
				"DEBUG",
				"_DEBUG"
			}
			flags {
				"Symbols"
			}
			libdirs (libSearchDirs)
			links (linklibs_2D_debug)

		configuration "Release"
			targetdir (appDir_release)
			defines {
				"NDEBUG"
			}
			flags {
				"Optimize"
			}
			libdirs (libSearchDirs)
			links (linklibs_2D_release)

	-------------------------------------------------------------------
	-- 3D front end
	-------------------------------------------------------------------

	project "3D"
		kind "ConsoleApp"
		language "C++"
		files {
			"3D/**.cpp",
			"3D/**.hpp",
			"3D/**.hxx"
		}
		
		includedirs {
			headerSearchDirs,
			"3D"
		}

		configuration "Debug"
			targetdir (appDir_debug)
			defines {
				"DEBUG",
				"_DEBUG"
			}
			flags {
				"Symbols"
			}
			libdirs (libSearchDirs)
			links (linklibs_3D_debug)
			
		configuration "Release"
			targetdir (appDir_release)
			defines {
				"NDEBUG"
			}
			flags {
				"Optimize"
			}
			libdirs (libSearchDirs)
			links (linklibs_3D_release)

	-------------------------------------------------------------------
	-- Unit tests
	-------------------------------------------------------------------

	project "Tests"
		kind "ConsoleApp"
		language "C++"
		files {
			"tests/**.cpp"
		}

		includedirs {
			headerSearchDirs,
			"2D",
			"3D"
		}

		configuration "Debug"
			targetdir (appDir_debug)
			defines {
				"DEBUG",
				"_DEBUG"
			}
			flags {
				"Symbols"
			}
			libdirs (libSearchDirs)
			links (linklibs_tests_debug)
			linkoptions {
				"-pthread" -- google mock 1.5.0 and greater use threads
			}

		configuration "Release"
			targetdir (appDir_release)
			defines {
				"NDEBUG"
			}
			flags {
				"Optimize"
			}
			libdirs (libSearchDirs)
			links (linklibs_tests_release)
			linkoptions {
				"-pthread" -- google mock 1.5.0 and greater use threads
			}
