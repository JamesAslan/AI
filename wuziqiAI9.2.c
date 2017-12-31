#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 15
#define CHARSIZE 2
//#define depth_max 6
//#define width 35
#define choose_max 20

#define quardzi_defend 30000
#define quard_bishou_defend 80000
#define huoer_attack 60
#define tri_kong_attack 5000
#define tri_si_attack 100
#define tri_huo_kong_partial 2000
#define quard_bishen_attack 100000

#define wu_eva 5000
#define huo_si_eva 1280
#define si_si_eva 320
#define huo_san_eva 320
#define si_san_eva 80
#define huo_er_eva 80
#define si_er_eva 20
#define yi_eva 1

#define wu_eva_anti 5000
#define huo_si_eva_anti 1280
#define si_si_eva_anti 320
#define huo_san_eva_anti 320
#define si_san_eva_anti 80
#define huo_er_eva_anti 80
#define si_er_eva_anti 20
#define yi_eva_anti 1

void initRecordBorard(void);
void recordtoDisplayArray(void);
void displayBoard(void);

//ï¿½ï¿½ï¿½ï¿½Ê¹ï¿½Ãµï¿½ï¿½ï¿½GBKï¿½ï¿½ï¿½ë£¬Ã¿Ò»ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ö·ï¿½Õ¼ï¿½ï¿½2ï¿½ï¿½ï¿½Ö½Ú¡ï¿½

//ï¿½ï¿½ï¿½Ì»ï¿½ï¿½ï¿½Ä£ï¿½ï¿½
char aInitDisplayBoardArray[SIZE][SIZE*CHARSIZE+1] = 
{
		"©³©Ó©Ó©Ó©Ó©Ó©Ó©Ó©Ó©Ó©Ó©Ó©Ó©Ó©·",
		"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
		"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
		"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
		"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
		"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
		"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
		"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
		"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
		"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
		"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
		"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
		"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
		"©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
		"©»©Û©Û©Û©Û©Û©Û©Û©Û©Û©Û©Û©Û©Û©¿"
};
//´ËÊý×éÓÃÓÚÏÔÊ¾ÆåÅÌ 
char aDisplayBoardArray[SIZE][SIZE*CHARSIZE+1];
 
char play1Pic[]="¡ñ";//ºÚÆå×Ó;
char play1CurrentPic[]="¡ø"; 

char play2Pic[]="¡ò";//°×Æå×Ó;
char play2CurrentPic[]="¡÷";

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
int AI_reduced(int player, int depth, int alpha, int beta);

int AIcolor;
int playercolor;
int initialAIcolor;
int initialplayercolor;

int importance[15][15];
int Round = 1;
int nextstep_1 = 0;
int nextstep_2 = 0;
int nextstep_index = 0;
int symbol = 0;

int originalboard[15][15];
int depth = 2;
int choose[2];
int width, depth_max;

struct evaluation
{
	int wu;
	int huo_si;
	int si_si;
	int huo_san;
	int si_san;
	int huo_er;
	int si_er;
	int yi;
};

struct eva_outcome
{
	int outcome;
	int huo_san;
	int si_si;
	int huo_si;
	int wu;
};

struct point
{
	int x;
	int y;
};

struct results
{
	int result;
	int kill;
};

int sortarray[225];

//struct point *index[225];

int main()

{
	initRecordBorard();
	printf("enter 1 to enable 2 players mode \n");
	scanf("%d", &mode);
	printf("\n");
	if (mode == 1)
	{
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
			initialplayercolor = playercolor;
			initialAIcolor = AIcolor;
		}
		else
		{
			recordtoDisplayArray();
			displayBoard();
			Round = 1;
			playercolor = 2;
			AIcolor = 1;
			initialplayercolor = playercolor;
			initialAIcolor = AIcolor;
		}
		singleplayer();
	}
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

