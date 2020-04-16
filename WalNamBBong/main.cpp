#include "Walnambbong.h"
#include "Player.h"
#include "GameManager.h"

void CardBaseSetting(Card** card); //기본적인 카드 준비 함수원형 // 1~13 차례대로 세팅됨.

int main()
{
#pragma region 기본 세팅 및 초기화 구간 - 플레이어 생성, 컴퓨터 생성, 게임매니져 생성

	srand(time(NULL));

	Player player; //플레이어 객체 생성.
	int playerTotalNumber; //플레이어 총 수를 입력 변수
	string playerName; //플레이어 이름을 입력받을 변수
	int vettingCall;
	int gameProgress; //게임 계속 진행하나?

	cout << "플레이어의 이름을 입력해 주세요 : ";
	cin >> playerName;
	player.SetNameSetting(playerName); //이름 설정
	player.SetMoneySetting(INIT_MONEY); //초기 소지금 설정
	player.SetCardSetting({ 0, "" }, {0, ""}); //플레이어 카드 초기화
	player.SetIsAlive(true);

	cout << "상대할 플레이어의 수를 입력해 주세요 : ";
	cin >> playerTotalNumber;

	Player* comPlayer = new Player[playerTotalNumber]; //Player포인터로 comPlayer를 동적할당

	//컴퓨터 초기화
	for (int i = 0; i < playerTotalNumber; i++)
	{
		comPlayer[i].SetNameSetting("com" + to_string(i+1)); //컴퓨터 이름 초기화
		comPlayer[i].SetMoneySetting(INIT_MONEY); // 컴퓨터 소지금 초기화
		comPlayer[i].SetCardSetting({ 0, "" }, {0, ""}); //카드 초기화
		comPlayer[i].SetIsAlive(true);
		//cout << comPlayer[i].GetName() << endl;
	}

	//게임 매니저 초기화가 일어나야 된다.
	//게임매니저 객체 생성 및 초기화.
	GameManager gm{0 ,0, TYPE_COUNT * CARD_EACH_NUMBER, TYPE_COUNT * CARD_EACH_NUMBER, playerTotalNumber + 1 , playerTotalNumber + 1, 0};
	//gm.SetLeftMoneyIsTrue(true);

#pragma endregion

	//카드 동적할당
	Card** card = new Card*[4];
	for (int i = 0; i < 4; i++)
		card[i] = new Card[13];

	CardBaseSetting(card); //기본 카드 세팅. 스페이드~클로바까지, 숫자 순서대로 되어있는 새 카드 준비.
	gm.CardSuffle(card); //카드 셔플

#pragma region 기본 선 플레이어 결정구간
	int turn = rand() % 4; // 0 ~ 3
	gm.SetFirstPlayer(turn);

	//if (gm.GetFirstPlayer() == 0)
	//{
	//	cout << "당신이 선 플레이어 입니다." << endl;
	//}
	//else
	//{
	//	cout << comPlayer[gm.GetFirstPlayer() - 1].GetName() << "이 선 플레이어 입니다." << endl;
	//}
#pragma endregion
	
#pragma region 게임이 진행되는 구간
	while (1)
	{
#pragma region 카드 셔플

		// 1.남아있는 카드의 개수가 총 플레이어 수 * 3보다 작으면 카드 셔플이 일어난다.
		if (gm.GetRemainingCardNumber() < gm.GetRemainingPlayerNumber() * 3)
		{
			gm.CardSuffle(card); //카드 셔플
			gm.SetXPositionYPosition(0, 0); //다시 0, 0위치를 가리키도록 설정.
		}
//
#pragma endregion

#pragma region 기본 베팅을 하는 구간

		//판에 잔여 금액이 남아있지 않으면
		if (gm.GetGameTotalMoney() <= 0)
		{
			// 2.게임에 참가를 해야하므로 각 플레이어마다 소지금 -200을 한다.
			if (player.GetIsAlive())
			{
				player.BaseVetting(&gm);
				cout << "플레이어 기본 베팅 200" << endl;
				Sleep(1000);
			}

			for (int i = 0; i < gm.GetTotalPlayerNumber() - 1; i++)
			{
				if (comPlayer[i].GetIsAlive())
				{
					comPlayer[i].BaseVetting(&gm);
					cout << comPlayer[i].GetName() << " 기본베팅 200" << endl;
					Sleep(1000);
				}
			}

			//카드 분배
			gm.CardDividing(card, &player, comPlayer);
		}
		
		cout << "현재 판 돈 : " << gm.GetGameTotalMoney() << endl;
		Sleep(2000);

#pragma endregion
		
		
	//각 플레이어간의 카드 출력
	/*
	//for (int i = 0; i < gm.GetTotalPlayerNumber(); i++)
	//{
	//	if (i == 0) 
	//	{
	//		cout << player.GetFirstCard().type << ", " << player.GetFirstCard().cardNumber << endl;
	//		cout << player.GetSecondCard().type << ", " << player.GetSecondCard().cardNumber << endl;
	//	}
	//	else
	//	{
	//		cout << comPlayer[i-1].GetFirstCard().type << ", " << comPlayer[i - 1].GetFirstCard().cardNumber << endl;
	//		cout << comPlayer[i-1].GetSecondCard().type << ", " << comPlayer[i - 1].GetSecondCard().cardNumber << endl;
	//	}
	//	cout << endl;
	//}
	//gm.SetRemainingCardNumeber(gm.GetRemainingCardNumber() - gm.GetRemainingPlayerNumber() * 2);
	//cout << "남은 카드 개수 : " << gm.GetRemainingCardNumber(); //남은 카드의 개수 출력
	*/

#pragma region 베팅 true? false?
		gameProgress = gm.PlayerGameStart(card, &player, comPlayer);
		
		switch (gameProgress)
		{ 
			case 0: // 빗자루로 승리.
				// 승리한 사람이 선 플레이어가 된다.
				cout << "빗자루!" << endl; 
				player.PullMoney(gm.GetGameTotalMoney()); //판돈에 올라와있는 모든 돈을 다 받고,
				gm.PullGameTotalMoney(-gm.GetGameTotalMoney()); //게임 매니저에서는 이 만큼 판돈이 빠져야 된다.
				continue;
				break;

			case 1: // 베팅 시작
				cout << "베팅!!" << endl;
				break;

			case 2: // 다이
				
				cout << "다이!!" << endl;
				break;

		}		
#pragma endregion

#pragma region 게임 종료 구간



#pragma endregion


		break;
	}
#pragma endregion

	delete[] comPlayer;
	//카드 동적할당 해제
	for (int i = 0; i < 4; i++)
		delete[] card[i];

	delete[] card;

}

void CardBaseSetting(Card** card) //기본적인 카드 준비 함수
{
	for (int i = 0; i < TYPE_COUNT; i++)
	{
		for (int j = 0; j < CARD_EACH_NUMBER; j++)
		{
			card[i][j].cardNumber = (j + 1);
			
			switch (i)
			{
			case CARD_TYPE::SPADE:
				card[i][j].type = "♠";
				break;

			case CARD_TYPE::DIAMOND:
					card[i][j].type = "◆";
					break;

			case CARD_TYPE::HEART:
				card[i][j].type = "♥";
				break;

			case CARD_TYPE::CLOVER:
				card[i][j].type = "♣";

				break;

			}
		}
	}
}