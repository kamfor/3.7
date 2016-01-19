# 3.7
##Wspomaganie organizacji konferencji
Program pozwala na dodawanie i edycje danych o prezenterach i prezentacjach. Dane przechowywane sa w tablicach struktur. Kod zrodlowy znajduje sie w plikach *.c oraz w folderze source. Baze danych mozna wczytac z pliku tekstowego lub binarnego chronionego haslem i zapisac dane do obu typow plikow. 
###Struktura listy:
```C
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
	
int addnode(void*, List*); \*dodawanie elementu do listy*\
int delnode(Element*,List*); \*usuwanie elementu z listy*\
int dellist(List*); \*usuwanie listy*\
```
###Typy danych:
######Prezenter
```C
typedef struct Presenter {
	char name[64];
	char surname[64];
	char affiliation[128];
	char gen; /*0-brak 1-ustne 2-plakat*/
	char payment; /*0-brak 1-zaplacono*/
	char pn[8];
	List presentations;
} Presenter;
```
######Prezentacja
```C
typedef struct Presentation {
	char name[64];
	char type;/*0-ustna 1-plakat*/
	char pn[8];
	Presenter *owner;
} Presentation;
```
######Katalog
```C
typedef struct Cat{
	char name[64];
	char type; /*0 -presenters 1-presentations*/
	List listofelements;
}Cat;
```

###Funkcje 
#####Obsluga plików

```C
FILE *CreateBin(char*,FILE*);
int CreateRaw(char*,FILE*);
int OpenBin(char*,FILE*);
int OpenRaw(char*,FILE*);
int SaveBin(char*,FILE*);
int SaveRaw(FILE*);
int LoadBin(char*,FILE*);
int LoadRaw(FILE*);
```
#####Interfejs użytkownika
Interfejs użytkownika oparty jest o funkcję 
```C
void Msg(msgtype, int);
```
Oraz typu wyliczeniowego zawierającego możliwe typy komunikatów
```C
typedef enum msgtype {
	WELCOME,
	CLEAR,
	MAINMENU,
	FILE_MENU,
	FILE_OPEN_ERR,
        /*etc.*/
}msgtype;
```
Przykładowe użycie funkcji
```C
if(LoadRaw(filetemp))Msg(FILE_READ_ERR,0);/*informacja o błędzie odczytu pliku*/
```
Za pobieranie danych od użytkownika odpowiadają dwie funkcje:
```C
int ReadFromStd();/*funkcja zwraca pobraną od użytkownika zmienną liczbową i ją zwraca*/
char *ReadData(char*);/*funkcja zwraca pobrany od użytkownika ciąg znaków*/
```
