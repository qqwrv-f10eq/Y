#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

loadtext y_players[character];

static 
	PlayerText:charSelectTextDraw[MAX_PLAYERS][Y_PLAYER_MAX_CHARACTER_TEXTDRAW] = { PlayerText:INVALID_TEXT_DRAW, ... },
	charSelectTextDrawID[MAX_PLAYERS][Y_PLAYER_MAX_CHARACTER],
	charSelectTextDrawCount[MAX_PLAYERS],
	characterLister[MAX_PLAYERS][Y_PLAYER_MAX_CHARACTER]
; 

SelectCharacter(playerid)
{
	new query[160];

	mysql_format(dbHandle, query, sizeof query, "SELECT c.id, c.name, s.level, s.skin FROM " CHARACTER_TABLE " c LEFT JOIN " CHARACTER_STATUS_TABLE " s ON c.id = s.character_id WHERE account_id = %d", _:Player.Auth[playerid][@id]);
	
	inline CharacterFetch()
	{
		if (!cache_num_rows()) {
			#if defined Y_PLAYER_IG_REGISTER_CHARACTER
				@return ShowCreateCharacterDialog(playerid);
			#else
				Text_Send(playerid, $CHARACTER_NOT_FOUND);
				Text_Send(playerid, $CHARACTER_REGISTER_ON, WEBSITE_URL);
				defer TimedKick(playerid);
				@return 1;
			#endif
		}

		new rows;
		cache_get_row_count(rows);

		#if defined Y_PLAYER_NO_MULTI_CHARACTER
	
			cache_get_value_name_int(0, "id", _:Player.Status[playerid][@id]);

			#if defined Y_PLAYER_VERIFY_CHARACTER
			VerifyAccount(playerid);
			#else
			call OnPlayerLogin(playerid);
			#endif

			@return log("load single character from %d", playerid);

		#else

			new 
				str[40],
				playerLevel, 
				playerLastSkin,
				playerName[MAX_PLAYER_NAME + 1],
				Float:td_posY= 121.0
			;

			#if defined Y_PLAYER_IG_REGISTER_CHARACTER
			new Float:td_posX= 318.0 - (85.0 * float((rows > 3 ? 3 : rows) - ((rows < 3) ? 0 : 1))) + (5.0 * float((rows > 3 ? 3 : rows) - ((rows < 3) ? 0 : 1)));
			#else
			new Float:td_posX= 318.0 - (85.0 * float((rows > 3 ? 3 : rows) - 1)) + (5.0 * float((rows > 3 ? 3 : rows) - 1));
			#endif

			for (new i = 0; i < rows; i ++)
			{
				cache_get_value_name_int(i, "id", characterLister[playerid][i]);
				cache_get_value_name(i, "name", playerName);
				cache_get_value_name_int(i, "level", playerLevel);
				cache_get_value_name_int(i, "skin", playerLastSkin);

				charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]] = CreatePlayerTextDraw(playerid, td_posX, td_posY, "_");
				PlayerTextDrawFont(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 1);
				PlayerTextDrawLetterSize(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 0.595833, 16.450000);
				PlayerTextDrawTextSize(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 255.500000, 148.500000);
				PlayerTextDrawSetOutline(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 1);
				PlayerTextDrawSetShadow(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 0);
				PlayerTextDrawAlignment(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 2);
				PlayerTextDrawColor(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], -1);
				PlayerTextDrawBackgroundColor(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 255);
				PlayerTextDrawBoxColor(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 70);
				PlayerTextDrawUseBox(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 1);
				PlayerTextDrawSetProportional(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 1);
				PlayerTextDrawSetSelectable(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]++], 0);

				format(str, sizeof(str), "%s~n~Level %d", playerName, playerLevel);
				charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]] = CreatePlayerTextDraw(playerid, td_posX - 73.0, td_posY, str);
				PlayerTextDrawFont(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 1);
				PlayerTextDrawLetterSize(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 0.183329, 0.849995);
				PlayerTextDrawTextSize(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], td_posX + 82.0, 17.000000);
				PlayerTextDrawSetOutline(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 0);
				PlayerTextDrawSetShadow(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 0);
				PlayerTextDrawAlignment(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 1);
				PlayerTextDrawColor(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], -1);
				PlayerTextDrawBackgroundColor(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 255);
				PlayerTextDrawBoxColor(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 50);
				PlayerTextDrawUseBox(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 0);
				PlayerTextDrawSetProportional(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 1);
				PlayerTextDrawSetSelectable(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]++], 0);

				charSelectTextDrawID[playerid][i] = charSelectTextDrawCount[playerid];
				charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]] = CreatePlayerTextDraw(playerid, td_posX - 83.0, td_posY + 13.0, "Preview_Model");
				PlayerTextDrawFont(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 5);
				PlayerTextDrawLetterSize(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 0.600000, 2.000000);
				PlayerTextDrawTextSize(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 166.500000, 140.500000);
				PlayerTextDrawSetOutline(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 0);
				PlayerTextDrawSetShadow(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 0);
				PlayerTextDrawAlignment(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 1);
				PlayerTextDrawColor(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], -1);
				PlayerTextDrawBackgroundColor(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 0);
				PlayerTextDrawBoxColor(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 255);
				PlayerTextDrawUseBox(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 0);
				PlayerTextDrawSetProportional(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 1);
				PlayerTextDrawSetSelectable(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 1);
				PlayerTextDrawSetPreviewModel(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], playerLastSkin);
				PlayerTextDrawSetPreviewRot(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], -8.000000, 0.000000, -1.000000, 0.979999);
				PlayerTextDrawSetPreviewVehCol(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]++], 1, 1);

				td_posX += 160.0;

				if (i != 0 && i%2 == 0) {
					td_posY += 164;
					#if defined Y_PLAYER_IG_REGISTER_CHARACTER
					td_posX= 318.0 - (65.0 * float(rows - 3) - ((rows < 3) ? 0 : 1)) + (5.0 * float(rows - 3) - ((rows < 3) ? 0 : 1));
					#else
					td_posX= 318.0 - (65.0 * float(rows - 3) - 1) + (5.0 * float(rows - 3) - 1);
					#endif
				}
			}

			#if defined Y_PLAYER_IG_REGISTER_CHARACTER
			if (rows + 1 < Y_PLAYER_MAX_CHARACTER) {
				new i  = rows + 1;
				characterLister[playerid][i] = -1;
				charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]] = CreatePlayerTextDraw(playerid, td_posX, td_posY, "_");
				PlayerTextDrawFont(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 1);
				PlayerTextDrawLetterSize(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 0.595833, 16.450000);
				PlayerTextDrawTextSize(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 255.500000, 148.500000);
				PlayerTextDrawSetOutline(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 1);
				PlayerTextDrawSetShadow(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 0);
				PlayerTextDrawAlignment(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 2);
				PlayerTextDrawColor(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], -1);
				PlayerTextDrawBackgroundColor(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 255);
				PlayerTextDrawBoxColor(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 70);
				PlayerTextDrawUseBox(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 1);
				PlayerTextDrawSetProportional(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 1);
				PlayerTextDrawSetSelectable(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]++], 0);

				charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]] = CreatePlayerTextDraw(playerid, td_posX - 73.0, td_posY, "NEW CHARACTER");
				PlayerTextDrawFont(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 1);
				PlayerTextDrawLetterSize(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 0.183329, 0.849995);
				PlayerTextDrawTextSize(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], td_posX + 82.0, 17.000000);
				PlayerTextDrawSetOutline(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 0);
				PlayerTextDrawSetShadow(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 0);
				PlayerTextDrawAlignment(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 1);
				PlayerTextDrawColor(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], -1);
				PlayerTextDrawBackgroundColor(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 255);
				PlayerTextDrawBoxColor(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 50);
				PlayerTextDrawUseBox(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 0);
				PlayerTextDrawSetProportional(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 1);
				PlayerTextDrawSetSelectable(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]++], 0);

				charSelectTextDrawID[playerid][i] = charSelectTextDrawCount[playerid];
				charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]] = CreatePlayerTextDraw(playerid, td_posX - 83.0, td_posY + 13.0, "Preview_Model");
				PlayerTextDrawFont(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 5);
				PlayerTextDrawLetterSize(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 0.600000, 2.000000);
				PlayerTextDrawTextSize(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 166.500000, 140.500000);
				PlayerTextDrawSetOutline(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 0);
				PlayerTextDrawSetShadow(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 0);
				PlayerTextDrawAlignment(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 1);
				PlayerTextDrawColor(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], -1);
				PlayerTextDrawBackgroundColor(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 0);
				PlayerTextDrawBoxColor(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 255);
				PlayerTextDrawUseBox(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 0);
				PlayerTextDrawSetProportional(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 1);
				PlayerTextDrawSetSelectable(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 1);
				PlayerTextDrawSetPreviewModel(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], 264);
				PlayerTextDrawSetPreviewRot(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]], -8.000000, 0.000000, -1.000000, 0.979999);
				PlayerTextDrawSetPreviewVehCol(playerid, charSelectTextDraw[playerid][charSelectTextDrawCount[playerid]++], 1, 1);

				td_posX += 160.0;

				if (i != 0 && i%2 == 0) {
					td_posY += 164;
					td_posX= 318.0 - (65.0 * float(rows - 3)) + (5.0 * float(rows - 3));
				}
			}
			#endif
			
			for (new i; i < charSelectTextDrawCount[playerid]; i++)
				PlayerTextDrawShow(playerid, charSelectTextDraw[playerid][i]);

			SelectTextDraw(playerid, 0xFFFFFF95);

			@return log("load %d character from %d", rows, playerid);

		#endif
	}

	mysql_tquery_inline(dbHandle, query, using inline CharacterFetch);
}

