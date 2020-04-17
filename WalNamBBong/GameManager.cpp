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
			//cout << "1" << endl;
		}
		else
		{
			//살아있으면 나눠준다.
			if (_comPlayer[j - 1].GetIsAlive() == true) {
				_comPlayer[j - 1].GiveMeCard(_card[this->x][this->y]);
				(this->y)++;
			}
			//cout << "2" << endl;
		}

		if ((j+1) % this->GetTotalPlayerNumber() == 0)
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

		Sleep(SLEEP_NUMBER);

		if ((_player->GetFirstCard().cardNumber == 13) || (_player->GetSecondCard().cardNumber == 13))
		{
			if ((_player->GetFirstCard().cardNumber == 13) && (_player->GetSecondCard().cardNumber == 13)) //빗자루.
			{
				cout << " 13이 두 개!! " << endl;
				cout << " 빗 자 루 !!" << endl;
				this->sackSSleE = true;
				return 0; //빗자루로 승리.
			}
			else
			{
				//cout << "13..다이.." << endl;
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
			cout << "패가 좋지 않군.. 다이!" << endl;
			return 2;
		}
	}
	else
	{
		if (_comPlayer[j - 1].GetIsAlive() == true)
		{
			cout << _comPlayer[j - 1].GetName() << "님 차례입니다." << endl;
			cout << endl;
			cout << _comPlayer[j - 1].GetName() << "님이 가진 카드 : " << _comPlayer[j - 1].GetFirstCard().type << " " << _comPlayer[j - 1].GetFirstCard().cardNumber
				<< ", " << _comPlayer[j - 1].GetSecondCard().type << " " << _comPlayer[j - 1].GetSecondCard().cardNumber << endl;

			if ((_comPlayer[j - 1].GetFirstCard().cardNumber == 13) || (_comPlayer[j - 1].GetSecondCard().cardNumber == 13))
			{
				if ((_comPlayer[j - 1].GetFirstCard().cardNumber == 13) && (_comPlayer[j - 1].GetSecondCard().cardNumber == 13)) //빗자루.
				{
					cout << " 13이 두 개!! " << endl;
					cout << " 빗 자 루 !!" << endl;
					this->sackSSleE = true;
					//_player->PullMoney(this->GetGameTotalMoney());

					return 0; //빗자루로 승리.
				}
				else
				{
					return 2;
				}
			}

			cout << endl;
			cout << " < 베팅 여부 결정 > " << endl;
			cout << endl;

			Sleep(SLEEP_NUMBER);

			//컴퓨터 판단....
			_comPlayer[j - 1].SetJudgement(_comPlayer[j - 1].JudgementFunction(this));

			//판단에 의해 return 1, return 2; // 1은 베팅하기 2는 다이
			return ((rand() % 80) < _comPlayer[j - 1].GetJudgement()) ? 1 : 2;
		}
	}

	return -1;
}

