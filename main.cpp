#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>

using namespace std;

// movement function
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// slow down anim
void slow()
{
    float a = 1;
    do
    {
        a = a + 0.1;
    } while (a < 1000000);
}

// arena
void arena()
{
    for (int i = 1; i < 69; i++)
    {
        for (int j = 3; j < 23; j++)
        {
            gotoxy(i, j);
            cout << " ";
        }
    }
}

// arena boundary
void bounds()
{
    gotoxy(0, 0);
    printf("%c", 218);
    gotoxy(0, 24);
    printf("%c", 192);
    gotoxy(21, 1);
    printf("ASDW : bergerak, ESC : keluar");
    gotoxy(11, 1);
    printf("%c", 179);
    gotoxy(62, 1);
    printf("%c", 179);

    for (int x = 1; x < 70; x++)
    {
        gotoxy(x, 0);
        printf("%c", 196);
        gotoxy(x, 2);
        printf("%c", 196);
        gotoxy(x, 24);
        printf("%c", 196);
    }

    gotoxy(11, 0);
    printf("%c", 194);
    gotoxy(62, 0);
    printf("%c", 194);
    gotoxy(70, 0);
    printf("%c", 191);
    gotoxy(11, 2);
    printf("%c", 193);
    gotoxy(62, 2);
    printf("%c", 193);
    gotoxy(70, 24);
    printf("%c", 217);

    for (int y = 1; y < 24; y++)
    {
        gotoxy(0, y);
        printf("%c", 179);
        gotoxy(70, y);
        printf("%c", 179);
    }

    gotoxy(0, 2);
    printf("%c", 195);
    gotoxy(70, 2);
    printf("%c", 180);
}

int xAcak()
{
    int x = rand();
    if (x < 1)
    {
        return (x % 69) + 1;
    }
    else
    {
        return (x % 69);
    }
}

int yAcak()
{
    int y = rand();
    if ((y % 23) < 4)
    {
        return (y % 23) + 4;
    }
    else
    {
        return (y % 23);
    }
}

// Scoring
struct node
{
    int value;
    struct node *next;
};

struct node *head = NULL;
struct node *tail = NULL;
int xScore;
int score = 0;

bool isEmpty()
{
    return head == NULL;
}

void insScore(int data)
{
    if (isEmpty())
    {
        node *temp = new node();
        temp->value = data;
        temp->next = NULL;

        head = tail = temp;
    }
    else
    {
        node *temp = new node();
        temp->value = data;
        temp->next = NULL;

        tail->next = temp;
        tail = temp;
    }
}

void delScore(int data)
{
    if (isEmpty()) // Pengecekan Isi Data
    {
    }
    else
    {
        node *key = head;
        node *prev = NULL;

        while (key != NULL)
        {
            if (key->value == data)
            {
                if (key->next == NULL)
                {
                    prev->next = NULL;
                    tail = prev;
                    free(key);
                }
            }
            prev = key;
            key = key->next;
        }
    }
}

void dispScore()
{
    node *key = head;

    int xScore = 64;
    for (int i = 0; i < 4; i++)
    {
        gotoxy(xScore + i, 1);
        printf(" ");
    }

    while (key != NULL)
    {
        gotoxy(xScore, 1);
        cout << key->value;
        xScore++;
        key = key->next;
    }
}

