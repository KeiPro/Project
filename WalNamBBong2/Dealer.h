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
	Card Distribuing();
	void AddingTotalMoney(int money);
	void CardDividing(Player* (&phead), Player* (&p));

	//Setter
	//inline void SetPlayerTurn() {};

	//Getter
	inline int GetGameTotalMoney() { return gameTotalMoney; }

	//������
	Dealer(int _distribute, int _gameTotalMoney);
	~Dealer();
	
};