#pragma once
#include "Card.h"

class Player
{
private:

	Player* link; //다음 Player 객체를 가리킬 link변수.
	int turn; //턴을 저장하는 변수
	string name;
	int myMoney; //소지금
	Card myFirstCard; //플레이어가 받을 첫 번째 카드
	Card mySecondCard; //플레이어가 받을 두 번째 카드
	bool bettingJudge; //판단. 베팅을 할지 안할지
	int bettingMoney; //베팅 금액
	bool isAlive; //게임을 계속 진행할 수 있는 상태인가

public:

	//Getter
	inline string GetName() { return name; }
	inline Player* GetLink() { return link; }
	inline int GetTurn() { return turn; }
	inline int GetMyMoney() { return myMoney; }
	inline Card GetMyFirstCard() { return myFirstCard; }
	inline Card GetMySecondCard() { return mySecondCard; }
	//inline Card GetMyCard() { return myCards; }

	//Setter
	inline void SetName(string _name) { name = _name; }
	inline void SetTurn(int _turn) { turn = _turn; }
	inline void SetLink(Player* _nextLink) { link = _nextLink; }
	inline void SetMyMoney(int _myMoney) { myMoney = _myMoney; }
	inline void SetMyFirstCard(Card _card) { myFirstCard = _card; }
	inline void SetMySecondCard(Card _card) { mySecondCard = _card; }
	//생성자
	Player();

};