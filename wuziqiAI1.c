#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 15
#define CHARSIZE 2

#define quardzi_defend 30000
#define quard_bishou_defend 80000
#define huoer_attack 60
#define tri_kong_attack 5000
#define tri_si_attack 100
#define tri_huo_kong_partial 2000
#define quard_bishen_attack 100000

void initRecordBorard(void);
void recordtoDisplayArray(void);
void displayBoard(void);

//棋盘使用的是GBK编码，每一个中文字符占用2个字节。

//棋盘基本模板 
char aInitDisplayBoardArray[SIZE][SIZE*CHARSIZE+1] = 
{
		"┏┯┯┯┯┯┯┯┯┯┯┯┯┯┓",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┗┷┷┷┷┷┷┷┷┷┷┷┷┷┛"
};
//此数组用于显示棋盘 
char aDisplayBoardArray[SIZE][SIZE*CHARSIZE+1];
 
char play1Pic[]="●";//黑棋子;
char play1CurrentPic[]="▲"; 

char play2Pic[]="◎";//白棋子;
char play2CurrentPic[]="△";


//??????????????????
int aRecordBoard[SIZE][SIZE];

//ben ren mo gai
int heifang(void);
int baifang(void);
int mode;
void doubleplayers(void);
void singleplayer(void);
int referee(void);
int AI(void);

int AIcolor;
int playercolor;
int importance[15][15];
int Round = 1;
int nextstep_1 = 0;
int nextstep_2 = 0;
int nextstep_index = 0;

int main()

{
	int n;
	initRecordBorard();
	printf("enter 1 to enable 2 players mode \n");
	scanf("%d", &mode);
	printf("\n");
	if (mode == 1)
	{
		recordtoDisplayArray();
		displayBoard();
		doubleplayers();
	}
	else
	{
		int i, j;
		for (i = 0; i <= 14; i++)
		{
			for (j = 0; j <= 14; j++)
			{
				importance[i][j] = 0;
			}
		}
		int index;
		printf("if you want to use hei qi, please enter 1");
		scanf("%d", &index);
		initRecordBorard();
		if (index == 1)
		{
			Round = 2;
			playercolor = 1;
			AIcolor = 2;
			recordtoDisplayArray();
			displayBoard();
		}
		else
		{
			recordtoDisplayArray();
			displayBoard();
			Round = 1;
			playercolor = 2;
			AIcolor = 1;
		}
		singleplayer();
	}
	scanf("%d",&n);
	return 0;
}

//???????????
void initRecordBorard(void)
{
	int i, j;
	for (i = 0; i <= 15; i++)
	{
		for (j = 0; j <= 15; j++)
		{
			aRecordBoard[i][j] = 0;
		}
	}
	//?????????????aRecordBoard??0
}

//??aRecordBoard?м????????λ????????aDisplayBoardArray??
void recordtoDisplayArray(void)
{
	//?????????aInitDisplayBoardArray?м???????????????aDisplayBoardArray??
	int i, j;
	for (i = 0; i <= 14; i++)
	{
		for (j = 0; j <= 30; j++)
		{
			aDisplayBoardArray[i][j] = aInitDisplayBoardArray[i][j];
		}
	}
	//??????????aRecordBoard??????????0?????????????????aDisplayBoardArray?????λ????
	for (i = 0; i <= 14; i++)
	{
		for (j = 0; j <= 14; j++)
		{
			if (aRecordBoard[i][j] == 1)
			{
				aDisplayBoardArray[i][2 * j] = play1Pic[0];
				aDisplayBoardArray[i][2 * j + 1] = play1Pic[1];
			}
			else if (aRecordBoard[i][j] == 2)
			{
				aDisplayBoardArray[i][2 * j] = play2Pic[0];
				aDisplayBoardArray[i][2 * j + 1] = play2Pic[1];
			}
		}
	}
	//???aDisplayBoardArray????????????????????????????2???????????????????????????2??????
}

//?????????
void displayBoard(void)
{
	int i, j;
	//???????????
	system("clear"); //????
	//?????????aDisplayBoardArray??????????
	for (i = 0; i <= 14; i++)
	{
		if (i >= 6)
			printf(" %d", 15 - i);
		else
			printf("%d", 15 - i);
		printf("%s", aDisplayBoardArray[i]);

		printf("\n");
	}

	//????????????????????????A B ....
	printf("  A B C D E F G H I J K L M N O\n");
}

//luo zi
int heifang(void)
{
	int a = 0;
	char b;
	printf("qing hei fang wan jia shu ru luo zi zuo biao\n");
	char c[4] = {"quit"};
	char d[4];
	scanf("%s", d);
	if (strcmp(c, d) == 0)
		return 0;
	if (d[1] == ',')
	{
		a = d[0] - '0';
		b = d[2];
	}
	else if (d[2] == ',')
	{
		a = 10 * (d[0] - '0') + d[1] - '0';
		b = d[3];
	}
	printf("\n");
	if (a < 1 || a > 15 || b - 'A' < 0 || b - 'A' > 14)
	{
		printf("wrong number!\n");
		return 1;
	}
	if (aRecordBoard[15 - a][b - 'A'] == 0)
	{
		aRecordBoard[15 - a][b - 'A'] = 1;
		aDisplayBoardArray[15 - a][2 * (b - 'A')] = play1CurrentPic[0];
		aDisplayBoardArray[15 - a][2 * (b - 'A') + 1] = play1CurrentPic[1];
		return 2;
	}
	else
	{
		printf("don't play tricks!\n");
		return 1;
	}
}

int baifang(void)
{
	int a;
	char b;
	printf("qing bai fang wan jia shu ru luo zi zuo biao\n");
	char c[4] = {"quit"};
	char d[4];
	scanf("%s", d);
	if (strcmp(c, d) == 0)
		return 0;
	if (d[1] == ',')
	{
		a = d[0] - '0';
		b = d[2];
	}
	else if (d[2] == ',')
	{
		a = 10 * (d[0] - '0') + d[1] - '0';
		b = d[3];
	}
	printf("\n");
	if (a < 1 || a > 15 || b - 'A' < 0 || b - 'A' > 14)
	{
		printf("wrong number!\n");
		return 2;
	}
	if (aRecordBoard[15 - a][b - 'A'] == 0)
	{
		aRecordBoard[15 - a][b - 'A'] = 2;
		aDisplayBoardArray[15 - a][2 * (b - 'A')] = play2CurrentPic[0];
		aDisplayBoardArray[15 - a][2 * (b - 'A') + 1] = play2CurrentPic[1];
		return 1;
	}
	else
	{
		printf("don't play tricks!\n");
		return 2;
	}
}

int wanjia(void)
{
	int a;
	char b;
	scanf("%d,%c", &a, &b);
	printf("\n");
	if (aRecordBoard[15 - a][b - 'A'] == 0)
	{
		aRecordBoard[15 - a][b - 'A'] = playercolor;
		return 1;
	}
	else
	{
		printf("don't play tricks!\n");
		return 2;
	}
}

