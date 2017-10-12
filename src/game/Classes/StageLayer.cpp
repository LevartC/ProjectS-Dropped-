
#include "stdafx.h"
#include "Global.h"
#include "Const.h"
#include "UtilFunctions.h"
#include "Log.h"
#include "StageLayer.h"


#define AUTO_RELEASE_STL(node) \
do { \
	for( auto it = node.begin(); it != node.end(); ) { \
	CC_SAFE_DELETE(*it); \
	it = node.erase(it); \
	} \
	if( !node.empty() ) { node.clear(); } \
} while (0)

StageLayer::StageLayer(CharacterNumber charNum)
{
	stageStatus = SC_PROGRESS;
	this->charNum = charNum;

	dtMissile = 0.0f;
	dtAddTarget = 0.0f;
}

StageLayer::~StageLayer()
{
	AUTO_RELEASE_STL(_characterBullets);
	AUTO_RELEASE_STL(_monsters);
	AUTO_RELEASE_STL(_stageMonsters);
}

// on "init" you need to initialize your instance
bool StageLayer::init(int stageNumber)
{
    bool ret = false;
    do
    {
        // super init first
        CC_BREAK_IF(! CCLayer::init());

		//	Get window size
		winSize = CCDirector::sharedDirector()->getWinSize();

		this->setTouchEnabled(true);

		//	화면에 플레이어 스프라이트 추가
		this->setPlayerSprite();

		//	이동 스크롤 화면 스케줄 생성
		ret = true;

		Data = &g_StageData.find(stageNumber)->second;

		//	몬스터 출현 정보 받기
		for (int i=MAP_STARTNUM; i<Data->StageMonsters.size(); ++i)
		{
			StageMonsterData *tmp = new StageMonsterData;
			memcpy(tmp, &Data->StageMonsters.find(i)->second, sizeof(StageMonsterData));
			_stageMonsters.push_back(tmp);
		}
	} while (0);

    return ret;
}

void StageLayer::gameLogic(float delayTime, CCPoint bgPos)
{
	/*
	**	이동 처리 순서
	**	캐릭터 행동 -> 아군 행동 -> 캐릭터 애니메이션 -> 적군 행동 ->
	**	아군 미사일 이동 -> 적군 미사일 이동 -> 아군 미사일 판정 -> 적군 미사일 판정
	*/
	//	아군 행동
	keyboardInput(delayTime);
	missileInput(delayTime);

	//	캐릭터 애니메이션
	g_player1Character->doAction(delayTime);

	//	적군 행동
	for (auto it = _monsters.begin(); it != _monsters.end(); ++it)
	{
		(*it)->doAction(delayTime);
	}
	//	몬스터 출현
	for (auto it = _stageMonsters.begin(); it != _stageMonsters.end();)
	{
		if (bgPos.x >= (*it)->Position.x)
		{
			Monster *mop = new Monster(this);
			mop->createSprite( (*it)->MonsterNumber, ccp(0,0) );
			mop->setPosition(winSize.width + mop->getMonsterData()->Size.width/2, (*it)->Position.y);
			mop->setBulletList(&_enemyBullets);
			_monsters.push_back(mop);
			it = _stageMonsters.erase(it);
		}
		else
		{ ++it; }
	}

	//	아군 미사일 이동
	moveAllyBullet(delayTime);

	//	적군 미사일 이동
	moveEnemyBullet(delayTime);

	//	적군 충돌 체크
	enemyCollisionCheck(delayTime);

}

void StageLayer::missileInput(float delayTime)
{
	CharacterStatusType status = CS_STAND;
	if ( GetAsyncKeyState(0x5A) & SHIFTED )	//	0x5A = 'Z'키
	{
		if (dtMissile == -1.0f)
		{
			dtMissile = missileDelay;
			dtMissile -= delayTime;
		}
		dtMissile += delayTime;
		if (dtMissile >= missileDelay)
		{
			dtMissile -= missileDelay;
			Bullet *tmpBullet = new Bullet(this);
			tmpBullet->createSprite(
				g_player1Character->getCurrentRangeStruct()->BulletNumber,
				ccp(g_player1Character->getPosition().x + (g_player1Character->getSize().width * 0.4f), g_player1Character->getPosition().y),
				ccp(winSize.width, g_player1Character->getPosition().y),
				g_player1Character->getCharacterData()->BulletSpeed,
				g_player1Character->getCurrentRangeStruct()->Damage
				);
			_characterBullets.push_back(tmpBullet);
		}
		g_player1Character->setCurrentCharacterStatus(CS_RANGEATTACK);
	}
	else
	{
		dtMissile = -1.0f;
	}
}

void StageLayer::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
	this->removeFromParentAndCleanup(true);
    CCDirector::sharedDirector()->end();
}

