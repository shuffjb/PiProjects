#include <stdio.h>
#include <string.h>
#include "pipedemo.h"
#define BUFSIZE 128

int runCmd(char * qcmd, char * qreturn)  {
    /*char cmd[BUFSIZE];
     * sprintf(cmd, qcmd);  
     */  

    char buf[BUFSIZE];
    FILE *fp;

    if ((fp = popen(qcmd, "r")) == NULL) {
        printf("Error opening pipe!\n");
        return -1;
    }

    while (fgets(buf, BUFSIZE, fp) != NULL) {
        // Do whatever you want here...
        // printf("OUTPUT: %s", buf);
        strcpy(qreturn, buf);        /* put output of cmd in return */
    }

    if(pclose(fp))  {
        printf("Command not found or exited with error status\n");
        return -1;
    }

    return 0;
}




