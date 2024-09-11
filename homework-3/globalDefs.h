/*
 * Program: globalDefs.h
 * Name: Mark Erle
 * UID: merle
 *
 * DO NOT EDIT THIS FILE
 */

#ifndef GLOBALDEFS_H
#define GLOBALDEFS_H

#define NUM_BYTES_TO_COPY_AT_A_TIME 1013
#define MSG_LENGTH 16

union quadByteUnion {
  int i;
  char c[4];
};
typedef union quadByteUnion qbu_t;  /* pronounced "q but" */
    
#endif