//mo shi

void doubleplayers(void)
{
	int n;
	if (Round != 0)
	{
		if (Round == 1)
		{
			Round = heifang();
			displayBoard();
			recordtoDisplayArray();
			//getchar();
		}
		else if (Round == 2)
		{
			Round = baifang();
			displayBoard();
			recordtoDisplayArray();
		}
		if (referee() == 1)
		{
			printf("black win!");
		}
		else if (referee() == 2)
		{
			printf("white win!");
		}
		else
			doubleplayers();
	}
	else
	scanf("%d",&n);
}

void singleplayer(void)
{
	if (Round == 1)
	{
		Round = AI();
		recordtoDisplayArray();
		displayBoard();
		nextstep_index = 0;
	}
	else
	{
		Round = wanjia();
		recordtoDisplayArray();
		displayBoard();
	}
	if (referee() == 1)
	{
		printf("black win!");
	}
	else if (referee() == 2)
	{
		printf("white win!");
	}
	else
		singleplayer();
	int n;
	scanf("%d",&n);
}

int check(int i, int j)
{
	int i1, j1;
	int a = 0;
	int left, right;
	int left1, right1;

	if (i >= 2 && i <= 12)
	{
		left = right = 2;
	}
	else if (i == 1)
	{
		left = 1;
		right = 2;
	}
	else if (i == 13)
	{
		left = 2;
		right = 1;
	}
	else if (i == 0)
	{
		left = 0;
		right = 2;
	}
	else if (i == 14)
	{
		left = 2;
		right = 0;
	}
	else
		;

	if (j >= 2 && j <= 12)
	{
		left1 = right1 = 2;
	}
	else if (j == 1)
	{
		left1 = 1;
		right1 = 2;
	}
	else if (j == 13)
	{
		left1 = 2;
		right1 = 1;
	}
	else if (j == 0)
	{
		left1 = 0;
		right1 = 2;
	}
	else if (j == 14)
	{
		left1 = 2;
		right1 = 0;
	}
	else
		;

	for (i1 = i - left; i1 <= i + right; i1++)
	{
		for (j1 = j - left1; j1 <= j + right; j1++)
		{
			if (aRecordBoard[i1][j1] == 2 || aRecordBoard[i1][j1] == 1)
				a = 1;
			else
				;
		}
	}
	return a;
}

void escape(int i, int j)
{
	int i1, j1;
	int left, right;
	int left1, right1;

	if (i >= 1 && i <= 13)
	{
		left = right = 1;
	}
	else if (i == 0)
	{
		left = 0;
		right = 1;
	}
	else if (i == 14)
	{
		left = 1;
		right = 0;
	}
	else
		;

	if (j >= 1 && j <= 13)
	{
		left1 = right1 = 1;
	}
	else if (j == 0)
	{
		left1 = 0;
		right1 = 1;
	}
	else if (j == 14)
	{
		left1 = 1;
		right1 = 0;
	}
	else
		;

	for (i1 = i - left; i1 <= i + right; i1++)
	{
		for (j1 = j - left1; j1 <= j + right; j1++)
		{
			if (aRecordBoard[i1][j1] == playercolor)
				importance[i][j] -= 100;
		}
	}
}

void escape_1z(int i, int j)
{
	int i1, j1;
	int left, right;
	int left1, right1;

	if (i >= 1 && i <= 13)
	{
		left = right = 1;
	}
	else if (i == 0)
	{
		left = 0;
		right = 1;
	}
	else if (i == 14)
	{
		left = 1;
		right = 0;
	}
	else
		;

	if (j >= 1 && j <= 13)
	{
		left1 = right1 = 1;
	}
	else if (j == 0)
	{
		left1 = 0;
		right1 = 1;
	}
	else if (j == 14)
	{
		left1 = 1;
		right1 = 0;
	}
	else
		;

	for (i1 = i - left; i1 <= i + right; i1++)
	{
		for (j1 = j - left1; j1 <= j + right; j1++)
		{
			if (aRecordBoard[i1][j1] == playercolor)
				importance[i][j] -= 5;
		}
	}
}

void escape_3zi(int i, int j)
{
	int i1, j1;
	int left, right;
	int left1, right1;

	if (i >= 1 && i <= 13)
	{
		left = right = 1;
	}
	else if (i == 0)
	{
		left = 0;
		right = 1;
	}
	else if (i == 14)
	{
		left = 1;
		right = 0;
	}
	else
		;

	if (j >= 1 && j <= 13)
	{
		left1 = right1 = 1;
	}
	else if (j == 0)
	{
		left1 = 0;
		right1 = 1;
	}
	else if (j == 14)
	{
		left1 = 1;
		right1 = 0;
	}
	else
		;

	for (i1 = i - left; i1 <= i + right; i1++)
	{
		for (j1 = j - left1; j1 <= j + right; j1++)
		{
			if (aRecordBoard[i1][j1] == playercolor)
			{
				importance[i][j] -= 1000;
			}
		}
	}
}

