#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

loadtext y_players[secure];

forward OnSecretKeyHash(playerid);
public OnSecretKeyHash(playerid)
{
    new dest[250];
    bcrypt_get_hash(dest);

    inline UpdateSecretKey()
    {
        @return VerifyAccount(playerid);
    }

    new query[112];
    mysql_format(dbHandle, query, sizeof(query), "UPDATE characters SET secret_key = '%e' WHERE id = %d", dest, _:Player.Status[playerid][@id]); 
    mysql_tquery_inline(dbHandle, query, using inline UpdateSecretKey);
}

forward OnSecretKeyVerify(playerid,bool:success);
public OnSecretKeyVerify(playerid,bool:success) {
 	if(success) {
        inline UpdatePlayerIP()
        {
            @return VerifyAccount(playerid);
        }
        new ip[18], query[100];
        GetPlayerIp(playerid, ip, sizeof ip);
        mysql_format(dbHandle, query, sizeof(query), "UPDATE characters SET ip = '%e', logged_at = NOW() WHERE id = %d", ip, _:Player.Status[playerid][@id]);
        mysql_tquery_inline(dbHandle, query, using inline UpdatePlayerIP);
 	} else {
        Text_Send(playerid, $INVALID_KEY);
		defer TimedKick(playerid);
 	}
 }

ShowSecretCreationDialog(playerid)
{
    inline HandleCreationSecretWord(pid, dialogid, response, listitem, string:inputtext[])
    {
        #pragma unused pid, dialogid, listitem

        if(!response)
        {
            defer TimedKick(playerid);
            @return 0;
        }

        if (isnull(inputtext)) {
            @return ShowSecretCreationDialog(playerid);
        }

        bcrypt_hash(playerid, "OnSecretKeyHash", inputtext, Y_BCRYPT_WORK_FACTOR);
        @return 1;
    }
    Text_PasswordBox(playerid, using inline HandleCreationSecretWord, $SECRET_TITLE, $SECRET_BODY, $SECRET_CONFIRM, $SECRET_EXIT);
	return 1;
}

ShowSecretVerifyDialog(playerid)
{
    inline HandleVerifySecretWord(pid, dialogid, response, listitem, string:inputtext[])
    {
        #pragma unused pid, dialogid, listitem

        if(!response)
        {
            defer TimedKick(playerid);
            @return 0;
        }

        if (isnull(inputtext)) {
            @return ShowSecretVerifyDialog(playerid);
        }

        bcrypt_verify(playerid,"OnSecretKeyVerify", inputtext, Player.Status[playerid][@secretkey]);
        
        @return 1;
    }
    Text_PasswordBox(playerid, using inline HandleVerifySecretWord, $SECRET_TITLE, $SECRET_VERIFY_BODY, $SECRET_CONFIRM, $SECRET_EXIT);
    return 1;
}


forward VerifyAccount(playerid);
public VerifyAccount(playerid)
{
    new query[160];

	inline HandleSecurityVerify()
	{
	    if (!cache_num_rows()) {
	    	@return log("[%d] can't load character data", playerid);
	    }

        new
            bool:active,
            loginIp[18],
            ip[18],
            day
        ;

        cache_get_value_name(0, "secret_key", Player.Status[playerid][@secretkey]);
        cache_get_value_name_bool(0, "active", active);
        cache_get_value_name(0, "ip", loginIp);
        cache_get_value_name_int(0, "day", day);

        GetPlayerIp(playerid, ip, sizeof ip);
    
        if (isnull(Player.Status[playerid][@secretkey])) {
            @return ShowSecretCreationDialog(playerid);
        }
        else if (!active) {
            format(query, sizeof(query), "UPDATE ucp_applications SET fingerprint = 1 WHERE character_id = %d", _:Player.Status[playerid][@id]);
            mysql_pquery(dbHandle, query);
            
            Text_Send(playerid, $APPLICATION_ALERT_A);
            Text_Send(playerid, $APPLICATION_ALERT_B, WEBSITE_URL);
            Text_Send(playerid, $APPLICATION_ALERT_C);
            Text_Send(playerid, $APPLICATION_ALERT_D, SERVER_ALIAS);

            defer TimedKick(playerid);
            @return 0;
        }
        else if (day >= Y_PLAYER_SECURE_LOGIN_DAY) {

            Text_Send(playerid, $EMAIL_VERIFY_MSG_A);
            Text_Send(playerid, $EMAIL_VERIFY_MSG_B);
            Text_Send(playerid, $EMAIL_VERIFY_MSG_C);

            format(query,sizeof(query),"ip=%s&time=%d&id=%d", loginIp, gettime(), _:Player.Status[playerid][@id]);
            HTTP(playerid, HTTP_POST, "localhost/api/verify_email.php", query,"HttpVerifyRequest");
            @return 0;
        }
        else if (!isnull(loginIp) && strcmp(loginIp, ip, true)) {
            @return ShowSecretVerifyDialog(playerid);
        }

        mysql_format(dbHandle, query, sizeof(query), "UPDATE characters SET ip = '%e', logged_at = NOW() WHERE id = %d", ip, _:Player.Status[playerid][@id]);
        mysql_pquery(dbHandle, query);

        call OnPlayerLogin(playerid);
        log("%d verify character and login", playerid);
	}
    mysql_format(dbHandle, query, sizeof(query), "SELECT secret_key, active, ip, DATEDIFF(NOW(), logged_at) as day FROM characters WHERE id = %d", _:Player.Status[playerid][@id]);
    mysql_tquery_inline(dbHandle, query, using inline HandleSecurityVerify);
    return 1;
}