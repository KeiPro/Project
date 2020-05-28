#include "GameController.h"
#include "Dealer.h"

void GameController::InputNamePrint(Player* player)
{
	string name;
	cout << "�÷��̾��� �̸��� �Է��� �ּ��� : ";
	cin >> name;

	player->SetName(name);
}

void GameController::InputTotalNum()
{
	cout << "�� �÷��̾��� ���� �Է��� �ּ���(���� ����) : ";
	cin >> inputTotalNum;
	
	if (inputTotalNum <= 17)
	{
		maxPlayerNum = inputTotalNum;
		waitPlayerNum = 0;
		waitPlayerIndex = 0;
	}
	else
	{
		maxPlayerNum = 17;
		waitPlayerNum = inputTotalNum - maxPlayerNum;
		waitPlayerIndex = 17;
	}

	leftPlayerNum = inputTotalNum;

	comPlayer = new Player[inputTotalNum -1];

	switch (RegisterComName())
	{
		case 1: //��ǻ�� �̸� �ڵ������ϱ�
			cout << endl;
			cout << ">> ��ǻ���̸� �ڵ� �����ϱ⸦ �����ϼ̽��ϴ�." << endl;
			Sleep(1000);
			cout << ">> ��ø� ��ٷ� �ּ���... " << endl;
			Sleep(1000);
			AutoRegisterComName(inputTotalNum-1);
			break;

		case 2: //��ǻ�� �̸� ���� �Է�.
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

	cout << " < ��ǻ�� �̸� ���� > " << endl;
	cout << endl;
	cout << "1)��ǻ�� �̸� �ڵ� �����ϱ�" << endl;
	cout << "2)��ǻ�� �̸� ���� �Է��ϱ�(������...)" << endl;
	cout << endl;

	cout << "--> ��ȣ�� �Է��� �ּ��� : ";

	while (1)
	{
		cin >> inputNum;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');

			cout << "��ȣ�� �ٽ� �Է��� �ּ��� : ";
		}
		else
		{
			if (inputNum == 1)
			{
				break;
			}
			else
			{
				cout << "��ȣ�� �ٽ� �Է��� �ּ��� : ";
				continue;
			}
		}
		
	}

	return inputNum;
}

void GameController::AutoRegisterComName(int _totalNumber)
{
	string autoName[30] = {"Ż��", "����", "�ƹ���", "ī��", "����̸�", "ī���", "����", "�轺", "������", "����",
							"������", "������", "����ī��", "������Ʈ", "����", "�����Ƴ�", "�ǻ�", "���̶�", "����", "����Ʋ��",
							"����", "ī�̻�", "���縮����", "���׿�", "Ű�Ƴ�", "�ŵ��", "����", "ī�ÿ����", "¡ũ��", "����"};

	int* number = new int[_totalNumber];

	//��ġ�� �ʰ� ��ȣ ����
	for (int i = 0; i < _totalNumber; i++)
	{
		number[i] = rand() % 30;

		for (int j = 0; j < i; j++)
		{
			if (number[j] == number[i])
				i--;
		}
	}

	//�̸� ����
	for (int i = 0; i < _totalNumber; i++)
	{
		comPlayer[i].SetName(autoName[number[i]]);
	}

	system("cls");
	cout << "\t < �ڵ����� �Ϸ�! > " << endl;
	cout << endl;
	Sleep(1000);
	//�̸� ����
	for (int i = 0; i < _totalNumber; i++)
	{
		cout << "\t" << i+1 << "�� ��� �̸� : " << comPlayer[i].GetName() << endl;
		Sleep(100);
	}

	Sleep(1000);
	cout << endl;
	cout << "��� �����Ϸ��� �ƹ�Ű�� �Է��ϼ���." << endl;

	int ch = _getch();

	delete[] number;
}

void GameController::InputRegisterComName(int _totalNumber)
{
	string inputName;
	cout << " < ���� �Է� > " << endl;
	for (int i = 0; i < _totalNumber; i++)
	{
		//����ϱ�
		//�ٽ� �Է��ϱ�
	}
}

