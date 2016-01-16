#ifndef USERFACE_H_INCLUDED
#define USERFACE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "file.h"


typedef enum msgtype {
	WELCOME,
	CLEAR,
	MAINMENU,
	FILE_MENU,
	FILE_OPEN_ERR,
	FILE_OPEN_SUCCES,
	FILE_READ_ERR,
	FILE_READ_SUCCES,
	CREATE_FILE_PROMPT,
	CREATE_FILE_SUCCES,
	CREATE_FILE_ERR,
	PRESENTER_ADD,
	PRESENTER_ADD_SUCCES,
	PRESENTER_DEL,
	PRESENTER_DEL_SUCCES,
	PRESENTER_NEXIST,
    PRESENTER_CHANGE,
    PRESENTER_CHANGE_SUCCES,
	PRESENTER_CHANGE_NEXT,
	PRESENTER_CHANGE_ERR,
	PRESENTER_PRINT_TABLE,
	PRESENTER_PRINT_SORTORDER_LIST,
	PRESENTATION_ADD,
	PRESENTATION_ADD_SUCCES,
	PRESENTATION_DEL,
	PRESENTATION_DEL_SUCCES,
	PRESENTATION_NEXIST,
	PRESENTATION_CHANGE,
    PRESENTATION_CHANGE_SUCCES,
	PRESENTATION_CHANGE_NEXT,
	PRESENTATION_CHANGE_ERR,
    PRESENTATION_PRINT_TABLE,
	PRESENTATION_PRINT_SORTORDER_LIST,
	CAT_ADD,
	CAT_ADD_NEXT,
    CAT_ADD_ERR,
    CAT_ADD_SUCCES,
    CAT_PRINT_TABLE,
	INPUT_ERR,
	MENU_ERR,
	INIT_ERR,
	DEL_ERR,
	ADD_ERR,
	WELCOME_PROMPT,
	BIN_ERR,
	RAW_ERR,
	MENU_PROMPT,
	ADD_NEXT,
	DEL_NEXT,
	PRES_ADD_ERR,
	SEARCH,
	SEARCH_ERR,
	SEARCH_NEXT,
	CONTINUE
}msgtype;


void DataInit();
void Begin();
int Exit();
int ReadFromStd();
char *ReadData(char*);
void Msg(msgtype, int);

void UserPresenterAdd();
void UserPresentationAdd();
void UserCatalougeAdd();
void UserPresenterDel();
void UserPresentationDel();
void UserPresenterUpdate();
void UserPresentationUpdate();
void UserPresenterPrintTable();
void UserPresentationPrintTable();
void UserPrintCatTable();
void UserFileHandling();
void UserSearch();
int CommandParse(char*);

#endif
