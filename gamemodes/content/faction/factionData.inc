//Enum del sistema de Facciones
enum FactionData
{
	Name[MAX_PLAYER_NAME],
	Leader[MAX_PLAYER_NAME],
	Coleader1[MAX_PLAYER_NAME],
	Coleader2[MAX_PLAYER_NAME],
	Captain1[MAX_PLAYER_NAME],
	Captain2[MAX_PLAYER_NAME],
	Member1[MAX_PLAYER_NAME],
	Member2[MAX_PLAYER_NAME],
	Member3[MAX_PLAYER_NAME],
	Member4[MAX_PLAYER_NAME],
	Member5[MAX_PLAYER_NAME],
	Float:ExteriorPos[3],
	Money,
	Pay
};
new fInfo[MAX_FACTIONS][FactionData];