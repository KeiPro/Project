#include "Dealer.h"
#include "Player.h"
#include "GameController.h"

int main()
{
	srand(time(NULL));

	Player player; //플레이어 객체 생성
	GameController gameController; // 게임 컨트롤러 객체 생성

	gameController.InputNamePrint(&player); // 플레이어 이름 설정.
	gameController.InputTotalNum(); //총 플레이어의 수 입력 함수 --> 컴퓨터들의 객체 생성
	gameController.TurnSetting(&player);

	Dealer dealer(0, 0); //딜러 객체 생성
	dealer.CardSetting();
	dealer.CardShuffle();
	
	gameController.TurnSetting(&player);



	return 0;
}