/*
	영웅은 구조적

	** 영웅은 절차적 2 : 영웅은 구조적
	1) 가로 * 세로 타일 사이즈를 원하게 설정할 수 있도록 만들자. (동적 할당)
	2) w, a, s, d이동
	***3) 배열, 구조체, 함수를 최대한 활용해보자.
	4) 전투는 가위 바위 보
	5) 몬스터는 포켓몬스터처럼 랜덤한 인카운터 방식. //이 타일에 들어갔을 때 확률에 따라서 만날수도 있고 안만날수도있고
	6) 타일에 종류가 있다. (숲, 늪, 땅) 마다 만나는 몬스터도 다르다. 숲에서 만나는 얘들 늪에서 만나는 얘들 ... 다 다르게
	7) 플레이어 속성 : 이름 / 최대 HP(레벨에 따라 증가) / 현재 HP / 경험치 / 레벨 / 골드
	8) 물약 : 이름 / 가격 / 회복치
	9) 몬스터 : 이름(포켓몬스터) / 최대 HP / 현재 HP / 획득 경험치 / 획득 골드 / 속성
	10) 상점 : 아이템 종류
*/

#include <iostream>
#include <string>
#include <Windows.h>
#include <ctime>
#include <conio.h>
#include <cmath>

#define MONSTERSIZE 16 
#define SHOPSIZE 3 //상점 3개

enum TILETYPE{ SHOP=1, LAND , WATER , FOREST, FLY }; //땅, 물, 숲, 비행
enum SRP { SCISSORS=1, ROCK, PAPER };

using namespace std;

//영웅 구조체
struct Hero
{
	string heroName{""}; //히어로 이름
	int level{0};
	int maxHp{0}; //최대체력
	int currentHp{0}; //현재체력
	int maxExp{0}; //다음 레벨업을 하기 위한 경험치
	int currentExp{0}; //경험치
	int myGold{0}; //재화
	int myXPosition{ 0 }, myYPosition{0}; //나의 x, y좌표
	int damage{0};
	bool freeMove;
};

//몬스터 구조체
struct Monster
{
	string monsterName{""}; //몬스터 이름
	int maxHp{0}; //몬스터의 최대체력
	int currentHp{0}; //몬스터의 현재체력
	int giveExp{0}; //몬스터의 경험치
	int giveGold{0}; //획득 골드
	int tileType{0}; //몬스터가 생존하고 있는 타일
	int monsterDmg{0}; //몬스터 데미지
};

//물약 구조체
struct Portion 
{
	string name; //물약의 이름
	int price; //물약 가격
	int healHp; //회복치
};

//상점 구조체
struct Shop
{
	int shopXPosition, shopYPosition;
};

void IntroEmoticon(); //시작 애니메이션
void RunEmoticon(); //도망가는 애니메이션
void WinEmoticon(); //승리 애니메이션
void GameStartPrint(); // 인트로 출력
void MapCreate(char** map, int width, int height, int* tilePositionSave, Shop* shop); //맵 동적할당 함수 원형
void MapFree(char** map, int width, int height); //맵을 해제하는 함수 원형
void Settings(Hero* hero, Monster* monster, string monsterName[], int area); // 히어로와 몬스터를 세팅하기 위한 함수
void HeroSetting(Hero* hero, int count); //히어로를 세팅하기 위해 area값을 넘겨주기 위한 함수
void MonsterSetting(Monster* monster, string monsterName[], int count); //몬스터를 세팅하기위해 area값을 넘겨주기 위한 함수
void MapPrint(char** map, int width, int height, Hero* hero); //맵 출력 함수
int CharacterMove(Hero* hero, char* move, char** map, int width, int height, int* tilePositionSave, int*, int*); //캐릭터 움직임 계산 함수 원형
void Move(Hero* hero, char** map, int* tilePositionSave, int y, int x, int*, int*); //실제로 움직이는 코드
void FightAndShop(Hero* hero, Monster* monster, int moveResult, int* tilePositionSave, char** map, int*, int*); //상점 방문 or 몬스터와 싸울 함수
void ShopVisit(Hero* hero); //상점을 방문했을 때
void MonsterMeet(Hero* hero, Monster* monster, int monsterType, int* tilePositionSave); //몬스터와 만나는 함수 원형
inline bool RandResult(int result); //몬스터를 만날 확률을 구하는 함수
bool Fight(Hero* hero, Monster* monster, int monNumber); //전투함수
bool Draw(Hero* hero, Monster* monster, int monNumber, int result); //가위바이보 비김 함수
bool Win(Hero* hero, Monster* monster, int monNumber, int result); //가위바위보 이김 함수
bool Defeat(Hero* hero, Monster* monster, int monNumber, int result); //가위바위보 패배 함수
void LevelUp(Hero* hero); //레벨업 함수


