#include "GameController.h"
#include "Dealer.h"

void GameController::InputNamePrint(Player* player)
{
	string name;
	cout << "플레이어의 이름을 입력해 주세요 : ";
	cin >> name;

	player->SetName(name);
}

void GameController::InputTotalNum()
{
	cout << "총 플레이어의 수를 입력해 주세요(본인 포함) : ";
	cin >> inputTotalNum;
	
	if (inputTotalNum > 17)
	{
		realPlayerNum = 17;
	}

	comPlayer = new Player[inputTotalNum -1];

	switch (RegisterComName())
	{
		case 1: //컴퓨터 이름 자동생성하기
			cout << endl;
			cout << ">> 컴퓨터이름 자동 생성하기를 선택하셨습니다." << endl;
			Sleep(1000);
			cout << ">> 잠시만 기다려 주세요... " << endl;
			Sleep(1000);
			AutoRegisterComName(inputTotalNum-1);
			break;

		case 2: //컴퓨터 이름 수기 입력.
			InputRegisterComName(inputTotalNum-1);
			break;

		default:

			break;
	}
	
}

int GameController::RegisterComName()
{
	string inputComName;
	int inputNum;

	system("cls");

	cout << " < 컴퓨터 이름 설정 > " << endl;
	cout << endl;
	cout << "1)컴퓨터 이름 자동 생성하기" << endl;
	cout << "2)컴퓨터 이름 직접 입력하기(수정중...)" << endl;
	cout << endl;

	cout << "--> 번호를 입력해 주세요 : ";

	while (1)
	{
		cin >> inputNum;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');

			cout << "번호를 다시 입력해 주세요 : ";
		}
		else
		{
			if (inputNum == 1)
			{
				break;
			}
			else
			{
				cout << "번호를 다시 입력해 주세요 : ";
				continue;
			}
		}
		
	}

	return inputNum;
}

void GameController::AutoRegisterComName(int _totalNumber)
{
	string autoName[30] = {"탈론", "리븐", "아무무", "카밀", "블라디미르", "카사딘", "피즈", "잭스", "라이즈", "럼블",
							"레넥톤", "나서스", "마오카이", "말파이트", "럭스", "오리아나", "뽀삐", "자이라", "제드", "케이틀린",
							"녹턴", "카이사", "아펠리오스", "판테온", "키아나", "신드라", "제라스", "카시오페아", "징크스", "베인"};

	int* number = new int[_totalNumber];

	//겹치지 않게 번호 설정
	for (int i = 0; i < _totalNumber; i++)
	{
		number[i] = rand() % 30;

		for (int j = 0; j < i; j++)
		{
			if (number[j] == number[i])
				i--;
		}
	}

	//이름 설정
	for (int i = 0; i < _totalNumber; i++)
	{
		comPlayer[i].SetName(autoName[number[i]]);
	}

	system("cls");
	cout << "\t < 자동생성 완료! > " << endl;
	cout << endl;
	Sleep(1000);
	//이름 설정
	for (int i = 0; i < _totalNumber; i++)
	{
		cout << "\t" << i+1 << "번 상대 이름 : " << comPlayer[i].GetName() << endl;
		Sleep(100);
	}

	Sleep(1000);
	cout << endl;
	cout << "계속 진행하려면 아무키나 입력하세요." << endl;

	int ch = _getch();

	delete[] number;
}

void GameController::InputRegisterComName(int _totalNumber)
{
	string inputName;
	cout << " < 수기 입력 > " << endl;
	for (int i = 0; i < _totalNumber; i++)
	{
		//등록하기
		//다시 입력하기
	}
}

