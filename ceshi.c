#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 15
#define CHARSIZE 2

#define wu_eva_anti 11000
#define huo_si_eva_anti 11000
#define si_si_eva_anti 11000
#define huo_san_eva_anti 1100
#define si_san_eva_anti 32
#define huo_er_eva_anti 32
#define si_er_eva_anti 8
#define yi_eva_anti 1

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
    struct evaluation color_eva;
    struct evaluation anti_color_eva;
};


void initRecordBorard(void);
void recordtoDisplayArray(void);
void displayBoard(void);


//����ʹ�õ���GBK���룬ÿһ�������ַ�ռ��2���ֽڡ�

//���̻���ģ�� 
char aInitDisplayBoardArray[SIZE][SIZE*CHARSIZE+1] = 
{
		"���өөөөөөөөөөөөө�",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"���۩۩۩۩۩۩۩۩۩۩۩۩۩�"
};
//������������ʾ���� 
char aDisplayBoardArray[SIZE][SIZE*CHARSIZE+1];
 
char play1Pic[]="��";//������;
char play1CurrentPic[]="��"; 

char play2Pic[]="��";//������;
char play2CurrentPic[]="��";

//���������ڼ�¼���̸��? 
int aRecordBoard[SIZE][SIZE];

//ben ren mo gai
int heifang(void);
int baifang(void);
int mode;
void doubleplayers(void);
void singleplayer(void);
int referee(void);

int main()

{
	initRecordBorard();
	printf("enter 1 to enable 2 players mode \n");
	scanf("%d",&mode);
	printf("\n");
	if(mode==1)
	{
		doubleplayers();	
	}
	else
	{
		singleplayer();
	}
}

//��ʼ�����̸��? 
void initRecordBorard(void){
	int i,j;	
	for(i=0;i<=15;i++)
	{
		for(j=0;j<=15;j++)
		{
			aRecordBoard[i][j]=0;
		}
	}
//ͨ��˫��ѭ������aRecordBoard��0
}

//��aRecordBoard�м�¼������λ�ã�ת����aDisplayBoardArray��
void recordtoDisplayArray(void){
//��һ������aInitDisplayBoardArray�м�¼�Ŀ����̣����Ƶ�aDisplayBoardArray��
	int i,j;	
	for(i=0;i<=14;i++)
	{
		for(j=0;j<=30;j++)
		{
			aDisplayBoardArray[i][j]=aInitDisplayBoardArray[i][j];
		}
	}
//�ڶ�����ɨ��aRecordBoard����������0��Ԫ�أ�������ߡ��Ƶ�aDisplayBoardArray����Ӧλ����
	for(i=0;i<=14;i++)
	{
		for(j=0;j<=14;j++)
		{
			if(aRecordBoard[i][j]==1)
			{								
				aDisplayBoardArray[i][2*j]=play1Pic[0];
				aDisplayBoardArray[i][2*j+1]=play1Pic[1];
			}
			else if(aRecordBoard[i][j]==2)
			{				
				aDisplayBoardArray[i][2*j]=play2Pic[0];
				aDisplayBoardArray[i][2*j+1]=play2Pic[1];
			}
		}
	}
//ע�⣺aDisplayBoardArray����¼���ַ��������ַ���ÿ���ַ�ռ2���ֽڡ���͡�Ҳ�������ַ���ÿ��Ҳ�?2���ֽڡ�
}


//��ʾ���̸��? 
void displayBoard(void){
	int i,j;
	//��һ��������
	system("clear");   //����  
	//�ڶ�������aDisplayBoardArray�������Ļ��?
	for(i=0;i<=14;i++)
	{
		if(i>=6) 
		printf(" %d",15-i);
		else
		printf("%d",15-i);
		printf("%s",aDisplayBoardArray[i]);
		
		printf("\n");
	}
		
	//������������������һ����ĸA B .... 
	printf ("  A B C D E F G H I J K L M N O\n");
} 

