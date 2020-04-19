#include "Dealer.h"
#include "Player.h"
#include "GameController.h"

int main()
{
	srand(time(NULL));

	Player player; //�÷��̾� ��ü ����
	GameController gameController; // ���� ��Ʈ�ѷ� ��ü ����

	gameController.InputNamePrint(&player); // �÷��̾� �̸� ����.
	gameController.InputTotalNum(); //�� �÷��̾��� �� �Է� �Լ� --> ��ǻ�͵��� ��ü ����
	gameController.TurnSetting(&player);

	Dealer dealer(0, 0); //���� ��ü ����
	dealer.CardSetting();
	dealer.CardShuffle();
	
	gameController.TurnSetting(&player);



	return 0;
}