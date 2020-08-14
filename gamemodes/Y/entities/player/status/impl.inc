#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnPlayerLogin(playerid)
{
	inline FetchedPlayerStatus()
	{
		if (!cache_num_rows()) {
			@return log("Did not find player %d status data", playerid);
		}

		cache_get_value_name(0, "name", Player.Status[playerid][@name], MAX_PLAYER_NAME + 1);
		cache_get_value_name_int(0, "vip", Player.Status[playerid][@vip]);
		cache_get_value_name_int(0, "money", Player.Status[playerid][@money]);
		cache_get_value_name_int(0, "skin", Player.Status[playerid][@skin]);
		cache_get_value_name_int(0, "admin", Player.Status[playerid][@admin]);

		if (Player.Status[playerid][@admin] > 0) {
			Group_SetPlayer(AdminGroup[Player.Status[playerid][@admin] - 1], playerid, true);
		}
	
		cache_get_value_name_bool(0, "developer", Player.Status[playerid][@developer]);

		if (Player.Status[playerid][@developer]) {
			Group_SetPlayer(DeveloperGroup, playerid, true);
		}

		if(SetPlayerName(playerid, Player.Status[playerid][@name]) == -1)
		{
			@return log("player %d fail to change name", playerid);
		}
		
		defer onPlayerInitiated(playerid);
		@return log("Load player %s status data", Player.Status[playerid][@name]);
	}

	new query[160];
	mysql_format(dbHandle, query, sizeof query, "SELECT s.*, c.name FROM " CHARACTER_STATUS_TABLE " s LEFT JOIN " CHARACTER_TABLE " c ON s.character_id = c.id WHERE s.character_id = %d LIMIT 1", _:Player.Status[playerid][@id]);
	mysql_tquery_inline(dbHandle, query, using inline FetchedPlayerStatus);

	new ip[16];
	GetPlayerIp(playerid, ip, sizeof ip);
	Player.Status[playerid][@ip] = IPToInt(ip);

	return 1;
}

timer onPlayerInitiated[100](playerid)
{
	call OnPlayerInit(playerid);
}