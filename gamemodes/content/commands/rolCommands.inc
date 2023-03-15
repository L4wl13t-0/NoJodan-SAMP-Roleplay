CMD:me(playerid, params[])
{
	if(isnull(params)) return SendClientMessage(playerid, COLOR_WHITE, "Utiliza: /me (Accion)");
	new string[128];
	format(string, sizeof(string), "* %s %s.", GetPlayerNameEx(playerid), params);
	ProxDetector(15.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
	return 1;
}

CMD:do(playerid, params[])
{
	if(isnull(params)) return SendClientMessage(playerid, COLOR_WHITE, "Utiliza: /do (Accion)");
	new string[128];
	format(string, sizeof(string), "* %s (( %s ))", params, GetPlayerNameEx(playerid));
	ProxDetector(20.0, playerid, string, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW);
	return 1;
}

CMD:e(playerid, params[])
{
	if(isnull(params)) return SendClientMessage(playerid, COLOR_WHITE, "Utiliza: /e (Entorno)");
	new string[128];
	format(string, sizeof(string), "[Entorno]: %s (( %s ))", params, GetPlayerNameEx(playerid));
	ProxDetector(25.0, playerid, string, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN);
	return 1;
}

CMD:susurrar(playerid, params[])
{
	if(isnull(params)) return SendClientMessage(playerid, COLOR_WHITE, "Utiliza: /susurrar (dialogo)");
	new string[128];
	format(string, sizeof(string), "%s susurra: %s", GetPlayerNameEx(playerid), params);
	ProxDetector(5.0, playerid, string, COLOR_FADE5, COLOR_FADE5, COLOR_FADE5, COLOR_FADE5, COLOR_FADE5);
	return 1;
}

CMD:gritar(playerid, params[])
{
	if(isnull(params)) return SendClientMessage(playerid, COLOR_WHITE, "Utiliza: /gritar (dialogo)");
	new string[128];
	format(string, sizeof(string), "%s grita: %s", GetPlayerNameEx(playerid), params);
	ProxDetector(25.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
	return 1;
}