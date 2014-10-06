// --------------------------------------------------------------
// define export macros
// --------------------------------------------------------------

#ifndef __LIB_GOL_EXPORT_HPP__
#	define __LIB_GOL_EXPORT_HPP__

	// headers
#	include <gol/Config.hpp>

#	if defined(LIB_GOL_DYNAMIC)
#		define LIB_GOL_API LIB_GOL_EXPORT
#	else
#		define LIB_GOL_API LIB_GOL_IMPORT
#	endif

#endif // __LIB_GOL_EXPORT_HPP__
