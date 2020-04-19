#pragma once
#include "Card.h"

class Dealer
{
private:
	Card* cards;
	int distribute; //카드 순서를 담당하는 변수
	int gameTotalMoney; //판돈
	//int playerTurn; //플레이어 턴

public:

	//일반 함수들
	void CardSetting();
	void Print();
	void CardShuffle();
	Card Distribuing();
	void AddingTotalMoney(int money);

	//Setter
	//inline void SetPlayerTurn() {};

	//Getter
	inline int GetGameTotalMoney() { return gameTotalMoney; }

	//생성자
	Dealer(int _distribute, int _gameTotalMoney);
	~Dealer();
	
};