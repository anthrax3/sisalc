/**************************************************************************/
/* FILE   **************      AssignNewLoop.c      ************************/
/**************************************************************************/
/* Author: Dave Cann                                                      */
/* Update: Patrick Miller -- Ansi support (Dec 2000)                      */
/* Copyright (C) University of California Regents                         */
/**************************************************************************/
/**************************************************************************/

#include "world.h"


/**************************************************************************/
/* GLOBAL **************    AssignNewLoopTports    ************************/
/**************************************************************************/
/* PURPOSE: ASSIGN NEW T PORT NUMBERS, STARTING WITH p, TO THE IMPORTS OF */
/*          LOOP l'S BODY SUBGRAPH AND ADJUST ALL REFERENCES. THE NEXT    */
/*          LEGAL PORT IS RETURNED.                                       */
/**************************************************************************/

int AssignNewLoopTports( p, l )
int   p;
PNODE l;
{
  register PEDGE i;
 if (l->L_BODY != NULL)
    {
      for ( i = l->L_BODY->imp; i != NULL; i = i->isucc )
        if ( (!l->L_INIT) && (!i) && (!IsImport( l->L_INIT, i->iport )) ) {
          if ( (l->L_TEST) && (i->iport != p )) {
            ChangeExportPorts( l->L_TEST, i->iport, -p );
            i->iport = -p;
          }
          
          p++;
        }
    }
  return( p );
}

/*
 * $Log: AssignNewLoop.c,v $
 * Revision 1.2  2001/01/02 09:16:45  patmiller
 * Now ANSI compliant, but still a pthread problem
 *
 * Revision 1.1.1.1  2000/12/31 17:58:11  patmiller
 * Well, here is the first set of big changes in the distribution
 * in 5 years!  Right now, I did a lot of work on configuration/
 * setup (now all autoconf), breaking out the machine dependent
 * #ifdef's (with a central acconfig.h driven config file), changed
 * the installation directories to be more gnu style /usr/local
 * (putting data in the /share/sisal14 dir for instance), and
 * reduced the footprint in the top level /usr/local/xxx hierarchy.
 *
 * I also wrote a new compiler tool (sisalc) to replace osc.  I
 * found that the old logic was too convoluted.  This does NOT
 * replace the full functionality, but then again, it doesn't have
 * 300 options on it either.
 *
 * Big change is making the code more portably correct.  It now
 * compiles under gcc -ansi -Wall mostly.  Some functions are
 * not prototyped yet.
 *
 * Next up: Full prototypes (little) checking out the old FLI (medium)
 * and a new Frontend for simpler extension and a new FLI (with clean
 * C, C++, F77, and Python! support).
 *
 * Pat
 *
 *
 * Revision 1.2  1994/03/03  17:13:58  solomon
 * Added some tests to help prevent failing when dealing with invalid
 * if1 code.
 *
 * Revision 1.1  1993/04/16  18:59:46  miller
 * Name shortening to keep the archiver from truncating names in Backend/Library
 * Since some names were changed, other files were affected.  All names in the
 * library now start with no more than 13 (unique) characters.
 *
 * Revision 1.1  1993/01/21  23:27:51  miller
 * Initial version of the IFX library.  It replaces the if[12]build.c
 * read.c timer.c util.c and write.c and if[12].h files from the
 * backend phases.
 *
 */
