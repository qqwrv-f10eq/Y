#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI\y_hooks>

hook OnGameModeInit()
{
	mysql_log(MYSQL_LOG);

	new MySQLOpt:options = mysql_init_options();
	mysql_set_option(options, POOL_SIZE, MYSQL_POOL_SIZE);

	dbHandle = mysql_connect(MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DB, options);

	if (dbHandle == MYSQL_INVALID_HANDLE || mysql_errno(dbHandle) != 0) {
		print("MySQL connection failed. Server is shutting down.");
		SendRconCommand("exit");
	} else {
		print("MySQL connection established");
		
		mysql_set_charset(MYSQL_CHARSET, dbHandle);
		mysql_query(dbHandle, "SET NAMES "MYSQL_CHARSET"");

		call OnDatabaseInit();
	}
	
	return 1;
}

hook OnGameModeExit()
{
	mysql_close(dbHandle);

	return 1;
}