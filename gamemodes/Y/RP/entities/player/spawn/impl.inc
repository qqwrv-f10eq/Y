#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnPlayerInit(playerid)
{
	SetPlayerPos(playerid, Y_DEFAULT_SPAWN_LOCATION_X, Y_DEFAULT_SPAWN_LOCATION_Y, Y_DEFAULT_SPAWN_LOCATION_Z);
	SetPlayerInterior(playerid, 0);
	SetPlayerVirtualWorld(playerid, 0);
	return 1;
}