void MyCode(Hero* hero)
{
	string mySecretCode = "20";
	string inputPassword;
	
	string inputStringPrint = " InputCode : ";
	
	cout << endl;
	cout << " 왈도 : 힘쎄고 강한아침 만일 내게 물어보면 나는 왈도." << endl;
	Sleep(1500);
	cout << "\t써라, 기수 너의." << endl;
	Sleep(1500);
	cout << "\t준다, 나랑 같으면 보상." << endl;
	Sleep(2000);
	cout << endl;
	cout << " < 코드 입력 성공 시 공격력 +1, 돈 1000획득! >" << endl;
	cout << "   ( 힌트 : 현재 경일 게임아카데미의 기수 )" << endl;
	cout << endl;

	Sleep(2000);

	for (int i = 0; i < inputStringPrint.size(); i++)
	{
		cout << inputStringPrint.at(i);
		Sleep(100);
	}

	cin >> inputPassword;

	if (inputPassword == mySecretCode)
	{
		cout << endl;
		cout << " < 코드 입력 완료!! >" << endl;
		cout << endl;
		int tmp = hero->damage;
		(hero->damage)++;

		cout << " 영웅 공격력 : " << tmp << " -> " << hero->damage << endl;
		cout << " 돈 1000획득!" << endl;
		
		hero->myGold += 1000;

		Sleep(2000);
	}
	else
	{
		cout << endl;
		cout << "코드 입력 실패..";
		Sleep(2000);
	}
}

int monsterCount = 0; //총 몬스터 마리수 전역변수 설정

int main()
{
	srand(time(NULL));
	Hero hero;
	Monster* monster;
	Shop* shop = nullptr;
	string monsterName[] = { "모래두지", "닥트리오", "딱구리", "뿔카노", //monsterName[0] ~ monsterName[3] : 땅
		"수륙챙이", "야도란", "킹크랩", "아쿠스타",					 //monsterName[4] ~ monsterName[7] : 물
		"독침붕", "콘팡", "라플레시아", "독파리",						 //monsterNmae[8] ~ monsterName[11] : 숲
		"망나뇽", "버터플", "리자몽", "갸라도스"};						 //monsterName[12] ~ monsterName[15] : 비행
	
	monster = new Monster[MONSTERSIZE];
	shop = new Shop[SHOPSIZE];

	int saveXPosition = 0, saveYPosition = 0; //움직일때마다 전 좌표를 저장해놓을 변수
	int width;
	int height;

	GameStartPrint();

	while (1)
	{
		cout << " >> 가로 입력 : ";
		cin >> width;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "숫자를 다시 입력해 주세요." << endl;
			Sleep(1000);
			cout << endl;
		}
		else
			break;
	}
	while (1)
	{
		cout << " >> 높이 입력 : ";
		cin >> height;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "숫자를 다시 입력해 주세요." << endl;
			Sleep(1000);
			cout << endl;
		}
		else
			break;
	}
	
	
	hero.myXPosition = 0, hero.myYPosition = 0; //나의 위치 초기화
	int tilePositionSave = 0;
	char** map = new char*[height]; //2차원 배열 동적할당 하기 위한 이중 포인터 변수
	MapCreate(map, width, height, &tilePositionSave, shop); //맵 동적할당 함수

#pragma region 이 사이에서 게임이 이루어진다.

	Settings( &hero, monster, monsterName , width * height); //히어로와 몬스터 세팅 함수

	char move; //움직임을 받는 변수 CharacterMove함수의 변수로 활용.
	int moveResult; //움직이고 나서 나온 반환값을 받을 변수 // 1 = Shop, 2 = Land, 3 = Water, 4 = Forest, 5 = Fly;

	MyCode(&hero);
	
	//for (int i = 0; i < MONSTERSIZE; i++)
	//{
	//	monster[i].giveExp = 2000;
	//}

	//몬스터 능력치 확인 코드
	/*for (int i = 0; i < MONSTERSIZE; i++)
	{
		cout << "이름 : " << (*(monster+i)).monsterName << ", 최대 체력 : " << monster[i].maxHp << ", 현재 체력 : " << monster[i].currentHp
			<< ", 몬스터 경험치 : " << monster[i].giveExp << ", 획득 골드 : " << monster[i].giveGold << ", 타일 : " << monster[i].tileType << endl;
	}*/

	//Sleep(2000);
	
	IntroEmoticon();
	////////////////////////////////////// 게임 진행 ////////////////////////////////////////////////
	while (1)
	{
		system("cls");
		MapPrint(map, width, height, &hero); //맵 출력 함수
		moveResult = CharacterMove(&hero, &move, map, width, height, &tilePositionSave, &saveXPosition, &saveYPosition); //캐릭터가 움직이는 함수
		if(moveResult != 0)
			FightAndShop(&hero, monster, moveResult, &tilePositionSave, map, &saveXPosition, &saveYPosition) ; //움직이고 난 후의 타일이 상점인지 몬스터인지
	}

#pragma endregion
	MapFree(map, width, height); //맵 해제 함수
	   	  
	delete[] shop;
	delete[] monster;
	return 0;
}

