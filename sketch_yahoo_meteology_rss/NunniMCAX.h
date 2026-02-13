/*
 * $Id: NunniMCAX.h,v 1.4 2005/02/21 11:26:44 nunnari Exp $
 *
 * Copyright (c) 2004 Roberto Nunnari - roberto.nunnari@nunnisoft.ch
 * All rights reserved.
 *
 *  This file is part of NunniMCAX.
 *
 *  NunniMCAX is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  NunniMCAX is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with NunniFSMGen; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
  Modified by todotani 2009/8/23 for adaptation to Arduino
*/


#ifndef NunniMCAX_H
#define NunniMCAX_H


#ifdef __cplusplus
extern "C"
{
#endif		/* __cplusplus */

#include <stdio.h>


/* NunniHashtable functions */
struct NunniHashtable * NunniHashtableCreate();
void NunniHashtableDelete( struct NunniHashtable *ht );
int NunniHashtableIsEmpty( struct NunniHashtable *ht );
int NunniHashtablePut( struct NunniHashtable *ht, char *key, char *value );
const char * NunniHashtableGet( struct NunniHashtable *ht, const char *key );
int NunniHashtableContains( struct NunniHashtable *ht, const char *key );
int NunniHashtableKeys( struct NunniHashtable *ht, char *keys[] );
int NunniHashtableSize( struct NunniHashtable *ht );
void NunniHashtableClear( struct NunniHashtable *ht, int freeup );


/* the callback functions */
struct NunniMCAXContentHandler {
  int (*startDocument)(void);
  int (*startElement)( const char *tagname, struct NunniHashtable *args );
  int (*characters)( char ch[], int start, int length );
  int (*endElement)( const char *tagname );
  int (*endDocument)(void);
};


/* the parser interface to the user */
int NunniMCAXparse( int (*getcFunc)(void), struct NunniMCAXContentHandler *handler );
int NunniMCAXparseStr( const char *xmldoc, int doclen, struct NunniMCAXContentHandler *handler );


#ifdef __cplusplus
}
#endif		/* __cplusplus */


#endif