void GameController::TurnSetting(Player* player, Player** phead)
{
	system("cls"); 
	cout << endl;
	cout << "\t < 순서를 정합니다. > " << endl;
	cout << endl;

	int* dynamicNum = new int[inputTotalNum]; //

	//랜덤하게 번호를 뽑고
	for (int i = 0; i < inputTotalNum; i++)
	{
		dynamicNum[i] = rand() % inputTotalNum;

		for (int j = 0; j < i; j++)
		{
			if (dynamicNum[i] == dynamicNum[j])
			{
				i--;
			}
		}
	}

	//플레이어에게 랜덤하게 번호를 부여
	player->SetTurn(dynamicNum[inputTotalNum-1]);
	for (int i = 0; i < inputTotalNum-1; i++)
	{
		comPlayer[i].SetTurn(dynamicNum[i]);
	}

	cout << ">> \t" << player->GetName() << "님 순서 : " << player->GetTurn()+1 << "번" << endl;
	for (int i = 0; i < inputTotalNum-1; i++)
	{
		cout << "\t" << comPlayer[i].GetName() << "님 순서 : " << comPlayer[i].GetTurn()+1 << "번" << endl;
	}

	cout << endl;
	cout << endl;
	cout << " >> 아무키나 입력해 주세요.";
	
	char ch = _getch();

#pragma region Circular Linked List 구현
	int count = 0;
	Player* p = nullptr;

	//최대 가능 인원.
	for (int i = 0; i < inputTotalNum; i++)
	{
		for (int j = 0; j < inputTotalNum - 1; j++)
		{
			if (comPlayer[j].GetTurn() == i || player->GetTurn() == i)
			{
				if (comPlayer[j].GetTurn() == i)
				{
					if (*phead == nullptr)
					{
						*phead = (comPlayer + j);
						p = *phead;
						break;
					}
					else
					{
						if (p->GetLink() == nullptr)
						{
							p->SetLink(comPlayer + j);
							p = p->GetLink();
							break;
						}
					}
				}
				else
				{
					if (*phead == nullptr)
					{
						*phead = player;
						p = *phead;
						break;
					}
					else
					{
						if (p->GetLink() == nullptr)
						{
							p->SetLink(player);
							p = p->GetLink();
							break;
						}
					}
				}
			}
		}

		count++;
		if (count == 17)
			break;
	}

	p->SetLink(*phead);
	p = p->GetLink();

#pragma endregion
	
#pragma region 순서 소트 - 순서대로 Print하는 곳

	Player* tmpPlayer = new Player[inputTotalNum];
	Player tmp;
	
	for (int i = 0; i < inputTotalNum-1; i++)
	{
		tmpPlayer[i] = comPlayer[i];
	}
	tmpPlayer[inputTotalNum - 1] = *player;
	
	for (int i = 0; i < inputTotalNum; i++)
	{
		for (int j = 0; j < inputTotalNum; j++)
		{
			if ( (i == tmpPlayer[j].GetTurn()) && ( i != j ) )
			{
				tmp = tmpPlayer[j];
				tmpPlayer[j] = tmpPlayer[i];
				tmpPlayer[i] = tmp;
				break;
			}
		}

		system("cls");
		cout << endl;
		cout << "\t\t < 순서 정렬 > " << endl;
		cout << endl;
		for (int i = 0; i < inputTotalNum; i++)
		{
			if (i == player->GetTurn())
			{
				if (tmpPlayer[i].GetName().size() < 4)
				{
					cout << "\t\b\b\b>>> " << tmpPlayer[i].GetName() << "님 \t\t\t 순서 : " << tmpPlayer[i].GetTurn() + 1 << "번" << endl;
				}
				else
				{
					cout << "\t\b\b\b>>> " << tmpPlayer[i].GetName() << "님 \t\t 순서 : " << tmpPlayer[i].GetTurn() + 1 << "번" << endl;
				}
			}
			else
			{
				cout << "\t " << tmpPlayer[i].GetName() << "님 \t\t 순서 : " << tmpPlayer[i].GetTurn() + 1 << "번" << endl;
			}
		}
		Sleep(10);
	}

	system("cls");

	cout << endl;
	cout << "\t\t < 순서 정렬 > " << endl;
	cout << endl;

	for (int i = 0; i < inputTotalNum; i++)
	{
		if (i < realPlayerNum)
		{
			if (i == player->GetTurn())
			{
				if (tmpPlayer[i].GetName().size() < 4)
				{
					cout << "\t\b\b\b>>> " << tmpPlayer[i].GetName() << "님 \t\t\t 순서 : " << tmpPlayer[i].GetTurn() + 1 << "번" << endl;
				}
				else
				{
					cout << "\t\b\b\b>>> " << tmpPlayer[i].GetName() << "님 \t\t 순서 : " << tmpPlayer[i].GetTurn() + 1 << "번" << endl;
				}
			}
			else
			{
				cout << "\t " << tmpPlayer[i].GetName() << "님 \t\t 순서 : " << tmpPlayer[i].GetTurn() + 1 << "번" << endl;
			}
		}
		else
		{
			if (i == player->GetTurn())
			{
				if (tmpPlayer[i].GetName().size() < 4)
				{
					cout << "\t\b\b\b>>> " << tmpPlayer[i].GetName() << "님 \t\t\t 순서 : " << tmpPlayer[i].GetTurn() + 1 << "번 -- 대기" << endl;
				}
				else
				{
					cout << "\t\b\b\b>>> " << tmpPlayer[i].GetName() << "님 \t\t 순서 : " << tmpPlayer[i].GetTurn() + 1 << "번 -- 대기" << endl;
				}
			}
			else
			{
				cout << "\t " << tmpPlayer[i].GetName() << "님 \t\t 순서 : " << tmpPlayer[i].GetTurn() + 1 << "번 -- 대기" << endl;
			}
		}
	}

	cout << endl;
	cout << " >> 아무키나 입력해 주세요.";
	
	ch = _getch();

	cout << endl;

	//cout << endl;
	//for (int i = 0; i < inputTotalNum; i++)
	//{
	//	cout << p->GetName() << ", ";
	//	p = p->GetLink();
	//	if ((i + 1) % 5 == 0)
	//		cout << endl;
	//}

	//cout << player->GetName() << endl; 
	
	delete[] tmpPlayer;


#pragma endregion

	delete[] dynamicNum;
}

