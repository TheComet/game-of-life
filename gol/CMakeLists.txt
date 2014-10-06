if (BUILD_STATIC)
	set (LIB_GOL_STATIC 1)
else()
	set (LIB_GOL_DYNAMIC 1)
endif ()
configure_file (
	"${CMAKE_CURRENT_LIST_DIR}/include/gol/Config.hpp.in"
	"${CMAKE_CURRENT_LIST_DIR}/include/gol/Config.hpp"
)

set (gol_HEADERS
	"include/gol/Vector3.hxx"
	"include/gol/Vector2.hxx"
	"include/gol/Vector2.hpp"
	"include/gol/GenericCellField.hxx"
	"include/gol/Exception.hpp"
	"include/gol/Cell.hxx"
	"include/gol/Config.hpp"
	"include/gol/Export.hpp"
	"include/gol/Rule.hpp"
	"include/gol/GenericCellField.hpp"
	"include/gol/Cell.hpp"
	"include/gol/Vector3.hpp"
)
set (gol_SOURCES
	"src/Rule.cpp"
)

include_directories ("include")
add_library (gol ${gol_HEADERS} ${gol_SOURCES})

