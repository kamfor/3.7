#ifndef CONTAINERS_H_INCLUDED
#define CONTAINERS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "list.h"
#include "userface.h"
#include "cat.h"

typedef struct Presenter {
	char name[64];
	char surname[64];
	char affiliation[128];
	char gen; /*0-brak 1-ustne 2-plakat*/
	char payment; /*0-brak 1-zaplacono*/
	char pn[8];
	List presentations;
} Presenter;

typedef struct Presentation {
	char name[64];
	char type;/*0-ustna 1-plakat*/
	char pn[8];
	Presenter *owner;
} Presentation;


Presenter *AddPresenter(char*);
Presentation *AddPresentation(char*);
Element *FindPresenter(char*, List*);
Element *FindPresentation(char*, List*);
int DeletePresenter(Element*);
int DeletePresentation(Element*);
int UpdatePresenter(Presenter*,char *);
int UpdatePresentation(Presentation*,char *);
void PrintPresenterFile(FILE*);
void PrintSortedPresenterTable(int);
void PrintPresenterLine(Presenter*,FILE*);
void PrintPresentationFile(FILE*);
void PrintSortedPresentationTable(int);
void PrintPresentationLine(Presentation*,FILE*);
void PrintPresenterIdTable();
void PrintPresentationIdTable();
/*compare function*/
int ComparePresenterName(const void*, const void*);
int ComparePresenterSurname(const void*, const void*);
int ComparePresenterAffiliation(const void*, const void*);
int ComparePresenterGen(const void*, const void*);
int ComparePresenterPayment(const void*, const void*);
int ComparePresenterPresentations(const void*, const void*);
int ComparePresentationName(const void*, const void*);
int ComparePresentationType(const void*, const void*);

#endif
