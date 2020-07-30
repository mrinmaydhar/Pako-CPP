/*
//
   TODO
   >More walls
   >Timer
   >Mouse Integration
   >Triple Buffer video memory (simultaneous artifact render)
   >Procedurally generated mazes
     >depth based, recursive division etc.
//
*/
#include <iostream.h>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <process.h>
#include <math.h>

#define PIE_SIZE 10

// Functions
void screensave();
void init();
void game(int &);
void Sound(int, int);
void soundfun();
void menu();
void history();

// main Begins
void main() {
  init();
  soundfun();
  menu();
}

void menu() {
  int diffchar, diff;
  char choice = 'y';
  do {
    int midx = getmaxx() / 2;
    int midy = getmaxy() / 2;
    cleardevice();
    setcolor(14);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(midx - 300, midy - 200,
              "Enter difficulty (1.Hard 2.Normal 3.Easy)");
    outtextxy(midx - 300, midy - 175,
              "Press 4 for help menu, 5 for Pako's story.");
    outtextxy(midx - 300, midy - 150, "Press 6 to Exit.");
    outtextxy(midx - 290, midy - 125,
              "Press \"esc\" while in game to return here.");
    gotoxy(10, 10);
    cin >> diffchar;
    switch (diffchar) {
      case 3:
        outtextxy(midx - 300, midy - 50, "Easy Mode Selected");
        diff = 60;
        game(diff);
        break;
      case 2:
        outtextxy(midx - 300, midy - 50, "Normal Mode Selected");
        diff = 50;
        game(diff);
        break;
      case 1:
        outtextxy(midx - 300, midy - 50, "Hard Mode Selected");
        diff = 40;
        game(diff);
        break;
      case 4:
        outtextxy(midx - 300, midy - 50, "Help menu Selected");
        sleep(1);
        cleardevice();
        outtextxy(midx - 300, midy - 200, "Press \'w\' for moving up");
        outtextxy(midx - 300, midy - 175, "Press \'a\' for moving left");
        outtextxy(midx - 300, midy - 150, "Press \'s\' for moving down");
        outtextxy(midx - 300, midy - 125, "Press \'d\' for moving right");
        setcolor(1);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
        outtextxy(midx - 300, midy, " Avoid the walls!!");
        getch();
        break;
      case 5:
        outtextxy(midx - 300, midy - 50, "The Epilogue...");
        sleep(1);
        cleardevice();
        history();
        break;
      case 6:
        screensave();
        break;
      default:
        outtextxy(midx - 300, midy - 50, "Invalid option. Try Again");
    }
    cleardevice();
    if (diffchar == 4 || diffchar == 5) menu();
    cout << "More (y/n): ";
    cin >> choice;
  } while (choice == 'n' || choice == 'N');
  screensave();
}

