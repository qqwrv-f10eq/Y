#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

RPizeName(name[], len = sizeof name)
{
	for (new i = 0; i != len; ++i) {
		if (name[i] == '_') {
			name[i] = ' ';
		}
	}
}