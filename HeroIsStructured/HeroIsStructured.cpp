/*
	������ ������

	** ������ ������ 2 : ������ ������
	1) ���� * ���� Ÿ�� ����� ���ϰ� ������ �� �ֵ��� ������. (���� �Ҵ�)
	2) w, a, s, d�̵�
	***3) �迭, ����ü, �Լ��� �ִ��� Ȱ���غ���.
	4) ������ ���� ���� ��
	5) ���ʹ� ���ϸ���ó�� ������ ��ī���� ���. //�� Ÿ�Ͽ� ���� �� Ȯ���� ���� �������� �ְ� �ȸ��������ְ�
	6) Ÿ�Ͽ� ������ �ִ�. (��, ��, ��) ���� ������ ���͵� �ٸ���. ������ ������ ��� �˿��� ������ ��� ... �� �ٸ���
	7) �÷��̾� �Ӽ� : �̸� / �ִ� HP(������ ���� ����) / ���� HP / ����ġ / ���� / ���
	8) ���� : �̸� / ���� / ȸ��ġ
	9) ���� : �̸�(���ϸ���) / �ִ� HP / ���� HP / ȹ�� ����ġ / ȹ�� ��� / �Ӽ�
	10) ���� : ������ ����
*/

#include <iostream>
#include <string>
#include <Windows.h>
#include <ctime>
#include <conio.h>
#include <cmath>

#define MONSTERSIZE 16 
#define SHOPSIZE 3 //������ 3��

enum TILETYPE{ SHOP=1, LAND , WATER , FOREST, FLY }; //��, ��, ��, ����
enum SRP { SCISSORS=1, ROCK, PAPER };

using namespace std;

//���� ����ü
struct Hero
{
	string heroName{""}; //����� �̸�
	int level{0};
	int maxHp{0}; //�ִ�ü��
	int currentHp{0}; //����ü��
	int maxExp{0}; //���� �������� �ϱ� ���� ����ġ
	int currentExp{0}; //����ġ
	int myGold{0}; //��ȭ
	int myXPosition{ 0 }, myYPosition{0}; //���� x, y��ǥ
	int damage{0};
};

//���� ����ü
struct Monster
{
	string monsterName{""}; //���� �̸�
	int maxHp{0}; //������ �ִ�ü��
	int currentHp{0}; //������ ����ü��
	int giveExp{0}; //������ ����ġ
	int giveGold{0}; //ȹ�� ���
	int tileType{0}; //���Ͱ� �����ϰ� �ִ� Ÿ��
	int monsterDmg{0}; //���� ������
};

//���� ����ü
struct Portion 
{
	string name; //������ �̸�
	int price; //���� ����
	int healHp; //ȸ��ġ
};

//���� ����ü
struct Shop
{
	int shopXPosition, shopYPosition;
};

void MapCreate(char** map, int width, int height, int* tilePositionSave, Shop* shop); //�� �����Ҵ� �Լ� ����
void MapFree(char** map, int width, int height); //���� �����ϴ� �Լ� ����
void Settings(Hero* hero, Monster* monster, string monsterName[], int area); // ����ο� ���͸� �����ϱ� ���� �Լ�
void HeroSetting(Hero* hero, int count); //����θ� �����ϱ� ���� area���� �Ѱ��ֱ� ���� �Լ�
void MonsterSetting(Monster* monster, string monsterName[], int count); //���͸� �����ϱ����� area���� �Ѱ��ֱ� ���� �Լ�
void MapPrint(char** map, int width, int height, Hero* hero); //�� ��� �Լ�
int CharacterMove(Hero* hero, char* move, char** map, int width, int height, int* tilePositionSave); //ĳ���� ������ �Լ�����
void FightAndShop(Hero* hero, Monster* monster, int moveResult, int* tilePositionSave); //���� �湮 or ���Ϳ� �ο� �Լ�
void ShopVisit(Hero* hero); //������ �湮���� ��
void MonsterMeet(Hero* hero, Monster* monster, int monsterType, int* tilePositionSave); //���Ϳ� ������ �Լ� ����
inline bool RandResult(int result); //���͸� ���� Ȯ���� ���ϴ� �Լ�
bool Fight(Hero* hero, Monster* monster, int monNumber); //�����Լ�
bool Draw(Hero* hero, Monster* monster, int monNumber, int result); //�������̺� ��� �Լ�
bool Win(Hero* hero, Monster* monster, int monNumber, int result); //���������� �̱� �Լ�
bool Defeat(Hero* hero, Monster* monster, int monNumber, int result); //���������� �й� �Լ�
void LevelUp(Hero* hero); //������ �Լ�

