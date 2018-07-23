#include <stdio.h>
#include <stdlib.h>
#include "can.h"

#define BUFFLEN 80

int main(void) {
	char buff[BUFFLEN];

	canInit();
	int state = canRun();

	canGetErrorMsg(state,buff,BUFFLEN);
	//printf("errno is: %s\n", buff);

	canGetTestCondition(buff,BUFFLEN);
	//printf("condition: %s",buff);
	canRelease();


	return EXIT_SUCCESS;
}
