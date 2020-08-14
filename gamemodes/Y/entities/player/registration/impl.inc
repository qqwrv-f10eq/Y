#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

loadtext y_players[auth];

hook OnPlayerRegister(playerid)
{
	#if defined Y_PLAYER_LOGIN_AFTER_REG
	SelectCharacter(playerid);
	#else
	FetchPlayer(playerid);
	#endif

	return 1;
}

ShowRegistrationDialog(playerid, e_ERROR_PASSWORD:errorCode = e_ERROR_PASSWORD_NONE)
{
	new
		error[64]
	;

	if (errorCode != e_ERROR_PASSWORD_NONE) {
		switch (errorCode) {
			case e_ERROR_PASSWORD_EMPTY: {
				Text_Format_Dialog(error, sizeof error, Langs_GetPlayerLanguage(playerid), $PASSWORD_EMPTY);
			}
			case e_ERROR_PASSWORD_SHORT: {
				Text_Format_Dialog(error, sizeof error, Langs_GetPlayerLanguage(playerid), $PASSWORD_TOO_SHORT, Y_PLAYER_REGISTRATION_MIN_PASS_LENGTH);
			}
			case e_ERROR_PASSWORD_LONG: {
				Text_Format_Dialog(error, sizeof error, Langs_GetPlayerLanguage(playerid), $PASSWORD_TOO_LONG, Y_PLAYER_REGISTRATION_MAX_PASS_LENGTH);
			}
		}
	}

	inline HandleRegistration(pid, dialogid, response, listitem, string:inputtext[])
	{
		#pragma unused pid, dialogid, listitem

		if (!response) {
			defer TimedKick(playerid);
			@return 1;
		}

		CheckRegistrationPassword(playerid, inputtext);
	}
	Text_PasswordBox(playerid, using inline HandleRegistration, $REGISTRATION_BOX_TITLE, $REGISTRATION_BOX_TEXT, $REGISTRATION_BOX_REGISTER, $REGISTRATION_BOX_EXIT, error, Y_PLAYER_REGISTRATION_MIN_PASS_LENGTH, Y_PLAYER_REGISTRATION_MAX_PASS_LENGTH);
	return 1;
}

CheckRegistrationPassword(playerid, password[])
{
	new len = strlen(password);

	if (isnull(password)) {
		return ShowRegistrationDialog(playerid, e_ERROR_PASSWORD_EMPTY);
	}

	if (len < Y_PLAYER_REGISTRATION_MIN_PASS_LENGTH) {
		return ShowRegistrationDialog(playerid, e_ERROR_PASSWORD_SHORT);
	}

	if (len > Y_PLAYER_REGISTRATION_MAX_PASS_LENGTH) {
		return ShowRegistrationDialog(playerid, e_ERROR_PASSWORD_LONG);
	}

	return Register(playerid, password);
}

Register(playerid, const password[])
{
	bcrypt_hash(playerid, "OnPassswordHash", password, Y_BCRYPT_WORK_FACTOR);
	return 1;
}

forward OnPassswordHash(playerid);
public OnPassswordHash(playerid)
{	
	new dest[250];
	bcrypt_get_hash(dest);
	strcpy(Player.Auth[playerid][@password], dest);
	new
		query[320]
	;
	mysql_format(dbHandle, query, sizeof query, "INSERT INTO " PLAYER_TABLE " (name, password) VALUES ('%e', '%e')", Player.Auth[playerid][@name], Player.Auth[playerid][@password]);
	
	inline SavePlayer()
	{
		Player.Auth[playerid][@id] = DBID:cache_insert_id();
		call OnPlayerRegister(playerid);
	}
	mysql_tquery_inline(dbHandle, query, using inline SavePlayer);
}