void GameController::InputMoney(Player** phead, Player* p, int _myMoney)
{
	p->SetMyMoney(_myMoney);
	p = p->GetLink();

	while (p != *phead)
	{
		p->SetMyMoney(_myMoney);
		p = p->GetLink();
	}
}

void GameController::BaseBetting(Player* (&phead), Player* (&p), Dealer &dealer)
{
	cout << endl;
	cout << "기본 베팅금액 입력 >> ";
	cin >> this->baseInputMoney;
	cout << endl;
	cout << "기본 베팅금액이 " << this->baseInputMoney << "원으로 설정되었습니다. " << endl;
	Sleep(1000);
	
	cout << "모든 플레이어 금액 -" << this->baseInputMoney << "원 적용." << endl;

	p->SetMyMoney(p->GetMyMoney()- this->baseInputMoney);
	dealer.AddingTotalMoney(this->baseInputMoney);
	p = p->GetLink();

	while ( p != phead )
	{
		p->SetMyMoney(p->GetMyMoney() - this->baseInputMoney);
		dealer.AddingTotalMoney(this->baseInputMoney);
		p = p->GetLink();
	}
}

void GameController::bettingMoney(Player** phead, Player* p)
{
	//cout << "얼마를 베팅하시겠습니까"
}

void GameController::CurrentStatePrint(Player* (&phead), Player* (&p), Dealer &dealer)
{
	system("cls");
	cout << "\t=========================================" << endl;
	cout << "\t|   \t\t\t\t\t|" << endl;
	cout << "\t|\t    < 판돈 : " << dealer.GetGameTotalMoney() << " >\t\t|" << endl;
	cout << "\t|   \t\t\t\t\t|" << endl;
	cout << "\t=========================================" << endl;
	cout << "\t|\t\b\b아이디\t|\t남은 금액\t|" << endl;
	cout << "\t=========================================" << endl;
	
	if (p->GetMyMoney() <= this->baseInputMoney)
	{
		if (p->GetName().size() < 3)
		{
			cout << "\t|    " << p->GetName() << "\t\t|\t\t\b\b\b\b" << p->GetMyMoney() << "\t (out)  |" << endl;
		}
		else
		{
			cout << "\t|    " << p->GetName() << "\t|\t\t\b\b\b\b" << p->GetMyMoney() << "\t (out)  |" << endl;
		}
	}
	else
	{
		if (p->GetName().size() < 3)
		{
			cout << "\t|    " << p->GetName() << "\t\t|\t\t\b\b\b\b" << p->GetMyMoney() << "\t|" << endl;
		}
		else
		{
			cout << "\t|    " << p->GetName() << "\t|\t\t\b\b\b\b" << p->GetMyMoney() << "\t|" << endl;
		}
	}
	p = p->GetLink();

	while (p != phead)
	{
		if (p->GetMyMoney() <= this->baseInputMoney)
		{
			if (p->GetName().size() < 3)
			{
				cout << "\t|    " << p->GetName() << "\t\t|\t\t\b\b\b\b" << p->GetMyMoney() << "\t (out)  |" << endl;
			}
			else
			{
				cout << "\t|    " << p->GetName() << "\t|\t\t\b\b\b\b" << p->GetMyMoney() << "\t (out)  |" << endl;
			}
		}
		else
		{
			if (p->GetName().size() < 3)
			{
				cout << "\t|    " << p->GetName() << "\t\t|\t\t\b\b\b\b" << p->GetMyMoney() << "\t|" << endl;
			}
			else
			{
				cout << "\t|    " << p->GetName() << "\t|\t\t\b\b\b\b" << p->GetMyMoney() << "\t|" << endl;
			}
		}
		p = p->GetLink();
	}
	cout << "\t=========================================" << endl;

	cout << endl;
	cout << "계속 진행하려면 아무키를 눌러주세요." << endl;
	char ch = _getch();
}

