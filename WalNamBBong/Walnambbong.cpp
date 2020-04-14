#include "Walnambbong.h"

//기본 베팅 함수.
void Player::BaseVetting()
{
	if (this->myMoney > 200) 
	{
		this->myMoney -= 200;
	}
	
}

//게임 베팅 함수.
void Player::GameVetting(int inputMoney)
{
	if (this->myMoney >= inputMoney)
	{
		this->myMoney -= inputMoney;
	}
}

//소지한 카드 변수 초기화.
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

//돈을 받는 함수
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

//게임 판돈
void GameManager::SetGameTotalMoney(int gameTotalMoney)
{
	this->gameTotalMoney = gameTotalMoney;
}

//게임 총 카드 개수
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




//카드셔플 함수
void GameManager::CardSuffle(Card** _card)
{
	Card tmp;
	int x, y, a, b;

	for (int i = 0; i < 500; i++)
	{
		x = rand() % 4; // 0 ~ 3 까지
		y = rand() % 13; // 0 ~ 13 까지
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
