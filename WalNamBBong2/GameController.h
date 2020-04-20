#pragma once
#include "pch.h"
#include "Player.h"

class Dealer;
class GameController
{
private:
	int inputTotalNum;
	Player* comPlayer;
	int RegisterComName(); //��ǻ�͵��� �̸��� �����ϴ� �Լ�
	void AutoRegisterComName(int _totalNumber); //�����ϰ� ��ǻ�� �̸��� �����Ǵ� �Լ�
	void InputRegisterComName(int _totalNumber); //��ǻ�� �̸� ���� �Է� �Լ�.
	
public:
	
	void InputNamePrint(Player* player); //�÷��̾��� �̸��� �����ϴ� �Լ�
	void InputTotalNum(); //��ü �÷��̾� �� �Է� �Լ�
	void TurnSetting(Player* player, Player** phead); //������ �����ϴ� �Լ� //Circular Linked List����.
	void InputMoney(Player** phead, Player* p, int _myMoney); //�ݾ��� �����ϴ� �Լ�
	void BaseBetting(Player* (&phead), Player* (&p), Dealer &dealer); //�⺻ �����Լ�
	void bettingMoney(Player** phead, Player* p); //�ݾ��� �����ϴ� �Լ�
	void CurrentStatePrint(Player* (&phead), Player* (&p), Dealer& dealer); //���� ��Ȳ�� ����Ʈ�ϴ� �Լ�

	//Getter
	inline int GetInputTotalNum() { return inputTotalNum; }
	inline Player* GetPlayer() { return comPlayer; }

	//Setter


	//������ �� �Ҹ���
	~GameController();
};