int calculate(int i, int j)
{
	//1 ZI
	if (aRecordBoard[i][j] == AIcolor)
	{
		//JIN LIAN
		if (i - 2 >= 0 && j - 2 >= 0 && aRecordBoard[i - 2][j - 2] != playercolor)
		{
			importance[i - 1][j - 1] += huoer_attack;
			escape_1z(i - 1, j - 1);
		}
		if (i - 2 >= 0 && aRecordBoard[i - 2][j] != playercolor)
		{
			importance[i - 1][j] += huoer_attack;
			escape_1z(i - 1, j);
		}
		if (i - 2 >= 0 && j + 2 <= 14 && aRecordBoard[i - 2][j + 2] != playercolor)
		{
			importance[i - 1][j + 1] += huoer_attack;
			escape_1z(i - 1, j + 1);
		}
		if (j + 2 <= 14 && aRecordBoard[i][j + 2] != playercolor)
		{
			importance[i][j + 1] += huoer_attack;
			escape_1z(i, j + 1);
		}
		if (i + 2 <= 14 && j + 2 <= 14 && aRecordBoard[i + 2][j + 2] != playercolor)
		{
			importance[i + 1][j + 1] += huoer_attack;
			escape_1z(i + 1, j + 1);
		}
		if (i + 2 <= 14 && aRecordBoard[i + 2][j] != playercolor)
		{
			importance[i + 1][j] += huoer_attack;
			escape_1z(i + 1, j);
		}
		if (i + 2 <= 14 && j - 2 >= 0 && aRecordBoard[i + 2][j - 2] != playercolor)
		{
			importance[i + 1][j - 1] += huoer_attack;
			escape_1z(i + 1, j - 1);
		}
		if (j - 2 >= 0 && aRecordBoard[i][j - 2] != playercolor)
		{
			importance[i][j - 1] += huoer_attack;
			escape_1z(i, j - 1);
		}
		//KONG 1 GE
		if (i - 2 >= 0 && j - 2 >= 0 && aRecordBoard[i - 1][j - 1] != playercolor)
		{
			importance[i - 2][j - 2] += huoer_attack;
			escape_1z(i - 2, j - 2);
		}
		if (i - 2 >= 0 && aRecordBoard[i - 1][j] != playercolor)
		{
			importance[i - 2][j] += huoer_attack;
			escape_1z(i - 2, j);
		}
		if (i - 2 >= 0 && j + 2 <= 14 && aRecordBoard[i - 1][j + 1] != playercolor)
		{
			importance[i - 2][j + 2] += huoer_attack;
			escape_1z(i - 2, j + 2);
		}
		if (j + 2 <= 14 && aRecordBoard[i][j + 1] != playercolor)
		{
			importance[i][j + 2] += huoer_attack;
			escape_1z(i, j + 2);
		}
		if (i + 2 <= 14 && j + 2 <= 14 && aRecordBoard[i + 1][j + 1] != playercolor)
		{
			importance[i + 2][j + 2] += huoer_attack;
			escape_1z(i + 2, j + 2);
		}
		if (i + 2 <= 14 && aRecordBoard[i + 1][j] != playercolor)
		{
			importance[i + 2][j] += huoer_attack;
			escape_1z(i + 2, j);
		}
		if (i + 2 <= 14 && j - 2 >= 0 && aRecordBoard[i + 1][j - 1] != playercolor)
		{
			importance[i + 2][j - 2] += huoer_attack;
			escape_1z(i + 2, j - 2);
		}
		if (j - 2 >= 0 && aRecordBoard[i][j - 1] != playercolor)
		{
			importance[i][j - 2] += huoer_attack;
			escape_1z(i, j - 2);
		}
	}
	//2 ZI
	//horizon
	if (aRecordBoard[i][j] == AIcolor && aRecordBoard[i + 1][j] == AIcolor)
	{
		if (i - 1 >= 0)
		{
			if (i + 2 <= 14 && aRecordBoard[i + 2][j] != playercolor)
			{
				importance[i - 1][j] += 3000;
				escape(i - 1, j);
			}
			else
				importance[i - 1][j] += tri_si_attack;
		}
		if (i + 2 <= 14)
		{
			if (i - 1 >= 0 && aRecordBoard[i - 1][j] != playercolor)
			{
				importance[i + 2][j] += 3000;
				escape(i + 2, j);
			}
			else
				importance[i + 2][j] += tri_si_attack;
		}
	}
	if (aRecordBoard[i][j] == AIcolor && aRecordBoard[i + 1][j] == 0 && aRecordBoard[i + 2][j] == AIcolor)
	{
		if (i + 3 <= 14 && i - 1 >= 0 && aRecordBoard[i - 1][j] != playercolor && aRecordBoard[i + 3][j] != playercolor)
		{
			importance[i + 1][j] += 3000;
			if (i + 4 <= 14 && aRecordBoard[i - 1][j] != playercolor && aRecordBoard[i + 4][j] != playercolor)
				importance[i + 3][j] += tri_huo_kong_partial;
			if (i - 2 >= 0 && aRecordBoard[i - 2][j] != playercolor && aRecordBoard[i + 3][j] != playercolor)
				importance[i - 1][j] += tri_huo_kong_partial;
		}
		else
			importance[i + 1][j] += tri_si_attack;
	}
	//vertical
	if (aRecordBoard[i][j] == AIcolor && aRecordBoard[i][j + 1] == AIcolor)
	{
		if (j - 1 >= 0)
		{
			if (j + 2 <= 14 && aRecordBoard[i][j + 2] != playercolor)
			{
				importance[i][j - 1] += 3000;
				escape(i, j - 1);
			}
			else
				importance[i][j - 1] += tri_si_attack;
		}
		if (j + 2 <= 14)
		{
			if (j - 1 >= 0 && aRecordBoard[i][j - 1] != playercolor)
			{
				importance[i][j + 2] += 3000;
				escape(i, j + 2);
			}
			else
				importance[i][j + 2] += tri_si_attack;
		}
	}
	if (aRecordBoard[i][j] == AIcolor && aRecordBoard[i][j + 1] == 0 && aRecordBoard[i][j + 2] == AIcolor)
	{
		if (j + 3 <= 14 && j - 1 >= 0 && aRecordBoard[i][j - 1] != playercolor && aRecordBoard[i][j + 3] != playercolor)
		{
			importance[i][j + 1] += 3000;
			if (j + 4 <= 14 && aRecordBoard[i][j - 1] != playercolor && aRecordBoard[i][j + 4] != playercolor)
				importance[i][j + 3] += tri_huo_kong_partial;
			if (j - 2 >= 0 && aRecordBoard[i][j - 2] != playercolor && aRecordBoard[i][j + 3] != playercolor)
				importance[i][j - 1] += tri_huo_kong_partial;
		}
		else
			importance[i][j + 1] += tri_si_attack;
	}
	//left right
	if (aRecordBoard[i][j] == AIcolor && aRecordBoard[i + 1][j + 1] == AIcolor)
	{
		if (i - 1 >= 0 && j - 1 >= 0)
		{
			if (i + 2 <= 14 && j + 2 <= 14 && aRecordBoard[i + 2][j + 2] != playercolor)
			{
				importance[i - 1][j - 1] += 3000;
				escape(i - 1, j - 1);
			}
			else
				importance[i - 1][j - 1] += tri_si_attack;
		}
		if (i + 2 <= 14 && j + 2 <= 14)
		{
			if (i - 1 >= 0 && j - 1 >= 0 && aRecordBoard[i - 1][j - 1] != playercolor)
			{
				importance[i + 2][j + 2] += 3000;
				escape(i + 2, j + 2);
			}
			else
				importance[i + 2][j + 2] += tri_si_attack;
		}
	}
	if (aRecordBoard[i][j] == AIcolor && aRecordBoard[i + 1][j + 1] == 0 && aRecordBoard[i + 2][j + 2] == AIcolor)
	{
		if (i + 3 <= 14 && i - 1 >= 0 && j + 3 <= 14 && j - 1 >= 0 && aRecordBoard[i - 1][j - 1] != playercolor && aRecordBoard[i + 3][j + 3] != playercolor)
		{
			importance[i + 1][j + 1] += 3000;
			if (i + 4 <= 14 && j + 4 <= 14 && aRecordBoard[i - 1][j - 1] != playercolor && aRecordBoard[i + 4][j + 4] != playercolor)
				importance[i + 3][j + 3] += tri_huo_kong_partial;
			if (i - 2 >= 0 && j - 2 >= 0 && aRecordBoard[i - 2][j - 2] != playercolor && aRecordBoard[i + 3][j + 3] != playercolor)
				importance[i - 1][j - 1] += tri_huo_kong_partial;
		}
		else
			importance[i + 1][j + 1] += tri_si_attack;
	}
	//other
	if (aRecordBoard[i][j] == AIcolor && aRecordBoard[i - 1][j + 1] == AIcolor)
	{
		if (i + 1 <= 14 && j - 1 >= 0)
		{
			if (i - 2 >= 0 && j + 2 <= 14 && aRecordBoard[i - 2][j + 2] != playercolor)
			{
				importance[i + 1][j - 1] += 3000;
				escape(i + 1, j - 1);
			}
			else
				importance[i + 1][j - 1] += tri_si_attack;
		}
		if (i - 2 >= 0 && j + 2 <= 14)
		{
			if (i + 1 <= 14 && j - 1 >= 0 && aRecordBoard[i + 1][j - 1] != playercolor)
			{
				importance[i - 2][j + 2] += 3000;
				escape(i - 2, j + 2);
			}
			else
				importance[i - 2][j + 2] += tri_si_attack;
		}
	}
	if (aRecordBoard[i][j] == AIcolor && aRecordBoard[i - 1][j + 1] == 0 && aRecordBoard[i - 2][j + 2] == AIcolor)
	{
		if (i - 3 >= 0 && i + 1 <= 14 && j + 3 <= 14 && j - 1 >= 0 && aRecordBoard[i + 1][j - 1] != playercolor && aRecordBoard[i - 3][j + 3] != playercolor)
		{
			importance[i - 1][j + 1] += 3000;
			if (i - 4 >= 0 && j + 4 <= 14 && aRecordBoard[i + 1][j - 1] != playercolor && aRecordBoard[i - 4][j + 4] != playercolor)
				importance[i - 3][j + 3] += tri_huo_kong_partial;
			if (i + 2 <= 14 && j - 2 >= 0 && aRecordBoard[i + 2][j - 2] != playercolor && aRecordBoard[i - 3][j + 3] != playercolor)
				importance[i + 1][j - 1] += tri_huo_kong_partial;
		}
		else
			importance[i - 1][j + 1] += tri_si_attack;
	}
	//3ZI
	//HORIZEN
	if (aRecordBoard[i][j] == AIcolor && aRecordBoard[i + 1][j] == AIcolor && aRecordBoard[i + 2][j] == AIcolor)
	{
		if (i - 1 >= 0)
		{
			if (i + 3 <= 14 && aRecordBoard[i + 3][j] != playercolor)
			{
				importance[i - 1][j] += 10000;
				escape_3zi(i - 1, j);
			}
			else
				importance[i - 1][j] += 5000;
		}
		if (i + 3 <= 14)
		{
			if (i - 1 >= 0 && aRecordBoard[i - 1][j] != playercolor)
			{
				importance[i + 3][j] += 10000;
				escape_3zi(i + 3, j);
			}
			else
				importance[i + 3][j] += 5000;
		}
		if (i + 4 <= 14 && aRecordBoard[i + 3][j] != playercolor)
			importance[i + 4][j] += tri_kong_attack;
		if (i - 2 >= 0 && aRecordBoard[i - 1][j] != playercolor)
			importance[i - 2][j] += tri_kong_attack;
	}
	if (aRecordBoard[i][j] == AIcolor && aRecordBoard[i + 1][j] == 0 && aRecordBoard[i + 2][j] == AIcolor && aRecordBoard[i + 3][j] == AIcolor)
	{
		if (i + 1 <= 14)
			importance[i + 1][j] += 10000;
	}
	if (aRecordBoard[i][j] == AIcolor && aRecordBoard[i + 1][j] == AIcolor && aRecordBoard[i + 2][j] == 0 && aRecordBoard[i + 3][j] == AIcolor)
	{
		if (i + 2 <= 14)
			importance[i + 2][j] += 10000;
	}
	else
		;
	//VERICAL

	if (aRecordBoard[i][j] == AIcolor && aRecordBoard[i][j + 1] == AIcolor && aRecordBoard[i][j + 2] == AIcolor)
	{
		if (j - 1 >= 0)
		{
			if (j + 3 <= 14 && aRecordBoard[i][j + 3] != playercolor)
			{
				importance[i][j - 1] += 10000;
				escape_3zi(i, j - 1);
			}
			else
				importance[i][j - 1] += 5000;
		}
		if (j + 3 <= 14)
		{
			if (j - 1 >= 0 && aRecordBoard[i][j - 1] != playercolor)
			{
				importance[i][j + 3] += 10000;
				escape_3zi(i, j + 3);
			}
			else
				importance[i][j + 3] += 5000;
		}
		if (j + 4 <= 14 && aRecordBoard[i][j + 3] != playercolor)
			importance[i][j + 4] += tri_kong_attack;
		if (j - 2 >= 0 && aRecordBoard[i][j - 1] != playercolor)
			importance[i][j - 2] += tri_kong_attack;
	}
	if (aRecordBoard[i][j] == AIcolor && aRecordBoard[i][j + 1] == AIcolor && aRecordBoard[i][j + 2] == 0 && aRecordBoard[i][j + 3] == AIcolor)
	{
		if (j + 2 <= 14)
			importance[i][j + 2] += 10000;
	}
	if (aRecordBoard[i][j] == AIcolor && aRecordBoard[i][j + 1] == 0 && aRecordBoard[i][j + 2] == AIcolor && aRecordBoard[i][j + 3] == AIcolor)
	{
		if (j + 1 <= 14)
			importance[i][j + 1] += 10000;
	}
	//LEFT RIGHT
	if (aRecordBoard[i][j] == AIcolor && aRecordBoard[i + 1][j + 1] == AIcolor && aRecordBoard[i + 2][j + 2] == AIcolor)
	{
		if (i - 1 >= 0 && j - 1 >= 0)
		{
			if (j + 3 <= 14 && i + 3 <= 14 && aRecordBoard[i + 3][j + 3] != playercolor)
			{
				importance[i - 1][j - 1] += 10000;
				escape_3zi(i - 1, j - 1);
			}
			else
				importance[i - 1][j - 1] += 5000;
		}
		if (i + 3 <= 14 && j + 3 <= 14)
		{
			if (j - 1 >= 0 && i - 1 >= 0 && aRecordBoard[i - 1][j - 1] != playercolor)
			{
				importance[i + 3][j + 3] += 10000;
				escape_3zi(i + 3, j + 3);
			}
			else
				importance[i + 3][j + 3] += 5000;
		}
		if (i - 2 >= 0 && j - 2 >= 0 && aRecordBoard[i - 1][j - 1] != playercolor)
			importance[i - 2][j - 2] += tri_kong_attack;
		if (i + 4 <= 14 && j + 4 <= 14 && aRecordBoard[i + 3][j + 3] != playercolor)
			importance[i + 4][j + 4] += tri_kong_attack;
	}
	if (aRecordBoard[i][j] == AIcolor && aRecordBoard[i + 1][j + 1] == AIcolor && aRecordBoard[i + 2][j + 2] == 0 && aRecordBoard[i + 3][j + 3] == AIcolor)
	{
		if (i + 2 <= 14 && j + 2 <= 14)
			importance[i + 2][j + 2] += 10000;
	}
	if (aRecordBoard[i][j] == AIcolor && aRecordBoard[i + 1][j + 1] == 0 && aRecordBoard[i + 2][j + 2] == AIcolor && aRecordBoard[i + 3][j + 3] == AIcolor)
	{
		if (i + 1 <= 14 && j + 1 <= 14)
			importance[i + 1][j + 1] += 10000;
	}
	//OTHER

	if (aRecordBoard[i][j] == AIcolor && aRecordBoard[i - 1][j + 1] == AIcolor && aRecordBoard[i - 2][j + 2] == AIcolor)
	{
		if (i + 1 <= 14 && j - 1 >= 0)
		{
			if (i - 3 >= 0 && j + 3 <= 14 && aRecordBoard[i - 3][j + 3] != playercolor)
			{
				importance[i + 1][j - 1] += 10000;
				escape_3zi(i + 1, j - 1);
			}
			else
				importance[i + 1][j - 1] += 5000;
		}
		if (i - 3 >= 0 && j + 3 <= 14)
		{
			if (i + 1 <= 14 && j - 1 >= 0 && aRecordBoard[i + 1][j - 1] != playercolor)
			{
				importance[i - 3][j + 3] += 10000;
				escape_3zi(i - 3, j + 3);
			}
			else
				importance[i - 3][j + 3] += 5000;
		}
		if (i + 2 <= 14 && j - 2 >= 0 && aRecordBoard[i + 1][j - 1] != playercolor)
			importance[i + 2][j - 2] += tri_kong_attack;
		if (i - 3 >= 0 && j + 4 <= 14 && aRecordBoard[i - 3][j + 3] != playercolor)
			importance[i - 4][j + 4] += tri_kong_attack;
	}
	if (aRecordBoard[i][j] == AIcolor && aRecordBoard[i - 1][j + 1] == AIcolor && aRecordBoard[i - 2][j + 2] == 0 && aRecordBoard[i - 3][j + 3] == AIcolor)
	{
		if (i - 2 >= 0 && j + 2 <= 14)
			importance[i - 2][j + 2] += 10000;
	}
	if (aRecordBoard[i][j] == AIcolor && aRecordBoard[i - 1][j + 1] == 0 && aRecordBoard[i - 2][j + 2] == AIcolor && aRecordBoard[i - 3][j + 3] == AIcolor)
	{
		if (i - 1 >= 0 && j + 1 <= 14)
			importance[i - 1][j + 1] += 10000;
	}

	//4ZI
	//HORIZEN
	if (aRecordBoard[i][j] == AIcolor && aRecordBoard[i + 1][j] == AIcolor && aRecordBoard[i + 2][j] == AIcolor && aRecordBoard[i + 3][j] == 0 && aRecordBoard[i + 4][j] == AIcolor)
	{
		if (i + 3 <= 14)
			importance[i + 3][j] += quard_bishen_attack;
	}
	if (aRecordBoard[i][j] == AIcolor && aRecordBoard[i + 1][j] == AIcolor && aRecordBoard[i + 2][j] == 0 && aRecordBoard[i + 3][j] == AIcolor && aRecordBoard[i + 4][j] == AIcolor)
	{
		if (i + 2 <= 14)
			importance[i + 2][j] += quard_bishen_attack;
	}
	if (aRecordBoard[i][j] == AIcolor && aRecordBoard[i + 1][j] == 0 && aRecordBoard[i + 2][j] == AIcolor && aRecordBoard[i + 3][j] == AIcolor && aRecordBoard[i + 4][j] == AIcolor)
	{
		if (i + 1 <= 14)
			importance[i + 3][j] += quard_bishen_attack;
	}
	//vertical
	if (aRecordBoard[i][j] == AIcolor && aRecordBoard[i][j + 1] == AIcolor && aRecordBoard[i][j + 2] == AIcolor && aRecordBoard[i][j + 3] == 0 && aRecordBoard[i][j + 4] == AIcolor)
	{
		if (j + 3 <= 14)
			importance[i][j + 3] += quard_bishen_attack;
	}
	if (aRecordBoard[i][j] == AIcolor && aRecordBoard[i][j + 1] == AIcolor && aRecordBoard[i][j + 2] == 0 && aRecordBoard[i][j + 3] == AIcolor && aRecordBoard[i][j + 4] == AIcolor)
	{
		if (j + 2 <= 14)
			importance[i][j + 2] += quard_bishen_attack;
	}
	if (aRecordBoard[i][j] == AIcolor && aRecordBoard[i][j + 1] == 0 && aRecordBoard[i][j + 2] == AIcolor && aRecordBoard[i][j + 3] == AIcolor && aRecordBoard[i][j + 4] == AIcolor)
	{
		if (j + 1 <= 14)
			importance[i][j + 1] += quard_bishen_attack;
	}
	//left right
	if (aRecordBoard[i][j] == AIcolor && aRecordBoard[i + 1][j + 1] == AIcolor && aRecordBoard[i + 2][j + 2] == AIcolor && aRecordBoard[i + 3][j + 3] == 0 && aRecordBoard[i + 4][j + 4] == AIcolor)
	{
		if (j + 3 <= 14 && i + 3 <= 14)
			importance[i + 3][j + 3] += quard_bishen_attack;
	}
	if (aRecordBoard[i][j] == AIcolor && aRecordBoard[i + 1][j + 1] == AIcolor && aRecordBoard[i + 2][j + 2] == 0 && aRecordBoard[i + 3][j + 3] == AIcolor && aRecordBoard[i + 4][j + 4] == AIcolor)
	{
		if (j + 2 <= 14 && i + 2 <= 14)
			importance[i + 2][j + 2] += quard_bishen_attack;
	}
	if (aRecordBoard[i][j] == AIcolor && aRecordBoard[i + 1][j + 1] == 0 && aRecordBoard[i + 2][j + 2] == AIcolor && aRecordBoard[i + 3][j + 3] == AIcolor && aRecordBoard[i + 4][j + 4] == AIcolor)
	{
		if (j + 1 <= 14 && i + 1 <= 14)
			importance[i + 1][j + 1] += quard_bishen_attack;
	}
	//other
	if (aRecordBoard[i][j] == AIcolor && aRecordBoard[i - 1][j + 1] == AIcolor && aRecordBoard[i - 2][j + 2] == AIcolor && aRecordBoard[i - 3][j + 3] == 0 && aRecordBoard[i - 4][j + 4] == AIcolor)
	{
		if (j + 3 <= 14 && i - 3 >= 0)
			importance[i - 3][j + 3] += quard_bishen_attack;
	}
	if (aRecordBoard[i][j] == AIcolor && aRecordBoard[i - 1][j + 1] == AIcolor && aRecordBoard[i - 2][j + 2] == 0 && aRecordBoard[i - 3][j + 3] == AIcolor && aRecordBoard[i - 4][j + 4] == AIcolor)
	{
		if (j + 2 <= 14 && i - 2 >= 0)
			importance[i - 2][j + 2] += quard_bishen_attack;
	}
	if (aRecordBoard[i][j] == AIcolor && aRecordBoard[i - 1][j + 1] == 0 && aRecordBoard[i - 2][j + 2] == AIcolor && aRecordBoard[i - 3][j + 3] == AIcolor && aRecordBoard[i - 4][j + 4] == AIcolor)
	{
		if (j + 1 <= 14 && i - 1 >= 0)
			importance[i - 1][j + 1] += quard_bishen_attack;
	}
	//PU TONG BU KONG
	if (aRecordBoard[i][j] == AIcolor && aRecordBoard[i + 1][j] == AIcolor && aRecordBoard[i + 2][j] == AIcolor && aRecordBoard[i + 3][j] == AIcolor)
	{
		if (i + 4 <= 14)
			importance[i + 4][j] += quard_bishen_attack;
		if (i - 1 >= 0)
			importance[i - 1][j] += quard_bishen_attack;
	}
	if (aRecordBoard[i][j] == AIcolor && aRecordBoard[i][j + 1] == AIcolor && aRecordBoard[i][j + 2] == AIcolor && aRecordBoard[i][j + 3] == AIcolor)
	{
		if (j + 4 <= 14)
			importance[i][j + 4] += quard_bishen_attack;
		if (j - 1 >= 0)
			importance[i][j - 1] += quard_bishen_attack;
	}
	if (aRecordBoard[i][j] == AIcolor && aRecordBoard[i + 1][j + 1] == AIcolor && aRecordBoard[i + 2][j + 2] == AIcolor && aRecordBoard[i + 3][j + 3] == AIcolor)
	{
		if (j + 4 <= 14 && i + 4 <= 14)
			importance[i + 4][j + 4] += quard_bishen_attack;
		if (j - 1 >= 0 && i - 1 >= 0)
			importance[i - 1][j - 1] += quard_bishen_attack;
	}
	if (aRecordBoard[i][j] == AIcolor && aRecordBoard[i - 1][j + 1] == AIcolor && aRecordBoard[i - 2][j + 2] == AIcolor && aRecordBoard[i - 3][j + 3] == AIcolor)
	{
		if (j + 4 <= 14 && i - 4 >= 0)
			importance[i - 4][j + 4] += quard_bishen_attack;
		if (j - 1 >= 0 && i + 1 <= 14)
			importance[i + 1][j - 1] += quard_bishen_attack;
	}
}

