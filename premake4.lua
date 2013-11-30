-------------------------------------------------------------------
-- Game of Life build script
-------------------------------------------------------------------

-- Windows specific settings
if os.get() == "windows" then
	
	-- global header include directories
	headerSearchDirs = {
		"$(SFML_HOME)/include"
	}
	
	-- lib include directories
	libSearchDirs = {
		"$(SFML_HOME)/lib"
	}
	
	-- link libraries
	linklibs_debug = {
		"sfml-system",
		"sfml-graphics"
	}
	linklibs_release = {
	}

elseif os.get() == "linux" then

	-- header search directories
	headerSearchDirs = {
		"usr/local/include/",
		"usr/include",
		"game-of-life"
	}

	-- lib include directories
	libSearchDirs = {
		"usr/local/lib",
		"usr/lib"
	}

	-- link libraries
	linklibs_debug = {
		"sfml-system",
		"sfml-graphics"
	}
	linklibs_release = {
		"sfml-system",
		"sfml-graphics"
	}
	linklibs_tests_debug = {
		"gmock"
	}
	linklibs_tests_release = {
		"gmock"
	}

-- MAAAC
elseif os.get() == "macosx" then

	-- TODO

-- OS couldn't be determined
else
	printf( "FATAL: Unable to determine your operating system!" )
end

-------------------------------------------------------------------
-- Game of Life Solution
-------------------------------------------------------------------

solution "GameOfLife"
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
	-- Chocobun core
	-------------------------------------------------------------------
	
	project "Game"
		kind "ConsoleApp"
		language "C++"
		files {
			"game-of-life/**.cpp",
			"game-of-life/**.hpp",
			"game-of-life/**.hxx"
		}
		
		includedirs (headerSearchDirs)
		
		configuration "Debug"
			if os.get() == "macosx" then -- very ugly hotfix to make shit work with OS X. If you know any better, please fix!
				targetdir "bin/bin/debug"
			else
				targetdir "bin/debug"
			end
			targetsuffix "_d"
			defines {
				"DEBUG",
				"_DEBUG"
			}
			flags {
				"Symbols"
			}
			libdirs (libSearchDirs)
			links (linklibs_debug)
			
		configuration "Release"
			if os.get() == "macosx" then -- very ugly hotfix to make shit work with OS X. If you know any better, please fix!
				targetdir "bin/bin/release"
			else
				targetdir "bin/release"
			end
			defines {
				"NDEBUG"
			}
			flags {
				"Optimize"
			}
			libdirs (libSearchDirs)
			links (linklibs_release)

	-------------------------------------------------------------------
	-- Unit tests
	-------------------------------------------------------------------

	project "Tests"
		kind "ConsoleApp"
		language "C++"
		files {
			"game-of-life-tests/**.cpp"
		}

		includedirs (headerSearchDirs)

		configuration "Debug"
			if os.get() == "macosx" then -- very ugly hotfix to make shit work with OS X. If you know any better, please fix!
				targetdir "bin/bin/debug"
			else
				targetdir "bin/debug"
			end
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
			if os.get() == "macosx" then -- very ugly hotfix to make shit work with OS X. If you know any better, please fix!
				targetdir "bin/bin/release"
			else
				targetdir "bin/release"
			end
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