void GameController::TurnSetting(Player* player, Player** phead)
{
	system("cls"); 
	cout << endl;
	cout << "\t < ������ ���մϴ�. > " << endl;
	cout << endl;

	int* dynamicNum = new int[inputTotalNum]; //

	//�����ϰ� ��ȣ�� �̰�
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

	//�÷��̾�� �����ϰ� ��ȣ�� �ο�
	player->SetTurn(dynamicNum[inputTotalNum-1]);
	for (int i = 0; i < inputTotalNum-1; i++)
	{
		comPlayer[i].SetTurn(dynamicNum[i]);
	}

	cout << ">> \t" << player->GetName() << "�� ���� : " << player->GetTurn()+1 << "��" << endl;
	for (int i = 0; i < inputTotalNum-1; i++)
	{
		cout << "\t" << comPlayer[i].GetName() << "�� ���� : " << comPlayer[i].GetTurn()+1 << "��" << endl;
	}

	cout << endl;
	cout << endl;
	cout << " >> �ƹ�Ű�� �Է��� �ּ���.";
	
	char ch = _getch();

#pragma region ���� ���Ḯ��Ʈ ����
	int count = 0;
	Player* p = nullptr;

	//�ִ� ���� �ο�.
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
						if (p->GetNextLink() == nullptr)
						{
							p->SetNextLink(comPlayer + j);
							(p->GetNextLink())->SetPrevLink(p);
							p = p->GetNextLink();
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
						if (p->GetNextLink() == nullptr)
						{
							p->SetNextLink(player);
							(p->GetNextLink())->SetPrevLink(p);
							p = p->GetNextLink();
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

	p->SetNextLink(*phead);
	(*phead)->SetPrevLink(p);
	p = p->GetNextLink();

#pragma endregion

#pragma region ���� ��Ʈ - ������� Print�ϴ� ��

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
		cout << "\t\t < ���� ���� > " << endl;
		cout << endl;
		for (int i = 0; i < inputTotalNum; i++)
		{
			if (i == player->GetTurn())
			{
				if (tmpPlayer[i].GetName().size() < 4)
				{
					cout << "\t\b\b\b>>> " << tmpPlayer[i].GetName() << "�� \t\t\t ���� : " << tmpPlayer[i].GetTurn() + 1 << "��" << endl;
				}
				else
				{
					cout << "\t\b\b\b>>> " << tmpPlayer[i].GetName() << "�� \t\t ���� : " << tmpPlayer[i].GetTurn() + 1 << "��" << endl;
				}
			}
			else
			{
				cout << "\t " << tmpPlayer[i].GetName() << "�� \t\t ���� : " << tmpPlayer[i].GetTurn() + 1 << "��" << endl;
			}
		}
		Sleep(10);
	}

	system("cls");

	cout << endl;
	cout << "\t\t < ���� ���� > " << endl;
	cout << endl;

	for (int i = 0; i < inputTotalNum; i++)
	{
		if (i < maxPlayerNum)
		{
			if (i == player->GetTurn())
			{
				if (tmpPlayer[i].GetName().size() < 4)
				{
					cout << "\t\b\b\b>>> " << tmpPlayer[i].GetName() << "�� \t\t\t ���� : " << tmpPlayer[i].GetTurn() + 1 << "��" << endl;
				}
				else
				{
					cout << "\t\b\b\b>>> " << tmpPlayer[i].GetName() << "�� \t\t ���� : " << tmpPlayer[i].GetTurn() + 1 << "��" << endl;
				}
			}
			else
			{
				cout << "\t " << tmpPlayer[i].GetName() << "�� \t\t ���� : " << tmpPlayer[i].GetTurn() + 1 << "��" << endl;
			}
		}
		else
		{
			if (i == player->GetTurn())
			{
				if (tmpPlayer[i].GetName().size() < 4)
				{
					cout << "\t\b\b\b>>> " << tmpPlayer[i].GetName() << "�� \t\t\t ���� : " << tmpPlayer[i].GetTurn() + 1 << "�� -- ���" << endl;
				}
				else
				{
					cout << "\t\b\b\b>>> " << tmpPlayer[i].GetName() << "�� \t\t ���� : " << tmpPlayer[i].GetTurn() + 1 << "�� -- ���" << endl;
				}
			}
			else
			{
				cout << "\t " << tmpPlayer[i].GetName() << "�� \t\t ���� : " << tmpPlayer[i].GetTurn() + 1 << "�� -- ���" << endl;
			}
		}
	}

	cout << endl;
	cout << " >> �ƹ�Ű�� �Է��� �ּ���.";
	
	ch = _getch();

	cout << endl;

	//cout << endl;
	//for (int i = 0; i < inputTotalNum; i++)
	//{
	//	cout << p->GetName() << ", ";
	//	p = p->GetNextLink();
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
	p = p->GetNextLink();

	while (p != *phead)
	{
		p->SetMyMoney(_myMoney);
		p = p->GetNextLink();
	}
}

void GameController::InputBaseBetting()
{
	cout << endl;
	cout << "�⺻ ���ñݾ� �Է� >> ";
	cin >> this->baseInputMoney;
	cout << endl;
	cout << "�⺻ ���ñݾ��� " << this->baseInputMoney << "������ �����Ǿ����ϴ�. " << endl;
	Sleep(1000);
}



void GameController::BaseBetting(Player* (&phead), Player* (&p), Dealer &dealer)
{
	cout << endl;
	cout << "\t�ǵ��� 0�� �Դϴ�." << endl;
	cout << endl;
	Sleep(1000);

	cout << "\t��� �÷��̾� �ݾ� -" << this->baseInputMoney << "�� ����." << endl;

	Sleep(1000);

	p->SetMyMoney(p->GetMyMoney()- this->baseInputMoney);
	dealer.AddingTotalMoney(this->baseInputMoney);
	p = p->GetNextLink();

	while ( p != phead )
	{
		p->SetMyMoney(p->GetMyMoney() - this->baseInputMoney);
		dealer.AddingTotalMoney(this->baseInputMoney);
		p = p->GetNextLink();
	}
}

void GameController::CurrentStatePrint(Player* (&phead), Player* (&p), Dealer &dealer)
{
	system("cls");
	cout << "\t=========================================" << endl;
	cout << "\t|   \t\t\t\t\t|" << endl;
	cout << "\t|\t    < �ǵ� : " << dealer.GetGameTotalMoney() << " >\t\t|" << endl;
	cout << "\t|   \t\t\t\t\t|" << endl;
	cout << "\t=========================================" << endl;
	cout << "\t|\t\b\b���̵�\t|\t���� �ݾ�\t|" << endl;
	cout << "\t=========================================" << endl;
	
	if (p->GetMyMoney() < this->baseInputMoney+100)
	{
		if (p->GetName().size() < 3)
		{
			cout << "\t|    " << p->GetName() << "\t\t|\t\t\b\b\b\b" << p->GetMyMoney() << "\t (Die)  |" << endl;
		}
		else
		{
			cout << "\t|    " << p->GetName() << "\t|\t\t\b\b\b\b" << p->GetMyMoney() << "\t (Die)  |" << endl;
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
	p = p->GetNextLink();

	while (p != phead)
	{
		if (p->GetMyMoney() < this->baseInputMoney+100)
		{
			if (p->GetName().size() < 3)
			{
				cout << "\t|    " << p->GetName() << "\t\t|\t\t\b\b\b\b" << p->GetMyMoney() << "\t (OUT)  |" << endl;
			}
			else
			{
				cout << "\t|    " << p->GetName() << "\t|\t\t\b\b\b\b" << p->GetMyMoney() << "\t (OUT)  |" << endl;
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
		p = p->GetNextLink();
	}
	cout << "\t=========================================" << endl;

	cout << endl;
	cout << "\t��� �����Ϸ��� �ƹ�Ű�� �����ּ���." << endl;
	char ch = _getch();
}

bool GameController::ThirteenCardCheck(Player* (&phead), Player* (&p), Dealer& dealer, Player* (&player))
{
	//13�� ����ִ� ����
	if ( (p->GetMyFirstCard().GetNum() == 13) || (p->GetMySecondCard().GetNum() == 13))
	{
		//�ǵ��� �ִ� ��� �ݾ��� �� �����´�.
		if ((p->GetMyFirstCard().GetNum() == 13) && (p->GetMySecondCard().GetNum() == 13))
		{
			cout << endl;
			cout << "\t �� �� ! ! ! ! !" << endl;
			Sleep(1000);
			cout << endl;
			cout << "\t 13�� �� ���� �־� �ǵ��� ���� ��� �����ɴϴ�. " << endl;
			Sleep(1000);
			cout << endl;
			cout << "\t ȹ���� �ݾ� : +" << dealer.GetGameTotalMoney() << "��" << endl;

			//������ �� �����´�.
			player->SetMyMoney(player->GetMyMoney() + dealer.GetGameTotalMoney());
			dealer.AddingTotalMoney(-dealer.GetGameTotalMoney());
			return true;
		}
		else
		{
			Sleep(1000);
			cout << "\t 13�� �� ���� �־� ������ �� �����ϴ�. " << endl;
			Sleep(2000);
			cout << endl;

			//////////////////���� �Լ� ����
			
			PlayerOutFunction(phead, p, player, dealer);

			return true;
		}
	}

	return false;
}

bool GameController::BettingYesOrNo(Player *(&phead), Player *(&p), int& playerNumber, Dealer &dealer, Player* player)
{
	int bettingMoney;
	int bettingYesOrNo;
	int gabPropability;
	bool bettingCall;

	system("cls");
	cout << endl;
	cout << "\t\t< " << (playerNumber+1) << "��° �÷��̾� > " << endl;
	cout << endl;
	if(p == player)
	{
		cout << "\t\t>> ��� ���� �Դϴ� <<" << endl;
		cout << endl;
	}
	cout << "\t\t "<< p->GetName() <<" �÷��̾�" << endl;
	cout << endl;
	cout << "\t\t  �ǵ� : "<< dealer.GetGameTotalMoney() << "��" << endl;
	cout << endl;
	cout << "\t=======================================" << endl;
	cout << "\t|   ���� ī��\t|\t���� �ݾ�     |" << endl;
	cout << "\t=======================================" << endl;
	cout << "\t|  " << p->GetMyFirstCard().GetShape() << p->GetMyFirstCard().GetNum() << 
		"\t|  "<< p->GetMySecondCard().GetShape() << p->GetMySecondCard().GetNum() <<"\t|\t "<< p->GetMyMoney() <<"��\t\t\b\b|" << endl;
	cout << "\t=======================================" << endl;
	cout << endl;

	if (ThirteenCardCheck(phead, p, dealer, player))
	{
		return false;
	}

	
	//�÷��̾�� �����ϵ���.
	if (p == player)
	{
		cout << "\t ���� �Ͻðڽ��ϱ�? 1)�� 2)�ƴϿ� >> ";

		while (1)
		{
			cin >> bettingYesOrNo;

			if (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
				cout << "\n\t �ٽ� �Է��� �ּ���." << endl;
				Sleep(1000);
			}
			else
			{
				break;
			}
		}

		int bettingTmp;

		if (bettingYesOrNo == 1)
		{
			cout << "\t �󸶸� �����Ͻðڽ��ϱ�? " << endl;
			cout << endl;
			cout << "\t  ( ������ ���� �ݾװ� �ǵ��� �ݾ׺��� �۾ƾ� �մϴ�. ) >>";
			
			while (1)
			{
				cin >> bettingTmp;

				if (cin.fail() || (bettingTmp > p->GetMyMoney()) || (bettingTmp > dealer.GetGameTotalMoney()))
				{
					cin.clear();
					cin.ignore(256, '\n');

					cout << "\t�ݾ��� �ٽ� �Է��� �ּ���. " << endl;
					Sleep(1000);
				}
				else
					break;
			}

			p->SetBettingMoney(bettingTmp);
			p->SetMyMoney(p->GetMyMoney() - p->GetBettingMoney());
			dealer.AddingTotalMoney(p->GetBettingMoney());
			
			return true;
		}
		else
			return false;

	}
	else //��ǻ�͸� �Ǵ��ؼ� �����ϵ���.
	{
		cout << "\t ���� �Ͻðڽ��ϱ�? 1)�� 2)�ƴϿ� >> ";
		//�Ǵ��ؼ�
		gabPropability = TwoNumberGap(p->GetMyFirstCard().GetNum(), p->GetMySecondCard().GetNum());
		bettingCall = ComJudgeFunction(gabPropability);
		
		if (bettingCall == true) //���� yes
		{
			Sleep(2000);
			cout << "1)��" << endl;
			cout << endl;
			cout << "\t(" << "��ǻ�Ͱ� �Ǵ��� Ȯ�� : " << gabPropability << "(%))" ;
			Sleep(2000);
			p->SetBettingMoney(HowMuchBetting(p, gabPropability, dealer));
			p->SetMyMoney(p->GetMyMoney() - p->GetBettingMoney()); //�÷��̾� betting�ݾ� ����
			dealer.AddingTotalMoney(p->GetBettingMoney()); //�ǵ� betting�ݾ� ����
			cout << "\t ���� �ݾ� : " << p->GetBettingMoney() << "��" << endl;
			Sleep(2000);

			return true;
		}
		else // ���� no
		{
			Sleep(2000);
			cout << "2)�ƴϿ�";
			Sleep(2000);

			///////////���� �Լ� ����
			PlayerOutFunction(phead, p, player, dealer);

			return false;
		}
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
		return ((rand() % 100) < 10) ? true : false;
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

	if (Propability >= 60) //������ ������ Ȯ���� 60�� �̻��� ��
	{
		if( (rand() % 100) < 80) //�� 80�ۼ�Ʈ�� Ȯ���� 
		{
			if (p->GetMyMoney() > dealer.GetGameTotalMoney()) //���� ���� �ݾ��� �ǵ����� ������
			{
				bettingMoney = (int)(dealer.GetGameTotalMoney() * 0.8); //�ǵ��� 80�ۼ�Ʈ�� �ش��ϴ� �ݾ��� ����.
			}
			else //�ǵ��� �� ���ų� �Ȱ��� ��� ���� ���� �ݾ��� 80�ۼ�Ʈ�� �ݾ� ����.
			{
				bettingMoney = (int)(p->GetMyMoney() * 0.8); //���� 80�ۼ�Ʈ�� �ش��ϴ� �ݾ��� ����.
			}
		}
		else //20�ۼ�Ʈ�� Ȯ����
		{
			if (p->GetMyMoney() > dealer.GetGameTotalMoney()) //���� ���� �ݾ��� �ǵ����� ������
			{
				bettingMoney = dealer.GetGameTotalMoney(); //�ǵ��� �ݾ� ����
			}
			else //�ǵ��� �� ���ų� �Ȱ��� ��� 
			{
				bettingMoney = p->GetMyMoney(); //���� ���� �ݾ� ����
			}
		}
	}
	else if (Propability >= 40) //������ ������ Ȯ���� 40�� �̻��� ��
	{
		if ((rand() % 100) < 60) //60�ۼ�Ʈ�� Ȯ����
		{
			if (p->GetMyMoney() > dealer.GetGameTotalMoney()) //���� ���� �ݾ��� �ǵ����� ������
			{
				bettingMoney = (int)(dealer.GetGameTotalMoney() * 0.6); //�ǵ��� 60�ۼ�Ʈ�� �ش��ϴ� �ݾ��� ����.
			}
			else //�ǵ��� �� ���ų� �Ȱ��� ���
			{
				bettingMoney = (int)(p->GetMyMoney() * 0.6); //���� 80�ۼ�Ʈ�� �ش��ϴ� �ݾ��� ����.
			}
		}
		else //�׷��� ������
		{
			if (p->GetMyMoney() > dealer.GetGameTotalMoney()) //���� ���� �ݾ��� �ǵ����� ������
			{
				bettingMoney = (int)(dealer.GetGameTotalMoney() * 0.5); //�ǵ��� 50�ۼ�Ʈ�� �ش��ϴ� �ݾ��� ����.
			}
			else //�ǵ��� �� ���ų� �Ȱ��� ���
			{
				bettingMoney = (int)(p->GetMyMoney() * 0.5); //���� 50�ۼ�Ʈ�� �ش��ϴ� �ݾ��� ����.
			}
		}
	}
	else if (Propability >= 20)
	{
		if ((rand() % 100) < 40)
		{
			if (p->GetMyMoney() > dealer.GetGameTotalMoney()) //���� ���� �ݾ��� �ǵ����� ������
			{
				bettingMoney = (int)(dealer.GetGameTotalMoney() * 0.4); //�ǵ��� 40�ۼ�Ʈ�� �ش��ϴ� �ݾ��� ����.
			}
			else //�ǵ��� �� ���ų� �Ȱ��� ���
			{
				bettingMoney = (int)(p->GetMyMoney() * 0.4); //���� 40�ۼ�Ʈ�� �ش��ϴ� �ݾ��� ����.
			}
		}
		else
		{
			if (p->GetMyMoney() > dealer.GetGameTotalMoney()) //���� ���� �ݾ��� �ǵ����� ������
			{
				bettingMoney = (int)(dealer.GetGameTotalMoney() * 0.3); //�ǵ��� 30�ۼ�Ʈ�� �ش��ϴ� �ݾ��� ����.
			}
			else //�ǵ��� �� ���ų� �Ȱ��� ���
			{
				bettingMoney = (int)(p->GetMyMoney() * 0.3); //���� 30�ۼ�Ʈ�� �ش��ϴ� �ݾ��� ����.
			}
		}
	}
	else
	{
		if (p->GetMyMoney() > dealer.GetGameTotalMoney()) //���� ���� �ݾ��� �ǵ����� ������
		{
			bettingMoney = (int)(dealer.GetGameTotalMoney() * 0.2); //�ǵ��� 20�ۼ�Ʈ�� �ش��ϴ� �ݾ��� ����.
		}
		else //�ǵ��� �� ���ų� �Ȱ��� ���
		{
			bettingMoney = (int)(p->GetMyMoney() * 0.2); //���� 20�ۼ�Ʈ�� �ش��ϴ� �ݾ��� ����.
		}
	}

	return bettingMoney;
}

void GameController::NextPlayerPointer(Player* (&p), int& playerNumber)
{
	p = p->GetNextLink(); //���� �÷��̾�� �̵�
	playerNumber++;

	if (leftPlayerNum > 17)
	{
		if (playerNumber >= maxPlayerNum)
				playerNumber = 0;
	}
	else
	{
		if (playerNumber >= leftPlayerNum)
			playerNumber = 0;
	}
}

void GameController::BettingCardOpen(Player* (&phead), Player* (&p), Dealer& dealer, Player* player)
{
	system("cls");
	Card openCard = dealer.Distributing();
	cout << dealer.GetDistribute();
	cout << endl;
	cout << "\t\t " << p->GetName() << " �÷��̾�" << endl;
	cout << endl;
	cout << "\t\t  �ǵ� : " << dealer.GetGameTotalMoney() << "��" << endl;
	cout << endl;
	cout << "\t=======================================" << endl;
	cout << "\t|   ���� ī��\t|\t���� �ݾ�     |" << endl;
	cout << "\t=======================================" << endl;
	cout << "\t|  " << p->GetMyFirstCard().GetShape() << p->GetMyFirstCard().GetNum() <<
		"\t|  " << p->GetMySecondCard().GetShape() << p->GetMySecondCard().GetNum() << "\t|\t " << p->GetMyMoney() << "��\t\t\b\b|" << endl;
	cout << "\t=======================================" << endl;
	cout << endl;
	cout << "\t>>���� �ݾ� : " << p->GetBettingMoney() << endl;
	cout << endl;
	cout << "\t>>ī�� ���� ��� : " << openCard.GetShape() << openCard.GetNum() << endl;

	if ((openCard.GetNum() > p->GetMyFirstCard().GetNum() &&
		openCard.GetNum() < p->GetMySecondCard().GetNum()) ||
		(openCard.GetNum() < p->GetMyFirstCard().GetNum() &&
			openCard.GetNum() > p->GetMySecondCard().GetNum()))
	{
		Sleep(2000);
		cout << endl;
		cout << "\t���� ����!" << endl;
		Sleep(2000);

		p->SetMyMoney(p->GetMyMoney() + p->GetBettingMoney() * 2);
		dealer.AddingTotalMoney(-(p->GetBettingMoney() * 2));
		cout << endl;
		cout << "\t�ݾ� +" << p->GetBettingMoney() * 2 << "�� ȹ���ϼ̽��ϴ�." << endl;
		Sleep(2000);
		cout << "\t" << p->GetName() << " �÷��̾� ���� �ݾ� : " << p->GetMyMoney() << endl;

		Sleep(2000);
	}
	else
	{
		Sleep(2000);
		cout << endl;
		cout << "\t���� ����!" << endl;
		Sleep(2000);

		////////////���� �Լ� ����
		PlayerOutFunction(phead, p, player, dealer);
	}
}

void GameController::PlayerOutFunction(Player* (&phead), Player* (&p), Player* (&player), Dealer& dealer)
{
	//���� �����ϴ� �ο��� �������� üũ�Ѵ�.
	//�������� �ش� �ݾ� �����̸�,

	//�ƿ� ����
	if (p->GetMyMoney() < baseInputMoney + 100)
	{
		//���� �����ϴ� �÷��̾ ���� Player���� ��ǻ������ ���Ѵ�.
		//Player�̸� �ٷ� ���� ������ ���� �ǰ�,
		if (p == player)
		{
			cout << "\t\t < ���ӿ��� �й��Ͽ����ϴ�. >" << endl;
			exit(1);
		}
		else //��ǻ���̸�
		{
			cout << endl;
			cout << "\t" << p->GetName() << " �÷��̾� �ƿ�!" << endl;
			cout << endl;

			//��ǻ�͸� ����ο��� �ִ����� üũ�Ѵ�.
			if (waitPlayerNum > 0) //����ο����� ��ü
			{
				//����ο��� ������ ���� ��ǻ�� �÷��̾�� �ƿ�ó���� �Ͽ� ����ο����� ��ü�ϰ�
				for (int i = 0; i < inputTotalNum; i++)
				{
					if (comPlayer[i].GetTurn() == waitPlayerIndex || player->GetTurn() == waitPlayerIndex)
					{
						//����ο� ��ü�� ó���ؾ��� ����.
						// 1. ���;� �� ����ο��� turn���� �ƿ��� �÷��̾��� turn������ ��ü.
						// 2. waitPlayerIndex�� ���� 1����.	
						if (comPlayer[i].GetTurn() == waitPlayerIndex) //����ο��� ã�Ƴ���.
						{
							comPlayer[i].SetNextLink(p->GetNextLink());
							comPlayer[i].SetPrevLink(p->GetPrevLink());
							(p->GetPrevLink())->SetNextLink(comPlayer + i);
							(p->GetNextLink())->SetPrevLink(comPlayer + i);

							if (p == phead)
								phead = (comPlayer + i);

							comPlayer[i].SetTurn(p->GetTurn());
							p = (comPlayer + i);
						}
						else
						{
							player->SetNextLink(p->GetNextLink());
							player->SetPrevLink(p->GetPrevLink());
							(p->GetPrevLink())->SetNextLink(player);
							(p->GetNextLink())->SetPrevLink(player);

							if (p == phead)
								phead = player;

							player->SetTurn(p->GetTurn());
							p = player;
						}
						waitPlayerIndex++;
						break;
					}
				}

				Sleep(2000);

				cout << "\t" << p->GetName() << " �÷��̾ ���ӿ� �����Ͽ����ϴ�. " << endl;
				p->SetMyMoney(2000);
				cout << endl;
				cout << "\t" << p->GetName() << " �÷��̾� ���� ��� -" << this->baseInputMoney << "�� ����." << endl;
				p->SetMyMoney(p->GetMyMoney() - this->baseInputMoney); //�÷��̾� betting�ݾ� ����
				dealer.AddingTotalMoney(this->baseInputMoney); //�ǵ� betting�ݾ� ����
				Sleep(2000);
				cout << endl;
				cout << "�ǵ��� " << this->baseInputMoney << "�� �����˴ϴ�." << endl;
				/////////////////////////////////////����.
				Sleep(2000);

			}
			else //��� �ο��� ������ ���� �����ϰ��ִ� �÷��̾��� Next�� Prev�� ������ �ϸ� ��.
			{
				(p->GetPrevLink())->SetNextLink(p->GetNextLink());
				(p->GetNextLink())->SetPrevLink(p->GetPrevLink());

				if (p == phead)
					phead = p->GetNextLink();

				p = p->GetPrevLink();
				Sleep(2000);
			}

			waitPlayerNum--; //����ο� 1 ����.
			leftPlayerNum--; //�� �÷����ο��� 1 ����.
		}
	}
	else //�״�� ���� ����
	{
		return;
	}
}

GameController::~GameController()
{
	delete[] comPlayer;
}
