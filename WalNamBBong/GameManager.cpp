#include "GameManager.h"
#include "Player.h"

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
void GameManager::CardDividing(Card** _card, Player* _player, Player* _comPlayer)
{
	int j = this->GetFirstPlayer(); //�� �÷��̾��� �ε����� �����´�. 0�̸� �÷��̾�, 1 ~ 3 : ��ǻ��1,2,3
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
			//��������� �����ش�.
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

//���ʿ� ���� ������ ó���� �Լ�
int GameManager::PlayerGameStart(Card ** _card, Player * _player, Player * _comPlayer)
{
	int vettingCall;
	int j = this->GetFirstPlayer();

	if (j == 0)
	{
		cout << _player->GetName() << "�� �����Դϴ�." << endl;
		cout << endl;
		cout << _player->GetName() << "���� ���� ī�� : " << _player->GetFirstCard().type << " " << _player->GetFirstCard().cardNumber << ", " << 
			_player->GetSecondCard().type << " " << _player->GetSecondCard().cardNumber << endl;

		Sleep(2000);

		if ((_player->GetFirstCard().cardNumber == 13) || (_player->GetSecondCard().cardNumber == 13))
		{
			if ((_player->GetFirstCard().cardNumber == 13) && (_player->GetSecondCard().cardNumber == 13)) //���ڷ�.
			{
				cout << " 13�� �� ��!! " << endl;
				cout << " �� �� �� !!" << endl;
				
				return 0; //���ڷ�� �¸�.
			}
			else
			{
				cout << "����.." << endl;
				return 2;
			}
		}

		cout << "���� �Ͻðڽ��ϱ�? 1) �� 2) �ƴϿ� >> ";
		cin >> vettingCall;

		if (vettingCall == 1)
		{
			return 1;
		}
		else
		{
			cout << "����.." << endl;
			return 2;
		}
	}
	else
	{
		cout << _comPlayer[j - 1].GetName() << "�� �����Դϴ�." << endl;
		cout << endl;
		cout << _comPlayer[j - 1].GetName() << "���� ���� ī�� : " << _comPlayer[j-1].GetFirstCard().type << " " << _comPlayer[j - 1].GetFirstCard().cardNumber 
			 << ", " << _comPlayer[j - 1].GetSecondCard().type << " " << _comPlayer[j - 1].GetSecondCard().cardNumber << endl;

		if ((_comPlayer[j - 1].GetFirstCard().cardNumber == 13) || (_comPlayer[j - 1].GetFirstCard().cardNumber == 13))
		{
			if ((_comPlayer[j - 1].GetFirstCard().cardNumber == 13) && (_comPlayer[j - 1].GetFirstCard().cardNumber == 13)) //���ڷ�.
			{
				cout << " 13�� �� ��!! " << endl;
				cout << " �� �� �� !!" << endl;

				_player->PullMoney(this->GetGameTotalMoney());

				return 0; //���ڷ�� �¸�.
			}
			else
			{
				cout << "����.." << endl;
				return 2;
			}
		}

		cout << "���� �Ͻðڽ��ϱ�? >> "; 
		Sleep(2000);

		//��ǻ�� �Ǵ�....

		//�Ǵܿ� ���� return 1, return 2;
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

//���� �ǵ�
void GameManager::PullGameTotalMoney(int _pullMoney)
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