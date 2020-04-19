#pragma once
#include "pch.h"
#include "Player.h"

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
	void TurnSetting(Player* player, Player** phead); //������ �����ϴ� �Լ�
	//Getter
	inline int GetInputTotalNum() { return inputTotalNum; }
	inline Player* GetPlayer() { return comPlayer; }

	//Setter


	//������ �� �Ҹ���
	~GameController();
};