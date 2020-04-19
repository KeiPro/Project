#pragma once
#include "Card.h"

class Player
{
private:

	Player* link; //다음 Player 객체를 가리킬 link변수.
	int turn; //턴을 저장하는 변수
	string name;
	int myMoney; //소지금
	Card myCards[2]; //플레이어가 받을 카드
	bool bettingJudge; //판단. 베팅을 할지 안할지
	int bettingMoney; //베팅 금액
	bool isAlive; //게임을 계속 진행할 수 있는 상태인가

public:

	//Getter
	inline string GetName() { return name; }
	inline Player* GetLink() { return link; }
	inline int GetTurn() { return turn; }

	//Setter
	inline void SetName(string _name) { name = _name; }
	inline void SetTurn(int _turn) { turn = _turn; }
	inline void SetLink(Player* _nextLink) 
	{
		link = _nextLink; 
	}

	//생성자
	Player();

};