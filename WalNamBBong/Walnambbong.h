#pragma once
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <string>

#define TYPE_COUNT 4
#define CARD_EACH_NUMBER 13
#define INIT_MONEY 2000
#define BASE_GAME_MONEY 200

using namespace std;

enum CARD_TYPE {SPADE, DIAMOND, HEART, CLOVER};

struct Card
{
	int cardNumber; //카드의 숫자
	int type; //카드의 모양
};

class GameManager;

class Player
{
private:

	string name;
	Card firstCard, secondCard;
	int myMoney; //나의 소지금
	//bool defeat;

public:
	Player(int _cardNumber = 0, int type = -1, int _myMoney = 0) : firstCard{ _cardNumber, type }, secondCard{ _cardNumber, type }, myMoney{_myMoney}
	{} 

	void GiveMeCard(Card); //셔플 후 카드를 받을 함수원형
	void PullMoney(int); // 돈 받는 함수 원형
	void BaseVetting(GameManager* _gm);
	//기본 베팅하는 함수 원형
	void GameVetting(int, GameManager* _gm); //게임 베팅하는 함수 원형

	//Setter
	void SetCardSetting(Card, Card); //카드를 세팅하는 함수
	void SetNameSetting(string); //이름을 세팅하는 함수
	void SetMoneySetting(int); // 머니를 설정하는 함수
	void SetFirstCard(Card); //첫 번째 카드를 세팅하는 함수
	void SetSecondCard(Card); //두 번째 카드를 세팅하는 함수

	//Getter
	Card GetFirstCard();
	Card GetSecondCard();
	int GetMoney();
	string GetName();

	~Player()
	{

	}
	
};

//게임 매니져 클래스
class GameManager
{
private:
	int firstPlayer; //첫 번째 플레이어 변수
	int gameTotalMoney; //게임 판 돈
	int totalCardNumber; //전체 카드 개수
	int remainingCardNumeber; //남은 카드 개수
	int totalPlayerNumber; //전체 플레이어 수
	int remainingPlayerNumber; //남은 플레이어 수
	int x, y; //카드의 위치를 가리킬 위치 좌표.

public:
	//생성자 사용 및 초기화
	GameManager(int _firstPlayer = 0, int _totalMoney = 0, int _totalCard = 52, int _remainingCard = 52, int _totalPlayer = 0, int _remainingPlayer = 0, int _x = 0, int _y = 0)
		: gameTotalMoney{ _totalMoney }, totalCardNumber{ _totalCard }, remainingCardNumeber{ _remainingCard },
		totalPlayerNumber{ _totalPlayer }, remainingPlayerNumber{ _remainingPlayer }, x{ _x }, y{ _y }, firstPlayer{ _firstPlayer }
	{

	}

	//setter
	void SetGameTotalMoney(int);
	void SetTotalCardNumber(int);
	void SetRemainingCardNumeber(int);
	void SetTotalPlayerNumber(int);
	void SetRemainingPlayerNumber(int);
	void SetXPositionYPosition(int, int);
	void SetFirstPlayer(int);

	//getter
	int GetTotalCardNumber();
	int GetRemainingCardNumber();
	int GetTotalPlayerNumber();
	int GetRemainingPlayerNumber();
	int GetGameTotalMoney();
	int GetFirstPlayer();

	void CardSuffle(Card** _card); //카드 셔플 메소드
	void CardDividing(Card** _card, Player* _player, Player* _comPlayer); //카드 나눠주는 메소드
	int PullMoney(); //돈을 받을 메소드
	//void GameStart(); //게임 진행하는 함수
};