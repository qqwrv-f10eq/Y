#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

loadtext y_rp_players[chat];

hook OnGroupInit()
{
    Command_AddAltNamed("shout", "s");
    Command_AddAltNamed("local", "t");
    Command_AddAltNamed("local", "l");
    
	GROUP_ADD<LoggedGroup>
	{
		@YCMD:me;
        @YCMD:do;
        @YCMD:dolow;
        @YCMD:ame;
        @YCMD:local;
        @YCMD:l;
        @YCMD:t;
        @YCMD:low;
        @YCMD:shout;
        @YCMD:s;
        @YCMD:b;
	}
}

hook OnPlayerText(playerid, text[]) 
{
	new 
        Float:posx, 
        Float:posy, 
        Float:posz,
        len = strlen(text)
    ;

	GetPlayerPos(playerid, posx, posy, posz);

	foreach(new i:GroupMember(LoggedGroup)) {
		if(GetPlayerInterior(playerid) == GetPlayerInterior(i) && GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(i)) {

            if (IsPlayerInRangeOfPoint(i, 20.0, posx, posy, posz)) {
                Text_Send(i, $SAYS, Player.RP[playerid][@name], text);
                if (len > 80) {
                    Text_Send(i, $SAYS_NEXT, text[80]);
                }
            }
		}
	}
	return Y_HOOKS_BREAK_RETURN_0;
}

YCMD:me(playerid, params[], help)
{
    if( help ) return SendClientMessage(playerid, -1, "not support !");

    if(isnull(params)) return Text_Send(playerid, $INVALID_COMMAND_PARAMS_ACTION, YCMD:me);

	if (strlen(params) > 80) {
	    SendNearbyMessage(playerid, 20.0, COLOR_ACTION, "* %s %.80s", Player.RP[playerid][@name], params);
	    SendNearbyMessage(playerid, 20.0, COLOR_ACTION, "... %s", params[80]);
	}
	else SendNearbyMessage(playerid, 20.0, COLOR_ACTION, "* %s %s", Player.RP[playerid][@name], params);

    return 1;
}

YCMD:do(playerid, params[], help)
{
    if( help ) return SendClientMessage(playerid, -1, "not support !");

    if(isnull(params)) return Text_Send(playerid, $INVALID_COMMAND_PARAMS_EMOTE, YCMD:do);

	if (strlen(params) > 80) {
	    SendNearbyMessage(playerid, 20.0, COLOR_ACTION, "* %s", params);
	    SendNearbyMessage(playerid, 20.0, COLOR_ACTION, "... %s (( %s ))", params[80], Player.RP[playerid][@name]);
	}
	else SendNearbyMessage(playerid, 20.0, COLOR_ACTION, "* %s (( %s ))", params, Player.RP[playerid][@name]);

    return 1;
}

YCMD:ame(playerid, params[], help)
{
    if( help ) return SendClientMessage(playerid, -1, "not support !");

    if(isnull(params)) return Text_Send(playerid, $INVALID_COMMAND_PARAMS_ACTION, YCMD:ame);
	
	new string[144 + 1];
	format(string, sizeof(string), "* %s %s", Player.RP[playerid][@name], params);
	SendClientMessage(playerid, COLOR_ACTION, string);

 	SetPlayerChatBubble(playerid, string, COLOR_ACTION, 30.0, 6000);
	return 1;
}

YCMD:dolow(playerid, params[], help)
{
    if( help ) return SendClientMessage(playerid, -1, "not support !");

    if(isnull(params)) return Text_Send(playerid, $INVALID_COMMAND_PARAMS_EMOTE, YCMD:dolow);

	if (strlen(params) > 80) {
	    SendNearbyMessage(playerid, 10.0, COLOR_ACTION, "* %s", params);
	    SendNearbyMessage(playerid, 10.0, COLOR_ACTION, "... %s (( %s ))", params[80], Player.RP[playerid][@name]);
	}
	else SendNearbyMessage(playerid, 10.0, COLOR_ACTION, "* %s (( %s ))", params, Player.RP[playerid][@name]);

	return 1;
}

