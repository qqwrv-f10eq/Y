#if defined _inc_header
	#undef _inc_header
#endif

enum E_PLAYER_STATUS {
	DBID:E_PLAYER_Status_id,
	E_PLAYER_Status_name[MAX_PLAYER_NAME + 1],
	E_PLAYER_Status_secretkey[60 + 1],
	E_PLAYER_Status_ip,
	E_PLAYER_Status_money,
	E_PLAYER_Status_vip,
	E_PLAYER_Status_admin,
	E_PLAYER_Status_skin,
	bool:E_PLAYER_Status_developer
}

new PlayerStatus[MAX_PLAYERS][E_PLAYER_STATUS];

#define ALS_DO_PlayerInit<%0> %0<PlayerInit,i>(end:playerid)

#define CHARACTER_STATUS_TABLE "character_statuses"