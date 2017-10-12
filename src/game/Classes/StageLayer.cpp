
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

		//	ȭ�鿡 �÷��̾� ��������Ʈ �߰�
		this->setPlayerSprite();

		//	�̵� ��ũ�� ȭ�� ������ ����
		ret = true;

		Data = &g_StageData.find(stageNumber)->second;

		//	���� ���� ���� �ޱ�
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
	**	�̵� ó�� ����
	**	ĳ���� �ൿ -> �Ʊ� �ൿ -> ĳ���� �ִϸ��̼� -> ���� �ൿ ->
	**	�Ʊ� �̻��� �̵� -> ���� �̻��� �̵� -> �Ʊ� �̻��� ���� -> ���� �̻��� ����
	*/
	//	�Ʊ� �ൿ
	keyboardInput(delayTime);
	missileInput(delayTime);

	//	ĳ���� �ִϸ��̼�
	g_player1Character->doAction(delayTime);

	//	���� �ൿ
	for (auto it = _monsters.begin(); it != _monsters.end(); ++it)
	{
		(*it)->doAction(delayTime);
	}
	//	���� ����
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

	//	�Ʊ� �̻��� �̵�
	moveAllyBullet(delayTime);

	//	���� �̻��� �̵�
	moveEnemyBullet(delayTime);

	//	���� �浹 üũ
	enemyCollisionCheck(delayTime);

}

void StageLayer::missileInput(float delayTime)
{
	CharacterStatusType status = CS_STAND;
	if ( GetAsyncKeyState(0x5A) & SHIFTED )	//	0x5A = 'Z'Ű
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
		//	ȭ���� ��� ��� ����
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
		//	ȭ���� ��� ��� ����
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
				//	�浹 üũ
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
		//	��������Ʈ ȸ��
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

	//	������ ����
	p1pos.x += p1Acc.x; p1pos.y += p1Acc.y;
	
	//	ȭ�� ��Ż ����
	if ( p1pos.x >= winSize.width - g_player1Character->getCharacterData()->Size.width/2 )
	{ p1pos.x = winSize.width - g_player1Character->getCharacterData()->Size.width/2; }
	if ( p1pos.x <= g_player1Character->getCharacterData()->Size.width/2 )
	{ p1pos.x = g_player1Character->getCharacterData()->Size.width/2; }
	if ( p1pos.y >= winSize.height - g_player1Character->getCharacterData()->Size.height/2 )
	{ p1pos.y = winSize.height - g_player1Character->getCharacterData()->Size.height/2; }
	if ( p1pos.y <= g_player1Character->getCharacterData()->Size.height/2 )
	{ p1pos.y = g_player1Character->getCharacterData()->Size.height/2; }

	g_player1Character->setCurrentCharacterStatus(status);
	//	�̵����� ���� ��� ������ ���� ����
	if ( p1Acc.x != 0.0f || p1Acc.y != 0.0f )
	{
		p1Acc.x = 0.0f; p1Acc.y = 0.0f;
		g_player1Character->setPosition(p1pos.x, p1pos.y);
	}
}

void StageLayer::missileMovedFinished(cocos2d::CCNode *node)
{
	_missiles.remove((CCSprite *)node);
	//	�����Ÿ��� ��� �̻��� ����
	node->removeFromParentAndCleanup(true);
}
