#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

loadtext y[core];

hook OnGameModeInit()
{
	Command_SetDeniedReturn(true);
	Group_SetGlobalCommandDefault(false);

	SetColour("ERROR", 0xFF6347FF);
	SetColour("SUCCESS", X11_GREEN);
	SetColour("INFO", X11_LIGHT_BLUE);
	SetColour("NORMAL", X11_WHITE);
	SetColour("YELLOW", X11_YELLOW);
	SetColour("ALERT", X11_FIREBRICK);
	SetColour("KHAKI", X11_KHAKI);

	defer onAllInitiated();
}

timer onAllInitiated[100]()
{
	call OnGroupInit();
}

public e_COMMAND_ERRORS:OnPlayerCommandReceived(playerid, cmdtext[], e_COMMAND_ERRORS:success) 
{
    if(!IsLoggedIn(playerid))
    {
		Text_Send(playerid, $LOGIN_REQUIRED);
		return COMMAND_DENIED;
    }

    switch(success)
    {
    	case COMMAND_DENIED:
    	{
			Text_Send(playerid, $UNAUTHORIZED_ACTION_CMD);
    		return COMMAND_DENIED;
    	}
    	case COMMAND_UNDEFINED:
    	{
			Text_Send(playerid, $UNKNOWN_CMD);
    		return COMMAND_OK;
    	}
    }
    return success;
}

public OnQueryError(errorid, const error[], const callback[], const query[], MySQL:handle)
{
	switch(errorid) {
		case CR_SERVER_GONE_ERROR: {
			err("Lost connection to server");
		}
		case ER_SYNTAX_ERROR: {
			err("Something is wrong in your syntax, query: %s",query);
		}
		default: {
			err("Other mysql error %d %s (callback %s), query %s", errorid, error, callback, query);
		}
	}
	return 1;
}

FadeToWhite(colour, Float:percent)
{
	if (percent <= 0.0) {
		return colour;
	}

	if (percent >= 1.0) {
		return 0xFFFFFF;
	}

	new
		r = (colour >> 16) & 0xFF,
		g = (colour >> 8) & 0xFF,
		b = colour & 0xFF,
		dr = floatround((0xFF - r) * percent),
		dg = floatround((0xFF - g) * percent),
		db = floatround((0xFF - b) * percent)
	;

	return ((r + dr) << 16) + ((g + dg) << 8) + (b + db);
}