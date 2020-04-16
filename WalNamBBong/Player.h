#pragma once
#include "Walnambbong.h"

class GameManager;
class Player
{
private:

	string name;
	Card firstCard, secondCard;
	bool isAlive;
	int judgement;

	int myMoney; //���� ������
	//bool defeat;

public:
	Player(int _cardNumber = 0, int _myMoney = 0, bool _isAlive = true) : firstCard{ _cardNumber, "" }, secondCard{ _cardNumber, "" }, myMoney{ _myMoney }, isAlive{ _isAlive }
	{
		
	}

	void GiveMeCard(Card); //���� �� ī�带 ���� �Լ�����
	void PullMoney(int); // �� �޴� �Լ� ����
	void BaseVetting(GameManager* _gm);	//�⺻ �����ϴ� �Լ� ����
	void GameVetting(int, GameManager* _gm); //���� �����ϴ� �Լ� ����


	//Setter
	void SetCardSetting(Card, Card); //ī�带 �����ϴ� �Լ�
	void SetNameSetting(string); //�̸��� �����ϴ� �Լ�
	void SetMoneySetting(int); // �Ӵϸ� �����ϴ� �Լ�
	void SetFirstCard(Card); //ù ��° ī�带 �����ϴ� �Լ�
	void SetSecondCard(Card); //�� ��° ī�带 �����ϴ� �Լ�
	void SetIsAlive(bool); //��ҳ� �׾����� üũ�ϴ� �Լ�
	

	//Getter
	Card GetFirstCard();
	Card GetSecondCard();
	int GetMoney();
	string GetName();
	bool GetIsAlive();
	int JudgementFunction(GameManager* _gm);

};