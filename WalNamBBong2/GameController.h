#pragma once
#include "pch.h"
#include "Player.h"

class GameController
{
private:
	int inputTotalNum;
	Player* comPlayer;
	int RegisterComName(); //컴퓨터들의 이름을 설정하는 함수
	void AutoRegisterComName(int _totalNumber); //랜덤하게 컴퓨터 이름이 설정되는 함수
	void InputRegisterComName(int _totalNumber); //컴퓨터 이름 수기 입력 함수.
	
public:
	void InputNamePrint(Player* player); //플레이어의 이름을 설정하는 함수
	void InputTotalNum(); //전체 플레이어 수 입력 함수
	void TurnSetting(Player* player, Player** phead); //순서를 설정하는 함수
	//Getter
	inline int GetInputTotalNum() { return inputTotalNum; }
	inline Player* GetPlayer() { return comPlayer; }

	//Setter


	//생성자 및 소멸자
	~GameController();
};