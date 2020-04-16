#pragma once
//���� �Ŵ��� Ŭ����
#include "Walnambbong.h"

class Player; //���� ����
class GameManager
{
private:
	int firstPlayer; //ù ��° �÷��̾� ����
	int gameTotalMoney; //���� �� ��
	int totalCardNumber; //��ü ī�� ����
	int remainingCardNumeber; //���� ī�� ����
	int totalPlayerNumber; //��ü �÷��̾� ��
	int remainingPlayerNumber; //���� �÷��̾� ��
	int x, y; //ī���� ��ġ�� ����ų ��ġ ��ǥ.
	int turn;
public:
	int order;
	//bool leftMoneyIsTure; //���� �ǵ��� �����ϴ���.
	

public:
	//������ ��� �� �ʱ�ȭ
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

	void CardSuffle(Card** _card); //ī�� ���� �޼ҵ�
	void CardDividing(Card** _card, Player* _player, Player* _comPlayer); //ī�� �����ִ� �޼ҵ�
	int PlayerGameStart(Card** _card, Player* _player, Player* _comPlayer); //���� �� �� �� ���� �����ϴ� �޼ҵ�
	void PlayerVetting(Card** _card, Player* _player, Player* _comPlayer); // ���� ����
	bool NextCardOpen(Card** _card, Player* _player, Player* _comPlayer); //ī�� ���� �Լ�
	//int PullMoney(); //���� ���� �޼ҵ�
	//void GameStart(); //���� �����ϴ� �Լ�
};