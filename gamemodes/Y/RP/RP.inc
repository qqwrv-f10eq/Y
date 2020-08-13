#if defined _inc_Y
	#undef _inc_Y
#endif

#if !defined Y_RP_HEADER


	#define Y_RP_HEADER
#elseif !defined Y_RP_END


	#define Y_RP_END
#else
	#error Y rp already set up
#endif