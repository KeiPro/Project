#include "GameController.h"

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

	comPlayer = new Player[inputTotalNum -1];

	switch (RegisterComName())
	{
		case 1: //컴퓨터 이름 자동생성하기
			cout << endl;
			cout << ">> 컴퓨터이름 자동 생성하기를 선택하셨습니다." << endl;
			Sleep(2000);
			cout << ">> 잠시만 기다려 주세요... " << endl;
			Sleep(3000);
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
	cout << "2)컴퓨터 이름 직접 입력하기" << endl;
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
			if (inputNum == 1 || inputNum == 2)
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
	string autoName[30] = {"탈론", "리븐", "아무무", "블리츠크랭크", "블라디미르", "카사딘", "피즈", "잭스", "라이즈", "럼블",
							"레넥톤", "나서스", "마오카이", "말파이트", "럭스", "오리아나", "뽀삐", "자이라", "제드", "케이틀린",
							"녹턴", "카이사", "아펠리오스", "판테온", "키아나", "트위스티드 페이트", "제라스", "카시오페아", "징크스", "베인"};

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

void GameController::TurnSetting(Player* player)
{
	system("cls"); 
	cout << " < 순서를 정합니다. > " << endl;
	
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


	cout << ">> " << player->GetName() << "님 순서 : " << player->GetTurn()+1 << "번" << endl;
	for (int i = 0; i < inputTotalNum-1; i++)
	{
		cout << comPlayer[i].GetName() << "님 순서 : " << comPlayer[i].GetTurn()+1 << "번" << endl;
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
	//				*player = comPlayer[i]; //이렇게 되면 Player의 turn이 또 바뀌게 되므로, 결국 최종적으로 comPlayer의 i번째가 접근하지 못하는 곳까지 도달하게 된다.
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
