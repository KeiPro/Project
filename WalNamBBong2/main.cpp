#include "Dealer.h"
#include "Player.h"
#include "GameController.h"

int main()
{
	srand((unsigned)time(NULL));

	Player player; //플레이어 객체 생성
	GameController gameController; // 게임 컨트롤러 객체 생성

	Player* phead = nullptr; //원형연결리스트로 사용되기 위한 변수. 턴 순서대로 활용되기 위해서 쓰인다.

	gameController.InputNamePrint(&player); // 플레이어 이름 설정.
	gameController.InputTotalNum(); //총 플레이어의 수 입력 함수 --> 컴퓨터들의 객체 생성
	gameController.TurnSetting(&player, &phead); //순서 세팅이 된다.

	Dealer dealer(0, 0); //딜러 객체 생성
	dealer.CardSetting(); //기본 카드 세팅
	
	Player* p = phead; //이 포인터를 통해 순서대로 접근할 수 있도록 한다.
	gameController.InputMoney(&phead, p, 2000); //플레이어에게 금액 부여
	
	int playerNumber = 0; //임시적으로 몇 번째 플레이어인지 보여주기 위한 변수
	bool bettingCall = false;

	//게임 진행 함수
	while (1)
	{
		//판돈이 0원이면.
		if (dealer.GetGameTotalMoney() == 0)
		{
			//남은 카드 수가 남은 플레이어의 3배 보다 적으면
			if ((CARD_TOTAL_NUMBER - dealer.GetDistribute()) < gameController.GetLeftPlayerNum() * 3)
			{
				dealer.CardShuffle(); //카드 셔플
				dealer.SetDistribute(0);
				gameController.CurrentStatePrint(phead, p, dealer); //현재 상황 프린트
				gameController.BaseBetting(phead, p, dealer); //기본 베팅
				gameController.CurrentStatePrint(phead, p, dealer); //현재 상황 프린트
				dealer.CardDividing(phead, p); //카드 분배
			}
			else
			{
				gameController.CurrentStatePrint(phead, p, dealer); //현재 상황 프린트
				gameController.BaseBetting(phead, p, dealer); //기본 베팅
				gameController.CurrentStatePrint(phead, p, dealer); //현재 상황 프린트
				dealer.CardDividing(phead, p); //카드 분배
			}
		}
		else if ( p == phead ) //한바퀴 돌고 다시 맨 처음으로 돌아왔을때
		{
			//남은 카드 수가 남은 플레이어의 3배 보다 적으면
			if ((CARD_TOTAL_NUMBER - dealer.GetDistribute()) < gameController.GetLeftPlayerNum() * 3)
			{
				dealer.CardShuffle(); //카드 셔플
				dealer.SetDistribute(0);
				gameController.BaseBetting(phead, p, dealer); //기본 베팅
				gameController.CurrentStatePrint(phead, p, dealer); //현재 상황 프린트
				dealer.CardDividing(phead, p); //카드 분배
			}
			else
			{
				dealer.CardDividing(phead, p); //카드 분배
			}
		}
		
		bettingCall = gameController.BettingYesOrNo(phead, p, playerNumber, dealer, &player);

		if (bettingCall)
		{
			gameController.BettingCardOpen(phead, p, dealer, &player);
		}

		gameController.NextPlayerPointer(p, playerNumber);
	}
	
	return 0;
}