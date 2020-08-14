#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

loadtext y_players[character];

static 
	PlayerText:charSelectTextDraw[MAX_PLAYERS][MAX_CHARSELECT_TEXTDRAW] = { PlayerText:INVALID_TEXT_DRAW, ... },
	charSelectTextDrawID[MAX_PLAYERS][MAX_CHARSELECT],
	charSelectTextDrawCount[MAX_PLAYERS],
	characterLister[MAX_PLAYERS][MAX_CHARSELECT]
; 

SelectCharacter(playerid)
{
	new query[160];

	mysql_format(dbHandle, query, sizeof query, "SELECT c.id, c.name, s.level, s.skin FROM " CHARACTER_TABLE " c LEFT JOIN " CHARACTER_STATUS_TABLE " s ON c.id = s.character_id WHERE account_id = %d", _:Player.Auth[playerid][@id]);
	
	inline CharacterFetch()
	{
		if (!cache_num_rows()) {

			#if defined Y_PLAYER_NO_MULTI_CHARACTER
		
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
						call OnPlayerLogin(playerid);
						@return 1;
					}
					mysql_format(dbHandle, query, sizeof query, "INSERT INTO " CHARACTER_STATUS_TABLE " (character_id) VALUES (%d)", _:Player.Status[playerid][@id]);
					mysql_pquery_inline(dbHandle, query, using inline OnStatusCreated);
					@return 1;
				}

				mysql_format(dbHandle, query, sizeof(query), "INSERT INTO " CHARACTER_TABLE " (name, account_id) VALUES('%e', %d)", Player.Auth[playerid][@name], _:Player.Auth[playerid][@id]);
				mysql_tquery_inline(dbHandle, query, using inline OnCharacterCreated);
		
			#else

			Text_Send(playerid, $CHARACTER_NOT_FOUND);
			Text_Send(playerid, $CHARACTER_REGISTER_ON, WEBSITE_URL);
			defer TimedKick(playerid);	

			#endif
			@return 1;
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
				
				Float:td_posX= 318.0 - (85.0 * float((rows > 3 ? 3 : rows) - 1)) + (5.0 * float((rows > 3 ? 3 : rows) - 1)),
				Float:td_posY= 121.0
			;

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
					td_posX= 318.0 - (65.0 * float(rows - 3) - 1) + (5.0 * float(rows - 3) - 1);
				}
			}

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

		for (new i; i != MAX_CHARSELECT; i++)
		{
			if (playertextid == charSelectTextDraw[playerid][charSelectTextDrawID[playerid][i]])
			{
				CancelSelectTextDraw(playerid);
				for (new x; x < charSelectTextDrawCount[playerid]; x++) {
					PlayerTextDrawDestroy(playerid, charSelectTextDraw[playerid][x]);
					charSelectTextDraw[playerid][x] = PlayerText:INVALID_TEXT_DRAW;
				}
				charSelectTextDrawCount[playerid] = 0;
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
	SpawnPlayer(playerid); // ใช้ TogglePlayerSpectating แทน
	// TogglePlayerSpectating(playerid, false);

	return 1;
}