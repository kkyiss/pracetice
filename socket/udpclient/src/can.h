#ifndef SRC_CAN_H_
#define SRC_CAN_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "config/global.h"

//error code
#define ERROR_SOCKCREATE    -2
#define ERROR_SENDTO        -3
#define ERROR_RECVFROM      -4
#define ERROR_CHECKVALID    -5
#define ERROR_TIMEOUT		-6
#define ERROR_BUFF_SIZE		-7

void canInit();
int canRun();
int canGetErrorMsg(int num, char* buf, int bufLen);
int canGetTestCondition(char* buf, int bufLen);
void canRelease();
int checkValid(int uid, char *recvMsg);
int checkBuf(int bufLen,char* str);


#endif /* SRC_CAN_H_ */
