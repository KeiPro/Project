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
	
	Player* p = phead; //�� �����͸� ���� ������� ������ �� �ֵ��� �Ѵ�.
	gameController.InputMoney(&phead, p, 2000); //�÷��̾�� �ݾ� �ο�
	
	int playerNumber = 0; //�ӽ������� �� ��° �÷��̾����� �����ֱ� ���� ����
	bool bettingCall = false;

	//���� ���� �Լ�
	while (1)
	{
		//�ǵ��� 0���̸�.
		if (dealer.GetGameTotalMoney() == 0)
		{
			//���� ī�� ���� ���� �÷��̾��� 3�� ���� ������
			if ((CARD_TOTAL_NUMBER - dealer.GetDistribute()) < gameController.GetLeftPlayerNum() * 3)
			{
				dealer.CardShuffle(); //ī�� ����
				dealer.SetDistribute(0);
				gameController.CurrentStatePrint(phead, p, dealer); //���� ��Ȳ ����Ʈ
				gameController.BaseBetting(phead, p, dealer); //�⺻ ����
				gameController.CurrentStatePrint(phead, p, dealer); //���� ��Ȳ ����Ʈ
				dealer.CardDividing(phead, p); //ī�� �й�
			}
			else
			{
				gameController.CurrentStatePrint(phead, p, dealer); //���� ��Ȳ ����Ʈ
				gameController.BaseBetting(phead, p, dealer); //�⺻ ����
				gameController.CurrentStatePrint(phead, p, dealer); //���� ��Ȳ ����Ʈ
				dealer.CardDividing(phead, p); //ī�� �й�
			}
		}
		else if ( p == phead ) //�ѹ��� ���� �ٽ� �� ó������ ���ƿ�����
		{
			//���� ī�� ���� ���� �÷��̾��� 3�� ���� ������
			if ((CARD_TOTAL_NUMBER - dealer.GetDistribute()) < gameController.GetLeftPlayerNum() * 3)
			{
				dealer.CardShuffle(); //ī�� ����
				dealer.SetDistribute(0);
				gameController.BaseBetting(phead, p, dealer); //�⺻ ����
				gameController.CurrentStatePrint(phead, p, dealer); //���� ��Ȳ ����Ʈ
				dealer.CardDividing(phead, p); //ī�� �й�
			}
			else
			{
				dealer.CardDividing(phead, p); //ī�� �й�
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