void MyCode(Hero* hero)
{
	string code = "kyw8918";
	string inputPassword;

	cout << "�ڵ� �Է� : ";
	cin >> inputPassword;

	if (inputPassword == code)
	{
		cout << "�ڵ� �Է� �Ϸ�!!" << endl;
		hero->damage = 100;
		cout << "���� �⺻ ���ݷ� : " << hero->damage;
		Sleep(2000);
	}
	else
	{
		cout << "�ڵ� �Է� ����..";
		Sleep(2000);
	}
}


int monsterCount = 0; //�� ���� ������ �������� ����

int main()
{
	srand(time(NULL));
	Hero hero;
	Monster* monster;
	Shop* shop = nullptr;
	string monsterName[] = { "�𷡵���", "��Ʈ����", "������", "��ī��", //monsterName[0] ~ monsterName[3] : ��
		"����ì��", "�ߵ���", "ŷũ��", "������Ÿ",					 //monsterName[4] ~ monsterName[7] : ��
		"��ħ��", "����", "���÷��þ�", "���ĸ�",						 //monsterNmae[8] ~ monsterName[11] : ��
		"������", "������", "���ڸ�", "���󵵽�"};						 //monsterName[12] ~ monsterName[15] : ����
	
	monster = new Monster[MONSTERSIZE];
	shop = new Shop[SHOPSIZE];
	int width;
	int height;

	cout << "�ʺ� �Է� : ";
	cin >> width;
	cout << "���� �Է� : ";
	cin >> height;
	
	hero.myXPosition = 0, hero.myYPosition = 0; //���� ��ġ �ʱ�ȭ
	int tilePositionSave = 0;
	char** map = new char*[height]; //2���� �迭 �����Ҵ� �ϱ� ���� ���� ������ ����
	MapCreate(map, width, height, &tilePositionSave, shop); //�� �����Ҵ� �Լ�


#pragma region �� ���̿��� ������ �̷������.

	Settings( &hero, monster, monsterName , width * height); //����ο� ���� ���� �Լ�

	char move; //�������� �޴� ���� CharacterMove�Լ��� ������ Ȱ��.
	int moveResult; //�����̰� ���� ���� ��ȯ���� ���� ���� // 1 = Shop, 2 = Land, 3 = Water, 4 = Forest, 5 = Fly;

	MyCode(&hero);
	
	//���� �ɷ�ġ Ȯ�� �ڵ�
	/*for (int i = 0; i < MONSTERSIZE; i++)
	{
		cout << "�̸� : " << (*(monster+i)).monsterName << ", �ִ� ü�� : " << monster[i].maxHp << ", ���� ü�� : " << monster[i].currentHp
			<< ", ���� ����ġ : " << monster[i].giveExp << ", ȹ�� ��� : " << monster[i].giveGold << ", Ÿ�� : " << monster[i].tileType << endl;
	}*/

	//Sleep(2000);
	

	////////////////////////////////////// ���� ���� ////////////////////////////////////////////////


	while (1)
	{
		system("cls");
		MapPrint(map, width, height, &hero); //�� ��� �Լ�
		moveResult = CharacterMove(&hero, &move, map, width, height, &tilePositionSave); //ĳ���Ͱ� �����̴� �Լ�
		FightAndShop(&hero, monster, moveResult, &tilePositionSave); //�����̰� �� ���� Ÿ���� �������� ��������
	}

#pragma endregion
	MapFree(map, width, height); //�� ���� �Լ�
	   	  
	delete[] shop;
	delete[] monster;
	return 0;
}

//���� ����ϴ� �Լ�
void MapPrint(char** map, int width, int height, Hero* hero)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (map[i][j] == 0)
				cout << "��";
			if (map[i][j] == 1)
				cout << "��";
			if (map[i][j] == 2)
				cout << "��";
			if (map[i][j] == 3)
				cout << "��";
			if (map[i][j] == 4)
				cout << "��";
			if (map[i][j] == 5)
				cout << "��";
		}
		cout << endl;
	}

	cout << endl;
	cout << "\t < ���� ���� > " << endl;
	cout << endl;
	cout << " - �̸� : " << hero->heroName << endl; 
	cout << " - ���� : " << hero->level << endl; 
	cout << " - ���ݷ� : " << hero->damage << endl; 
	cout << " - ���� ü�� : " << hero->currentHp << endl; 
	cout << " - ���� ����ġ : " << hero->currentExp << endl; 
	cout << " - ��ǥ ����ġ : " << hero->maxExp << endl; 
	cout << " - ������ ��� : " << hero->myGold << endl; 
}

