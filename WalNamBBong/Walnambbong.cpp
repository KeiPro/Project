#include "Walnambbong.h"

//�⺻ ���� �Լ�.
void Player::BaseVetting()
{
	if (this->myMoney > 200) 
	{
		this->myMoney -= 200;
	}
	
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

void Player::SetNameSetting(string name)
{
	this->name = name;
}

void Player::SetMoneySetting(int _setMoney)
{
	this->myMoney = _setMoney;
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


void GameManager::SetTotalCardNumber(int totalCardNumber)
{
	this->totalCardNumber = totalCardNumber;
}

void GameManager::SetRemainingCardNumebr(int _remainingCardNumber)
{
	this->remainingCardNumebr = _remainingCardNumber;
}

void GameManager::SetTotalPlayerNumber(int _totalPlayerNumber)
{
	this->totalPlayerNumber = _totalPlayerNumber;
}

void GameManager::SetRemainingPlayerNumber(int _remainingPlayerNumber)
{
	this->remainingPlayerNumber = _remainingPlayerNumber;
}

//���� �ǵ�
void GameManager::SetGameTotalMoney(int gameTotalMoney)
{
	this->gameTotalMoney = gameTotalMoney;
}

//���� �� ī�� ����
int GameManager::GetTotalCardNumber()
{
	return this->totalCardNumber;
}

int GameManager::GetRemainingCardNumebr()
{
	return this->remainingCardNumebr;
}

int GameManager::GetRemainingPlayerNumber()
{
	return this->remainingPlayerNumber;
}

int GameManager::GetGameTotalMoney()
{
	return this->gameTotalMoney;
}

int GameManager::GetTotalPlayerNumber()
{
	return this->totalPlayerNumber;
}




//ī����� �Լ�
void GameManager::CardSuffle(Card** _card)
{
	Card tmp;
	int x, y, a, b;

	for (int i = 0; i < 500; i++)
	{
		x = rand() % 4; // 0 ~ 3 ����
		y = rand() % 13; // 0 ~ 13 ����
		a = rand() % 4;
		b = rand() % 13;

		while ((x == a) && (y == b))
		{
			a = rand() % 4;
			b = rand() % 13;
		}

		tmp = _card[x][y];
		_card[x][y] = _card[a][b];
		_card[a][b] = tmp;
		
	}
}
