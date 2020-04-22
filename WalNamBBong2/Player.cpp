#include "Player.h"

Player::Player()
{
	nextLink = nullptr;
	prevLink = nullptr;
	name = "";
	myMoney = 0;
	bettingJudge = false;
	bettingMoney = 0;
	isAlive = true;
	turn = 0;
}
