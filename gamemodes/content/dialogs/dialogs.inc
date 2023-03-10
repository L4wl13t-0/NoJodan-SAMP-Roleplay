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
					INI_WriteInt(File, "fInvite", 0);
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
		case ContractDialog:
		{
			if(response == 1)
			{
				pInfo[playerid][Faction] = pInfo[playerid][fInvite];
				pInfo[playerid][FactionRol] = MiembroF;
				fInfo[pInfo[playerid][fInvite]][MembersC]++;
				pInfo[playerid][fInvite] = 0;
				SaveFaction_data(pInfo[playerid][Faction]);
				SaveUser_Data(playerid);
				SendClientMessage(playerid, COLOR_GREEN, "Acabas de unirte a una faccion.");
			}
			else
			{
				pInfo[playerid][fInvite] = 0;
				SendClientMessage(playerid, COLOR_GREEN, "Rechazaste la oferta.");
			}
			return 1;
		}
	}
	return 1;
}