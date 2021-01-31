#include<stdio.h>
#include<stdbool.h> 
#include<stdlib.h> 
#include<time.h> 
#include<conio.h>
#define p 100

bool over;
int height,width; //wall specifications;
int khanax,khanay,score,var,decide;
float det ;
char old,new;	//for validations
typedef struct tail   //for snake
{
	int tailx,taily,oldx,oldy;
	char initial;
}tail;
tail taail[30]={0}; 

void delay(float sec)               //for delay
{
	int millisec=1000*sec;
	clock_t start=clock();
	while (clock()<start + millisec);
}

void set()
{
	over=false;
	height=20;
	width=40;
	taail[0].tailx=width/2;
	taail[0].taily=height/2;
	srand(time(0));
	khanax=rand() / (RAND_MAX / (width  + 1) + 1);
	khanay=rand() / (RAND_MAX / (height  + 1) + 1);
	decide=0;
	score=0;
	det=0.1;
	var=0;
	taail[0].initial='a';
	new='a';
	//0 stop; 1 up; 2 down; 3 left; 4 right;
}

void press()
{

		switch(taail[0].initial)
			{
			case 'a':decide=3;
				break;
			case 's':decide=2;
				break;
			case 'd':decide=4;
				break;
			case 'w':decide=1;
				break;
			}
	old=new;
	if(kbhit())
	{
			switch(new=getch())
			{
			case 'a':
				if(old=='d')
					{
					decide=4;
					taail[0].initial='d';
					new='d';
					}
					else
					{
					decide=3;
					taail[0].initial='a';
					}	
					break;
			case 's':
					if(old=='w')
					{
					decide=1;
					taail[0].initial='w';
					new='w';
					}
					else
					{
					decide=2;
					taail[0].initial='s';
					}
			
					break;
			case 'd':if(old=='a')
					{
					decide=3;
					taail[0].initial='a';
					new='a';
					}
					else
					{
					decide=4;
					taail[0].initial='d';
					}
						
					break;
			case 'w':
					if(old=='s')
					{
					decide=2;
					taail[0].initial='s';
					new='s';
					}
					else
					{
					decide=1;
					taail[0].initial='w';
					}
					break;
			default:
					break;
			}
	}
}

void appsnake()
{
	int k;	
		
	for(k=var;k>=0;k--)
	{
		taail[k].oldx=taail[k].tailx;
		taail[k].oldy=taail[k].taily;
	}
	
	for(k=var;k>0;k--)
	{
		taail[k].tailx=taail[k-1].oldx;
		taail[k].taily=taail[k-1].oldy;
	
	}		
				for(k=var;k>1;k--)
				{
					if(taail[0].tailx==taail[k].oldx && taail[0].taily==taail[k].oldy)
					{
						over=true;
					}
	
				}		
			
}


void run()
{
	switch(decide)
	{
		case 1:taail[0].oldy=taail[0].taily;
		appsnake();
		taail[0].taily--;
			
		break;
		case 2:taail[0].oldy=taail[0].taily;
		appsnake();
		taail[0].taily++;
		
		break;
		case 3:taail[0].oldx=taail[0].tailx;
		appsnake();
		taail[0].tailx--;
		
		break;
		case 4:taail[0].oldx=taail[0].tailx;
		appsnake();
		taail[0].tailx++;
			
		break;
	}
	
			if(taail[0].taily>height-1 || taail[0].taily<0 || taail[0].tailx<0 || taail[0].tailx>=width-3)
				over=true;
			if(taail[0].tailx==khanax && taail[0].taily==khanay)
				{
					khanax=rand()%(width-2);
					khanay=rand()%(height-1);
					score=score+5;	
					var++;
					det-=(float)0.01;              //to increase speed after feeding
					appsnake();
				}
}


void wall()
{
	int x=0,y=0,z=0;
	int i,j,k;
	system("cls");
	for(i=0;i<width;i++)
	printf("#");
	printf("\n");
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++){
			 x=0;y=0;z=0;
			if(j==0 || j==(width-2))
			printf("#"); 
			if(i==taail[0].taily && j==taail[0].tailx)
			{	
				printf("S");
				x=1;
			}
			if(i==khanay && j==khanax )
			{
					printf("x");
					z=1;
			}
				
			if(var>0 && x==0 && z==0)
			{
				for(k=var;k>0;k--)
				{
				 if(i==taail[k].taily && j==taail[k].tailx)
					{	
						printf("o");
						y=1;
					}
					
				}
				if(y==0)
				printf(" ");
				
			}	
			if(var==0 && x==0 && y==0 && z==0)
			printf(" ");
		}
		printf("\n");
	}
	for(i=0;i<width;i++)
	printf("#");
	printf("\n");
	printf("\n-----------------------------------------\n");
	printf("|                  SCORE :%d            |\n",score);
	printf("-----------------------------------------\n");
}

int main()
{	int k=0;
	do
	{
		k=0;
		set();
	while(!over)
	{
		delay(det);
		wall();
		press();
		run();
	
	}
		system("cls");
		printf("\n------------------------------------------------------------\n");
		printf("|                  GAME    OVER                            |\n");
		
		printf("|                  YOUR    SCORE: %d                       |\n",score);
		printf("------------------------------------------------------------\n");
		printf("                   WANT TO CONTINUE THE GAME  ?             \n");
		printf("                   ENTER  1  TO  CONTINUE                   \n");
		scanf("%d",&k);
		
	}while(k==1);
}

