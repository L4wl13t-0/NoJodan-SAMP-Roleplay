//Enum del sistema de registro
enum PlayerData
{
	Pass,
	Money,
	Float:Health,
	Float:Armour,
	Sex,
	Age,
	VIP,
	Admin,
	OnDuty,
	Float:PosX,
	Float:PosY,
	Float:PosZ,
	Float:PosA,
	Skin,
	VirtualW,
	Interior,
	Weapon[13],
	Ammo[13],
	TriesL,
	TriesR,
	Faction,
	FactionRol,
	fInvite
};
new pInfo[MAX_PLAYERS][PlayerData];