int calculate_defend(int i, int j)
{ //4ZI
	//HORIZEN
	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i + 1][j] == playercolor && aRecordBoard[i + 2][j] == playercolor && aRecordBoard[i + 3][j] == 0 && aRecordBoard[i + 4][j] == playercolor)
	{
		if (i + 3 <= 14)
			importance[i + 3][j] += quardzi_defend;
	}
	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i + 1][j] == playercolor && aRecordBoard[i + 2][j] == 0 && aRecordBoard[i + 3][j] == playercolor && aRecordBoard[i + 4][j] == playercolor)
	{
		if (i + 2 <= 14)
			importance[i + 2][j] += quardzi_defend;
	}
	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i + 1][j] == 0 && aRecordBoard[i + 2][j] == playercolor && aRecordBoard[i + 3][j] == playercolor && aRecordBoard[i + 4][j] == playercolor)
	{
		if (i + 1 <= 14)
			importance[i + 3][j] += quardzi_defend;
	}
	//vertical
	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i][j + 1] == playercolor && aRecordBoard[i][j + 2] == playercolor && aRecordBoard[i][j + 3] == 0 && aRecordBoard[i][j + 4] == playercolor)
	{
		if (j + 3 <= 14)
			importance[i][j + 3] += quardzi_defend;
	}
	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i][j + 1] == playercolor && aRecordBoard[i][j + 2] == 0 && aRecordBoard[i][j + 3] == playercolor && aRecordBoard[i][j + 4] == playercolor)
	{
		if (j + 2 <= 14)
			importance[i][j + 2] += quardzi_defend;
	}
	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i][j + 1] == 0 && aRecordBoard[i][j + 2] == playercolor && aRecordBoard[i][j + 3] == playercolor && aRecordBoard[i][j + 4] == playercolor)
	{
		if (j + 1 <= 14)
			importance[i][j + 1] += quardzi_defend;
	}
	//left right
	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i + 1][j + 1] == playercolor && aRecordBoard[i + 2][j + 2] == playercolor && aRecordBoard[i + 3][j + 3] == 0 && aRecordBoard[i + 4][j + 4] == playercolor)
	{
		if (j + 3 <= 14 && i + 3 <= 14)
			importance[i + 3][j + 3] += quardzi_defend;
	}
	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i + 1][j + 1] == playercolor && aRecordBoard[i + 2][j + 2] == 0 && aRecordBoard[i + 3][j + 3] == playercolor && aRecordBoard[i + 4][j + 4] == playercolor)
	{
		if (j + 2 <= 14 && i + 2 <= 14)
			importance[i + 2][j + 2] += quardzi_defend;
	}
	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i + 1][j + 1] == 0 && aRecordBoard[i + 2][j + 2] == playercolor && aRecordBoard[i + 3][j + 3] == playercolor && aRecordBoard[i + 4][j + 4] == playercolor)
	{
		if (j + 1 <= 14 && i + 1 <= 14)
			importance[i + 1][j + 1] += quardzi_defend;
	}
	//other
	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i - 1][j + 1] == playercolor && aRecordBoard[i - 2][j + 2] == playercolor && aRecordBoard[i - 3][j + 3] == 0 && aRecordBoard[i - 4][j + 4] == playercolor)
	{
		if (j + 3 <= 14 && i - 3 >= 0)
			importance[i - 3][j + 3] += quardzi_defend;
	}
	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i - 1][j + 1] == playercolor && aRecordBoard[i - 2][j + 2] == 0 && aRecordBoard[i - 3][j + 3] == playercolor && aRecordBoard[i - 4][j + 4] == playercolor)
	{
		if (j + 2 <= 14 && i - 2 >= 0)
			importance[i - 2][j + 2] += quardzi_defend;
	}
	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i - 1][j + 1] == 0 && aRecordBoard[i - 2][j + 2] == playercolor && aRecordBoard[i - 3][j + 3] == playercolor && aRecordBoard[i - 4][j + 4] == playercolor)
	{
		if (j + 1 <= 14 && i - 1 >= 0)
			importance[i - 1][j + 1] += quardzi_defend;
	}
	//PU TONG BU KONG
	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i + 1][j] == playercolor && aRecordBoard[i + 2][j] == playercolor && aRecordBoard[i + 3][j] == playercolor)
	{
		if (i + 4 <= 14)
			importance[i + 4][j] += quard_bishou_defend;
		if (i - 1 >= 0)
			importance[i - 1][j] += quard_bishou_defend;
	}
	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i][j + 1] == playercolor && aRecordBoard[i][j + 2] == playercolor && aRecordBoard[i][j + 3] == playercolor)
	{
		if (j + 4 <= 14)
			importance[i][j + 4] += quard_bishou_defend;
		if (j - 1 >= 0)
			importance[i][j - 1] += quard_bishou_defend;
	}
	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i + 1][j + 1] == playercolor && aRecordBoard[i + 2][j + 2] == playercolor && aRecordBoard[i + 3][j + 3] == playercolor)
	{
		if (j + 4 <= 14 && i + 4 <= 14)
			importance[i + 4][j + 4] += quard_bishou_defend;
		if (j - 1 >= 0 && i - 1 >= 0)
			importance[i - 1][j - 1] += quard_bishou_defend;
	}
	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i - 1][j + 1] == playercolor && aRecordBoard[i - 2][j + 2] == playercolor && aRecordBoard[i - 3][j + 3] == playercolor)
	{
		if (j + 4 <= 14 && i - 4 >= 0)
			importance[i - 4][j + 4] += quard_bishou_defend;
		if (j - 1 >= 0 && i + 1 <= 14)
			importance[i + 1][j - 1] += quard_bishou_defend;
	}

	//3 ZI
	//HORIZEN
	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i + 1][j] == playercolor && aRecordBoard[i + 2][j] == playercolor)
	{
		if (i - 1 >= 0)
		{
			if (i + 3 <= 14 && aRecordBoard[i + 3][j] != AIcolor)
				importance[i - 1][j] += 10000;
			else
				importance[i - 1][j] += 100;
		}
		if (i + 3 <= 14)
		{
			if (i - 1 >= 0 && aRecordBoard[i - 1][j] != AIcolor)
				importance[i + 3][j] += 10000;
			else
				importance[i + 3][j] += 100;
		}
		else
			;
	}
	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i + 1][j] == 0 && aRecordBoard[i + 2][j] == playercolor && aRecordBoard[i + 3][j] == playercolor)
	{
		if (i + 1 <= 14)
			importance[i + 1][j] += 10000;
	}
	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i + 1][j] == playercolor && aRecordBoard[i + 2][j] == 0 && aRecordBoard[i + 3][j] == playercolor)
	{
		if (i + 2 <= 14)
			importance[i + 2][j] += 10000;
	}
	else
		;
	//VERTICAL

	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i][j + 1] == playercolor && aRecordBoard[i][j + 2] == playercolor)
	{
		if (j - 1 >= 0)
		{
			if (j + 3 <= 14 && aRecordBoard[i][j + 3] != AIcolor)
				importance[i][j - 1] += 10000;
			else
				importance[i][j - 1] += 100;
		}
		if (j + 3 <= 14)
		{
			if (j - 1 >= 0 && aRecordBoard[i][j - 1] != AIcolor)
				importance[i][j + 3] += 10000;
			else
				importance[i][j + 3] += 100;
		}
	}
	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i][j + 1] == playercolor && aRecordBoard[i][j + 2] == 0 && aRecordBoard[i][j + 3] == playercolor)
	{
		printf("haha");
		if (j + 2 <= 14)
		{
			printf("haha");
			importance[i][j + 2] = importance[i][j + 2] + 10000;
		}
	}
	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i][j + 1] == 0 && aRecordBoard[i][j + 2] == playercolor && aRecordBoard[i][j + 3] == playercolor)
	{
		printf("haha");
		if (j + 1 <= 14)
		{
			printf("haha");
			importance[i][j + 1] = importance[i][j + 1] + 10000;
		}
	}
	//LEFT RIGHT
	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i + 1][j + 1] == playercolor && aRecordBoard[i + 2][j + 2] == playercolor)
	{
		if (i - 1 >= 0 && j - 1 >= 0)
		{
			if (j + 3 <= 14 && i + 3 <= 14 && aRecordBoard[i + 3][j + 3] != AIcolor)
				importance[i - 1][j - 1] += 10000;
			else
				importance[i - 1][j - 1] += 100;
		}
		if (i + 3 <= 14 && j + 3 <= 14)
		{
			if (j - 1 >= 0 && i - 1 >= 0 && aRecordBoard[i - 1][j - 1] != AIcolor)
				importance[i + 3][j + 3] += 10000;
			else
				importance[i + 3][j + 3] += 100;
		}
	}
	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i + 1][j + 1] == playercolor && aRecordBoard[i + 2][j + 2] == 0 && aRecordBoard[i + 3][j + 3] == playercolor)
	{

		if (i + 2 <= 14 && j + 2 <= 14)
			importance[i + 2][j + 2] += 10000;
	}
	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i + 1][j + 1] == 0 && aRecordBoard[i + 2][j + 2] == playercolor && aRecordBoard[i + 3][j + 3] == playercolor)
	{
		printf("haha");
		if (i + 1 <= 14 && j + 1 <= 14)
			importance[i + 1][j + 1] += 10000;
	}
	//OTHER

	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i - 1][j + 1] == playercolor && aRecordBoard[i - 2][j + 2] == playercolor)
	{
		if (i + 1 <= 14 && j - 1 >= 0)
		{
			if (i - 3 >= 0 && j + 3 <= 14 && aRecordBoard[i - 3][j + 3] != AIcolor)
				importance[i + 1][j - 1] += 10000;
			else
				importance[i + 1][j - 1] += 100;
		}
		if (i - 3 >= 0 && j + 3 <= 14)
		{
			if (i + 1 <= 14 && j - 1 >= 0 && aRecordBoard[i + 1][j - 1] != AIcolor)
				importance[i - 3][j + 3] += 10000;
			else
				importance[i - 3][j + 3] += 100;
		}
	}
	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i - 1][j + 1] == playercolor && aRecordBoard[i - 2][j + 2] == 0 && aRecordBoard[i - 3][j + 3] == playercolor)
	{
		if (i - 2 >= 0 && j + 2 <= 14)
			importance[i - 2][j + 2] += 10000;
	}
	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i - 1][j + 1] == 0 && aRecordBoard[i - 2][j + 2] == playercolor && aRecordBoard[i - 3][j + 3] == playercolor)
	{
		if (i - 1 >= 0 && j + 1 <= 14)
			importance[i - 1][j + 1] += 10000;
	}

	//2 ZI
	//horizon
	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i + 1][j] == playercolor)
	{
		if (i - 1 >= 0)
			importance[i - 1][j] += 100;
		else
			;
		if (i + 2 <= 14)
			importance[i + 2][j] += 100;
		else
			;
	}
	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i + 1][j] == 0 && aRecordBoard[i + 2][j] == playercolor)
	{
		if (i + 1 <= 14)
			importance[i + 1][j] += 100;
	}
	//vertical
	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i][j + 1] == playercolor)
	{
		if (j - 1 >= 0)
			importance[i][j - 1] += 100;
		else if (j + 2 <= 14)
			importance[i][j + 2] += 100;
	}
	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i + 1][j] == 0 && aRecordBoard[i + 2][j] == playercolor)
	{
		if (j + 1 <= 14)
			importance[i][j + 1] += 100;
	}
	//left right
	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i + 1][j + 1] == playercolor)
	{
		if (i - 1 >= 0 && j - 1 >= 0)
			importance[i - 1][j - 1] += 100;
		else
			;
		if (i + 2 <= 14 && j + 2 <= 14)
			importance[i + 2][j + 2] += 100;
		else
			;
	}
	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i + 1][j + 1] == 0 && aRecordBoard[i + 2][j + 2] == playercolor)
	{
		if (i + 1 <= 14 && j + 1 <= 14)
			importance[i + 1][j + 1] += 100;
	}
	//other
	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i - 1][j + 1] == playercolor)
	{
		if (i + 1 <= 14 && j - 1 >= 0)
			importance[i + 1][j - 1] += 100;
		else
			;
		if (i - 2 >= 0 && j + 2 <= 14)
			importance[i - 2][j + 2] += 100;
		else
			;
	}
	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i - 1][j + 1] == 0 && aRecordBoard[i - 2][j + 2] == playercolor)
	{
		if (i - 1 >= 0 && j + 1 <= 14)
			importance[i - 1][j + 1] += 100;
	}
	//1ZI
	if (aRecordBoard[i][j] == playercolor)
	{
		int i1, j1;
		int left, right;
		int left1, right1;

		if (i >= 1 && i <= 13)
		{
			left = right = 1;
		}
		else if (i == 0)
		{
			left = 0;
			right = 1;
		}
		else if (i == 14)
		{
			left = 1;
			right = 0;
		}
		else
			;

		if (j >= 1 && j <= 13)
		{
			left1 = right1 = 1;
		}
		else if (j == 0)
		{
			left1 = 0;
			right1 = 1;
		}
		else if (j == 14)
		{
			left1 = 1;
			right1 = 0;
		}
		else
			;

		for (i1 = i - left; i1 <= i + right; i1++)
		{
			for (j1 = j - left1; j1 <= j + right; j1++)
			{
				importance[i1][j1] += 10;
			}
		}
	}
	return 0;
}



