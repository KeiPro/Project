#pragma once
#include "Card.h"

class Player;
class Dealer
{
private:
	Card* cards;
	int distribute; //카드 순서를 담당하는 변수
	int gameTotalMoney; //판돈

public:

	//일반 함수들
	void CardSetting();
	void Print();
	void CardShuffle();
	Card Distributing();
	void AddingTotalMoney(int money);
	void CardDividing(Player* (&phead), Player* (&p));

	//Setter
	//inline void SetPlayerTurn() {};
	inline void SetDistribute(int _distribute) { distribute = _distribute; }
	
	//Getter
	inline int GetGameTotalMoney() { return gameTotalMoney; }
	inline int GetDistribute() { return distribute; }

	//생성자
	Dealer(int _distribute, int _gameTotalMoney);
	~Dealer();
	
};