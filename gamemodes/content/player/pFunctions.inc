#define 				User_Path					"/Users/%s.ini"

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
	INI_Int("fInvite", pInfo[playerid][fInvite]);
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

//Funcion para guardar los datos de los usuarios
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
		INI_WriteInt(File, "fInvite", pInfo[playerid][fInvite]);
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

//Stock para obtener el path del usuario
stock UserPath(playerid)
{
	new string[128], playername[MAX_PLAYER_NAME];
	GetPlayerName(playerid, playername, sizeof(playername));
	format(string, sizeof(string), User_Path, playername);
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