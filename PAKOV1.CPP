/*
Made by Mrinmay Dhar and Avinash Chaudhary
Class XII-A
Subject Code: 083
*/
// Header Files Used
#include <fstream.h>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <process.h>
#include <math.h>

// Data Members
int diffchar, diff;
int x, y, m, n;
int ch, j, i = 10;
int gdriver = DETECT, gmode, errorcode;
int midx, midm, midy, midn;
int xco = 20, yco = 30, xco1 = 50, yco1 = 60;
int count1, count2;
int stangle = 45, endangle = 315, radius = 10;
char choice = 'y';

// Functions
void screensave();
void init();
void score(int&, int&);
void game(int&);
void welcome();
void Sound(int, int);
void soundfun();
void history();

// main Begins
void main() {
  init();
  soundfun();
  while (choice == 'y' || choice == 'Y') {
    midx = getmaxx() / 2;
    midy = getmaxy() / 2;
    midm = getmaxx() / 3;
    midn = getmaxy() / 3;
  star:
    cleardevice();
    outtextxy(midx - 300, midy - 200,
              "Enter difficulty (1.Hard 2.Normal 3.Easy)");
    outtextxy(midx - 300, midy - 150, "Press 4 for help");
    outtextxy(midx + 100, midy - 150, "Press 6 to Exit");
    outtextxy(midx - 100, midy - 150, "Press 5 for History");
    window(10, 10, 40, 11);
    cin >> diffchar;
    switch (diffchar) {
      case 3:
        outtextxy(midx - 300, midy - 50, "Easy Mode Selected");
        diff = 5;
        game(diff);
        break;
      case 2:
        outtextxy(midx - 300, midy - 50, "Normal Mode Selected");
        diff = 3;
        game(diff);
        break;
      case 1:
        outtextxy(midx - 300, midy - 50, "Hard Mode Selected");
        diff = 0;
        game(diff);
        break;
      case 4:
        welcome();
        break;
      case 6:
        screensave();
        break;
      case 5:
        history();
        break;
      default:
        outtextxy(midx - 300, midy - 50, "Invalid option. Try Again");
        break;
    }
    cleardevice();
    if (diffchar == 4 || diffchar == 5) goto star;
    cout << "More (y/n): ";
    cin >> choice;
    if (choice == 'n' || choice == 'N') screensave();
  }
}

