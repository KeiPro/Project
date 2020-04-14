#include "Walnambbong.h"

void CardBaseSetting(Card** card); //기본적인 카드 준비 함수원형 // 1~13 차례대로 세팅됨.

int main()
{
	srand(time(NULL));

	Player player{0, 0, 0}; //플레이어 객체 생성.
	int playerTotalNumber; //플레이어 총 수 입력 변수
	string playerName; //플레이어 이름을 입력받을 변수

	cout << "플레이어의 이름을 입력해 주세요 : ";
	cin >> playerName;
	player.SetNameSetting(playerName); //이름 설정
	player.SetMoneySetting(INIT_MONEY); //초기 소지금 설정
	player.SetCardSetting(); //플레이어 카드 초기화

	cout << "상대할 플레이어의 수를 입력해 주세요 : ";
	cin >> playerTotalNumber;

	Player* comPlayer = new Player[playerTotalNumber]; //Player포인터로 comPlayer를 동적할당

	//컴퓨터 초기화
	for (int i = 0; i < playerTotalNumber; i++)
	{
		comPlayer[i].SetNameSetting("com"+(i+1)); //컴퓨터 이름 초기화
		comPlayer[i].SetMoneySetting(INIT_MONEY); // 컴퓨터 소지금 초기화
		comPlayer[i].SetCardSetting(); //카드 초기화
	}

	//게임 메니저 초기화가 일어나야 된다.
	 //게임매니저 객체 생성 및 초기화.
	GameManager gm{ 0, TYPE_COUNT * CARD_EACH_NUMBER, TYPE_COUNT * CARD_EACH_NUMBER, playerTotalNumber + 1 , playerTotalNumber + 1 };
	
	cout << gm.GetGameTotalMoney() << ", " << gm.GetTotalPlayerNumber() << ", " << gm.GetTotalCardNumber() << ", " << gm.GetRemainingPlayerNumber() << ", " << gm.GetRemainingCardNumebr() << endl;


	//카드 동적할당
	Card** card = new Card*[4];
	for (int i = 0; i < 4; i++)
		card[i] = new Card[13];

	CardBaseSetting(card); //기본 카드 세팅. 스페이드~클로바까지, 숫자 순서대로 되어있는 새 카드 준비.
	gm.CardSuffle(card); //카드 셔플

	

	
	//카드 동적할당 해제
	for (int i = 0; i < 4; i++)
		delete[] card[i];

	delete[] card;
	delete[] comPlayer;
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