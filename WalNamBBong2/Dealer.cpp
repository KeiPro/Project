#include "Dealer.h"

void Dealer::CardSetting()
{
	for (int i = 0; i < CARD_TOTAL_NUMBER; i++)
	{
		cards[i].SetNum(i % 13 + 1);
		switch (i / 13)
		{
			case 0:
				cards[i].SetShape("¢¼");
				break;

			case 1:
				cards[i].SetShape("¡ß");
				break;

			case 2:
				cards[i].SetShape("¢¾");
				break;

			case 3:
				cards[i].SetShape("¢À");
				break;
		}
	}
}

void Dealer::Print()
{
	for (int i = 0; i < CARD_TOTAL_NUMBER; i++)
	{
		cout << cards[i].GetShape() << " " << cards[i].GetNum() << " ";
		if ((i + 1) % 13 == 0)
			cout << endl;
	}
}

void Dealer::CardShuffle()
{
	int rand1;
	int rand2;
	Card tmp;

	for (int i = 0; i < 1000; i++) 
	{
		rand1 = rand() % 52;
		rand2 = rand() % 52;

		tmp = cards[rand1];
		cards[rand1] = cards[rand2];
		cards[rand2] = tmp;

		//Print();
		//Sleep(10);
		//system("cls");
	}
}

Card Dealer::Distribuing()
{
	return cards[distribute++];
}

void Dealer::AddingTotalMoney(int money)
{
	gameTotalMoney += money;
}

Dealer::Dealer(int _distribute = 0, int _gameTotalMoney = 0)
	: distribute {_distribute} , gameTotalMoney{_gameTotalMoney}
{
	cards = new Card[52];
}

Dealer::~Dealer()
{
	delete[] cards;
}
