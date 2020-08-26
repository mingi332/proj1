#include "GamePlayScene.h"
#include "BackGround.h"
#include "Player.h"
#include "basicUI.h"
#include "Bubble.h"
#include "appleItem.h"

bool GamePlayScene::init()
{
	//갯수
	Maxitem = 15;			//각 아이템 별 최대 개수 기본값 (당근)
	ItemCnt = 0;


	//생성 시간
	upgradetime = 1.0f;		//기본 10초
	carrot_time = 0;
	apple_time = 0;
	bubble_time = 0;
	upgradebubbletime = 30.0f; // 기본 30초

	BackGround* bg = BackGround::create();
	this->addChild(bg);

	Player* p1 = Player::create();
	this->addChild(p1,1,"player");
	p1->setPosition(300, 150);

	basicUI* ui = basicUI::create();
	this->addChild(ui,10);


	this->scheduleUpdate();

	return true;
}

void GamePlayScene::update(float dt)
{
	Player* p1 = (Player*)this->getChildByName("player");
	
	//당근 충돌처리
	Carrot* ct = (Carrot*)this->getChildByName("carrot");
	for (Carrot* ct : vCarrot)
	{
		if (p1 != nullptr && ct != nullptr)
		{
			Rect rt = p1->gettheBox();
			Rect rt2 = ct->gettheBox();
			
			if (rt.intersectsRect(rt2) == true)
			{
				vCarrot.eraseObject(ct);
				ct->removeFromParentAndCleanup(true);
				ItemCnt--;
				break;			
			}
		}
	}


	//사과 충돌처리
	appleItem* app = (appleItem*)this->getChildByName("carrot");
	for (appleItem* app : vApple)
	{
		if (p1 != nullptr && app != nullptr)
		{
			Rect rt = p1->gettheBox();
			Rect rt2 = app->getBoundingBox();

			if (rt.intersectsRect(rt2) == true)
			{
				vApple.eraseObject(app);
				app->removeFromParentAndCleanup(true);
				ItemCnt--;
				break;
			}
		}
	}

	//버블 충돌처리
	Bubble* bub = (Bubble*)this->getChildByName("bubble");
	if (p1 != nullptr && bub != nullptr)
	{
		Rect rt = p1->gettheBox();
		Rect rt2 = bub->gettheBox();

		if (rt.intersectsRect(rt2) == true)
		{
			bub->setPosition(p1->getPosition());
		}
	}
	




	//아이템 생성 (당근)
	carrot_time += dt;

	if (carrot_time >= upgradetime)
	{
		makeCarrot();
		carrot_time = 0;
	}

	//아이템 생성 (사과)

	apple_time += dt;

	if (apple_time >= upgradetime)
	{
		makeApple();
		apple_time = 0;
	}

	//아이템 생성 (버블)

	bubble_time += dt;

	if (bubble_time >= upgradebubbletime)
	{
		makeBubble();
		bubble_time = -9999; //(1개만 생성되게 하기 위해, 충돌 시 수정)
	}

}

void GamePlayScene::makeCarrot()
{

	int random_Y = CCRANDOM_0_1() * 280 + 100;
	int random_X = CCRANDOM_0_1() * 500 + 50;


	if (ItemCnt < Maxitem)
	{
		Carrot* ct = Carrot::create();
		this->addChild(ct, 1, "carrot");

		ct->setPosition(random_X, random_Y);

		vCarrot.pushBack(ct);
		ItemCnt++;
	}

	else return;
}

void GamePlayScene::makeApple()
{
	int random_Y = CCRANDOM_0_1() * 280 + 100;
	int random_X = CCRANDOM_0_1() * 500 + 50;


	if (ItemCnt < Maxitem)
	{
		appleItem* app = appleItem::create();
		this->addChild(app, 1, "apple");

		app->setPosition(random_X, random_Y);

		vApple.pushBack(app);
		ItemCnt++;
	}

	else return;
}

void GamePlayScene::makeBubble()
{
	int random_Y = CCRANDOM_0_1() * 280 + 100;
	int random_X = CCRANDOM_0_1() * 500 + 50;

	Bubble* bub = Bubble::create();
	this->addChild(bub, 1, "bubble");

	bub->setPosition(random_X, random_Y);

}