//�� �����Ҵ� �� �����Լ�
void MapCreate(char** map, int width, int height, int* tileSavePosition, Shop* shop)
{
	for (int i = 0; i < height; i++)
		*(map + i) = new char[width];

	//�� �ʱ�ȭ
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (rand() % 100 < 50) //�� 50%����
			{
				map[i][j] = TILETYPE::LAND;
			}
		}
	}

	//�ٴ� �ʱ�ȭ
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (map[i][j] != TILETYPE::LAND && (rand() % 100 < 30)) //�ٴ� 30%����
			{
				map[i][j] = TILETYPE::WATER;
			}
		}
	}

	//�� �ʱ�ȭ
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (map[i][j] != TILETYPE::LAND && map[i][j] != TILETYPE::WATER && ( rand() % 100 < 30)) //�� 30%����
			{
				map[i][j] = TILETYPE::FOREST;
			}
		}
	}

	//���� �ʱ�ȭ
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (map[i][j] != TILETYPE::LAND && map[i][j] != TILETYPE::WATER && map[i][j] != TILETYPE::FOREST) //������ ����Ÿ�� ����
			{
				map[i][j] = TILETYPE::FLY;
			}
		}
	}

	int count = 0;
	//���� ��ġ ����
	for (int i = 0; i < SHOPSIZE; i++)
	{
		shop[i].shopXPosition = rand() % width, shop[i].shopYPosition = rand() % height;
		
		//1 - ������ ��ġ�� ���� ��ġ�� ��ġ�� �ʰ� ��ǥ ����
		while ((shop[i].shopXPosition == 0) && (shop[i].shopYPosition == 0) )
		{
			shop[i].shopXPosition = rand() % width; shop[i].shopYPosition = rand() % height; 
		}

		if (i != 0)
		{
			for (int j = 0; j < i ; j++) //������ ��ġ�� �ʰ� ����
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

	*tileSavePosition = map[0][0]; //�� ��ġ�� ���� Ÿ���� ���� ����
	map[0][0] = 0; //�� ��ġ ����
}

//�� �޸� ����
void MapFree(char** map, int width, int height)
{
	//�����Ҵ� �޸� ����
	for (int i = 0; i < height; i++)
	{
		delete[] map[i];
	}
	delete[] map;
}

//����� �� ���͸� �����ϴ� �Լ�
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
		monsterCount = (count + 1) * 20; //�뷱��
	}
	else
	{
		while (area > 0)
		{
			area -= 10;
			count++;
		}
		monsterCount = (count + 1) * 3; //�뷱��
	}
	
	HeroSetting(hero, count); //����� �ʱ�ȭ �� ����
	MonsterSetting(monster, monsterName, count); //���� �ʱ�ȭ �� ����
}

//����� ���� �Լ�
void HeroSetting(Hero* hero = nullptr, int count = 0)
{
	cout << "������� �̸��� �Է��� �ּ��� : ";
	cin >> hero->heroName;

	hero->maxHp = 100 + count * 10; //������� �⺻ ü���� �ּ� 100�� ü���� ������ �ִ´�. 
	hero->level = 1; //���� 1�� ����.
	hero->currentHp = hero->maxHp; //���� �ÿ��� ���� ü���� �ƽ� ü���̾�� �Ѵ�.
	hero->maxExp = 1000 + count * 200;  //�ּ� ����ġ : 1000 ����
	hero->damage = 1;
	hero->currentExp = 0; //���� ����ġ
	hero->myGold = 0; //���� ���
	hero->myXPosition = 0, hero->myYPosition = 0; //������ ��ǥ
}

//���� �����Լ�
void MonsterSetting(Monster* monster, string monsterName[], int count)
{
	int j = 0;

	for (int i = 0; i < MONSTERSIZE; i++)
	{
		(monster + i)->monsterName = monsterName[i];
		(monster + i)->tileType = TILETYPE(j);
		(monster + i)->maxHp = (rand() % 3 + (int)ceil(1 + j*1.5f)) + count; //�� ���ϸ��� ü���� 1~2�� �ȴ�.
		(monster + i)->currentHp = (monster + i)->maxHp;
		(monster + i)->giveExp = (rand() % 20 + 100 + (i * 5)) + (count * 50); //�ּ� ����ġ 100 //�뷱�� ����
		(monster + i)->giveGold = (rand() % 10 + 10 + (i * 5)) + (count + 1) * 2; //�ּ� ��� ȹ��
		(monster + i)->monsterDmg = count + 3;

		if ((i + 1) % 4 == 0)
		{
			j++; // TILETYPE�� 1���� ��Ű�� ���� ����
		}
	}
}

