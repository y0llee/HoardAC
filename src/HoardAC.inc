// MIT License
//
// Copyright (c) 2018 yollee
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

// Author: yollee

// List Anti-Cheats:

// 		WeaponHack
//      AntiDeAMX
// 		FlyHack
// 		MoneyHack
// 		HealthHack
// 		ArmourHack
// 		TeleportHack
// 		AimHack
// 		NopPos
// 		HighPing

#include <a_samp>

public OnGameModeInit()
{
	new a[][] =     {"Unarmed (Fist)","Brass K"};
	#pragma unused a

	print("\n----------------------------------");
	print(" Hoard Anti-Cheat loaded!");
	print(" by yollee");
	print("----------------------------------\n");
	return 1;
}
#if defined _ALS_OnGameModeInit
		#undef OnGameModeInit
	#else
		#define _ALS_OnGameModeInit
	#endif
	#define OnGameModeInit AC_OnGameModeInit
	forward OnGameModeInit();

new
			 wInfo[MAX_PLAYERS][47],
			 
			 FlyTimer[MAX_PLAYERS],
			 TpTimer[MAX_PLAYERS],
			 
			 bool:PlayerSpawned[MAX_PLAYERS],
			 Float:acX[MAX_PLAYERS], Float:acY[MAX_PLAYERS], Float:acZ[MAX_PLAYERS],
			 
			 MonA[MAX_PLAYERS],
			 Float:HeaA[MAX_PLAYERS],
			 Float:ArmA[MAX_PLAYERS],
			 
			 HpTimer[MAX_PLAYERS],
			 ArmTimer[MAX_PLAYERS],
			 MoneyTimer[MAX_PLAYERS],
			 
			 PingTimer[MAX_PLAYERS],
			 MaximPing;

public OnPlayerConnect(playerid)
{
    ResetPlayerMoney(playerid);

	HeaA[playerid] = 0;
	ArmA[playerid] = 0;
	MonA[playerid] = 0;

    PlayerSpawned[playerid] = false;
    
	FlyTimer[playerid] = SetTimerEx("OnPlayerFlyHack", 1000, true, "i", playerid);
	TpTimer[playerid] = SetTimerEx("OnPlayerTeleportHack", 1000, true, "i", playerid);
	
	HpTimer[playerid] = SetTimerEx("OnPlayerHealthHack", 1000, true, "i", playerid);
	ArmTimer[playerid] = SetTimerEx("OnPlayerArmourHack", 1000, true, "i", playerid);
	MoneyTimer[playerid] = SetTimerEx("OnPlayerMoneyHack", 1000, true, "i", playerid);
	
	PingTimer[playerid] = SetTimerEx("OnPlayerHighPing", 1000, true, "i", playerid);
    return 1;
}
#if defined _ALS_OnPlayerConnect
		#undef OnPlayerConnect
	#else
		#define _ALS_OnPlayerConnect
	#endif
	#define OnPlayerConnect AC_OnPlayerConnect
	forward OnPlayerConnect(playerid);

public OnPlayerDisconnect(playerid)
{
	KillTimer(FlyTimer[playerid]);
	KillTimer(TpTimer[playerid]);
	KillTimer(HpTimer[playerid]);
	KillTimer(ArmTimer[playerid]);
	KillTimer(MoneyTimer[playerid]);
	KillTimer(PingTimer[playerid]);
    return 1;
}
#if defined _ALS_OnPlayerDisconnect
		#undef OnPlayerDisconnect
	#else
		#define _ALS_OnPlayerDisconnect
	#endif
	#define OnPlayerDisconnect AC_OnPlayerDisconnect
	forward OnPlayerDisconnect(playerid, reason);

public OnPlayerSpawn(playerid)
{
	PlayerSpawned[playerid] = true;
	return 1;
}
#if defined _ALS_OnPlayerSpawn
		#undef OnPlayerSpawn
	#else
		#define _ALS_OnPlayerSpawn
	#endif
	#define OnPlayerSpawn AC_OnPlayerSpawn
	forward OnPlayerSpawn(playerid);

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
	if(wInfo[playerid][weaponid] != GetPlayerAmmo(playerid)) CallRemoteFunction("OnPlayerWeaponHack", "i", playerid);
	new Float:tmp, Float:hX, Float:hY, Float:hZ;
	GetPlayerLastShotVectors(playerid, tmp, tmp, tmp, hX, hY, hZ);
	if(!IsPlayerInRangeOfPoint(playerid, 3.0, hX, hY, hZ) && !IsPlayerFacingCoords(playerid, hX, hY, 8)) CallRemoteFunction("OnPlayerAimHack", "i", playerid);
    return 1;
}
#if defined _ALS_OnPlayerWeaponShot
		#undef OnPlayerWeaponShot
	#else
		#define _ALS_OnPlayerWeaponShot
	#endif
	#define OnPlayerWeaponShot AC_OnPlayerWeaponShot
	forward OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ);

