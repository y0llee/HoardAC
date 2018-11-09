# HoardAC ( 1 . 61 )
Anti-Cheat system for the SA-MP.
Author: yollee

To enable Anti-Cheat, configure it using as s and connect include (#include <HoardAC>)

Functions:
```pawn
SetPlayerPosAC(playerid, Float:X, Float:Y, Float:Z); - Sets the position for the player through the anti-cheat method.
SetPlayerMoneyAC(playerid, money); - Sets the amount of money using the anti-cheat method.
SetPlayerHealthAC(playerid, health); - Sets the amount of health using the anti-cheat method.
SetPlayerArmourAC(playerid, armour); - Sets the amount of armor using the anti-cheat method.

GetPlayerMoneyAC(playerid); - Gets the true amount of player money.
GetPlayerHealthAC(playerid); - Gets the true amount of health of the player.
GetPlayerArmourAC(playerid); - Gets the true amount of the player's armor.
```
Callback's:
```pawn
public OnPlayerFlyCheat(playerid); - Called when using a cheat on a fly, returns the playerid argument.
public OnPlayerAimCheat(playerid); - Called when using a cheat on a aim, returns the playerid argument.
public OnPlayerWeaponCheat(playerid); - Called when using a cheat on a weapon, returns the playerid argument.

public OnPlayerMoneyCheat(playerid); - Called when using a cheat on a money, returns the playerid argument.
public OnPlayerHealthCheat(playerid); - Called when using a cheat on a health, returns the playerid argument.
public OnPlayerArmourCheat(playerid); - Called when using a cheat on a armour, returns the playerid argument.

public OnPlayerTeleportCheat(playerid); - Called when using a cheat on a teleport, returns the playerid argument.
public OnPlayerNopPos(playerid); - Called when using a cheat on a nop position, returns the playerid argument.
public OnPlayerHighPing(playerid); - Called when ping is greater than limited. Returns the playerid argument.
```

Example of use:
```pawn
forward OnPlayerFlyCheat(playerid);
public OnPlayerFlyCheat(playerid)
{
	Ban(playerid);
	return 1;
}

forward OnPlayerAimCheat(playerid);
public OnPlayerAimCheat(playerid)
{
	Kick(playerid);
	return 1;
}

forward OnPlayerWeaponCheat(playerid);
public OnPlayerWeaponCheat(playerid)
{
	Kick(playerid);
	return 1;
}

forward OnPlayerMoneyCheat(playerid);
public OnPlayerMoneyCheat(playerid)
{
	Ban(playerid);
	return 1;
}

forward OnPlayerHealthCheat(playerid);
public OnPlayerHealthCheat(playerid)
{
	Kick(playerid);
	return 1;
}

forward OnPlayerArmourCheat(playerid);
public OnPlayerArmourCheat(playerid)
{
	Kick(playerid);
	return 1;
}

forward OnPlayerTeleportCheat(playerid);
public OnPlayerTeleportCheat(playerid)
{
	Kick(playerid);
	return 1;
}

forward OnPlayerNopPos(playerid);
public OnPlayerNopPos(playerid)
{
	Kick(playerid);
	return 1;
}

forward OnPlayerHighPing(playerid);
public OnPlayerHighPing(playerid)
{
	Kick(playerid);
	return 1;
}
```
