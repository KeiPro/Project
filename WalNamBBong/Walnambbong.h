#pragma once
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <string>

#define TYPE_COUNT 4
#define CARD_EACH_NUMBER 13

using namespace std;

enum CARD_TYPE {SPADE, DIAMOND, HEART, CLOVER};

struct Card
{
	int cardNumber; //ī���� ����
	int type; //ī���� ���
};

class Player
{
private:

	int firstCard, secondCard;
	int myMoney; //���� ������

public:
	Player(int x = 0, int y = 0, int z = 0) : firstCard{ x }, secondCard{ y }, myMoney{ z }
	{}

	void BaseVetting(); //�⺻ �����ϴ� �Լ� ����
	void GameVetting(int); //���� �����ϴ� �Լ� ����
	void SetCardSetting(); //ī�带 �����ϴ� �Լ�
	void CardSetting(int); //���� �� ī�带 ���� �Լ�����
	void PullMoney(int); // �� �޴� �Լ� ����
	int GetFirstCard();
	int GetSecondCard();
	int GetMoney();
};


//���� �Ŵ��� Ŭ����
class GameManager
{
private:
	int gameTotalMoney; //���� �� ��
	int totalCardNumber; //��ü ī�� ����
	int remainingCardNumebr; //���� ī�� ����
	int totalPlayerNumber; //��ü �÷��̾� ��
	int remainingPlayerNumber; //���� �÷��̾� ��

	
public:
	//������ ��� �� �ʱ�ȭ
	GameManager(int _totalMoney = 0, int _totalCard = 52, int _remainingCard = 52, int _totalPlayer = 0, int _remainingPlayer = 0) : gameTotalMoney{ _totalMoney },
		totalCardNumber{ _totalCard }, remainingCardNumebr{ _remainingCard }, totalPlayerNumber{ _totalPlayer }, remainingPlayerNumber{ _remainingPlayer }
	{

	}

	void CardSuffle(Card** _card); //ī�� ���� �Լ�����
	void CardDividing(); //ī�� �����ִ� �Լ�����
	void FirstPlayerSetting(); //�� �÷��̾� ���� �Լ�����
	

};
