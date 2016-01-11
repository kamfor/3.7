#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "userface.h"
#include "containers.h"
#include "cat.h"

int CreateBin();
int CreateRaw();
int OpenBin();
int OpenRaw();
int SaveBin();
int SaveRaw();
int LoadBin();
int LoadRaw();
int CheckPasswd(char*,char*);
void PrintFileHeader();
void PrintPresenterHeader(FILE*);
void PrintPresentationHeader(FILE*);
#endif