//맵을 출력하는 함수
void MapPrint(char** map, int width, int height, Hero* hero)
{
	cout << endl;
	cout << " < 영웅 정보 > " << endl;
	cout << endl;
	cout << " - 이름 : \t" << hero->heroName << "\t - 레벨 : \t" << hero->level << endl;
	cout << " - 공격력 : \t" << hero->damage << "\t - 현재 체력 : \t" << hero->currentHp << endl;
	cout << " - 현재 경험치 : " << hero->currentExp  << "\t - 목표 경험치 : " << hero->maxExp << endl;
	cout << " - 소유한 골드 : " << hero->myGold << endl;
	cout << endl;
	cout << endl;
	cout << " < 설  명 >  " << endl;
	cout << endl;
	cout << " - 키 설명 : (w, a, s, d : 이동, g : 영웅 투명화)" << endl;
	cout << " - 케릭터 모양 : (● : 영웅, ◎ : 영웅 투명화)" << endl;
	cout << " - 상점   모양 : (♨ : 상점)" << endl;
	cout << " - 타일   모양 : (□ : 땅, ㆀ : 물, ♧ : 숲, ＾ : 비행) " << endl;
	cout << endl;
	cout << endl;
	cout << " - 남은 몬스터 수 : " << monsterCount << "마리" << endl;
	cout << endl;
	cout << endl;
	for (int i = 0; i < height; i++)
	{
		cout << " ";
		for (int j = 0; j < width; j++)
		{
			switch (map[i][j])
			{
				case 0:	cout << "●";  break; // 케릭터

				case 1:	cout << "♨"; break; // 상점

				case TILETYPE::LAND: cout << "□"; break; // 땅

				case TILETYPE::WATER: cout << "ㆀ"; break; //물
					
				case TILETYPE::FOREST: cout << "♧"; break; //숲
					
				case TILETYPE::FLY: cout << "＾"; break; //비행
					
				case 6:	cout << "◎"; break;//케릭터 투명화
					
			}
		}
		cout << endl;
	}


}

//맵 동적할당 및 세팅함수
void MapCreate(char** map, int width, int height, int* tileSavePosition, Shop* shop)
{
	for (int i = 0; i < height; i++)
		*(map + i) = new char[width];

	//땅 초기화
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (rand() % 100 < 50) //땅 50%생성
			{
				map[i][j] = TILETYPE::LAND;
			}
		}
	}

	//바다 초기화
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (map[i][j] != TILETYPE::LAND && (rand() % 100 < 30)) //바다 30%생성
			{
				map[i][j] = TILETYPE::WATER;
			}
		}
	}

	//숲 초기화
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (map[i][j] != TILETYPE::LAND && map[i][j] != TILETYPE::WATER && ( rand() % 100 < 30)) //숲 30%생성
			{
				map[i][j] = TILETYPE::FOREST;
			}
		}
	}

	//비행 초기화
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (map[i][j] != TILETYPE::LAND && map[i][j] != TILETYPE::WATER && map[i][j] != TILETYPE::FOREST) //나머지 비행타일 생성
			{
				map[i][j] = TILETYPE::FLY;
			}
		}
	}

	int count = 0;
	//상점 위치 설정
	for (int i = 0; i < SHOPSIZE; i++)
	{
		shop[i].shopXPosition = rand() % width, shop[i].shopYPosition = rand() % height;
		
		//1 - 상점의 위치가 나의 위치와 겹치지 않게 좌표 설정
		while ((shop[i].shopXPosition == 0) && (shop[i].shopYPosition == 0) )
		{
			shop[i].shopXPosition = rand() % width; shop[i].shopYPosition = rand() % height; 
		}

		if (i != 0)
		{
			for (int j = 0; j < i ; j++) //상점이 겹치지 않게 설정
			{
				while ( ((shop[i].shopXPosition == 0) && (shop[i].shopYPosition == 0))
					|| ((shop[i].shopXPosition == shop[j].shopXPosition) && (shop[i].shopYPosition == shop[j].shopYPosition)))
				{
					shop[i].shopXPosition = rand() % width; shop[i].shopYPosition = rand() % height;
					j = 0;
				}
			}
		}
	}
	
	for (int i = 0; i < SHOPSIZE; i++)
	{
		map[shop[i].shopYPosition][shop[i].shopXPosition] = 1;
	}

	*tileSavePosition = map[0][0]; //내 위치에 대한 타일의 값을 저장
	map[0][0] = 0; //내 위치 설정
}

//맵 메모리 해제
void MapFree(char** map, int width, int height)
{
	//동적할당 메모리 해제
	for (int i = 0; i < height; i++)
	{
		delete[] map[i];
	}
	delete[] map;
}

//히어로 및 몬스터를 세팅하는 함수
void Settings(Hero* hero, Monster* monster, string monsterName[] ,int area)
{
	int count = 0;

	if (area > 100)
	{
		while (area > 100)
		{
			area -= 100;
			count++;
		}
		monsterCount = (count + 1) * 10; //밸런스
	}
	else
	{
		while (area > 0)
		{
			area -= 10;
			count++;
		}
		monsterCount = (count + 1) * 2; //밸런스
	}
	
	HeroSetting(hero, count); //히어로 초기화 및 세팅
	MonsterSetting(monster, monsterName, count); //몬스터 초기화 및 세팅
}

