#pragma once
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <string>

#define TYPE_COUNT 4
#define CARD_EACH_NUMBER 13
#define INIT_MONEY 2000
#define BASE_GAME_MONEY 200

using namespace std;

enum CARD_TYPE { SPADE, DIAMOND, HEART, CLOVER };

struct Card
{
	int cardNumber; //카드의 숫자
	string type; //카드의 모양
};