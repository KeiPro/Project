#include "Player.h"
#include "GameManager.h"

#pragma region Player Method

#pragma region Game Method
//기본 베팅 함수.
void Player::BaseVetting(GameManager* _gm)
{
	if (this->myMoney >= BASE_GAME_MONEY)
	{
		this->myMoney -= BASE_GAME_MONEY;
		_gm->PullGameTotalMoney(BASE_GAME_MONEY);
	}
}

//게임 베팅 함수.
void Player::GameVetting(int inputMoney, GameManager* _gm)
{
	if (this->myMoney >= inputMoney)
	{
		this->myMoney -= inputMoney;
	}
}

//돈을 받는 함수
void Player::PullMoney(int pullMoney)
{
	this->myMoney += pullMoney;
}

#pragma endregion


#pragma region Setter Method
//소지한 카드 변수 초기화.
void Player::SetCardSetting(Card _firstCard, Card _secondCard)
{
	this->firstCard = _firstCard;
	this->secondCard = _secondCard;
}

void Player::SetNameSetting(string _name)
{
	this->name = _name;
}

void Player::SetMoneySetting(int _setMoney)
{
	this->myMoney = _setMoney;
}

void Player::SetFirstCard(Card _card)
{
	this->firstCard = _card;
}

void Player::SetSecondCard(Card _card)
{
	this->secondCard = _card;
}

void Player::SetIsAlive(bool _isAlive)
{
	this->isAlive = _isAlive;
}

void Player::GiveMeCard(Card _card)
{
	if ((this->GetFirstCard().cardNumber == 0))
	{
		this->SetFirstCard(_card);
	}
	else
	{
		this->SetSecondCard(_card);
	}
}

#pragma endregion


#pragma region Getter Method

Card Player::GetFirstCard()
{
	return this->firstCard;
}

Card Player::GetSecondCard()
{
	return this->secondCard;
}

int Player::GetMoney()
{
	return this->myMoney;
}
string Player::GetName()
{
	return this->name;
}

bool Player::GetIsAlive()
{
	return this->isAlive;
}


#pragma endregion


#pragma endregion
