#include "Walnambbong.h"

void CardBaseSetting(Card** card); //�⺻���� ī�� �غ� �Լ����� // 1~13 ���ʴ�� ���õ�.

int main()
{
	srand(time(NULL));

	Player player{0, 0, 0};
	GameManager gm;

	//ī�� �����Ҵ�
	Card** card = new Card*[4];
	for (int i = 0; i < 4; i++)
		card[i] = new Card[13];

	CardBaseSetting(card); //�⺻ ī�� ����. �����̵�~Ŭ�ιٱ���, ���� ������� �Ǿ��ִ� �� ī�� �غ�.
	gm.CardSuffle(card);
	
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