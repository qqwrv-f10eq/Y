#if defined _inc_impl
	#undef _inc_impl
#endif

SendNearbyMessage(playerid, Float:radius, color, const fmat[], {Float,_}:...)
{
	new
		str[145];
	va_format(str, sizeof (str), fmat, va_start<4>);

	foreach(new i:GroupMember(LoggedGroup)) {
        
		if (IsPlayerNearPlayer(i, playerid, radius)) 
		{
			SendClientMessage(i, color, str);
		}
	}
	return 1;
}