stock GetWeaponSlot(weaponid)
{
     switch(weaponid)
     {
		case 0,1: return 0;
		case 2..9: return 1;
		case 10..15: return 10;
		case 16..18,39: return 8;
		case 22..24: return 2;
		case 25..27: return 3;
		case 28,29,32: return 4;
		case 30,31: return 5;
		case 33,34: return 6;
		case 35..38: return 7;
		case 40: return 12;
		case 41..43: return 9;
 		case 44..46: return 11;
     }
     return -1;
}

stock GivePlayerWeaponAC(playerid, weaponid, ammo)
{
	wInfo[playerid][weaponid] += ammo;
	GivePlayerWeapon(playerid, weaponid, ammo);
	return 1;
}

forward OnPlayerFlyHack(playerid);
public OnPlayerFlyHack(playerid)
{
	new animlib[32], animname[32];
	GetAnimationName(GetPlayerAnimationIndex(playerid), animlib, sizeof animlib, animname, sizeof animname);
	new Float:X, Float:Y, Float:Z;
	GetPlayerPos(playerid, X, Y, Z);
	if(Z > 2 && !IsPlayerInWater(playerid))
	{
	    if(strcmp(animlib, "SWIM", true) == 0 && strcmp(animname, "SWIM_crawl", true) == 0)
	    {
	        CallRemoteFunction("OnPlayerFlyHack", "i", playerid);
	    }
	}
	return 1;
}

forward OnPlayerTeleportHack(playerid);
public OnPlayerTeleportHack(playerid)
{
	if(PlayerSpawned[playerid] == true)
	{
	    if(GetPlayerDistanceFromPoint(playerid, acX[playerid], acY[playerid], acZ[playerid]) > 100.0) CallRemoteFunction("OnPlayerTeleportHack", "i", playerid);
        GetPlayerPos(playerid, acX[playerid], acY[playerid], acZ[playerid]);

        new Float:X, Float:Y, Float:Z;
        GetPlayerPos(playerid, X, Y, Z);

        if(!IsPlayerInRangeOfPoint(playerid, 5.0, X, Y, Z)) CallRemoteFunction("OnPlayerNopPos", "i", playerid);
	}
}

forward OnPlayerHealthHack(playerid);
public OnPlayerHealthHack(playerid)
{
    new Float:hp;
    GetPlayerHealth(playerid, hp);
	if(HeaA[playerid] != hp) CallRemoteFunction("OnPlayerHealthHack", "i", playerid);
	GetPlayerHealth(playerid, HeaA[playerid]);
	return 1;
}

forward OnPlayerMoneyHack(playerid);
public OnPlayerMoneyHack(playerid)
{
    if(MonA[playerid] != GetPlayerMoney(playerid)) CallRemoteFunction("OnPlayerMoneyHack", "i", playerid);
    MonA[playerid] = GetPlayerMoney(playerid);
	return 1;
}

forward OnPlayerArmourHack(playerid);
public OnPlayerArmourHack(playerid)
{
	new Float:arm;
	GetPlayerArmour(playerid, arm);
    if(ArmA[playerid] != arm) CallRemoteFunction("OnPlayerArmourHack", "i", playerid);
    GetPlayerArmour(playerid, ArmA[playerid]);
	return 1;
}

forward OnPlayerHighPing(playerid);
public OnPlayerHighPing(playerid)
{
	if(GetPlayerPing(playerid) > MaximPing) CallRemoteFunction("OnPlayerHighPing", "i", playerid);
	return 1;
}

Float:GetAngle(Float:x, Float:y, Float:ix, Float:iy)
{
        new Float:absoluteangle, Float:tmpangle, Float:misc = 5.0;
        tmpangle = 180.0 - atan2(x-ix,y-iy);
        tmpangle += misc;
        misc *= -1;
        absoluteangle = tmpangle + misc;
        return absoluteangle;
}