//�ɸ��� ������ �Լ�
int CharacterMove(Hero* hero, char* move, char** map, int width, int height, int* tilePositionSave)
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
				map[hero->myYPosition][hero->myXPosition] = *tilePositionSave; //���� �� ��ġ�� *tilePositionSave���� ����.
				hero->myYPosition--;	//���� ��ġ��                         
				*tilePositionSave = map[hero->myYPosition][hero->myXPosition];
				map[hero->myYPosition][hero->myXPosition] = 0;
			}

			break;

		case 'a':
			 
			if (hero->myXPosition == 0)
			{
				return 0;
			}
			else
			{
				map[hero->myYPosition][hero->myXPosition] = *tilePositionSave;
				hero->myXPosition--;
				*tilePositionSave = map[hero->myYPosition][hero->myXPosition];
				map[hero->myYPosition][hero->myXPosition] = 0;
			}

			break;

		case 's':

			if (hero->myYPosition == height-1)
			{
				return 0;
			}
			else
			{
				map[hero->myYPosition][hero->myXPosition] = *tilePositionSave; 
				hero->myYPosition++;
				*tilePositionSave = map[hero->myYPosition][hero->myXPosition];
				map[hero->myYPosition][hero->myXPosition] = 0;
			}

			break;

		case 'd':

			if (hero->myXPosition == width - 1)
			{
				return 0;
			}
			else
			{
				map[hero->myYPosition][hero->myXPosition] = *tilePositionSave;
				hero->myXPosition++;
				*tilePositionSave = map[hero->myYPosition][hero->myXPosition];
				map[hero->myYPosition][hero->myXPosition] = 0;
			}

			break;
		default:
			break;

	}

	return (*tilePositionSave);

	//if (*tilePositionSave == 1) //�����̶��
	//	return TILETYPE::SHOP;		/* ShopVisit();*/
	//else if (*tilePositionSave == 2) //��
	//	return TILETYPE::LAND;	/* RandomFightFunction(LAND);*/
	//else if (*tilePositionSave == 3) //��
	//	return TILETYPE::WATER;	/*RandomFightFunction(WATER);*/
	//else if (*tilePositionSave == 4) //��
	//	return TILETYPE::FOREST; /*RandomFightFunction(FOREST);*/
	//else							 //�ϴ�
	//	return TILETYPE::FLY;		/*RandomFightFunction(FLY);*/
}

//Ÿ�Ͽ� ���� ������
void FightAndShop(Hero* hero, Monster* monster , int moveResult, int* tilePositionSave)
{
	if (moveResult == SHOP)
	{
		ShopVisit(hero);
	}
	else
	{
		if (RandResult(moveResult) == true) //���Ϳ� ���� Ȯ���� ���� true�̸�
		{
			MonsterMeet(hero, monster, moveResult, tilePositionSave);
		}
		else	//���� �ȸ���
		{
			return;
		}
	}
}

//���Ϳ� ������ �Լ�
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
	cout << monster[randNum].monsterName << "(��)�� �����ߴ�!!!" << endl;

	Sleep(1000);

	while (1)
	{
		system("cls");
		cout << endl;
		cout << "\t < ���� ���� > " << endl;
		cout << endl;
		cout << "\t- �̸� : " << monster[randNum].monsterName << endl;
		cout << "\t- ü�� : " << monster[randNum].currentHp << endl;
		cout << "\t- ���ݷ� : " << monster[randNum].monsterDmg << endl;
		cout << endl;
		cout << "\t < ������ ���� > " << endl;
		cout << endl;
		cout << "\t- �̸� : " << hero->heroName << endl;
		cout << "\t- ���� : " << hero->level << endl;
		cout << "\t- ���ݷ� : " << hero->damage << endl;
		cout << "\t- ü�� : " << hero->currentHp << endl;
		cout << "\t- ������ �ݾ� : " << hero->myGold << endl;
		cout << "\t- ���� ����ġ : " << hero->currentExp << endl;
		cout << "\t- ��ǥ ����ġ : " << hero->maxExp << endl;
		cout << endl;
		cout << " >> �ο�ðڽ��ϱ�?(1) �������ðڽ��ϱ�?(2) : ";
		cin >> selectFightOrRun;

		if (selectFightOrRun == 1)
		{
			if (Fight(hero, monster, randNum) == true) //�̰��� �� while ���� ����
				break;
		}
		else
		{
			cout << endl;
			cout << hero->heroName << " : ��...������ �ٽú���.... " << endl;
			Sleep(1000);
			cout << endl;
			cout << monster[randNum].monsterName << " : ������~ �ٺ�!! ������!!!! " << endl;
			Sleep(1000);
			break;
		}
	}
}

