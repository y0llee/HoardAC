# HoardAC
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
public OnPlayerFlyHack(playerid); - Called when using a cheat on a fly, returns the playerid argument.
public OnPlayerAimHack(playerid); - Called when using a cheat on a aim, returns the playerid argument.
public OnPlayerWeaponHack(playerid); - Called when using a cheat on a weapon, returns the playerid argument.

public OnPlayerMoneyHack(playerid); - Called when using a cheat on a money, returns the playerid argument.
public OnPlayerHealthHack(playerid); - Called when using a cheat on a health, returns the playerid argument.
public OnPlayerArmourHack(playerid); - Called when using a cheat on a armour, returns the playerid argument.

public OnPlayerTeleportHack(playerid); - Called when using a cheat on a teleport, returns the playerid argument.
public OnPlayerNopPos(playerid); - Called when using a cheat on a nop position, returns the playerid argument.
public OnPlayerHighPing(playerid); - Called when ping is greater than limited. Returns the playerid argument.
```
