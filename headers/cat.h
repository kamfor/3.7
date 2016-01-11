#ifndef CAT_H_INCLUDED
#define CAT_H_INCLUDED

#include <stdio.h>
#include "list.h"

typedef struct Cat{
	char name[64];
	char type[32];
	List listofelements; 
}Cat; 

void PrintCatHeader(FILE*); 
int PrintCat(Cat*, FILE*); 
int AddToCat(void*, Cat*); 
void PrintCatTable(FILE*); 
List * FindInCats(char*); 
Cat * AddCat(char*); 
#endif


