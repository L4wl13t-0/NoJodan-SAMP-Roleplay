//Funcion para cargar los datos de las facciones
forward LoadFaction_data(factionid, name[], value[]);
public LoadFaction_data(factionid, name[], value[])
{
	INI_String("Name", fInfo[factionid][Name], MAX_PLAYER_NAME);
	INI_String("Leader", fInfo[factionid][Leader], MAX_PLAYER_NAME);
	INI_Float("ExteriorX", fInfo[factionid][ExteriorPos][0]);
	INI_Float("ExteriorY", fInfo[factionid][ExteriorPos][1]);
	INI_Float("ExteriorZ", fInfo[factionid][ExteriorPos][2]);
	INI_Int("Money", fInfo[factionid][Money]);
	INI_Int("Pay", fInfo[factionid][Pay]);
	INI_Int("MembersC", fInfo[factionid][MembersC]);
	return 1;
}

//Funcion para guardar los datos de las facciones
forward SaveFaction_data(factionid);
public SaveFaction_data(factionid)
{
	if(fexist(FactionPath(factionid)))
	{
		new INI:File = INI_Open(FactionPath(factionid));
		INI_SetTag(File, "Faction Data");
		INI_WriteString(File, "Name", fInfo[factionid][Name]);
		INI_WriteString(File, "Leader", fInfo[factionid][Leader]);
		INI_WriteFloat(File, "ExteriorX", fInfo[factionid][ExteriorPos][0]);
		INI_WriteFloat(File, "ExteriorY", fInfo[factionid][ExteriorPos][1]);
		INI_WriteFloat(File, "ExteriorZ", fInfo[factionid][ExteriorPos][2]);
		INI_WriteInt(File, "Money", fInfo[factionid][Money]);
		INI_WriteInt(File, "Pay", fInfo[factionid][Pay]);
		INI_WriteInt(File, "MembersC", fInfo[factionid][MembersC]);
		INI_Close(File);
	}
	return 1;
}

//Stock para obtener el path de las facciones
stock FactionPath(factionid)
{
	new string[128];
	format(string, sizeof(string), "/Factions/%d.ini", factionid);
	return string;
}