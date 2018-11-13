# HoardAC ( 3 . 21 )
Anti-Cheat system for the SA-MP.
Author: yollee

To enable Anti-Cheat, configure it using as s and connect include.

# Fix of false positives:
```pawn
public OnGameModeInit()
{
	SetMaxPing(500);
	return 1;
}

public OnPlayerSpawn(playerid)
{
	SetPlayerPosAC(playerid, 15, 15, 15); // your position
	return 1;
}
```

# Functions:
```pawn
SetPlayerPosAC(playerid, Float:X, Float:Y, Float:Z); - Sets the position for the player through the anti-cheat method.
SetPlayerMoneyAC(playerid, money); - Sets the amount of money using the anti-cheat method.
SetPlayerHealthAC(playerid, health); - Sets the amount of health using the anti-cheat method.
SetPlayerArmourAC(playerid, armour); - Sets the amount of armor using the anti-cheat method.

GetPlayerMoneyAC(playerid); - Gets the true amount of player money.
GetPlayerHealthAC(playerid); - Gets the true amount of health of the player.
GetPlayerArmourAC(playerid); - Gets the true amount of the player's armor.
```
# Codes:
```pawn
0x721: High Ping
0x487: Cheat on Money
0x466: Cheat on Armor
0x618: Cheat on Weapon
0x421: Cheat on Health
0x241: Cheat on Nop Position
0x433: Cheat on Teleport
0x982: Cheat on Fly
```

# Example of use:
```pawn
forward OnPlayerCheat(playerid, code); // code type: string
public OnPlayerCheat(playerid, code)
{
	Kick(playerid);
	return 1;
}
```
