#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <iostream>

using namespace std;

// Berpindah sesuai dengan koordinat (x, y)
void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Efek slow / memperlambat
void slow()
{
  float a = 1;
  do
  {
    a = a + 0.1;
  } while (a < 1000000);
}

// Membersihkan seluruh cmd
void clearCMD()
{
  system("cls");
}

// Membuat / mengkosongkan arena
void clearArena()
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

/*
  Untuk membuat menu permainan
  (key binds, score, timer)
*/
void printMenu()
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

// Memberikan koordinat x secara acak
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

// Memberikan koordinat y secara acak
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

#endif