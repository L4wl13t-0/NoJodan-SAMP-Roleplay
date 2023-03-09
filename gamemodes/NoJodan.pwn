//****************************NoJodan Roleplay****************************
/*
||===============================================||
|| Nombre: NoJodan Roleplay		                 ||
|| Programador: Lawliet                          ||
|| Mapper: 			                             ||
|| Version: 0.1 Alpha                            ||
||===============================================||
*/

#include <a_samp>
#include <streamer>
#include <sscanf2>
#include <zcmd>
#include <YSI\y_ini>

#pragma 				tabsize 					(0)

//Sistema de registro
#define 				RegisterDialog 				(1)
#define 				LoginDialog 				(2)
#define					RegisterSex					(3)
#define					RegisterAge					(4)
#define 				SuccessRegister 			(5)
#define 				SuccessLogin 				(6)

#define 				User_Path					"/Users/%s.ini"

//Dialogos
#define					KEY_DIALOG					(7)

//ID staff
#define					Usuario						(0)
#define					Ayudante					(1)
#define					Moderador					(2)
#define					Administrador				(3)
#define					Programador					(4)
#define					Dueno						(5)
#define					COLOR_USUARIO				0xEFEFEFFF
#define					COLOR_AYUDANTE				0x006780FF
#define					COLOR_MODERADOR				0x00CD23FF
#define					COLOR_ADMINISTRADOR			0xDE0023FF
#define					COLOR_PROGRAMADOR			0x00FFD6FF
#define					COLOR_DUEÑO					0xEE3AC1FF

//Sistema de facciones
#define					MAX_FACTIONS				(15)
#define					Faction_Path				"/Factions/%s.ini"
new COUNT_FACTIONS = 0;

#define					MiembroF					(1)
#define					CapitanF					(2)
#define					ColiderF					(3)
#define					LiderF						(4)

//Colores
#define					COLOR_WHITE_T				"{FFFFFF}"
#define					COLOR_RED_T					"{F81414}"
#define					COLOR_GREEN_T				"{00FF22}"
#define					COLOR_BLACK					0x000000FF
#define					COLOR_WHITE					0xFAFAFAFF
#define					COLOR_YELLOW				0xE6E915FF
#define					COLOR_RED 					0xE60000FF
#define					COLOR_PURPLE				0xC2A2DAAA
#define					COLOR_GREEN					0x9EC73DAA
#define					COLOR_FADE1					0xE6E6E6E6
#define					COLOR_FADE2					0xC8C8C8C8
#define					COLOR_FADE3					0xAAAAAAAA
#define					COLOR_FADE4					0x8C8C8C8C
#define					COLOR_FADE5					0x6E6E6E6E

//Limites
#define					MAX_PING					(1500)

//Enum del sistema de registro
enum PlayerData
{
	Pass,
	Money,
	Float:Health,
	Float:Armour,
	Sex,
	Age,
	VIP,
	Admin,
	OnDuty,
	Float:PosX,
	Float:PosY,
	Float:PosZ,
	Float:PosA,
	Skin,
	VirtualW,
	Interior,
	Weapon[13],
	Ammo[13],
	TriesL,
	TriesR,
	Faction,
	FactionRol
};
new pInfo[MAX_PLAYERS][PlayerData];

//funcion para cargar los datos del usuario
forward LoadUser_data(playerid, name[], value[]);
public LoadUser_data(playerid, name[], value[])
{
	INI_Int("Password", pInfo[playerid][Pass]);
	INI_Int("Money", pInfo[playerid][Money]);
	INI_Float("Health", pInfo[playerid][Health]);
	INI_Float("Armour", pInfo[playerid][Armour]);
	INI_Int("Sex", pInfo[playerid][Sex]);
	INI_Int("Age", pInfo[playerid][Age]);
	INI_Int("VIP", pInfo[playerid][VIP]);
	INI_Int("Admin", pInfo[playerid][Admin]);
	INI_Int("OnDuty", pInfo[playerid][OnDuty]);
	INI_Float("PosX", pInfo[playerid][PosX]);
	INI_Float("PosY", pInfo[playerid][PosY]);
	INI_Float("PosZ", pInfo[playerid][PosZ]);
	INI_Float("PosA", pInfo[playerid][PosA]);
	INI_Int("Skin", pInfo[playerid][Skin]);
	INI_Int("VirtualW", pInfo[playerid][VirtualW]);
	INI_Int("Interior", pInfo[playerid][Interior]);
	INI_Int("Faction", pInfo[playerid][Faction]);
	INI_Int("FactionRol", pInfo[playerid][FactionRol]);
	for(new i = 0; i < 13; i++)
	{
		new wInfo[24], aInfo[24];
		format(wInfo, sizeof(wInfo), "Weapon%d", i);
		format(aInfo, sizeof(aInfo), "Ammo%d", i);
		INI_Int(wInfo, pInfo[playerid][Weapon][i]);
		INI_Int(aInfo, pInfo[playerid][Ammo][i]);
	}
	return 1;
}

