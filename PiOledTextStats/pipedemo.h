/*
***************************************************************************
* pipedemo - demo pipe open for unix commands
* 2021-01-23 JBS Created
*
*
*
*
*
***************************************************************************
*/


#ifndef BOOL
    #define BOOL
    #define FALSE 0
    #define TRUE -1
#endif


#ifndef PIPEDEMO_H_INCLUDED
#define PIPEDEMO_H_INCLUDED
#endif

/* Function Prototypes  */

int runCmd(char * qcmd, char * qreturn);

/* End of pipedemo.h    */