void StageLayer::moveAllyBullet(float delayTime)
{
	for( auto it = _characterBullets.begin(); it != _characterBullets.end(); )
	{
		(*it)->doAction(delayTime);
		CCPoint moveDuration = (*it)->getPosition();
		//	화면을 벗어날 경우 삭제
		if (moveDuration.x >= winSize.width + (*it)->getBulletData()->Size.width/2
			|| moveDuration.x <= 0.0f || moveDuration.y <= 0.0f ||
			moveDuration.y >= winSize.height + (*it)->getBulletData()->Size.height/2)
		{
			SAFE_DELETE(*it);
			it = _characterBullets.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void StageLayer::moveEnemyBullet(float delayTime)
{
	for( auto it = _enemyBullets.begin(); it != _enemyBullets.end(); )
	{
		(*it)->doAction(delayTime);
		CCPoint moveDuration = (*it)->getPosition();
		//	화면을 벗어날 경우 삭제
		if (moveDuration.x >= winSize.width + (*it)->getBulletData()->Size.width/2
			|| moveDuration.x <= 0.0f || moveDuration.y <= 0.0f ||
			moveDuration.y >= winSize.height + (*it)->getBulletData()->Size.height/2)
		{
			SAFE_DELETE(*it);
			it = _enemyBullets.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void StageLayer::enemyCollisionCheck(float delayTime)
{
	for( auto bul_it = _characterBullets.begin(); bul_it != _characterBullets.end(); )
	{
		bool collisionFlag = false;

		CCRect bulletRect = CCRectMake(
			(*bul_it)->getPosition().x - ((*bul_it)->getSize().width/2),
			(*bul_it)->getPosition().y - ((*bul_it)->getSize().height/2),
			(*bul_it)->getSize().width,
			(*bul_it)->getSize().height);
		for( auto mop_it = _monsters.begin(); mop_it != _monsters.end(); )
		{
			if( (*mop_it) != nullptr )
			{
				CCRect targetRect = CCRectMake(
					(*mop_it)->getPosition().x - ((*mop_it)->getSize().width/2),
					(*mop_it)->getPosition().y - ((*mop_it)->getSize().height/2),
					(*mop_it)->getSize().width,
					(*mop_it)->getSize().height);
				//	충돌 체크
				if( CCRect::CCRectIntersectsRect(bulletRect, targetRect) )
				{
					if ((*mop_it)->subtractLife((*bul_it)->getDamage()) <= 0.0f )
					{
						SAFE_DELETE(*mop_it);
						mop_it = _monsters.erase(mop_it);
					}
					collisionFlag = true;
					break;
				}
				else
				{
					++mop_it;
				}
			}
			else
			{
				SAFE_DELETE(*mop_it);
				mop_it = _monsters.erase(mop_it);
			}
		}
		if( collisionFlag )
		{
			SAFE_DELETE(*bul_it);
			bul_it = _characterBullets.erase(bul_it);
		}
		else
		{ ++bul_it; }
	}
}

void StageLayer::setPlayerSprite()
{
	g_player1Character = new Character(this);
	g_player1Character->createSprite(charNum);
	g_player1Character->setBulletList(&_characterBullets);
	missileDelay = 1.0f / g_player1Character->getCharacterData()->ShootPerSec;
}

void StageLayer::spriteMoveFinished(CCNode *node)
{
	for( auto it = _monsters.begin(); it != _monsters.end(); )
	{
		//	스프라이트 회수
		if ((*it)->getCurrentSprite() == node)
		{
			this->removeChild(node, true);
			CC_SAFE_DELETE(*it);
			it = _monsters.erase(it);
		}
		else
		{ ++it; }
	}
}

void StageLayer::keyboardInput(float delayTime)
{
	CCPoint p1pos = g_player1Character->getPosition();
	CCPoint p1Acc;
	CharacterStatusType status = CS_STAND;
	if ( GetAsyncKeyState(VK_UP) & SHIFTED )
	{
		p1Acc.y += g_player1Character->getCharacterData()->MoveSpeed * delayTime;
		status = CS_UP;
	}
	if ( GetAsyncKeyState(VK_DOWN) & SHIFTED )
	{
		p1Acc.y -= g_player1Character->getCharacterData()->MoveSpeed * delayTime;
		status = CS_DOWN;
	}
	if ( GetAsyncKeyState(VK_LEFT) & SHIFTED )
	{
		p1Acc.x -= g_player1Character->getCharacterData()->MoveSpeed * delayTime;
		status = CS_LEFT;
	}
	if ( GetAsyncKeyState(VK_RIGHT) & SHIFTED )
	{
		p1Acc.x += g_player1Character->getCharacterData()->MoveSpeed * delayTime;
		status = CS_RIGHT;
	}

	//	포지션 설정
	p1pos.x += p1Acc.x; p1pos.y += p1Acc.y;
	
	//	화면 이탈 방지
	if ( p1pos.x >= winSize.width - g_player1Character->getCharacterData()->Size.width/2 )
	{ p1pos.x = winSize.width - g_player1Character->getCharacterData()->Size.width/2; }
	if ( p1pos.x <= g_player1Character->getCharacterData()->Size.width/2 )
	{ p1pos.x = g_player1Character->getCharacterData()->Size.width/2; }
	if ( p1pos.y >= winSize.height - g_player1Character->getCharacterData()->Size.height/2 )
	{ p1pos.y = winSize.height - g_player1Character->getCharacterData()->Size.height/2; }
	if ( p1pos.y <= g_player1Character->getCharacterData()->Size.height/2 )
	{ p1pos.y = g_player1Character->getCharacterData()->Size.height/2; }

	g_player1Character->setCurrentCharacterStatus(status);
	//	이동값이 있을 경우 포지션 변경 실행
	if ( p1Acc.x != 0.0f || p1Acc.y != 0.0f )
	{
		p1Acc.x = 0.0f; p1Acc.y = 0.0f;
		g_player1Character->setPosition(p1pos.x, p1pos.y);
	}
}

void StageLayer::missileMovedFinished(cocos2d::CCNode *node)
{
	_missiles.remove((CCSprite *)node);
	//	사정거리를 벗어난 미사일 제거
	node->removeFromParentAndCleanup(true);
}