//luo zi
int heifang(void)
{
	int a;
	char b;
	scanf("%d,%c",&a,&b);
	printf("\n");
	if(aRecordBoard[15-a][b-'A']==0)
	{	
		aRecordBoard[15-a][b-'A']=1;
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
	scanf("%d,%c",&a,&b);
	printf("\n");
	if(aRecordBoard[15-a][b-'A']==0)
	{	
		aRecordBoard[15-a][b-'A']=2;
		return 1;
	}
	else
	{	
		printf("don't play tricks!\n");
		return 2;
	}
}

//mo shi
int Round=1;
void doubleplayers(void)
{
	if(Round==1)
	{
		Round=heifang();
		recordtoDisplayArray();
    		displayBoard();
   		//getchar();
	}
	else
	{
		Round=baifang();
		recordtoDisplayArray();
    		displayBoard();
	}
    int anti_color=2;
    int color=1;
    int outcome=0;
    struct evaluation eva={0,0,0,0,0,0,0,0};
    struct evaluation eva1={0,0,0,0,0,0,0,0};

	int RecordBoard_heng[240];
	int heng=0;
	for (int i=0;i<=14;i++)
	{
		for(int j=0;j<=15;j++)
		{
			if(j!=15)
			{
				RecordBoard_heng[heng]=aRecordBoard[i][j];
			}
			else
				RecordBoard_heng[heng]=anti_color;
			heng++;
		}
	}

	int RecordBoard_shu[240];
	int shu=0;
	for (int j=0;j<=14;j++)
	{
		for(int i=0;i<=15;i++)
		{
			if(i!=15)
			{
				RecordBoard_shu[shu]=aRecordBoard[i][j];
			}
			else
				RecordBoard_shu[shu]=anti_color;
			shu++;
		}
	}
	

    int RecordBoard_you[226];
	int you=0;
    for(int i=0;i<=10;i++)
    {
        for(int j=0;j<=14;j++)
        {
			if(j+i<14)
			{
				RecordBoard_you[you]=aRecordBoard[j][j+i];
				you++;
			}
			else if(j+i==14)
			{
				RecordBoard_you[you]=aRecordBoard[j][j+i];
				you++;
				RecordBoard_you[you]=anti_color;
				you++;
				break;
			}
        }
    }
	 for(int i=-10;i<=-1;i++)
    {
        for(int j=14;j>=0;j--)
        {
			if(j+i>0)
			{
				RecordBoard_you[you]=aRecordBoard[j][j+i];
				you++;
			}
			else if(j+i==0)
			{
				RecordBoard_you[you]=aRecordBoard[j][j+i];
				you++;
				RecordBoard_you[you]=anti_color;
				you++;
				break;
			}
        }
    }

	int RecordBoard_zuo[226];
	int zuo=0;
    for(int i=4;i<=14;i++)
    {
        for(int j=0;j<=14;j++)
        {
			if(i-j>0)
			{
				RecordBoard_zuo[zuo]=aRecordBoard[j][i-j];
				zuo++;
			}
			else if(i-j==0)
			{
				RecordBoard_zuo[zuo]=aRecordBoard[j][i-j];
				zuo++;
				RecordBoard_zuo[zuo]=anti_color;
				zuo++;
				break;
			}
        }
    }
	 for(int i=15;i<=24;i++)
    {
        for(int j=14;j>=0;j--)
        {
			if(i-j<14)
			{
				RecordBoard_zuo[zuo]=aRecordBoard[j][i-j];
				zuo++;
			}
			else if(i-j==14)
			{
				RecordBoard_zuo[zuo]=aRecordBoard[j][i-j];
				zuo++;
				RecordBoard_zuo[zuo]=anti_color;
				zuo++;
				break;
			}
        }
    }

for(int i=0;i<=240;i++)
    {
            if(RecordBoard_heng[i]==color )
            {
                if(i+1<=240 && RecordBoard_heng[i+1]==color )
                {
                    if(i+2<=240 && RecordBoard_heng[i+2]==color )
                    {
                        if(i+3<=240 && RecordBoard_heng[i+3]==color )
                        {
                            if(i+4<=240 && RecordBoard_heng[i+4]==color )
                            {
                            	eva.wu++;
                            	i+=4;
                            }
                            else if((i+4<=240 && RecordBoard_heng[i+4]==0) && (i-1>=0 && RecordBoard_heng[i-1]==0))
							{
								eva.huo_si++;
								i+=4;
							}                               
								
                            else if((i+4<=240 && RecordBoard_heng[i+4]==0) || (i-1>=0 && RecordBoard_heng[i-1]==0))
							{
								eva.si_si++;
                            	i+=4;
							}
                                
                        }
						else if(i+4<=240 && RecordBoard_heng[i+1]==color && RecordBoard_heng[i+2]==color && RecordBoard_heng[i+3]==0 && RecordBoard_heng[i+4]==color)
						{
							eva.si_si++;
							i+=4;
						}
                        else if((i+3<=240 && RecordBoard_heng[i+3]==0) && (i-1>=0 && RecordBoard_heng[i-1]==0))
						{
							eva.huo_san++;
							i+=3;
						}
                            
						else if((i+3<=240 && RecordBoard_heng[i+3]==0) || (i-1>=0 && RecordBoard_heng[i-1]==0))
						{
							eva.si_san++;
                        	i+=3;
						}
							
                    }
					else if(i+4<=240 && RecordBoard_heng[i+2]==color && RecordBoard_heng[i+3]==0 && RecordBoard_heng[i+4]==color)
					{
						eva.si_si++;
						i+=4;
					}
					else if(i+4<=240 && RecordBoard_heng[i+2]==0 && RecordBoard_heng[i+3]==color && RecordBoard_heng[i+4]==color)
					{
						eva.si_si++;
						i+=4;
					}
					else if((i-1>=0 && RecordBoard_heng[i-1]==0) && (i+4<=240 && RecordBoard_heng[i+4]==0) && RecordBoard_heng[i+2]==0 && RecordBoard_heng[i+3]==color)
					{
						eva.huo_san++;
						i+=3;
					}
                    else if((i+2<=240 && RecordBoard_heng[i+2]==0) && (i-1>=0 && RecordBoard_heng[i-1]==0))
					{
						eva.huo_er++;
						i+=2;
					}
                        
                    else if((i+2<=240 && RecordBoard_heng[i+2]==0) || (i-1>=0 && RecordBoard_heng[i-1]==0))
					{
						eva.si_er++;
                    	i+=2;
					}
                        
                }
				else if(i+4<=240 && RecordBoard_heng[i+1]==0 && RecordBoard_heng[i+2]==color && RecordBoard_heng[i+3]==color && RecordBoard_heng[i+4]==color)
				{
					eva.si_si++;
					i+=4;
				}
					 
				else if((i-1>=0 && RecordBoard_heng[i-1]==0) && (i+4<=240 && RecordBoard_heng[i+4]==0) && RecordBoard_heng[i+1]==0 && RecordBoard_heng[i+2]==color && RecordBoard_heng[i+3]==color)
				{
					eva.huo_san++;
					i+=3;
				}
				else if((i-1>=0 && RecordBoard_heng[i-1]==0) && (i+3<=240 && RecordBoard_heng[i+3]==0) && RecordBoard_heng[i+1]==0 && RecordBoard_heng[i+2]==color)
				{
					eva.huo_er++;
					i+=2;
				}
                else if((i+1<=240 && RecordBoard_heng[i+1]==0) || (i-1>=0 && RecordBoard_heng[i-1]==0))
				{
					eva.yi++;
					i++;
				}
            }
            else 
                ;
        }

	for(int i=0;i<=240;i++)
    {
            if(RecordBoard_shu[i]==color )
            {
                if(i+1<=240 && RecordBoard_shu[i+1]==color )
                {
                    if(i+2<=240 && RecordBoard_shu[i+2]==color )
                    {
                        if(i+3<=240 && RecordBoard_shu[i+3]==color )
                        {
                            if(i+4<=240 && RecordBoard_shu[i+4]==color )
                            {
                            	eva.wu++;
                            	i+=4;
                            }
                            else if((i+4<=240 && RecordBoard_shu[i+4]==0) && (i-1>=0 && RecordBoard_shu[i-1]==0))
							{
								eva.huo_si++;
								i+=4;
							}                               
								
                            else if((i+4<=240 && RecordBoard_shu[i+4]==0) || (i-1>=0 && RecordBoard_shu[i-1]==0))
							{
								eva.si_si++;
                            	i+=4;
							}
                                
                        }
						else if(i+4<=240 && RecordBoard_shu[i+1]==color && RecordBoard_shu[i+2]==color && RecordBoard_shu[i+3]==0 && RecordBoard_shu[i+4]==color)
						{
							eva.si_si++;
							i+=4;
						}
                        else if((i+3<=240 && RecordBoard_shu[i+3]==0) && (i-1>=0 && RecordBoard_shu[i-1]==0))
						{
							eva.huo_san++;
							i+=3;
						}
                            
						else if((i+3<=240 && RecordBoard_shu[i+3]==0) || (i-1>=0 && RecordBoard_shu[i-1]==0))
						{
							eva.si_san++;
                        	i+=3;
						}
							
                    }
					else if(i+4<=240 && RecordBoard_shu[i+2]==color && RecordBoard_shu[i+3]==0 && RecordBoard_shu[i+4]==color)
					{
						eva.si_si++;
						i+=4;
					}
					else if(i+4<=240 && RecordBoard_shu[i+2]==0 && RecordBoard_shu[i+3]==color && RecordBoard_shu[i+4]==color)
					{
						eva.si_si++;
						i+=4;
					}
					else if((i-1>=0 && RecordBoard_shu[i-1]==0) && (i+4<=240 && RecordBoard_shu[i+4]==0) && RecordBoard_shu[i+2]==0 && RecordBoard_shu[i+3]==color)
					{
						eva.huo_san++;
						i+=3;
					}
                    else if((i+2<=240 && RecordBoard_shu[i+2]==0) && (i-1>=0 && RecordBoard_shu[i-1]==0))
					{
						eva.huo_er++;
						i+=2;
					}
                        
                    else if((i+2<=240 && RecordBoard_shu[i+2]==0) || (i-1>=0 && RecordBoard_shu[i-1]==0))
					{
						eva.si_er++;
                    	i+=2;
					}
                        
                }
				else if(i+4<=240 && RecordBoard_shu[i+1]==0 && RecordBoard_shu[i+2]==color && RecordBoard_shu[i+3]==color && RecordBoard_shu[i+4]==color)
				{
					eva.si_si++;
					i+=4;
				}
					 
				else if((i-1>=0 && RecordBoard_shu[i-1]==0) && (i+4<=240 && RecordBoard_shu[i+4]==0) && RecordBoard_shu[i+1]==0 && RecordBoard_shu[i+2]==color && RecordBoard_shu[i+3]==color)
				{
					eva.huo_san++;
					i+=3;
				}
				else if((i-1>=0 && RecordBoard_shu[i-1]==0) && (i+3<=240 && RecordBoard_shu[i+3]==0) && RecordBoard_shu[i+1]==0 && RecordBoard_shu[i+2]==color)
				{
					eva.huo_er++;
					i+=2;
				}
                else if((i+1<=240 && RecordBoard_shu[i+1]==0) || (i-1>=0 && RecordBoard_shu[i-1]==0))
				{
					eva.yi++;
					i++;
				}
            }
            else 
                ;
        }
	
	for(int i=0;i<=226;i++)
    {
            if(RecordBoard_zuo[i]==color )
            {
                if(i+1<=226 && RecordBoard_zuo[i+1]==color )
                {
                    if(i+2<=226 && RecordBoard_zuo[i+2]==color )
                    {
                        if(i+3<=226 && RecordBoard_zuo[i+3]==color )
                        {
                            if(i+4<=226 && RecordBoard_zuo[i+4]==color )
                            {
                            	eva.wu++;
                            	i+=4;
                            }
                            else if((i+4<=226 && RecordBoard_zuo[i+4]==0) && (i-1>=0 && RecordBoard_zuo[i-1]==0))
							{
								eva.huo_si++;
								i+=4;
							}                               
								
                            else if((i+4<=226 && RecordBoard_zuo[i+4]==0) || (i-1>=0 && RecordBoard_zuo[i-1]==0))
							{
								eva.si_si++;
                            	i+=4;
							}
                                
                        }
						else if(i+4<=226 && RecordBoard_zuo[i+1]==color && RecordBoard_zuo[i+2]==color && RecordBoard_zuo[i+3]==0 && RecordBoard_zuo[i+4]==color)
						{
							eva.si_si++;
							i+=4;
						}
                        else if((i+3<=226 && RecordBoard_zuo[i+3]==0) && (i-1>=0 && RecordBoard_zuo[i-1]==0))
						{
							eva.huo_san++;
							i+=3;
						}
                            
						else if((i+3<=226 && RecordBoard_zuo[i+3]==0) || (i-1>=0 && RecordBoard_zuo[i-1]==0))
						{
							eva.si_san++;
                        	i+=3;
						}
							
                    }
					else if(i+4<=226 && RecordBoard_zuo[i+2]==color && RecordBoard_zuo[i+3]==0 && RecordBoard_zuo[i+4]==color)
					{
						eva.si_si++;
						i+=4;
					}
					else if(i+4<=226 && RecordBoard_zuo[i+2]==0 && RecordBoard_zuo[i+3]==color && RecordBoard_zuo[i+4]==color)
					{
						eva.si_si++;
						i+=4;
					}
					else if((i-1>=0 && RecordBoard_zuo[i-1]==0) && (i+4<=226 && RecordBoard_zuo[i+4]==0) && RecordBoard_zuo[i+2]==0 && RecordBoard_zuo[i+3]==color)
					{
						eva.huo_san++;
						i+=3;
					}
                    else if((i+2<=226 && RecordBoard_zuo[i+2]==0) && (i-1>=0 && RecordBoard_zuo[i-1]==0))
					{
						eva.huo_er++;
						i+=2;
					}
                        
                    else if((i+2<=226 && RecordBoard_zuo[i+2]==0) || (i-1>=0 && RecordBoard_zuo[i-1]==0))
					{
						eva.si_er++;
                    	i+=2;
					}
                        
                }
				else if(i+4<=226 && RecordBoard_zuo[i+1]==0 && RecordBoard_zuo[i+2]==color && RecordBoard_zuo[i+3]==color && RecordBoard_zuo[i+4]==color)
				{
					eva.si_si++;
					i+=4;
				}
					 
				else if((i-1>=0 && RecordBoard_zuo[i-1]==0) && (i+4<=226 && RecordBoard_zuo[i+4]==0) && RecordBoard_zuo[i+1]==0 && RecordBoard_zuo[i+2]==color && RecordBoard_zuo[i+3]==color)
				{
					eva.huo_san++;
					i+=3;
				}
				else if((i-1>=0 && RecordBoard_zuo[i-1]==0) && (i+3<=226 && RecordBoard_zuo[i+3]==0) && RecordBoard_zuo[i+1]==0 && RecordBoard_zuo[i+2]==color)
				{
					eva.huo_er++;
					i+=2;
				}
                else if((i+1<=226 && RecordBoard_zuo[i+1]==0) || (i-1>=0 && RecordBoard_zuo[i-1]==0))
				{
					eva.yi++;
					i++;
				}
            }
            else 
                ;
        }

	for(int i=0;i<=226;i++)
    {
            if(RecordBoard_you[i]==color )
            {
                if(i+1<=226 && RecordBoard_you[i+1]==color )
                {
                    if(i+2<=226 && RecordBoard_you[i+2]==color )
                    {
                        if(i+3<=226 && RecordBoard_you[i+3]==color )
                        {
                            if(i+4<=226 && RecordBoard_you[i+4]==color )
                            {
                            	eva.wu++;
                            	i+=4;
                            }
                            else if((i+4<=226 && RecordBoard_you[i+4]==0) && (i-1>=0 && RecordBoard_you[i-1]==0))
							{
								eva.huo_si++;
								i+=4;
							}                               
								
                            else if((i+4<=226 && RecordBoard_you[i+4]==0) || (i-1>=0 && RecordBoard_you[i-1]==0))
							{
								eva.si_si++;
                            	i+=4;
							}
                                
                        }
						else if(i+4<=226 && RecordBoard_you[i+1]==color && RecordBoard_you[i+2]==color && RecordBoard_you[i+3]==0 && RecordBoard_you[i+4]==color)
						{
							eva.si_si++;
							i+=4;
						}
                        else if((i+3<=226 && RecordBoard_you[i+3]==0) && (i-1>=0 && RecordBoard_you[i-1]==0))
						{
							eva.huo_san++;
							i+=3;
						}
                            
						else if((i+3<=226 && RecordBoard_you[i+3]==0) || (i-1>=0 && RecordBoard_you[i-1]==0))
						{
							eva.si_san++;
                        	i+=3;
						}
							
                    }
					else if(i+4<=226 && RecordBoard_you[i+2]==color && RecordBoard_you[i+3]==0 && RecordBoard_you[i+4]==color)
					{
						eva.si_si++;
						i+=4;
					}
					else if(i+4<=226 && RecordBoard_you[i+2]==0 && RecordBoard_you[i+3]==color && RecordBoard_you[i+4]==color)
					{
						eva.si_si++;
						i+=4;
					}
					else if((i-1>=0 && RecordBoard_you[i-1]==0) && (i+4<=226 && RecordBoard_you[i+4]==0) && RecordBoard_you[i+2]==0 && RecordBoard_you[i+3]==color)
					{
						eva.huo_san++;
						i+=3;
					}
                    else if((i+2<=226 && RecordBoard_you[i+2]==0) && (i-1>=0 && RecordBoard_you[i-1]==0))
					{
						eva.huo_er++;
						i+=2;
					}
                        
                    else if((i+2<=226 && RecordBoard_you[i+2]==0) || (i-1>=0 && RecordBoard_you[i-1]==0))
					{
						eva.si_er++;
                    	i+=2;
					}
                        
                }
				else if(i+4<=226 && RecordBoard_you[i+1]==0 && RecordBoard_you[i+2]==color && RecordBoard_you[i+3]==color && RecordBoard_you[i+4]==color)
				{
					eva.si_si++;
					i+=4;
				}
					 
				else if((i-1>=0 && RecordBoard_you[i-1]==0) && (i+4<=226 && RecordBoard_you[i+4]==0) && RecordBoard_you[i+1]==0 && RecordBoard_you[i+2]==color && RecordBoard_you[i+3]==color)
				{
					eva.huo_san++;
					i+=3;
				}
				else if((i-1>=0 && RecordBoard_you[i-1]==0) && (i+3<=226 && RecordBoard_you[i+3]==0) && RecordBoard_you[i+1]==0 && RecordBoard_you[i+2]==color)
				{
					eva.huo_er++;
					i+=2;
				}
                else if((i+1<=226 && RecordBoard_you[i+1]==0) || (i-1>=0 && RecordBoard_you[i-1]==0))
				{
					eva.yi++;
					i++;
				}
            }
            else 
                ;
        }
        eva1=eva;
        eva.huo_er=0;
        eva.si_er=0;
        eva.si_san=0;
        eva.si_si=0;
        eva.yi=0;
        eva.wu=0;
        eva.huo_si=0;
        eva.huo_san=0;
        color=2;
        anti_color=1;


	heng=0;
	for (int i=0;i<=14;i++)
	{
		for(int j=0;j<=15;j++)
		{
			if(j!=15)
			{
				RecordBoard_heng[heng]=aRecordBoard[i][j];
			}
			else
				RecordBoard_heng[heng]=anti_color;
			heng++;
		}
	}


	shu=0;
	for (int j=0;j<=14;j++)
	{
		for(int i=0;i<=15;i++)
		{
			if(i!=15)
			{
				RecordBoard_shu[shu]=aRecordBoard[i][j];
			}
			else
				RecordBoard_shu[shu]=anti_color;
			shu++;
		}
	}

    you=0;
    for(int i=0;i<=10;i++)
    {
        for(int j=0;j<=14;j++)
        {
			if(j+i<14)
			{
				RecordBoard_you[you]=aRecordBoard[j][j+i];
				you++;
			}
			else if(j+i==14)
			{
				RecordBoard_you[you]=aRecordBoard[j][j+i];
				you++;
				RecordBoard_you[you]=anti_color;
				you++;
				break;
			}
        }
    }
	 for(int i=-10;i<=-1;i++)
    {
        for(int j=14;j>=0;j--)
        {
			if(j+i>0)
			{
				RecordBoard_you[you]=aRecordBoard[j][j+i];
				you++;
			}
			else if(j+i==0)
			{
				RecordBoard_you[you]=aRecordBoard[j][j+i];
				you++;
				RecordBoard_you[you]=anti_color;
				you++;
				break;
			}
        }
    }

	zuo=0;
    for(int i=4;i<=14;i++)
    {
        for(int j=0;j<=14;j++)
        {
			if(i-j>0)
			{
				RecordBoard_zuo[zuo]=aRecordBoard[j][i-j];
				zuo++;
			}
			else if(i-j==0)
			{
				RecordBoard_zuo[zuo]=aRecordBoard[j][i-j];
				zuo++;
				RecordBoard_zuo[zuo]=anti_color;
				zuo++;
				break;
			}
        }
    }
	 for(int i=15;i<=24;i++)
    {
        for(int j=14;j>=0;j--)
        {
			if(i-j<14)
			{
				RecordBoard_zuo[zuo]=aRecordBoard[j][i-j];
				zuo++;
			}
			else if(i-j==14)
			{
				RecordBoard_zuo[zuo]=aRecordBoard[j][i-j];
				zuo++;
				RecordBoard_zuo[zuo]=anti_color;
				zuo++;
				break;
			}
        }
    }

for(int i=0;i<=240;i++)
    {
            if(RecordBoard_heng[i]==color )
            {
                if(i+1<=240 && RecordBoard_heng[i+1]==color )
                {
                    if(i+2<=240 && RecordBoard_heng[i+2]==color )
                    {
                        if(i+3<=240 && RecordBoard_heng[i+3]==color )
                        {
                            if(i+4<=240 && RecordBoard_heng[i+4]==color )
                            {
                            	eva.wu++;
                            	i+=4;
                            }
                            else if((i+4<=240 && RecordBoard_heng[i+4]==0) && (i-1>=0 && RecordBoard_heng[i-1]==0))
							{
								eva.huo_si++;
								i+=4;
							}                               
								
                            else if((i+4<=240 && RecordBoard_heng[i+4]==0) || (i-1>=0 && RecordBoard_heng[i-1]==0))
							{
								eva.si_si++;
                            	i+=4;
							}
                                
                        }
						else if(i+4<=240 && RecordBoard_heng[i+1]==color && RecordBoard_heng[i+2]==color && RecordBoard_heng[i+3]==0 && RecordBoard_heng[i+4]==color)
						{
							eva.si_si++;
							i+=4;
						}
                        else if((i+3<=240 && RecordBoard_heng[i+3]==0) && (i-1>=0 && RecordBoard_heng[i-1]==0))
						{
							eva.huo_san++;
							i+=3;
						}
                            
						else if((i+3<=240 && RecordBoard_heng[i+3]==0) || (i-1>=0 && RecordBoard_heng[i-1]==0))
						{
							eva.si_san++;
                        	i+=3;
						}
							
                    }
					else if(i+4<=240 && RecordBoard_heng[i+2]==color && RecordBoard_heng[i+3]==0 && RecordBoard_heng[i+4]==color)
					{
						eva.si_si++;
						i+=4;
					}
					else if(i+4<=240 && RecordBoard_heng[i+2]==0 && RecordBoard_heng[i+3]==color && RecordBoard_heng[i+4]==color)
					{
						eva.si_si++;
						i+=4;
					}
					else if((i-1>=0 && RecordBoard_heng[i-1]==0) && (i+4<=240 && RecordBoard_heng[i+4]==0) && RecordBoard_heng[i+2]==0 && RecordBoard_heng[i+3]==color)
					{
						eva.huo_san++;
						i+=3;
					}
                    else if((i+2<=240 && RecordBoard_heng[i+2]==0) && (i-1>=0 && RecordBoard_heng[i-1]==0))
					{
						eva.huo_er++;
						i+=2;
					}
                        
                    else if((i+2<=240 && RecordBoard_heng[i+2]==0) || (i-1>=0 && RecordBoard_heng[i-1]==0))
					{
						eva.si_er++;
                    	i+=2;
					}
                        
                }
				else if(i+4<=240 && RecordBoard_heng[i+1]==0 && RecordBoard_heng[i+2]==color && RecordBoard_heng[i+3]==color && RecordBoard_heng[i+4]==color)
				{
					eva.si_si++;
					i+=4;
				}
					 
				else if((i-1>=0 && RecordBoard_heng[i-1]==0) && (i+4<=240 && RecordBoard_heng[i+4]==0) && RecordBoard_heng[i+1]==0 && RecordBoard_heng[i+2]==color && RecordBoard_heng[i+3]==color)
				{
					eva.huo_san++;
					i+=3;
				}
				else if((i-1>=0 && RecordBoard_heng[i-1]==0) && (i+3<=240 && RecordBoard_heng[i+3]==0) && RecordBoard_heng[i+1]==0 && RecordBoard_heng[i+2]==color)
				{
					eva.huo_er++;
					i+=2;
				}
                else if((i+1<=240 && RecordBoard_heng[i+1]==0) || (i-1>=0 && RecordBoard_heng[i-1]==0))
				{
					eva.yi++;
					i++;
				}
            }
            else 
                ;
        }

	for(int i=0;i<=240;i++)
    {
            if(RecordBoard_shu[i]==color )
            {
                if(i+1<=240 && RecordBoard_shu[i+1]==color )
                {
                    if(i+2<=240 && RecordBoard_shu[i+2]==color )
                    {
                        if(i+3<=240 && RecordBoard_shu[i+3]==color )
                        {
                            if(i+4<=240 && RecordBoard_shu[i+4]==color )
                            {
                            	eva.wu++;
                            	i+=4;
                            }
                            else if((i+4<=240 && RecordBoard_shu[i+4]==0) && (i-1>=0 && RecordBoard_shu[i-1]==0))
							{
								eva.huo_si++;
								i+=4;
							}                               
								
                            else if((i+4<=240 && RecordBoard_shu[i+4]==0) || (i-1>=0 && RecordBoard_shu[i-1]==0))
							{
								eva.si_si++;
                            	i+=4;
							}
                                
                        }
						else if(i+4<=240 && RecordBoard_shu[i+1]==color && RecordBoard_shu[i+2]==color && RecordBoard_shu[i+3]==0 && RecordBoard_shu[i+4]==color)
						{
							eva.si_si++;
							i+=4;
						}
                        else if((i+3<=240 && RecordBoard_shu[i+3]==0) && (i-1>=0 && RecordBoard_shu[i-1]==0))
						{
							eva.huo_san++;
							i+=3;
						}
                            
						else if((i+3<=240 && RecordBoard_shu[i+3]==0) || (i-1>=0 && RecordBoard_shu[i-1]==0))
						{
							eva.si_san++;
                        	i+=3;
						}
							
                    }
					else if(i+4<=240 && RecordBoard_shu[i+2]==color && RecordBoard_shu[i+3]==0 && RecordBoard_shu[i+4]==color)
					{
						eva.si_si++;
						i+=4;
					}
					else if(i+4<=240 && RecordBoard_shu[i+2]==0 && RecordBoard_shu[i+3]==color && RecordBoard_shu[i+4]==color)
					{
						eva.si_si++;
						i+=4;
					}
					else if((i-1>=0 && RecordBoard_shu[i-1]==0) && (i+4<=240 && RecordBoard_shu[i+4]==0) && RecordBoard_shu[i+2]==0 && RecordBoard_shu[i+3]==color)
					{
						eva.huo_san++;
						i+=3;
					}
                    else if((i+2<=240 && RecordBoard_shu[i+2]==0) && (i-1>=0 && RecordBoard_shu[i-1]==0))
					{
						eva.huo_er++;
						i+=2;
					}
                        
                    else if((i+2<=240 && RecordBoard_shu[i+2]==0) || (i-1>=0 && RecordBoard_shu[i-1]==0))
					{
						eva.si_er++;
                    	i+=2;
					}
                        
                }
				else if(i+4<=240 && RecordBoard_shu[i+1]==0 && RecordBoard_shu[i+2]==color && RecordBoard_shu[i+3]==color && RecordBoard_shu[i+4]==color)
				{
					eva.si_si++;
					i+=4;
				}
					 
				else if((i-1>=0 && RecordBoard_shu[i-1]==0) && (i+4<=240 && RecordBoard_shu[i+4]==0) && RecordBoard_shu[i+1]==0 && RecordBoard_shu[i+2]==color && RecordBoard_shu[i+3]==color)
				{
					eva.huo_san++;
					i+=3;
				}
				else if((i-1>=0 && RecordBoard_shu[i-1]==0) && (i+3<=240 && RecordBoard_shu[i+3]==0) && RecordBoard_shu[i+1]==0 && RecordBoard_shu[i+2]==color)
				{
					eva.huo_er++;
					i+=2;
				}
                else if((i+1<=240 && RecordBoard_shu[i+1]==0) || (i-1>=0 && RecordBoard_shu[i-1]==0))
				{
					eva.yi++;
					i++;
				}
            }
            else 
                ;
        }
	
	for(int i=0;i<=226;i++)
    {
            if(RecordBoard_zuo[i]==color )
            {
                if(i+1<=226 && RecordBoard_zuo[i+1]==color )
                {
                    if(i+2<=226 && RecordBoard_zuo[i+2]==color )
                    {
                        if(i+3<=226 && RecordBoard_zuo[i+3]==color )
                        {
                            if(i+4<=226 && RecordBoard_zuo[i+4]==color )
                            {
                            	eva.wu++;
                            	i+=4;
                            }
                            else if((i+4<=226 && RecordBoard_zuo[i+4]==0) && (i-1>=0 && RecordBoard_zuo[i-1]==0))
							{
								eva.huo_si++;
								i+=4;
							}                               
								
                            else if((i+4<=226 && RecordBoard_zuo[i+4]==0) || (i-1>=0 && RecordBoard_zuo[i-1]==0))
							{
								eva.si_si++;
                            	i+=4;
							}
                                
                        }
						else if(i+4<=226 && RecordBoard_zuo[i+1]==color && RecordBoard_zuo[i+2]==color && RecordBoard_zuo[i+3]==0 && RecordBoard_zuo[i+4]==color)
						{
							eva.si_si++;
							i+=4;
						}
                        else if((i+3<=226 && RecordBoard_zuo[i+3]==0) && (i-1>=0 && RecordBoard_zuo[i-1]==0))
						{
							eva.huo_san++;
							i+=3;
						}
                            
						else if((i+3<=226 && RecordBoard_zuo[i+3]==0) || (i-1>=0 && RecordBoard_zuo[i-1]==0))
						{
							eva.si_san++;
                        	i+=3;
						}
							
                    }
					else if(i+4<=226 && RecordBoard_zuo[i+2]==color && RecordBoard_zuo[i+3]==0 && RecordBoard_zuo[i+4]==color)
					{
						eva.si_si++;
						i+=4;
					}
					else if(i+4<=226 && RecordBoard_zuo[i+2]==0 && RecordBoard_zuo[i+3]==color && RecordBoard_zuo[i+4]==color)
					{
						eva.si_si++;
						i+=4;
					}
					else if((i-1>=0 && RecordBoard_zuo[i-1]==0) && (i+4<=226 && RecordBoard_zuo[i+4]==0) && RecordBoard_zuo[i+2]==0 && RecordBoard_zuo[i+3]==color)
					{
						eva.huo_san++;
						i+=3;
					}
                    else if((i+2<=226 && RecordBoard_zuo[i+2]==0) && (i-1>=0 && RecordBoard_zuo[i-1]==0))
					{
						eva.huo_er++;
						i+=2;
					}
                        
                    else if((i+2<=226 && RecordBoard_zuo[i+2]==0) || (i-1>=0 && RecordBoard_zuo[i-1]==0))
					{
						eva.si_er++;
                    	i+=2;
					}
                        
                }
				else if(i+4<=226 && RecordBoard_zuo[i+1]==0 && RecordBoard_zuo[i+2]==color && RecordBoard_zuo[i+3]==color && RecordBoard_zuo[i+4]==color)
				{
					eva.si_si++;
					i+=4;
				}
					 
				else if((i-1>=0 && RecordBoard_zuo[i-1]==0) && (i+4<=226 && RecordBoard_zuo[i+4]==0) && RecordBoard_zuo[i+1]==0 && RecordBoard_zuo[i+2]==color && RecordBoard_zuo[i+3]==color)
				{
					eva.huo_san++;
					i+=3;
				}
				else if((i-1>=0 && RecordBoard_zuo[i-1]==0) && (i+3<=226 && RecordBoard_zuo[i+3]==0) && RecordBoard_zuo[i+1]==0 && RecordBoard_zuo[i+2]==color)
				{
					eva.huo_er++;
					i+=2;
				}
                else if((i+1<=226 && RecordBoard_zuo[i+1]==0) || (i-1>=0 && RecordBoard_zuo[i-1]==0))
				{
					eva.yi++;
					i++;
				}
            }
            else 
                ;
        }

	for(int i=0;i<=226;i++)
    {
            if(RecordBoard_you[i]==color )
            {
                if(i+1<=226 && RecordBoard_you[i+1]==color )
                {
                    if(i+2<=226 && RecordBoard_you[i+2]==color )
                    {
                        if(i+3<=226 && RecordBoard_you[i+3]==color )
                        {
                            if(i+4<=226 && RecordBoard_you[i+4]==color )
                            {
                            	eva.wu++;
                            	i+=4;
                            }
                            else if((i+4<=226 && RecordBoard_you[i+4]==0) && (i-1>=0 && RecordBoard_you[i-1]==0))
							{
								eva.huo_si++;
								i+=4;
							}                               
								
                            else if((i+4<=226 && RecordBoard_you[i+4]==0) || (i-1>=0 && RecordBoard_you[i-1]==0))
							{
								eva.si_si++;
                            	i+=4;
							}
                                
                        }
						else if(i+4<=226 && RecordBoard_you[i+1]==color && RecordBoard_you[i+2]==color && RecordBoard_you[i+3]==0 && RecordBoard_you[i+4]==color)
						{
							eva.si_si++;
							i+=4;
						}
                        else if((i+3<=226 && RecordBoard_you[i+3]==0) && (i-1>=0 && RecordBoard_you[i-1]==0))
						{
							eva.huo_san++;
							i+=3;
						}
                            
						else if((i+3<=226 && RecordBoard_you[i+3]==0) || (i-1>=0 && RecordBoard_you[i-1]==0))
						{
							eva.si_san++;
                        	i+=3;
						}
							
                    }
					else if(i+4<=226 && RecordBoard_you[i+2]==color && RecordBoard_you[i+3]==0 && RecordBoard_you[i+4]==color)
					{
						eva.si_si++;
						i+=4;
					}
					else if(i+4<=226 && RecordBoard_you[i+2]==0 && RecordBoard_you[i+3]==color && RecordBoard_you[i+4]==color)
					{
						eva.si_si++;
						i+=4;
					}
					else if((i-1>=0 && RecordBoard_you[i-1]==0) && (i+4<=226 && RecordBoard_you[i+4]==0) && RecordBoard_you[i+2]==0 && RecordBoard_you[i+3]==color)
					{
						eva.huo_san++;
						i+=3;
					}
                    else if((i+2<=226 && RecordBoard_you[i+2]==0) && (i-1>=0 && RecordBoard_you[i-1]==0))
					{
						eva.huo_er++;
						i+=2;
					}
                        
                    else if((i+2<=226 && RecordBoard_you[i+2]==0) || (i-1>=0 && RecordBoard_you[i-1]==0))
					{
						eva.si_er++;
                    	i+=2;
					}
                        
                }
				else if(i+4<=226 && RecordBoard_you[i+1]==0 && RecordBoard_you[i+2]==color && RecordBoard_you[i+3]==color && RecordBoard_you[i+4]==color)
				{
					eva.si_si++;
					i+=4;
				}
					 
				else if((i-1>=0 && RecordBoard_you[i-1]==0) && (i+4<=226 && RecordBoard_you[i+4]==0) && RecordBoard_you[i+1]==0 && RecordBoard_you[i+2]==color && RecordBoard_you[i+3]==color)
				{
					eva.huo_san++;
					i+=3;
				}
				else if((i-1>=0 && RecordBoard_you[i-1]==0) && (i+3<=226 && RecordBoard_you[i+3]==0) && RecordBoard_you[i+1]==0 && RecordBoard_you[i+2]==color)
				{
					eva.huo_er++;
					i+=2;
				}
                else if((i+1<=226 && RecordBoard_you[i+1]==0) || (i-1>=0 && RecordBoard_you[i-1]==0))
				{
					eva.yi++;
					i++;
				}
            }
            else 
                ;
        }

    outcome=(eva.yi*yi_eva_anti)+(eva.si_er*si_er_eva_anti)+(eva.huo_er*huo_er_eva_anti)+(eva.si_san*si_san_eva_anti)+(eva.huo_san*huo_san_eva_anti)+(eva.si_si*si_si_eva_anti)+(eva.huo_si*huo_si_eva_anti)+(eva.wu*wu_eva_anti);
	if(referee()==1)
	{
		printf("black win!");
	}
	else if(referee()==2)
	{
		printf("white win!");
	}
	else
	doubleplayers();
}

void singleplayer(void)
{
	printf("...");
}

int referee(void)
{
	int i,j;
	for(i=0;i<=10;i++)
	{
		for(j=0;j<=14;j++)
		{
			if(aRecordBoard[i][j]==1 && aRecordBoard[i+1][j]==1 && aRecordBoard[i+2][j]==1 && aRecordBoard[i+3][j]==1 && aRecordBoard[i+4][j]==1)
			{
				return 1;
			}
			else if(aRecordBoard[i][j]==2 && aRecordBoard[i+1][j]==2 && aRecordBoard[i+2][j]==2 && aRecordBoard[i+3][j]==2 && aRecordBoard[i+4][j]==2)
			{
				return 2;
			}
		}
	}
	for(i=0;i<=14;i++)
	{
		for(j=0;j<=10;j++)
		{
			if(aRecordBoard[i][j]==1 && aRecordBoard[i][j+1]==1 && aRecordBoard[i][j+2]==1 && aRecordBoard[i][j+3]==1 && aRecordBoard[i][j+4]==1)
			{
				return 1;
			}
			else if(aRecordBoard[i][j]==2 && aRecordBoard[i][j+1]==2 && aRecordBoard[i][j+2]==2 && aRecordBoard[i][j+3]==2 && aRecordBoard[i][j+4]==2)
			{
				return 2;
			}
		}
	}
	for(i=0;i<=10;i++)
	{
		for(j=0;j<=10;j++)
		{
			if(aRecordBoard[i][j]==1 && aRecordBoard[i+1][j+1]==1 && aRecordBoard[i+2][j+2]==1 && aRecordBoard[i+3][j+3]==1 && aRecordBoard[i+4][j+4]==1)
			{
				return 1;
			}
			else if(aRecordBoard[i][j]==2 && aRecordBoard[i+1][j+1]==2 && aRecordBoard[i+2][j+2]==2 && aRecordBoard[i+3][j+3]==2 && aRecordBoard[i+4][j+4]==2)
			{
				return 2;
			}
		}
	}
	for(i=4;i<=14;i++)
	{
		for(j=0;j<=10;j++)
		{
			if(aRecordBoard[i][j]==1 && aRecordBoard[i-1][j+1]==1 && aRecordBoard[i-2][j+2]==1 && aRecordBoard[i-3][j+3]==1 && aRecordBoard[i-4][j+4]==1)
			{
				return 1;
			}
			else if(aRecordBoard[i][j]==2 && aRecordBoard[i-1][j+1]==2 && aRecordBoard[i-2][j+2]==2 && aRecordBoard[i-3][j+3]==2 && aRecordBoard[i-4][j+4]==2)
			{
				return 2;
			}
		}
	}
	return 0;
}

