-------------------------------------------------------------------
-- Game of Life build script
-------------------------------------------------------------------

-- Windows specific settings
if os.get() == "windows" then
	
	-- global header include directories
	headerSearchDirs = {
	}
	
	-- lib include directories
	libSearchDirs = {
	}
	
	-- link libraries
	linklibs_libgol_debug = {
	}
	linklibs_libgol_release = {
	}
	linklibs_3D_debug = {
	}
	linklibs_3D_release = {
	}

elseif os.get() == "linux" then

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
		"bin/debug",
		"bin/release"
	}

	-- link libraries
	linklibs_libgol_debug = {
	}
	linklibs_libgol_release = {
	}
	linklibs_2D_debug = {
		"sfml-system",
		"sfml-graphics"
	}
	linklibs_2D_release = {
		"sfml-system",
		"sfml-graphics"
	}
	linklibs_3D_debug = {
		"libgol"
	}
	linklibs_3D_release = {
		"libgol"
	}
	linklibs_tests_debug = {
		--"libgol",
		"gmock"
	}
	linklibs_tests_release = {
		--"libgol",
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
	
	project "libgol"
		kind "SharedLib"
		language "C++"
		files {
			"libgol/**.hpp",
			"libgol/**.hxx",
			"libgol/**.cpp"
		}
		
		includedirs (headerSearchDirs)

		configuration "Debug"
			if os.get() == "macosx" then -- very ugly hotfix to make shit work with OS X. If you know any better, please fix!
				targetdir "bin/bin/debug"
			else
				targetdir "bin/debug"
			end
			targetsuffix "_d"
			implibdir "bin/lib"
			defines {
				"DEBUG",
				"_DEBUG"
			}
			flags {
				"Symbols"
			}
			libdirs (libSearchDirs)
			links (linklibs_libgol_debug)

		configuration "Release"
			if os.get() == "macosx" then -- very ugly hotfix to make shit work with OS X. If you know any better, please fix!
				targetdir "bin/bin/release"
			else
				targetdir "bin/release"
			end
			implibdir "bin/lib"
			defines {
				"NDEBUG"
			}
			flags {
				"Optimize"
			}
			libdirs (libSearchDirs)
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
			if os.get() == "macosx" then -- very ugly hotfix to make shit work on OS X. If you know any better, please fix!
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
			links (linklibs_2D_debug)

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
			links (linklibs_3D_debug)
			
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
