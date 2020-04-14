#include "Walnambbong.h"

//기본 베팅 함수.
void Player::BaseVetting()
{
	if (this->myMoney > 200)
		this->myMoney -= 200;
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

//카드 세팅 받는 함수 총 2회 호출.
void Player::CardSetting(int cardNumber)
{
	if (this->firstCard == 0)
		this->firstCard = cardNumber;
	else
		this->firstCard = cardNumber;
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

void GameManager::CardSuffle(Card** _card)
{
	int y = rand() % 4; // 0 ~ 3 까지
	int x = rand() % 14; // 0 ~ 13 까지
	Card tmp1, tmp2;

	tmp1 = _card[y][x];

	y = rand() % 4; // 0 ~ 3 까지
	x = rand() % 14; // 0 ~ 13 까지

	tmp2 = _card[y][x];
}
