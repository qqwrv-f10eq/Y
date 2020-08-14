#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnGameModeInit()
{
	Languages[0] = Langs_Add("TH", "Thai");
	Languages[1] = Langs_Add("EN", "English");
	return 1;
}

hook OnPlayerConnect(playerid)
{
	Langs_SetPlayerLanguage(playerid, Languages[0]);
	return 1;
}