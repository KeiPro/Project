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
	int RegisterComName(); //컴퓨터들의 이름을 설정하는 함수
	void AutoRegisterComName(int _totalNumber); //랜덤하게 컴퓨터 이름이 설정되는 함수
	void InputRegisterComName(int _totalNumber); //컴퓨터 이름 수기 입력 함수.
	
public:
	
	void InputNamePrint(Player* player); //플레이어의 이름을 설정하는 함수
	void InputTotalNum(); //전체 플레이어 수 입력 함수
	void TurnSetting(Player* player, Player** phead); //순서를 설정하는 함수 //Circular Linked List구현.
	void InputMoney(Player** phead, Player* p, int _myMoney); //금액을 설정하는 함수
	void BaseBetting(Player* (&phead), Player* (&p), Dealer &dealer); //기본 베팅함수
	void bettingMoney(Player** phead, Player* p); //금액을 베팅하는 함수
	void CurrentStatePrint(Player* (&phead), Player* (&p), Dealer& dealer); //현재 상황을 프린트하는 함수
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


	//생성자 및 소멸자
	~GameController();
};