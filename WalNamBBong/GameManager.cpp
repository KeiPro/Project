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
			//cout << "1" << endl;
		}
		else
		{
			//��������� �����ش�.
			if (_comPlayer[j - 1].GetIsAlive() == true) {
				_comPlayer[j - 1].GiveMeCard(_card[this->x][this->y]);
				(this->y)++;
			}
			//cout << "2" << endl;
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
				cout << "13..����.." << endl;
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
			cout << "�а� ���� �ʱ�.. ����!" << endl;
			return 2;
		}
	}
	else
	{
		cout << _comPlayer[j - 1].GetName() << "�� �����Դϴ�." << endl;
		cout << endl;
		cout << _comPlayer[j - 1].GetName() << "���� ���� ī�� : " << _comPlayer[j-1].GetFirstCard().type << " " << _comPlayer[j - 1].GetFirstCard().cardNumber 
			 << ", " << _comPlayer[j - 1].GetSecondCard().type << " " << _comPlayer[j - 1].GetSecondCard().cardNumber << endl;

		if ((_comPlayer[j - 1].GetFirstCard().cardNumber == 13) || (_comPlayer[j - 1].GetSecondCard().cardNumber == 13))
		{
			if ((_comPlayer[j - 1].GetFirstCard().cardNumber == 13) && (_comPlayer[j - 1].GetSecondCard().cardNumber == 13)) //���ڷ�.
			{
				cout << " 13�� �� ��!! " << endl;
				cout << " �� �� �� !!" << endl;

				//_player->PullMoney(this->GetGameTotalMoney());

				return 0; //���ڷ�� �¸�.
			}
			else
			{
				cout << "13 �ϳ�.. ����.." << endl;
				return 2;
			}
		}

		cout << "���� �Ͻðڽ��ϱ�? >> "; 
		Sleep(2000);

		//��ǻ�� �Ǵ�....
		_comPlayer[j - 1].SetJudgement(_comPlayer[j - 1].JudgementFunction(this));

		//�Ǵܿ� ���� return 1, return 2; // 1�� �����ϱ� 2�� ����
		return ((rand() % 100) < _comPlayer[j - 1].GetJudgement()) ? 1 : 2;
	}
}

