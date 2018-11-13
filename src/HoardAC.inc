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
//              AntiDeAMX
// 		FlyHack
// 		MoneyHack
// 		HealthHack
// 		ArmourHack
// 		TeleportHack
// 		NopPos
// 		HighPing
//              InvisibleHack
//              SpeedHack (Vehicle)

#include <a_samp>
#define NULL 0

new
			 wInfo[MAX_PLAYERS][47],

			 FlyTimer[MAX_PLAYERS],
			 TpTimer[MAX_PLAYERS],

			 bool:PlayerSpawned[MAX_PLAYERS],
			 Float:acX[MAX_PLAYERS], Float:acY[MAX_PLAYERS], Float:acZ[MAX_PLAYERS],

			 MonA[MAX_PLAYERS],
			 Float:HeaA[MAX_PLAYERS],
			 Float:ArmA[MAX_PLAYERS],
			 
			 bool:Invis[MAX_PLAYERS],

			 HpTimer[MAX_PLAYERS],
			 ArmTimer[MAX_PLAYERS],
			 MoneyTimer[MAX_PLAYERS],
			 
			 VehTimer[MAX_PLAYERS],
			 
			 InvisibleTimer[MAX_PLAYERS],

             WeaponTimer[MAX_PLAYERS],

			 PingTimer[MAX_PLAYERS],
			 MaximPing;
			 
public OnGameModeInit()
{
	new a[][] =     {"Unarmed (Fist)","Brass K"};
	#pragma unused a

	print("\n----------------------------------");
	print(" Hoard Anti-Cheat loaded!");
	print(" by yollee");
	print("----------------------------------\n");
	
	if(MaximPing == NULL)
	{
		MaximPing = 500;
	}
	return 1;
}
#if defined _ALS_OnGameModeInit
		#undef OnGameModeInit
	#else
		#define _ALS_OnGameModeInit
	#endif
	#define OnGameModeInit AC_OnGameModeInit
	forward OnGameModeInit();

public OnPlayerConnect(playerid)
{
    ResetPlayerMoney(playerid);

	HeaA[playerid] = NULL;
	ArmA[playerid] = NULL;
	MonA[playerid] = NULL;
	
	Invis[playerid] = false;

    PlayerSpawned[playerid] = false;
    
	FlyTimer[playerid] = SetTimerEx("OnPlayerFlyHack", 1000, true, "i", playerid);
	TpTimer[playerid] = SetTimerEx("OnPlayerTeleportHack", 1000, true, "i", playerid);
	
	InvisibleTimer[playerid] = SetTimerEx("OnPlayerInvisibleHack", 1000, true, "i", playerid);
	
	HpTimer[playerid] = SetTimerEx("OnPlayerHealthHack", 1000, true, "i", playerid);
	ArmTimer[playerid] = SetTimerEx("OnPlayerArmourHack", 1000, true, "i", playerid);
	MoneyTimer[playerid] = SetTimerEx("OnPlayerMoneyHack", 1000, true, "i", playerid);
	
	WeaponTimer[playerid] = SetTimerEx("OnPlayerWeaponHack", 1000, true, "i", playerid);
	
	PingTimer[playerid] = SetTimerEx("OnPlayerHigPing", 1000, true, "i", playerid);
	
	VehTimer[playerid] = SetTimerEx("OnSpeedVehicle", 1000, true, "i", playerid);
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
	KillTimer(WeaponTimer[playerid]);
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
	Invis[playerid] = true;
	HeaA[playerid] = 100.0;
	return 1;
}
#if defined _ALS_OnPlayerSpawn
		#undef OnPlayerSpawn
	#else
		#define _ALS_OnPlayerSpawn
	#endif
	#define OnPlayerSpawn AC_OnPlayerSpawn
	forward OnPlayerSpawn(playerid);

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
	    if(strcmp(animlib, "SWIM", true) == NULL && strcmp(animname, "SWIM_crawl", true) == NULL)
	    {
   	 		printf("HAC: %s uses cheat. (Fly Cheat)", GetName(playerid));
	        SetTimerEx("timerfly", 1000, false, "is", playerid, "0x982");
	    }
	}
	return 1;
}

forward OnPlayerInvisibleHack(playerid);
public OnPlayerInvisibleHack(playerid)
{
	if(PlayerSpawned[playerid] == true)
	{
		if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING && Invis[playerid] == false)
		{
			printf("HAC: %s uses cheat. (Invisible Cheat)", GetName(playerid));
			SetTimerEx("timerinvs", 1000, false, "is", playerid, "0x541");
		}
	}
	return 1;
}