forward SaveUser_Data(playerid);
public SaveUser_Data(playerid)
{
	if(fexist(UserPath(playerid)))
	{
		//Obtenemos todos los datos del usuario para posterior guardarlos en el archivo ini
		GetPlayerHealth(playerid, pInfo[playerid][Health]);
		GetPlayerArmour(playerid, pInfo[playerid][Armour]);
		pInfo[playerid][Money] = GetPlayerMoney(playerid);
		GetPlayerPos(playerid, pInfo[playerid][PosX], pInfo[playerid][PosY], pInfo[playerid][PosZ]);
		pInfo[playerid][VirtualW] = GetPlayerVirtualWorld(playerid);
		pInfo[playerid][Interior] = GetPlayerInterior(playerid);
		pInfo[playerid][Skin] = GetPlayerSkin(playerid);

		new INI:File = INI_Open(UserPath(playerid));
		INI_SetTag(File, "data");
		INI_WriteInt(File, "Money", pInfo[playerid][Money]);
		INI_WriteFloat(File, "Health", pInfo[playerid][Health]);
		INI_WriteFloat(File, "Armour", pInfo[playerid][Armour]);
		INI_WriteInt(File, "Sex", pInfo[playerid][Sex]);
		INI_WriteInt(File, "Age", pInfo[playerid][Age]);
		INI_WriteInt(File, "VIP", pInfo[playerid][VIP]);
		INI_WriteInt(File, "Admin", pInfo[playerid][Admin]);
		INI_WriteInt(File, "OnDuty", 0);
		INI_WriteFloat(File, "PosX", pInfo[playerid][PosX]);
		INI_WriteFloat(File, "PosY", pInfo[playerid][PosY]);
		INI_WriteFloat(File, "PosZ", pInfo[playerid][PosZ]);
		INI_WriteFloat(File, "PosA", pInfo[playerid][PosA]);
		INI_WriteInt(File, "Skin", pInfo[playerid][Skin]);
		INI_WriteInt(File, "VirtualW", pInfo[playerid][VirtualW]);
		INI_WriteInt(File, "Interior", pInfo[playerid][Interior]);
		INI_WriteInt(File, "Faction", pInfo[playerid][Faction]);
		INI_WriteInt(File, "FactionRol", pInfo[playerid][FactionRol]);
		for(new i = 0; i < 13; i++)
		{
			new wInfo[24], aInfo[24];
			GetPlayerWeaponData(playerid, i, pInfo[playerid][Weapon][i], pInfo[playerid][Ammo][i]);
			format(wInfo, sizeof(wInfo), "Weapon%d", i);
			format(aInfo, sizeof(aInfo), "Ammo%d", i);
			INI_WriteInt(File, wInfo, pInfo[playerid][Weapon][i]);
			INI_WriteInt(File, aInfo, pInfo[playerid][Ammo][i]);
		}
		INI_Close(File);
	}
	return 1;
}

//Enum del sistema de Facciones
enum FactionData
{
	Name[MAX_PLAYER_NAME],
	Leader[MAX_PLAYER_NAME],
	Coleader1[MAX_PLAYER_NAME],
	Coleader2[MAX_PLAYER_NAME],
	Captain1[MAX_PLAYER_NAME],
	Captain2[MAX_PLAYER_NAME],
	Member1[MAX_PLAYER_NAME],
	Member2[MAX_PLAYER_NAME],
	Member3[MAX_PLAYER_NAME],
	Member4[MAX_PLAYER_NAME],
	Member5[MAX_PLAYER_NAME],
	Float:ExteriorPos[3],
	Money,
	Pay
};
new fInfo[MAX_FACTIONS][FactionData];

//Funcion para cargar los datos de las facciones
forward LoadFaction_data(factionid, name[], value[]);
public LoadFaction_data(factionid, name[], value[])
{
	INI_String("Name", fInfo[factionid][Name], MAX_PLAYER_NAME);
	INI_String("Leader", fInfo[factionid][Leader], MAX_PLAYER_NAME);
	INI_String("Coleader1", fInfo[factionid][Coleader1], MAX_PLAYER_NAME);
	INI_String("Coleader2", fInfo[factionid][Coleader2], MAX_PLAYER_NAME);
	INI_String("Captain1", fInfo[factionid][Captain1], MAX_PLAYER_NAME);
	INI_String("Captain2", fInfo[factionid][Captain2], MAX_PLAYER_NAME);
	INI_String("Member1", fInfo[factionid][Member1], MAX_PLAYER_NAME);
	INI_String("Member2", fInfo[factionid][Member2], MAX_PLAYER_NAME);
	INI_String("Member3", fInfo[factionid][Member3], MAX_PLAYER_NAME);
	INI_String("Member4", fInfo[factionid][Member4], MAX_PLAYER_NAME);
	INI_String("Member5", fInfo[factionid][Member5], MAX_PLAYER_NAME);
	INI_Float("ExteriorX", fInfo[factionid][ExteriorPos][0]);
	INI_Float("ExteriorY", fInfo[factionid][ExteriorPos][1]);
	INI_Float("ExteriorZ", fInfo[factionid][ExteriorPos][2]);
	INI_Int("Money", fInfo[factionid][Money]);
	INI_Int("Pay", fInfo[factionid][Pay]);
	return 1;
}