void GameManager::PlayerVetting(Card ** _card, Player * _player, Player * _comPlayer)
{
	int inputVetting;

	if (this->GetFirstPlayer() == 0)
	{
		system("cls");
		cout << endl;
		cout << "얼마를 베팅 하시겠습니까? (판돈 : " << this->GetGameTotalMoney() << "원, 보유금 : " << _player->GetMoney() << "원) " << endl;

		do
		{
			cout << "판돈과 보유금보다 적게 입력해 주세요 >> ";
			cin >> inputVetting;
		} while ((inputVetting > this->GetGameTotalMoney()) || (inputVetting > _player->GetMoney()) || inputVetting <= 0);

		//일단 베팅한 금액만큼 플레이어 소유금 차감.
		_player->GameVetting(inputVetting, this);

		//게임 메니져의 판돈이 증가.
		this->PullGameTotalMoney(inputVetting);

		//카드 오픈
		if (NextCardOpen(_card, _player, _comPlayer) == true)
		{
			Sleep(3000);
			cout << "베팅한 금액 * 2 ( " << inputVetting << " * 2 ) = " << inputVetting * 2 << "원 획득!" << endl;
			_player->PullMoney(inputVetting * 2);

			Sleep(SLEEP_NUMBER);
			cout << _player->GetName() << "님 보유 금액 : " << _player->GetMoney() << endl;

			Sleep(2000);
			this->PullGameTotalMoney(-inputVetting * 2);

			cout << "남은 판돈 : " << this->GetGameTotalMoney() << "원 " << endl;
			if (this->GetGameTotalMoney() <= 0)
				this->sackSSleE = true;
			Sleep(SLEEP_NUMBER);
		}
		else
		{
			Sleep(SLEEP_NUMBER);
			if ( _player->GetMoney() < 300 )
			{
				cout << "금액이 300원 미만이 되어 게임 패배... " << endl;
				exit(1);
			}
		}
	}
	else
	{
		int tmp;
		int tmp2;
		cout << "얼마를 베팅 하시겠습니까? (판돈 : " << this->GetGameTotalMoney() << "원, 보유금 : " << _comPlayer[this->GetFirstPlayer()-1].GetMoney() << "원) " << endl;

		cout << "처리중...." << endl;
		Sleep(SLEEP_NUMBER);

		cout << _comPlayer[this->GetFirstPlayer() - 1].GetName() << "님이 입력한 금액 : ";
		tmp = _comPlayer[this->GetFirstPlayer() - 1].GetJudgement(); //이길 확률 저장
		
		if (this->GetGameTotalMoney() <= _comPlayer[this->GetFirstPlayer() - 1].GetMoney())
		{
			if (tmp < 20)
			{
				tmp2 = ( this->GetGameTotalMoney() / 10 ) * 2;
			}
			else if (tmp < 30)
			{
				tmp2 = (int)(this->GetGameTotalMoney() * 0.4) + rand() % tmp;
			}
			else if (tmp < 50)
				tmp2 = (int)( this->GetGameTotalMoney() * 1 / 3) + rand() % tmp ;
			else
				tmp2 = this->GetGameTotalMoney();			//올인
		}
		else
		{
			if (tmp < 20)
			{
				tmp2 = (_comPlayer[this->GetFirstPlayer() - 1].GetMoney() / 10) * 2;
			}
			else if (tmp < 30)
			{
				tmp2 = (int)(_comPlayer[this->GetFirstPlayer() - 1].GetMoney() * 0.4) + rand() % tmp;
			}
			else if (tmp < 50)
				tmp2 = (int)(_comPlayer[this->GetFirstPlayer() - 1].GetMoney() * 1 / 3) + rand() % tmp;
			else
				tmp2 = _comPlayer[this->GetFirstPlayer() - 1].GetMoney(); //올인
		}

		cout << tmp2 << endl;
		
		////얼마 베팅할지 정해준다.	
		//if (tmp < 20)
		//{
		//	tmp2 = rand() % tmp + 100; //최소금액 100설정.
		//}
		//else if (tmp < 40)
		//{
		//	tmp2 = rand() % tmp + 200; //최소금액 200설정.
		//}
		//else if (tmp < 60)
		//{
		//	tmp2 = rand() % tmp + 300; //최소금액 300설정.
		//}
		//else if (tmp < 70)
		//{
		//	tmp2 = rand() % tmp + 400;
		//}
		//else
		//{
		//	tmp2 = rand() % tmp + rand() % 100 + 400;
		//}

		//일단 베팅한 금액만큼 플레이어 소유금 차감.
		_comPlayer[this->GetFirstPlayer() - 1].GameVetting(tmp2, this);

		//게임 메니져의 판돈이 증가.
		this->PullGameTotalMoney(tmp2);
		
		//카드 오픈
		if (NextCardOpen(_card, _player, _comPlayer) == true)
		{
			Sleep(SLEEP_NUMBER);
			cout << "베팅한 금액 * 2 ( " << tmp2 << " * 2 ) = " << tmp2 * 2 << "원 획득!" << endl;
			_comPlayer[this->GetFirstPlayer() - 1].PullMoney(tmp2 * 2);

			cout << _comPlayer[this->GetFirstPlayer() - 1].GetName() << "님 보유 금액 : " << _comPlayer[this->GetFirstPlayer() - 1].GetMoney();

			this->PullGameTotalMoney(-tmp2 * 2);

			cout << endl;
			cout << "남은 판돈 : " << this->GetGameTotalMoney() << "원 " << endl;

			if (this->GetGameTotalMoney() <= 0)
				this->sackSSleE = true;
		}
		else
		{
			Sleep(SLEEP_NUMBER);
			if (_comPlayer[this->GetFirstPlayer() - 1].GetMoney() < 300)
			{
				cout << "금액이 300원 미만이 되어 게임 탈락... " << endl;
				this->SetRemainingPlayerNumber((this->GetRemainingPlayerNumber()) - 1);
				_comPlayer[this->GetFirstPlayer() - 1].SetIsAlive(false);
			}
		}

	}
}

