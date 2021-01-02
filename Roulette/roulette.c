/* roulette.c - Roulette game  Version 0.1.0                         */
/* Copyright (C) 2020 aquila57 at github.com                         */

/* This program is free software; you can redistribute it and/or     */
/* modify it under the terms of the GNU General Public License as    */
/* published by the Free Software Foundation; either version 2 of    */
/* the License, or (at your option) any later version.               */

/* This program is distributed in the hope that it will be useful,   */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of    */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the      */
/* GNU General Public License for more details.                      */

/* You should have received a copy of the GNU General Public License */
/* along with this program; if not, write to:                        */

   /* Free Software Foundation, Inc.                                 */
   /* 59 Temple Place - Suite 330                                    */
   /* Boston, MA 02111-1307, USA.                                    */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <curses.h>
#include "etaus.h"

#define MAXBET (1000000000)

void initcrss(void)
   {
   initscr();
   cbreak();
   echo();
   nonl();
   intrflush(stdscr,FALSE);
   nodelay(stdscr,FALSE);
   } /* initcrss */

#define NUMBER ('a')
#define DBLZERO ('b')
#define EVEN ('c')
#define ODD  ('d')
#define RED  ('e')
#define BLACK ('f')
#define HLF_1_18 ('g')
#define HLF_19_36 ('h')
#define DOZ_1_12 ('i')
#define DOZ_13_24 ('j')
#define DOZ_25_36 ('k')
#define COL_1_3 ('l')
#define ROW_1_12 ('m')
#define QUIT ('q')

int getnumber(void)
   {
   char numstr[4096];
   int len;
   int num;
   getstr(numstr);
   len = strlen(numstr);
   if (len < 1)
      {
      move(14,1);
      clrtoeol();
      addstr("Invalid blank number ");
      /*      ....v....1....v....2....v....3           */
      refresh();
      sleep(2);
      return(-1);    /* return an invalid number */
      } /* if blank number */
   else if (len > 2)
      {
      move(14,1);
      clrtoeol();
      addstr("Invalid number:  ");
      /*      ....v....1....v....2....v....3           */
      move(14,18);
      addstr(numstr);
      refresh();
      sleep(2);
      return(-1);    /* return an invalid number */
      } /* if blank number */
   num = atoi(numstr);
   if (num < 1 || num > 36)
      {
      move(14,1);
      clrtoeol();
      addstr("Invalid number:  ");
      /*      ....v....1....v....2....v....3           */
      move(14,18);
      addstr(numstr);
      refresh();
      sleep(2);
      return(-1);    /* return an invalid number */
      } /* if invalid number of zero or less */
   return(num);
   } /* getnumber */

int getbet(void)
   {
   int len;
   int bet;
   char betstr[4096];
   move(16,1);
   addstr("Enter your bet:  ");
   /*      ....v....1....v....2....v....3           */
   getstr(betstr);
   /***********************************************************/
   /* if enter a blank number, return invalid bet             */
   /***********************************************************/
   len = strlen(betstr);
   if (!len)
      {
      move(16,1);
      clrtoeol();
      addstr("Invalid blank bet");
      refresh();
      sleep(2);
      return(-1);
      } /* if blank bet */
   bet = atoi(betstr);
   /***********************************************************/
   /* edit bet                                                */
   /***********************************************************/
   if (bet < 1 || bet > MAXBET)
      {
      move(16,1);
      clrtoeol();
      addstr("Invalid bet  ");
      /*      ....v....1....v....2....v....3           */
      move(16,14);
      addstr(betstr);
      refresh();
      sleep(2);
      bet = -1;    /* return invalid bet */
      } /* invalid bet */
   return(bet);
   } /* getbet */

void putspin(int spin)
   {
   char str[64];
   move(18,1);
   if (spin == 37)
      {
      sprintf(str,"Result is 00");
      } /* if spin == 37 */
   else
      {
      sprintf(str,"Result is %d", spin);
      } /* else spin is 0 to 36 */
   addstr(str);
   refresh();
   } /* putspin */

