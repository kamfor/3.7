#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "userface.h"
#include "containers.h"
#include "cat.h"

FILE *CreateBin(char*,FILE*);
FILE *CreateRaw(char*,FILE*);
FILE *OpenBin(char*,FILE*);
FILE *OpenRaw(char*,FILE*);
int SaveBin(char*,FILE*);
int SaveRaw(FILE*);
int LoadBin(char*,FILE*);
int LoadRaw(FILE*);
void PrintFileHeader(FILE*);
void PrintPresenterHeader(FILE*);
void PrintPresentationHeader(FILE*);
char *hash(char*);
#endif
