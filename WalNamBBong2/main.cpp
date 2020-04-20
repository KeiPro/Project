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
	dealer.CardShuffle(); //카드 셔플
	
	Player* p = phead; //이 포인터를 통해 순서대로 접근할 수 있도록 한다.
	gameController.InputMoney(&phead, p, 2000); //플레이어에게 금액 부여
	
	gameController.BaseBetting(phead, p, dealer);
	gameController.CurrentStatePrint(phead, p, dealer);
	dealer.CardDividing(phead, p); //카드 분배

	////게임 진행 함수
	//while (1)
	//{
	//	5


	//}
	
	//cout << endl;
	//cout << phead->GetMyFirstCard().GetShape() << " " << phead->GetMyFirstCard().GetNum() << ", " << phead->GetMySecondCard().GetShape() << " " << phead->GetMySecondCard().GetNum() << endl;
	//p = p->GetLink();
	//
	//for ( ; p != phead ; )
	//{
	//	cout << p->GetMyFirstCard().GetShape() << " " << p->GetMyFirstCard().GetNum() << ", " << p->GetMySecondCard().GetShape() << " " << p->GetMySecondCard().GetNum() << endl;
	//	p = p->GetLink();
	//}




	return 0;
}