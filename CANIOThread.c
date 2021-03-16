/*****************************************************************************
 * FILE NAME    : CANIOThread.c
 * DATE         : January 17 2019
 * PROJECT      : Bay Simulator
 * COPYRIGHT    : Copyright (C) 2019 by Vertiv Company
 *****************************************************************************/
#define _POSIX_C_SOURCE 200809L

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <ascii.h>
#include <unistd.h>
#include <pthread.h>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "CANInterface.h"
#include "CANIOThread.h"
#include "UserInterfaceServer.h"

/*****************************************************************************!
 * Local Macros
 *****************************************************************************/
#define MAIN_CAN_INTERFACE_NAME "slcan0"
#define SLEEP_MSEC				17

/*****************************************************************************!
 * Imported Data
 *****************************************************************************/
void
ProcessInputMessage
(CANMessage* InMessage);

/*****************************************************************************!
 * Local Data
 *****************************************************************************/
bool
CANWriteDisplayPacket = false;

CANInterface*
canInterface;

pthread_t
CANIOThreadID;

/*****************************************************************************!
 * Local Functions
 *****************************************************************************/
extern int
usleep(useconds_t);

void
CANWriteSend
(CANMessage* InMessage);

/*****************************************************************************!
 * Function : CANIOThreadInit
 *****************************************************************************/
void
CANIOThreadInit
()
{
}

/*****************************************************************************!
 * Function : CANIOThreadGetID
 *****************************************************************************/
pthread_t
CANIOThreadGetID
()
{
  return CANIOThreadID;
}

/*****************************************************************************!
 * Function : CANIOThreadStart
 *****************************************************************************/
void
CANIOThreadStart
()
{
  CANInterface*							interface;

  interface = CANInterfaceInit(MAIN_CAN_INTERFACE_NAME);
  if ( pthread_create(&CANIOThreadID, NULL, CANIOThread, interface) ) {
	fprintf(stderr, "Could not start CAN IO Thread\n");
	exit(EXIT_FAILURE);
  }
  fprintf(stderr, "Start CAN IO Thread\n");
  UserInterfaceServerStart();
}

/*****************************************************************************!
 * Function : CANIOThread
 *****************************************************************************/
void*
CANIOThread
(
 void*                                  InParameters
)
{
  CANMessage                            message;
  int                                   returnValue;
  uint64_t								data = 1;

  canInterface = (CANInterface*)InParameters;
  while (true) {
    returnValue = CANInterfaceReadTimeout(canInterface, &message.id.dword, &message.data.qword, &message.dataLength, 0);
    if ( returnValue == CAN_READ_OK ) {
      ProcessInputMessage(&message);
    }
	message.id.dword = 1;
	message.data.qword = data++;
	message.dataLength = 8;
	CANWriteSend(&message);
    usleep(SLEEP_MSEC * 1000);
  }
}

/*****************************************************************************!
 * Function : CANWriteSend
 *****************************************************************************/
void
CANWriteSend
(
 CANMessage*                            InMessage
)
{
  if ( NULL == InMessage ) {
    return;
  }
  CANInterfaceWrite(canInterface, InMessage->id.dword, InMessage->data.qword, InMessage->dataLength);
}

/*****************************************************************************!
 * Function : CANIOThreadStop
 *****************************************************************************/
void
CANIOThreadStop
()
{
  CANInterfaceClose(canInterface);
  pthread_cancel(CANIOThreadID);
}

/*****************************************************************************!
 * Function : CANIOThreadRestart
 *****************************************************************************/
void
CANIOThreadRestart
()
{
  CANInterface*                 interface;

  CANIOThreadStop();
  CANInterfaceReset();
  interface = CANInterfaceInit(MAIN_CAN_INTERFACE_NAME);
  pthread_create(&CANIOThreadID, NULL, CANIOThread, interface);
}

/*****************************************************************************!
 * Function : ProcessInputMessage
 *****************************************************************************/
void
ProcessInputMessage
(CANMessage* InMessage)
{
}
