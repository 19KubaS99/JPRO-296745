#ifdef __linux__
    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    #include <unistd.h>

int steps;

void clear_data()
{
   FILE *data;

   if ((data=fopen("data.txt", "w"))==NULL) {
     printf ("Cannot open file data.txt!\n");
     exit(1);
     }
}

void data(int alive[steps], int dead[steps], int born[steps],int deceased[steps])
{
    FILE *data;

   if ((data=fopen("data.txt", "a+"))==NULL) {
     printf ("Cannot open file data.txt!\n");
     exit(1);
     }
     for(int s=0;s<steps;s++)
   fprintf (data, "alive:%d\tdead:%d\tborn:%d\tdeceased:%d\n", alive[s], dead[s], born[s], deceased[s]);
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
     printf ("Cannot open file config.txt!");
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
     printf ("Cannot open file config.txt!\n");
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
     printf ("Cannot open file config.txt!\n");
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
     printf ("Cannot open file config.txt!\n");
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
     printf ("Cannot open file config.txt!\n");
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

/*void delay(float seconds)
{
    int milli_seconds = 1000 * seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}
*/
int next_step(char board[31][61], int board2[31][61], int* born_ptr, int* deceased_ptr)
{
    int i,j,count=0,born=0,deceased=0;
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
            {
                board[i][j] = 'X';
                born++;

            }
            else if(board2[i][j] == 2)
                board[i][j] = board[i][j];
            else
            {
                if(board[i][j] == 'X') deceased++;
                board[i][j] = '.';

            }

        }
        *born_ptr = born;
        *deceased_ptr = deceased;
    }

    system("clear");
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
    int i,j,c,d,born_value,deceased_value;
    int *born_ptr, *deceased_ptr;
    born_ptr = malloc(sizeof(int));
    deceased_ptr = malloc(sizeof(int));

    float seconds;
    seconds = check_seconds();
    seconds = seconds * 1000000;
    steps = check_steps();
    int alive[steps];
    int dead[steps];
    int born[steps];
    int deceased[steps];
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
        printf("Error in random switch\n");

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
    printf("Press enter to start simulation\n");
    int pause = getchar();
    clear_data();
    for(int s=0;s<steps;s++)
    {
        usleep(seconds);
        next_step(board,board2, born_ptr,deceased_ptr);
        alive[s] = alive_number(board);
        dead[s] = 1800 - alive[s];
        born[s] = *born_ptr;
        deceased[s] = *deceased_ptr;
    }
    data(alive,dead,born, deceased);
}

#elif _WIN32
    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>

int steps;

void clear_data()
{
   FILE *data;

   if ((data=fopen("data.txt", "w"))==NULL) {
     printf ("Cannot open file data.txt!\n");
     exit(1);
     }
}

void data(int alive[steps], int dead[steps], int born[steps],int deceased[steps])
{
    FILE *data;

   if ((data=fopen("data.txt", "a+"))==NULL) {
     printf ("Cannot open file data.txt!\n");
     exit(1);
     }
     for(int s=0;s<steps;s++)
   fprintf (data, "alive:%d\tdead:%d\tborn:%d\tdeceased:%d\t\n", alive[s], dead[s], born[s], deceased[s]);
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
     printf ("Cannot open file config.txt!\n");
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
     printf ("Cannot open file config.txt!\n");
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
     printf ("Cannot open file config.txt!\n");
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
     printf ("Cannot open file config.txt!\n");
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
     printf ("Cannot open file config.txt!\n");
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

int next_step(char board[31][61], int board2[31][61], int* born_ptr, int* deceased_ptr)
{
    int i,j,count=0,born=0,deceased=0;
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
            {
                board[i][j] = 'X';
                born++;

            }
            else if(board2[i][j] == 2)
                board[i][j] = board[i][j];
            else
            {
                if(board[i][j] == 'X') deceased++;
                board[i][j] = '.';

            }

        }
        *born_ptr = born;
        *deceased_ptr = deceased;
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
    int i,j,c,d,born_value,deceased_value;
    int *born_ptr, *deceased_ptr;
    born_ptr = malloc(sizeof(int));
    deceased_ptr = malloc(sizeof(int));

    float seconds;
    seconds = check_seconds();
    steps = check_steps();
    int alive[steps];
    int dead[steps];
    int born[steps];
    int deceased[steps];
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
        printf("Error in random switch\n");

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
    printf("Press any button to start simulation\n");
    system("pause");
    clear_data();
    for(int s=0;s<steps;s++)
    {
        delay(seconds);
        next_step(board,board2, born_ptr,deceased_ptr);
        alive[s] = alive_number(board);
        dead[s] = 1800 - alive[s];
        born[s] = *born_ptr;
        deceased[s] = *deceased_ptr;
    }
    data(alive,dead,born, deceased);
}














#else

#endif
