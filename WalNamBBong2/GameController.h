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
	int waitPlayerNum; //대기인원이 몇 명 남았나?
	int waitPlayerIndex; //대기인원 인덱스
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
	void CurrentStatePrint(Player* (&phead), Player* (&p), Dealer& dealer); //현재 상황을 프린트하는 함수
	bool ThirteenCardCheck(Player* (&phead), Player* (&p), Dealer& dealer, Player* (&player));
	bool BettingYesOrNo(Player* (&phead), Player* (&p), int& playerNumber, Dealer &dealer, Player* player);
	bool ComJudgeFunction(int vicProbability);
	int TwoNumberGap(int num1, int num2); // 두 숫자 사이의 값이 나올 확률
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

	//생성자 및 소멸자
	~GameController();
};