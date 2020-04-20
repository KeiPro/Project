#pragma once
#include "Card.h"

class Player
{
private:

	Player* link; //���� Player ��ü�� ����ų link����.
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
	//������
	Player();

};