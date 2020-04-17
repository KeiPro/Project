#pragma once
#include "Card.h"

class GameManager
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
	GameManager(int _distribute, int _gameTotalMoney);
	~GameManager();
	
};