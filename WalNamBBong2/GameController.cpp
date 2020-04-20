#include "GameController.h"

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
	cout << "2)��ǻ�� �̸� ���� �Է��ϱ�" << endl;
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
			if (inputNum == 1 || inputNum == 2)
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

#pragma region Circular Linked List ����

	Player* p = nullptr;

	for (int i = 0; i < inputTotalNum; i++)
	{
		for (int j = 0; j < inputTotalNum-1; j++)
		{
			if ( comPlayer[j].GetTurn() == i || player->GetTurn() == i )
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
							p->SetLink(comPlayer+j);
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
	}

	p->SetLink(*phead);
	p = p->GetLink();

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
		Sleep(50);
	}


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

	//Print - Test
	//cout << (*phead)->GetMyMoney() << ", ";
	//p = p->GetLink();
	//for ( ; p != *phead ; )
	//{
	//	cout << p->GetMyMoney() << ", ";
	//	p = p->GetLink();
	//}
}

GameController::~GameController()
{
	delete[] comPlayer;
}
