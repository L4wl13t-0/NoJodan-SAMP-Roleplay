CMD:crearfacc(playerid, params[])
{
	if(pInfo[playerid][Admin] > Moderador && pInfo[playerid][OnDuty] == 1)
    {
		if(isnull(params)) return SendClientMessage(playerid, COLOR_WHITE, "Utiliza: /crearfacc <Nombre Faccion>");

		//new factionNum = getFactionNum();
		if(COUNT_FACTIONS < MAX_FACTIONS)
		{
			new INI:File = INI_Open(FactionPath(COUNT_FACTIONS+1));
			INI_SetTag(File, "Faction Data");
			INI_WriteString(File, "Name", params);
			INI_WriteString(File, "Leader", "Ninguno");
			INI_WriteFloat(File, "ExteriorX", 0);
			INI_WriteFloat(File, "ExteriorY",0);
			INI_WriteFloat(File, "ExteriorZ", 0);
			INI_WriteInt(File, "Money", 50000);
			INI_WriteInt(File, "Pay", 25000);
			INI_WriteInt(File, "MembersC", 1);
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