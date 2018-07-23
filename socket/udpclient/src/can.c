#include "can.h"

#define SER_ADDR "192.168.0.3"
#define HOST_ADDR "192.168.0.6"
#define PORT 4030
#define CAN "CAN_001"
#define BUFFLEN 256

struct canInfo{
	char desAddr[20];
	char hostAddr[20];
	int port;
	char can[25];
	int uid;
};

static struct canInfo *info;

void canInit(){

	// malloc struct canInfo
	info = (struct canInfo *)malloc(sizeof(struct canInfo));

	// host ip
	strcpy(info->hostAddr, HOST_ADDR);

	// server ip
	strcpy(info->desAddr,SER_ADDR);
	info->port = PORT;

	// can number
	strcpy(info->can,CAN);

	// srand msg
	srand(time(NULL));
	info->uid = rand();

}

int canRun(){
	// timeout 100ms
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 100000;

	// create UDP socket
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock < 0){
		return ERROR_SOCKCREATE;
	}

	// socket connection
	struct sockaddr_in sockinfo, hostinfo;
	socklen_t addrLen = sizeof(struct sockaddr_in);
	memset(&sockinfo, 0, sizeof(sockinfo));
	memset(&hostinfo, 0, sizeof(hostinfo));

	// host ip setting
	hostinfo.sin_family=AF_INET;
	hostinfo.sin_addr.s_addr = inet_addr(info->hostAddr);
	hostinfo.sin_port = htons(info->port);
	bind(sock, (struct sockaddr *)&hostinfo, sizeof(hostinfo));

	// VIU IP setting
	sockinfo.sin_family=AF_INET;
	sockinfo.sin_addr.s_addr = inet_addr(info->desAddr);
	sockinfo.sin_port = htons(info->port);

	// sent msg "uid,CAN_001"
	char msg[BUFFLEN];
	char recvMsg[BUFFLEN];
	sprintf(msg,"%d,%s", info->uid, info->can);

	// set sendto timeout
	if (setsockopt (sock, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv)) < 0){
		return ERROR_TIMEOUT;
	}

	if(sendto(sock,msg,strlen(msg), 0, (struct sockaddr *)&sockinfo, addrLen) < 0){
		return ERROR_SENDTO;
	}

	// set recvfrom timeout
	if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0) {
		return ERROR_TIMEOUT;
	}

	if(recvfrom(sock, recvMsg, (socklen_t)BUFFLEN, 0, (struct sockaddr *)&sockinfo, &addrLen) < 0){
		return ERROR_RECVFROM;
	}

	// compare uid integrity
	if(checkValid(info->uid,recvMsg) < 0){
		close(sock);
		return ERROR_CHECKVALID;
	}

    printf("close Socket\n");
    close(sock);

    return PASS;
}

int checkValid(int uid, char *recvMsg){
	char *delim = ",";
	char *ptr = strtok(recvMsg,delim);

	// str splitrecvfrom
//	char *c;
//	while(ptr != NULL){
//		c = ptr;
//		ptr = strtok(NULL,delim);
//	}
//
//	int checkNum = atoi(c);
	int checkNum = atoi(ptr);
	if(uid != checkNum){
		return FAIL;
	}

	return PASS;
}

int canGetErrorMsg(int num, char* buf, int bufLen){
// get error message
	memset(buf, 0, bufLen);
	switch(num){
		case -1:
			if(checkBuf(bufLen,"Error") < 0)return ERROR_BUFF_SIZE;
			strcpy(buf,"Error");
			break;
		case -2:
			if(checkBuf(bufLen,"Error socket created") < 0)return ERROR_BUFF_SIZE;
			strcpy(buf,"Error socket created");
			break;
		case -3:
			if(checkBuf(bufLen,"No route to host") < 0)return ERROR_BUFF_SIZE;
			strcpy(buf,"No route to host");
			break;
		case -4:
			if(checkBuf(bufLen,"Error receive") < 0)return ERROR_BUFF_SIZE;
			strcpy(buf,"Error receive");
			break;
		case -5:
			if(checkBuf(bufLen,"UID different") < 0)return ERROR_BUFF_SIZE;
			strcpy(buf,"UID different");
			break;
		case -6:
			if(checkBuf(bufLen,"Error timeout") < 0)return ERROR_BUFF_SIZE;
			strcpy(buf,"Error timeout");
			break;
		case -7:
			if(checkBuf(bufLen,"Error buffsize") < 0)return ERROR_BUFF_SIZE;
			strcpy(buf,"Error buffsize");
			break;
	}

	return strlen(buf);
}

int canGetTestCondition(char* buf,int bufLen){
// return can id
	// check buff size
	if(checkBuf(bufLen,info->can) < 0)return ERROR_BUFF_SIZE;

	memset(buf, 0, strlen(buf));
	strcpy(buf,info->can);
	return strlen(buf);
}

void canRelease(){
// free malloc
	free(info);
}

int checkBuf(int bufLen,char* str){
	int strLen = strlen(str);

	if(bufLen < strLen){
		printf("buf size is too small.");
		return FAIL;
	}

	return PASS;
}


