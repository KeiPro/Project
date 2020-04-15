#include "Walnambbong.h"

void CardBaseSetting(Card** card); //�⺻���� ī�� �غ� �Լ����� // 1~13 ���ʴ�� ���õ�.

int main()
{
#pragma region �⺻ ���� �� �ʱ�ȭ ���� - �÷��̾� ����, ��ǻ�� ����, ���ӸŴ��� ����

	srand(time(NULL));

	Player player; //�÷��̾� ��ü ����.
	int playerTotalNumber; //�÷��̾� �� �� �Է� ����
	string playerName; //�÷��̾� �̸��� �Է¹��� ����

	cout << "�÷��̾��� �̸��� �Է��� �ּ��� : ";
	cin >> playerName;
	player.SetNameSetting(playerName); //�̸� ����
	player.SetMoneySetting(INIT_MONEY); //�ʱ� ������ ����
	player.SetCardSetting({ 0, -1 }, {0, -1}); //�÷��̾� ī�� �ʱ�ȭ

	cout << "����� �÷��̾��� ���� �Է��� �ּ��� : ";
	cin >> playerTotalNumber;

	Player* comPlayer = new Player[playerTotalNumber]; //Player�����ͷ� comPlayer�� �����Ҵ�

	//��ǻ�� �ʱ�ȭ
	for (int i = 0; i < playerTotalNumber; i++)
	{
		comPlayer[i].SetNameSetting("com" + to_string(i+1)); //��ǻ�� �̸� �ʱ�ȭ
		comPlayer[i].SetMoneySetting(INIT_MONEY); // ��ǻ�� ������ �ʱ�ȭ
		comPlayer[i].SetCardSetting({ 0, -1 }, {0, -1}); //ī�� �ʱ�ȭ
		//cout << comPlayer[i].GetName() << endl;
	}

	//���� �޴��� �ʱ�ȭ�� �Ͼ�� �ȴ�.
	 //���ӸŴ��� ��ü ���� �� �ʱ�ȭ.
	GameManager gm{0 ,0, TYPE_COUNT * CARD_EACH_NUMBER, TYPE_COUNT * CARD_EACH_NUMBER, playerTotalNumber + 1 , playerTotalNumber + 1, 0};

#pragma endregion

	//ī�� �����Ҵ�
	Card** card = new Card*[4];
	for (int i = 0; i < 4; i++)
		card[i] = new Card[13];

	CardBaseSetting(card); //�⺻ ī�� ����. �����̵�~Ŭ�ιٱ���, ���� ������� �Ǿ��ִ� �� ī�� �غ�.
	gm.CardSuffle(card); //ī�� ����

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
//	
#pragma region �⺻ ������ �ϴ� ����
//
//		// 2.���ӿ� ������ �ؾ��ϹǷ� �� �÷��̾�� ������ -200�� �Ѵ�.
		player.BaseVetting(&gm);
		//cout << gm.GetRemainingPlayerNumber();
		for (int i = 0; i < gm.GetRemainingPlayerNumber()-1; i++)
		{
			comPlayer[i].BaseVetting(&gm);
		}

#pragma endregion

#pragma region �� �÷��̾ �����ϴ� ����

		gm.SetFirstPlayer(rand()%4);
		if (gm.GetFirstPlayer() == 0)
		{
			cout << "����� �� �÷��̾� �Դϴ�." << endl;
		}
		else
		{
			cout << comPlayer[gm.GetFirstPlayer()-1].GetName() << "�� �� �÷��̾� �Դϴ�." << endl;
		}

#pragma endregion

#pragma region ���� �Ŵ����� ī�带 �����ִ� ����

		gm.CardDividing(card , &player, comPlayer, gm.GetRemainingPlayerNumber());
		
		gm.SetRemainingCardNumeber(gm.GetRemainingCardNumber() - gm.GetRemainingPlayerNumber() * 2);
		cout << gm.GetRemainingCardNumber();

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