//히어로 세팅 함수
void HeroSetting(Hero* hero = nullptr, int count = 0)
{
	cout << " >> 히어로의 이름을 입력해 주세요 : ";
	cin >> hero->heroName;

	hero->maxHp = 100 + count * 10; //히어로의 기본 체력은 최소 100의 체력을 가지고 있는다. 
	hero->level = 1; //레벨 1로 세팅.
	hero->currentHp = hero->maxHp; //세팅 시에는 현재 체력이 맥스 체력이어야 한다.
	hero->maxExp = 1600;  //1000 설정
	hero->damage = 1;
	hero->currentExp = 0; //현재 경험치
	hero->myGold = 0; //현재 골드
	hero->myXPosition = 0, hero->myYPosition = 0; //영웅의 좌표
	hero->freeMove = false;
}

//몬스터 세팅함수
void MonsterSetting(Monster* monster, string monsterName[], int count)
{
	int j = 0;

	for (int i = 0; i < MONSTERSIZE; i++)
	{
		(monster + i)->monsterName = monsterName[i];
		(monster + i)->tileType = TILETYPE(j);
		(monster + i)->maxHp = (rand() % 2 + (int)ceil(j*1.5f) + i/2) + count/2; //땅 포켓몬은 체력이 1~2가 된다.
		(monster + i)->currentHp = (monster + i)->maxHp;
		(monster + i)->giveExp = (rand() % 100 + 100 + (i * 5) + j * 50) + (count * 50); //최소 경험치 100 //밸런스 조절
		(monster + i)->giveGold = (rand() % 10 + 10 + (i * 5)) + (count + 1) * 2; //최소 골드 획득
		(monster + i)->monsterDmg = count + 3;

		if ((i + 1) % 4 == 0)
		{
			j++; // TILETYPE을 1증가 시키기 위한 변수
		}
	}
}

//케릭터 움직임 함수
void Move(Hero* hero, char** map, int* tilePositionSave, int y, int x, int* saveXPosition, int* saveYPosition)
{
	map[hero->myYPosition][hero->myXPosition] = *tilePositionSave; //현재 내 위치에 *tilePositionSave값을 대입.
	*saveYPosition = hero->myYPosition, *saveXPosition = hero->myXPosition;
	(hero->myYPosition) += y; (hero->myXPosition) += x; //나의 위치를 x, y만큼 이동하여 저장.
	*tilePositionSave = map[hero->myYPosition][hero->myXPosition]; //타일 번호를 저장한다.
	if (hero->freeMove == true)
	{
		map[hero->myYPosition][hero->myXPosition] = 6;
	}
	else
		map[hero->myYPosition][hero->myXPosition] = 0;
}

//케릭터 움직임 계산 알고리즘
int CharacterMove(Hero* hero, char* move, char** map, int width, int height, int* tilePositionSave, int* saveXPosition, int* saveYPosition)
{
	*move = _getch();
	
	switch (*move)
	{
		case 'w':
			
			if (hero->myYPosition == 0)
			{
				return 0;
			}
			else
			{
				Move(hero, map, tilePositionSave, -1, 0, saveXPosition, saveYPosition);
			}

			break;

		case 'a':
			 
			if (hero->myXPosition == 0)
			{
				return 0;
			}
			else
			{
				Move(hero, map, tilePositionSave, 0, -1, saveXPosition, saveYPosition);
			}

			break;

		case 's':

			if (hero->myYPosition == height-1)
			{
				return 0;
			}
			else
			{
				Move(hero, map, tilePositionSave, 1, 0, saveXPosition, saveYPosition);
			}

			break;

		case 'd':

			if (hero->myXPosition == width - 1)
			{
				return 0;
			}
			else
			{
				Move(hero, map, tilePositionSave, 0, 1, saveXPosition, saveYPosition);
			}

			break;
		default: //자유롭게 움직이도록 설정하는 코드
			if ((*move == 'g') && (hero->freeMove == false))
			{
				hero->freeMove = true;
				map[hero->myYPosition][hero->myXPosition] = 6; //자유롭게 움직일 수 있는 이모티콘
				
			}
			else if (((*move) == 'g') && (hero->freeMove == true))
			{
				hero->freeMove = false;
				map[hero->myYPosition][hero->myXPosition] = 0;
				
			}
			return 0;
			break;
	}

	return (*tilePositionSave);
}

