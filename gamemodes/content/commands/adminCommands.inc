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
                GetPlayerHealth(playerid, pInfo[playerid][Health]);
                GetPlayerArmour(playerid, pInfo[playerid][Armour]);
                SetPlayerHealth(playerid, 100);
		        SetPlayerArmour(playerid, 100);
			}
			case Moderador:
			{
				new string[128];
				format(string, sizeof(string), "[NoJodan] El moderador "COLOR_WHITE_T"%s(%i) esta en servicio.", GetPlayerNameEx(playerid), playerid);
				SendClientMessageToAll(COLOR_GREEN, string);
				SetPlayerColor(playerid, COLOR_MODERADOR);
				pInfo[playerid][OnDuty] = 1;
                GetPlayerHealth(playerid, pInfo[playerid][Health]);
                GetPlayerArmour(playerid, pInfo[playerid][Armour]);
                SetPlayerHealth(playerid, 100);
		        SetPlayerArmour(playerid, 100);
			}
			case Administrador:
			{
				new string[128];
				format(string, sizeof(string), "[NoJodan] El administrador "COLOR_WHITE_T"%s(%i) esta en servicio.", GetPlayerNameEx(playerid), playerid);
				SendClientMessageToAll(COLOR_GREEN, string);
				SetPlayerColor(playerid, COLOR_ADMINISTRADOR);
				pInfo[playerid][OnDuty] = 1;
                GetPlayerHealth(playerid, pInfo[playerid][Health]);
                GetPlayerArmour(playerid, pInfo[playerid][Armour]);
                SetPlayerHealth(playerid, 100);
		        SetPlayerArmour(playerid, 100);
			}
			case Programador:
			{
				new string[128];
				format(string, sizeof(string), "[NoJodan] El programador "COLOR_WHITE_T"%s(%i) esta en servicio.", GetPlayerNameEx(playerid), playerid);
				SendClientMessageToAll(COLOR_GREEN, string);
				SetPlayerColor(playerid, COLOR_PROGRAMADOR);
				pInfo[playerid][OnDuty] = 1;
                GetPlayerHealth(playerid, pInfo[playerid][Health]);
                GetPlayerArmour(playerid, pInfo[playerid][Armour]);
                SetPlayerHealth(playerid, 100);
		        SetPlayerArmour(playerid, 100);
			}
			case Dueno:
			{
				new string[128];
				format(string, sizeof(string), "[NoJodan] El dueño "COLOR_WHITE_T"%s(%i) esta en servicio.", GetPlayerNameEx(playerid), playerid);
				SendClientMessageToAll(COLOR_GREEN, string);
				SetPlayerColor(playerid, COLOR_DUEÑO);
				pInfo[playerid][OnDuty] = 1;
                GetPlayerHealth(playerid, pInfo[playerid][Health]);
                GetPlayerArmour(playerid, pInfo[playerid][Armour]);
                SetPlayerHealth(playerid, 100);
		        SetPlayerArmour(playerid, 100);
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
                SetPlayerHealth(playerid, pInfo[playerid][Health]);
                SetPlayerArmour(playerid, pInfo[playerid][Armour]);
			}
			case Moderador:
			{
				new string[128];
				format(string, sizeof(string), "[NoJodan] El moderador "COLOR_WHITE_T"%s(%i) esta fuera de servicio.", GetPlayerNameEx(playerid), playerid);
				SendClientMessageToAll(COLOR_GREEN, string);
				SetPlayerColor(playerid, COLOR_USUARIO);
				pInfo[playerid][OnDuty] = 0;
                SetPlayerHealth(playerid, pInfo[playerid][Health]);
                SetPlayerArmour(playerid, pInfo[playerid][Armour]);
			}
			case Administrador:
			{
				new string[128];
				format(string, sizeof(string), "[NoJodan] El administrador "COLOR_WHITE_T"%s(%i) esta fuera de servicio.", GetPlayerNameEx(playerid), playerid);
				SendClientMessageToAll(COLOR_GREEN, string);
				SetPlayerColor(playerid, COLOR_USUARIO);
				pInfo[playerid][OnDuty] = 0;
                SetPlayerHealth(playerid, pInfo[playerid][Health]);
                SetPlayerArmour(playerid, pInfo[playerid][Armour]);
			}
			case Programador:
			{
				new string[128];
				format(string, sizeof(string), "[NoJodan] El programador "COLOR_WHITE_T"%s(%i) esta fuera de servicio.", GetPlayerNameEx(playerid), playerid);
				SendClientMessageToAll(COLOR_GREEN, string);
				SetPlayerColor(playerid, COLOR_USUARIO);
				pInfo[playerid][OnDuty] = 0;
                SetPlayerHealth(playerid, pInfo[playerid][Health]);
                SetPlayerArmour(playerid, pInfo[playerid][Armour]);
			}
			case Dueno:
			{
				new string[128];
				format(string, sizeof(string), "[NoJodan] El dueno "COLOR_WHITE_T"%s(%i) esta fuera de servicio.", GetPlayerNameEx(playerid), playerid);
				SendClientMessageToAll(COLOR_GREEN, string);
				SetPlayerColor(playerid, COLOR_USUARIO);
				pInfo[playerid][OnDuty] = 0;
                SetPlayerHealth(playerid, pInfo[playerid][Health]);
                SetPlayerArmour(playerid, pInfo[playerid][Armour]);
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
			SendClientMessage(playerid, COLOR_GREEN, "Haz obtenido el rol DUEÑO.");
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