void remove_exist(void)
{
	int i, j;
	for (i = 0; i <= 14; i++)
	{
		for (j = 0; j <= 14; j++)
		{
			if (aRecordBoard[i][j] != 0)
				importance[i][j] = 0;
		}
	}
}

int AI(void)
{
	int i, j;
	for (i = 0; i <= 14; i++)
	{
		for (j = 0; j <= 14; j++)
		{
			importance[i][j] = 0;
		}
	}

	importance[7][7] += 1;

	for (i = 0; i <= 14; i++)
	{
		for (j = 0; j <= 14; j++)
		{
			if (check(i, j) == 1)
			{
				calculate(i, j);
				calculate_defend(i, j);
			}
			else
				;
		}
	}

	remove_exist();

	for (i = 0; i <= 14; i++)
	{
		for (j = 0; j <= 14; j++)
		{
			if (importance[i][j] >= nextstep_index)
			{
				nextstep_index = importance[i][j];
				nextstep_1 = i;
				nextstep_2 = j;
			}
			else
				;
		}
	}

	printf("%d  %d \n", nextstep_1, nextstep_2);
	for (i = 0; i <= 14; i++)
	{
		for (j = 0; j <= 13; j++)
		{
			printf("%d\t", importance[i][j]);
		}
		printf("%d\t\n", importance[i][j]);
	}

	if (aRecordBoard[nextstep_1][nextstep_2] == 0)
	{
		aRecordBoard[nextstep_1][nextstep_2] = AIcolor;
		return 2;
	}
	else
		return 1;
}

