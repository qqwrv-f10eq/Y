#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

loadtext y_rp_players[chat];

hook OnGroupInit()
{
	GROUP_ADD<LoggedGroup>
	{
		@YCMD:me;
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
            /*if (len > 80) {

                Text_Format_Client(message, sizeof message, Langs_GetPlayerLanguage(i), $SAYS_LINE_A, Player.RP[playerid][@name], text);
                Text_Format_Client(message2, sizeof message2, Langs_GetPlayerLanguage(i), $SAYS_LINE_B, text[80]);

                if (fDistance > 16.0) {
                    SendClientMessage(i, X11_GRAY60, message);
                    SendClientMessage(i, X11_GRAY60, message2);
                }
                else if (fDistance > 8.0) {
                    SendClientMessage(i, X11_GRAY63, message);
                    SendClientMessage(i, X11_GRAY63, message2);  
                }
                else if (fDistance > 4.0) {
                    SendClientMessage(i, X11_GRAY67, message);
                    SendClientMessage(i, X11_GRAY67, message2);
                }
                else if (fDistance > 2.0) {
                    SendClientMessage(i, X11_GRAY70, message);
                    SendClientMessage(i, X11_GRAY70, message2);
                } else {
                    SendClientMessage(i, X11_GRAY80, message);
                    SendClientMessage(i, X11_GRAY80, message2);
                } 
            }
            else {
                Text_Format_Client(message, sizeof message, Langs_GetPlayerLanguage(i), $SAYS, Player.RP[playerid][@name], text);

                if (fDistance > 16.0) {
                    SendClientMessage(i, X11_GRAY60, message);
                }
                else if (fDistance > 8.0) {
                    SendClientMessage(i, X11_GRAY63, message);
                }
                else if (fDistance > 4.0) {
                    SendClientMessage(i, X11_GRAY67, message);
                }
                else if (fDistance > 2.0) {
                    SendClientMessage(i, X11_GRAY70, message);
                } else {
                    SendClientMessage(i, X11_GRAY80, message);
                }   
            }*/
		}
	}
	return Y_HOOKS_BREAK_RETURN_0;
}

YCMD:me(playerid, params[], help)
{
    if( help ) return SendClientMessage(playerid, -1, "not support !");

    if(isnull(params)) return Text_Send(playerid, $INVALID_COMMAND_PARAMS_ME, YCMD:me);

	if (strlen(params) > 80) {
	    SendNearbyMessage(playerid, 20.0, COLOR_ACTION, "* %s %.80s", Player.RP[playerid][@name], params);
	    SendNearbyMessage(playerid, 20.0, COLOR_ACTION, "... %s", params[80]);
	}
	else SendNearbyMessage(playerid, 20.0, COLOR_ACTION, "* %s %s", Player.RP[playerid][@name], params);

    return 1;
}