//타일에 접근 했을때
void FightAndShop(Hero* hero, Monster* monster , int moveResult, int* tilePositionSave, char** map, int* saveXPosition, int* saveYPosition)
{
	if (moveResult == SHOP)
	{
		ShopVisit(hero);
		if (hero->freeMove == true)
		{
			map[hero->myYPosition][hero->myXPosition] = 1; //shop
			*tilePositionSave = map[*saveYPosition][*saveXPosition];
			map[*saveYPosition][*saveXPosition] = 6; //투명한 영웅 표현
			hero->myYPosition = *saveYPosition, hero->myXPosition = *saveXPosition;
		}
		else
		{
			map[hero->myYPosition][hero->myXPosition] = 1; //shop
			*tilePositionSave = map[*saveYPosition][*saveXPosition];
			map[*saveYPosition][*saveXPosition] = 0; //영웅 표현
			hero->myYPosition = *saveYPosition, hero->myXPosition = *saveXPosition;
		}
	}
	else
	{
		if (hero->freeMove == false) {
			if (RandResult(moveResult) == true) //몬스터와 만날 확률을 통해 true이면
			{
				MonsterMeet(hero, monster, moveResult, tilePositionSave);
			}
			else	//몬스터 안만남
			{
				return;
			}
		}
	}
}

//몬스터와 만나는 함수
void MonsterMeet(Hero* hero, Monster* monster, int monsterType, int* tilePositionSave) 
{
	int randNum;
	int loop = 0;

	while (loop < 100)
	{
		randNum = rand() % 4; // 0~3
		loop++;
	}
	int selectFightOrRun;

	switch (monsterType)
	{
		case TILETYPE::LAND: break; //0~3
		case TILETYPE::WATER: randNum += 4; break;//4~7
		case TILETYPE::FOREST: randNum += 8; break;//8~11
		case TILETYPE::FLY: randNum += 12; break;//12~15

		default: break;
	}
	cout << endl;
	cout << monster[randNum].monsterName << "(이)가 출현했다!!!" << endl;

	Sleep(1000);

	while (1)
	{
		system("cls");
		cout << endl;
		cout << "\t < 몬스터 정보 > " << endl;
		cout << endl;
		cout << "\t- 이름 : " << monster[randNum].monsterName << endl;
		cout << "\t- 남은 체력 : " << monster[randNum].currentHp << endl;
		cout << "\t- 공격력 : " << monster[randNum].monsterDmg << endl;
		cout << "\t- 획득 골드 : " << monster[randNum].giveGold << endl;
		cout << "\t- 획득 경험치 : " << monster[randNum].giveExp << endl;
		cout << endl;
		cout << "\t < 영웅의 정보 > " << endl;
		cout << endl;
		cout << "\t- 이름 : " << hero->heroName << endl;
		cout << "\t- 레벨 : " << hero->level << endl;
		cout << "\t- 공격력 : " << hero->damage << endl;
		cout << "\t- 현재 체력 : " << hero->currentHp << endl;
		cout << "\t- 최대 체력 : " << hero->maxHp << endl;
		cout << "\t- 보유한 금액 : " << hero->myGold << endl;
		cout << "\t- 현재 경험치 : " << hero->currentExp << endl;
		cout << "\t- 목표 경험치 : " << hero->maxExp << endl;
		cout << endl;

		//오류처리
		while (1)
		{
			cout << " >> 싸우시겠습니까?(1) 도망가시겠습니까?(2) : ";
			cin >> selectFightOrRun;

			if (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
				cout << "숫자를 다시 입력해 주세요." << endl;
				Sleep(1000);
				cout << endl;
			}
			else
				break;
		}

		if (selectFightOrRun == 1)
		{
			if (Fight(hero, monster, randNum) == true) //이겼을 때 while 루프 종료
				break;
		}
		else if (selectFightOrRun == 2)
		{
			cout << endl;
			cout << hero->heroName << " : 하...다음에 다시보자.... " << endl;
			Sleep(1000);
			cout << endl;
			cout << monster[randNum].monsterName << " : 헤헤헤~ 바보!! 멍충이!!!! " << endl;
			Sleep(1000);
			RunEmoticon();
			break;
		}
		else
		{
			cout << endl;
			cout << "숫자를 다시 입력해 주세요. " << endl;
			Sleep(1000);
			continue;
		}
	}
}

