#include "Player.h"
#include "GameManager.h"

#pragma region Player Method

#pragma region Game Method
//�⺻ ���� �Լ�.
void Player::BaseVetting(GameManager* _gm)
{
	if (this->myMoney >= BASE_GAME_MONEY)
	{
		this->myMoney -= BASE_GAME_MONEY;
		_gm->PullGameTotalMoney(BASE_GAME_MONEY);
	}
}

//���� ���� �Լ�.
void Player::GameVetting(int inputMoney, GameManager* _gm)
{
	if (this->myMoney >= inputMoney)
	{
		this->myMoney -= inputMoney;
	}
}

//���� �޴� �Լ�
void Player::PullMoney(int pullMoney)
{
	this->myMoney += pullMoney;
}

#pragma endregion


#pragma region Setter Method
//������ ī�� ���� �ʱ�ȭ.
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

void Player::SetJudgement(int _probability)
{
	judgement = _probability;
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

int Player::GetJudgement()
{
	return this->judgement;
}

int Player::JudgementFunction(GameManager* _gm)
{
	int highNumber;
	int lowNumber;
	int probability;
	if (this->firstCard.cardNumber > this->secondCard.cardNumber)
	{
		highNumber = this->firstCard.cardNumber;
		lowNumber = this->secondCard.cardNumber;
	}
	else if (this->firstCard.cardNumber < this->secondCard.cardNumber)
	{
		highNumber = this->secondCard.cardNumber;
		lowNumber = this->firstCard.cardNumber;
	}
	else
		return 0;

	cout << highNumber << ", " << lowNumber << endl;
	probability = (int)( 100 * ((double)highNumber - lowNumber-1) / CARD_EACH_NUMBER); // %�� ����� ���´�.
	cout << "Ȯ�� ��� ��...." << probability << endl;
	return probability;
}


#pragma endregion


#pragma endregion
