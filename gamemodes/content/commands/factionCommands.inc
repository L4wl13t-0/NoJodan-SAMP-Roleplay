CMD:crearfacc(playerid, params[])
{
	if(pInfo[playerid][Admin] > Moderador && pInfo[playerid][OnDuty] == 1)
    {
		if(isnull(params)) return SendClientMessage(playerid, COLOR_WHITE, "Utiliza: /crearfacc <Nombre Faccion>");

		//new factionNum = getFactionNum();
		if(COUNT_FACTIONS < MAX_FACTIONS)
		{
			new pickupid = CreateDynamicPickup(1274, 0, -2016.4399, -79.77140, 35.3203, 0, 0);
			new INI:File = INI_Open(FactionPath(COUNT_FACTIONS+1));
			INI_SetTag(File, "Faction Data");
			INI_WriteString(File, "Name", params);
			INI_WriteString(File, "Leader", "Ninguno");
			INI_WriteFloat(File, "ExteriorX", -2016.4399);
			INI_WriteFloat(File, "ExteriorY", -79.77140);
			INI_WriteFloat(File, "ExteriorZ", 35.3203);
			INI_WriteInt(File, "Money", 50000);
			INI_WriteInt(File, "Pay", 25000);
			INI_WriteInt(File, "MembersC", 1);
			INI_WriteInt(File, "Pickup", 1274);
			INI_WriteInt(File, "PickupID", pickupid);
			INI_Close(File);

			SendClientMessage(playerid, COLOR_WHITE, "Faccion creada.");
			COUNT_FACTIONS++;
			INI_ParseFile(FactionPath(COUNT_FACTIONS), "LoadFaction_data", .bExtra = true, .extra = COUNT_FACTIONS);
			new string[128];
			format(string, sizeof(string), "Faccion: %s\nID: %d", params, COUNT_FACTIONS);
			fInfo[COUNT_FACTIONS][LabelID] = CreateDynamic3DTextLabel(string, COLOR_WHITE, -2016.4399, -79.77140, 35.3203, 20.0);
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
	if(pInfo[playerid][Admin] > Moderador && pInfo[playerid][OnDuty] == 1)
    {
        if(!sscanf(params, "dd", params[0], params[1]))
        {
            if(IsPlayerConnected(params[0]))
            {
				pInfo[params[0]][Faction] = params[1];
				pInfo[params[0]][FactionRol] = LiderF;
				GetPlayerName(params[0], fInfo[params[1]][Leader], MAX_PLAYER_NAME);
				SaveFaction_data(params[1]);
				SaveUser_Data(params[0]);
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
	if(pInfo[playerid][Admin] > Moderador && pInfo[playerid][OnDuty] == 1)
    {
		new option[64], faccID;
        if(!sscanf(params, "ds[64]", faccID, option))
        {
			if(!sscanf(params, "ds[64]d", faccID, option, params[2]))
			{
				if(!strcmp(option, "dinero", true))
				{
					fInfo[faccID][Money] = params[2];
					SaveFaction_data(faccID);
					SendClientMessage(playerid, COLOR_GREEN, "Acabas de editar una faccion.");
					return 1;
				}
				else if(!strcmp(option, "paga", true))
				{
					fInfo[faccID][Pay] = params[2];
					SaveFaction_data(faccID);
					SendClientMessage(playerid, COLOR_GREEN, "Acabas de editar una faccion.");
					return 1;
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREEN, "Uso: /editarfacc <Faccion ID> <Dinero - Paga - Exterior> <Valor (Opcional)>");
				}
			}
			else if(!strcmp(option, "exterior", true))
			{
				GetPlayerPos(playerid, fInfo[faccID][ExteriorPos][0], fInfo[faccID][ExteriorPos][1], fInfo[faccID][ExteriorPos][2]);
				DestroyDynamicPickup(fInfo[faccID][PickupID]);
				DestroyDynamic3DTextLabel(fInfo[faccID][LabelID]);
				fInfo[faccID][PickupID] = CreateDynamicPickup(fInfo[faccID][Pickup], 0, fInfo[faccID][ExteriorPos][0], fInfo[faccID][ExteriorPos][1], fInfo[faccID][ExteriorPos][2], 0, 0);
				new string[128];
				format(string, sizeof(string), "Faccion: %s\nID: %d", fInfo[faccID][Name], faccID);
				fInfo[faccID][LabelID] = CreateDynamic3DTextLabel(string, COLOR_WHITE, fInfo[faccID][ExteriorPos][0], fInfo[faccID][ExteriorPos][1], fInfo[faccID][ExteriorPos][2], 20.0);
				SaveFaction_data(faccID);
				SendClientMessage(playerid, COLOR_GREEN, "Acabas de editar una faccion.");
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREEN, "Uso: /editarfacc <Faccion ID> <Dinero - Paga - Exterior> <Valor (Opcional)>");
			}
        }
        else
        {
            SendClientMessage(playerid, COLOR_GREEN, "Uso: /editarfacc <Faccion ID> <Dinero - Paga Exterior> <Valor (Opcional)>");
        }
    }
    else
    {
        SendClientMessage(playerid, COLOR_RED, "No estas en modo administrador o no tienes permisos para esto.");
    }
    return 1;
}

CMD:contratar(playerid, params[])
{
	if(pInfo[playerid][FactionRol] >= ColiderF)
	{
		if(!sscanf(params, "d", params[0]))
		{
			if(fInfo[pInfo[playerid][Faction]][MembersC] == MAX_FMEMBER)		return 	SendClientMessage(playerid, COLOR_RED, "No puedes invitar a nadie mas, faccion llena.");
			if(IsPlayerConnected(params[0]))
			{
				if(ProxDetectorS(8.0, playerid, params[0]))
				{
					if(params[0] == playerid) 		return	SendClientMessage(playerid, COLOR_RED, "No puedes invitarte a ti mismo.");
					if(pInfo[params[0]][Faction] != 0)		return	SendClientMessage(playerid, COLOR_RED, "El jugador ya se encuentra en una faccion.");

					pInfo[params[0]][fInvite] = pInfo[playerid][Faction];
					SendClientMessage(playerid, COLOR_GREEN, "Enviaste una oferta.");
					ShowPlayerDialog(params[0], ContractDialog, DIALOG_STYLE_MSGBOX, "Oferta de trabajo", "Te ofrecieron un contrato, ¿Quieres aceptarlo y pertenecer a esta organizacion?", "Aceptar", "Rechazar");
				}
				else
				{
					SendClientMessage(playerid, COLOR_RED, "El jugador no esta cerca.");
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_RED, "El jugador no esta conectado.");
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREEN, "Uso: /contratar <ID>");
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_RED, "No eres lider de una faccion para realizar esto.");
	}
	return 1;
}

CMD:despedir(playerid, params[])
{
	if(pInfo[playerid][FactionRol] >= ColiderF)
	{
		if(!sscanf(params, "d", params[0]))
		{
			if(!IsPlayerConnected(params[0]))		return 		SendClientMessage(playerid, COLOR_RED, "El jugador no esta conectado.");
			if(pInfo[params[0]][Faction] != pInfo[playerid][Faction])		return 		SendClientMessage(playerid, COLOR_RED, "El jugador no esta en tu faccion.");
			if(pInfo[params[0]][FactionRol] > pInfo[playerid][FactionRol])		return 		SendClientMessage(playerid, COLOR_RED, "No puedes expulsar a tu lider.");
			if(params[0] == playerid) 		return	SendClientMessage(playerid, COLOR_RED, "No puedes expulsarte a ti mismo.");

			pInfo[params[0]][Faction] = 0;
			pInfo[params[0]][FactionRol] = 0;
			fInfo[pInfo[playerid][Faction]][MembersC]--;
			SaveFaction_data(pInfo[params[0]][Faction]);
			SaveUser_Data(params[0]);
			SendClientMessage(params[0], COLOR_GREEN, "El lider te ha echado de la faccion.");
			SendClientMessage(playerid, COLOR_GREEN, "Despediste a un jugador.");
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREEN, "Uso: /despedir <ID>");
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_RED, "No eres lider de una faccion para realizar esto.");
	}
	return 1;
}

CMD:darrango(playerid, params[])
{
	if(pInfo[playerid][FactionRol] >= ColiderF)
	{
		new rango[32];
		if(!sscanf(params, "ds[32]", params[0], rango))
		{
			if(!IsPlayerConnected(params[0]))		return 		SendClientMessage(playerid, COLOR_RED, "El jugador no esta conectado.");
			if(pInfo[params[0]][Faction] != pInfo[playerid][Faction])		return 		SendClientMessage(playerid, COLOR_RED, "El jugador no esta en tu faccion.");
			if(pInfo[params[0]][FactionRol] > pInfo[playerid][FactionRol])		return 		SendClientMessage(playerid, COLOR_RED, "No puedes cambiar el rango de tu lider.");
			if(params[0] == playerid) 		return	SendClientMessage(playerid, COLOR_RED, "No puedes cambiar tu mismo rango.");

			if(!strcmp(rango, "miembro", true))
			{
				pInfo[params[0]][FactionRol] = MiembroF;
				SaveUser_Data(params[0]);
				SendClientMessage(params[0], COLOR_GREEN, "El lider te ha dado rol Miembro.");
				SendClientMessage(playerid, COLOR_GREEN, "Cambiaste el rol a un jugador.");
			}
			else if(!strcmp(rango, "capitan", true))
			{
				pInfo[params[0]][FactionRol] = CapitanF;
				SaveUser_Data(params[0]);
				SendClientMessage(params[0], COLOR_GREEN, "El lider te ha dado rol Capitan.");
				SendClientMessage(playerid, COLOR_GREEN, "Cambiaste el rol a un jugador.");
			}
			else if(!strcmp(rango, "colider", true))
			{
				pInfo[params[0]][FactionRol] = ColiderF;
				SaveUser_Data(params[0]);
				SendClientMessage(params[0], COLOR_GREEN, "El lider te ha dado rol Colider.");
				SendClientMessage(playerid, COLOR_GREEN, "Cambiaste el rol a un jugador.");
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREEN, "Uso: /darrango <ID> <Miembro - Capitan - Colider>");
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREEN, "Uso: /darrango <ID> <Miembro - Capitan - Colider>");
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_RED, "No eres lider de una faccion para realizar esto.");
	}
	return 1;
}

CMD:retirarfondos(playerid,params[])
{
	if(pInfo[playerid][FactionRol] >= ColiderF)
	{
		if(!sscanf(params, "d", params[0]))
		{
			if(fInfo[pInfo[playerid][Faction]][Money] < params[0]) 		return  	SendClientMessage(playerid, COLOR_RED, "Fondos insuficientes.");

			pInfo[playerid][Money] += params[0];
			GivePlayerMoney(playerid, pInfo[playerid][Money]);
			fInfo[pInfo[playerid][Faction]][Money] -= params[0];
			SaveFaction_data(pInfo[playerid][Faction]);
			SendClientMessage(playerid, COLOR_GREEN, "Retiraste una cantidad de dinero de la faccion");
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREEN, "Uso: /retirarfondos <Cantidad>");
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_RED, "No eres lider de una faccion para realizar esto.");
	}
	return 1;
}

