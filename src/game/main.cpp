#include "stdafx.h"

#include "Working.h"
#include "Const.h"
#include "UtilFunctions.h"
#include "main.h"
#include "Classes/AppDelegate.h"
#include "Log.h"
#include "LuaStateManager.h"
#include "Global.h"

USING_NS_CC;

map<CharacterNumber, CharacterData> g_CharData;
map<int, MonsterData> g_MonsterData;
map<string, int> g_MonsterTable;
map<int, BulletData> g_BulletData;
map<int, StageData> g_StageData;
map<int, InterfaceData> g_SelectSceneData;

Character* g_player1Character;

bool loadSelectSceneXML()
{
	try
	{
		TiXmlDocument xmlChar;
		int tmp;		//	temp
		string strtmp;	//	string temp

		//	파일 읽어오기
		if ( ! xmlChar.LoadFile(GETPATH(PATH_SELECTSCENE_XML)))
		{
			throw wstring(L"File Not Found : 'SelectScene.xml'");
		}

		//	XML Node
		TiXmlNode* pRoot = xmlChar.FirstChild("SelectScene");
		TiXmlNode* pNode = pRoot->FirstChild("Interface");

		DEBUG_LOG(L"Scene Loading...");
		while(pNode)
		{
			InterfaceData tmpInterfaceData;
			//	Position X, Y
			THROW_IF(!pNode->FirstChild("Position")->ToElement()->Attribute("X", &tmp), 
				L"Position.X does not exist.");
			THROW_IF(!pNode->FirstChild("Position")->ToElement()->Attribute("Y", &tmp), 
				L"Position.Y does not exist.");
			//	Size Width, Height
			THROW_IF(!pNode->FirstChild("Size")->ToElement()->Attribute("Width", &tmp), 
				L"Size.Width does not exist.");
			THROW_IF(!pNode->FirstChild("Size")->ToElement()->Attribute("Height", &tmp), 
				L"Size.Height does not exist.");
			TiXmlNode* pImageNode = pNode->FirstChild("Image");
			while(pImageNode)
			{
				string tmpName = pImageNode->ToElement()->Attribute("Name");
				string tmpPath = pImageNode->ToElement()->Attribute("Path");

				THROW_IF(!pImageNode->ToElement()->Attribute("Number", &tmp), 
					L"Image.Number does not exist.");
				tmpInterfaceData.ImageNames.insert( make_pair(tmp, tmpName) );
				tmpInterfaceData.ImagePaths.insert( make_pair(tmp, tmpPath) );
				pImageNode = pImageNode->NextSibling("Image");
			}
			//	다음 노드
			pNode = pNode->NextSibling("Interface");
		}
		xmlChar.Clear();
		DEBUG_LOG(L"Load Complete!");
		return true;
	}
	catch (const wstring& ErrorMessage)
	{
		FATAL_LOG(L"Failed to Load : %s. %s", A2U(PATH_SELECTSCENE_XML).c_str(), 
			ErrorMessage.c_str());
		return false;
	}
}

