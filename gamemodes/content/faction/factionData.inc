//Enum del sistema de Facciones
enum FactionData
{
	Name[MAX_PLAYER_NAME],
	Leader[MAX_PLAYER_NAME],
	Float:ExteriorPos[3],
	Money,
	Pay,
	MembersC,
	Pickup,
	PickupID,
	Text3D:LabelID
};
new fInfo[MAX_FACTIONS][FactionData];