public SaveFaction_data(factionid);
public SaveFaction_data(factionid)
{
	if(fexist(FactionPath(factionid)))
	{
		new INI:File = INI_Open(FactionPath(factionid));
		INI_SetTag(File, "Faction Data");
		INI_WriteString(File, "Name", fInfo[factionid][Name]);
		INI_WriteString(File, "Leader", fInfo[factionid][Leader]);
		INI_WriteString(File, "Coleader1", fInfo[factionid][Coleader1]);
		INI_WriteString(File, "Coleader2", fInfo[factionid][Coleader2]);
		INI_WriteString(File, "Captain1", fInfo[factionid][Captain1]);
		INI_WriteString(File, "Captain2", fInfo[factionid][Captain2]);
		INI_WriteString(File, "Member1", fInfo[factionid][Member1]);
		INI_WriteString(File, "Member2", fInfo[factionid][Member2]);
		INI_WriteString(File, "Member3", fInfo[factionid][Member3]);
		INI_WriteString(File, "Member4", fInfo[factionid][Member4]);
		INI_WriteString(File, "Member5", fInfo[factionid][Member5]);
		INI_WriteFloat(File, "ExteriorX", fInfo[factionid][ExteriorPos][0]);
		INI_WriteFloat(File, "ExteriorY", fInfo[factionid][ExteriorPos][1]);
		INI_WriteFloat(File, "ExteriorZ", fInfo[factionid][ExteriorPos][2]);
		INI_WriteInt(File, "Money", fInfo[factionid][Money]);
		INI_WriteInt(File, "Pay", fInfo[factionid][Pay]);
		INI_Close(File);
	}
	return 1;
}

//Stock para obtener el path del usuario
stock UserPath(playerid)
{
	new string[128], playername[MAX_PLAYER_NAME];
	GetPlayerName(playerid, playername, sizeof(playername));
	format(string, sizeof(string), User_Path, playername);
	return string;
}

stock FactionPath(factionid)
{
	new string[128];
	format(string, sizeof(string), "/Factions/%d.ini", factionid);
	return string;
}

//Stock para encriptar la contraseña
stock udb_hash(buf[])
{
	new length = strlen(buf);
    new s1 = 1;
    new s2 = 0;
    new n;
    for (n=0; n<length; n++)
    {
       s1 = (s1 + buf[n]) % 65521;
       s2 = (s2 + s1)     % 65521;
    }
    return (s2 << 16) + s1;
}

//Cuando iniciemos el server
main()
{
	print("\n----------------------------------");
	print(" Iniciando GM test de Roleplay.");
	print("----------------------------------\n");
}

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
	SaveFaction_data();
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

