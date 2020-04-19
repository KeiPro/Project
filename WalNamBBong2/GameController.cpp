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
			Sleep(2000);
			cout << ">> ��ø� ��ٷ� �ּ���... " << endl;
			Sleep(3000);
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
	string autoName[30] = {"Ż��", "����", "�ƹ���", "����ũ��ũ", "����̸�", "ī���", "����", "�轺", "������", "����",
							"������", "������", "����ī��", "������Ʈ", "����", "�����Ƴ�", "�ǻ�", "���̶�", "����", "����Ʋ��",
							"����", "ī�̻�", "���縮����", "���׿�", "Ű�Ƴ�", "Ʈ����Ƽ�� ����Ʈ", "����", "ī�ÿ����", "¡ũ��", "����"};

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

void GameController::TurnSetting(Player* player)
{
	system("cls"); 
	cout << " < ������ ���մϴ�. > " << endl;
	
	int* dynamicNum = new int[inputTotalNum]; //

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

	player->SetTurn(dynamicNum[inputTotalNum-1]);
	for (int i = 0; i < inputTotalNum-1; i++)
	{
		comPlayer[i].SetTurn(dynamicNum[i]);
	}


	cout << ">> " << player->GetName() << "�� ���� : " << player->GetTurn()+1 << "��" << endl;
	for (int i = 0; i < inputTotalNum-1; i++)
	{
		cout << comPlayer[i].GetName() << "�� ���� : " << comPlayer[i].GetTurn()+1 << "��" << endl;
	}

	Player tmp;

	
	//for (int i = 0; i < inputTotalNum; i++)
	//{
	//	for (int j = 0; j < inputTotalNum-1; j++)
	//	{
	//		if ( (comPlayer[j].GetTurn() == i) || player->GetTurn() == i)
	//		{
	//			if (comPlayer[j].GetTurn() == i)
	//			{
	//				tmp = comPlayer[i];
	//				comPlayer[i] = comPlayer[j];
	//				comPlayer[j] = tmp;
	//				break;
	//			}
	//			else
	//			{
	//				tmp = *player;
	//				*player = comPlayer[i]; //�̷��� �Ǹ� Player�� turn�� �� �ٲ�� �ǹǷ�, �ᱹ ���������� comPlayer�� i��°�� �������� ���ϴ� ������ �����ϰ� �ȴ�.
	//				comPlayer[i] = tmp;
	//				break;
	//			}
	//		}
	//	}
	//}

	cout << player->GetName() << endl; 
	
	
	delete[] dynamicNum;
}

GameController::~GameController()
{
	delete[] comPlayer;
}
