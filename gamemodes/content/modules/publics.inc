//Cuando la GM es iniciada
public OnGameModeInit()
{
	SetGameModeText("Test Roleplay");
	ShowPlayerMarkers(PLAYER_MARKERS_MODE_OFF);
	ShowNameTags(0);
	SetNameTagDrawDistance(7.0);
	EnableStuntBonusForAll(0);
	DisableInteriorEnterExits();
	SetWeather(2);
	SetWorldTime(11);
	UsePlayerPedAnims();
	LoadFaction_DataInit();
	return 1;
}

//Cuando la GM es cerrada
public OnGameModeExit()
{
	SaveFaction_DataExit();
	return 1;
}

//Cuando un usuario se conecta
public OnPlayerConnect(playerid)
{
	SetPlayerColor(playerid, COLOR_USUARIO);
	if(fexist(UserPath(playerid))) //Verificamos si el usuario existe
	{
		INI_ParseFile(UserPath(playerid), "LoadUser_%s", .bExtra = true, .extra = playerid);
		ShowPlayerDialog(playerid, LoginDialog, DIALOG_STYLE_INPUT, ""COLOR_WHITE_T"Iniciar sesion", ""COLOR_WHITE_T"Ingresa tu contraseNa para iniciar sesion:", "Ingresar", "Salir");
	}
	else
	{
		ShowPlayerDialog(playerid, RegisterDialog, DIALOG_STYLE_INPUT, ""COLOR_WHITE_T"Registrarse", ""COLOR_WHITE_T"Escribe una contrasena para crear tu cuenta:", "Siguiente", "Salir");
	}
	return 1;
}

public OnPlayerSpawn(playerid)
{
	INI_ParseFile(UserPath(playerid), "LoadUser_%s", .bExtra = true, .extra = playerid);
	SetPlayerSkin(playerid, pInfo[playerid][Skin]);
	SendClientMessage(playerid, COLOR_GREEN, "Iniciaste sesion.");
	GivePlayerMoney(playerid, pInfo[playerid][Money]);
	SetPlayerHealth(playerid, pInfo[playerid][Health]);
	SetPlayerArmour(playerid, pInfo[playerid][Armour]);
	for(new i = 0; i < 13; i++)
	{
		GivePlayerWeapon(playerid, pInfo[playerid][Weapon][i], pInfo[playerid][Ammo][i]);
	}
}

//Cuando un usuario se desconecta
public OnPlayerDisconnect(playerid, reason)
{
	SaveUser_Data(playerid);
	return 1;
}

//Cada vez que el usuario escribe
public OnPlayerText(playerid, text[])
{
	new string[256];
	format(string, sizeof(string), "%s dice: %s", GetPlayerNameEx(playerid), text); //Formateamos para que aparezca en formato RP
	ProxDetector(15.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5); //Usamos el ProxDetector para mandar el mensaje en un rango especifico
}

//Cada vez que un usuario escribe un comando
public OnPlayerCommandReceived(playerid, cmdtext[])
{
  	printf("[CMD] [%s]: %s", GetPlayerNameEx(playerid), cmdtext);
  	if(strfind(cmdtext, "|", true) != -1)
	{
		SendClientMessage(playerid, COLOR_RED, "No puedes usar el caracter '|' en un comando.");
		return 0;
	}
  	return 1;
}

//Cada vez que un comando se ejecuta
public OnPlayerCommandPerformed(playerid, cmdtext[], success)
{
  	if(!success) SendClientMessage(playerid, COLOR_GREEN, "NoJodan Roleplay: {FF0000}[Error 404] {FFFFFF}El Comando que has introducido es incorrecto, use {BFFF00}/ayuda{FFFFFF}.");
	return 1;
}