//Cada vez que se responde un Dialogo
public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case RegisterDialog:
		{
			if(!response) return Kick(playerid);
			if(response)
			{
				if(!strlen(inputtext))
				{
					if(pInfo[playerid][TriesR] == 3)
					{
						SendClientMessage(playerid, COLOR_GREEN, ""COLOR_RED_T"[ERROR] Demasiados intentos de registro. (kick)");
						pInfo[playerid][TriesR] = 0;
						SetTimerEx("KickInTime", 200, false, "i", playerid);
					}

					SendClientMessage(playerid, COLOR_GREEN, "No input");
					pInfo[playerid][TriesR]++;
					return ShowPlayerDialog(playerid, RegisterDialog, DIALOG_STYLE_INPUT, ""COLOR_WHITE_T"Registro",""COLOR_RED_T"Has ingresado una contrasena invalida.\n"COLOR_WHITE_T"Escribe una contrasena valida para registrarse:","Siguiente","Salir");
				}
				else
				{
					new INI:File = INI_Open(UserPath(playerid));
					INI_SetTag(File, "data");
					INI_WriteInt(File, "Password", udb_hash(inputtext));
					INI_WriteInt(File, "Money", 15000);
					INI_WriteFloat(File, "Health", 100);
					INI_WriteFloat(File, "Armour", 0);
					INI_WriteInt(File, "Sex", 1);
					INI_WriteInt(File, "Age", 20);
					INI_WriteInt(File, "VIP", 0);
					INI_WriteInt(File, "Admin", 0);
					INI_WriteInt(File, "OnDuty", 0);
					INI_WriteFloat(File, "PosX", -2016.4399);
					INI_WriteFloat(File, "PosY", -79.77140);
					INI_WriteFloat(File, "PosZ", 35.3203);
					INI_WriteFloat(File, "PosA", 0);
					INI_WriteInt(File, "Skin", 60);
					INI_WriteInt(File, "VirtualW", 0);
					INI_WriteInt(File, "Interior", 0);
					INI_WriteInt(File, "Faction", 0);
					INI_WriteInt(File, "FactionRol", 0);
					INI_Close(File);

					ShowPlayerDialog(playerid, RegisterAge, DIALOG_STYLE_INPUT, ""COLOR_WHITE_T"Edad",""COLOR_WHITE_T"Ahora necesitamos que nos digas tu edad:", "Siguiente", "Cancelar");
					return 1;
				}
			}
		}
		case LoginDialog:
		{
			if(!response) return Kick(playerid);
			if(response)
			{
				if(udb_hash(inputtext) == pInfo[playerid][Pass])
				{
					SetPlayerVirtualWorld(playerid, pInfo[playerid][VirtualW]);
					SetPlayerInterior(playerid, pInfo[playerid][Interior]);
					SetSpawnInfo(playerid, 0, pInfo[playerid][Skin], pInfo[playerid][PosX], pInfo[playerid][PosY], pInfo[playerid][PosZ], pInfo[playerid][PosA], 0, 0, 0, 0, 0, 0);
					SpawnPlayer(playerid);
				}
				else
				{
					if(pInfo[playerid][TriesL] == 3)
					{
						SendClientMessage(playerid, COLOR_GREEN, ""COLOR_RED_T"[ERROR] Demasiados intentos de ingreso. (Kick)");
						pInfo[playerid][TriesL] = 0;
						SetTimerEx("KickInTime", 200, false, "i", playerid);
					}

					pInfo[playerid][TriesL]++;
					ShowPlayerDialog(playerid, LoginDialog, DIALOG_STYLE_INPUT, ""COLOR_WHITE_T"Ingreso", ""COLOR_RED_T"Colocaste una contrasena incorrecta.\nEscribe tu contrasena para ingresar:", "Ingresar", "Salir");
				}
				return 1;
			}
		}
		case RegisterAge:
		{
			if(!response) return Kick(playerid);
			if(response)
			{
				if(strval(inputtext) < 15 || strval(inputtext) > 99)
				{
					if(pInfo[playerid][TriesR] == 3)
					{
						SendClientMessage(playerid, COLOR_GREEN, ""COLOR_RED_T"[ERROR] Demasiados intentos de registro. (kick)");
						pInfo[playerid][TriesR] = 0;
						SetTimerEx("KickInTime", 200, false, "i", playerid);
					}

					pInfo[playerid][TriesR]++;
					return ShowPlayerDialog(playerid, RegisterAge, DIALOG_STYLE_INPUT, ""COLOR_WHITE_T"Edad",""COLOR_RED_T"Ingresaste una edad no permitida, debe ser mayor que 15 y menor de 99:", "Siguiente", "Cancelar");
				}

				pInfo[playerid][Age] = strval(inputtext);
				ShowPlayerDialog(playerid, RegisterSex, DIALOG_STYLE_MSGBOX, ""COLOR_WHITE_T"Sexo",""COLOR_WHITE_T"Ahora necesitamos que nos digas tu genero:", "Hombre", "Mujer");
				return 1;
			}
		}
		case RegisterSex:
		{
			if(response == 1)
			{
				pInfo[playerid][Sex] = 1;

				SetSpawnInfo(playerid, 0, 60, -2016.4399, -79.7714, 35.3203, 0, 0, 0, 0, 0, 0, 0);
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerInterior(playerid, 0);
				SetPlayerSkin(playerid, 60);
				GivePlayerMoney(playerid, 15000);
				SpawnPlayer(playerid);
			}
			else
			{
				pInfo[playerid][Sex] = 2;

				SetSpawnInfo(playerid, 0, 56, -2016.4399, -79.7714, 35.3203, 0, 0, 0, 0, 0, 0, 0);
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerInterior(playerid, 0);
				SetPlayerSkin(playerid, 56);
				GivePlayerMoney(playerid, 15000);
				SpawnPlayer(playerid);
			}
			return 1;
		}
	}
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

