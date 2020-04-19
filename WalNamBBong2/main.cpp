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
	dealer.CardSetting();
	dealer.CardShuffle();
	
	Player* p = phead;

	//for (int i = 0; i < gameController.GetInputTotalNum(); i++)
	//{
	//	cout << p->GetName() << ", ";
	//	p = p->GetLink();
	//	if ((i + 1) % 5 == 0)
	//		cout << endl;
	//}


	return 0;
}