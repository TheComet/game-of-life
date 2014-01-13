// --------------------------------------------------------------
// define export macros
// --------------------------------------------------------------

#ifndef __PONY_LIB_EXPORT_HPP__
#	define __PONY_LIB_EXPORT_HPP__

	// headers
#	include <pony/general/config.hpp>

#	if defined(PONY_LIB_DYNAMIC)
#		define PONY_LIB_API PONY_LIB_EXPORT
#	else
#		define PONY_LIB_API PONY_LIB_IMPORT
#	endif

#endif // __PONY_LIB_EXPORT_HPP__