void ShopVisit(Hero* hero) //상점을 방문했을 때
{
	int inputNumber; //입력받을 변수

	//상점에 대한 정보를 출력
	while (true)
	{
		system("cls");
		cout << endl;
		cout << "< 어서오세요~ " << hero->heroName << "님. 경일상점 입니다! >" << endl;
		cout << endl;
		cout << "=========================================" << endl;
		cout << "| 체력8  포션 회복하기(금액  10) : 1입력| " << endl;
		cout << "| hp만땅 포션 회복하기(금액 100) : 2입력|" << endl;
		cout << "| 데미지 1증가하기 (금액200원)   : 3입력| " << endl;
		cout << "| 상점 나가기\t\t\t : 4입력|" << endl;
		cout << "=========================================" << endl;
		cout << endl;
		cout << " * * < 영 웅 정 보 > * * " << endl;
		cout << endl;
		cout << "< - 이름 : " << hero->heroName << " > " << endl;
		cout << "< - 레벨 : " << hero->level << " > " << endl;
		cout << "< - 공격력 : " << hero->damage << " >" << endl;
		cout << "< - 현재 체력 / 총 체력 : " << hero->currentHp << " / " << hero->maxHp << " >" << endl;
		cout << "< - 남은 몬스터 수 : " << monsterCount << " >" << endl;
		cout << "< - 가진 금액 : " << hero->myGold << " >" << endl;

		cout << endl;

		while (1)
		{
			cout << "번호를 입력해 주세요 : ";
			cin >> inputNumber;
		
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
				cout << "숫자를 다시 입력해 주세요." << endl;
				Sleep(1000);
				cout << endl;
			}
			else
				break;
		}
		
		if (inputNumber == 1)
		{
			//돈이 없는 경우
			if (hero->myGold < 10)
			{
				cout << "금액이 부족합니다." << endl;
			}
			//체력이 full인 경우
			else if (hero->currentHp >= hero->maxHp)
			{
				cout << "체력이 풀 입니다." << endl;
			}
			//체력이 full이 아니고 돈도 충분한 경우
			else
			{
				hero->myGold -= 10;
				hero->currentHp += 8;

				if (hero->currentHp > hero->maxHp)
				{
					hero->currentHp = hero->maxHp;
				}

				cout << "체력이 8회복 되었습니다. " << endl;
				cout << "현재 체력 : " << hero->currentHp << endl;
			}
		}
		else if (inputNumber == 2)
		{
			//돈이 없는 경우
			if (hero->myGold < 200)
			{
				cout << "금액이 부족합니다." << endl;
			}
			//체력이 full인 경우
			else if (hero->currentHp >= hero->maxHp)
			{
				cout << "체력이 풀 입니다." << endl;
			}
			//체력이 full이 아니고 돈도 충분한 경우
			else
			{
				hero->myGold -= 100;
				hero->currentHp = hero->maxHp;

				cout << "체력이 풀로 회복되었습니다. " << endl;
				cout << "현재 체력 : " << hero->currentHp << endl;
			}
		}
		else if (inputNumber == 3)
		{
			if (hero->myGold < 200)
			{
				cout << "금액이 부족합니다." << endl;
			}
			else
			{
				hero->myGold -= 200;
				++(hero->damage);
				cout << "데미지가 1증가되었습니다." << endl;
			}
		}
		else if (inputNumber == 4)
		{
			cout << "상점에서 나갑니다." << endl;
			Sleep(2000);
			system("cls");
			break;
		}
		else
		{
			cout << "다시 입력해 주세요." << endl;
			Sleep(2000);
			system("cls");
		}
		Sleep(2000);
	}
}

//가위바위보 함수
bool Fight(Hero* hero, Monster* monster, int monNumber)
{
	int inputSPR; //가위 바위 보를 입력받을 변수
	int comSPR; //컴퓨터가 랜덤으로 가위 바위 보를 결정할 변수

	system("cls");
	comSPR = rand() % 3 + 1; // 컴퓨터가 랜덤하게 값을 설정.

	cout << endl;
	cout << "\t < 전 투 시 작 ! ! >" << endl;
	cout << endl;

	while (1)
	{
		cout << " - 가위(1), 바위(2), 보(3) 숫자로 입력 : ";
		cin >> inputSPR;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');

			cout << "숫자를 다시 입력해 주세요." << endl;
			Sleep(1000);
			cout << endl;
		}
		else
			break;
	}

	switch (inputSPR)
	{
		case SRP::SCISSORS:

			if (comSPR == SRP::SCISSORS) //비김 조건
				return Draw(hero, monster, monNumber, SRP::SCISSORS);
			else if (comSPR == SRP::ROCK) //패배 조건
				return Defeat(hero, monster, monNumber, SRP::SCISSORS);
			else //승리 조건
				return Win(hero, monster, monNumber, SRP::SCISSORS);
			break;

		case SRP::ROCK:

			if (comSPR == SRP::ROCK) //비김 조건
				return Draw(hero, monster, monNumber, SRP::ROCK);
			else if (comSPR == SRP::PAPER) //패배 조건
				return Defeat(hero, monster, monNumber, SRP::ROCK);
			else //승리 조건
				return Win(hero, monster, monNumber, SRP::ROCK);
			break;

		case SRP::PAPER:

			if (comSPR == SRP::PAPER) //비김 조건
				return Draw(hero, monster, monNumber, SRP::PAPER);
			else if (comSPR == SRP::SCISSORS) //패배 조건
				return Defeat(hero, monster, monNumber, SRP::PAPER);
			else //승리 조건
				return Win(hero, monster, monNumber, SRP::PAPER);
			break;

		default:
			return false;
			break;
	}
}

//타일에 닿았을 때 땅타입은 만날확률 높게 ~ 하늘은 만날 확률 낮게 설정.
inline bool RandResult(int result)
{
	return ((rand() % 100) < (70-10*result));
}

//비김 함수
bool Draw(Hero* hero, Monster* monster, int monNumber, int result) // 비김 함수
{
	cout << endl;
	cout << " >> 결과 : 방어!!" << endl;
	cout << endl;
	if (result == SRP::SCISSORS)
	{
		cout << " " << monster[monNumber].monsterName << " : '가위'는 '가위'로!" << endl;
	}
	else if(result == SRP::ROCK)
		cout << " " << monster[monNumber].monsterName << " : '바위'는 '바위'로!" << endl;
	else
		cout << " " << monster[monNumber].monsterName << " : '보'는 '보'로!" << endl;

	cout << " " << hero->heroName << " : '음... 좀 더 신중하게.....'" << endl;
	cout << endl;
	cout << " >> 아무키나 입력해 주세요 << ";
	int ch = _getch();

	return false;
}

