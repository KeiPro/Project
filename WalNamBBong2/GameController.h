#pragma once
#include "pch.h"
#include "Player.h"

class Dealer;
class GameController
{
private:
	int inputTotalNum;
	int maxPlayerNum;
	int leftPlayerNum;
	int waitPlayerNum; //����ο��� �� �� ���ҳ�?
	int waitPlayerIndex; //����ο� �ε���
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
	void CurrentStatePrint(Player* (&phead), Player* (&p), Dealer& dealer); //���� ��Ȳ�� ����Ʈ�ϴ� �Լ�
	bool ThirteenCardCheck(Player* (&phead), Player* (&p), Dealer& dealer, Player* (&player));
	bool BettingYesOrNo(Player* (&phead), Player* (&p), int& playerNumber, Dealer &dealer, Player* player);
	bool ComJudgeFunction(int vicProbability);
	int TwoNumberGap(int num1, int num2); // �� ���� ������ ���� ���� Ȯ��
	int HowMuchBetting(Player* (&p), int gabPropability, Dealer &dealer);
	void NextPlayerPointer(Player* (&p), int& playerNumber);
	void BettingCardOpen(Player* (&phead), Player* (&p), Dealer& dealer, Player* player);
	void PlayerOutFunction(Player* (&phead), Player* (&p), Player* (&player));

	//void BettingMoney

	//Getter
	inline int GetInputTotalNum() { return inputTotalNum; }
	inline int GetRealPlayerNum() { return maxPlayerNum; }
	inline int GetLeftPlayerNum() {	return leftPlayerNum; }
	inline Player* GetPlayer() { return comPlayer; }

	//Setter
	inline int SetLeftPlayerNum(int _leftPlayerNum) { leftPlayerNum = _leftPlayerNum; }

	GameController() : inputTotalNum(0), maxPlayerNum(0), leftPlayerNum(0), waitPlayerIndex(0), baseInputMoney(0), waitPlayerNum(0)
	{
		comPlayer = nullptr;
	}

	//������ �� �Ҹ���
	~GameController();
};