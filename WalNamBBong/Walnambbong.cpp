#include "Walnambbong.h"

#pragma region Player Method

#pragma region Game Method
//�⺻ ���� �Լ�.
void Player::BaseVetting(GameManager* _gm)
{
	if (this->myMoney >= BASE_GAME_MONEY)
	{
		this->myMoney -= BASE_GAME_MONEY;
		_gm->SetGameTotalMoney(BASE_GAME_MONEY);
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

void Player::GiveMeCard(Card _card)
{
	if ((this->GetFirstCard().cardNumber == 0))
	{
		this->SetFirstCard(_card);
		cout << "ù ��° ī�� ����!" << endl;
	}
	else
	{
		this->SetSecondCard(_card);
		cout << "�� ��° ī�� ����!" << endl;
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


#pragma endregion


#pragma endregion

#pragma region GameManager Method

#pragma region Game Method
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

//ī�� ������ �Լ�
void GameManager::CardDividing(Card** _card, Player* _player, Player* _comPlayer, int _playerTotalNumber)
{
	for (int i = 0; i < 2; i++)
	{
		_player->GiveMeCard(_card[this->x][this->y]);
		cout << this->x << ", " << this->y << endl;
		(this->y)++;

		//y���� �� ����� ī�� ����(13��-1) ���� Ŀ���ٸ� y�� 0���� �ٲ��ְ� x�� 1������Ų��.
		if (this->y > CARD_EACH_NUMBER - 1)
		{
			this->y = 0;
			this->x++;
		}
		for (int j = 0; j < _playerTotalNumber-1 ; j++) //��Ϻ�..
		{
			_comPlayer[j].GiveMeCard(_card[this->x][this->y]);
			cout << this->x << ", " << this->y << endl;
			(this->y)++;
			if (this->y > CARD_EACH_NUMBER - 1)
			{
				this->y = 0;
				this->x++;
			}
		}
	}
}

#pragma endregion

#pragma region Setter Method
void GameManager::SetTotalCardNumber(int totalCardNumber)
{
	this->totalCardNumber = totalCardNumber;
}

void GameManager::SetRemainingCardNumeber(int _remainingCardNumber)
{
	this->remainingCardNumeber = _remainingCardNumber;
}

void GameManager::SetTotalPlayerNumber(int _totalPlayerNumber)
{
	this->totalPlayerNumber = _totalPlayerNumber;
}

void GameManager::SetRemainingPlayerNumber(int _remainingPlayerNumber)
{
	this->remainingPlayerNumber = _remainingPlayerNumber;
}

void GameManager::SetXPositionYPosition(int _x, int _y)
{
	this->x = _x;
	this->y = _y;
}

void GameManager::SetFirstPlayer(int _firstPlayer)
{
	this->firstPlayer = _firstPlayer;
}

//���� �ǵ�
void GameManager::SetGameTotalMoney(int _pullMoney)
{
	this->gameTotalMoney += _pullMoney;
}

#pragma endregion

#pragma region Getter Method
//���� �� ī�� ����
int GameManager::GetTotalCardNumber()
{
	return this->totalCardNumber;
}

int GameManager::GetRemainingCardNumber()
{
	return this->remainingCardNumeber;
}

int GameManager::GetRemainingPlayerNumber()
{
	return this->remainingPlayerNumber;
}

int GameManager::GetGameTotalMoney()
{
	return this->gameTotalMoney;
}

int GameManager::GetFirstPlayer()
{
	return this->firstPlayer;
}

int GameManager::GetTotalPlayerNumber()
{
	return this->totalPlayerNumber;
}

#pragma endregion

#pragma endregion