int referee(void)
{
	int i, j;
	for (i = 0; i <= 10; i++)
	{
		for (j = 0; j <= 14; j++)
		{
			if (aRecordBoard[i][j] == 1 && aRecordBoard[i + 1][j] == 1 && aRecordBoard[i + 2][j] == 1 && aRecordBoard[i + 3][j] == 1 && aRecordBoard[i + 4][j] == 1)
			{
				return 1;
			}
			else if (aRecordBoard[i][j] == 2 && aRecordBoard[i + 1][j] == 2 && aRecordBoard[i + 2][j] == 2 && aRecordBoard[i + 3][j] == 2 && aRecordBoard[i + 4][j] == 2)
			{
				return 2;
			}
		}
	}
	for (i = 0; i <= 14; i++)
	{
		for (j = 0; j <= 10; j++)
		{
			if (aRecordBoard[i][j] == 1 && aRecordBoard[i][j + 1] == 1 && aRecordBoard[i][j + 2] == 1 && aRecordBoard[i][j + 3] == 1 && aRecordBoard[i][j + 4] == 1)
			{
				return 1;
			}
			else if (aRecordBoard[i][j] == 2 && aRecordBoard[i][j + 1] == 2 && aRecordBoard[i][j + 2] == 2 && aRecordBoard[i][j + 3] == 2 && aRecordBoard[i][j + 4] == 2)
			{
				return 2;
			}
		}
	}
	for (i = 0; i <= 10; i++)
	{
		for (j = 0; j <= 10; j++)
		{
			if (aRecordBoard[i][j] == 1 && aRecordBoard[i + 1][j + 1] == 1 && aRecordBoard[i + 2][j + 2] == 1 && aRecordBoard[i + 3][j + 3] == 1 && aRecordBoard[i + 4][j + 4] == 1)
			{
				return 1;
			}
			else if (aRecordBoard[i][j] == 2 && aRecordBoard[i + 1][j + 1] == 2 && aRecordBoard[i + 2][j + 2] == 2 && aRecordBoard[i + 3][j + 3] == 2 && aRecordBoard[i + 4][j + 4] == 2)
			{
				return 2;
			}
		}
	}
	for (i = 4; i <= 14; i++)
	{
		for (j = 0; j <= 10; j++)
		{
			if (aRecordBoard[i][j] == 1 && aRecordBoard[i - 1][j + 1] == 1 && aRecordBoard[i - 2][j + 2] == 1 && aRecordBoard[i - 3][j + 3] == 1 && aRecordBoard[i - 4][j + 4] == 1)
			{
				return 1;
			}
			else if (aRecordBoard[i][j] == 2 && aRecordBoard[i - 1][j + 1] == 2 && aRecordBoard[i - 2][j + 2] == 2 && aRecordBoard[i - 3][j + 3] == 2 && aRecordBoard[i - 4][j + 4] == 2)
			{
				return 2;
			}
		}
	}
	return 0;
}
