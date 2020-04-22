#pragma once
#include "Card.h"

class Player
{
private:

	Player* nextLink; //���� Player ��ü�� ����ų link����.
	Player* prevLink; //���� Player ��ü�� ����ų link����
	int turn; //���� �����ϴ� ����
	string name;
	int myMoney; //������
	Card myFirstCard; //�÷��̾ ���� ù ��° ī��
	Card mySecondCard; //�÷��̾ ���� �� ��° ī��
	bool bettingJudge; //�Ǵ�. ������ ���� ������
	int bettingMoney; //���� �ݾ�
	bool isAlive; //������ ��� ������ �� �ִ� �����ΰ�

public:

	//Getter
	inline string GetName() { return name; }
	inline Player* GetNextLink() { return nextLink; }
	inline Player* GetPrevLink() { return prevLink; }
	inline int GetTurn() { return turn; }
	inline int GetMyMoney() { return myMoney; }
	inline Card GetMyFirstCard() { return myFirstCard; }
	inline Card GetMySecondCard() { return mySecondCard; }
	inline int GetBettingMoney() { return bettingMoney; }

	//Setter
	inline void SetName(string _name) { name = _name; }
	inline void SetTurn(int _turn) { turn = _turn; }
	inline void SetNextLink(Player* _nextLink) { nextLink = _nextLink; }
	inline void SetPrevLink(Player* _prevLink) { prevLink = _prevLink; }
	inline void SetMyMoney(int _myMoney) { myMoney = _myMoney; }
	inline void SetMyFirstCard(Card _card) { myFirstCard = _card; }
	inline void SetMySecondCard(Card _card) { mySecondCard = _card; }
	inline void SetBettingMoney(int _bettingMoney) { bettingMoney = _bettingMoney; }

	//������
	Player();

};