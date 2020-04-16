#pragma once
#include "Walnambbong.h"

class GameManager;
class Player
{
private:

	string name;
	Card firstCard, secondCard;
	bool isAlive;
	int judgement;

	int myMoney; //나의 소지금
	//bool defeat;

public:
	Player(int _cardNumber = 0, int _myMoney = 0, bool _isAlive = true) : firstCard{ _cardNumber, "" }, secondCard{ _cardNumber, "" }, myMoney{ _myMoney }, isAlive{ _isAlive }
	{
		
	}

	void GiveMeCard(Card); //셔플 후 카드를 받을 함수원형
	void PullMoney(int); // 돈 받는 함수 원형
	void BaseVetting(GameManager* _gm);	//기본 베팅하는 함수 원형
	void GameVetting(int, GameManager* _gm); //게임 베팅하는 함수 원형


	//Setter
	void SetCardSetting(Card, Card); //카드를 세팅하는 함수
	void SetNameSetting(string); //이름을 세팅하는 함수
	void SetMoneySetting(int); // 머니를 설정하는 함수
	void SetFirstCard(Card); //첫 번째 카드를 세팅하는 함수
	void SetSecondCard(Card); //두 번째 카드를 세팅하는 함수
	void SetIsAlive(bool); //살았나 죽었나를 체크하는 함수
	

	//Getter
	Card GetFirstCard();
	Card GetSecondCard();
	int GetMoney();
	string GetName();
	bool GetIsAlive();
	int JudgementFunction(GameManager* _gm);

};