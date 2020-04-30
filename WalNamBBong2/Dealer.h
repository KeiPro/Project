#pragma once
#include "Card.h"

class Player;
class Dealer
{
private:
	Card* cards;
	int distribute; //ī�� ������ ����ϴ� ����
	int gameTotalMoney; //�ǵ�

public:

	//�Ϲ� �Լ���
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

	//������
	Dealer(int _distribute, int _gameTotalMoney);
	~Dealer();
	
};