#if defined _inc_header
	#undef _inc_header
#endif

#if defined Y_PLAYER_IG_REGISTER_CHARACTER

#define Y_PLAYER_MAX_CHARACTER_TEXTDRAW		(Y_PLAYER_MAX_CHARACTER * 5) + 5 // +1 if display server logo, +5 for New Character button

enum e_ERROR_CHARACTER {
	e_ERROR_CHARACTER_NONE,
	e_ERROR_CHARACTER_EMPTY,
	e_ERROR_CHARACTER_SHORT,
	e_ERROR_CHARACTER_LONG,
	e_ERROR_CHARACTER_VALID_NAME
}

#else

#define Y_PLAYER_MAX_CHARACTER_TEXTDRAW		(Y_PLAYER_MAX_CHARACTER * 5) // +1 if display server logo, +5 for New Character button

#endif

#define CHARACTER_TABLE "characters"