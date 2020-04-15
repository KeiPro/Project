#pragma once
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <string>

#define TYPE_COUNT 4
#define CARD_EACH_NUMBER 13
#define INIT_MONEY 2000
#define BASE_GAME_MONEY 200

using namespace std;

enum CARD_TYPE {SPADE, DIAMOND, HEART, CLOVER};

struct Card
{
	int cardNumber; //ī���� ����
	int type; //ī���� ���
};

class GameManager;

class Player
{
private:

	string name;
	Card firstCard, secondCard;
	int myMoney; //���� ������
	//bool defeat;

public:
	Player(int _cardNumber = 0, int type = -1, int _myMoney = 0) : firstCard{ _cardNumber, type }, secondCard{ _cardNumber, type }, myMoney{_myMoney}
	{} 

	void GiveMeCard(Card); //���� �� ī�带 ���� �Լ�����
	void PullMoney(int); // �� �޴� �Լ� ����
	void BaseVetting(GameManager* _gm);
	//�⺻ �����ϴ� �Լ� ����
	void GameVetting(int, GameManager* _gm); //���� �����ϴ� �Լ� ����

	//Setter
	void SetCardSetting(Card, Card); //ī�带 �����ϴ� �Լ�
	void SetNameSetting(string); //�̸��� �����ϴ� �Լ�
	void SetMoneySetting(int); // �Ӵϸ� �����ϴ� �Լ�
	void SetFirstCard(Card); //ù ��° ī�带 �����ϴ� �Լ�
	void SetSecondCard(Card); //�� ��° ī�带 �����ϴ� �Լ�

	//Getter
	Card GetFirstCard();
	Card GetSecondCard();
	int GetMoney();
	string GetName();

	~Player()
	{

	}
	
};

//���� �Ŵ��� Ŭ����
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

public:
	//������ ��� �� �ʱ�ȭ
	GameManager(int _firstPlayer = 0, int _totalMoney = 0, int _totalCard = 52, int _remainingCard = 52, int _totalPlayer = 0, int _remainingPlayer = 0, int _x = 0, int _y = 0)
		: gameTotalMoney{ _totalMoney }, totalCardNumber{ _totalCard }, remainingCardNumeber{ _remainingCard },
		totalPlayerNumber{ _totalPlayer }, remainingPlayerNumber{ _remainingPlayer }, x{ _x }, y{ _y }, firstPlayer{ _firstPlayer }
	{

	}

	//setter
	void SetGameTotalMoney(int);
	void SetTotalCardNumber(int);
	void SetRemainingCardNumeber(int);
	void SetTotalPlayerNumber(int);
	void SetRemainingPlayerNumber(int);
	void SetXPositionYPosition(int, int);
	void SetFirstPlayer(int);

	//getter
	int GetTotalCardNumber();
	int GetRemainingCardNumber();
	int GetTotalPlayerNumber();
	int GetRemainingPlayerNumber();
	int GetGameTotalMoney();
	int GetFirstPlayer();

	void CardSuffle(Card** _card); //ī�� ���� �޼ҵ�
	void CardDividing(Card** _card, Player* _player, Player* _comPlayer); //ī�� �����ִ� �޼ҵ�
	int PullMoney(); //���� ���� �޼ҵ�
	//void GameStart(); //���� �����ϴ� �Լ�
};