void screensave() {
  init();
  setcolor(14);
  settextstyle(TRIPLEX_FONT, HORIZ_DIR, 5);
  outtextxy(getmaxx() / 2 + 200, getmaxy() / 2 - 200, "BYE");
  settextstyle(SMALL_FONT, HORIZ_DIR, 10);
  outtextxy(getmaxx() / 2 - 300, getmaxy() / 2, "Made By:");
  settextstyle(SMALL_FONT, HORIZ_DIR, 7);
  outtextxy(getmaxx() / 2 - 300, getmaxy() / 2 + 50,
            "Mrinmay Dhar and Avinash Chaudhary.");
  settextstyle(SMALL_FONT, HORIZ_DIR, 10);
  outtextxy(getmaxx() / 2 - 300, getmaxy() / 2 + 150, "Class 12 A");
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
      pieslice(x, y * 100 + 200, stangle, endangle, r);
      delay(50);
      setcolor(0);
      setfillstyle(1, 0);
      pieslice(x, y * 100 + 200, stangle, endangle, r);
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

void init() {
  initgraph(&gdriver, &gmode, "\\tc\\bgi");
  errorcode = graphresult();
  if (errorcode != grOk) {
    printf("Graphics error: %s\n", grapherrormsg(errorcode));
    printf("Press any key to halt:");
    getch();
    exit(1);
  }
}
void score(int& score1, int& score2) {
  init();
  char name1[30], name2[30];
  ofstream fil("score.txt", ios::app);
  window(1, 1, 80, 25);
  cout << "Enter Name of Player Yellow: ";
  gets(name1);
  cout << name1 << "'s score is " << score1 << endl;
  cout << "Enter Name of Player Pink: ";
  gets(name2);
  cout << name2 << "'s score is " << score2 << endl;
  if (score1 > score2) {
    cout << endl;
    puts(name1);
    cout << "Wins!";
  }
  if (score1 < score2) {
    cout << endl;
    puts(name2);
    cout << "Wins!";
  }
  if (score1 == score2) cout << "\nIt's a draw";
  fil << name1 << "\t" << score1 << "\t"
      << "Team Yellow\n";
  fil << name2 << "\t" << score2 << "\t"
      << "Team Pink\n";
  fil.close();
  cout << "\nMenu? (y/n) ";
  cin >> choice;
  if (choice == 'y' || choice == 'Y')
    main();
  else
    screensave();
}

void game(int& diff) {
  midx = getmaxx() / 2;
  midy = getmaxy() / 2;
  midm = getmaxx() / 3;
  midn = getmaxy() / 3;
  m = n = x = y = count1 = count2 = 0;
  randomize();
  outtextxy(midx - 300, midy, "Please Wait...");
  sleep(1);
  while (1) {
    cleardevice();
    setcolor(14);  // yellow
    setfillstyle(SOLID_FILL, getcolor());
    pieslice(midx, midy, stangle, endangle,
             radius);  // controls: up,down,right,left
    setcolor(5);  // pink
    setfillstyle(SOLID_FILL, getcolor());
    pieslice(midm, midn, stangle, endangle, radius);  // controls: w,a,s,d
    setcolor(15);  // white
    setfillstyle(SOLID_FILL, getcolor());
    pieslice(xco, yco, 0, 360, 4);  // food
    setcolor(12);  // light red
    setfillstyle(SOLID_FILL, getcolor());
    pieslice(xco1, yco1, 0, 360, 4);  // poison
    if ((midx <= (midm + 10) && midx >= (midm - 10)) &&
        (midy <= (midn + 10) && midy >= (midn - 10))) {
      setcolor(15);
      settextstyle(TRIPLEX_FONT, HORIZ_DIR, 14);
      outtext("CRASH");
      for (i = 1000; i > 750; i--) {
        sound(i);
        delay(10);
      }
      nosound();
      goto lab;
    }
    if ((midx <= (xco + 10) && midx >= (xco - 10)) &&
        (midy <= (yco + 10) && midy >= (yco - 10))) {
      count1++;
      sound(350);
      delay(5);
      nosound();
      xco = random(getmaxx());
      yco = random(getmaxy());
    }
    if ((midm <= (xco + 10) && midm >= (xco - 10)) &&
        (midn <= (yco + 10) && midn >= (yco - 10))) {
      count2++;
      sound(350);
      delay(5);
      nosound();
      xco = random(getmaxx());
      yco = random(getmaxy());
    }
    if ((midx <= (xco1 + 10) && midx >= (xco1 - 10)) &&
        (midy <= (yco1 + 10) && midy >= (yco1 - 10))) {
      count1--;
      sound(450);
      delay(5);
      nosound();
      xco1 = random(getmaxx());
      yco1 = random(getmaxy());
    }
    if ((midm <= (xco1 + 10) && midm >= (xco1 - 10)) &&
        (midn <= (yco1 + 10) && midn >= (yco1 - 10))) {
      count2--;
      sound(450);
      delay(5);
      nosound();
      xco1 = random(getmaxx());
      yco1 = random(getmaxy());
    }

    if (kbhit()) {
      ch = getch();
      if (ch == 72)  // up key
      {
        x = 0;
        y = -1;
        sound(550);
        delay(10);
        nosound();
      }
      if (ch == 75)  // left key
      {
        x = -1;
        y = 0;
        sound(550);
        delay(10);
        nosound();
      }
      if (ch == 77)  // right key
      {
        x = 1;
        y = 0;
        sound(550);
        delay(10);
        nosound();
      }
      if (ch == 80)  // down key
      {
        x = 0;
        y = 1;
        sound(550);
        delay(10);
        nosound();
      }
      if (ch == 119)  // w key
      {
        m = 0;
        n = -1;
        sound(550);
        delay(10);
        nosound();
      }
      if (ch == 97)  // a key
      {
        m = -1;
        n = 0;
        sound(550);
        delay(10);
        nosound();
      }
      if (ch == 100)  // d key
      {
        m = 1;
        n = 0;
        sound(550);
        delay(10);
        nosound();
      }
      if (ch == 115)  // s key
      {
        m = 0;
        n = 1;
        sound(550);
        delay(10);
        nosound();
      }
      if (ch == 27)  // escape key
      {
      lab:
        cleardevice();
        closegraph();
        score(count1, count2);
      }
    }
    midm += m;
    midn += n;
    midx += x;
    midy += y;
    if (midx < 0) midx = getmaxx();
    if (midy < 0) midy = getmaxy();
    if (midx > getmaxx()) midx = 0;
    if (midy > getmaxy()) midy = 0;
    if (midm < 0) midm = getmaxx();
    if (midn < 0) midn = getmaxy();
    if (midm > getmaxx()) midm = 0;
    if (midn > getmaxy()) midn = 0;
    delay(diff);
  }
}
void Sound(int x, int y) {
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
void welcome() {
  cleardevice();
  clrscr();
  init();
  cout << "Controls\n";
  cout << "Pink: \n\tW: Move upwards\tS: Move downwards\n\tA: Move left\tD: "
          "Move right\n\n";
  cout << "Yellow:\n\t" << char(24) << ": Move upwards\t" << char(25)
       << ": Move downwards\n\t" << char(27) << ": Move left\t" << char(26)
       << ": Move right\n\n";
  cout << "Press any key to exit";
  getch();
}
void history() {
  init();
  cleardevice();
  char ch[60];
  cout << "History\n";
  ifstream fin("score.txt");
  while (!fin.eof()) {
    fin.getline(ch, 50);
    puts(ch);
  }
  getch();
}
