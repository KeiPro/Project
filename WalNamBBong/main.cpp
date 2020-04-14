#include "Walnambbong.h"

void CardBaseSetting(Card** card); //기본적인 카드 준비 함수원형 // 1~13 차례대로 세팅됨.

int main()
{
	srand(time(NULL));

	Player player{0, 0, 0};
	GameManager gm;

	//카드 동적할당
	Card** card = new Card*[4];
	for (int i = 0; i < 4; i++)
		card[i] = new Card[13];

	CardBaseSetting(card); //기본 카드 세팅. 스페이드~클로바까지, 숫자 순서대로 되어있는 새 카드 준비.
	gm.CardSuffle(card);
	
	//카드 동적할당 해제
	for (int i = 0; i < 4; i++)
		delete[] card[i];

	delete[] card;
}

void CardBaseSetting(Card** card) //기본적인 카드 준비 함수
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