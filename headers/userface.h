#ifndef USERFACE_H_INCLUDED
#define USERFACE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef enum msgtype {
	WELCOME,
	CLEAR, 
	MAINMENU,
	FILE_OPEN_ERR,
	FILE_OPEN_SUCCES,
	FILE_READ_ERR, 
	CREATE_FILE_PROMPT,
	CREATE_FILE_SUCCES,
	CREATE_FILE_ERR,
	PRESENTER_ADD,
	PRESENTER_ADD_SUCCES,
	PRESENTER_NEXIST, 
	PRESENTATION_ADD,
	PRESENTATION_ADD_SUCCES,
	PRESENTATION_NEXIST,
	INPUT_ERR, 
	INIT_ERR,
	DEL_ERR,
	ADD_ERR	
}msgtype;


void DataInit(); 
void Begin(); 
int Exit(); 
int ReadFromStd();
void Msg(msgtype, int); 
#endif 