void GameController::BettingYesOrNo(Player *(&phead), Player *(&p), int& playerNumber, Dealer &dealer, Player* player)
{
	int bettingMoney;
	int bettingYesOrNo;
	int gabPropability;
	bool bettingCall;

	system("cls");
	cout << endl;
	cout << "\t\t< " << (playerNumber+1) << "번째 플레이어 > " << endl;
	cout << endl;
	if(p == player)
	{
		cout << "\t\t>> 당신 차례 입니다 <<" << endl;
		cout << endl;
	}
	cout << "\t\t "<< p->GetName() <<" 플레이어" << endl;
	cout << endl;
	cout << "\t\t  판돈 : "<< dealer.GetGameTotalMoney() << "원" << endl;
	cout << endl;
	cout << "\t=======================================" << endl;
	cout << "\t|   보유 카드\t|\t보유 금액     |" << endl;
	cout << "\t=======================================" << endl;
	cout << "\t|  " << p->GetMyFirstCard().GetShape() << p->GetMyFirstCard().GetNum() << 
		"\t|  "<< p->GetMySecondCard().GetShape() << p->GetMySecondCard().GetNum() <<"\t|\t "<< p->GetMyMoney() <<"원\t\t\b\b|" << endl;
	cout << "\t=======================================" << endl;
	cout << endl;
	cout << "\t 베팅 하시겠습니까? 1)예 2)아니오 >> ";
	
	//플레이어면 선택하도록.
	if (p == player)
	{
		while (1)
		{
			cin >> bettingYesOrNo;

			if (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
				cout << "\t 다시 입력해 주세요." << endl;
				Sleep(1000);
			}
			else
			{
				break;
			}
		}

	}
	else //컴퓨터면 판단해서 선택하도록.
	{
		//판단해서
		gabPropability = TwoNumberGap(p->GetMyFirstCard().GetNum(), p->GetMySecondCard().GetNum());
		bettingCall = ComJudgeFunction(gabPropability);
		
		if (bettingCall == true) //베팅 yes
		{
			cout << "1)예" << endl;
			cout << endl;
			cout << "\t(" << "컴퓨터가 판단한 확률 : " << gabPropability << "(%))" ;
			Sleep(1000);
			bettingMoney = HowMuchBetting(p, gabPropability, dealer);
			cout << "\t 베팅 금액 : " << bettingMoney << "원" << endl;
			Sleep(1000);			
			/////////////////////////////////////////시작 
		}
		else // 베팅 no
		{
			cout << "2)아니오";
			//Sleep();
		}
	}

	p = p->GetLink(); //다음 플레이어로 이동

	if (realPlayerNum < inputTotalNum)
	{
		playerNumber++;
		if (playerNumber >= realPlayerNum)
			playerNumber = 0;
	}
	else
	{
		playerNumber++;
		if (playerNumber >= inputTotalNum)
			playerNumber = 0;
	}
}

bool GameController::ComJudgeFunction(int vicProbability)
{
	if ( vicProbability >= 60 )
	{
		return ((rand() % 100) < 80) ? true : false;
	}
	else if ( vicProbability >= 40)
	{
		return ((rand() % 100) < 60) ? true : false;
	}
	else if ( vicProbability >= 20)
	{
		return ((rand() % 100) < 40) ? true : false;
	}
	else
	{
		return ((rand() % 100) < 20) ? true : false;
	}
}

int GameController::TwoNumberGap(int num1, int num2)
{
	int numberGap = abs(num2 - num1);
	double vicProbability = ((double)numberGap / 13) * 100;

	return (int)vicProbability;
}

