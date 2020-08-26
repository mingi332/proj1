#pragma once
#include <cocos2d.h>
#include "Carrot.h"
#include "appleItem.h"
USING_NS_CC;
using namespace std;


class GamePlayScene : public Scene
{
public:
	CREATE_FUNC(GamePlayScene);
	bool init();
	void update(float dt);
	int Maxitem;				//생성 최대 개수를 조절하기 위한 변수 (기본 15)
	int ItemCnt;

	float upgradetime;			//업그레이드 시 아이템 생성주기 감소

	//충돌처리 하는 함수

	//당근 생성을 위한 조건들
	
	float carrot_time;			//당근 생성 주기
	void makeCarrot();			//당근을 생성해주는 함수
	Vector<Carrot*> vCarrot;

	//사과 생성을 위한 조건들
	
	float apple_time;
	void makeApple();
	Vector<appleItem*> vApple;

	//버블 생성을 위한 조건들
	float bubble_time;			//버블 생성주기 (버블 충돌시 9999), (장애물 충돌 시 30)
	float upgradebubbletime;	//업그레이드 요소
	void makeBubble();
	
};

