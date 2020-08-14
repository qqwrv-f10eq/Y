#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnPlayerInit(playerid)
{
	strcpy(Player.RP[playerid][@name], Player.Status[playerid][@name]);
	RPizeName(Player.RP[playerid][@name]);
	SetPlayerSkin(playerid, Player.Status[playerid][@skin]);
	return 1;
}