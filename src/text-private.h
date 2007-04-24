/*
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
 * NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *      Alexandre Pigolkine (pigolkine@gmx.de)
 *      Duncan Mak (duncan@ximian.com)
 *      Miguel de Icaza (miguel@ximian.com)
 *      Ravindra (rkumar@novell.com)
 *  	Sanjay Gupta (gsanjay@novell.com)
 *	Vladimir Vukicevic (vladimir@pobox.com)
 *	Geoff Norton (gnorton@customerdna.com)
 *      Jonathan Gilbert (logic@deltaq.org)
 *	Sebastien Pouliot  <sebastien@ximian.com>
 *
 * Copyright (C) 2003-2007 Novell, Inc (http://www.novell.com)
 */

/*
 * NOTE: This is a private header files and everything is subject to changes.
 */

#ifndef __TEXT_PRIVATE_H__
#define __TEXT_PRIVATE_H__

#include "gdiplus-private.h"
#include "stringformat-private.h"

/* Flags and Support structure for MeasureOrDrawString */
#define STRING_DETAIL_TAB		(1<<0)
#define STRING_DETAIL_LF		(1<<1)
#define STRING_DETAIL_HOTKEY		(1<<2)
#define STRING_DETAIL_BREAK		(1<<3)
#define STRING_DETAIL_HIDDEN		(1<<4)
#define STRING_DETAIL_LINESTART		(1<<5)

/* cache for computed information during MeasureString that can be reused during DrawString */
typedef struct {
	BOOL	has_hotkeys;
	int	align_horz;
	int	align_vert;
	int	line_height;
	int	max_y;
} GpDrawTextData;

typedef struct {
	unsigned long	Flags;
	unsigned long	Linefeeds;
	float		PosX;		/* We call it X, even though it might become Y for vertical drawing */
	float		PosY;		/* We call it Y, even though it might become X for vertical drawing */
	float		Width;		/* Width of the character; height is defined in font structure */
	int		LineLen;	/* If LineStart how many chars is the line long? */
} GpStringDetailStruct;

#include "text.h"

#endif