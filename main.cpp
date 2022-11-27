#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "header.h"

using namespace std;

// Calculating score
struct scoreStack
{
  int value;
  scoreStack *next;
};

scoreStack *head = NULL;
scoreStack *tail = NULL;

int xScore;
int scoreValue = 0;

bool isEmpty();
void addScore();
void subScore();
void dispScore();

// Posisi hero, enemy, fruit
// Posisi awal hero
int xHero = 35;
int yHero = 13;
int xHeroPrev = xHero + 1;
int yHeroPrev = yHero;

// Batas Gerak
int tAtas = 2;
int tKiri = 0;
int tBawah = 24;
int tKanan = 70;

// Posisi awal enemy
float xEnemy = 69;
float yEnemy = 23;
float xEnemyPrev = xEnemy;
float yEnemyPrev = yEnemy;

// langkah enemy
float lEnemy = 0.3;

// Posisi awal fruit
int xFruit = xAcak();
int yFruit = yAcak();

void dispFruit();

// Displaying dan Movement hero & enemy
void dispHeroEnemy();
void heroMovement();
void enemyMovement();

// Game Over
int gameOver();

// Untuk menerima inputan keyboard
char clickedKey;

// Untuk menghitung detik
float timer = 0;

int main()
{
  srand(time(0));

  // set arena
  clearCMD();
  printMenu();
  clearArena();

  // tampil fruit pertama
  dispFruit();

  // start the game
  do
  {
    // menghitung detik
    timer += 0.1;

    gotoxy(1, 1);
    printf("Timer: %.0f ", timer);

    // jika tidak makan selama 10 detik (-1 score)
    if ((int)timer >= 10)
    {
      // subScore();
      // dispScore();

      timer = 0;
    }

    // jika fruit tertimpa enemy (memindahkan fruit)
    if ((int)xEnemy == xFruit && (int)yEnemy == yFruit)
    {
      dispFruit();
    }

    // Displaying Hero & Enemy
    dispHeroEnemy();

    // Movement Hero & Enemy
    heroMovement();
    enemyMovement();

    // Jika hero makan fruit (+1 score)
    if (xHero == xFruit && yHero == yFruit)
    {
      addScore();
      dispScore();

      dispFruit();

      timer = 0;
    }

    // (1) game over
    if (gameOver() == 1 || gameOver() == 2)
    {
      break;
    }

    slow();

  } while (clickedKey != 27);

  gotoxy(0, 25);

  return 0;
}

// Mengecek apakah scoreStack kosong
bool isEmpty()
{
  return head == NULL;
}

// Menambah score
void addScore()
{
  scoreValue++;

  scoreStack *help = new scoreStack();
  help->value = scoreValue;
  help->next = NULL;

  if (isEmpty())
  {
    head = tail = help;
  }
  else
  {
    tail->next = help;
    tail = help;
  }
}

// Mengurangi score
void subScore()
{
  scoreStack *key = head;
  scoreStack *prev = NULL;

  if (isEmpty())
  {
  }
  else
  {
    while (key != NULL)
    {
      if (key->next == NULL)
      {
        prev->next = NULL;
        tail = prev;
        free(key);
        break;
      }
      prev = key;
      key = key->next;
    }
  }
}

// Menampilkan score
void dispScore()
{
  scoreStack *key = head;

  xScore = 64;
  while (key != NULL)
  {
    gotoxy(xScore, 1);
    printf("%d", key->value);
    xScore++;
    key = key->next;
  }
}

// Menampilkan fruit secara acak
void dispFruit()
{
  xFruit = xAcak();
  yFruit = yAcak();
  gotoxy(xFruit, yFruit);
  printf("*");
}

// Menampilkan hero dan enemy
void dispHeroEnemy()
{
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
}

// Mengerakkan hero dgn keyboard
void heroMovement()
{
  // Deteksi keyboard
  if (kbhit())
  {
    clickedKey = getch();
  }

  if (toupper(clickedKey) == 'W') // ke atas
  {
    xHeroPrev = xHero;
    yHeroPrev = yHero;
    yHero--;
  }
  if (toupper(clickedKey) == 'A') // ke kiri
  {
    xHeroPrev = xHero;
    yHeroPrev = yHero;
    xHero--;
  }
  if (toupper(clickedKey) == 'S') // ke bawah
  {
    xHeroPrev = xHero;
    yHeroPrev = yHero;
    yHero++;
  }
  if (toupper(clickedKey) == 'D') // ke kanan
  {
    xHeroPrev = xHero;
    yHeroPrev = yHero;
    xHero++;
  }
}

// Mengerakkan enemy untuk mengejar hero
void enemyMovement()
{
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
}

int gameOver()
{
  if (xHero == (int)xEnemy && yHero == (int)yEnemy)
  {
    clearArena();
    dispHeroEnemy();
    gotoxy(29, 13);
    printf("Game Over!!!");
    return 1;
  }
  if (yHero == tAtas)
  {
    yHero += 1;
    clearArena();
    dispHeroEnemy();
    gotoxy(29, 13);
    printf("Game Over!!!");
    return 1;
  }
  if (xHero == tKiri)
  {
    xHero += 1;
    clearArena();
    dispHeroEnemy();
    gotoxy(29, 13);
    printf("Game Over!!!");
    return 1;
  }
  if (yHero == tBawah)
  {
    yHero -= 1;
    clearArena();
    dispHeroEnemy();
    gotoxy(29, 13);
    printf("Game Over!!!");
    return 1;
  }
  if (xHero == tKanan)
  {
    xHero -= 1;
    clearArena();
    dispHeroEnemy();
    gotoxy(29, 13);
    printf("Game Over!!!");
    return 1;
  }
}
