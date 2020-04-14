#include "Walnambbong.h"

//�⺻ ���� �Լ�.
void Player::BaseVetting()
{
	if (this->myMoney > 200)
		this->myMoney -= 200;
}

//���� ���� �Լ�.
void Player::GameVetting(int inputMoney)
{
	if (this->myMoney >= inputMoney)
	{
		this->myMoney -= inputMoney;
	}
}

//������ ī�� ���� �ʱ�ȭ.
void Player::SetCardSetting()
{
	this->firstCard = 0;
	this->secondCard = 0;
}

//ī�� ���� �޴� �Լ� �� 2ȸ ȣ��.
void Player::CardSetting(int cardNumber)
{
	if (this->firstCard == 0)
		this->firstCard = cardNumber;
	else
		this->firstCard = cardNumber;
}

//���� �޴� �Լ�
void Player::PullMoney(int pullMoney)
{
	this->myMoney += pullMoney;
}

int Player::GetFirstCard()
{
	return this->firstCard;
}

int Player::GetSecondCard()
{
	return this->secondCard;
}

int Player::GetMoney()
{
	return this->myMoney;
} 

void GameManager::CardSuffle(Card** _card)
{
	int y = rand() % 4; // 0 ~ 3 ����
	int x = rand() % 14; // 0 ~ 13 ����
	Card tmp1, tmp2;

	tmp1 = _card[y][x];

	y = rand() % 4; // 0 ~ 3 ����
	x = rand() % 14; // 0 ~ 13 ����

	tmp2 = _card[y][x];
}