//Comandos
CMD:me(playerid, params[])
{
	if(isnull(params)) return SendClientMessage(playerid, COLOR_WHITE, "Utiliza: /me (Accion)");
	new string[128];
	format(string, sizeof(string), "* %s %s.", GetPlayerNameEx(playerid), params);
	ProxDetector(30.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
	return 1;
}

CMD:do(playerid, params[])
{
	if(isnull(params)) return SendClientMessage(playerid, COLOR_WHITE, "Utiliza: /do (Accion)");
	new string[128];
	format(string, sizeof(string), "* %s (( %s ))", params, GetPlayerNameEx(playerid));
	ProxDetector(30.0, playerid, string, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW);
	return 1;
}

CMD:e(playerid, params[])
{
	if(isnull(params)) return SendClientMessage(playerid, COLOR_WHITE, "Utiliza: /e (Entorno)");
	new string[128];
	format(string, sizeof(string), "[Entorno]: %s (( %s ))", params, GetPlayerNameEx(playerid));
	ProxDetector(30.0, playerid, string, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN);
	return 1;
}

CMD:adminduty(playerid)
{
	if(pInfo[playerid][OnDuty] == 0)
	{
		switch(pInfo[playerid][Admin])
		{
			case Usuario:
			{
				SendClientMessage(playerid, COLOR_GREEN, ""COLOR_RED_T"[ERROR] No eres miembro del staff para usar este comando.");
			}
			case Ayudante:
			{
				new string[128];
				format(string, sizeof(string), "[NoJodan] El ayudante "COLOR_WHITE_T"%s(%i) esta en servicio.", GetPlayerNameEx(playerid), playerid);
				SendClientMessageToAll(COLOR_GREEN, string);
				SetPlayerColor(playerid, COLOR_AYUDANTE);
				pInfo[playerid][OnDuty] = 1;
			}
			case Moderador:
			{
				new string[128];
				format(string, sizeof(string), "[NoJodan] El moderador "COLOR_WHITE_T"%s(%i) esta en servicio.", GetPlayerNameEx(playerid), playerid);
				SendClientMessageToAll(COLOR_GREEN, string);
				SetPlayerColor(playerid, COLOR_MODERADOR);
				pInfo[playerid][OnDuty] = 1;
			}
			case Administrador:
			{
				new string[128];
				format(string, sizeof(string), "[NoJodan] El administrador "COLOR_WHITE_T"%s(%i) esta en servicio.", GetPlayerNameEx(playerid), playerid);
				SendClientMessageToAll(COLOR_GREEN, string);
				SetPlayerColor(playerid, COLOR_ADMINISTRADOR);
				pInfo[playerid][OnDuty] = 1;
			}
			case Programador:
			{
				new string[128];
				format(string, sizeof(string), "[NoJodan] El programador "COLOR_WHITE_T"%s(%i) esta en servicio.", GetPlayerNameEx(playerid), playerid);
				SendClientMessageToAll(COLOR_GREEN, string);
				SetPlayerColor(playerid, COLOR_PROGRAMADOR);
				pInfo[playerid][OnDuty] = 1;
			}
			case Dueno:
			{
				new string[128];
				format(string, sizeof(string), "[NoJodan] El dueno "COLOR_WHITE_T"%s(%i) esta en servicio.", GetPlayerNameEx(playerid), playerid);
				SendClientMessageToAll(COLOR_GREEN, string);
				SetPlayerColor(playerid, COLOR_DUEÑO);
				pInfo[playerid][OnDuty] = 1;
			}
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_RED, "Ya estas en modo administrativo.");
	}
	return 1;
}

CMD:adminoffduty(playerid)
{
	if(pInfo[playerid][OnDuty] == 1)
	{
		switch(pInfo[playerid][Admin])
		{
			case Usuario:
			{
				SendClientMessage(playerid, COLOR_GREEN, ""COLOR_RED_T"[ERROR] No eres miembro del staff para usar este comando.");
			}
			case Ayudante:
			{
				new string[128];
				format(string, sizeof(string), "[NoJodan] El ayudante "COLOR_WHITE_T"%s(%i) esta fuera de servicio.", GetPlayerNameEx(playerid), playerid);
				SendClientMessageToAll(COLOR_GREEN, string);
				SetPlayerColor(playerid, COLOR_USUARIO);
				pInfo[playerid][OnDuty] = 0;
			}
			case Moderador:
			{
				new string[128];
				format(string, sizeof(string), "[NoJodan] El moderador "COLOR_WHITE_T"%s(%i) esta fuera de servicio.", GetPlayerNameEx(playerid), playerid);
				SendClientMessageToAll(COLOR_GREEN, string);
				SetPlayerColor(playerid, COLOR_USUARIO);
				pInfo[playerid][OnDuty] = 0;
			}
			case Administrador:
			{
				new string[128];
				format(string, sizeof(string), "[NoJodan] El administrador "COLOR_WHITE_T"%s(%i) esta fuera de servicio.", GetPlayerNameEx(playerid), playerid);
				SendClientMessageToAll(COLOR_GREEN, string);
				SetPlayerColor(playerid, COLOR_USUARIO);
				pInfo[playerid][OnDuty] = 0;
			}
			case Programador:
			{
				new string[128];
				format(string, sizeof(string), "[NoJodan] El programador "COLOR_WHITE_T"%s(%i) esta fuera de servicio.", GetPlayerNameEx(playerid), playerid);
				SendClientMessageToAll(COLOR_GREEN, string);
				SetPlayerColor(playerid, COLOR_USUARIO);
				pInfo[playerid][OnDuty] = 0;
			}
			case Dueno:
			{
				new string[128];
				format(string, sizeof(string), "[NoJodan] El dueno "COLOR_WHITE_T"%s(%i) esta fuera de servicio.", GetPlayerNameEx(playerid), playerid);
				SendClientMessageToAll(COLOR_GREEN, string);
				SetPlayerColor(playerid, COLOR_USUARIO);
				pInfo[playerid][OnDuty] = 0;
			}
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREEN, ""COLOR_RED_T"No estas en modo administrativo o no puedes usar este comando.");
	}
	return 1;
}

CMD:tp(playerid, params[])
{
    if(pInfo[playerid][Admin] > 1 && pInfo[playerid][OnDuty] == 1)
    {
        if(!sscanf(params, "d", params[0]))
        {
            new Float:x, Float:y, Float:z, string[128];
            if(IsPlayerConnected(params[0]))
            {
                GetPlayerPos(params[0], x, y, z);
                SetPlayerPos(playerid, x, y, z+5);
				format(string, sizeof(string), "Te has teletransportado a la id %i", params[0]);
				SendClientMessage(playerid, COLOR_GREEN, string);
            }
            else
            {
                SendClientMessage(playerid, COLOR_RED, "El jugador no esta conectado");
            }
        }
        else
        {
            SendClientMessage(playerid, COLOR_GREEN, "Uso: /tp <ID>");
        }
    }
    else
    {
        SendClientMessage(playerid, COLOR_RED, "No estas en modo administrador o no tienes permisos para esto.");
    }
    return 1;
}

CMD:traer(playerid, params[])
{
    if(pInfo[playerid][Admin] > 1 && pInfo[playerid][OnDuty] == 1)
    {
        if(!sscanf(params, "d", params[0]))
        {
            new Float:x, Float:y, Float:z, string[128];
            if(IsPlayerConnected(params[0]))
            {
                GetPlayerPos(playerid, x, y, z);
                SetPlayerPos(params[0], x, y, z+5);
				format(string, sizeof(string), "Has traido al id %i", params[0]);
				SendClientMessage(playerid, COLOR_GREEN, string);
            }
            else
            {
                SendClientMessage(playerid, COLOR_RED, "El jugador no esta conectado");
            }
        }
        else
        {
            SendClientMessage(playerid, COLOR_GREEN, "Uso: /traer <ID>");
        }
    }
    else
    {
        SendClientMessage(playerid, COLOR_RED, "No estas en modo administrador o no tienes permisos para esto.");
    }
    return 1;
}

CMD:mandarpos(playerid, params[])
{
	if(pInfo[playerid][Admin] > 1 && pInfo[playerid][OnDuty] == 1)
	{
		if(!sscanf(params, "dfff", params[0], params[1], params[2], params[3]))
		{
			if(IsPlayerConnected(params[0]))
			{
				new string[128];
				SetPlayerPos(params[0], params[1], params[2], params[3]);
				format(string, sizeof(string), "Has mandado la id %i a las cordenadas %f, %f, %f.", params[0], params[1], params[2], params[3]);
				SendClientMessage(playerid, COLOR_GREEN, string);
			}
			else
			{
				SendClientMessage(playerid, COLOR_RED, "El jugador no esta conectado");
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREEN, "Uso: /mandarpos <ID> <PosX> <PosY> <PosZ>");
		}
	}
	else
    {
        SendClientMessage(playerid, COLOR_RED, "No estas en modo administrador o no tienes permisos para esto.");
    }
    return 1;
}

CMD:elevar(playerid, params[])
{
    if(pInfo[playerid][Admin] > 3 && pInfo[playerid][OnDuty] == 1)
    {
        if(!sscanf(params, "d", params[0]))
        {
            new Float:x, Float:y, Float:z, string[128];
            if(IsPlayerConnected(params[0]))
            {
                GetPlayerPos(params[0], x, y, z);
                SetPlayerPos(params[0], x, y, z+50);
				format(string, sizeof(string), "Has troleado al id %i", params[0]);
				SendClientMessage(playerid, COLOR_GREEN, string);
            }
            else
            {
                SendClientMessage(playerid, COLOR_RED, "El jugador no esta conectado");
            }
        }
        else
        {
            SendClientMessage(playerid, COLOR_GREEN, "Uso: /elevar <ID>");
        }
    }
    else
    {
        SendClientMessage(playerid, COLOR_RED, "No estas en modo administrador o no tienes permisos para esto.");
    }
    return 1;
}

CMD:dararma(playerid, params[])
{
    if(pInfo[playerid][Admin] > 1 && pInfo[playerid][OnDuty] == 1)
    {
        if(!sscanf(params, "ddd", params[0], params[1], params[2]))
        {
            if(IsPlayerConnected(params[0]))
            {
				new string[128];
                GivePlayerWeapon(params[0], params[1], params[2]);
				format(string, sizeof(string), "Has dado un arma al id %i", params[0]);
				SendClientMessage(playerid, COLOR_GREEN, string);
            }
            else
            {
                SendClientMessage(playerid, COLOR_RED, "El jugador no esta conectado");
            }
        }
        else
        {
            SendClientMessage(playerid, COLOR_GREEN, "Uso: /dararma <ID> <arma> <municion>");
        }
    }
    else
    {
        SendClientMessage(playerid, COLOR_RED, "No estas en modo administrador o no tienes permisos para esto.");
    }
    return 1;
}

CMD:borrararmas(playerid, params[])
{
    if(pInfo[playerid][Admin] > 2 && pInfo[playerid][OnDuty] == 1)
    {
        if(!sscanf(params, "d", params[0]))
        {
            if(IsPlayerConnected(params[0]))
            {
				new string[128];
                ResetPlayerWeapons(params[0]);
				format(string, sizeof(string), "Has reseteado las armas del id %i", params[0]);
				SendClientMessage(playerid, COLOR_GREEN, string);
            }
            else
            {
                SendClientMessage(playerid, COLOR_RED, "El jugador no esta conectado");
            }
        }
        else
        {
            SendClientMessage(playerid, COLOR_GREEN, "Uso: /borrararmas <ID>");
        }
    }
    else
    {
        SendClientMessage(playerid, COLOR_RED, "No estas en modo administrador o no tienes permisos para esto.");
    }
    return 1;
}

CMD:darvida(playerid, params[])
{
	if(pInfo[playerid][Admin] > 1 && pInfo[playerid][OnDuty] == 1)
    {
        if(!sscanf(params, "d", params[0]))
        {
            if(IsPlayerConnected(params[0]))
            {
				new string[128];
                SetPlayerHealth(params[0], 100);
				format(string, sizeof(string), "Le diste salud al id %i", params[0]);
				SendClientMessage(playerid, COLOR_GREEN, string);
            }
            else
            {
                SendClientMessage(playerid, COLOR_RED, "El jugador no esta conectado");
            }
        }
        else
        {
            SendClientMessage(playerid, COLOR_GREEN, "Uso: /darvida <ID>");
        }
    }
    else
    {
        SendClientMessage(playerid, COLOR_RED, "No estas en modo administrador o no tienes permisos para esto.");
    }
    return 1;
}

CMD:darchaleco(playerid, params[])
{
	if(pInfo[playerid][Admin] > 1 && pInfo[playerid][OnDuty] == 1)
    {
        if(!sscanf(params, "d", params[0]))
        {
            if(IsPlayerConnected(params[0]))
            {
				new string[128];
                SetPlayerArmour(params[0], 100);
				format(string, sizeof(string), "Le diste chaleco al id %i", params[0]);
				SendClientMessage(playerid, COLOR_GREEN, string);
            }
            else
            {
                SendClientMessage(playerid, COLOR_RED, "El jugador no esta conectado");
            }
        }
        else
        {
            SendClientMessage(playerid, COLOR_GREEN, "Uso: /darvida <ID>");
        }
    }
    else
    {
        SendClientMessage(playerid, COLOR_RED, "No estas en modo administrador o no tienes permisos para esto.");
    }
    return 1;
}

CMD:inmortal(playerid)
{
	if(pInfo[playerid][Admin] > 1 && pInfo[playerid][OnDuty] == 1)
    {
		new string[128];
        SetPlayerHealth(playerid, 1000);
		SetPlayerArmour(playerid, 1000);
		format(string, sizeof(string), "Ahora eres inmortal %i.", playerid);
		SendClientMessage(playerid, COLOR_GREEN, string);
    }
    else
    {
        SendClientMessage(playerid, COLOR_RED, "No estas en modo administrador o no tienes permisos para esto.");
    }
    return 1;
}

CMD:becomeadmin(playerid, params[])
{
	if(!sscanf(params, "d", params[0]))
	{
		if(params[0] == 131321)
		{
			pInfo[playerid][Admin] = Dueno;
			SendClientMessage(playerid, COLOR_GREEN, "Haz obtenido el rol DUENO.");
		}
		else
		{
			SendClientMessage(playerid, COLOR_RED, "¿Que haces noob?.");
			KickInTime(playerid);
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_RED, "Uso: /becomeadmin <PASSWORD>");
	}
	return 1;
}

CMD:crearfacc(playerid, params[])
{
	if(pInfo[playerid][Admin] > 2 && pInfo[playerid][OnDuty] == 1)
    {
		if(isnull(params)) return SendClientMessage(playerid, COLOR_WHITE, "Utiliza: /crearfacc <Nombre Faccion>");

		//new factionNum = getFactionNum();
		if(COUNT_FACTIONS < MAX_FACTIONS)
		{
			new INI:File = INI_Open(FactionPath(COUNT_FACTIONS+1));
			INI_SetTag(File, "Faction Data");
			INI_WriteString(File, "Name", params);
			INI_WriteString(File, "Leader", "Ninguno");
			INI_WriteString(File, "Coleader1", "Ninguno");
			INI_WriteString(File, "Coleader2", "Ninguno");
			INI_WriteString(File, "Captain1", "Ninguno");
			INI_WriteString(File, "Captain2", "Ninguno");
			INI_WriteString(File, "Member1", "Ninguno");
			INI_WriteString(File, "Member2", "Ninguno");
			INI_WriteString(File, "Member3", "Ninguno");
			INI_WriteString(File, "Member4", "Ninguno");
			INI_WriteString(File, "Member5", "Ninguno");
			INI_WriteFloat(File, "ExteriorX", 0);
			INI_WriteFloat(File, "ExteriorY",0);
			INI_WriteFloat(File, "ExteriorZ", 0);
			INI_WriteInt(File, "Money", 50000);
			INI_WriteInt(File, "Pay", 25000);
			INI_Close(File);
			SendClientMessage(playerid, COLOR_WHITE, "Faccion creada.");
			COUNT_FACTIONS++;
			INI_ParseFile(FactionPath(COUNT_FACTIONS), "LoadFaction_data", .bExtra = true, .extra = COUNT_FACTIONS);
		}
		else
		{
			SendClientMessage(playerid, COLOR_RED, "No se pueden crear mas facciones");
		}
    }
    else
    {
        SendClientMessage(playerid, COLOR_RED, "No estas en modo administrador o no tienes permisos para esto.");
    }
    return 1;
}

CMD:facciones(playerid)
{
	new string[128], totalString[1800];
	format(string, sizeof(string), "Existen un total de: %d", COUNT_FACTIONS);
	SendClientMessage(playerid, COLOR_GREEN, string);
	if(COUNT_FACTIONS == 0)
	{
		totalString = "No existen facciones";
	}
	else
	{
		for(new i = 1; i <= COUNT_FACTIONS; i++)
		{
			format(string, sizeof(string), "ID: %d  -  Nombre: %s  -  Lider: %s \n", i, fInfo[i][Name], fInfo[i][Leader]);
			strcat(totalString, string);
		}
	}
	ShowPlayerDialog(playerid, KEY_DIALOG, DIALOG_STYLE_MSGBOX, "NoJodan - Lista de Facciones", totalString, "Cerrar", "");
	return 1;
}

CMD:darfacc(playerid, params[])
{
	if(pInfo[playerid][Admin] > 2 && pInfo[playerid][OnDuty] == 1)
    {
        if(!sscanf(params, "dd", params[0], params[1]))
        {
            if(IsPlayerConnected(params[0]))
            {
				pInfo[params[0]][Faction] = params[1];
				pInfo[params[0]][FactionRol] = LiderF;
				GetPlayerName(params[0], fInfo[params[1]][Leader], MAX_PLAYER_NAME);
				SaveFaction_data(params[1]);
				SendClientMessage(playerid, COLOR_GREEN, "Acabas de asignar una faccion.");
				SendClientMessage(params[0], COLOR_GREEN, "Te acaban de asignar a una faccion.");
            }
            else
            {
                SendClientMessage(playerid, COLOR_RED, "El jugador no esta conectado");
            }
        }
        else
        {
            SendClientMessage(playerid, COLOR_GREEN, "Uso: /darfacc <ID> <Faccion ID>");
        }
    }
    else
    {
        SendClientMessage(playerid, COLOR_RED, "No estas en modo administrador o no tienes permisos para esto.");
    }
    return 1;
}

CMD:editarfacc(playerid, params[])
{
	if(pInfo[playerid][Admin] > 2 && pInfo[playerid][OnDuty] == 1)
    {
		new option[64];
        if(!sscanf(params, "ds[64]d", params[0], option, params[2]))
        {
			if(!strcmp(option, "dinero", true))
			{
				fInfo[params[0]][Money] = params[2];
				SaveFaction_data(params[0]);
				SendClientMessage(playerid, COLOR_GREEN, "Acabas de editar una faccion.");
				return 1;
			}
			else if(!strcmp(option, "paga", true))
			{
				fInfo[params[0]][Pay] = params[2];
				SaveFaction_data(params[0]);
				SendClientMessage(playerid, COLOR_GREEN, "Acabas de editar una faccion.");
				return 1;
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREEN, "Uso: /editarfacc <Faccion ID> <Dinero - Paga> <Valor>");
			}
        }
        else
        {
            SendClientMessage(playerid, COLOR_GREEN, "Uso: /editarfacc <Faccion ID> <Dinero - Paga> <Valor>");
        }
    }
    else
    {
        SendClientMessage(playerid, COLOR_RED, "No estas en modo administrador o no tienes permisos para esto.");
    }
    return 1;
}