stock IsPlayerFacingCoords(playerid, Float:destx, Float:desty, offset = 0)
{
        new Float:px, Float:py, Float:pz, Float:a, Float:a2;
        GetPlayerPos(playerid, px, py, pz);
        GetPlayerFacingAngle(playerid, a);
        a2 = GetAngle(px, py, destx, desty);
        if((a2 + offset) > 360) a2 = 360 - offset;
        if((a2 - offset) < 0) a2 = 0 + offset;
        if(a < (a2 + offset) && a > (a2 - offset)) return 1;
        return 0;
}

stock GetPlayerHealthAC(playerid)
{
	return HeaA[playerid];
}
#define GetPlayerHealth GetPlayerHealthAC

#if defined _ALS_GetPlayerHealthAC
    #undef    GetPlayerHealthAC
#else
    #define    _ALS_GetPlayerHealthAC
#endif

stock GetPlayerArmourAC(playerid)
{
	return ArmA[playerid];
}
#define GetPlayerArmour GetPlayerArmourAC
#if defined _ALS_GetPlayerArmourAC
    #undef    GetPlayerArmourAC
#else
    #define    _ALS_GetPlayerArmourAC
#endif

stock GetPlayerMoneyAC(playerid)
{
	return MonA[playerid];
}
#define GetPlayerMoney GetPlayerMoneyAC
#if defined _ALS_GetPlayerMoneyAC
    #undef    GetPlayerMoneyAC
#else
    #define    _ALS_GetPlayerMoneyAC
#endif

stock SetPlayerPosAC(playerid, Float:X, Float:Y, Float:Z)
{
    acX[playerid] = X, acY[playerid] = Y, acZ[playerid] = Z;
    SetPlayerPos(playerid, X, Y, Z);
    return 1;
}
#define SetPlayerPos SetPlayerPosAC
#if defined _ALS_SetPlayerPosAC
    #undef    SetPlayerPosAC
#else
    #define    _ALS_SetPlayerPosAC
#endif

stock SetPlayerHealthAC(playerid, health)
{
	HeaA[playerid] = armour;
	ResetPlayerHealth(playerid);
	SetPlayerHealth(playerid, health);
	return 1;
}
#define SetPlayerHealth SetPlayerHealthAC
#if defined _ALS_SetPlayerHealthAC
    #undef    SetPlayerHealthAC
#else
    #define    _ALS_SetPlayerHealthAC
#endif


stock SetPlayerArmourAC(playerid, armour)
{
	ArmA[playerid] = armour;
	ResetPlayerArmour(playerid);
	SetPlayerArmour(playerid, armour);
	return 1;
}
#define SetPlayerArmour SetPlayerArmourAC
#if defined _ALS_SetPlayerArmourAC
    #undef    SetPlayerArmourAC
#else
    #define    _ALS_SetPlayerArmourAC
#endif

stock SetPlayerMoneyAC(playerid, money)
{
	MonA[playerid] += money;
	ResetPlayerMoney(playerid);
	GivePlayerMoney(money);
	return 1;
}
#define SetPlayerMoney SetPlayerMoneyAC
#if defined _ALS_SetPlayerMoneyAC
    #undef    SetPlayerMoneyAC
#else
    #define    _ALS_SetPlayerMoneyAC
#endif

stock SetMaxPing(playerid, ping)
{
	MaximPing = ping;
	return 1;
}
#if defined _ALS_SetMaxPing
    #undef    SetMaxPing
#else
    #define    _ALS_SetMaxPing
#endif

stock IsPlayerInWater(playerid)
{
        new Float:Z;
        GetPlayerPos(playerid,Z,Z,Z);
        if(Z < 0.7) switch(GetPlayerAnimationIndex(playerid)) { case 1543,1538,1539: return 1; }
        if(GetPlayerDistanceFromPoint(playerid,-965,2438,42) <= 700 && Z < 45)return 1;
        new Float:water_places[][] =
        {
                {25.0,  2313.0, -1417.0,        23.0},
                {15.0,  1280.0, -773.0,         1082.0},
                {15.0,  1279.0, -804.0,         86.0},
                {20.0,  1094.0, -674.0,         111.0},
                {26.0,  194.0,  -1232.0,        76.0},
                {25.0,  2583.0, 2385.0,         15.0},
                {25.0,  225.0,  -1187.0,        73.0},
                {50.0,  1973.0, -1198.0,        17.0}
        };
        for(new t=0; t < sizeof water_places; t++)
                if(GetPlayerDistanceFromPoint(playerid,water_places[t][1],water_places[t][2],water_places[t][3]) <= water_places[t][0]) return 1;
        return 0;
}