CMD:anadirfondos(playerid, params[])
{
	if(pInfo[playerid][FactionRol] >= ColiderF)
	{
		if(!sscanf(params, "d", params[0]))
		{
			if(pInfo[playerid][Money] < params[0]) 		return  	SendClientMessage(playerid, COLOR_RED, "Fondos insuficientes.");

			pInfo[playerid][Money] -= params[0];
			GivePlayerMoney(playerid, -params[0]);
			fInfo[pInfo[playerid][Faction]][Money] += params[0];
			SaveFaction_data(pInfo[playerid][Faction]);
			SendClientMessage(playerid, COLOR_GREEN, "Añadiste una cantidad de dinero de la faccion");
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREEN, "Uso: /anadirfondos <Cantidad>");
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_RED, "No eres lider de una faccion para realizar esto.");
	}
	return 1;
}

CMD:infofacc(playerid, params[])
{
	if(pInfo[playerid][Faction] != 0)
	{
		new info[1200], miembros[500], capitanes[500], coliders[500], string[64];
		for(new i = 0; i < MAX_PLAYERS; i++)
		{
			if (IsPlayerConnected(i))
			{
				if(pInfo[i][Faction] == pInfo[playerid][Faction])
				{
					if(pInfo[i][FactionRol] == MiembroF)
					{
						format(string, sizeof(string), "%s - ", GetPlayerNameEx(i));
						strcat(miembros, string);
					}
					if(pInfo[i][FactionRol] == CapitanF)
					{
						format(string, sizeof(string), "%s - ", GetPlayerNameEx(i));
						strcat(capitanes, string);
					}
					if(pInfo[i][FactionRol] == ColiderF)
					{
						format(string, sizeof(string), "%s - ", GetPlayerNameEx(i));
						strcat(coliders, string);
					}
				}
			}
		}
		format(info, sizeof(info), "Lider: %s\n\nMiembros conectados:\n\nColideres: %s\n\nCapitanes: %s\n\nMiembros: %s\n\nDinero: %d", fInfo[pInfo[playerid][Faction]][Leader], coliders, capitanes, miembros, fInfo[pInfo[playerid][Faction]][Money]);
		ShowPlayerDialog(playerid, KEY_DIALOG, DIALOG_STYLE_MSGBOX, fInfo[pInfo[playerid][Faction]][Name], info, "Cerrar", "");
	}
	else
	{
		SendClientMessage(playerid, COLOR_RED, "No estas en una faccion para realizar esto.");
	}
	return 1;
}