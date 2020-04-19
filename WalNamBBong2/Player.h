#pragma once
#include "Card.h"

class Player
{
private:

	Player* link; //���� Player ��ü�� ����ų link����.
	int turn; //���� �����ϴ� ����
	string name;
	int myMoney; //������
	Card myCards[2]; //�÷��̾ ���� ī��
	bool bettingJudge; //�Ǵ�. ������ ���� ������
	int bettingMoney; //���� �ݾ�
	bool isAlive; //������ ��� ������ �� �ִ� �����ΰ�

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

	//������
	Player();

};