#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnGameModeInit()
{
	DeveloperGroup = Group_Create("Developer");
	return 1;
}