int makebet(char cmd, etfmt *et)
   {
   char numstr[4096];
   char color[64];
   int num;
   int winloss;
   int spin;
   int bet;
   int rslt;
   int col;
   int row;
   strcpy(color,"grbrbrbrbrbbrbrbrbr");
   strcat(color, "rbrbrbrbrbbrbrbrbrg");
   winloss = 0;
   spin = etausint(et,38);
   /*********************************************************************/
   spin = 0;
   /*********************************************************************/
   if (cmd == NUMBER)
      {
      move(14,1);
      clrtoeol();
      addstr("Enter number 1-36, 0:  ");
      /*      ....v....1....v....2....v....3           */
      num = getnumber();
      if (num < 0) return(0);
      bet = getbet();
      if (bet < 0) return(0);
      /***********************************************************/
      /* test 00                                                 */
      /***********************************************************/
      rslt = strcmp(numstr,"00");
      if (!rslt)
         {
	 move(16,1);
	 clrtoeol();
	 move(14,1);
	 clrtoeol();
	 addstr("Invalid number 00.  Use option b on menu");
	 refresh();
	 return(0);
	 } /* if 00 */
      putspin(spin);
      if (spin == num)
         {
	 return(35*bet);
	 } /* if spin == num */
      else
         {
	 return(-bet);
	 } /* else spin != num */
      } /* if cmd == NUMBER */
   /***********************************************************/
   /* double zero                                             */
   /***********************************************************/
   else if (cmd == DBLZERO)
      {
      move(14,1);
      clrtoeol();
      addstr("Double zero");
      bet = getbet();
      if (bet < 0) return(0);
      putspin(spin);
      /***********************************************************/
      /* test 00                                                 */
      /***********************************************************/
      if (spin == 37)
         {
         return(35*bet);
         } /* if hit 00 */
      else
         {
         return(-bet);
         } /* else miss 00 */
      } /* else if cmd == DBLZERO */
   /***********************************************************/
   /* even number bet                                         */
   /***********************************************************/
   else if (cmd == EVEN)
      {
      move(14,1);
      clrtoeol();
      addstr("Even number:");
      bet = getbet();
      if (bet < 0) return(0);
      putspin(spin);
      /***********************************************************/
      /* test 00                                                 */
      /***********************************************************/
      if (spin < 2 || spin > 36)
         {
         return(-bet);
         } /* if miss even# */
      else if (spin % 2 == 0)
         {
         return(bet);
         } /* if hit even# */
      else
         {
         return(-bet);
         } /* else miss even# */
      } /* else if cmd == EVEN */
   /***********************************************************/
   /* odd number bet                                          */
   /***********************************************************/
   else if (cmd == ODD)
      {
      move(14,1);
      clrtoeol();
      addstr("Odd number:");
      bet = getbet();
      if (bet < 0) return(0);
      putspin(spin);
      /***********************************************************/
      /* test odd                                                */
      /***********************************************************/
      if (spin < 1 || spin > 35)
         {
         return(-bet);
         } /* if miss odd# */
      else if (spin % 2 == 1)
         {
         return(bet);
         } /* if hit odd# */
      else
         {
         return(-bet);
         } /* else miss odd# */
      } /* else if cmd == ODD */
   /***********************************************************/
   /* red number bet                                          */
   /***********************************************************/
   else if (cmd == RED)
      {
      move(14,1);
      clrtoeol();
      addstr("Red number:");
      bet = getbet();
      if (bet < 0) return(0);
      putspin(spin);
      /***********************************************************/
      /* test red                                                */
      /***********************************************************/
      if (spin < 1 || spin > 36)
         {
         return(-bet);
         } /* if miss red# */
      else
         {
	 if (color[spin] == 'r')
            {
            return(bet);
            } /* hit red# */
         else
            {
            return(-bet);
            } /* else miss red# */
         } /* else look up color */
      } /* else if cmd == RED */
   /***********************************************************/
   /* black number bet                                        */
   /***********************************************************/
   else if (cmd == BLACK)
      {
      move(14,1);
      clrtoeol();
      addstr("Black number:");
      bet = getbet();
      if (bet < 0) return(0);
      putspin(spin);
      /***********************************************************/
      /* test black                                              */
      /***********************************************************/
      if (spin < 1 || spin > 36)
         {
         return(-bet);
         } /* if miss black# */
      else
         {
	 if (color[spin] == 'b')
            {
            return(bet);
            } /* hit black# */
         else
            {
            return(-bet);
            } /* else miss black# */
         } /* else look up color */
      } /* else if cmd == BLACK */
   /***********************************************************/
   /* 1-18 number bet                                         */
   /***********************************************************/
   else if (cmd == HLF_1_18)
      {
      move(14,1);
      clrtoeol();
      addstr("Numbers 1-18:");
      bet = getbet();
      if (bet < 0) return(0);
      putspin(spin);
      /***********************************************************/
      /* test 1-18                                               */
      /***********************************************************/
      if (spin < 1 || spin > 18)
         {
         return(-bet);
         } /* if miss #1-18 */
      else
         {
         return(bet);
         } /* else won spin */
      } /* else if cmd == HLF_1_18 */
   /***********************************************************/
   /* 19-36 number bet                                         */
   /***********************************************************/
   else if (cmd == HLF_19_36)
      {
      move(14,1);
      clrtoeol();
      addstr("Numbers 19-36:");
      bet = getbet();
      if (bet < 0) return(0);
      putspin(spin);
      /***********************************************************/
      /* test 19-36                                              */
      /***********************************************************/
      if (spin < 19 || spin > 36)
         {
         return(-bet);
         } /* if miss #19-36 */
      else
         {
         return(bet);
         } /* else won spin */
      } /* else if cmd == HLF_19_36 */
   /***********************************************************/
   /* 1-12 number bet                                         */
   /***********************************************************/
   else if (cmd == DOZ_1_12)
      {
      move(14,1);
      clrtoeol();
      addstr("Numbers 1-12:");
      bet = getbet();
      if (bet < 0) return(0);
      putspin(spin);
      /***********************************************************/
      /* test 1-12                                               */
      /***********************************************************/
      if (spin < 1 || spin > 12)
         {
         return(-bet);
         } /* if miss #1-12 */
      else
         {
         return(2*bet);
         } /* else won spin */
      } /* else if cmd == DOZ_1_12 */
   /***********************************************************/
   /* 13-24 number bet                                        */
   /***********************************************************/
   else if (cmd == DOZ_13_24)
      {
      move(14,1);
      clrtoeol();
      addstr("Numbers 13-24:");
      bet = getbet();
      if (bet < 0) return(0);
      putspin(spin);
      /***********************************************************/
      /* test 13-24                                              */
      /***********************************************************/
      if (spin < 13 || spin > 24)
         {
         return(-bet);
         } /* if miss #13-24 */
      else
         {
         return(2*bet);
         } /* else won spin */
      } /* else if cmd == DOZ_13_24 */
   /***********************************************************/
   /* 25-36 number bet                                        */
   /***********************************************************/
   else if (cmd == DOZ_25_36)
      {
      move(14,1);
      clrtoeol();
      addstr("Numbers 25-36:");
      bet = getbet();
      if (bet < 0) return(0);
      putspin(spin);
      /***********************************************************/
      /* test 25-36                                              */
      /***********************************************************/
      if (spin < 25 || spin > 36)
         {
         return(-bet);
         } /* if miss #25-36 */
      else
         {
         return(2*bet);
         } /* else won spin */
      } /* else if cmd == DOZ_25_36 */
   /***********************************************************/
   /* column 1-3 bet                                          */
   /***********************************************************/
   else if (cmd == COL_1_3)
      {
      move(14,1);
      clrtoeol();
      addstr("Enter column 1-3:  ");
      /*      ....v....1....v....2....v....3           */
      num = getnumber();
      if (num < 0) return(0);
      /***********************************************************/
      /* edit column number                                      */
      /***********************************************************/
      if (num < 1 || num > 3)
         {
         move(14,1);
         clrtoeol();
	 sprintf(numstr,"Invalid column number:  %d ", num);
         /*              ....v....1....v....2....v....3     */
	 addstr(numstr);
	 refresh();
	 sleep(2);
	 return(0);
	 } /* invalid # */
      bet = getbet();
      if (bet < 0) return(0);
      putspin(spin);
      col = (spin % 3);
      if (!col) col = 3;
      if (spin < 1 || spin > 36)
         {
	 return(-bet);
	 } /* if spin == 0 or 00 */
      else if (col == num)
         {
	 return(2*bet);
	 } /* if spin == column */
      else
         {
	 return(-bet);
	 } /* else spin != column */
      } /* if cmd == COL_1_3 */
   /***********************************************************/
   /* row 1-12 bet                                            */
   /***********************************************************/
   else if (cmd == ROW_1_12)
      {
      move(14,1);
      clrtoeol();
      addstr("Enter row 1-12:  ");
      /*      ....v....1....v....2....v....3           */
      num = getnumber();
      if (num < 0) return(0);
      /***********************************************************/
      /* edit row number                                         */
      /***********************************************************/
      if (num < 1 || num > 12)
         {
         move(14,1);
         clrtoeol();
	 sprintf(numstr,"Invalid row number:  %d ", num);
         /*              ....v....1....v....2....v....3     */
	 addstr(numstr);
	 refresh();
	 sleep(2);
	 return(0);
	 } /* invalid # */
      bet = getbet();
      if (bet < 0) return(0);
      putspin(spin);
      row = ((spin-1) / 3) + 1;
      if (spin < 1 || spin > 36)
         {
	 return(-bet);
	 } /* if spin == 0 or 00 */
      else if (row == num)
         {
	 return(11*bet);
	 } /* if spin == row */
      else
         {
	 return(-bet);
	 } /* else spin != row */
      } /* if cmd == ROW_1_12 */
   return(winloss);
   } /* makebet */

