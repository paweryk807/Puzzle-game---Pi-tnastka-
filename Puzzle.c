#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<conio.h>
#include<assert.h>
#include<string.h>
#include<Windows.h>

#define bool int
#define true 1
#define false 0

// Alokowanie planszy do gry z randomowymi danymi.
int *makeBoard(int *board) 
{
    board = (int *)malloc(4 * 4 * sizeof(int));
    int i, j;
    int z = 0;

    /// Tworzenie tablicy, ktora sprawdza czy dana liczba juz wystepuje w tablicy planszy.
    bool tab[16];
    int value = 0;
    for(value; value < 16; value++)
    {
        tab[value]=false;
    }

	srand( time (NULL) );
        for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
            {
                while(true)
                    {
                        z = rand()%16;
                        if( !tab[z] )
                            {
                                tab[ z ] = true;
                                break;
                            }
                    }
            *(board + i*4 + j) = z;
            }
    return board; //   Zwracam adres
}

// Funkcja generujaca nowe ulozenie liczb w grze.
void randomize(int *board) 
{
     bool tab[16];
     int i,j,z;
     int value = 0;
     for(value; value < 16; value++)
     {
        tab[value]=false;
     }

	 srand( time (NULL) );
        for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
            {
                while(true)
                    {
                        z = rand()%16;
                        if( !tab[z] )
                            {
                                tab[ z ] = true;
                                break;
                            }
                    }
            *(board + i*4 + j) = z;
            }
}

// Funkcja tworzaca plansze na podstawie danych pobranych z pliku podanego przez uzytkownika.
void *boardFromFile(int *board,int tab[]) 
{
    int i, j;
    int x=0;
        for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
            {
                *(board + i*4 + j) = tab[x];
                x++;
            }
    return board; //  zwracam adres
}

// Funkcja drukujaca plansze na ekran konsoli.
void printBoard(int *board) 
{
    int i, j;
    system("@cls||clear");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
    printf("Aby zakonczyc wcisnij Esc \n");
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if(*(board + i * 4 + j)==0)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                printf("%*|%*d|", 1, 2, *(board + i * 4 + j));
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
            }
            else
                printf("%*|%*d|", 1, 2, *(board + i * 4 + j));
        }
        printf("\n");
    }
}

// Funkcja zajmujaca sie sterowaniem w grze,a takze wywolywaniem
// drukowania planszy na ekran, umozliwiajac poprawne 
// rozegranie partii Pietnastki.
// Podsumowujac - interfejs uzytkownika ;) 
void game( int *board)
{
    /// Poszukiwanie wartosci 0 na planszy <--------- To nim sterujemy
    int zC, zR;   //<--------- ZERO.column i ZERO.row
    int i, j;
    for( i = 0; i < 4 ; i++)
      {
          for ( j = 0; j < 4; j++)
            {
                if(   *(board + i*4 + j) == 0 )
                    {
                        zC = j;
                        zR = i;
                    }
            }
      }
    char num;
    int wartosc;
    bool end = false;
    while(true)
    {
        printBoard(board);
        num = getch();
        bool found = false;
        bool done = false;
              switch ( num )
              {
                case 72: // gora
                {
                    if(zR != 0 )
                    {
                    		found = true;
                    		i=zR-1;
                    		j=zC;
                    		if(i<=3 && i>=0)
                    		{
                    		wartosc = *(board + i*4 + j);
                    		*(board + i*4 + j) = 0;
                    		*(board + zR*4 + zC) = wartosc;
                    		zR=i;
                    		zC=j;
							}
                    }
                    break;
                }
                case 80: // dol
                {
                    if(zR != 3)
                       {
                    		found=true;
                    		i=zR+1;
                    		j=zC;
                    		if(i<=3 && i>=0)
                    		{
                    		wartosc = *(board + i*4 + j);
                    		*(board + i*4 + j) = 0;
                    		*(board + zR*4 + zC) = wartosc;
                    		zR=i;
                    		zC=j;
                    	}
                       }
                    break;
                }
                case (75): // lewo
                {
                    if(zC != 0)
                        {
                    		i=zR;
                    		j=zC-1;
                    		if(j<=3 && j>=0)
                    		{
                    		found=true;
                    		wartosc = *(board + i*4 + j);
                    		*(board + i*4 + j) = 0;
                    		*(board + zR*4 + zC) = wartosc;
                    		zR=i;
                    		zC=j;
                    		}
                        }
                    break;
                }
                case (77): // prawo
                {
                    if(zC != 3)
                    {
                    		i=zR;
                    		j=zC+1;
                    		if(j<=3 && j>=0)
                    		{
                    		found=true;
                    		wartosc = *(board + i*4 + j);
                    		*(board + i*4 + j) = 0;
                    		*(board + zR*4 + zC) = wartosc;
                    		zR=i;
                    		zC=j;
                    	}
                    }
                    break;
                }
                case (27) :
                    {
                        end = true;
                        break;
                    }

              }

       	int x = 1;
      	bool V = false;
      	bool breaker = false;
      	if( end ) break;
      	for( i = 0; i < 4 ; i++ )
      	{
          for ( j = 0; j < 4; j++ )
            {
            	if(*(board + i*4 + j) == x)
            	{
            		x++;
            		if(x==16)
            		{
            			V = true;
					}
				}
				else
				{
					breaker = true;
					break;
				}
            }
            if ( breaker ) break;
        }
        if ( V )
        {
        	printf( " Udalo sie! Gratulacje \n " );
        	break;
		}
    }

    }
    