//승리 함수
bool Win(Hero* hero, Monster* monster, int monNumber, int result) // 이김 함수
{
	int tmp;
	int critical = rand() % 2;
	tmp = hero->damage + critical;
	monster[monNumber].currentHp -= tmp;
	
	if (monster[monNumber].currentHp <= 0)
	{
		WinEmoticon();
	}

	cout << endl;
	cout << endl;
	cout << " >> 결과 : 승!!" << endl;
	if (critical > 0)
	{
		cout << " >> 크리티컬 발동!!" << endl;
	}
	cout << " >> " << hero->heroName << " 님이 " << tmp << " 만큼 공격!" << endl;
	cout << endl;
	cout << endl;
	
	
	if (result == SRP::SCISSORS)
		cout << " " << hero->heroName << " : 유승준의 가위!!" << endl;
	else if (result == SRP::ROCK)
		cout << " " << hero->heroName << " : 바위처럼 단단하게!!" << endl;
	else
		cout << " " << hero->heroName << " : 쫙 펼친 보!!" << endl;

	if (monster[monNumber].currentHp <= 0)
	{
		cout << " " << monster[monNumber].monsterName << " : 으아아ㅏㅏㄱ....." << endl;
		hero->myGold += monster[monNumber].giveGold; //돈 획득.
		hero->currentExp += monster[monNumber].giveExp; //경험치 획득

		cout << endl;
		cout << "\t < 보  상 >" << endl;
		cout << endl;
		cout << " - " << monster[monNumber].monsterName << "를(을) 잡아 돈 " << monster[monNumber].giveGold << "원"
			" 획득!" << endl;
		cout << " - 경험치 : " << monster[monNumber].giveExp << "획득!" << endl;
		if (hero->currentExp >= hero->maxExp) //레벨 업
		{
			cout << endl;
			cout << " >> 아무키나 입력해 주세요 << ";
			int ch = _getch();
			system("cls");
			LevelUp(hero);
		}
		else
		{
			cout << " - 현재 남은 체력 : " << hero->currentHp << endl;
			cout << " - 보유한 금액 : " << hero->myGold << endl;
			cout << " - 남은 몬스터의 수 : " << --monsterCount << endl;

			cout << endl;
			cout << " >> 아무키나 입력해 주세요 << ";
			int ch = _getch();
		}
		
		monster[monNumber].currentHp = monster[monNumber].maxHp; //현재 몬스터를 아예 없애지 않고 다시 최대체력으로 회복하여 잡을 수 있도록 설정한다.
		
		system("cls");

		if (monsterCount <= 0)
		{
			cout << endl;
			cout << " ♪（ｖ＾＿＾）ｖｖ（＾＿＾ｖ）♪ " << endl;
			cout << endl;
			cout << hero->heroName << "님이 모든 몬스터를 처치하고 승리!" << endl;
			cout << "레벨 : " << hero->level << endl;
			cout << "데미지 : " << hero->damage << endl;
			cout << "보유한 금액 : " << hero->myGold << endl;
			cout << endl;
			exit(1);
		}
		return true;
	}
	else
	{
		cout << " " << monster[monNumber].monsterName << " : 앗..! " << endl;
		
		cout << endl;
		cout << " >> 아무키나 입력해 주세요 << ";
		int ch = _getch();
		return false;
	}
}

//패 함수
bool Defeat(Hero* hero, Monster* monster, int monNumber, int result) //패배 함수
{
	hero->currentHp -= monster[monNumber].monsterDmg;
	if (hero->currentHp <= 0)
	{
		hero->currentHp = 0;
	}

	cout << endl;
	cout << " >> 결과 : 패.." << endl;
	cout << " >> 현재 남은 체력 : " << hero->currentHp << endl;
	cout << endl;
	if(result == SRP::SCISSORS)
		cout << " " << monster[monNumber].monsterName << " : 바위처럼 단단하게!!" << endl;	
	if(result == SRP::ROCK)
		cout << " " << monster[monNumber].monsterName << " : 주먹엔 쫙 펼친 보!!" << endl;
	if(result == SRP::PAPER)
		cout << " " << monster[monNumber].monsterName << " : 보에는 가위!!" << endl;
	cout << " " << hero->heroName << " : 앗...!" << endl;
	cout << endl;

	//게임 종료
	if (hero->currentHp <= 0)
	{
		cout << monster[monNumber].monsterName << "의 공격으로 인해 " << hero->heroName <<
			"님이 패배하였습니다. " << endl;
		exit(1);
	}

	cout << " >> 아무키나 입력해 주세요 << ";
	int ch = _getch();

	return false;
}

