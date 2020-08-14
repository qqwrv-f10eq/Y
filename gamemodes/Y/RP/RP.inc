#if defined _inc_Y
	#undef _inc_Y
#endif

#if !defined Y_RP_HEADER

	#include "core\header"
	#include "utils\header"
	#include "entities\header"
	

	#define Y_RP_HEADER
#elseif !defined Y_RP_END

	#include "core\impl"
	#include "utils\impl"
	#include "entities\impl"


	#define Y_RP_END
#else
	#error Y rp already set up
#endif