bool loadMonsterXML()
{
	try
	{
		TiXmlDocument xmlChar;
		int tmp;		//	temp
		string strtmp;	//	string temp

		//	파일 읽어오기
		if ( ! xmlChar.LoadFile(GETPATH(PATH_MONSTER_XML)) )
		{
			throw wstring(L"File Not Found : 'Monster.xml'");
		}

		//	XML Node
		TiXmlNode* pRoot = xmlChar.FirstChild("MonsterData");
		TiXmlNode* pNode = pRoot->FirstChild("Monster");

		DEBUG_LOG(L"Monster Loading...");
		while(pNode)
		{
			MonsterData tmpMonsterData;

			//	이름
			tmpMonsterData.Name = pNode->ToElement()->Attribute("Name");
			//	사이즈
			THROW_IF(!pNode->FirstChild("Size")->ToElement()->Attribute("Width", &tmp), 
				L"Size.Width does not exist.");
			tmpMonsterData.Size.width = (float)tmp;
			THROW_IF(!pNode->FirstChild("Size")->ToElement()->Attribute("Height", &tmp), 
				L"Size.Height does not exist.");
			tmpMonsterData.Size.height = (float)tmp;
			//	이동속도
			THROW_IF(!pNode->FirstChild("MoveSpeed")->ToElement()->Attribute("Value", 
				&tmp), L"MoveSpeed.Value does not exist.");
			tmpMonsterData.MoveSpeed = tmp;
			//	공격정보
			THROW_IF(!pNode->FirstChild("AttackRange")->ToElement()->Attribute("Value", &tmp),
				L"AttackRange.Value does not exist.");
			tmpMonsterData.AttackRange = tmp;
			THROW_IF(!pNode->FirstChild("BulletSpeed")->ToElement()->Attribute("Value", &tmp),
				L"BulletSpeed.Value does not exist.");
			tmpMonsterData.BulletSpeed = tmp;
			//	라이프
			THROW_IF(!pNode->FirstChild("Life")->ToElement()->Attribute("Begin",
				&tmp), L"Life.Begin does not exist.");
			tmpMonsterData.Life = tmp;
			//	최대 라이프
			THROW_IF(!pNode->FirstChild("Life")->ToElement()->Attribute("Max",
				&tmp), L"Life.Max does not exist.");
			tmpMonsterData.MaxLife = tmp;
			//	마나
			THROW_IF(!pNode->FirstChild("Mana")->ToElement()->Attribute("Begin",
				&tmp), L"Mana.Begin does not exist.");
			tmpMonsterData.Mana = tmp;
			//	최대 마나
			THROW_IF(!pNode->FirstChild("Mana")->ToElement()->Attribute("Max",
				&tmp), L"Mana.Max does not exist.");
			tmpMonsterData.MaxMana = tmp;

			TiXmlNode* pNode_ImagePath = pNode->FirstChild("StandingImages")->FirstChild("Image");
			vector<ImageSpriteInfo> tmpStandingImage;
			while( pNode_ImagePath )
			{
				ImageSpriteInfo infotmp;
				infotmp.Path = pNode_ImagePath->ToElement()->Attribute("File");
				THROW_IF(!pNode_ImagePath->ToElement()->Attribute("Number", &tmp), 
					L"StandingImages->Image.Number does not exist.");
				infotmp.Index = tmp;
				THROW_IF(!pNode_ImagePath->ToElement()->Attribute("Frame", &tmp), 
					L"StandingImages->Image.Frame does not exist.");
				infotmp.Frame = tmp;
				tmpStandingImage.push_back(infotmp);
				pNode_ImagePath = pNode_ImagePath->NextSibling("Image");
				
			}
			tmpMonsterData.Images.insert(make_pair(MS_STAND, tmpStandingImage));

			pNode_ImagePath = pNode->FirstChild("MovingImages")->FirstChild("Moving");
			for (int k=0; k<4; ++k)
			{
				strtmp = pNode_ImagePath->ToElement()->Attribute("State");
				if( strtmp == string("Up") )
				{
					vector<ImageSpriteInfo> tmpMovingImage;
					TiXmlNode* tmpPath = pNode_ImagePath->FirstChild("Image");
					while( tmpPath )
					{
						ImageSpriteInfo infotmp;
						infotmp.Path = tmpPath->ToElement()->Attribute("File");
						THROW_IF(!tmpPath->ToElement()->Attribute("Number", &tmp), 
							L"MovingImages->Image.Number does not exist.");
						infotmp.Index = tmp;
						THROW_IF(!tmpPath->ToElement()->Attribute("Frame", &tmp), 
							L"MovingImages->Image.Frame does not exist.");
						infotmp.Frame = tmp;
						tmpMovingImage.push_back(infotmp);
						tmpPath = tmpPath->NextSibling("Image");
					}
					tmpMonsterData.Images.insert(make_pair(MS_UP, tmpMovingImage));
				}
				else if( strtmp == string("Down") )
				{
					vector<ImageSpriteInfo> tmpMovingImage;
					TiXmlNode* tmpPath = pNode_ImagePath->FirstChild("Image");
					while( tmpPath )
					{
						ImageSpriteInfo infotmp;
						infotmp.Path = tmpPath->ToElement()->Attribute("File");
						THROW_IF(!tmpPath->ToElement()->Attribute("Number", &tmp), 
							L"MovingImages->Image.Number does not exist.");
						infotmp.Index = tmp;
						THROW_IF(!tmpPath->ToElement()->Attribute("Frame", &tmp), 
							L"MovingImages->Image.Frame does not exist.");
						infotmp.Frame = tmp;
						tmpMovingImage.push_back(infotmp);
						tmpPath = tmpPath->NextSibling("Image");
					}
					tmpMonsterData.Images.insert(make_pair(MS_DOWN, tmpMovingImage));
				}
				else if( strtmp == string("Left") )
				{
					vector<ImageSpriteInfo> tmpMovingImage;
					TiXmlNode* tmpPath = pNode_ImagePath->FirstChild("Image");
					while( tmpPath )
					{
						ImageSpriteInfo infotmp;
						infotmp.Path = tmpPath->ToElement()->Attribute("File");
						THROW_IF(!tmpPath->ToElement()->Attribute("Number", &tmp), 
							L"MovingImages->Image.Number does not exist.");
						infotmp.Index = tmp;
						THROW_IF(!tmpPath->ToElement()->Attribute("Frame", &tmp), 
							L"MovingImages->Image.Frame does not exist.");
						infotmp.Frame = tmp;
						tmpMovingImage.push_back(infotmp);
						tmpPath = tmpPath->NextSibling("Image");
					}
					tmpMonsterData.Images.insert(make_pair(MS_LEFT, tmpMovingImage));
				}
				else if( strtmp == string("Right") )
				{
					vector<ImageSpriteInfo> tmpMovingImage;
					TiXmlNode* tmpPath = pNode_ImagePath->FirstChild("Image");
					while( tmpPath )
					{
						ImageSpriteInfo infotmp;
						infotmp.Path = tmpPath->ToElement()->Attribute("File");
						THROW_IF(!tmpPath->ToElement()->Attribute("Number", &tmp), 
							L"MovingImages->Image.Number does not exist.");
						infotmp.Index = tmp;
						THROW_IF(!tmpPath->ToElement()->Attribute("Frame", &tmp), 
							L"MovingImages->Image.Frame does not exist.");
						infotmp.Frame = tmp;
						tmpMovingImage.push_back(infotmp);
						tmpPath = tmpPath->NextSibling("Image");
					}
					tmpMonsterData.Images.insert(make_pair(MS_RIGHT, tmpMovingImage));
				}
				else
				{
					throw wstring(L"MovingImages->Moving.State value is invalid.");
				}
				pNode_ImagePath = pNode_ImagePath->NextSibling();
			}
			//	원거리 공격 정보
			TiXmlNode* pNode_Attack = pNode->FirstChild("RangeAttack")->FirstChild("Attack");
			while( pNode_Attack )
			{
				RangeAttackStruct tmpRangeAttack;
				THROW_IF(!pNode_Attack->FirstChild("Bullet")->ToElement()->Attribute("Number", &tmp), 
					L"RangeAttack->Bullet.Number does not exist.");
				tmpRangeAttack.BulletNumber = tmp;
				THROW_IF(!pNode_Attack->FirstChild("Damage")->ToElement()->Attribute("Value", &tmp), 
					L"RangeAttack->Damage.Value does not exist.");
				tmpRangeAttack.Damage = tmp;

				TiXmlNode* pNode_Path = pNode_Attack->FirstChild("Images")->FirstChild("Image");
				while( pNode_Path )
				{
					ImageSpriteInfo infotmp;
					infotmp.Path = pNode_Path->ToElement()->Attribute("File");
					THROW_IF(!pNode_Path->ToElement()->Attribute("Number", &tmp), 
						L"RangeAttack->Attack->Images->Image.Number does not exist.");
					infotmp.Index = tmp;
					THROW_IF(!pNode_Path->ToElement()->Attribute("Frame", &tmp), 
						L"RangeAttack->Attack->Images->Image.Frame does not exist.");
					infotmp.Frame = tmp;
					tmpRangeAttack.ImagePath.push_back(infotmp);
					pNode_Path = pNode_Path->NextSibling("Image");
				}
				THROW_IF(!pNode_Attack->ToElement()->Attribute("Level", &tmp), 
					L"RangeAttack->Attack.Level does not exist.");
				tmpMonsterData.RangeAttack.insert( make_pair(tmp, tmpRangeAttack) );

				pNode_Attack = pNode_Attack->NextSibling("Attack");
			}
			//	로드 완료 후 추가
			pNode->ToElement()->Attribute("Number", &tmp);
			g_MonsterData.insert( make_pair(tmp, tmpMonsterData) );
			g_MonsterTable.insert( make_pair(tmpMonsterData.Name, tmp) );
			//	다음 몬스터
			pNode = pNode->NextSibling("Monster");
		}
		xmlChar.Clear();
		DEBUG_LOG(L"Load Complete!");
		return true;
	}
	catch (const wstring& ErrorMessage)
	{
		FATAL_LOG(L"Failed to Load : %s. %s", A2U(PATH_MONSTER_XML).c_str(), 
			ErrorMessage.c_str());
		return false;
	}
}
bool loadBulletXML()
{
	try
	{
		TiXmlDocument xmlChar;
		int tmp;		//	temp
		string strtmp;	//	string temp

		//	파일 읽어오기
		if ( ! xmlChar.LoadFile(GETPATH(PATH_BULLET_XML)) )
		{
			throw wstring(L"File Not Found : Bullet.xml");
		}

		//	XML Node
		TiXmlNode* pRoot = xmlChar.FirstChild("BulletData");
		TiXmlNode* pNode = pRoot->FirstChild("Bullet");

		DEBUG_LOG(L"Bullet Loading...");
		while(pNode)
		{
			BulletData tmpBulletData;

			//	이름
			tmpBulletData.Name = pNode->ToElement()->Attribute("Name");
			//	사이즈
			THROW_IF(!pNode->FirstChild("Size")->ToElement()->Attribute("Width", &tmp), 
				L"Size.Width does not exist.");
			tmpBulletData.Size.width = (float)tmp;
			THROW_IF(!pNode->FirstChild("Size")->ToElement()->Attribute("Height", &tmp), 
				L"Size.Height does not exist.");
			tmpBulletData.Size.height = (float)tmp;
			//	이동속도
			THROW_IF(!pNode->FirstChild("MoveSpeed")->ToElement()->Attribute("Value", 
				&tmp), L"MoveSpeed.Value does not exist.");
			tmpBulletData.MoveSpeed = tmp;
			//	대미지
			THROW_IF(!pNode->FirstChild("Damage")->ToElement()->Attribute("Value", 
				&tmp), L"Damage.Value does not exist.");
			tmpBulletData.Damage = tmp;
			//	대미지속성
			tmpBulletData.DamageType = pNode->FirstChild("DamageType")->ToElement()->Attribute("Name");
			//	피어싱 레벨
			THROW_IF(!pNode->FirstChild("Piercing")->ToElement()->Attribute("Level", &tmp),
				L"Piercing.Level does not exist.");
			tmpBulletData.PiercingLevel = tmp;

			TiXmlNode* pNode_ImagePath = pNode->FirstChild("Image");
			while( pNode_ImagePath )
			{
				ImageSpriteInfo infotmp;
				infotmp.Path = pNode_ImagePath->ToElement()->Attribute("File");
				THROW_IF(!pNode_ImagePath->ToElement()->Attribute("Number", &tmp), 
					L"StandingImages->Image.Number does not exist.");
				infotmp.Index = tmp;
				THROW_IF(!pNode_ImagePath->ToElement()->Attribute("Frame", &tmp), 
					L"StandingImages->Image.Frame does not exist.");
				infotmp.Frame = tmp;
				tmpBulletData.Images.push_back(infotmp);
				pNode_ImagePath = pNode_ImagePath->NextSibling("Image");
			}
			pNode->ToElement()->Attribute("Number", &tmp);
			g_BulletData.insert( make_pair(tmp, tmpBulletData) );
			//	다음 총알
			pNode = pNode->NextSibling("Bullet");
		}
		xmlChar.Clear();
		DEBUG_LOG(L"Load Complete!");
		return true;
	}
	catch (const wstring& ErrorMessage)
	{
		FATAL_LOG(L"Failed to Load : %s. %s", A2U(PATH_BULLET_XML).c_str(), 
			ErrorMessage.c_str());
		return false;
	}
}
bool loadStageXML()
{
	try
	{
		TiXmlDocument xmlChar;
		int tmp;		//	temp
		string strtmp;	//	string temp

		//	파일 읽어오기
		if ( ! xmlChar.LoadFile(GETPATH(PATH_STAGE_XML)) )
		{
			throw wstring(L"File Not Found : Stage.xml");
		}

		//	XML Node
		TiXmlNode* pRoot = xmlChar.FirstChild("Stages");
		TiXmlNode* pNode = pRoot->FirstChild("Stage");

		DEBUG_LOG(L"Stage Loading...");
		while(pNode)
		{
			StageData tmpStageData;

			//	이름
			tmpStageData.Name = pNode->ToElement()->Attribute("Name");
			tmpStageData.BackgroundImagePath = 
				pNode->FirstChild("BackgroundImage")->ToElement()->Attribute("Path");
			//	화면 길이
			THROW_IF(!pNode->FirstChild("Length")->ToElement()->Attribute("Value", 
				&tmp), L"Length.Value does not exist.");
			tmpStageData.Length = tmp;
			//	화면 이동속도
			THROW_IF(!pNode->FirstChild("MoveSpeed")->ToElement()->Attribute("Value", 
				&tmp), L"MoveSpeed.Value does not exist.");
			tmpStageData.MoveSpeed = tmp;

			//	몬스터 로드
			TiXmlNode* pNode_Monsters = 
				pNode->FirstChild("Monsters")->FirstChild("Monster");
			while( pNode_Monsters )
			{
				StageMonsterData tmpMonsters;
				THROW_IF(!pNode_Monsters->ToElement()->Attribute("PositionX", &tmp), 
					L"Monsters->Monster.PositionX does not exist.");
				tmpMonsters.Position.x = tmp;
				THROW_IF(!pNode_Monsters->ToElement()->Attribute("PositionY", &tmp), 
					L"Monsters->Monster.PositionX does not exist.");
				tmpMonsters.Position.y = tmp;
				THROW_IF(!pNode_Monsters->ToElement()->Attribute("MonsterNumber", &tmp), 
					L"Monsters->Monster.MonsterNumber does not exist.");
				tmpMonsters.MonsterNumber = tmp;
				THROW_IF(!pNode_Monsters->ToElement()->Attribute("Number", &tmp), 
					L"Monsters->Monster.Number does not exist.");
				tmpStageData.StageMonsters.insert(make_pair(tmp, tmpMonsters));
				//	다음으로 이동
				pNode_Monsters = pNode_Monsters->NextSibling("Monster");
			}
			pNode->ToElement()->Attribute("Number", &tmp);
			g_StageData.insert( make_pair(tmp, tmpStageData) );
			//	다음 총알
			pNode = pNode->NextSibling("Stage");
		}
		xmlChar.Clear();
		DEBUG_LOG(L"Load Complete!");
		return true;
	}
	catch (const wstring& ErrorMessage)
	{
		FATAL_LOG(L"Failed to Load : %s. %s", A2U(PATH_STAGE_XML).c_str(), 
			ErrorMessage.c_str());
		return false;
	}
}
bool loadCharacterXML()
{
	try
	{
		TiXmlDocument xmlChar;
		int tmp;		//	temp
		string strtmp;	//	string temp

		//	파일 읽어오기
		if ( ! xmlChar.LoadFile(GETPATH(PATH_CHARACTER_XML)) )
		{
			throw wstring(L"File Not Found : 'Character.xml'");
		}

		//	XML Node
		TiXmlNode* pRoot = xmlChar.FirstChild("CharacterData");
		TiXmlNode* pNode = pRoot->FirstChild("Character");

		DEBUG_LOG(L"Character Loading...");
		while (pNode)
		{
			CharacterData tmpCharData;

			//	캐릭터 이름
			tmpCharData.Name = pNode->ToElement()->Attribute("Name");
			//	캐릭터 사이즈
			THROW_IF(!pNode->FirstChild("Size")->ToElement()->Attribute("Width", &tmp), 
				L"Size.Width does not exist.");
			tmpCharData.Size.width = (float)tmp;
			THROW_IF(!pNode->FirstChild("Size")->ToElement()->Attribute("Height", &tmp), 
				L"Size.Height does not exist.");
			tmpCharData.Size.height = (float)tmp;
			//	캐릭터 이동속도
			THROW_IF(!pNode->FirstChild("MoveSpeed")->ToElement()->Attribute("Value", 
				&tmpCharData.MoveSpeed), L"MoveSpeed.Value does not exist.");
			//	캐릭터 공격정보
			THROW_IF(!pNode->FirstChild("AttackRange")->ToElement()->Attribute("Value", &tmp),
				 L"AttackRange.Value does not exist.");
			tmpCharData.AttackRange = tmp;
			THROW_IF(!pNode->FirstChild("BulletSpeed")->ToElement()->Attribute("Value", &tmp),
				L"BulletSpeed.Value does not exist.");
			tmpCharData.BulletSpeed = tmp;
			//	미사일 초당 발사수
			THROW_IF(!pNode->FirstChild("RangeAttack")->ToElement()->Attribute("ShootPerSec", 
				&tmp), L"RangeAttack.ShootPerSec does not exist.");
			tmpCharData.ShootPerSec = tmp;
			//	라이프
			THROW_IF(!pNode->FirstChild("Life")->ToElement()->Attribute("Begin",
				&tmp), L"Life.Begin does not exist.");
			tmpCharData.Life = tmp;
			//	최대 라이프
			THROW_IF(!pNode->FirstChild("Life")->ToElement()->Attribute("Max",
				&tmp), L"Life.Max does not exist.");
			tmpCharData.MaxLife = tmp;
			//	마나
			THROW_IF(!pNode->FirstChild("Mana")->ToElement()->Attribute("Begin",
				&tmp), L"Mana.Begin does not exist.");
			tmpCharData.Mana = tmp;
			//	최대 마나
			THROW_IF(!pNode->FirstChild("Mana")->ToElement()->Attribute("Max",
				&tmp), L"Mana.Max does not exist.");
			tmpCharData.MaxMana = tmp;

			TiXmlNode* pNode_ImagePath = pNode->FirstChild("StandingImages")->FirstChild("Image");
			vector<ImageSpriteInfo> tmpStandingImage;
			while( pNode_ImagePath )
			{
				ImageSpriteInfo infotmp;
				infotmp.Path = pNode_ImagePath->ToElement()->Attribute("File");
				THROW_IF(!pNode_ImagePath->ToElement()->Attribute("Number", &tmp), 
					L"StandingImages->Image.Number does not exist.");
				infotmp.Index = tmp;
				THROW_IF(!pNode_ImagePath->ToElement()->Attribute("Frame", &tmp), 
					L"MovingImages->Image.Frame does not exist.");
				infotmp.Frame = tmp;
				tmpStandingImage.push_back(infotmp);
				pNode_ImagePath = pNode_ImagePath->NextSibling("Image");
			}
			tmpCharData.Images.insert(make_pair(CS_STAND, tmpStandingImage));

			pNode_ImagePath = pNode->FirstChild("MovingImages")->FirstChild("Moving");
			for (int k=0; k<4; ++k)
			{
				strtmp = pNode_ImagePath->ToElement()->Attribute("State");
				if( strtmp == string("Up") )
				{
					vector<ImageSpriteInfo> tmpMovingImage;
					TiXmlNode* tmpPath = pNode_ImagePath->FirstChild("Image");
					while( tmpPath )
					{
						ImageSpriteInfo infotmp;
						infotmp.Path = tmpPath->ToElement()->Attribute("File");
						THROW_IF(!tmpPath->ToElement()->Attribute("Number", &tmp), 
							L"MovingImages->Image.Number does not exist.");
						infotmp.Index = tmp;
						THROW_IF(!tmpPath->ToElement()->Attribute("Frame", &tmp), 
							L"MovingImages->Image.Frame does not exist.");
						infotmp.Frame = tmp;
						tmpMovingImage.push_back(infotmp);
						tmpPath = tmpPath->NextSibling("Image");
					}
					tmpCharData.Images.insert(make_pair(CS_UP, tmpMovingImage));
				}
				else if( strtmp == string("Down") )
				{
					vector<ImageSpriteInfo> tmpMovingImage;
					TiXmlNode* tmpPath = pNode_ImagePath->FirstChild("Image");
					while( tmpPath )
					{
						ImageSpriteInfo infotmp;
						infotmp.Path = tmpPath->ToElement()->Attribute("File");
						THROW_IF(!tmpPath->ToElement()->Attribute("Number", &tmp), 
							L"MovingImages->Image.Number does not exist.");
						infotmp.Index = tmp;
						THROW_IF(!tmpPath->ToElement()->Attribute("Frame", &tmp), 
							L"MovingImages->Image.Frame does not exist.");
						infotmp.Frame = tmp;
						tmpMovingImage.push_back(infotmp);
						tmpPath = tmpPath->NextSibling("Image");
					}
					tmpCharData.Images.insert(make_pair(CS_DOWN, tmpMovingImage));
				}
				else if( strtmp == string("Left") )
				{
					vector<ImageSpriteInfo> tmpMovingImage;
					TiXmlNode* tmpPath = pNode_ImagePath->FirstChild("Image");
					while( tmpPath )
					{
						ImageSpriteInfo infotmp;
						infotmp.Path = tmpPath->ToElement()->Attribute("File");
						THROW_IF(!tmpPath->ToElement()->Attribute("Number", &tmp), 
							L"MovingImages->Image.Number does not exist.");
						infotmp.Index = tmp;
						THROW_IF(!tmpPath->ToElement()->Attribute("Frame", &tmp), 
							L"MovingImages->Image.Frame does not exist.");
						infotmp.Frame = tmp;
						tmpMovingImage.push_back(infotmp);
						tmpPath = tmpPath->NextSibling("Image");
					}
					tmpCharData.Images.insert(make_pair(CS_LEFT, tmpMovingImage));
				}
				else if( strtmp == string("Right") )
				{
					vector<ImageSpriteInfo> tmpMovingImage;
					TiXmlNode* tmpPath = pNode_ImagePath->FirstChild("Image");
					while( tmpPath )
					{
						ImageSpriteInfo infotmp;
						infotmp.Path = tmpPath->ToElement()->Attribute("File");
						THROW_IF(!tmpPath->ToElement()->Attribute("Number", &tmp), 
							L"MovingImages->Image.Number does not exist.");
						infotmp.Index = tmp;
						THROW_IF(!tmpPath->ToElement()->Attribute("Frame", &tmp), 
							L"MovingImages->Image.Frame does not exist.");
						infotmp.Frame = tmp;
						tmpMovingImage.push_back(infotmp);
						tmpPath = tmpPath->NextSibling("Image");
					}
					tmpCharData.Images.insert(make_pair(CS_RIGHT, tmpMovingImage));
				}
				else
				{
					throw wstring(L"MovingImages->Moving.State value is invalid.");
				}
				pNode_ImagePath = pNode_ImagePath->NextSibling();
			}
			//	캐릭터 원거리 공격 정보
			TiXmlNode* pNode_Attack = pNode->FirstChild("RangeAttack")->FirstChild("Attack");
			while( pNode_Attack )
			{
				RangeAttackStruct tmpRangeAttack;
				THROW_IF(!pNode_Attack->FirstChild("Bullet")->ToElement()->Attribute("Number", &tmp), 
					L"RangeAttack->Bullet.Number does not exist.");
				tmpRangeAttack.BulletNumber = tmp;
				THROW_IF(!pNode_Attack->FirstChild("Damage")->ToElement()->Attribute("Value", &tmp), 
					L"RangeAttack->Damage.Value does not exist.");
				tmpRangeAttack.Damage = tmp;

				TiXmlNode* pNode_Path = pNode_Attack->FirstChild("Images")->FirstChild("Image");
				while( pNode_Path )
				{
					ImageSpriteInfo infotmp;
					infotmp.Path = pNode_Path->ToElement()->Attribute("File");
					THROW_IF(!pNode_Path->ToElement()->Attribute("Number", &tmp), 
						L"RangeAttack->Attack->Images->Image.Number does not exist.");
					infotmp.Index = tmp;
					THROW_IF(!pNode_Path->ToElement()->Attribute("Frame", &tmp), 
						L"RangeAttack->Attack->Images->Image.Frame does not exist.");
					infotmp.Frame = tmp;
					tmpRangeAttack.ImagePath.push_back(infotmp);
					pNode_Path = pNode_Path->NextSibling("Image");
				}
				THROW_IF(!pNode_Attack->ToElement()->Attribute("Level", &tmp), 
					L"RangeAttack->Attack.Level does not exist.");
				tmpCharData.RangeAttack.insert( make_pair(tmp, tmpRangeAttack) );

				pNode_Attack = pNode_Attack->NextSibling("Attack");
			}

			pNode->ToElement()->Attribute("Number", &tmp);
			g_CharData.insert( make_pair((CharacterNumber)tmp, tmpCharData) );

			pNode = pNode->NextSibling("Character");
		}
		xmlChar.Clear();
		DEBUG_LOG(L"Load Complete!");
		return true;
	}
	catch (const wstring& ErrorMessage)
	{
		FATAL_LOG(L"Failed to Load : %s. %s", A2U(PATH_CHARACTER_XML).c_str(), 
			ErrorMessage.c_str());
		return false;
	}
}

