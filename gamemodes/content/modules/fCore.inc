//Determina la proximidad de un jugador frente a ls otros
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

forward ProxDetectorS(Float:radi, playerid, targetid);
public ProxDetectorS(Float:radi, playerid, targetid)
{
	new Float: fp_playerPos[3];
	GetPlayerPos(targetid, fp_playerPos[0], fp_playerPos[1], fp_playerPos[2]);
	if(IsPlayerInRangeOfPoint(playerid, radi, fp_playerPos[0], fp_playerPos[1], fp_playerPos[2]) && GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(targetid))
	{
		return 1;
	}
	return 0;
}

//Funcion para cargar los datos de las facciones al inicio de la GM
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

//Funcion para guardar los datos de las facciones al salir de la GM
SaveFaction_DataExit()
{
	COUNT_FACTIONS = getFactionNum();
	if(COUNT_FACTIONS > 0)
	{
		for(new i = 1; i <= COUNT_FACTIONS; i++)
		{
			SaveFaction_data(i);
		}
	}
	return 1;
}

//Obtenemos el numero de facciones existentes
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

//Para tener el nombre sin ningun signo: Lawliet_Salvatore -> Lawliet Salvatore
GetPlayerNameEx(playerid)
{
	new sz_playerName[MAX_PLAYER_NAME], i_pos;
	GetPlayerName(playerid, sz_playerName, MAX_PLAYER_NAME);
	while ((i_pos = strfind(sz_playerName, "_", false, i_pos)) != -1) sz_playerName[i_pos] = ' ';
	return sz_playerName;
}

//Para kickear a un jugador
forward KickInTime(playerid);
public KickInTime(playerid)
{
	return Kick(playerid);
}