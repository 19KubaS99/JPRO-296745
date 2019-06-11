#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void clear_data()
{
   FILE *data;

   if ((data=fopen("data.txt", "w"))==NULL) {
     printf ("Nie mogê otworzyæ pliku test.txt do zapisu!\n");
     exit(1);
     }
}

void data(int alive, int dead)
{
    FILE *data;

   if ((data=fopen("data.txt", "a+"))==NULL) {
     printf ("Nie mogê otworzyæ pliku test.txt do zapisu!\n");
     exit(1);
     }
   fprintf (data, "alive:%d     dead:%d\n", alive, dead);
   fclose (data);

}

int alive_number(char board[31][61])
{
    int i,j,alive=0;
    for(i=1;i<30;i++)
    {
        for(j=1;j<60;j++)
        {
            if(board[i][j]=='X')
                alive++;
        }
    }
    return alive;
}


float check_seconds()
{
    float seconds;
    FILE *fp;
   if ((fp=fopen("config.txt", "r"))==NULL) {
     printf ("Nie moge otworzyc pliku config.txt!\n");
     exit(1);
     }
    fseek(fp, 75, 0);
    fscanf(fp,"%f", &seconds);
    fclose (fp);
    return seconds;
}

int check_steps()
{
    int steps;
    FILE *fp;
   if ((fp=fopen("config.txt", "r"))==NULL) {
     printf ("Nie moge otworzyc pliku config.txt!\n");
     exit(1);
     }
    fseek(fp, 60, 0);
    fscanf(fp,"%d", &steps);
    fclose (fp);
    return steps;
}

int check_compaction()
{
    int compaction;
    FILE *fp;
   if ((fp=fopen("config.txt", "r"))==NULL) {
     printf ("Nie moge otworzyc pliku config.txt!\n");
     exit(1);
     }
    fseek(fp, 41, 0);
    fscanf(fp,"%d", &compaction);
    fclose (fp);
    return compaction;
}

int check_random()
{
    int i;
    FILE *fp;
   if ((fp=fopen("config.txt", "r"))==NULL) {
     printf ("Nie moge otworzyc pliku config.txt do zapisu!\n");
     exit(1);
     }
    char tab[13];
    for(i=0;i<13;i++)
    {
        fscanf(fp,"%c", &tab[i]);
    }
    if(tab[12] == 'y')
        return 1;
    else if(tab[12] == 'n')
        return 0;
    else
        return 3;
    fclose (fp);
}

void cells(char board[16][16])
{
    board[1+8][1+8] = 'X';
    board[1+8][2+8] = 'X';
    board[1+8][3+8] = 'X';
    board[2+8][1+8] = 'X';
    board[3+8][2+8] = 'X';

}

void config(char board[31][61])
{
    char k = '1';
    int i,j;
    FILE *fp;
   if ((fp=fopen("config.txt", "r"))==NULL) {
     printf ("Nie moge otworzyc pliku config.txt do zapisu!\n");
     exit(1);
     }

for(i=1;i<30;i++)
{
    for(j=1;j<60;j++)
    {
        if(k!=EOF){
            do
            {
                fscanf(fp, "%c", &k);
            }
            while (k!='.' && k!='X' && k!=EOF);
        }
        board[i][j]=k;
    }

}
fclose (fp);
}
void out()
{

}

void random_cells(char board[31][61])
{
int p,z,x,y;
p = check_compaction() * 100;
printf("%d", p);
srand( time( NULL ) );
for(z=0;z<p;z++)
{
    x = rand()%29+1;
    y = rand()%59+1;
    board[x][y] = 'X';
}
}

void delay(float seconds)
{
    int milli_seconds = 1000 * seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}

void next_step(char board[31][61], int board2[31][61])
{
    int i,j,count=0;
    for(i=1;i<30;i++)
    {
        for(j=1;j<60;j++)
        {
            if(board[i-1][j-1] == 'X')
                count++;
            if(board[i-1][j] == 'X')
                count++;
            if(board[i-1][j+1] == 'X')
                count++;
            if(board[i][j-1] == 'X')
                count++;
            if(board[i][j+1] == 'X')
                count++;
            if(board[i+1][j-1] == 'X')
                count++;
            if(board[i+1][j] == 'X')
                count++;
            if(board[i+1][j+1] == 'X')
                count++;
            board2[i][j] = count;
            count = 0;

        }
    }
    for(i=0;i<31;i++)
    {
        for(j=0;j<61;j++)
        {
            if(board2[i][j] == 3)
                board[i][j] = 'X';
            else if(board2[i][j] == 2)
                board[i][j] = board[i][j];
            else
                board[i][j] = '.';
        }
    }

    system("cls");
    for(i=1;i<30;i++)
    {
        for(j=1;j<60;j++)
        {
            printf("%c",board[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int i,j,c,d,steps,alive,dead;
    float seconds;
    seconds = check_seconds();
    steps = check_steps();
    char board[31][61];
    int board2[31][61];
    for(i=0;i<31;i++)
    {
        for(j=0;j<61;j++)
        {
            board[i][j] = '.';
        }
    }
if (check_random()==1)
    random_cells(board);
else if(check_random()==0)
    config(board);
else
    printf("Blad w przelaczniku random\n");

for(c = 1; c<30;c++){
        for(d=1;d<60;d++){
            printf("%c", board[c][d]);
        }
        printf("\n");
    }
for(i=0;i<31;i++)
{
    for(j=0;j<61;j++)
    {
        board2[i][j] = 0;
    }
}
printf("Wcisnij dowolny klawisz by rozpoczac animacje\n");
system("pause");
clear_data();
for(int s=0;s<steps;s++)
{
    delay(seconds);
    next_step(board,board2);
   alive = alive_number(board);
   dead = 1800 - alive;
   int temp_alive = alive;
   int temp_dead = dead;
   data(alive,dead);
}
}


















