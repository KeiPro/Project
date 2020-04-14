#pragma once
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <string>

#define TYPE_COUNT 4
#define CARD_EACH_NUMBER 13
#define INIT_MONEY 2000

using namespace std;

enum CARD_TYPE {SPADE, DIAMOND, HEART, CLOVER};

struct Card
{
	int cardNumber; //카드의 숫자
	int type; //카드의 모양
};

class Player
{
private:

	string name;
	int firstCard, secondCard;
	int myMoney; //나의 소지금

public:
	Player(int x = 0, int y = 0, int z = 0) : firstCard{ x }, secondCard{ y }, myMoney{ z }
	{} 

	void BaseVetting(); //기본 베팅하는 함수 원형
	void GameVetting(int); //게임 베팅하는 함수 원형
	void SetCardSetting(); //카드를 세팅하는 함수
	void SetNameSetting(string); //이름을 세팅하는 함수
	void SetMoneySetting(int); // 머니를 설정하는 함수
	//void GiveMeCard(int); //셔플 후 카드를 받을 함수원형
	void PullMoney(int); // 돈 받는 함수 원형
	int GetFirstCard();
	int GetSecondCard();
	int GetMoney();
	
};


//게임 매니져 클래스
class GameManager
{
private:
	int gameTotalMoney; //게임 판 돈
	int totalCardNumber; //전체 카드 개수
	int remainingCardNumebr; //남은 카드 개수
	int totalPlayerNumber; //전체 플레이어 수
	int remainingPlayerNumber; //남은 플레이어 수

public:
	//생성자 사용 및 초기화
	GameManager(int _totalMoney = 0, int _totalCard = 52, int _remainingCard = 52, int _totalPlayer = 0, int _remainingPlayer = 0) : gameTotalMoney{ _totalMoney },
		totalCardNumber{ _totalCard }, remainingCardNumebr{ _remainingCard }, totalPlayerNumber{ _totalPlayer }, remainingPlayerNumber{ _remainingPlayer }
	{

	}

	//setter
	void SetGameTotalMoney(int);
	void SetTotalCardNumber(int);
	void SetRemainingCardNumebr(int);
	void SetTotalPlayerNumber(int);
	void SetRemainingPlayerNumber(int);

	//getter
	int GetTotalCardNumber();
	int GetRemainingCardNumebr();
	int GetTotalPlayerNumber();
	int GetRemainingPlayerNumber();
	int GetGameTotalMoney();

	void CardSuffle(Card** _card); //카드 셔플 함수원형
	void CardDividing(); //카드 나눠주는 함수원형
	void FirstPlayerSetting(); //선 플레이어 결정 함수원형
};