int main()
{
    char key;

    // Posisi awal hero
    int xHero = 35;
    int yHero = 13;
    int xHeroPrev = xHero + 1;
    int yHeroPrev = yHero;

    // Batas Gerak
    int tAtas = 2;
    int tBawah = 24;
    int tKanan = 70;
    int tKiri = 0;

    // Posisi awal enemy
    float xEnemy = 69;
    float yEnemy = 23;
    float xEnemyPrev = xEnemy;
    float yEnemyPrev = yEnemy;

    // langkah enemy
    float lEnemy = 0.3;

    // Posisi awal fruit
    srand(time(0));
    int xFruit = xAcak();
    int yFruit = yAcak();

    // clear area
    bounds();
    // create arena
    arena();

    // tampil fruit
    gotoxy(xFruit, yFruit);
    printf("*");

    // dummy cari detik
    float timer = 0;

    // print langkah
    // int langkah = 27;
    // gotoxy(0, langkah);
    // cout << "    xHero    |    yHero    |  xHeroPrev  |  yHeroPrev  |   xEnemy   |   yEnemy   | xEnemyPrev | yEnemyPrev ";
    // langkah++;

    do
    {
        // gotoxy(0, langkah);
        // printf("  %2f  |  %2f  |  %2f  |  %2f  |  %2f  |  %2f  |  %2f  |  %2f  ", (float)xHero, (float)yHero, (float)xHeroPrev, (float)yHeroPrev, xEnemy, yEnemy, xEnemyPrev, yEnemyPrev);
        // langkah++;

        // mulai cari detik
        timer += 0.1;
        gotoxy(1, 1);
        printf("Timer: %.0f ", timer);

        if ((int)timer >= 10)
        {
            // delScore(score);
            // dispScore();

            timer = 0;
        }

        if ((int)xEnemy == xFruit && (int)yEnemy == yFruit)
        {
            xFruit = xAcak();
            yFruit = yAcak();
            gotoxy(xFruit, yFruit); // mengacak posisi fruit
            printf("*");
        }

        // Menghilangkan jejak Hero dan Enemy
        gotoxy(xHeroPrev, yHeroPrev);
        printf(" ");
        gotoxy(xEnemyPrev, yEnemyPrev);
        printf(" ");

        // Memunculkan Hero dan Enemy
        gotoxy(xHero, yHero);
        printf("H");
        gotoxy(xEnemy, yEnemy);
        printf("O");

        // kondisi menang
        if (score == 5)
        {
            gotoxy(25, 13);
            printf("Selamat anda menang!!");
            break;
        }

        // Detetksi Tombol
        if (kbhit())
        {
            key = getch();
        }

        if (toupper(key) == 'W') // ke atas
        {
            xHeroPrev = xHero;
            yHeroPrev = yHero;
            yHero--;
            if (yHero <= tAtas)
                yHero = tAtas + 1;
        }
        if (toupper(key) == 'A') // ke kiri
        {
            xHeroPrev = xHero;
            yHeroPrev = yHero;
            xHero--;
            if (xHero <= tKiri)
                xHero = tKiri + 1;
        }
        if (toupper(key) == 'S') // ke bawah
        {
            xHeroPrev = xHero;
            yHeroPrev = yHero;
            yHero++;
            if (yHero >= tBawah)
                yHero = tBawah - 1;
        }
        if (toupper(key) == 'D') // ke kanan
        {
            xHeroPrev = xHero;
            yHeroPrev = yHero;
            xHero++;
            if (xHero >= tKanan)
                xHero = tKanan - 1;
        }

        // ALgoritma Kejar Hero
        if (yEnemy < yHero + lEnemy) // enemy di atas hero
        {
            yEnemyPrev = yEnemy;
            yEnemy += lEnemy;
        }
        else if (yEnemy > yHero) // enemy di bawah kero
        {
            yEnemyPrev = yEnemy;
            yEnemy -= lEnemy;
        }

        if (xEnemy < xHero + lEnemy) // enemy di kiri hero
        {
            xEnemyPrev = xEnemy;
            xEnemy += lEnemy;
        }
        else if (xEnemy > xHero) // enemy di kanan hero
        {
            xEnemyPrev = xEnemy;
            xEnemy -= lEnemy;
        }

        // Algoritma makan fruit
        if (xHero == xFruit && yHero == yFruit)
        {

            score++;
            insScore(score);
            dispScore();

            xFruit = xAcak();
            yFruit = yAcak();
            gotoxy(xFruit, yFruit); // mengacak posisi fruit
            printf("*");

            timer = 0;
        }

        slow();
    } while (key != 27);

    gotoxy(0, 25);

    return 0;
}
