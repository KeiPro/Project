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
	dealer.CardSetting(); //�⺻ ī�� ����
	dealer.CardShuffle(); //ī�� ����
	
	Player* p = phead; //�� �����͸� ���� ������� ������ �� �ֵ��� �Ѵ�.
	gameController.InputMoney(&phead, p, 2000); //�÷��̾�� �ݾ� �ο�
	
	gameController.BaseBetting(phead, p, dealer);
	gameController.CurrentStatePrint(phead, p, dealer);
	dealer.CardDividing(phead, p); //ī�� �й�

	////���� ���� �Լ�
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