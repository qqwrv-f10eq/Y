#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

loadtext y_rp_players[chat];

hook OnGroupInit()
{
    Command_AddAltNamed("ooc", "o");
	GROUP_ADD<LoggedGroup>
	{
		@YCMD:ooc;
	}
}

hook OnPlayerText(playerid, text[]) 
{
	new 
        Float:posx, 
        Float:posy, 
        Float:posz,
        Float:fDistance,
        len = strlen(text)
    ;

	GetPlayerPos(playerid, posx, posy, posz);

	foreach(new i:GroupMember(LoggedGroup)) {
		if(GetPlayerInterior(playerid) == GetPlayerInterior(i) && GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(i)) {

            fDistance = GetPlayerDistanceFromPoint(i, posx, posy, posz);

            if (fDistance > 20.0)
                continue;

            Text_Send(i, $SAYS, Player.RP[playerid][@name], text);
            if (len > 80) {
                Text_Send(i, $SAYS_NEXT, text[80]);
            }
		}
	}
	return Y_HOOKS_BREAK_RETURN_0;
}

YCMD:ooc(playerid, params[], help)
{
    if( help ) return SendClientMessage(playerid, -1, "not support !");

    if(isnull(params)) return Text_Send(playerid, $INVALID_COMMAND_PARAMS_ME, Command_GetDisplayNamed("ooc"));

	if (strlen(params) > 80) {
	    SendNearbyMessage(playerid, 20.0, COLOR_ACTION, "* %s %.80s", Player.RP[playerid][@name], params);
	    SendNearbyMessage(playerid, 20.0, COLOR_ACTION, "... %s", params[80]);
	}
	else SendNearbyMessage(playerid, 20.0, COLOR_ACTION, "* %s %s", Player.RP[playerid][@name], params);

    return 1;
}