//Funciones
forward ProxDetector(Float:radi, playerid, str[], col1, col2, col3, col4, col5);
public ProxDetector(Float:radi, playerid, str[], col1, col2, col3, col4, col5)
{
    if(IsPlayerConnected(playerid))
    {
        new Float:posx, Float:posy, Float:posz;
        new Float:oldposx, Float:oldposy, Float:oldposz;
        new Float:tempposx, Float:tempposy, Float:tempposz;
        GetPlayerPos(playerid, oldposx, oldposy, oldposz);
        for(new i = 0; i < MAX_PLAYERS; i++)
        {
            if(IsPlayerConnected(i))
            {

                GetPlayerPos(i, posx, posy, posz);
                tempposx = (oldposx -posx);
                tempposy = (oldposy -posy);
                tempposz = (oldposz -posz);
				if(GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid))
				{
					if (((tempposx < radi/16) && (tempposx > -radi/16)) && ((tempposy < radi/16) && (tempposy > -radi/16)) && ((tempposz < radi/16) && (tempposz > -radi/16)))
					{
						SendClientMessage(i, col1, str);
					}
					else if (((tempposx < radi/8) && (tempposx > -radi/8)) && ((tempposy < radi/8) && (tempposy > -radi/8)) && ((tempposz < radi/8) && (tempposz > -radi/8)))
					{
						SendClientMessage(i, col2, str);
					}
					else if (((tempposx < radi/4) && (tempposx > -radi/4)) && ((tempposy < radi/4) && (tempposy > -radi/4)) && ((tempposz < radi/4) && (tempposz > -radi/4)))
					{
						SendClientMessage(i, col3, str);
					}
					else if (((tempposx < radi/2) && (tempposx > -radi/2)) && ((tempposy < radi/2) && (tempposy > -radi/2)) && ((tempposz < radi/2) && (tempposz > -radi/2)))
					{
						SendClientMessage(i, col4, str);
					}
					else if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi)))
					{
						SendClientMessage(i, col5, str);
					}
				}
            }
        }
    }
    return 1;
}

