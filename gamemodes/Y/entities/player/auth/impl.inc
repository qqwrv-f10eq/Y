#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

loadtext y_players[auth];

hook OnGameModeInit()
{
	LoggedGroup = Group_Create("Logged in");

	return 1;
}

hook OnPlayerConnect(playerid)
{
	// ทดสอบตอนรันบนโฮสต์
	if (!isnull(Player.Auth[playerid][@name]))
	{
		SetPlayerName(playerid, Player.Auth[playerid][@name]);
	}
	FetchPlayer(playerid);
	SetSpawnInfo(playerid, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0);
	Text_Send(playerid, $WELCOME_TO_SERVER, SERVER_NAME);
	return 1;
}

hook OnPlayerRequestClass(playerid, classid)
{
	TogglePlayerSpectating(playerid, true);
	return 1;
}

/* // When TogglePlayerSpectating false they already force to spawn
hook OnPlayerSpawn(playerid, classid)
{
	TogglePlayerSpectating(playerid, false);
	return 1;
}*/

FetchPlayer(playerid)
{
	new query[64 + MAX_PLAYER_NAME + 1];
	new name[MAX_PLAYER_NAME + 1];
	GetPlayerName(playerid, name, sizeof name);
	strcpy(Player.Auth[playerid][@name], name);
	mysql_format(dbHandle, query, sizeof query, "SELECT * FROM " PLAYER_TABLE" WHERE name = '%e'", name);
	inline PlayerFetched()
	{
		if (!cache_num_rows()) {
			#if defined Y_PLAYER_IG_REGISTER_ACCOUNT
				@return ShowRegistrationDialog(playerid);
			#else
				Text_Send(playerid, $AUTH_ACCOUNT_NOT_FOUND_A, name);
				Text_Send(playerid, $AUTH_ACCOUNT_NOT_FOUND_B);
				Text_Send(playerid, $AUTH_ACCOUNT_NOT_FOUND_C, WEBSITE_URL);
				defer TimedKick(playerid);
				@return 1;
			#endif
		}
		cache_get_value_name_int(0, "id", _:Player.Auth[playerid][@id]);
		cache_get_value_name(0, "name", Player.Auth[playerid][@name]);
		cache_get_value_name(0, "password", Player.Auth[playerid][@password]);

		@return ShowLoginDialog(playerid);
	}
	mysql_tquery_inline(dbHandle, query, using inline PlayerFetched);

}