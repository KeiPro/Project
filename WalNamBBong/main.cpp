#include "Walnambbong.h"

void CardBaseSetting(Card** card); //기본적인 카드 준비 함수원형 // 1~13 차례대로 세팅됨.

int main()
{
#pragma region 기본 세팅 및 초기화 구간 - 플레이어 생성, 컴퓨터 생성, 게임매니져 생성

	srand(time(NULL));

	Player player; //플레이어 객체 생성.
	int playerTotalNumber; //플레이어 총 수 입력 변수
	string playerName; //플레이어 이름을 입력받을 변수

	cout << "플레이어의 이름을 입력해 주세요 : ";
	cin >> playerName;
	player.SetNameSetting(playerName); //이름 설정
	player.SetMoneySetting(INIT_MONEY); //초기 소지금 설정
	player.SetCardSetting({ 0, -1 }, {0, -1}); //플레이어 카드 초기화

	cout << "상대할 플레이어의 수를 입력해 주세요 : ";
	cin >> playerTotalNumber;

	Player* comPlayer = new Player[playerTotalNumber]; //Player포인터로 comPlayer를 동적할당

	//컴퓨터 초기화
	for (int i = 0; i < playerTotalNumber; i++)
	{
		comPlayer[i].SetNameSetting("com" + to_string(i+1)); //컴퓨터 이름 초기화
		comPlayer[i].SetMoneySetting(INIT_MONEY); // 컴퓨터 소지금 초기화
		comPlayer[i].SetCardSetting({ 0, -1 }, {0, -1}); //카드 초기화
		//cout << comPlayer[i].GetName() << endl;
	}

	//게임 메니저 초기화가 일어나야 된다.
	 //게임매니저 객체 생성 및 초기화.
	GameManager gm{0 ,0, TYPE_COUNT * CARD_EACH_NUMBER, TYPE_COUNT * CARD_EACH_NUMBER, playerTotalNumber + 1 , playerTotalNumber + 1, 0};

#pragma endregion

	//카드 동적할당
	Card** card = new Card*[4];
	for (int i = 0; i < 4; i++)
		card[i] = new Card[13];

	CardBaseSetting(card); //기본 카드 세팅. 스페이드~클로바까지, 숫자 순서대로 되어있는 새 카드 준비.
	gm.CardSuffle(card); //카드 셔플

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
//	
#pragma region 기본 베팅을 하는 구간
//
//		// 2.게임에 참가를 해야하므로 각 플레이어마다 소지금 -200을 한다.
		player.BaseVetting(&gm);
		//cout << gm.GetRemainingPlayerNumber();
		for (int i = 0; i < gm.GetRemainingPlayerNumber()-1; i++)
		{
			comPlayer[i].BaseVetting(&gm);
		}

#pragma endregion

#pragma region 선 플레이어를 결정하는 구간

		gm.SetFirstPlayer(rand()%4);
		if (gm.GetFirstPlayer() == 0)
		{
			cout << "당신이 선 플레이어 입니다." << endl;
		}
		else
		{
			cout << comPlayer[gm.GetFirstPlayer()-1].GetName() << "이 선 플레이어 입니다." << endl;
		}

#pragma endregion

#pragma region 게임 매니져가 카드를 나눠주는 구간

		gm.CardDividing(card , &player, comPlayer, gm.GetRemainingPlayerNumber());
		
		gm.SetRemainingCardNumeber(gm.GetRemainingCardNumber() - gm.GetRemainingPlayerNumber() * 2);
		cout << gm.GetRemainingCardNumber();

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
			if (i == 0)
				card[i][j].type = CARD_TYPE::SPADE;
			else if (i == 1)
				card[i][j].type = CARD_TYPE::DIAMOND;
			else if (i == 2)
				card[i][j].type = CARD_TYPE::HEART;
			else
				card[i][j].type = CARD_TYPE::CLOVER;
		}
	}
}