forward OnPlayerTeleportHack(playerid);
public OnPlayerTeleportHack(playerid)
{
	if(PlayerSpawned[playerid] == true)
	{
		if(GetPlayerDistanceFromPoint(playerid, acX[playerid], acY[playerid], acZ[playerid]) > 100.0)
		{
			printf("HAC: %s uses cheat. (Teleport Cheat)", GetName(playerid));
			SetTimerEx("timertp", 1000, false, "is", playerid, "0x433");
		}
        GetPlayerPos(playerid, acX[playerid], acY[playerid], acZ[playerid]);

        new Float:X, Float:Y, Float:Z;
        GetPlayerPos(playerid, X, Y, Z);

        if(!IsPlayerInRangeOfPoint(playerid, 5.0, X, Y, Z))
		{
			printf("HAC: %s uses cheat. (Nop Position)", GetName(playerid));
			SetTimerEx("timernop", 1000, false, "is", playerid, "0x241");
		}
	}
	return 1;
}

forward OnPlayerHealthHack(playerid);
public OnPlayerHealthHack(playerid)
{
    new Float:hp;
    GetPlayerHealth(playerid, hp);
	if(HeaA[playerid] < hp)
	{
		printf("HAC: %s uses cheat. (Health Cheat)", GetName(playerid));
		SetTimerEx("timerhp", 1000, false, "is", playerid, "0x412");
	}
	else
	{
		HeaA[playerid] = hp;
	}
	return 1;
}

forward OnPlayerWeaponHack(playerid);
public OnPlayerWeaponHack(playerid)
{
	for(new i = 0; i != 47; i++)
	{
		if(wInfo[playerid][i] != GetPlayerAmmo(playerid))
	 	{
			printf("HAC: %s uses cheat. (Weapon Cheat)", GetName(playerid));
			SetTimerEx("timerweapn", 1000, false, "is", playerid, "0x618");
		}
	}
	return 1;
}

forward OnPlayerMoneyHack(playerid);
public OnPlayerMoneyHack(playerid)
{
    if(MonA[playerid] != GetPlayerMoney(playerid))
    {
        printf("HAC: %s uses cheat. (Money Cheat)", GetName(playerid));
		SetTimerEx("timermoney", 1000, false, "is", playerid, "0x487");
	}
    MonA[playerid] = GetPlayerMoney(playerid);
	return 1;
}

forward OnPlayerArmourHack(playerid);
public OnPlayerArmourHack(playerid)
{
	new Float:arm;
	GetPlayerArmour(playerid, arm);
    if(ArmA[playerid] != arm)
	{
		printf("HAC: %s uses cheat. (Armour Cheat)", GetName(playerid));
		SetTimerEx("timerarm", 1000, false, "is", playerid, "0x466");
	}
    GetPlayerArmour(playerid, ArmA[playerid]);
	return 1;
}

