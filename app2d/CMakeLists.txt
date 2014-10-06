set (app2d_HEADERS
	"include/app2d/MainFrame.hpp"
	"include/app2d/Background.hpp"
	"include/app2d/CellField.hpp"
	"include/app2d/Exception.hpp"
	"include/app2d/LoopTimer.hpp"
	"include/app2d/Canvas.hpp"
	"include/app2d/Drawable.hpp"
	"include/app2d/App.hpp"
	"include/app2d/wxSFMLCanvas.hpp"
)
set (app2d_SOURCES
	"src/Background.cpp"
	"src/App.cpp"
	"src/main.cpp"
	"src/wxSFMLCanvas.cpp"
	"src/MainFrame.cpp"
	"src/Drawable.cpp"
	"src/Canvas.cpp"
	"src/CellField.cpp"
	"src/LoopTimer.cpp"
)

include_directories ("include")
add_executable (app2d ${app2d_HEADERS} ${app2d_SOURCES})
target_link_libraries (app2d gol)

include (ExternalProject)

set (COMMON_CMAKE_ARGS
	-DCMAKE_INSTALL_PREFIX=${EXTERNAL_DEP_DIR}
	-DCMAKE_PREFIX_PATH=${EXTERNAL_DEP_DIR}
	-DCMAKE_INCLUDE_PATH=${EXTERNAL_DEP_DIR}/include
	-DCMAKE_LIBRARY_PATH=${EXTERNAL_DEP_DIR}/lib
)

find_package (SFML 2 COMPONENTS
	system
	window
	graphics
)
if (SFML_FOUND)
	include_directories (${SFML_INCLUDE_DIRS})
	target_link_libraries (app2d
		${SFML_SYSTEM_LIBRARY}
		${SFML_WINDOW_LIBRARY}
		${SFML_GRAPHICS_LIBRARY}
	)
	add_custom_target (SFML_PROJECT)
else ()
	externalproject_add (SFML_PROJECT
		PREFIX ${EXTERNAL_DEP_DIR}
		GIT_REPOSITORY "git://github.com/LaurentGomila/SFML.git"
		GIT_TAG "2.1"
		CMAKE_ARGS ${COMMON_CMAKE_ARGS}
	)
	target_link_libraries (app2d
		sfml-system
		sfml-window
		sfml-graphics
	)
endif ()
