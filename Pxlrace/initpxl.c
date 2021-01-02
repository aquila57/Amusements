/*
initpxl.c - Initialize pxl racers  Version 0.1.0
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

void initpxl(xxfmt *xx)
   {
   int i;
   xx->first = 0;
   XSetBackground(xx->dpy, xx->gc, xx->whiteColor);
   XSetForeground(xx->dpy, xx->gc, xx->blackColor);
   XDrawImageString(xx->dpy,xx->w,xx->gc,
      220,16,"Leader = ",9);
   for (i=0;i<xx->racers;i++)
      {
      xx->racer[i] = 0;
      XDrawPoint(xx->dpy,xx->w,xx->gc,0,i+25);
      } /* initialize participants */
   } /* initpxl */
