CMD:entrar(playerid, params[])
{
   // Verificamos si el jugador esta de pie o en el suelo, estado normal
    if(GetPlayerState(playerid) == 1)
    {
        // Entrada a interiores facciones
        for(new i = 1; i <= COUNT_FACTIONS; i++)
        {
            if(IsPlayerInRangeOfPoint(playerid, 2.0, fInfo[i][ExteriorPos][0], fInfo[i][ExteriorPos][1], fInfo[i][ExteriorPos][2]))
            {
                SetPlayerVirtualWorld(playerid, 1);
                SetPlayerInterior(playerid, fInfo[i][InteriorID]);
                SetPlayerPos(playerid, fInfo[i][InteriorPos][0], fInfo[i][InteriorPos][1], fInfo[i][InteriorPos][2]);
            }
            else if(IsPlayerInRangeOfPoint(playerid, 2.0, fInfo[i][InteriorPos][0], fInfo[i][InteriorPos][1], fInfo[i][InteriorPos][2]))
            {
                SetPlayerVirtualWorld(playerid, 0);
                SetPlayerInterior(playerid, 0);
                SetPlayerPos(playerid, fInfo[i][ExteriorPos][0], fInfo[i][ExteriorPos][1], fInfo[i][ExteriorPos][2]);
            }
        }
    }
    return 1;
}