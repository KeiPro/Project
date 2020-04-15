#include "Walnambbong.h"

#pragma region Player Method

#pragma region Game Method
//기본 베팅 함수.
void Player::BaseVetting(GameManager* _gm)
{
	if (this->myMoney >= BASE_GAME_MONEY)
	{
		this->myMoney -= BASE_GAME_MONEY;
		_gm->SetGameTotalMoney(BASE_GAME_MONEY);
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


#pragma endregion


#pragma endregion

#pragma region GameManager Method

#pragma region Game Method
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

//카드 나누기 함수
void GameManager::CardDividing(Card** _card, Player* _player, Player* _comPlayer)
{
	int j = this->GetFirstPlayer(); //선 플레이어의 인덱스를 가져온다. 0이면 플레이어, 1 ~ 3 : 컴퓨터1,2,3
	for (int i = 0; i < this->GetRemainingPlayerNumber() * 2; i++)
	{
		if (j == 0) 
		{
			_player->GiveMeCard(_card[this->x][this->y]);
			(this->y)++;
			
		}
		else
		{
			_comPlayer[j-1].GiveMeCard(_card[this->x][this->y]);
			(this->y)++;

		}

		if ((j + 1) % this->GetRemainingPlayerNumber() == 0)
		{
			j = 0;
		}
		else
		{
			j++;
		}

		if (this->y > CARD_EACH_NUMBER - 1)
		{
			this->y = 0;
			this->x++;
		}
	}
}

void GameManager::PlayerVetting(Card ** _card, Player * _player, Player * _comPlayer)
{
	if (this->GetFirstPlayer() == 0)
	{
		cout << _player->GetName() << "님 선 플레이어 입니다." << endl;
		cout << endl;
		cout << _player->GetName() << "님이 가진 카드 : " << _player->GetFirstCard().cardNumber << ", " << _player->GetSecondCard().cardNumber << endl;
	}
	else
	{
		cout << _comPlayer[this->GetFirstPlayer()-1].GetName() << "님 선 플레이어 입니다." << endl;
		cout << endl;
		cout << _comPlayer[this->GetFirstPlayer() - 1].GetName() << "님이 가진 카드 : " << _comPlayer[this->GetFirstPlayer() - 1].GetFirstCard().cardNumber << ", " << _comPlayer[this->GetFirstPlayer() - 1].GetSecondCard().cardNumber << endl;
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

//게임 판돈
void GameManager::SetGameTotalMoney(int _pullMoney)
{
	this->gameTotalMoney += _pullMoney;
}

#pragma endregion

#pragma region Getter Method
//게임 총 카드 개수
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