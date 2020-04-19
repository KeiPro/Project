#pragma once
#include "Card.h"

class Dealer
{
private:
	Card* cards;
	int distribute; //ī�� ������ ����ϴ� ����
	int gameTotalMoney; //�ǵ�
	//int playerTurn; //�÷��̾� ��

public:

	//�Ϲ� �Լ���
	void CardSetting();
	void Print();
	void CardShuffle();
	Card Distribuing();
	void AddingTotalMoney(int money);

	//Setter
	//inline void SetPlayerTurn() {};

	//Getter
	inline int GetGameTotalMoney() { return gameTotalMoney; }

	//������
	Dealer(int _distribute, int _gameTotalMoney);
	~Dealer();
	
};