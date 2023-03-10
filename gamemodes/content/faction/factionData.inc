//Enum del sistema de Facciones
enum FactionData
{
	Name[MAX_PLAYER_NAME],
	Leader[MAX_PLAYER_NAME],
	Float:ExteriorPos[3],
	Money,
	Pay,
	MembersC
};
new fInfo[MAX_FACTIONS][FactionData];