//카드 오픈 구간.
bool GameManager::NextCardOpen(Card ** _card, Player * _player, Player * _comPlayer)
{
	this->SetRemainingCardNumeber(this->GetRemainingCardNumber()-1);

	int tmp = _card[this->x][this->y].cardNumber;
	cout << endl;
	cout << "오픈한 카드 -> " << _card[this->x][this->y].type << " " << tmp << endl;
	Sleep(2000);
	this->y++;
	if (this->y > CARD_EACH_NUMBER - 1)
	{
		this->y = 0;
		this->x++;
	}

	Sleep(SLEEP_NUMBER);
	cout << endl;
	if (this->GetFirstPlayer() == 0)
	{
		
		if (tmp > _player->GetFirstCard().cardNumber && tmp < _player->GetSecondCard().cardNumber)
		{
			
			cout << _player->GetFirstCard().cardNumber << " < " << tmp << " < " << _player->GetSecondCard().cardNumber << endl;
			cout << "베팅 결과 : 성공!! " << endl;


			return true;
		}
		else if (tmp < _player->GetFirstCard().cardNumber && tmp > _player->GetSecondCard().cardNumber)
		{
			//성공!!
			
			cout << _player->GetSecondCard().cardNumber<< " < " << tmp << " < " << _player->GetFirstCard().cardNumber << endl;
			cout << "베팅 결과 : 성공!! " << endl;
			return true;
		}
		else
		{
			cout << "베팅 결과 : 실패... " << endl;
			Sleep(SLEEP_NUMBER);
			cout << _player->GetName() << "님 보유 금액 : " << _player->GetMoney() << endl;
			//베팅 실패..
			return false;
		}
	}
	else
	{
		if (tmp > _comPlayer[this->GetFirstPlayer()-1].GetFirstCard().cardNumber && tmp < _comPlayer[this->GetFirstPlayer() - 1].GetSecondCard().cardNumber)
		{
			cout << _comPlayer[this->GetFirstPlayer() - 1].GetFirstCard().cardNumber << " < " << tmp << " < " << _comPlayer[this->GetFirstPlayer() - 1].GetSecondCard().cardNumber << endl;
			cout << "베팅 결과 : 성공!! " << endl;

			return true;
		}
		else if (tmp < _comPlayer[this->GetFirstPlayer() - 1].GetFirstCard().cardNumber && tmp > _comPlayer[this->GetFirstPlayer() - 1].GetSecondCard().cardNumber)
		{
			//성공!!
			cout << _comPlayer[this->GetFirstPlayer() - 1].GetSecondCard().cardNumber << " < " << tmp << " < " << _comPlayer[this->GetFirstPlayer() - 1].GetFirstCard().cardNumber << endl;
			cout << "베팅 결과 : 성공!! " << endl;
			return true;
		}
		else
		{
			cout << "베팅 결과 : 실패... " << endl;
			Sleep(SLEEP_NUMBER);
			cout << _comPlayer[this->GetFirstPlayer() - 1].GetName() << "님 보유 금액 : " << _comPlayer[this->GetFirstPlayer() - 1].GetMoney() << endl;
			//베팅 실패..
			return false;
		}
	}
	cout << endl;
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