#include "Dealer.h"
#include "Player.h"
#include "GameController.h"

int main()
{
	srand((unsigned)time(NULL));

	Player player; //�÷��̾� ��ü ����
	GameController gameController; // ���� ��Ʈ�ѷ� ��ü ����
	Player* phead = nullptr; //�������Ḯ��Ʈ�� ���Ǳ� ���� ����. �� ������� Ȱ��Ǳ� ���ؼ� ���δ�.

	gameController.InputNamePrint(&player); // �÷��̾� �̸� ����.
	gameController.InputTotalNum(); //�� �÷��̾��� �� �Է� �Լ� --> ��ǻ�͵��� ��ü ����
	gameController.TurnSetting(&player, &phead); //���� ������ �ȴ�.

	Dealer dealer(0, 0); //���� ��ü ����
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