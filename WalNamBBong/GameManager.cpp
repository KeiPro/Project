#include "GameManager.h"
#include "Player.h"

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
	for (int i = 0; i < this->GetTotalPlayerNumber() * 2; i++)
	{
		if (j == 0)
		{
			if (_player->GetIsAlive() == true)
			{
				_player->GiveMeCard(_card[this->x][this->y]);
				(this->y)++;
			}
			cout << "1" << endl;
		}
		else
		{
			//살아있으면 나눠준다.
			if (_comPlayer[j - 1].GetIsAlive() == true) {
				_comPlayer[j - 1].GiveMeCard(_card[this->x][this->y]);
				(this->y)++;
			}
			cout << "2" << endl;
		}

		if ( (j + 1) % this->GetTotalPlayerNumber() == 0 )
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

//차례와 베팅 유무를 처리할 함수
int GameManager::PlayerGameStart(Card ** _card, Player * _player, Player * _comPlayer)
{
	int vettingCall;
	int j = this->GetFirstPlayer();

	if (j == 0)
	{
		cout << _player->GetName() << "님 차례입니다." << endl;
		cout << endl;
		cout << _player->GetName() << "님이 가진 카드 : " << _player->GetFirstCard().type << " " << _player->GetFirstCard().cardNumber << ", " << 
			_player->GetSecondCard().type << " " << _player->GetSecondCard().cardNumber << endl;

		Sleep(2000);

		if ((_player->GetFirstCard().cardNumber == 13) || (_player->GetSecondCard().cardNumber == 13))
		{
			if ((_player->GetFirstCard().cardNumber == 13) && (_player->GetSecondCard().cardNumber == 13)) //빗자루.
			{
				cout << " 13이 두 개!! " << endl;
				cout << " 빗 자 루 !!" << endl;
				
				return 0; //빗자루로 승리.
			}
			else
			{
				cout << "다이.." << endl;
				return 2;
			}
		}

		cout << "베팅 하시겠습니까? 1) 예 2) 아니오 >> ";
		cin >> vettingCall;

		if (vettingCall == 1)
		{
			return 1;
		}
		else
		{
			cout << "다이.." << endl;
			return 2;
		}
	}
	else
	{
		cout << _comPlayer[j - 1].GetName() << "님 차례입니다." << endl;
		cout << endl;
		cout << _comPlayer[j - 1].GetName() << "님이 가진 카드 : " << _comPlayer[j-1].GetFirstCard().type << " " << _comPlayer[j - 1].GetFirstCard().cardNumber 
			 << ", " << _comPlayer[j - 1].GetSecondCard().type << " " << _comPlayer[j - 1].GetSecondCard().cardNumber << endl;

		if ((_comPlayer[j - 1].GetFirstCard().cardNumber == 13) || (_comPlayer[j - 1].GetFirstCard().cardNumber == 13))
		{
			if ((_comPlayer[j - 1].GetFirstCard().cardNumber == 13) && (_comPlayer[j - 1].GetFirstCard().cardNumber == 13)) //빗자루.
			{
				cout << " 13이 두 개!! " << endl;
				cout << " 빗 자 루 !!" << endl;

				_player->PullMoney(this->GetGameTotalMoney());

				return 0; //빗자루로 승리.
			}
			else
			{
				cout << "다이.." << endl;
				return 2;
			}
		}

		cout << "베팅 하시겠습니까? >> "; 
		Sleep(2000);

		//컴퓨터 판단....

		//판단에 의해 return 1, return 2;
	}
}

void GameManager::PlayerVetting(Card ** _card, Player * _player, Player * _comPlayer)
{

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

void GameManager::SetLeftMoneyIsTrue(bool _data)
{
	this->leftMoneyIsTure = _data;
}

//게임 판돈
void GameManager::PullGameTotalMoney(int _pullMoney)
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

bool GameManager::GetLeftMoneyIsTrue()
{
	return this->leftMoneyIsTure;
}

int GameManager::GetTotalPlayerNumber()
{
	return this->totalPlayerNumber;
}

#pragma endregion

#pragma endregion