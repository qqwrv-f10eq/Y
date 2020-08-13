#if defined _inc_Y
	#undef _inc_Y
#endif

#if !defined Y_@@@@_HEADER
	#include "core\header"
	#include "db\header"
	#include "log\header"
	#include "debug\header"
	#include "utils\header"
	#include "language\header"


	#include "object\header"

	#if defined Y_MODE_RP
		#include "RP\RP"
	#endif

	#define Y_@@@@_HEADER
#elseif !defined Y_@@@@_END
	#include "core\impl"
	#include "db\impl"
	#include "debug\impl"
	#include "utils\impl"
	#include "language\impl"

	#include "object\impl"

	#if defined Y_MODE_RP
		#include "RP\RP"
	#endif
	#define Y_@@@@_END
#else
	#error Y core already set up
#endif