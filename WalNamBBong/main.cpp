#include "Walnambbong.h"
#include "Player.h"
#include "GameManager.h"

void CardBaseSetting(Card** card); //�⺻���� ī�� �غ� �Լ����� // 1~13 ���ʴ�� ���õ�.

int main()
{
#pragma region �⺻ ���� �� �ʱ�ȭ ���� - �÷��̾� ����, ��ǻ�� ����, ���ӸŴ��� ����

	srand(time(NULL));

	Player player; //�÷��̾� ��ü ����.
	int playerTotalNumber; //�÷��̾� �� ���� �Է� ����
	string playerName; //�÷��̾� �̸��� �Է¹��� ����
	int vettingCall;
	int gameProgress; //���� ��� �����ϳ�?

	cout << "�÷��̾��� �̸��� �Է��� �ּ��� : ";
	cin >> playerName;
	player.SetNameSetting(playerName); //�̸� ����
	player.SetMoneySetting(INIT_MONEY); //�ʱ� ������ ����
	player.SetCardSetting({ 0, "" }, {0, ""}); //�÷��̾� ī�� �ʱ�ȭ
	player.SetIsAlive(true);

	cout << "����� �÷��̾��� ���� �Է��� �ּ��� : ";
	cin >> playerTotalNumber;

	Player* comPlayer = new Player[playerTotalNumber]; //Player�����ͷ� comPlayer�� �����Ҵ�

	//��ǻ�� �ʱ�ȭ
	for (int i = 0; i < playerTotalNumber; i++)
	{
		comPlayer[i].SetNameSetting("com" + to_string(i+1)); //��ǻ�� �̸� �ʱ�ȭ
		comPlayer[i].SetMoneySetting(INIT_MONEY); // ��ǻ�� ������ �ʱ�ȭ
		comPlayer[i].SetCardSetting({ 0, "" }, {0, ""}); //ī�� �ʱ�ȭ
		comPlayer[i].SetIsAlive(true);
		//cout << comPlayer[i].GetName() << endl;
	}

	//���� �Ŵ��� �ʱ�ȭ�� �Ͼ�� �ȴ�.
	//���ӸŴ��� ��ü ���� �� �ʱ�ȭ.
	GameManager gm{0 ,0, TYPE_COUNT * CARD_EACH_NUMBER, TYPE_COUNT * CARD_EACH_NUMBER, playerTotalNumber + 1 , playerTotalNumber + 1, 0};
	//gm.SetLeftMoneyIsTrue(true);

#pragma endregion

	//ī�� �����Ҵ�
	Card** card = new Card*[4];
	for (int i = 0; i < 4; i++)
		card[i] = new Card[13];

	CardBaseSetting(card); //�⺻ ī�� ����. �����̵�~Ŭ�ιٱ���, ���� ������� �Ǿ��ִ� �� ī�� �غ�.
	gm.CardSuffle(card); //ī�� ����

#pragma region �⺻ �� �÷��̾� ��������
	int turn = rand() % 4; // 0 ~ 3
	gm.SetFirstPlayer(turn);

	//if (gm.GetFirstPlayer() == 0)
	//{
	//	cout << "����� �� �÷��̾� �Դϴ�." << endl;
	//}
	//else
	//{
	//	cout << comPlayer[gm.GetFirstPlayer() - 1].GetName() << "�� �� �÷��̾� �Դϴ�." << endl;
	//}
#pragma endregion
	
#pragma region ������ ����Ǵ� ����
	while (1)
	{
#pragma region ī�� ����

		// 1.�����ִ� ī���� ������ �� �÷��̾� �� * 3���� ������ ī�� ������ �Ͼ��.
		if (gm.GetRemainingCardNumber() < gm.GetRemainingPlayerNumber() * 3)
		{
			gm.CardSuffle(card); //ī�� ����
			gm.SetXPositionYPosition(0, 0); //�ٽ� 0, 0��ġ�� ����Ű���� ����.
		}
//
#pragma endregion

#pragma region �⺻ ������ �ϴ� ����

		//�ǿ� �ܿ� �ݾ��� �������� ������
		if (gm.GetGameTotalMoney() <= 0)
		{
			// 2.���ӿ� ������ �ؾ��ϹǷ� �� �÷��̾�� ������ -200�� �Ѵ�.
			if (player.GetIsAlive())
			{
				player.BaseVetting(&gm);
				cout << "�÷��̾� �⺻ ���� 200" << endl;
				Sleep(1000);
			}

			for (int i = 0; i < gm.GetTotalPlayerNumber() - 1; i++)
			{
				if (comPlayer[i].GetIsAlive())
				{
					comPlayer[i].BaseVetting(&gm);
					cout << comPlayer[i].GetName() << " �⺻���� 200" << endl;
					Sleep(1000);
				}
			}

			//ī�� �й�
			gm.CardDividing(card, &player, comPlayer);
		}
		
		cout << "���� �� �� : " << gm.GetGameTotalMoney() << endl;
		Sleep(2000);

#pragma endregion
		
		
	//�� �÷��̾�� ī�� ���
	/*
	//for (int i = 0; i < gm.GetTotalPlayerNumber(); i++)
	//{
	//	if (i == 0) 
	//	{
	//		cout << player.GetFirstCard().type << ", " << player.GetFirstCard().cardNumber << endl;
	//		cout << player.GetSecondCard().type << ", " << player.GetSecondCard().cardNumber << endl;
	//	}
	//	else
	//	{
	//		cout << comPlayer[i-1].GetFirstCard().type << ", " << comPlayer[i - 1].GetFirstCard().cardNumber << endl;
	//		cout << comPlayer[i-1].GetSecondCard().type << ", " << comPlayer[i - 1].GetSecondCard().cardNumber << endl;
	//	}
	//	cout << endl;
	//}
	//gm.SetRemainingCardNumeber(gm.GetRemainingCardNumber() - gm.GetRemainingPlayerNumber() * 2);
	//cout << "���� ī�� ���� : " << gm.GetRemainingCardNumber(); //���� ī���� ���� ���
	*/

#pragma region ���� true? false?
		gameProgress = gm.PlayerGameStart(card, &player, comPlayer);
		
		switch (gameProgress)
		{ 
			case 0: // ���ڷ�� �¸�.
				// �¸��� ����� �� �÷��̾ �ȴ�.
				cout << "���ڷ�!" << endl; 
				player.PullMoney(gm.GetGameTotalMoney()); //�ǵ��� �ö���ִ� ��� ���� �� �ް�,
				gm.PullGameTotalMoney(-gm.GetGameTotalMoney()); //���� �Ŵ��������� �� ��ŭ �ǵ��� ������ �ȴ�.
				continue;
				break;

			case 1: // ���� ����
				cout << "����!!" << endl;
				break;

			case 2: // ����
				
				cout << "����!!" << endl;
				break;

		}		
#pragma endregion

#pragma region ���� ���� ����



#pragma endregion


		break;
	}
#pragma endregion

	delete[] comPlayer;
	//ī�� �����Ҵ� ����
	for (int i = 0; i < 4; i++)
		delete[] card[i];

	delete[] card;

}

void CardBaseSetting(Card** card) //�⺻���� ī�� �غ� �Լ�
{
	for (int i = 0; i < TYPE_COUNT; i++)
	{
		for (int j = 0; j < CARD_EACH_NUMBER; j++)
		{
			card[i][j].cardNumber = (j + 1);
			
			switch (i)
			{
			case CARD_TYPE::SPADE:
				card[i][j].type = "��";
				break;

			case CARD_TYPE::DIAMOND:
					card[i][j].type = "��";
					break;

			case CARD_TYPE::HEART:
				card[i][j].type = "��";
				break;

			case CARD_TYPE::CLOVER:
				card[i][j].type = "��";

				break;

			}
		}
	}
}