void GameManager::PlayerVetting(Card ** _card, Player * _player, Player * _comPlayer)
{
	int inputVetting;

	if (this->GetFirstPlayer() == 0)
	{
		cout << "�󸶸� ���� �Ͻðڽ��ϱ�? (�ǵ� : " << this->GetGameTotalMoney() << "��, ������ : " << _player->GetMoney() << "��) " << endl;

		do
		{
			cout << "�ǵ��� �����ݺ��� �۰� �Է��� �ּ��� >> ";
			cin >> inputVetting;
		} while ((inputVetting > this->GetGameTotalMoney()) || (inputVetting > _player->GetMoney()) || inputVetting <= 0);

		//�ϴ� ������ �ݾ׸�ŭ �÷��̾� ������ ����.
		_player->GameVetting(inputVetting, this);

		//���� �޴����� �ǵ��� ����.
		this->PullGameTotalMoney(inputVetting);

		//ī�� ����
		if (NextCardOpen(_card, _player, _comPlayer) == true)
		{
			Sleep(2000);
			cout << "������ �ݾ� * 2 ( " << inputVetting << " * 2 ) = " << inputVetting * 2 << "�� ȹ��!" << endl;
			_player->PullMoney(inputVetting * 2);

			cout << _player->GetName() << "�� ���� �ݾ� : " << _player->GetMoney();

			this->PullGameTotalMoney(-inputVetting * 2);

			cout << "���� �ǵ� : " << this->GetGameTotalMoney() << "�� " << endl;
		}
		else
		{
			Sleep(2000);
			if ( _player->GetMoney() < 300 )
			{
				cout << "�ݾ��� 300�� �̸��� �Ǿ� ���� �й�... " << endl;
				exit(1);
			}
		}
	}
	else
	{
		int tmp;
		int tmp2;
		cout << "�󸶸� ���� �Ͻðڽ��ϱ�? (�ǵ� : " << this->GetGameTotalMoney() << "��, ������ : " << _comPlayer[this->GetFirstPlayer()-1].GetMoney() << "��) " << endl;

		cout << "ó����...." << endl;
		Sleep(2000);

		tmp = _comPlayer[this->GetFirstPlayer() - 1].GetJudgement(); //�̱� Ȯ�� ����
		
		if (this->GetGameTotalMoney() <= _comPlayer[this->GetFirstPlayer() - 1].GetMoney())
		{
			tmp2 = this->GetGameTotalMoney();
		}
		else
			tmp2 = 100;
		
		////�� �������� �����ش�.	
		//if (tmp < 20)
		//{
		//	tmp2 = rand() % tmp + 100; //�ּұݾ� 100����.
		//}
		//else if (tmp < 40)
		//{
		//	tmp2 = rand() % tmp + 200; //�ּұݾ� 200����.
		//}
		//else if (tmp < 60)
		//{
		//	tmp2 = rand() % tmp + 300; //�ּұݾ� 300����.
		//}
		//else if (tmp < 70)
		//{
		//	tmp2 = rand() % tmp + 400;
		//}
		//else
		//{
		//	tmp2 = rand() % tmp + rand() % 100 + 400;
		//}

		//�ϴ� ������ �ݾ׸�ŭ �÷��̾� ������ ����.
		_comPlayer[this->GetFirstPlayer() - 1].GameVetting(tmp2, this);

		//���� �޴����� �ǵ��� ����.
		this->PullGameTotalMoney(tmp2);

		//ī�� ����
		if (NextCardOpen(_card, _player, _comPlayer) == true)
		{
			Sleep(2000);
			cout << "������ �ݾ� * 2 ( " << tmp2 << " * 2 ) = " << tmp2 * 2 << "�� ȹ��!" << endl;
			_comPlayer[this->GetFirstPlayer() - 1].PullMoney(tmp2 * 2);

			cout << _comPlayer[this->GetFirstPlayer() - 1].GetName() << "�� ���� �ݾ� : " << _comPlayer[this->GetFirstPlayer() - 1].GetMoney();

			this->PullGameTotalMoney(-tmp2 * 2);

			cout << "���� �ǵ� : " << this->GetGameTotalMoney() << "�� " << endl;
		}
		else
		{
			Sleep(2000);
			if (_comPlayer[this->GetFirstPlayer() - 1].GetMoney() < 300)
			{
				cout << "�ݾ��� 300�� �̸��� �Ǿ� ���� Ż��... " << endl;
				_comPlayer[this->GetFirstPlayer() - 1].SetIsAlive(false);
			}
		}

	}
}

//ī�� ���� ����.
bool GameManager::NextCardOpen(Card ** _card, Player * _player, Player * _comPlayer)
{
	int tmp = _card[this->x][this->y].cardNumber;
	cout << "������ ī�� -> " << _card[this->x][this->y].type << " " << tmp << endl;
	
	this->y++;
	if (this->y > CARD_EACH_NUMBER - 1)
	{
		this->y = 0;
		this->x++;
	}

	Sleep(2000);
	if (this->GetFirstPlayer() == 0)
	{
		if (tmp > _player->GetFirstCard().cardNumber && tmp < _player->GetSecondCard().cardNumber)
		{
			cout << "���� ����!! " << endl;

			return true;
		}
		else if (tmp < _player->GetFirstCard().cardNumber && tmp > _player->GetSecondCard().cardNumber)
		{
			//����!!
			cout << "���� ����!! " << endl;
			return true;
		}
		else
		{
			cout << "���� ����... " << endl;
			//���� ����..
			return false;
		}
	}
	else
	{
		if (tmp > _comPlayer[this->GetFirstPlayer()-1].GetFirstCard().cardNumber && tmp < _comPlayer[this->GetFirstPlayer() - 1].GetSecondCard().cardNumber)
		{
			cout << "���� ����!! " << endl;

			return true;
		}
		else if (tmp < _comPlayer[this->GetFirstPlayer() - 1].GetFirstCard().cardNumber && tmp > _comPlayer[this->GetFirstPlayer() - 1].GetSecondCard().cardNumber)
		{
			//����!!
			cout << "���� ����!! " << endl;
			return true;
		}
		else
		{
			cout << "���� ����... " << endl;
			//���� ����..
			return false;
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

void GameManager::SetTurn(int _turn)
{
	this->turn = _turn;
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

int GameManager::GetTurn()
{
	return this->turn;
}

int GameManager::GetTotalPlayerNumber()
{
	return this->totalPlayerNumber;
}

#pragma endregion

#pragma endregion