void ShopVisit(Hero* hero) //������ �湮���� ��
{

}

//���������� �Լ�
bool Fight(Hero* hero, Monster* monster, int monNumber)
{
	int inputSPR; //���� ���� ���� �Է¹��� ����
	int comSPR; //��ǻ�Ͱ� �������� ���� ���� ���� ������ ����

	system("cls");
	comSPR = rand() % 3 + 1; // ��ǻ�Ͱ� �����ϰ� ���� ����.

	cout << endl;
	cout << "\t < �� �� �� �� ! ! >" << endl;
	cout << endl;
	cout << " - ����(1), ����(2), ��(3) ���ڷ� �Է� : ";
	cin >> inputSPR;

	switch (inputSPR)
	{
		case SRP::SCISSORS:

			if (comSPR == SRP::SCISSORS) //��� ����
				return Draw(hero, monster, monNumber, SRP::SCISSORS);
			else if (comSPR == SRP::ROCK) //�й� ����
				return Defeat(hero, monster, monNumber, SRP::SCISSORS);
			else //�¸� ����
				return Win(hero, monster, monNumber, SRP::SCISSORS);
			break;

		case SRP::ROCK:

			if (comSPR == SRP::ROCK) //��� ����
				return Draw(hero, monster, monNumber, SRP::ROCK);
			else if (comSPR == SRP::PAPER) //�й� ����
				return Defeat(hero, monster, monNumber, SRP::ROCK);
			else //�¸� ����
				return Win(hero, monster, monNumber, SRP::ROCK);
			break;

		case SRP::PAPER:

			if (comSPR == SRP::PAPER) //��� ����
				return Draw(hero, monster, monNumber, SRP::PAPER);
			else if (comSPR == SRP::SCISSORS) //�й� ����
				return Defeat(hero, monster, monNumber, SRP::PAPER);
			else //�¸� ����
				return Win(hero, monster, monNumber, SRP::PAPER);
			break;

		default:
			return false;
			break;
	}
}

//Ÿ�Ͽ� ����� �� ��Ÿ���� ����Ȯ�� ���� ~ �ϴ��� ���� Ȯ�� ���� ����.
inline bool RandResult(int result)
{
	return ((rand() % 100) < (70-10*result));
}

bool Draw(Hero* hero, Monster* monster, int monNumber, int result) // ��� �Լ�
{
	cout << endl;
	cout << " >> ��� : ���!!" << endl;
	cout << endl;
	if (result == SRP::SCISSORS)
	{
		cout << " " << monster[monNumber].monsterName << " : '����'�� '����'��!" << endl;
	}
	else if(result == SRP::ROCK)
		cout << " " << monster[monNumber].monsterName << " : '����'�� '����'��!" << endl;
	else
		cout << " " << monster[monNumber].monsterName << " : '��'�� '��'��!" << endl;

	cout << endl;
	cout << " >> �ƹ�Ű�� �Է��� �ּ��� << ";
	int ch = _getch();

	return false;
}

