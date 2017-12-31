#include<stdio.h>
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

int main()
{
    int anti_color=2;
    int color=1;
    int aRecordBoard[15][15];
    for(int i=0;i<=14;i++)
    {
        for(int j=0;j<=14;j++)
        {
            aRecordBoard[i][j]=0;
        }
    }
    aRecordBoard[10][11]=1;
    aRecordBoard[9][12]=1;
    aRecordBoard[8][13]=1;
	aRecordBoard[7][14]=1;

	int outcome=0;
    struct evaluation eva={0,0,0,0,0,0,0,0};

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

    return outcome=(eva.yi*yi_eva_anti)+(eva.si_er*si_er_eva_anti)+(eva.huo_er*huo_er_eva_anti)+(eva.si_san*si_san_eva_anti)+(eva.huo_san*huo_san_eva_anti)+(eva.si_si*si_si_eva_anti)+(eva.huo_si*huo_si_eva_anti)+(eva.wu*wu_eva_anti);
}