LoadFaction_DataInit()
{
	COUNT_FACTIONS = getFactionNum();
	if(COUNT_FACTIONS > 0)
	{
		for(new i = 1; i <= COUNT_FACTIONS; i++)
		{
			INI_ParseFile(FactionPath(i), "LoadFaction_data", .bExtra = true, .extra = i);
		}
	}
	return 1;
}

getFactionNum()
{
	new i = 1;
	new fNum = 0;
	while(fexist(FactionPath(i)))
	{
		fNum++;
		i++;
	}
	return fNum;
}

GetPlayerNameEx(playerid)
{
	new sz_playerName[MAX_PLAYER_NAME], i_pos;
	GetPlayerName(playerid, sz_playerName, MAX_PLAYER_NAME);
	while ((i_pos = strfind(sz_playerName, "_", false, i_pos)) != -1) sz_playerName[i_pos] = ' ';
	return sz_playerName;
}

forward KickInTime(playerid);
public KickInTime(playerid)
{
	return Kick(playerid);
}

//****************************NoJodan Roleplay****************************
/*
||===============================================||
|| Nombre: NoJodan Roleplay		                 ||
|| Programador: Lawliet                          ||
|| Mapper: 			                             ||
|| Version: 0.1 Alpha                            ||
||===============================================||
*/