bool Win(Hero* hero, Monster* monster, int monNumber, int result) // �̱� �Լ�
{
	int tmp;
	tmp = hero->damage + rand() % 2;
	cout << endl;
	cout << " >> ��� : ��!!" << endl;
	cout << " >> " << hero->heroName << " ���� " << tmp << " ��ŭ ����!" << endl;
	cout << endl;
	monster[monNumber].currentHp -= tmp;

	if (result == SRP::SCISSORS)
		cout << " " << hero->heroName << " : ��ī�ο� ����!!" << endl;
	else if (result == SRP::ROCK)
		cout << " " << hero->heroName << " : �ܴ��� ����!!" << endl;
	else
		cout << " " << hero->heroName << " : �� ��ģ ��!!" << endl;
	
	cout << endl;

	if (monster[monNumber].currentHp <= 0)
	{
		hero->myGold += monster[monNumber].giveGold; //�� ȹ��.
		hero->currentExp += monster[monNumber].giveExp; //����ġ ȹ��

		cout << endl;
		cout << "\t < ��  �� >" << endl;
		cout << endl;
		cout << " - " << monster[monNumber].monsterName << "��(��) ��� ��" << monster[monNumber].giveGold << "��"
			" ȹ��!" << endl;
		cout << " - ����ġ : " << monster[monNumber].giveExp << "ȹ��!" << endl;
		if (hero->currentExp >= hero->maxExp) //���� ��
		{
			Sleep(1000);
			system("cls");
			LevelUp(hero);
		}
		else
		{
			cout << " - ���� ���� ü�� : " << hero->currentHp << endl;
			cout << " - ������ �ݾ� : " << hero->myGold << endl;
			cout << " - ���� ������ �� : " << --monsterCount << endl;

			cout << endl;
			cout << " >> �ƹ�Ű�� �Է��� �ּ��� << ";
			int ch = _getch();
		}
		
		monster[monNumber].currentHp = monster[monNumber].maxHp; //���� ���͸� �ƿ� ������ �ʰ� �ٽ� �ִ�ü������ ȸ���Ͽ� ���� �� �ֵ��� �����Ѵ�.
		
		system("cls");

		if (monsterCount <= 0)
		{
			cout << endl;
			cout << " �ܣ����ޣߣޣ��������ޣߣޣ����� " << endl;
			cout << endl;
			cout << hero->heroName << "���� ��� ���͸� óġ�ϰ� �¸�!" << endl;
			cout << "������ �ݾ� : " << hero->myGold << endl;
			cout << endl;
			exit(1);
		}

		return true;
	}
	else
	{
		cout << " >> �ƹ�Ű�� �Է��� �ּ��� << ";
		int ch = _getch();
		return false;
	}
}

bool Defeat(Hero* hero, Monster* monster, int monNumber, int result) //�й� �Լ�
{
	hero->currentHp -= monster[monNumber].monsterDmg;
	if (hero->currentHp <= 0)
	{
		hero->currentHp = 0;
	}

	cout << endl;
	cout << " >> ��� : ��.." << endl;
	cout << " >> ���� ���� ü�� : " << hero->currentHp << endl;
	cout << endl;
	if(result == SRP::SCISSORS)
		cout << " " << monster[monNumber].monsterName << " : ������ �ܴ��� ����!!" << endl;	
	if(result == SRP::ROCK)
		cout << " " << monster[monNumber].monsterName << " : �ָԿ� �� ��ģ ��!!" << endl;
	if(result == SRP::PAPER)
		cout << " " << monster[monNumber].monsterName << " : ������ ��ī�ο� ����!!" << endl;
	cout << endl;
	
	//���� ����
	if (hero->currentHp <= 0)
	{
		cout << monster[monNumber].monsterName << "�� �������� ���� " << hero->heroName <<
			"���� �й��Ͽ����ϴ�. " << endl;
		exit(1);
	}

	cout << " >> �ƹ�Ű�� �Է��� �ּ��� << ";
	int ch = _getch();

	return false;
}

void LevelUp(Hero* hero)
{
	int tmp = 0;

	cout << endl;
	cout << "\t\t< ������ �ö����ϴ�!!! >" << endl;
	cout << endl;

	tmp = hero->level+1;
	cout << "\t���� : \t\t" << hero->level << "\t --> \t" << tmp << endl;
	(hero->level)++;
	
	tmp = hero->damage + 1;
	cout << "\t���ݷ� : \t" << hero->damage << "\t --> \t" << tmp << endl;
	(hero->damage)++;

	tmp = ((hero->maxHp) + (hero->level) * 50); //������ �� �� �ƽ� hp�� ���� ���.

	cout << "\t�ִ� ü�� : \t" << hero->maxHp << "\t --> \t" << tmp << endl;
	hero->maxHp = tmp;
	hero->currentHp = hero->maxHp;

	tmp = (hero->maxExp) + (hero->level) * 300;
	cout << "\t�ִ� ����ġ : \t" << hero->maxExp << "\t --> \t" << tmp << endl;
	hero->maxExp = tmp;
	hero->currentExp = 0;

	cout << endl;
	cout << "\t\t�ƹ�Ű�� �Է��� �ּ���." << endl;
	int ch = _getch();
}