void history() {
  randomize();
  init();
  cleardevice();
  int midx = getmaxx() / 2;
  int midy = getmaxy() / 2;
  setcolor(15);
  settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
  /*
  Pako, after evading the ghosts in his maiden voyage,
  was last seen on a journey through space and time.
  On his FTL starship, the "WII_LGM", he cruised through
  the ravages of time to seek the greater mysteries of time.
  But, alas, he was to be captured again by the ghosts.
  This time though, they kept him locked in a synthetic universe,
  so that he can be mentally tortured, knowing he can never escape.

  Help Pako in his endeavour to escape the cells.....
  */
  outtextxy(midx - 300, midy - 200,
            "Pako, after evading the ghosts in his maiden voyage,");
  outtextxy(midx - 295, midy - 180,
            "was last seen on a journey through space and time.");
  outtextxy(midx - 295, midy - 160,
            "On his FTL starship, the \"WII_LGM\", he cruised through");
  outtextxy(midx - 295, midy - 140,
            "the ravages of time to seek the greater mysteries of time.");
  getch();

  cleardevice();
  init();
  static int r = 20;
  static int StartX = 100;
  static int StartY = 50;

  struct viewporttype vp;
  int PauseTime, x, y, ulx, uly, lrx, lry, i, width, height, step;
  void *Saucer;

  getviewsettings(&vp);

  unsigned int size_s;
  int MaxX, MaxY; /* The maximum resolution of the screen */
  int MaxColors;  /* The maximum # of colors available	*/

  MaxColors = getmaxcolor() + 1; /* Read maximum number of colors*/

  MaxX = getmaxx();
  MaxY = getmaxy(); /* Read size of screen		*/

  /* Plot some "stars"  */
  for (i = 0; i < 1000; ++i)
    putpixel(random(MaxX), random(MaxY), random(MaxColors - 1) + 1);
  x = MaxX / 2;
  y = MaxY / 2;

  /* Draw Saucer */
  setfillstyle(SOLID_FILL, getmaxcolor());
  fillellipse(StartX, StartY, r, (r / 3) + 2);
  ellipse(StartX, StartY - 4, 190, 357, r, r / 3);

  line(StartX + 7, StartY - 6, StartX + 10, StartY - 12);
  circle(StartX + 10, StartY - 12, 2);
  line(StartX - 7, StartY - 6, StartX - 10, StartY - 12);
  circle(StartX - 10, StartY - 12, 2);

  /* Read saucer image */
  ulx = StartX - (r + 1);
  uly = StartY - 14;
  lrx = StartX + (r + 1);
  lry = StartY + (r / 3) + 3;
  width = lrx - ulx + 1;
  height = lry - uly + 1;
  size_s = imagesize(ulx, uly, lrx, lry);

  Saucer = malloc(size_s);
  getimage(ulx, uly, lrx, lry, Saucer);
  putimage(ulx, uly, Saucer, XOR_PUT);

  x = MaxX / 2;
  y = MaxY / 2;
  PauseTime = 70;
  while (!kbhit()) {
    /* Draw the Saucer */
    putimage(x, y, Saucer, XOR_PUT); /*  draw image  */
    delay(PauseTime);
    putimage(x, y, Saucer, XOR_PUT); /* erase image  */

    /* Move Saucer */

    step = random(2 * r);
    if ((step / 2) % 2 != 0) step = -1 * step;
    x = x + step;
    step = random(r);
    if ((step / 2) % 2 != 0) step = -1 * step;
    y = y + step;

    if (vp.left + x + width - 1 > vp.right)
      x = vp.right - vp.left - width + 1;
    else if (x < 0)
      x = 0;
    if (vp.top + y + height - 1 > vp.bottom)
      y = vp.bottom - vp.top - height + 1;
    else if (y < 0)
      y = 0;
  }
  free(Saucer);
  cleardevice();
  setcolor(12);
  outtextxy(midx - 295, midy - 120,
            "But, alas, he was to be captured again by the ghosts.");
  outtextxy(midx - 295, midy - 100,
            "This time though, they kept him locked in a synthetic universe,");
  outtextxy(
      midx - 295, midy - 80,
      "so that he can be mentally tortured, knowing he can never escape.");
  getch();
  sound(100);
  delay(50);
  nosound();
  getch();
  cleardevice();
  setcolor(14);
  settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
  outtextxy(midx - 300, midy - 150, "Help Pako in his endeavour to");
  outtextxy(midx - 290, midy - 120, "escape the cells.....");
  getch();
}

void init() {
  int gdriver = DETECT, gmode, errorcode;
  initgraph(&gdriver, &gmode, "\\turboc3\\bgi");
  errorcode = graphresult();
  if (errorcode != grOk) {
    printf("Graphics error: %s\n", grapherrormsg(errorcode));
    printf("Press any key to halt:");
    getch();
    exit(1);
  }
}