forward OnPlayerHigPing(playerid);
public OnPlayerHigPing(playerid)
{
	if(PlayerSpawned[playerid] == false) return 0;
	if(GetPlayerPing(playerid) > MaximPing)
    {
		printf("HAC: At %s has big ping. (0x721)", GetName(playerid));
		SetTimerEx("timerpng", 1000, false, "is", playerid, "0x721");
	}
	return 1;
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
#if defined _ALS_SetPlayerPosAC
    #undef    SetPlayerPosAC
#else
    #define    _ALS_SetPlayerPosAC
#endif

stock SetPlayerHealthAC(playerid, health)
{
	if(IsPlayerConnected(playerid))
	{
		HeaA[playerid] = health;
		SetPlayerHealth(playerid, health);
	}
	return 1;
}
#if defined _ALS_SetPlayerHealthAC
    #undef    SetPlayerHealthAC
#else
    #define    _ALS_SetPlayerHealthAC
#endif

stock TogglePlayerSpectatingAC(playerid, toggle)
{
	if(toggle == 1) Invisible[playerid] = true;
	else if(toggle == 0) Invisible[playerid] = false;
	return 1;
}
#if defined _ALS_TogglePlayerSpectatingAC
    #undef    TogglePlayerSpectatingAC
#else
    #define    _ALS_TogglePlayerSpectatingAC
#endif


stock SetPlayerArmourAC(playerid, armour)
{
	ArmA[playerid] = armour;
	ResetPlayerArmour(playerid);
	SetPlayerArmour(playerid, armour);
	return 1;
}
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
#if defined _ALS_SetPlayerMoneyAC
    #undef    SetPlayerMoneyAC
#else
    #define    _ALS_SetPlayerMoneyAC
#endif

stock SetMaxPing(ping)
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

stock GetName(playerid)
{
	new name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	return name;
}

forward timerpng(playerid, code[]);
public timerpng(playerid, code[])
{
	CallRemoteFunction("OnPlayerCheat", "is", playerid, code);
	return 1;
}

forward timermoney(playerid, code[]);
public timermoney(playerid, code[])
{
	CallRemoteFunction("OnPlayerCheat", "is", playerid, code);
	return 1;
}

forward timerhp(playerid, code[]);
public timerhp(playerid, code[])
{
	CallRemoteFunction("OnPlayerCheat", "is", playerid, code);
	return 1;
}

forward timerinvs(playerid, code[]);
public timerinvs(playerid, code[])
{
	CallRemoteFunction("OnPlayerCheat", "is", playerid, code);
	return 1;
}

forward timerarm(playerid, code[]);
public timerarm(playerid, code[])
{
	CallRemoteFunction("OnPlayerCheat", "is", playerid, code);
	return 1;
}

forward timertp(playerid, code[]);
public timertp(playerid, code[])
{
	CallRemoteFunction("OnPlayerCheat", "is", playerid, code);
	return 1;
}

forward timernop(playerid, code[]);
public timernop(playerid, code[])
{
	CallRemoteFunction("OnPlayerCheat", "is", playerid, code);
	return 1;
}

forward timerfly(playerid, code[]);
public timerfly(playerid, code[])
{
	CallRemoteFunction("OnPlayerCheat", "is", playerid, code);
	return 1;
}

forward timerweapn(playerid, code[]);
public timerweapn(playerid, code[])
{
	CallRemoteFunction("OnPlayerCheat", "is", playerid, code);
	return 1;
}

forward OnSpeedVehicle(playerid);
public OnSpeedVehicle(playerid)
{
	if(IsPlayerConnected(playerid))
	{
	    if(!IsPlayerInAnyVehicle(playerid)) return 0;
	    SpeedLimit(playerid);
	}
	return 1;
}

stock SpeedLimit(playerid)
{
	new carid = GetPlayerVehicleID(carid);
    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 400 && GetVehicleSpeed(carid) > 100) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 401 && GetVehicleSpeed(carid) > 100) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 402 && GetVehicleSpeed(carid) > 110) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 403 && GetVehicleSpeed(carid) > 75) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 404 && GetVehicleSpeed(carid) > 90) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 405 && GetVehicleSpeed(carid) > 105) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 409 && GetVehicleSpeed(carid) > 105) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 410 && GetVehicleSpeed(carid) > 90) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 411 && GetVehicleSpeed(carid) > 130) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 412 && GetVehicleSpeed(carid) > 105) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 413 && GetVehicleSpeed(carid) > 90) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 415 && GetVehicleSpeed(carid) > 115) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 416 && GetVehicleSpeed(carid) > 100) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 418 && GetVehicleSpeed(carid) > 85) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 419 && GetVehicleSpeed(carid) > 100) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 420 && GetVehicleSpeed(carid) > 95) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 421 && GetVehicleSpeed(carid) > 100) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 422 && GetVehicleSpeed(carid) > 95) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 426 && GetVehicleSpeed(carid) > 110) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 427 && GetVehicleSpeed(carid) > 105) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 428 && GetVehicleSpeed(carid) > 105) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 429 && GetVehicleSpeed(carid) > 120) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 433 && GetVehicleSpeed(carid) > 90) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 434 && GetVehicleSpeed(carid) > 105) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 436 && GetVehicleSpeed(carid) > 100) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 439 && GetVehicleSpeed(carid) > 105) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 444 && GetVehicleSpeed(carid) > 90) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 445 && GetVehicleSpeed(carid) > 105) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 451 && GetVehicleSpeed(carid) > 115) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 459 && GetVehicleSpeed(carid) > 100) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 461 && GetVehicleSpeed(carid) > 125) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 463 && GetVehicleSpeed(carid) > 125) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 466 && GetVehicleSpeed(carid) > 95) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 467 && GetVehicleSpeed(carid) > 95) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 468 && GetVehicleSpeed(carid) > 125) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 470 && GetVehicleSpeed(carid) > 100) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 474 && GetVehicleSpeed(carid) > 100) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 475 && GetVehicleSpeed(carid) > 105) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 477 && GetVehicleSpeed(carid) > 115) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 478 && GetVehicleSpeed(carid) > 90) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 479 && GetVehicleSpeed(carid) > 100) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 480 && GetVehicleSpeed(carid) > 110) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 483 && GetVehicleSpeed(carid) > 95) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 489 && GetVehicleSpeed(carid) > 95) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 490 && GetVehicleSpeed(carid) > 100) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 491 && GetVehicleSpeed(carid) > 100) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 492 && GetVehicleSpeed(carid) > 95) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 494 && GetVehicleSpeed(carid) > 125) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 495 && GetVehicleSpeed(carid) > 110) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 496 && GetVehicleSpeed(carid) > 105) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 498 && GetVehicleSpeed(carid) > 85) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 500 && GetVehicleSpeed(carid) > 95) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 502 && GetVehicleSpeed(carid) > 125) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 503 && GetVehicleSpeed(carid) > 125) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 505 && GetVehicleSpeed(carid) > 95) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 506 && GetVehicleSpeed(carid) > 110) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 507 && GetVehicleSpeed(carid) > 105) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 516 && GetVehicleSpeed(carid) > 105) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 517 && GetVehicleSpeed(carid) > 105) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 518 && GetVehicleSpeed(carid) > 105) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 521 && GetVehicleSpeed(carid) > 130) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 522 && GetVehicleSpeed(carid) > 130) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 523 && GetVehicleSpeed(carid) > 125) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 525 && GetVehicleSpeed(carid) > 100) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 526 && GetVehicleSpeed(carid) > 100) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 527 && GetVehicleSpeed(carid) > 100) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 528 && GetVehicleSpeed(carid) > 110) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 529 && GetVehicleSpeed(carid) > 100) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 531 && GetVehicleSpeed(carid) > 80) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 533 && GetVehicleSpeed(carid) > 105) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 534 && GetVehicleSpeed(carid) > 105) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 535 && GetVehicleSpeed(carid) > 95) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 536 && GetVehicleSpeed(carid) > 110) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 540 && GetVehicleSpeed(carid) > 100) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 541 && GetVehicleSpeed(carid) > 120) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 542 && GetVehicleSpeed(carid) > 105) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 543 && GetVehicleSpeed(carid) > 100) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 545 && GetVehicleSpeed(carid) > 100) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 546 && GetVehicleSpeed(carid) > 100) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 547 && GetVehicleSpeed(carid) > 100) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 549 && GetVehicleSpeed(carid) > 100) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 550 && GetVehicleSpeed(carid) > 100) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 551 && GetVehicleSpeed(carid) > 105) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 554 && GetVehicleSpeed(carid) > 100) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 555 && GetVehicleSpeed(carid) > 95) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 558 && GetVehicleSpeed(carid) > 105) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 559 && GetVehicleSpeed(carid) > 110) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 560 && GetVehicleSpeed(carid) > 105) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 561 && GetVehicleSpeed(carid) > 100) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562 && GetVehicleSpeed(carid) > 110) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 565 && GetVehicleSpeed(carid) > 105) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 566 && GetVehicleSpeed(carid) > 105) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 567 && GetVehicleSpeed(carid) > 110) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 568 && GetVehicleSpeed(carid) > 95) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 571 && GetVehicleSpeed(carid) > 75) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 575 && GetVehicleSpeed(carid) > 105) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 576 && GetVehicleSpeed(carid) > 100) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 579 && GetVehicleSpeed(carid) > 100) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 580 && GetVehicleSpeed(carid) > 100) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 581 && GetVehicleSpeed(carid) > 125) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 582 && GetVehicleSpeed(carid) > 95) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 586 && GetVehicleSpeed(carid) > 125) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 587 && GetVehicleSpeed(carid) > 105) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 589 && GetVehicleSpeed(carid) > 105) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 596 && GetVehicleSpeed(carid) > 110) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 597 && GetVehicleSpeed(carid) > 110) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 598 && GetVehicleSpeed(carid) > 110) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 599 && GetVehicleSpeed(carid) > 100) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 600 && GetVehicleSpeed(carid) > 100) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 601 && GetVehicleSpeed(carid) > 90) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 602 && GetVehicleSpeed(carid) > 110) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 603 && GetVehicleSpeed(carid) > 110) CallRemoteFunction("PlayerOnCheat", "is", playerid, "0x315");
}

stock GetVehicleSpeed(vehicleid)
{
        if(vehicleid != INVALID_VEHICLE_ID)
        {
                new Float:Pos[3],Float:VS ;
                GetVehicleVelocity(vehicleid, Pos[0], Pos[1], Pos[2]);
                VS = floatsqroot(Pos[0]*Pos[0] + Pos[1]*Pos[1] + Pos[2]*Pos[2])*200;
                return floatround(VS,floatround_round);
        }
        return INVALID_VEHICLE_ID;
}
