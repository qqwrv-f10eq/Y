#if defined _inc_header
	#undef _inc_header
#endif

#include <samp_bcrypt>
#include <YSI_Players\y_text>
#include <YSI_Visual\y_dialog>
#include <YSI_Coding\y_inline>

enum e_ERROR_PASSWORD {
	e_ERROR_PASSWORD_NONE,
	e_ERROR_PASSWORD_EMPTY,
	e_ERROR_PASSWORD_SHORT,
	e_ERROR_PASSWORD_LONG
}

#define ALS_DO_PlayerRegister<%0> %0<PlayerRegister,i>(end:playerid)
