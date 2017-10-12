#pragma once

#include "stdafx.h"

const int GAMEFPS = 60;

const int VECTOR_STARTNUM = 0;
const int MAP_STARTNUM = 1;

//	파일 경로
#define PATH_BACKGROUND_JPG "res/image/BackGround.jpg"
#define PATH_CLOSENORMAL_PNG "res/image/CloseNormal.png"
#define PATH_CLOSESELECTED_PNG "res/image/CloseSelected.png"
#define PATH_PLAYER_PNG "res/image/Player.png"
#define PATH_TARGET_PNG "res/image/Target.png"
#define PATH_MISSILE_PNG "res/image/Missile.png"
#define PATH_BOSS_PNG "res/image/Boss.png"

#define PATH_SELECT_PENGUIN_PNG "res/image/Select_Penguin.png"

#define PATH_SYSTEM_XML "res/xml/System.xml"
#define PATH_CHARACTER_XML "res/xml/Character.xml"
#define PATH_MONSTER_XML "res/xml/Monster.xml"
#define PATH_SKILL_XML "res/xml/Skill.xml"
#define PATH_BULLET_XML "res/xml/Bullet.xml"
#define PATH_STAGE_XML "res/xml/Stage.xml"
#define PATH_SELECTSCENE_XML "res/xml/SelectScene.xml"


#define MONSTER_SCRIPT_FILENAME "res/lua/Monster.lua"
#define BULLET_SCRIPT_FILENAME "res/lua/Bullet.lua"

//Lua 함수명
#define LUA_MONSTER_FUNCTION "MonsterSchedule_%d"
#define LUA_BULLET_FUNCTION "BulletSchedule_%d"

//	각각의 scene 이름 정의
enum StageSceneType 
{
	SC_STOP = 0,
	SC_PAUSE = 1,
	SC_PROGRESS = 2,
	SC_MIDBOSS = 3,
	SC_APPEARBOSS = 4,
	SC_BOSS = 5,
	SC_CLEAR = 6,
	SC_CONTINUE = 7,
	SC_GAMEOVER = 8,
	SC_END
};

// 우선순위

#define ZORDER_UI			20000

#define ZORDER_LAYER		11000
#define ZORDER_CHARACTER	12000
#define ZORDER_MONSTER		12000
#define ZORDER_MISSILE		11800
#define ZORDER_ITEM			11500

#define ZORDER_BG			10000