//??aRecordBoard?ï¿½ï¿½????????ï¿½ï¿½????????aDisplayBoardArray??
void recordtoDisplayArray(void)
{
	//?????????aInitDisplayBoardArray?ï¿½ï¿½???????????????aDisplayBoardArray??
	int i, j;
	for (i = 0; i <= 14; i++)
	{
		for (j = 0; j <= 30; j++)
		{
			aDisplayBoardArray[i][j] = aInitDisplayBoardArray[i][j];
		}
	}
	//??????????aRecordBoard??????????0?????????????????aDisplayBoardArray?????ï¿½ï¿½????
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
	int a;
	char b;
	scanf("%d,%c", &a, &b);
	printf("\n");
	if (aRecordBoard[15 - a][b - 'A'] == 0)
	{
		aRecordBoard[15 - a][b - 'A'] = 1;
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
	scanf("%d,%c", &a, &b);
	printf("\n");
	if (aRecordBoard[15 - a][b - 'A'] == 0)
	{
		aRecordBoard[15 - a][b - 'A'] = 2;
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
		aRecordBoard[15 - a][b - 'A'] = initialplayercolor;
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
	if (Round == 1)
	{
		Round = heifang();
		recordtoDisplayArray();
		displayBoard();
	}
	else
	{
		Round = baifang();
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
		doubleplayers();
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
	scanf("%d", &n);
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
		if (j + 2 <= 14)
			importance[i][j + 2] = importance[i][j + 2] + 10000;
	}
	if (aRecordBoard[i][j] == playercolor && aRecordBoard[i][j + 1] == 0 && aRecordBoard[i][j + 2] == playercolor && aRecordBoard[i][j + 3] == playercolor)
	{
		if (j + 1 <= 14)
			importance[i][j + 1] = importance[i][j + 1] + 10000;
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

void remove_exist(void) //qing chu suo you yi jing luo guo zi de dian
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

struct eva_outcome evaluator_anti(int color)
{
	int anti_color = (color - 1) ? 1 : 2;
	struct evaluation eva = {0, 0, 0, 0, 0, 0, 0, 0};
	struct eva_outcome outcomes;

	int RecordBoard_heng[240];
	int heng = 0;
	for (int i = 0; i <= 14; i++)
	{
		for (int j = 0; j <= 15; j++)
		{
			if (j != 15)
			{
				RecordBoard_heng[heng] = aRecordBoard[i][j];
			}
			else
				RecordBoard_heng[heng] = anti_color;
			heng++;
		}
	}

	int RecordBoard_shu[240];
	int shu = 0;
	for (int j = 0; j <= 14; j++)
	{
		for (int i = 0; i <= 15; i++)
		{
			if (i != 15)
			{
				RecordBoard_shu[shu] = aRecordBoard[i][j];
			}
			else
				RecordBoard_shu[shu] = anti_color;
			shu++;
		}
	}

	int RecordBoard_you[226];
	int you = 0;
	for (int i = 0; i <= 10; i++)
	{
		for (int j = 0; j <= 14; j++)
		{
			if (j + i < 14)
			{
				RecordBoard_you[you] = aRecordBoard[j][j + i];
				you++;
			}
			else if (j + i == 14)
			{
				RecordBoard_you[you] = aRecordBoard[j][j + i];
				you++;
				RecordBoard_you[you] = anti_color;
				you++;
				break;
			}
		}
	}
	for (int i = -10; i <= -1; i++)
	{
		for (int j = 14; j >= 0; j--)
		{
			if (j + i > 0)
			{
				RecordBoard_you[you] = aRecordBoard[j][j + i];
				you++;
			}
			else if (j + i == 0)
			{
				RecordBoard_you[you] = aRecordBoard[j][j + i];
				you++;
				RecordBoard_you[you] = anti_color;
				you++;
				break;
			}
		}
	}

	int RecordBoard_zuo[226];
	int zuo = 0;
	for (int i = 4; i <= 14; i++)
	{
		for (int j = 0; j <= 14; j++)
		{
			if (i - j > 0)
			{
				RecordBoard_zuo[zuo] = aRecordBoard[j][i - j];
				zuo++;
			}
			else if (i - j == 0)
			{
				RecordBoard_zuo[zuo] = aRecordBoard[j][i - j];
				zuo++;
				RecordBoard_zuo[zuo] = anti_color;
				zuo++;
				break;
			}
		}
	}
	for (int i = 15; i <= 24; i++)
	{
		for (int j = 14; j >= 0; j--)
		{
			if (i - j < 14)
			{
				RecordBoard_zuo[zuo] = aRecordBoard[j][i - j];
				zuo++;
			}
			else if (i - j == 14)
			{
				RecordBoard_zuo[zuo] = aRecordBoard[j][i - j];
				zuo++;
				RecordBoard_zuo[zuo] = anti_color;
				zuo++;
				break;
			}
		}
	}

	for (int i = 0; i <= 240; i++)
	{
		if (RecordBoard_heng[i] == color)
		{
			if (i + 1 <= 240 && RecordBoard_heng[i + 1] == color)
			{
				if (i + 2 <= 240 && RecordBoard_heng[i + 2] == color)
				{
					if (i + 3 <= 240 && RecordBoard_heng[i + 3] == color)
					{
						if (i + 4 <= 240 && RecordBoard_heng[i + 4] == color)
						{
							eva.wu++;
							i += 4;
						}
						else if ((i + 4 <= 240 && RecordBoard_heng[i + 4] == 0) && (i - 1 >= 0 && RecordBoard_heng[i - 1] == 0))
						{
							eva.huo_si++;
							i += 4;
						}

						else if ((i + 4 <= 240 && RecordBoard_heng[i + 4] == 0) || (i - 1 >= 0 && RecordBoard_heng[i - 1] == 0))
						{
							eva.si_si++;
							i += 4;
						}
					}
					else if (i + 4 <= 240 && RecordBoard_heng[i + 1] == color && RecordBoard_heng[i + 2] == color && RecordBoard_heng[i + 3] == 0 && RecordBoard_heng[i + 4] == color)
					{
						eva.si_si++;
						i += 4;
					}
					else if ((i + 3 <= 240 && RecordBoard_heng[i + 3] == 0) && (i - 1 >= 0 && RecordBoard_heng[i - 1] == 0))
					{
						eva.huo_san++;
						i += 3;
					}

					else if ((i + 3 <= 240 && RecordBoard_heng[i + 3] == 0) || (i - 1 >= 0 && RecordBoard_heng[i - 1] == 0))
					{
						eva.si_san++;
						i += 3;
					}
				}
				else if (i + 4 <= 240 && RecordBoard_heng[i + 2] == color && RecordBoard_heng[i + 3] == 0 && RecordBoard_heng[i + 4] == color)
				{
					eva.si_si++;
					i += 4;
				}
				else if (i + 4 <= 240 && RecordBoard_heng[i + 2] == 0 && RecordBoard_heng[i + 3] == color && RecordBoard_heng[i + 4] == color)
				{
					eva.si_si++;
					i += 4;
				}
				else if ((i - 1 >= 0 && RecordBoard_heng[i - 1] == 0) && (i + 4 <= 240 && RecordBoard_heng[i + 4] == 0) && RecordBoard_heng[i + 2] == 0 && RecordBoard_heng[i + 3] == color)
				{
					eva.huo_san++;
					i += 3;
				}
				else if ((i + 2 <= 240 && RecordBoard_heng[i + 2] == 0) && (i - 1 >= 0 && RecordBoard_heng[i - 1] == 0))
				{
					eva.huo_er++;
					i += 2;
				}

				else if ((i + 2 <= 240 && RecordBoard_heng[i + 2] == 0) || (i - 1 >= 0 && RecordBoard_heng[i - 1] == 0))
				{
					eva.si_er++;
					i += 2;
				}
			}
			else if (i + 4 <= 240 && RecordBoard_heng[i + 1] == 0 && RecordBoard_heng[i + 2] == color && RecordBoard_heng[i + 3] == color && RecordBoard_heng[i + 4] == color)
			{
				eva.si_si++;
				i += 4;
			}

			else if ((i - 1 >= 0 && RecordBoard_heng[i - 1] == 0) && (i + 4 <= 240 && RecordBoard_heng[i + 4] == 0) && RecordBoard_heng[i + 1] == 0 && RecordBoard_heng[i + 2] == color && RecordBoard_heng[i + 3] == color)
			{
				eva.huo_san++;
				i += 3;
			}
			else if ((i - 1 >= 0 && RecordBoard_heng[i - 1] == 0) && (i + 3 <= 240 && RecordBoard_heng[i + 3] == 0) && RecordBoard_heng[i + 1] == 0 && RecordBoard_heng[i + 2] == color)
			{
				eva.huo_er++;
				i += 2;
			}
			else if ((i + 1 <= 240 && RecordBoard_heng[i + 1] == 0) || (i - 1 >= 0 && RecordBoard_heng[i - 1] == 0))
			{
				eva.yi++;
				i++;
			}
		}
		else
			;
	}

	for (int i = 0; i <= 240; i++)
	{
		if (RecordBoard_shu[i] == color)
		{
			if (i + 1 <= 240 && RecordBoard_shu[i + 1] == color)
			{
				if (i + 2 <= 240 && RecordBoard_shu[i + 2] == color)
				{
					if (i + 3 <= 240 && RecordBoard_shu[i + 3] == color)
					{
						if (i + 4 <= 240 && RecordBoard_shu[i + 4] == color)
						{
							eva.wu++;
							i += 4;
						}
						else if ((i + 4 <= 240 && RecordBoard_shu[i + 4] == 0) && (i - 1 >= 0 && RecordBoard_shu[i - 1] == 0))
						{
							eva.huo_si++;
							i += 4;
						}

						else if ((i + 4 <= 240 && RecordBoard_shu[i + 4] == 0) || (i - 1 >= 0 && RecordBoard_shu[i - 1] == 0))
						{
							eva.si_si++;
							i += 4;
						}
					}
					else if (i + 4 <= 240 && RecordBoard_shu[i + 1] == color && RecordBoard_shu[i + 2] == color && RecordBoard_shu[i + 3] == 0 && RecordBoard_shu[i + 4] == color)
					{
						eva.si_si++;
						i += 4;
					}
					else if ((i + 3 <= 240 && RecordBoard_shu[i + 3] == 0) && (i - 1 >= 0 && RecordBoard_shu[i - 1] == 0))
					{
						eva.huo_san++;
						i += 3;
					}

					else if ((i + 3 <= 240 && RecordBoard_shu[i + 3] == 0) || (i - 1 >= 0 && RecordBoard_shu[i - 1] == 0))
					{
						eva.si_san++;
						i += 3;
					}
				}
				else if (i + 4 <= 240 && RecordBoard_shu[i + 2] == color && RecordBoard_shu[i + 3] == 0 && RecordBoard_shu[i + 4] == color)
				{
					eva.si_si++;
					i += 4;
				}
				else if (i + 4 <= 240 && RecordBoard_shu[i + 2] == 0 && RecordBoard_shu[i + 3] == color && RecordBoard_shu[i + 4] == color)
				{
					eva.si_si++;
					i += 4;
				}
				else if ((i - 1 >= 0 && RecordBoard_shu[i - 1] == 0) && (i + 4 <= 240 && RecordBoard_shu[i + 4] == 0) && RecordBoard_shu[i + 2] == 0 && RecordBoard_shu[i + 3] == color)
				{
					eva.huo_san++;
					i += 3;
				}
				else if ((i + 2 <= 240 && RecordBoard_shu[i + 2] == 0) && (i - 1 >= 0 && RecordBoard_shu[i - 1] == 0))
				{
					eva.huo_er++;
					i += 2;
				}

				else if ((i + 2 <= 240 && RecordBoard_shu[i + 2] == 0) || (i - 1 >= 0 && RecordBoard_shu[i - 1] == 0))
				{
					eva.si_er++;
					i += 2;
				}
			}
			else if (i + 4 <= 240 && RecordBoard_shu[i + 1] == 0 && RecordBoard_shu[i + 2] == color && RecordBoard_shu[i + 3] == color && RecordBoard_shu[i + 4] == color)
			{
				eva.si_si++;
				i += 4;
			}

			else if ((i - 1 >= 0 && RecordBoard_shu[i - 1] == 0) && (i + 4 <= 240 && RecordBoard_shu[i + 4] == 0) && RecordBoard_shu[i + 1] == 0 && RecordBoard_shu[i + 2] == color && RecordBoard_shu[i + 3] == color)
			{
				eva.huo_san++;
				i += 3;
			}
			else if ((i - 1 >= 0 && RecordBoard_shu[i - 1] == 0) && (i + 3 <= 240 && RecordBoard_shu[i + 3] == 0) && RecordBoard_shu[i + 1] == 0 && RecordBoard_shu[i + 2] == color)
			{
				eva.huo_er++;
				i += 2;
			}
			else if ((i + 1 <= 240 && RecordBoard_shu[i + 1] == 0) || (i - 1 >= 0 && RecordBoard_shu[i - 1] == 0))
			{
				eva.yi++;
				i++;
			}
		}
		else
			;
	}

	for (int i = 0; i <= 226; i++)
	{
		if (RecordBoard_zuo[i] == color)
		{
			if (i + 1 <= 226 && RecordBoard_zuo[i + 1] == color)
			{
				if (i + 2 <= 226 && RecordBoard_zuo[i + 2] == color)
				{
					if (i + 3 <= 226 && RecordBoard_zuo[i + 3] == color)
					{
						if (i + 4 <= 226 && RecordBoard_zuo[i + 4] == color)
						{
							eva.wu++;
							i += 4;
						}
						else if ((i + 4 <= 226 && RecordBoard_zuo[i + 4] == 0) && (i - 1 >= 0 && RecordBoard_zuo[i - 1] == 0))
						{
							eva.huo_si++;
							i += 4;
						}

						else if ((i + 4 <= 226 && RecordBoard_zuo[i + 4] == 0) || (i - 1 >= 0 && RecordBoard_zuo[i - 1] == 0))
						{
							eva.si_si++;
							i += 4;
						}
					}
					else if (i + 4 <= 226 && RecordBoard_zuo[i + 3] == 0 && RecordBoard_zuo[i + 4] == color)
					{
						eva.si_si++;
						i += 4;
					}
					else if ((i + 3 <= 226 && RecordBoard_zuo[i + 3] == 0) && (i - 1 >= 0 && RecordBoard_zuo[i - 1] == 0))
					{
						eva.huo_san++;
						i += 3;
					}

					else if ((i + 3 <= 226 && RecordBoard_zuo[i + 3] == 0) || (i - 1 >= 0 && RecordBoard_zuo[i - 1] == 0))
					{
						eva.si_san++;
						i += 3;
					}
				}
				else if (i + 4 <= 226 && RecordBoard_zuo[i + 2] == 0 && RecordBoard_zuo[i + 3] == color && RecordBoard_zuo[i + 4] == color)
				{
					eva.si_si++;
					i += 4;
				}
				else if ((i - 1 >= 0 && RecordBoard_zuo[i - 1] == 0) && (i + 4 <= 226 && RecordBoard_zuo[i + 4] == 0) && RecordBoard_zuo[i + 2] == 0 && RecordBoard_zuo[i + 3] == color)
				{
					eva.huo_san++;
					i += 3;
				}
				else if ((i + 2 <= 226 && RecordBoard_zuo[i + 2] == 0) && (i - 1 >= 0 && RecordBoard_zuo[i - 1] == 0))
				{
					eva.huo_er++;
					i += 2;
				}

				else if ((i + 2 <= 226 && RecordBoard_zuo[i + 2] == 0) || (i - 1 >= 0 && RecordBoard_zuo[i - 1] == 0))
				{
					eva.si_er++;
					i += 2;
				}
			}
			else if (i + 4 <= 226 && RecordBoard_zuo[i + 1] == 0 && RecordBoard_zuo[i + 2] == color && RecordBoard_zuo[i + 3] == color && RecordBoard_zuo[i + 4] == color)
			{
				eva.si_si++;
				i += 4;
			}

			else if ((i - 1 >= 0 && RecordBoard_zuo[i - 1] == 0) && (i + 4 <= 226 && RecordBoard_zuo[i + 4] == 0) && RecordBoard_zuo[i + 1] == 0 && RecordBoard_zuo[i + 2] == color && RecordBoard_zuo[i + 3] == color)
			{
				eva.huo_san++;
				i += 3;
			}
			else if ((i - 1 >= 0 && RecordBoard_zuo[i - 1] == 0) && (i + 3 <= 226 && RecordBoard_zuo[i + 3] == 0) && RecordBoard_zuo[i + 1] == 0 && RecordBoard_zuo[i + 2] == color)
			{
				eva.huo_er++;
				i += 2;
			}
			else if ((i + 1 <= 226 && RecordBoard_zuo[i + 1] == 0) || (i - 1 >= 0 && RecordBoard_zuo[i - 1] == 0))
			{
				eva.yi++;
				i++;
			}
		}
		else
			;
	}

	for (int i = 0; i <= 226; i++)
	{
		if (RecordBoard_you[i] == color)
		{
			if (i + 1 <= 226 && RecordBoard_you[i + 1] == color)
			{
				if (i + 2 <= 226 && RecordBoard_you[i + 2] == color)
				{
					if (i + 3 <= 226 && RecordBoard_you[i + 3] == color)
					{
						if (i + 4 <= 226 && RecordBoard_you[i + 4] == color)
						{
							eva.wu++;
							i += 4;
						}
						else if ((i + 4 <= 226 && RecordBoard_you[i + 4] == 0) && (i - 1 >= 0 && RecordBoard_you[i - 1] == 0))
						{
							eva.huo_si++;
							i += 4;
						}

						else if ((i + 4 <= 226 && RecordBoard_you[i + 4] == 0) || (i - 1 >= 0 && RecordBoard_you[i - 1] == 0))
						{
							eva.si_si++;
							i += 4;
						}
					}
					else if (i + 4 <= 226 && RecordBoard_you[i + 1] == color && RecordBoard_you[i + 2] == color && RecordBoard_you[i + 3] == 0 && RecordBoard_you[i + 4] == color)
					{
						eva.si_si++;
						i += 4;
					}
					else if ((i + 3 <= 226 && RecordBoard_you[i + 3] == 0) && (i - 1 >= 0 && RecordBoard_you[i - 1] == 0))
					{
						eva.huo_san++;
						i += 3;
					}

					else if ((i + 3 <= 226 && RecordBoard_you[i + 3] == 0) || (i - 1 >= 0 && RecordBoard_you[i - 1] == 0))
					{
						eva.si_san++;
						i += 3;
					}
				}
				else if (i + 4 <= 226 && RecordBoard_you[i + 2] == color && RecordBoard_you[i + 3] == 0 && RecordBoard_you[i + 4] == color)
				{
					eva.si_si++;
					i += 4;
				}
				else if (i + 4 <= 226 && RecordBoard_you[i + 2] == 0 && RecordBoard_you[i + 3] == color && RecordBoard_you[i + 4] == color)
				{
					eva.si_si++;
					i += 4;
				}
				else if ((i - 1 >= 0 && RecordBoard_you[i - 1] == 0) && (i + 4 <= 226 && RecordBoard_you[i + 4] == 0) && RecordBoard_you[i + 2] == 0 && RecordBoard_you[i + 3] == color)
				{
					eva.huo_san++;
					i += 3;
				}
				else if ((i + 2 <= 226 && RecordBoard_you[i + 2] == 0) && (i - 1 >= 0 && RecordBoard_you[i - 1] == 0))
				{
					eva.huo_er++;
					i += 2;
				}

				else if ((i + 2 <= 226 && RecordBoard_you[i + 2] == 0) || (i - 1 >= 0 && RecordBoard_you[i - 1] == 0))
				{
					eva.si_er++;
					i += 2;
				}
			}
			else if (i + 4 <= 226 && RecordBoard_you[i + 1] == 0 && RecordBoard_you[i + 2] == color && RecordBoard_you[i + 3] == color && RecordBoard_you[i + 4] == color)
			{
				eva.si_si++;
				i += 4;
			}

			else if ((i - 1 >= 0 && RecordBoard_you[i - 1] == 0) && (i + 4 <= 226 && RecordBoard_you[i + 4] == 0) && RecordBoard_you[i + 1] == 0 && RecordBoard_you[i + 2] == color && RecordBoard_you[i + 3] == color)
			{
				eva.huo_san++;
				i += 3;
			}
			else if ((i - 1 >= 0 && RecordBoard_you[i - 1] == 0) && (i + 3 <= 226 && RecordBoard_you[i + 3] == 0) && RecordBoard_you[i + 1] == 0 && RecordBoard_you[i + 2] == color)
			{
				eva.huo_er++;
				i += 2;
			}
			else if ((i + 1 <= 226 && RecordBoard_you[i + 1] == 0) || (i - 1 >= 0 && RecordBoard_you[i - 1] == 0))
			{
				eva.yi++;
				i++;
			}
		}
		else
			;
	}

	outcomes.outcome = (eva.yi * yi_eva_anti) + (eva.si_er * si_er_eva_anti) + (eva.huo_er * huo_er_eva_anti) + (eva.si_san * si_san_eva_anti) + (eva.huo_san * huo_san_eva_anti) + (eva.si_si * si_si_eva_anti) + (eva.huo_si * huo_si_eva_anti) + (eva.wu * wu_eva_anti);
	outcomes.huo_san = eva.huo_san;
	outcomes.huo_si = eva.huo_si;
	outcomes.si_si = eva.si_si;
	outcomes.wu = eva.wu;
	return outcomes;
}

struct eva_outcome evaluator(int color)
{
	int anti_color = (color - 1) ? 1 : 2;
	struct evaluation eva = {0, 0, 0, 0, 0, 0, 0, 0};
	struct eva_outcome outcomes;

	int RecordBoard_heng[240];
	int heng = 0;
	for (int i = 0; i <= 14; i++)
	{
		for (int j = 0; j <= 15; j++)
		{
			if (j != 15)
			{
				RecordBoard_heng[heng] = aRecordBoard[i][j];
			}
			else
				RecordBoard_heng[heng] = anti_color;
			heng++;
		}
	}

	int RecordBoard_shu[240];
	int shu = 0;
	for (int j = 0; j <= 14; j++)
	{
		for (int i = 0; i <= 15; i++)
		{
			if (i != 15)
			{
				RecordBoard_shu[shu] = aRecordBoard[i][j];
			}
			else
				RecordBoard_shu[shu] = anti_color;
			shu++;
		}
	}

	int RecordBoard_you[226];
	int you = 0;
	for (int i = 0; i <= 10; i++)
	{
		for (int j = 0; j <= 14; j++)
		{
			if (j + i < 14)
			{
				RecordBoard_you[you] = aRecordBoard[j][j + i];
				you++;
			}
			else if (j + i == 14)
			{
				RecordBoard_you[you] = aRecordBoard[j][j + i];
				you++;
				RecordBoard_you[you] = anti_color;
				you++;
				break;
			}
		}
	}
	for (int i = -10; i <= -1; i++)
	{
		for (int j = 14; j >= 0; j--)
		{
			if (j + i > 0)
			{
				RecordBoard_you[you] = aRecordBoard[j][j + i];
				you++;
			}
			else if (j + i == 0)
			{
				RecordBoard_you[you] = aRecordBoard[j][j + i];
				you++;
				RecordBoard_you[you] = anti_color;
				you++;
				break;
			}
		}
	}

	int RecordBoard_zuo[226];
	int zuo = 0;
	for (int i = 4; i <= 14; i++)
	{
		for (int j = 0; j <= 14; j++)
		{
			if (i - j > 0)
			{
				RecordBoard_zuo[zuo] = aRecordBoard[j][i - j];
				zuo++;
			}
			else if (i - j == 0)
			{
				RecordBoard_zuo[zuo] = aRecordBoard[j][i - j];
				zuo++;
				RecordBoard_zuo[zuo] = anti_color;
				zuo++;
				break;
			}
		}
	}
	for (int i = 15; i <= 24; i++)
	{
		for (int j = 14; j >= 0; j--)
		{
			if (i - j < 14)
			{
				RecordBoard_zuo[zuo] = aRecordBoard[j][i - j];
				zuo++;
			}
			else if (i - j == 14)
			{
				RecordBoard_zuo[zuo] = aRecordBoard[j][i - j];
				zuo++;
				RecordBoard_zuo[zuo] = anti_color;
				zuo++;
				break;
			}
		}
	}

	for (int i = 0; i <= 240; i++)
	{
		if (RecordBoard_heng[i] == color)
		{
			if (i + 1 <= 240 && RecordBoard_heng[i + 1] == color)
			{
				if (i + 2 <= 240 && RecordBoard_heng[i + 2] == color)
				{
					if (i + 3 <= 240 && RecordBoard_heng[i + 3] == color)
					{
						if (i + 4 <= 240 && RecordBoard_heng[i + 4] == color)
						{
							eva.wu++;
							i += 4;
						}
						else if ((i + 4 <= 240 && RecordBoard_heng[i + 4] == 0) && (i - 1 >= 0 && RecordBoard_heng[i - 1] == 0))
						{
							eva.huo_si++;
							i += 4;
						}

						else if ((i + 4 <= 240 && RecordBoard_heng[i + 4] == 0) || (i - 1 >= 0 && RecordBoard_heng[i - 1] == 0))
						{
							eva.si_si++;
							i += 4;
						}
					}
					else if (i + 4 <= 240 && RecordBoard_heng[i + 3] == 0 && RecordBoard_heng[i + 4] == color)
					{
						eva.si_si++;
						i += 4;
					}
					else if ((i + 3 <= 240 && RecordBoard_heng[i + 3] == 0) && (i - 1 >= 0 && RecordBoard_heng[i - 1] == 0))
					{
						eva.huo_san++;
						i += 3;
					}

					else if ((i + 3 <= 240 && RecordBoard_heng[i + 3] == 0) || (i - 1 >= 0 && RecordBoard_heng[i - 1] == 0))
					{
						eva.si_san++;
						i += 3;
					}
				}
				else if (i + 4 <= 240 && RecordBoard_heng[i + 2] == color && RecordBoard_heng[i + 3] == 0 && RecordBoard_heng[i + 4] == color)
				{
					eva.si_si++;
					i += 4;
				}
				else if (i + 4 <= 240 && RecordBoard_heng[i + 2] == 0 && RecordBoard_heng[i + 3] == color && RecordBoard_heng[i + 4] == color)
				{
					eva.si_si++;
					i += 4;
				}
				else if ((i - 1 >= 0 && RecordBoard_heng[i - 1] == 0) && (i + 4 <= 240 && RecordBoard_heng[i + 4] == 0) && RecordBoard_heng[i + 2] == 0 && RecordBoard_heng[i + 3] == color)
				{
					eva.huo_san++;
					i += 3;
				}
				else if ((i + 2 <= 240 && RecordBoard_heng[i + 2] == 0) && (i - 1 >= 0 && RecordBoard_heng[i - 1] == 0))
				{
					eva.huo_er++;
					i += 2;
				}

				else if ((i + 2 <= 240 && RecordBoard_heng[i + 2] == 0) || (i - 1 >= 0 && RecordBoard_heng[i - 1] == 0))
				{
					eva.si_er++;
					i += 2;
				}
			}
			else if (i + 4 <= 240 && RecordBoard_heng[i + 1] == 0 && RecordBoard_heng[i + 2] == color && RecordBoard_heng[i + 3] == color && RecordBoard_heng[i + 4] == color)
			{
				eva.si_si++;
				i += 4;
			}

			else if ((i - 1 >= 0 && RecordBoard_heng[i - 1] == 0) && (i + 4 <= 240 && RecordBoard_heng[i + 4] == 0) && RecordBoard_heng[i + 1] == 0 && RecordBoard_heng[i + 2] == color && RecordBoard_heng[i + 3] == color)
			{
				eva.huo_san++;
				i += 3;
			}
			else if ((i - 1 >= 0 && RecordBoard_heng[i - 1] == 0) && (i + 3 <= 240 && RecordBoard_heng[i + 3] == 0) && RecordBoard_heng[i + 1] == 0 && RecordBoard_heng[i + 2] == color)
			{
				eva.huo_er++;
				i += 2;
			}
			else if ((i + 1 <= 240 && RecordBoard_heng[i + 1] == 0) || (i - 1 >= 0 && RecordBoard_heng[i - 1] == 0))
			{
				eva.yi++;
				i++;
			}
		}
		else
			;
	}

	for (int i = 0; i <= 240; i++)
	{
		if (RecordBoard_shu[i] == color)
		{
			if (i + 1 <= 240 && RecordBoard_shu[i + 1] == color)
			{
				if (i + 2 <= 240 && RecordBoard_shu[i + 2] == color)
				{
					if (i + 3 <= 240 && RecordBoard_shu[i + 3] == color)
					{
						if (i + 4 <= 240 && RecordBoard_shu[i + 4] == color)
						{
							eva.wu++;
							i += 4;
						}
						else if ((i + 4 <= 240 && RecordBoard_shu[i + 4] == 0) && (i - 1 >= 0 && RecordBoard_shu[i - 1] == 0))
						{
							eva.huo_si++;
							i += 4;
						}

						else if ((i + 4 <= 240 && RecordBoard_shu[i + 4] == 0) || (i - 1 >= 0 && RecordBoard_shu[i - 1] == 0))
						{
							eva.si_si++;
							i += 4;
						}
					}
					else if (i + 4 <= 240 && RecordBoard_shu[i + 1] == color && RecordBoard_shu[i + 2] == color && RecordBoard_shu[i + 3] == 0 && RecordBoard_shu[i + 4] == color)
					{
						eva.si_si++;
						i += 4;
					}
					else if ((i + 3 <= 240 && RecordBoard_shu[i + 3] == 0) && (i - 1 >= 0 && RecordBoard_shu[i - 1] == 0))
					{
						eva.huo_san++;
						i += 3;
					}

					else if ((i + 3 <= 240 && RecordBoard_shu[i + 3] == 0) || (i - 1 >= 0 && RecordBoard_shu[i - 1] == 0))
					{
						eva.si_san++;
						i += 3;
					}
				}
				else if (i + 4 <= 240 && RecordBoard_shu[i + 2] == color && RecordBoard_shu[i + 3] == 0 && RecordBoard_shu[i + 4] == color)
				{
					eva.si_si++;
					i += 4;
				}
				else if (i + 4 <= 240 && RecordBoard_shu[i + 2] == 0 && RecordBoard_shu[i + 3] == color && RecordBoard_shu[i + 4] == color)
				{
					eva.si_si++;
					i += 4;
				}
				else if ((i - 1 >= 0 && RecordBoard_shu[i - 1] == 0) && (i + 4 <= 240 && RecordBoard_shu[i + 4] == 0) && RecordBoard_shu[i + 2] == 0 && RecordBoard_shu[i + 3] == color)
				{
					eva.huo_san++;
					i += 3;
				}
				else if ((i + 2 <= 240 && RecordBoard_shu[i + 2] == 0) && (i - 1 >= 0 && RecordBoard_shu[i - 1] == 0))
				{
					eva.huo_er++;
					i += 2;
				}

				else if ((i + 2 <= 240 && RecordBoard_shu[i + 2] == 0) || (i - 1 >= 0 && RecordBoard_shu[i - 1] == 0))
				{
					eva.si_er++;
					i += 2;
				}
			}
			else if (i + 4 <= 240 && RecordBoard_shu[i + 1] == 0 && RecordBoard_shu[i + 2] == color && RecordBoard_shu[i + 3] == color && RecordBoard_shu[i + 4] == color)
			{
				eva.si_si++;
				i += 4;
			}

			else if ((i - 1 >= 0 && RecordBoard_shu[i - 1] == 0) && (i + 4 <= 240 && RecordBoard_shu[i + 4] == 0) && RecordBoard_shu[i + 1] == 0 && RecordBoard_shu[i + 2] == color && RecordBoard_shu[i + 3] == color)
			{
				eva.huo_san++;
				i += 3;
			}
			else if ((i - 1 >= 0 && RecordBoard_shu[i - 1] == 0) && (i + 3 <= 240 && RecordBoard_shu[i + 3] == 0) && RecordBoard_shu[i + 1] == 0 && RecordBoard_shu[i + 2] == color)
			{
				eva.huo_er++;
				i += 2;
			}
			else if ((i + 1 <= 240 && RecordBoard_shu[i + 1] == 0) || (i - 1 >= 0 && RecordBoard_shu[i - 1] == 0))
			{
				eva.yi++;
				i++;
			}
		}
		else
			;
	}

	for (int i = 0; i <= 226; i++)
	{
		if (RecordBoard_zuo[i] == color)
		{
			if (i + 1 <= 226 && RecordBoard_zuo[i + 1] == color)
			{
				if (i + 2 <= 226 && RecordBoard_zuo[i + 2] == color)
				{
					if (i + 3 <= 226 && RecordBoard_zuo[i + 3] == color)
					{
						if (i + 4 <= 226 && RecordBoard_zuo[i + 4] == color)
						{
							eva.wu++;
							i += 4;
						}
						else if ((i + 4 <= 226 && RecordBoard_zuo[i + 4] == 0) && (i - 1 >= 0 && RecordBoard_zuo[i - 1] == 0))
						{
							eva.huo_si++;
							i += 4;
						}

						else if ((i + 4 <= 226 && RecordBoard_zuo[i + 4] == 0) || (i - 1 >= 0 && RecordBoard_zuo[i - 1] == 0))
						{
							eva.si_si++;
							i += 4;
						}
					}
					else if (i + 4 <= 226 && RecordBoard_zuo[i + 1] == color && RecordBoard_zuo[i + 2] == color && RecordBoard_zuo[i + 3] == 0 && RecordBoard_zuo[i + 4] == color)
					{
						eva.si_si++;
						i += 4;
					}
					else if ((i + 3 <= 226 && RecordBoard_zuo[i + 3] == 0) && (i - 1 >= 0 && RecordBoard_zuo[i - 1] == 0))
					{
						eva.huo_san++;
						i += 3;
					}

					else if ((i + 3 <= 226 && RecordBoard_zuo[i + 3] == 0) || (i - 1 >= 0 && RecordBoard_zuo[i - 1] == 0))
					{
						eva.si_san++;
						i += 3;
					}
				}
				else if (i + 4 <= 226 && RecordBoard_zuo[i + 2] == color && RecordBoard_zuo[i + 3] == 0 && RecordBoard_zuo[i + 4] == color)
				{
					eva.si_si++;
					i += 4;
				}
				else if (i + 4 <= 226 && RecordBoard_zuo[i + 2] == 0 && RecordBoard_zuo[i + 3] == color && RecordBoard_zuo[i + 4] == color)
				{
					eva.si_si++;
					i += 4;
				}
				else if ((i - 1 >= 0 && RecordBoard_zuo[i - 1] == 0) && (i + 4 <= 226 && RecordBoard_zuo[i + 4] == 0) && RecordBoard_zuo[i + 2] == 0 && RecordBoard_zuo[i + 3] == color)
				{
					eva.huo_san++;
					i += 3;
				}
				else if ((i + 2 <= 226 && RecordBoard_zuo[i + 2] == 0) && (i - 1 >= 0 && RecordBoard_zuo[i - 1] == 0))
				{
					eva.huo_er++;
					i += 2;
				}

				else if ((i + 2 <= 226 && RecordBoard_zuo[i + 2] == 0) || (i - 1 >= 0 && RecordBoard_zuo[i - 1] == 0))
				{
					eva.si_er++;
					i += 2;
				}
			}
			else if (i + 4 <= 226 && RecordBoard_zuo[i + 1] == 0 && RecordBoard_zuo[i + 2] == color && RecordBoard_zuo[i + 3] == color && RecordBoard_zuo[i + 4] == color)
			{
				eva.si_si++;
				i += 4;
			}

			else if ((i - 1 >= 0 && RecordBoard_zuo[i - 1] == 0) && (i + 4 <= 226 && RecordBoard_zuo[i + 4] == 0) && RecordBoard_zuo[i + 1] == 0 && RecordBoard_zuo[i + 2] == color && RecordBoard_zuo[i + 3] == color)
			{
				eva.huo_san++;
				i += 3;
			}
			else if ((i - 1 >= 0 && RecordBoard_zuo[i - 1] == 0) && (i + 3 <= 226 && RecordBoard_zuo[i + 3] == 0) && RecordBoard_zuo[i + 1] == 0 && RecordBoard_zuo[i + 2] == color)
			{
				eva.huo_er++;
				i += 2;
			}
			else if ((i + 1 <= 226 && RecordBoard_zuo[i + 1] == 0) || (i - 1 >= 0 && RecordBoard_zuo[i - 1] == 0))
			{
				eva.yi++;
				i++;
			}
		}
		else
			;
	}

	for (int i = 0; i <= 226; i++)
	{
		if (RecordBoard_you[i] == color)
		{
			if (i + 1 <= 226 && RecordBoard_you[i + 1] == color)
			{
				if (i + 2 <= 226 && RecordBoard_you[i + 2] == color)
				{
					if (i + 3 <= 226 && RecordBoard_you[i + 3] == color)
					{
						if (i + 4 <= 226 && RecordBoard_you[i + 4] == color)
						{
							eva.wu++;
							i += 4;
						}
						else if ((i + 4 <= 226 && RecordBoard_you[i + 4] == 0) && (i - 1 >= 0 && RecordBoard_you[i - 1] == 0))
						{
							eva.huo_si++;
							i += 4;
						}

						else if ((i + 4 <= 226 && RecordBoard_you[i + 4] == 0) || (i - 1 >= 0 && RecordBoard_you[i - 1] == 0))
						{
							eva.si_si++;
							i += 4;
						}
					}
					else if (i + 4 <= 226 && RecordBoard_you[i + 1] == color && RecordBoard_you[i + 2] == color && RecordBoard_you[i + 3] == 0 && RecordBoard_you[i + 4] == color)
					{
						eva.si_si++;
						i += 4;
					}
					else if ((i + 3 <= 226 && RecordBoard_you[i + 3] == 0) && (i - 1 >= 0 && RecordBoard_you[i - 1] == 0))
					{
						eva.huo_san++;
						i += 3;
					}

					else if ((i + 3 <= 226 && RecordBoard_you[i + 3] == 0) || (i - 1 >= 0 && RecordBoard_you[i - 1] == 0))
					{
						eva.si_san++;
						i += 3;
					}
				}
				else if (i + 4 <= 226 && RecordBoard_you[i + 2] == color && RecordBoard_you[i + 3] == 0 && RecordBoard_you[i + 4] == color)
				{
					eva.si_si++;
					i += 4;
				}
				else if (i + 4 <= 226 && RecordBoard_you[i + 2] == 0 && RecordBoard_you[i + 3] == color && RecordBoard_you[i + 4] == color)
				{
					eva.si_si++;
					i += 4;
				}
				else if ((i - 1 >= 0 && RecordBoard_you[i - 1] == 0) && (i + 4 <= 226 && RecordBoard_you[i + 4] == 0) && RecordBoard_you[i + 2] == 0 && RecordBoard_you[i + 3] == color)
				{
					eva.huo_san++;
					i += 3;
				}
				else if ((i + 2 <= 226 && RecordBoard_you[i + 2] == 0) && (i - 1 >= 0 && RecordBoard_you[i - 1] == 0))
				{
					eva.huo_er++;
					i += 2;
				}

				else if ((i + 2 <= 226 && RecordBoard_you[i + 2] == 0) || (i - 1 >= 0 && RecordBoard_you[i - 1] == 0))
				{
					eva.si_er++;
					i += 2;
				}
			}
			else if (i + 4 <= 226 && RecordBoard_you[i + 1] == 0 && RecordBoard_you[i + 2] == color && RecordBoard_you[i + 3] == color && RecordBoard_you[i + 4] == color)
			{
				eva.si_si++;
				i += 4;
			}

			else if ((i - 1 >= 0 && RecordBoard_you[i - 1] == 0) && (i + 4 <= 226 && RecordBoard_you[i + 4] == 0) && RecordBoard_you[i + 1] == 0 && RecordBoard_you[i + 2] == color && RecordBoard_you[i + 3] == color)
			{
				eva.huo_san++;
				i += 3;
			}
			else if ((i - 1 >= 0 && RecordBoard_you[i - 1] == 0) && (i + 3 <= 226 && RecordBoard_you[i + 3] == 0) && RecordBoard_you[i + 1] == 0 && RecordBoard_you[i + 2] == color)
			{
				eva.huo_er++;
				i += 2;
			}
			else if ((i + 1 <= 226 && RecordBoard_you[i + 1] == 0) || (i - 1 >= 0 && RecordBoard_you[i - 1] == 0))
			{
				eva.yi++;
				i++;
			}
		}
		else
			;
	}

	outcomes.outcome = (eva.yi * yi_eva_anti) + (eva.si_er * si_er_eva_anti) + (eva.huo_er * huo_er_eva_anti) + (eva.si_san * si_san_eva_anti) + (eva.huo_san * huo_san_eva_anti) + (eva.si_si * si_si_eva_anti) + (eva.huo_si * huo_si_eva_anti) + (eva.wu * wu_eva_anti);
	outcomes.huo_san = eva.huo_san;
	outcomes.huo_si = eva.huo_si;
	outcomes.si_si = eva.si_si;
	outcomes.wu = eva.wu;
	return outcomes;
}

struct results outcomer(int color)
{
	struct results result = {0, 0};
	int anti_color = (color - 1) ? 1 : 2;
	struct eva_outcome outcome1 = evaluator(color);
	struct eva_outcome outcome2 = evaluator_anti(anti_color);
	result.result = outcome1.outcome - outcome2.outcome;
	if (outcome1.wu >= 1)
		result.kill = color;
	else if (outcome1.huo_si >= 1 && (outcome2.huo_si == 0 && outcome2.si_si == 0 && outcome2.wu == 0))
		result.kill = color;
	else if (outcome1.si_si >= 2 && (outcome2.huo_si == 0 && outcome2.si_si == 0 && outcome2.wu == 0))
		result.kill = color;
	else if (outcome1.huo_san >= 2 && (outcome2.huo_si == 0 && outcome2.si_si == 0 && outcome2.wu == 0 && outcome2.huo_san == 0))
		result.kill = color;

	if (outcome1.wu >= 1)
		result.kill = anti_color;
	else if (outcome1.huo_si >= 1 && (outcome1.huo_si == 0 && outcome1.si_si == 0 && outcome1.wu == 0))
		result.kill = anti_color;
	else if (outcome1.si_si >= 2 && (outcome1.huo_si == 0 && outcome1.si_si == 0 && outcome1.wu == 0))
		result.kill = anti_color;
	else if (outcome1.huo_san >= 2 && (outcome1.huo_si == 0 && outcome1.si_si == 0 && outcome1.wu == 0 && outcome1.huo_san == 0))
		result.kill = anti_color;

	return result;
}

/*void swap(i,j)
{
	struct point *temp;
	temp=index[i];
	index[i]=index[j];
	index[j]=temp;
}

void swap2(int b,int i,int j)
{
	int temp;
	temp=b;
	sortarray[i]=sortarray[j];
	sortarray[j]=temp;
}

void mysort(int a[])
{
	int i,j;
	for(i=0;i<=224;i++)
	{		
		for(j=0;j<=224;j++)
		{
			if(a[i]<a[j])
			{
				swap2(a[i],i,j);
				swap(i,j);
			}
		}
	}
}

void choose_advanced(struct point array[],struct point *index[])
{
    for (int i = 0; i <= 14; i++)
			{
				for (int j = 0; j <= 14; j++)
				{
					if (check(i, j) == 1)
					{
						calculate(i, j);
						calculate_defend(i, j);
                    }
                }
            }
			remove_exist();        
                        
                        
					int k=0;
                        
						for(int i=0;i<=224;i++)
							index[i]=&array[i];
                        for(int a=0;a<=14;a++)
                        {
                            for(int b=0;b<=14;b++)
                            {
                                array[k].x=a;
                                array[k].y=b;
                                sortarray[k]=importance[a][b];
                                k++;
                            }
                        }
	
}*/

int counter(void)
{
	int a = 0;
	for (int i = 0; i <= 14; i++)
	{
		for (int j = 0; j <= 14; j++)
		{
			if (aRecordBoard[i][j] != 0)
				a++;
		}
	}
	return a;
}

int AI_reduced(int player, int depth, int alpha, int beta)
{
	struct results val;

	if (depth != 0)
	{
		for (int i = 0; i <= 14; i++)
		{
			for (int j = 0; j <= 14; j++)
			{
				importance[i][j] = 0;
			}
		}
	}

	if (player == initialAIcolor)
	{
		val = outcomer(initialAIcolor);
		if (depth <= depth_max)
		{

			struct point array[225];
			struct point *index[225];
			AIcolor = player;
			playercolor = initialplayercolor;

			for (int i = 0; i <= 14; i++)
			{
				for (int j = 0; j <= 14; j++)
				{
					if (check(i, j) == 1)
					{
						calculate(i, j);
						calculate_defend(i, j);
					}
				}
			}
			remove_exist();

			int k = 0;

			for (int i = 0; i <= 224; i++)
				index[i] = &array[i];
			for (int a = 0; a <= 14; a++)
			{
				for (int b = 0; b <= 14; b++)
				{
					array[k].x = a;
					array[k].y = b;
					sortarray[k] = importance[a][b];
					k++;
				}
			}
			//mysort(sortarray);
			int i1, j1;
			for (i1 = 0; i1 <= 224; i1++)
			{
				for (j1 = 0; j1 <= 224; j1++)
				{
					if (sortarray[i1] > sortarray[j1])
					{
						struct point *temp;
						temp = index[i1];
						index[i1] = index[j1];
						index[j1] = temp;
						int temd;
						temd = sortarray[i1];
						sortarray[i1] = sortarray[j1];
						sortarray[j1] = temd;
					}
				}
			}

			int i;
			for (i = 0; i <= width; i++)
			{
				aRecordBoard[(*index[i]).x][(*index[i]).y] = initialAIcolor;
				val.result = AI_reduced(initialplayercolor, depth + 1, alpha, beta);
				aRecordBoard[(*index[i]).x][(*index[i]).y] = 0;
				if (val.kill == initialAIcolor)
				{
					alpha = 1000000;
					if (depth == 0)
					{
						choose[0] = (*index[i]).x;
						choose[1] = (*index[i]).y;
					}
					break;
				}
				if (val.result > alpha)
				{
					alpha = val.result;
					if (depth == 0)
					{
						choose[0] = (*index[i]).x;
						choose[1] = (*index[i]).y;
					}
				}
				if (alpha >= beta)
				{
					return alpha;
				}
			}
			return alpha;
		}
		return val.result;
	}

	else if (player == initialplayercolor)
	{
		val = outcomer(initialplayercolor);
		if (depth <= depth_max)
		{
			int i;
			struct point array[225];
			struct point *index[225];
			AIcolor = initialplayercolor;
			playercolor = initialAIcolor;

			for (int i = 0; i <= 14; i++)
			{
				for (int j = 0; j <= 14; j++)
				{
					if (check(i, j) == 1)
					{
						calculate(i, j);
						calculate_defend(i, j);
					}
				}
			}
			remove_exist();

			int k = 0;

			for (int i = 0; i <= 224; i++)
				index[i] = &array[i];
			for (int a = 0; a <= 14; a++)
			{
				for (int b = 0; b <= 14; b++)
				{
					array[k].x = a;
					array[k].y = b;
					sortarray[k] = importance[a][b];
					k++;
				}
			}
			// mysort(sortarray);
			int i1, j1;
			for (i1 = 0; i1 <= 224; i1++)
			{
				for (j1 = 0; j1 <= 224; j1++)
				{
					if (sortarray[i1] > sortarray[j1])
					{
						struct point *temp;
						temp = index[i1];
						index[i1] = index[j1];
						index[j1] = temp;
						int temd;
						temd = sortarray[i1];
						sortarray[i1] = sortarray[j1];
						sortarray[j1] = temd;
					}
				}
			}
			for (i = 0; i <= width; i++)
			{
				aRecordBoard[(*index[i]).x][(*index[i]).y] = initialplayercolor;
				val.result = -AI_reduced(initialAIcolor, depth + 1, alpha, beta);
				aRecordBoard[(*index[i]).x][(*index[i]).y] = 0;
				if (val.kill == initialplayercolor)
				{
					beta = -1000000;
					break;
				}

				if (-val.result < beta)
				{
					beta = -val.result;
				}
				if (alpha >= beta)
				{
					return beta;
				}
			}
			return beta;
		}
		return -val.result;
	}
}

void kaiju(void)
{
	if (aRecordBoard[6][6] == initialplayercolor || aRecordBoard[6][8] == initialplayercolor)
	{
		choose[0] = 8;
		choose[1] = 7;
	}
	else if (aRecordBoard[8][8] == initialplayercolor || aRecordBoard[8][6] == initialplayercolor)
	{
		choose[0] = 6;
		choose[1] = 7;
	}
	else if (aRecordBoard[6][7] == initialplayercolor || aRecordBoard[7][8] == initialplayercolor)
	{
		choose[0] = 6;
		choose[1] = 8;
	}
	else if (aRecordBoard[7][6] == initialplayercolor || aRecordBoard[8][7] == initialplayercolor)
	{
		choose[0] = 8;
		choose[1] = 6;
	}
	else
	{
		if (aRecordBoard[9][9] != initialplayercolor)
		{
			choose[0] = 8;
			choose[1] = 8;
		}
		else
		{
			choose[0] = 6;
			choose[1] = 6;
		}
	}
}

int AI(void)
{
	if (counter() <= 1)
	{
		width = 8;
		depth = 8;
	}
	else// if (counter() <= 8)
	{
		width = 30;
		depth_max = 5;
	}
	/*else if (counter() <= 12)
	{
		width = 13;
		depth_max = 7;
	}
	else if (counter() <= 24)
	{
		width = 20;
		depth_max = 6;
	}
	else
	{
		width = 30;
		depth_max = 5;
	}*/

	int i, j;
	for (i = 0; i <= 14; i++)
	{
		for (j = 0; j <= 14; j++)
		{
			importance[i][j] = 0;
		}
	}

	importance[7][7] += 1;

	int i1, j1;
	for (i1 = 0; i1 <= 14; i1++)
	{
		for (j1 = 0; j1 <= 14; j1++)
		{
			originalboard[i1][j1] = aRecordBoard[i1][j1];
		}
	}

	if (counter() != 2)
		AI_reduced(initialAIcolor, 0, -1000000, 1000000);
	else
		kaiju();

	int i2, j2;
	for (i2 = 0; i2 <= 14; i2++)
	{
		for (j2 = 0; j2 <= 14; j2++)
		{
			aRecordBoard[i2][j2] = originalboard[i2][j2];
		}
	}

	if (aRecordBoard[choose[0]][choose[1]] == 0)
	{
		aRecordBoard[choose[0]][choose[1]] = initialAIcolor;
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