int GameController::HowMuchBetting(Player *(&p), int Propability, Dealer &dealer)
{
	int bettingMoney;

	if (Propability >= 60) //베팅을 성공할 확률이 60퍼 이상일 때
	{
		if( (rand() % 100) < 80) //약 80퍼센트의 확률로 
		{
			if (p->GetMyMoney() > dealer.GetGameTotalMoney()) //내가 가진 금액이 판돈보다 많으면
			{
				bettingMoney = (int)(dealer.GetGameTotalMoney() * 0.8); //판돈의 80퍼센트에 해당하는 금액을 결정.
			}
			else //판돈이 더 많거나 똑같을 경우 내가 가진 금액의 80퍼센트로 금액 결정.
			{
				bettingMoney = (int)(p->GetMyMoney() * 0.8); //나의 80퍼센트에 해당하는 금액을 결정.
			}
		}
		else //20퍼센트의 확률로
		{
			if (p->GetMyMoney() > dealer.GetGameTotalMoney()) //내가 가진 금액이 판돈보다 많으면
			{
				bettingMoney = dealer.GetGameTotalMoney(); //판돈의 금액 올인
			}
			else //판돈이 더 많거나 똑같을 경우 
			{
				bettingMoney = p->GetMyMoney(); //내가 가진 금액 올인
			}
		}
	}
	else if (Propability >= 40) //베팅을 성공할 확률이 40퍼 이상일 때
	{
		if ((rand() % 100) < 60) //60퍼센트의 확률로
		{
			if (p->GetMyMoney() > dealer.GetGameTotalMoney()) //내가 가진 금액이 판돈보다 많으면
			{
				bettingMoney = (int)(dealer.GetGameTotalMoney() * 0.6); //판돈의 60퍼센트에 해당하는 금액을 결정.
			}
			else //판돈이 더 많거나 똑같을 경우
			{
				bettingMoney = (int)(p->GetMyMoney() * 0.6); //나의 80퍼센트에 해당하는 금액을 결정.
			}
		}
		else //그렇지 않으면
		{
			if (p->GetMyMoney() > dealer.GetGameTotalMoney()) //내가 가진 금액이 판돈보다 많으면
			{
				bettingMoney = (int)(dealer.GetGameTotalMoney() * 0.5); //판돈의 50퍼센트에 해당하는 금액을 결정.
			}
			else //판돈이 더 많거나 똑같을 경우
			{
				bettingMoney = (int)(p->GetMyMoney() * 0.5); //나의 50퍼센트에 해당하는 금액을 결정.
			}
		}
	}
	else if (Propability >= 20)
	{
		if ((rand() % 100) < 40)
		{
			if (p->GetMyMoney() > dealer.GetGameTotalMoney()) //내가 가진 금액이 판돈보다 많으면
			{
				bettingMoney = (int)(dealer.GetGameTotalMoney() * 0.4); //판돈의 40퍼센트에 해당하는 금액을 결정.
			}
			else //판돈이 더 많거나 똑같을 경우
			{
				bettingMoney = (int)(p->GetMyMoney() * 0.4); //나의 40퍼센트에 해당하는 금액을 결정.
			}
		}
		else
		{
			if (p->GetMyMoney() > dealer.GetGameTotalMoney()) //내가 가진 금액이 판돈보다 많으면
			{
				bettingMoney = (int)(dealer.GetGameTotalMoney() * 0.3); //판돈의 30퍼센트에 해당하는 금액을 결정.
			}
			else //판돈이 더 많거나 똑같을 경우
			{
				bettingMoney = (int)(p->GetMyMoney() * 0.3); //나의 30퍼센트에 해당하는 금액을 결정.
			}
		}
	}
	else
	{
		if (p->GetMyMoney() > dealer.GetGameTotalMoney()) //내가 가진 금액이 판돈보다 많으면
		{
			bettingMoney = (int)(dealer.GetGameTotalMoney() * 0.2); //판돈의 20퍼센트에 해당하는 금액을 결정.
		}
		else //판돈이 더 많거나 똑같을 경우
		{
			bettingMoney = (int)(p->GetMyMoney() * 0.2); //나의 20퍼센트에 해당하는 금액을 결정.
		}
	}

	return bettingMoney;
}

GameController::~GameController()
{
	delete[] comPlayer;
}
