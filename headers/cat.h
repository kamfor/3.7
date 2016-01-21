#ifndef CAT_H_INCLUDED
#define CAT_H_INCLUDED

#include <stdio.h>
#include <ctype.h>
#include "list.h"
#include "containers.h"
#include "userface.h"

typedef struct Cat{
	char name[64];
	char type; /*0 -presenters 1-presentations*/
	List listofelements;
}Cat;

void PrintCatHeader(FILE*);
int PrintCat(Cat*, FILE*);
int AddToCat(Element*, Cat*);
void PrintCatTable(FILE*);
List *FindInCats(char*);
Cat *AddCat(char*);
#endif