void screensave() {
  init();
  setcolor(14);
  settextstyle(TRIPLEX_FONT, HORIZ_DIR, 7);
  outtextxy(getmaxx() / 2 + 200, getmaxy() / 2 - 200, "BYE");
  settextstyle(SMALL_FONT, HORIZ_DIR, 10);
  outtextxy(getmaxx() / 2 - 300, getmaxy() / 2, "Made By:");
  settextstyle(SMALL_FONT, HORIZ_DIR, 7);
  outtextxy(getmaxx() / 2 - 300, getmaxy() / 2 + 50, "Mrinmay Dhar.");
  settextstyle(SMALL_FONT, HORIZ_DIR, 10);
  outtextxy(getmaxx() / 2 - 300, getmaxy() / 2 + 150, "A2305216493");
  float x = 1, y = 0.00000, j = 0.5, count = 0.1;
  float r = 15;
  setcolor(14);
  line(0, 215, 650, 215);
  sleep(1);
  for (int k = 0; k <= 7; k++) {
    for (float i = 90; i < 270; i += 10) {
      y = cos(((i * 22 / 7) / 180)) / j;
      if (y > 0) y = -y;
      x += 5;
      setcolor(14);
      setfillstyle(1, 14);
      pieslice(x, y * 100 + 200, 45, 315, r);
      delay(50);
      setcolor(0);
      setfillstyle(1, 0);
      pieslice(x, y * 100 + 200, 45, 315, r);
      if (kbhit()) exit(0);
    }
    j += count;
    count += .1;
  }
  sleep(1);
  cleardevice();
  closegraph();
  exit(0);
}

inline void Sound(int x, int y) {
  sound(x);
  delay(y);
}

void soundfun() {
  setcolor(14);
  settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 10);
  ellipse(getmaxx() / 2, getmaxy() / 2, 0, 360, 300, 150);
  setcolor(15);
  outtextxy(getmaxx() / 2 - 250, getmaxy() / 2 - 100, "Welcome");
  settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
  cout << "Turn up your speakers";
  Sound(330, 100);
  Sound(330, 100);
  Sound(330, 100);
  Sound(262, 100);
  Sound(330, 100);
  Sound(392, 100);
  Sound(196, 100);
  Sound(196, 100);
  Sound(262, 100);
  Sound(330, 100);
  Sound(392, 100);
  Sound(523, 100);
  Sound(660, 100);
  Sound(784, 100);
  Sound(660, 100);
  Sound(207, 100);
  Sound(262, 100);
  Sound(311, 100);
  Sound(415, 100);
  Sound(523, 100);
  Sound(622, 100);
  Sound(830, 100);
  Sound(622, 100);
  Sound(233, 100);
  Sound(294, 100);
  Sound(349, 100);
  Sound(466, 100);
  Sound(587, 100);
  Sound(698, 100);
  Sound(932, 100);
  Sound(932, 100);
  Sound(932, 100);
  Sound(932, 100);
  Sound(1046, 675);
  nosound();
}

struct wall {
  int top;
  int left;
  int bottom;
  int right;
} wall[10];

