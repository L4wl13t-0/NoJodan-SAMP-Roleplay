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