hook OnPlayerClickTextDraw(playerid, Text:clickedid) {
	if(charSelectTextDraw[playerid][0] != PlayerText:INVALID_TEXT_DRAW) {
		if (_:clickedid == _:INVALID_TEXT_DRAW) {
			SelectTextDraw(playerid, 0xFFFFFF95);
			return Y_HOOKS_BREAK_RETURN_1;
		}
	}
	return 1;
}

hook OP_ClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	if(charSelectTextDraw[playerid][0] != PlayerText:INVALID_TEXT_DRAW) {

		for (new i; i != Y_PLAYER_MAX_CHARACTER; i++)
		{
			if (playertextid == charSelectTextDraw[playerid][charSelectTextDrawID[playerid][i]])
			{
				CancelSelectTextDraw(playerid);
				for (new x; x < charSelectTextDrawCount[playerid]; x++) {
					PlayerTextDrawDestroy(playerid, charSelectTextDraw[playerid][x]);
					charSelectTextDraw[playerid][x] = PlayerText:INVALID_TEXT_DRAW;
				}
				charSelectTextDrawCount[playerid] = 0;

				#if defined Y_PLAYER_IG_REGISTER_CHARACTER
				if (_:characterLister[playerid][i] == -1) {
					ShowCreateCharacterDialog(playerid);
					return Y_HOOKS_BREAK_RETURN_1;
				}
				#endif

				Player.Status[playerid][@id] = DBID:characterLister[playerid][i];
				
				#if defined Y_PLAYER_VERIFY_CHARACTER
				VerifyAccount(playerid);
				#else
				call OnPlayerLogin(playerid);
				#endif
				return Y_HOOKS_BREAK_RETURN_1;
			}
		}
		SelectTextDraw(playerid, 0xFFFFFF95);
		return Y_HOOKS_BREAK_RETURN_1;
	}
    return 1;
}

