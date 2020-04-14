#include "Walnambbong.h"

void CardBaseSetting(Card** card); //�⺻���� ī�� �غ� �Լ����� // 1~13 ���ʴ�� ���õ�.

int main()
{
	srand(time(NULL));

	Player player{0, 0, 0}; //�÷��̾� ��ü ����.
	int playerTotalNumber; //�÷��̾� �� �� �Է� ����
	string playerName; //�÷��̾� �̸��� �Է¹��� ����

	cout << "�÷��̾��� �̸��� �Է��� �ּ��� : ";
	cin >> playerName;
	player.SetNameSetting(playerName); //�̸� ����
	player.SetMoneySetting(INIT_MONEY); //�ʱ� ������ ����
	player.SetCardSetting(); //�÷��̾� ī�� �ʱ�ȭ

	cout << "����� �÷��̾��� ���� �Է��� �ּ��� : ";
	cin >> playerTotalNumber;

	Player* comPlayer = new Player[playerTotalNumber]; //Player�����ͷ� comPlayer�� �����Ҵ�

	//��ǻ�� �ʱ�ȭ
	for (int i = 0; i < playerTotalNumber; i++)
	{
		comPlayer[i].SetNameSetting("com"+(i+1)); //��ǻ�� �̸� �ʱ�ȭ
		comPlayer[i].SetMoneySetting(INIT_MONEY); // ��ǻ�� ������ �ʱ�ȭ
		comPlayer[i].SetCardSetting(); //ī�� �ʱ�ȭ
	}

	//���� �޴��� �ʱ�ȭ�� �Ͼ�� �ȴ�.
	 //���ӸŴ��� ��ü ���� �� �ʱ�ȭ.
	GameManager gm{ 0, TYPE_COUNT * CARD_EACH_NUMBER, TYPE_COUNT * CARD_EACH_NUMBER, playerTotalNumber + 1 , playerTotalNumber + 1 };
	
	cout << gm.GetGameTotalMoney() << ", " << gm.GetTotalPlayerNumber() << ", " << gm.GetTotalCardNumber() << ", " << gm.GetRemainingPlayerNumber() << ", " << gm.GetRemainingCardNumebr() << endl;


	//ī�� �����Ҵ�
	Card** card = new Card*[4];
	for (int i = 0; i < 4; i++)
		card[i] = new Card[13];

	CardBaseSetting(card); //�⺻ ī�� ����. �����̵�~Ŭ�ιٱ���, ���� ������� �Ǿ��ִ� �� ī�� �غ�.
	gm.CardSuffle(card); //ī�� ����

	

	
	//ī�� �����Ҵ� ����
	for (int i = 0; i < 4; i++)
		delete[] card[i];

	delete[] card;
	delete[] comPlayer;
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