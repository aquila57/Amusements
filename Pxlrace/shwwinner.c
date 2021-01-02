/*
shwwinner.c - Display winner  Version 0.1.0
Copyright (C) 2020  aquila57 at github.com

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to:

	Free Software Foundation, Inc.
	59 Temple Place - Suite 330
	Boston, MA  02111-1307, USA.
*/

#include "race.h"

void shwwinner(xxfmt *xx)
   {
   int i,row,dest;
   char str[128];
   i = 0;
   row = 50;
   dest = xx->dpywdth - 1;
   strcpy(str,"     Racer  Time");
   XDrawImageString(xx->dpy,xx->w,xx->gc,
      10,row,str,strlen(str));
   row += 20;
   while (i < 10 && xx->toptenw[i] < DFLTRACER)
      {
      sprintf(str,"%2d.  %4d   %4d",
         i+1, xx->toptenw[i]+1, xx->toptent[i]);
      XDrawImageString(xx->dpy,xx->w,xx->gc,
         10,row,str,strlen(str));
      row += 20;
      i++;
      } /* list top ten */
   XDrawImageString(xx->dpy,xx->w,xx->gc,
      10,380,"  r = rerun",11);
   XDrawImageString(xx->dpy,xx->w,xx->gc,
      10,400,"esc = exit",10);
   XDrawImageString(xx->dpy,xx->w,xx->gc,
      220,16,"Winner = ",9);
   XSetBackground(xx->dpy, xx->gc, xx->whiteColor);
   XSetForeground(xx->dpy, xx->gc, xx->red);
   XDrawPoint(xx->dpy,xx->w,xx->gc,
      dest,xx->first+25);
   XDrawPoint(xx->dpy,xx->w,xx->gc,
      dest-1,xx->first+25);
   XDrawPoint(xx->dpy,xx->w,xx->gc,
      dest-2,xx->first+25);
   XDrawPoint(xx->dpy,xx->w,xx->gc,
      dest,xx->first+24);
   XDrawPoint(xx->dpy,xx->w,xx->gc,
      dest-1,xx->first+24);
   XDrawPoint(xx->dpy,xx->w,xx->gc,
      dest-2,xx->first+24);
   XDrawPoint(xx->dpy,xx->w,xx->gc,
      dest,xx->first+26);
   XDrawPoint(xx->dpy,xx->w,xx->gc,
      dest-1,xx->first+26);
   XDrawPoint(xx->dpy,xx->w,xx->gc,
      dest-2,xx->first+26);
   XSetForeground(xx->dpy, xx->gc, xx->blackColor);
   sprintf(str,"  Time = %4d", xx->winticks);
   XDrawImageString(xx->dpy,xx->w,xx->gc,
      220,36,str,strlen(str));
   } /* shwwinner */
