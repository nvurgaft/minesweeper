#include <stdlib.h>
#include <time.h>
#include <windows.h>

//defining global STACK
int stack[3];
int top=-1;
int score=0;                             //For Score Calculation

void welcome();
void pop();
void push();
void pr_minesweeper();
void gotoxy(int x,int y);
void rand_mines(char msweep[12][12]);
void delay();
void printmatrix(char msweep[12][12],int r,char user_chart[12][12],int* ptr);
int process(char msweep[12][12],int r,int c,char user_chart[12][12]);

int main()
{
    system("COLOR 47");
    int q;
    int* ptr=NULL;
    q=45;
    ptr=&q;
                                                                           //size of array is 10,array starts from 1 to 11
    char msweep[12][12] = {{'0'}};
    int i,r,c;
    char user_chart[12][12] = {{'0'}};
    pr_minesweeper();
    welcome();
    for(i=0;i<3;i++)
    {
        push(0);
    }

    rand_mines(msweep);
    *ptr=45;
    printmatrix(msweep,12,user_chart,ptr);                                 // note grid from 1 to 11

    printf("\nEnter your location(ONLY 1 - 11) on the minefield x,y\n");
    *ptr=*ptr+2;
    scanf("%d %d",&r,&c);

    printmatrix(msweep,12,user_chart,ptr);

    i = process(msweep,r,c,user_chart); //returns 1 or 0,1 is notmine 0 = mine

    int count=0;
    U:
    while(i == 1)
    {
        printf("\nLucky BRAT, live on for another step\n");
        printf(" %c Surrounding MINEs\n\n",msweep[r][c]);
        *ptr=*ptr+4;

        printmatrix(msweep,12,user_chart,ptr);
        printf("\nEnter next move...(ONLY 1 - 11) ");
        scanf("%d%d",&r,&c);
        i=0;
        gotoxy(50,*ptr);
        i = process(msweep,r,c,user_chart);
    }

    if(i==0)
    {
        printf("\nGame OVER, ta ta. you stepped on a MINE !!\n");
        if(top!=-1)
        {
            printf("Wanna Undo one step!!!!!! press 'u' for undo.....!!!!\n");
            //Detect Click And Goto statement;
            if(getch()=='u')
            {
                pop();
                printf("Undo Remaining=%d\n",top+1);
                i=1;
                goto U;
            }
            else
            {
                goto End;
            }
        }
        else
        {
            End:
            printf("No More Undos remaining......!!!!! Game Over..!!!!");
            printf("\n\n\n\n                                                                 Total SCORE=%d\n\n",score);
        }
    }
    return 0;

}

void welcome(int* ptr)
{
    int i;
    char op; // opereation

    printf("Welcome to MINESWEEPER in C >>........\n\n");
    printf("Enter <<\n");
    printf("         i for instructions\n");
    printf("         any other key to enter game\n");
    scanf("%c",&op);

    if(op == 'i')
    {
        printf("OH DEAR, what a shock you are unfortunatly in the midst of a "); printf("mine field.\n");;
        printf("Enter the coordinates of the x and y plane between 1 to 11\n");
        printf("Are you destined to DIE or live ?\n");
        printf("HA ha ha hah, GOOD LUCK\n\n");

    }
    else
        return;
}

void rand_mines(char msweep[12][12])
{
    int r,c,m;

    srand(time(0));

    for(m=0;m<20;m++) // plant 20 rand mines(m

    {
        r = rand() % 13; // this is mine planting
                    // so can be at the edges aswell
        c = rand() % 13; // so 0 to 13 is APPROPRIATE.
        msweep[r][c] = '9';
        printf("%d %d \n",r,c);

    }

    return;

}

void printmatrix(char msweep[][12],int r,char user_chart[12][12],int* ptr)
{
    int i,j,t,k,p;
    gotoxy(65,*ptr);
    for(t=0;t<12;t++)
    {
        delay();
        printf("%c%c",178,177);
    }

    *ptr=(*ptr+1);                                        //For Center Printing

    for(i=1;i<r;i++)
    {
        gotoxy(65,*ptr);
        printf("%c",178);

        for(j=1;j<12;j++)                                 //printing 1 to 11
        {
            printf("%c ",user_chart[i][j]);//to refer to mines use msweep[i][j]
        }
        delay();
        printf("%c",178);
        *ptr=*ptr+1;
    }
    gotoxy(65,*ptr);
    for(t=0;t<12;t++)
    {
        delay();
        printf("%c%c",178,177);
    }

    *ptr=*ptr+1;

    return;
}

int process(char msweep[12][12],int r,int c,char user_chart[12][12])
{
    int i=r,j=c,b=0,k;
    char C;

    if(msweep[r][c] == '9')
    {
        k=0;
        return k;
    }
    else
    {
        if(msweep[i-1][j-1] == '9')
        b++;
        if(msweep[i-1][j] == '9')
        b++;
        if(msweep[i-1][j+1] == '9')
        b++;
        if(msweep[i][j-1] == '9')
        b++;
        if(msweep[i][j+1] == '9')
        b++;
        if(msweep[i+1][j-1] == '9')
        b++;
        if(msweep[i+1][j] == '9')
        b++;
        if(msweep[i+1][j+1] == '9')
        b++;

        C = (char)(((int)'0')+b); // to covert int to char;
        score=score+b;
        msweep[r][c] = C;
        user_chart[r][c] = C;
  }

    return 1;

}
void delay()
{
    int i,j;
    for(i=0;i<1000;i++)
    {
        for(j=0;j<10000;j++)
        {

        }
    }
    return;
}
void pr_minesweeper()
{
        gotoxy(50,10);

        //first line

        printf("| \\  / |  ");delay();printf("|_  _|  ");delay();printf("| \\| |  ");delay();printf("|==  ");delay();
        printf("/ /  ");delay();printf("\\ \\    / /  ");delay();printf("|==  ");delay();printf("|==  ");delay();
        printf("| |_)  ");delay();printf("|==  ");delay();printf("| | )  \n");delay();
        gotoxy(50,11);

        //second line

        printf("| |\\/| |  ");delay();printf("  | |   ");delay();printf("| |\\ |  ");delay();printf("|=   ");delay();
        printf("\\ \\  ");delay();printf(" \\ \\/\\/ /   ");delay();printf("|=   ");delay();
        printf("|=   ");delay();printf("| |    ");delay();printf("|=   ");delay();printf("| |\\   \n");delay();
        gotoxy(50,12);

        //third line

        printf("|_|  |_|  ");delay();printf("|____|  ");delay();printf("|_| \\_| ");delay();printf("|==  ");delay();
        printf("/_/  ");delay();printf("  \\_/\\_/    ");delay();printf("|==  ");delay();printf("|==  ");delay();
        printf("|_|    ");delay();printf("|==  ");delay();printf("|_| \\   \n");delay();

        return;
}
void gotoxy(int x,int y)
{
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
void pop()
{
    top--;
    return;
}
void push(int x)
{
    top++;
    stack[top]=x;
    return;
}