bool loadXML()
{
	if ( !loadSelectSceneXML() )
	{
		return false;
	}
	if ( !loadCharacterXML() )
	{
		return false;
	}
	if ( !loadMonsterXML() )
	{
		return false;
	}
	if ( !loadBulletXML() )
	{
		return false;
	}
	if ( !loadStageXML() )
	{
		return false;
	}
	return true;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);	

	g_Lua = new LuaStateManager();
	g_Lua->AddLuaGlues();

	if(g_Lua->ReadScriptFile(GETPATH(MONSTER_SCRIPT_FILENAME)) == false)
	{
		ERROR_LOG(L"Monster Script Loading Error");
		return 0;
	}
	if(g_Lua->ReadScriptFile(GETPATH(BULLET_SCRIPT_FILENAME)) == false)
	{
		ERROR_LOG(L"Bullet Script Loading Error");
		return 0;
	}

	DEBUG_LOG(L"Lua Script Loading Success");
	g_Lua->TestLua();

	if( !loadXML() ) {
		FATAL_LOG(L"Failed to Load XML.");
		return 0;
	}
	// create the application instance
    AppDelegate app;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setFrameSize(640, 480);

	g_player1Character = nullptr;
    
	// The resolution of ipad3 is very large. In general, PC's resolution is smaller than it.
    // So we need to invoke 'setFrameZoomFactor'(only valid on desktop(win32, mac, linux)) to make the window smaller.
	eglView->setFrameZoomFactor(1.0f);
    int returnValue = CCApplication::sharedApplication()->run();

	SAFE_DELETE(g_player1Character);

	delete g_Lua;

	return returnValue;
}

