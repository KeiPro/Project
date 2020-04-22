#pragma once
#include "pch.h"
#include "Player.h"

class Dealer;
class GameController
{
private:
	int inputTotalNum;
	int realPlayerNum;
	int baseInputMoney;
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
	void BettingYesOrNo(Player* (&phead), Player* (&p), int& playerNumber, Dealer &dealer, Player* player);
	bool ComJudgeFunction(int vicProbability);
	int TwoNumberGap(int num1, int num2);
	int HowMuchBetting(Player* (&p), int gabPropability, Dealer &dealer);

	//void BettingMoney

	//Getter
	inline int GetInputTotalNum() { return inputTotalNum; }
	inline int GetRealPlayerNum() { return realPlayerNum; }
	inline Player* GetPlayer() { return comPlayer; }

	//Setter


	//������ �� �Ҹ���
	~GameController();
};