//레벨 업 함수
void LevelUp(Hero* hero)
{
	int tmp = 0;

	cout << endl;
	cout << "\t\t< 레벨이 올랐습니다!!! >" << endl;
	cout << endl;

	tmp = hero->level+1;
	cout << "\t레벨 : \t\t" << hero->level << "\t --> \t" << tmp << endl;
	(hero->level)++;
	
	tmp = hero->damage + 1;
	cout << "\t공격력 : \t" << hero->damage << "\t --> \t" << tmp << endl;
	(hero->damage)++;

	tmp = ((hero->maxHp) + (hero->level) * 50); //레벨업 한 후 맥스 hp를 먼저 계산.

	cout << "\t최대 체력 : \t" << hero->maxHp << "\t --> \t" << tmp << endl;
	hero->maxHp = tmp;
	hero->currentHp = hero->maxHp;

	tmp = (hero->maxExp) + (hero->level) * 400;
	cout << "\t최대 경험치 : \t" << hero->maxExp << "\t --> \t" << tmp << endl;
	hero->maxExp = tmp;
	hero->currentExp = 0;

	cout << endl;
	cout << "\t\t아무키나 입력해 주세요." << endl;
	int ch = _getch();
}

void GameStartPrint() //인트로 출력 함수
{
	cout << endl;
	cout << "\t =======================================" << endl;
	cout << "\t|\t\t\t\t\t|" << endl;
	cout << "\t|  ♪（ｖ＾＿＾）ｖｖ（＾＿＾ｖ）♪\t|" << endl;
	cout << "\t|\t\t\t\t\t|" << endl;
	cout << "\t|\t\t\t\t\t|" << endl;
	cout << "\t|\t  ▶ 영웅은 구조적 ◀ \t\t|" << endl;
	cout << "\t|\t\t\t\t\t|" << endl;
	cout << "\t =======================================" << endl;
	cout << endl;

	cout << "-------------------- < 게 임 설 명 > -------------------------" << endl;
	cout << endl;
	cout << " - 사용자의 입력으로 가로, 세로의 크기를 받아 맵이\n   구현되며, 크기에 따라 난이도가 설정됩니다." << endl;
	cout << endl;
	cout << " - 맵을 한 칸씩 이동하며 각 타일마다 랜덤하게 몬스터를\n   만나게 됩니다." << endl;
	cout << endl;
	cout << " - 타일의 타입에 따라 만나는 몬스터가 다릅니다." << endl;
	cout << endl;
	cout << " - 게임은 가위, 바위, 보 형태로 진행되며 목표 몬스터의 수를\n   다 잡으면 게임을 승리합니다." << endl;
	cout << endl;
	cout << " - 몬스터를 잡아 돈을 획득하여 상점에서 데미지를 증가시키세요!" << endl;
	cout << endl;
	cout << " - 영웅 투명화를 진행하면 타일에서 몬스터를 만나진 않지만,\n   상점에는 들를 수 있습니다." << endl;
	cout << endl;
	cout << " - 조작법은 게임 내에 설명되어 있습니다." << endl;
	cout << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << endl;
}

void IntroEmoticon()
{
	system("cls");
	string space = " ";
	string haha1 = "♪（ｖ＾＿＾）ｖ";
	string haha2 = "ｖ（＾＿＾ｖ）♪";

	for (int k = 0; k < 2; k++) {
		for (int i = 0; i < 15; i++)
		{
			cout << endl;
			for (int j = 0; j < i; j++)
			{
				cout << space;
			}
			cout << haha1;
			cout << endl;
			cout << endl;
			cout << " Loading... ";
			Sleep(10);
			system("cls");
		}

		for (int i = 0; i < 15; i++)
		{
			cout << endl;
			for (int j = 15; j > i; j--)
			{
				cout << space;
			}
			cout << haha2;
			cout << endl;
			cout << endl;
			cout << " Loading... ";
			Sleep(10);
			system("cls");
		}
	}

}

void WinEmoticon()
{
	string haha1 = " o(#￣▽￣)==O))￣0￣\")o";
	string haha2 = " o(#￣▽￣)=O (￣0￣)o";
	string haha3 = " o(#￣▽￣)O  (￣0￣)o";
	cout << endl;

	for (int i = 0; i < 21; i++)
	{
		system("cls");
		cout << endl;
		if (i % 3 == 0)
		{
			cout << haha3;
			Sleep(30);
		}

		if (i % 3 == 1)
		{
			cout << haha2;
			Sleep(30);
		}

		if (i % 3 == 2)
		{
			cout << haha1;
			Sleep(30);
		}
	}

	Sleep(1000);
}

void RunEmoticon()
{
	string space = " ";
	string haha1 = "ε = ε = Σ((( つ＞＜)つ";
	string haha3 = "    ε = Σ((( っ＞＜)っ";

	for (int i = 0; i < 20; i++)
	{
		system("cls");
		cout << endl;
		for (int j = 0; j < i; j++)
		{
			cout << space;
		}
		if (i % 2 == 0)
		{
			cout << haha3;
			Sleep(10);
		}
		else
		{
			cout << haha1;
			Sleep(10);
		}
	}
}