int main()
   {
   char choice;
   char str[64];
   int rslt;
   double dblcash;
   etfmt *et;                     /* etaus structure */
   et = (etfmt *) etausinit();
   rslt = 0;
   dblcash = 0.0;
   initcrss();
   while (1)
      {
      clear();
      move(1,35);
      addstr("Roulette");
      move(2,32);
      addstr("Place your bet:");
      move(4,1);
      addstr("a) number 0-36");
      move(5,1);
      addstr("b) number 00");
      move(6,1);
      addstr("c) even number");
      move(7,1);
      addstr("d) odd  number");
      move(8,1);
      addstr("e) red  number");
      move(9,1);
      addstr("f) black number");
      move(4,40);
      addstr("g) number 1-18");
      move(5,40);
      addstr("h) number 19-36");
      move(6,40);
      addstr("i) number 1-12");
      move(7,40);
      addstr("j) number 13-24");
      move(8,40);
      addstr("k) number 25-36");
      move(10,1);
      addstr("l) column number 1-3");
      move(10,40);
      addstr("m) row number 1-12");
      move(12,1);
      addstr("q) Quit");
      move(12,40);
      addstr("Enter selection:  ");
      /*      ....v....1....v....2....v....3           */
      refresh();
      choice = getch();
      if (choice == 'q') break;
      refresh();
      rslt = makebet(choice,et);
      /*********************************************************/
      /* show win/loss                                         */
      /*********************************************************/
      move(20,1);
      clrtoeol();
      if (rslt > 0)
         {
         addstr("You won  ");
         /*      ....v....1....v....2....v....3           */
         sprintf(str,"$%d", rslt);
         move(20,10);
         addstr(str);
         refresh();
	 } /* if won */
      else if (rslt < 0)
         {
         addstr("You lost  ");
         /*      ....v....1....v....2....v....3           */
         sprintf(str,"$%d", -rslt);
         move(20,11);
         addstr(str);
         refresh();
	 } /* if won */
      else
         {
         addstr("Win/loss:  ");
         /*      ....v....1....v....2....v....3           */
         sprintf(str,"$%d", rslt);
         move(20,12);
         addstr(str);
         refresh();
	 } /* else win/loss = 0 */
      /*********************************************************/
      /* show cash                                             */
      /*********************************************************/
      dblcash += (double) rslt;
      sprintf(str,"$%.0f", dblcash);
      move(20,40);
      clrtoeol();
      addstr("Total cash:  ");
      /*      4....v....5....v....6....v....7           */
      move(20,53);
      addstr(str);
      move(22,25);
      addstr("Press any key to continue");
      refresh();
      getch();
      } /* for each turn of the wheel */
   endwin();
   free(et->state);
   free(et);
   return(0);            /* normal eoj */
   } /* main */
