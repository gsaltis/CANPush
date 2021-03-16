/*****************************************************************************
 * FILE NAME    : CANIOThread.h
 * DATE         : January 17 2019
 * PROJECT      : Bay Simulator
 * COPYRIGHT    : Copyright (C) 2019 by Vertiv Company
 *****************************************************************************/
#ifndef _caniothread_h_
#define _caniothread_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Type : CANMessage
 *****************************************************************************/
struct _CANMessage
{
  union {
	uint32_t							dword;
  } id;

  union {
	uint64_t							qword;
  } data;
  uint8_t								dataLength;
};
typedef struct _CANMessage CANMessage;

/*****************************************************************************!
 * Exported Data
 *****************************************************************************/

/*****************************************************************************!
 * Exported Functions
 *****************************************************************************/
void*
CANIOThread
(void* InParameters);

void
CANIOThreadInit
();

void
CANIOThreadRestart
();

pthread_t
CANIOThreadGetID
();

void
CANIOThreadStart
();

#endif /* _caniohread_h_*/
