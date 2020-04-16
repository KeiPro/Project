#pragma once
//게임 매니져 클래스
#include "Walnambbong.h"

class Player; //전방 선언
class GameManager
{
private:
	int firstPlayer; //첫 번째 플레이어 변수
	int gameTotalMoney; //게임 판 돈
	int totalCardNumber; //전체 카드 개수
	int remainingCardNumeber; //남은 카드 개수
	int totalPlayerNumber; //전체 플레이어 수
	int remainingPlayerNumber; //남은 플레이어 수
	int x, y; //카드의 위치를 가리킬 위치 좌표.
	int turn;
public:
	int order;
	//bool leftMoneyIsTure; //남은 판돈이 존재하는지.
	

public:
	//생성자 사용 및 초기화
	GameManager(int _firstPlayer = 0, int _totalMoney = 0, int _totalCard = 52, int _remainingCard = 52, int _totalPlayer = 0, int _remainingPlayer = 0, int _x = 0, int _y = 0)
		: gameTotalMoney{ _totalMoney }, totalCardNumber{ _totalCard }, remainingCardNumeber{ _remainingCard },
		totalPlayerNumber{ _totalPlayer }, remainingPlayerNumber{ _remainingPlayer }, x{ _x }, y{ _y }, firstPlayer{ _firstPlayer }
	{

	}

	//setter
	void PullGameTotalMoney(int);
	void SetTotalCardNumber(int);
	void SetRemainingCardNumeber(int);
	void SetTotalPlayerNumber(int);
	void SetRemainingPlayerNumber(int);
	void SetXPositionYPosition(int, int);
	void SetFirstPlayer(int);
	void SetTurn(int);
	//void SetLeftMoneyIsTrue(bool);

	//getter
	int GetTotalCardNumber();
	int GetRemainingCardNumber();
	int GetTotalPlayerNumber();
	int GetRemainingPlayerNumber();
	int GetGameTotalMoney();
	int GetFirstPlayer();
	int GetTurn();
	//bool GetLeftMoneyIsTrue();

	void CardSuffle(Card** _card); //카드 셔플 메소드
	void CardDividing(Card** _card, Player* _player, Player* _comPlayer); //카드 나눠주는 메소드
	int PlayerGameStart(Card** _card, Player* _player, Player* _comPlayer); //베팅 할 지 말 지를 결정하는 메소드
	void PlayerVetting(Card** _card, Player* _player, Player* _comPlayer); // 베팅 시작
	bool NextCardOpen(Card** _card, Player* _player, Player* _comPlayer); //카드 오픈 함수
	//int PullMoney(); //돈을 받을 메소드
	//void GameStart(); //게임 진행하는 함수
};