YCMD:local(playerid, params[], help)
{
    if( help ) return SendClientMessage(playerid, -1, "not support !");
    if(isnull(params)) return Text_Send(playerid, $INVALID_COMMAND_PARAMS_TEXT, YCMD:local);

	new 
        Float:posx, 
        Float:posy, 
        Float:posz,
        len = strlen(params)
    ;

	GetPlayerPos(playerid, posx, posy, posz);

	foreach(new i:GroupMember(LoggedGroup)) {
		if(GetPlayerInterior(playerid) == GetPlayerInterior(i) && GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(i)) {

            if (IsPlayerInRangeOfPoint(i, 20.0, posx, posy, posz)) {
                Text_Send(i, $SAYS, Player.RP[playerid][@name], params);
                if (len > 80) {
                    Text_Send(i, $SAYS_NEXT, params[80]);
                }
            }
		}
	}
	return 1;
}

YCMD:low(playerid, params[], help)
{
    if( help ) return SendClientMessage(playerid, -1, "not support !");
    if(isnull(params)) return Text_Send(playerid, $INVALID_COMMAND_PARAMS_TEXT, YCMD:low);
	
	new 
        Float:posx, 
        Float:posy, 
        Float:posz,
        len = strlen(params)
    ;

	GetPlayerPos(playerid, posx, posy, posz);

	foreach(new i:GroupMember(LoggedGroup)) {
		if(GetPlayerInterior(playerid) == GetPlayerInterior(i) && GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(i)) {

            if (IsPlayerInRangeOfPoint(i, 20.0, posx, posy, posz)) {
                Text_Send(i, $LOW, Player.RP[playerid][@name], params);
                if (len > 80) {
                    Text_Send(i, $SAYS_NEXT, params[80]);
                }
            }
		}
	}
	return 1;
}


YCMD:shout(playerid, params[], help)
{
    if( help ) return SendClientMessage(playerid, -1, "not support !");
    if(isnull(params)) return Text_Send(playerid, $INVALID_COMMAND_PARAMS_TEXT, YCMD:shout);

	new 
        Float:posx, 
        Float:posy, 
        Float:posz,
        len = strlen(params)
    ;

	GetPlayerPos(playerid, posx, posy, posz);

	foreach(new i:GroupMember(LoggedGroup)) {
		if(GetPlayerInterior(playerid) == GetPlayerInterior(i) && GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(i)) {

            if (IsPlayerInRangeOfPoint(i, 30.0, posx, posy, posz)) {
                if (len > 80) {
                    Text_Send(i, $SHOUT_A, Player.RP[playerid][@name], params);
                    Text_Send(i, $SHOUT_B, params[80]);
                }
                else {
                    Text_Send(i, $SHOUT, Player.RP[playerid][@name], params);
                }
            }
		}
	}
	return 1;
}

YCMD:b(playerid, params[], help)
{
    if( help ) return SendClientMessage(playerid, -1, "not support !");
    if(isnull(params)) return Text_Send(playerid, $INVALID_COMMAND_PARAMS_TEXT, YCMD:b);

	if(IsOnAdminDuty(playerid))
	{
		if(strlen(params) > 80)
		{
			SendNearbyMessage(playerid, 20.0, X11_LIGHTBLUE3, "(( "ORANGE"%s"LIGHTBLUE3": %.84s ))", Player.Status[playerid][@name], params);
			SendNearbyMessage(playerid, 20.0, X11_LIGHTBLUE3, "(( "ORANGE"%s"LIGHTBLUE3": ...%s ))", Player.Status[playerid][@name], params[80]);
		}
		else SendNearbyMessage(playerid, 20.0, X11_LIGHTBLUE3, "(( "ORANGE"%s"LIGHTBLUE3": %s ))", Player.Status[playerid][@name], params);
	}
	else
	{
		if(strlen(params) > 80)
		{
			SendNearbyMessage(playerid, 20.0, X11_LIGHTBLUE3, "(( %s: %.84s ))", Player.Status[playerid][@name], params);
			SendNearbyMessage(playerid, 20.0, X11_LIGHTBLUE3, "(( %s: ...%s ))", Player.Status[playerid][@name], params[80]); 
		}
		else SendNearbyMessage(playerid, 20.0, X11_LIGHTBLUE3, "(( %s: %s ))", Player.Status[playerid][@name], params);
	}	

	return 1;
}