// Funkcja sprawdzajaca poprawnosc danych wprowadzonych z pliku. 
// W przypadku blednych danych program zwraca wartosc 0, 
// gdy wszystko jest w porzadku zwraca 1 
// Uzywam wczesniej zdefiniowanego typu bool zeby wiedziec, ze funkcja sluzy jedynie jako warunek,
// ktory musi byc spelniony jesli wprowadzane sa dane z pliku. 
bool checkCorrectness(int tab[])
{
    int values[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    int correctnessTab[16] = {0};
    int i = 0;
    int z = 0;
    for(i; i < 16; i++)
    {
        while(tab[i] != values[z] && z < 16)
        {
            z++;
        }
        if(tab[i] == values[z])
        {
             correctnessTab[z] = 1;
        }
        z = 0;
    }
    int summary = 0;
    for(z; z < 16; z++)
    {
       summary = summary + correctnessTab[z];
    }
    if( summary == 16 ) return true;
    else return false;
}

int main(int argc, char** argv)
{
    int *board = NULL;
            board = makeBoard(board);
    int  tab[16];
    bool wannaMore = 1;
		if (argc != 2)
		{
		    printf("Podano zle argumenty, mapa zostanie wygenerowana losowo\n");
            game(board);
		}
		else
        {
            FILE * fr = fopen(argv[1], "rt");
            if( fr == NULL )
            {
                printf("Pliku nie znaleziono, mapa zostanie wygenerowana losowo\n");
                game(board);
            }
            else
            {
            	bool b=false;
	            while(!feof(fr) && !b)
	            {
	            	int i = 0;
	                for(i; i < 16; i++)
	                {
	                	tab[i] = -1; // Jesli wprowadzimy w tym miejscu do tablicy wartosc -1 chroni nasz program przed blednymi danymi (zlego typu).
	                    fscanf( fr, "%i", &tab[i] );
	                }
	                if( checkCorrectness(tab) == 1 )
                    {
                        boardFromFile(board,tab);
                    }
	            	else
                    {
                        printf(" Dane z pliku nie spelnialy kryteriow, plansza zostala wygenerowana losowo ");
                        b=true;
                        makeBoard(board);
                    }
	            	game(board);
	            }
	            fclose(fr);
        	}
		}
		
    while(wannaMore==1)
    {
        printf("Chcesz grac dalej?  0 - nie, 1 - tak \n"); // Wprowadzenie kazdej innej wartosci nie spowoduje bledu, lecz po prostu zakonczy dzialanie programu. 
        scanf("%i",&wannaMore);
        if(wannaMore==1)
        {
        	randomize(board);
            game(board);
        }
    }
    free(board);
    board=NULL;

   return 0;
}