hook OnPlayerLogin(playerid)
{
	log("OPL Called");
	SetPlayerColor(playerid, 0xFFFFFF00);
	Group_SetPlayer(LoggedGroup, playerid, true);
	// SpawnPlayer(playerid); // ใช้ TogglePlayerSpectating แทน
	TogglePlayerSpectating(playerid, false);

	return 1;
}

#if defined Y_PLAYER_IG_REGISTER_CHARACTER
ShowCreateCharacterDialog(playerid, e_ERROR_CHARACTER:errorCode = e_ERROR_CHARACTER_NONE)
{
	new
		error[64]
	;

	if (errorCode != e_ERROR_CHARACTER_NONE) {
		switch (errorCode) {
			case e_ERROR_PASSWORD_EMPTY: {
				Text_Format_Dialog(error, sizeof error, Langs_GetPlayerLanguage(playerid), $CHARACTER_NAME_EMPTY);
			}
			case e_ERROR_PASSWORD_SHORT: {
				Text_Format_Dialog(error, sizeof error, Langs_GetPlayerLanguage(playerid), $CHARACTER_TOO_SHORT, Y_PLAYER_CHARACTER_NAME_MIN_PASS_LENGTH);
			}
			case e_ERROR_PASSWORD_LONG: {
				Text_Format_Dialog(error, sizeof error, Langs_GetPlayerLanguage(playerid), $CHARACTER_TOO_LONG, Y_PLAYER_CHARACTER_NAME_MAX_PASS_LENGTH);
			}
			case e_ERROR_CHARACTER_VALID_NAME: {
				Text_Format_Dialog(error, sizeof error, Langs_GetPlayerLanguage(playerid), $CHARACTER_NAME_NOT_VALID);
			}
		}
	}

	inline HandleCreationCharacter(pid, dialogid, response, listitem, string:inputtext[])
	{
		#pragma unused pid, dialogid, listitem

		if (!response) {
			ShowCreateCharacterDialog(playerid);
			@return 1;
		}

		new len = strlen(inputtext);

		if (isnull(inputtext)) {
			@return ShowCreateCharacterDialog(playerid, e_ERROR_CHARACTER_EMPTY);
		}

		if (len < Y_PLAYER_CHARACTER_NAME_MIN_PASS_LENGTH) {
			@return ShowCreateCharacterDialog(playerid, e_ERROR_CHARACTER_SHORT);
		}

		if (len > Y_PLAYER_CHARACTER_NAME_MAX_PASS_LENGTH || len > 24) {
			@return ShowCreateCharacterDialog(playerid, e_ERROR_CHARACTER_LONG);
		}

		if (funcidx(Y_PLAYER_RESTRICT_NAME_FUNC) != -1) {
			new ret = CallLocalFunction(Y_PLAYER_RESTRICT_NAME_FUNC, "s", inputtext);

			if(ret != 1) {
				@return ShowCreateCharacterDialog(playerid, e_ERROR_CHARACTER_VALID_NAME);
			}
		}

		new query[256];

		inline OnCharacterCreated()
		{
			if (!cache_affected_rows()) {
				@return log("Can't add create %d character", playerid);
			}

			Player.Status[playerid][@id] = DBID:cache_insert_id();

			inline OnStatusCreated() 
			{
				if (!cache_affected_rows()) {
					@return log("Can't add create %d character status", playerid);
				}
				SelectCharacter(playerid);
				@return 1;
			}
			mysql_format(dbHandle, query, sizeof query, "INSERT INTO " CHARACTER_STATUS_TABLE " (character_id) VALUES (%d)", _:Player.Status[playerid][@id]);
			mysql_pquery_inline(dbHandle, query, using inline OnStatusCreated);

			@return 1;
		}

		mysql_format(dbHandle, query, sizeof(query), "INSERT INTO " CHARACTER_TABLE " (name, account_id) VALUES('%e', %d)", inputtext, _:Player.Auth[playerid][@id]);
		mysql_tquery_inline(dbHandle, query, using inline OnCharacterCreated);
	}

	Text_InputBox(playerid, using inline HandleCreationCharacter, $CHARACTER_BOX_TITLE, $CHARACTER_BOX_TEXT, $CHARACTER_BOX_CREATE, $CHARACTER_BOX_EXIT, error, Y_PLAYER_CHARACTER_NAME_MIN_PASS_LENGTH, Y_PLAYER_CHARACTER_NAME_MAX_PASS_LENGTH);
	return 1;
}
#endif

forward CharacaterRestrictName(const string[]);
public CharacaterRestrictName(const string[])
{
    for( new i = 0; string[ i ] != EOS; ++i )
	{
        switch( string[ i ] )
		{
            /*here your all chars*/
            case '0'..'9', 'A'..'Z', 'a'..'z','_','@',',': continue;
            default: return false;
        }
    }
    return true;
}