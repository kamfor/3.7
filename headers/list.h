#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "userface.h" 

typedef struct Element {
	struct Element *prev;
	struct Element *next; 
	void *obj; 
} Element;	

typedef struct List {
	Element *head; 
	Element *tail;
	int lenght; 
} List; 
	

int addnode(void*, List*); 
int delnode(Element*,List*); 
int dellist(List*); 

#endif