void game(int &diff) {
  cleardevice();
  init();
  int MaxX, MaxY; /* The maximum resolution of the screen */
  int MaxColors;  /* The maximum # of colors available	*/

  MaxX = getmaxx();
  MaxY = getmaxy(); /* Read size of screen		*/

  void *pie;
  int midx, midy;
  int ch;
  unsigned int size;
  midx = getmaxx() / 2;
  midy = getmaxy() / 2;

  wall[1].top = 50;
  wall[1].bottom = 60;
  wall[1].left = 50;
  wall[1].right = getmaxy() - 50;

  setfillstyle(XHATCH_FILL, 1);
  bar(wall[1].left, wall[1].top, wall[1].right, wall[1].bottom);
  setfillstyle(SOLID_FILL, 14);
  /* draw the image to be grabbed */
  moveto(midx, midy);
  pieslice(midx, midy, 45, 315, 10);

  /* calculate the size of the image */
  size = imagesize(midx - (PIE_SIZE), midy - PIE_SIZE, midx + (PIE_SIZE),
                   midy + PIE_SIZE);

  /* allocate memory to hold the image */
  pie = malloc(size);

  /* grab the image */
  getimage(midx - (PIE_SIZE), midy - PIE_SIZE, midx + (PIE_SIZE),
           midy + PIE_SIZE, pie);
  // long count=10000; //for timer based game
  /* repeat */
  while (1) {
    if (kbhit())  // if key pressed
    {
      ch = getch();  // get key pressed

      if (ch == 27)  // escape key
      {
        /* clean up */
        free(pie);
        cleardevice();
        menu();
      }

      else if (ch == 119)  // w key
      {
        while (!kbhit()) {
          if ((midx - 10) < wall[1].right && (midx + 10) > wall[1].left &&
              (midy - 10) < wall[1].bottom && (midy + 10) > wall[1].top) {
            delay(10);
            putimage(midx - (PIE_SIZE), midy - PIE_SIZE, pie, XOR_PUT);
            midx = getmaxx() / 2;
            midy = getmaxy() / 2;
            putimage(midx - (PIE_SIZE), midy - PIE_SIZE, pie, XOR_PUT);
            break;
          } else {
            /* delay for smooth movement across screen */
            delay(diff);
            /* erase old image */
            putimage(midx - (PIE_SIZE), midy - PIE_SIZE, pie, XOR_PUT);
            midy -= PIE_SIZE;
            if (midy <= 0) midy = MaxY;
            /* plot new image */
            putimage(midx - (PIE_SIZE), midy - PIE_SIZE, pie, XOR_PUT);
          }
        }
      }

      else if (ch == 115)  // s key
      {
        while (!kbhit()) {
          if ((midx - 10) < wall[1].right && (midx + 10) > wall[1].left &&
              (midy - 10) < wall[1].bottom && (midy + 10) > wall[1].top) {
            delay(10);
            putimage(midx - (PIE_SIZE), midy - PIE_SIZE, pie, XOR_PUT);
            midx = getmaxx() / 2;
            midy = getmaxy() / 2;
            putimage(midx - (PIE_SIZE), midy - PIE_SIZE, pie, XOR_PUT);
            break;
          } else {
            /* delay for smooth movement across screen */
            delay(diff);
            /* erase old image */
            putimage(midx - (PIE_SIZE), midy - PIE_SIZE, pie, XOR_PUT);
            midy += PIE_SIZE;
            if (midy >= MaxY) midy = 0;
            /* plot new image */
            putimage(midx - (PIE_SIZE), midy - PIE_SIZE, pie, XOR_PUT);
          }
        }
      }

      else if (ch == 97)  // a key
      {
        while (!kbhit()) {
          if ((midx - 10) < wall[1].right && (midx + 10) > wall[1].left &&
              (midy - 10) < wall[1].bottom && (midy + 10) > wall[1].top) {
            delay(10);
            putimage(midx - (PIE_SIZE), midy - PIE_SIZE, pie, XOR_PUT);
            midx = getmaxx() / 2;
            midy = getmaxy() / 2;
            putimage(midx - (PIE_SIZE), midy - PIE_SIZE, pie, XOR_PUT);
            break;
          } else {
            /* delay for smooth movement across screen */
            delay(diff);
            /* erase old image */
            putimage(midx - (PIE_SIZE), midy - PIE_SIZE, pie, XOR_PUT);
            midx -= PIE_SIZE;
            if (midx <= 0) midx = MaxX;
            /* plot new image */
            putimage(midx - (PIE_SIZE), midy - PIE_SIZE, pie, XOR_PUT);
          }
        }
      }

      else if (ch == 100)  // d key
      {
        while (!kbhit()) {
          if ((midx - 10) < wall[1].right && (midx + 10) > wall[1].left &&
              (midy - 10) < wall[1].bottom && (midy + 10) > wall[1].top) {
            delay(10);
            putimage(midx - (PIE_SIZE), midy - PIE_SIZE, pie, XOR_PUT);
            midx = getmaxx() / 2;
            midy = getmaxy() / 2;
            putimage(midx - (PIE_SIZE), midy - PIE_SIZE, pie, XOR_PUT);
            break;
          } else {
            /* delay for smooth movement across screen */
            delay(diff);
            /* erase old image */
            putimage(midx - (PIE_SIZE), midy - PIE_SIZE, pie, XOR_PUT);
            midx += PIE_SIZE;
            if (midx >= MaxX) midx = 0;
            /* plot new image */
            putimage(midx - (PIE_SIZE), midy - PIE_SIZE, pie, XOR_PUT);
          }
        }
      }
    }
  }
}
