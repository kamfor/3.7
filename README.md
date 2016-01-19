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
Pobrane dane tekstowe w postaci komend są dzielone na słowa przy pomocy funkcji strtok()
A następnie w zależności od podanej pozycji menu interpretowane przez funkcje organizacyjne.
Ich deklaracje przedstawione są poniżej: 
```C
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
```
Funkcje odpowiadają bezpośrednio realizacji danego elementu z menu programu. 
Korzystają one z niskopoziomowych funkcji odpowiedzialnych za realizację malych elementów. 
Opis funkcji niskopoziomowych znajduje się niżej. 
Ostatnią istotną funkcją interfejsu użytkownika jeat funkcja interpretacji komend obsługi plików
```C
int CommandParse(char*);
```
Funkcja ta dzleli pobraną komendę na słowa a następnie dzieli nazwę pliku na nazwę i rozszerzenie poprzez separator "." Funkcja wykonuje operację na plikach w zależności od komendy (odczytać/zapisz) (nazwa pliku.rozszerzenie) (hasło dla pliku binarnego) 

#####Funkcje niskopoziomowe
Poniższe funkcję odpowiadają za obsługę bazy danych
```C
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
```
Pozostają jeszcze funkcje odpowiedzialne za obsługę katalogów
```C
void PrintCatHeader(FILE*);
int PrintCat(Cat*, FILE*);
int AddToCat(void*, Cat*);
void PrintCatTable(FILE*);
List *FindInCats(char*);
Cat *AddCat(char*);
```
#####Sortowanie
Sortowanie danych polega na zapisaniu danej listy do tablicy wskaźników i następnie posortowania jej przy pomocy funkcji qsort() oraz jednej z poniższych funkcji porownujacych: 
```C
int ComparePresenterName(const void*, const void*);
int ComparePresenterSurname(const void*, const void*);
int ComparePresenterAffiliation(const void*, const void*);
int ComparePresenterGen(const void*, const void*);
int ComparePresenterPayment(const void*, const void*);
int ComparePresenterPresentations(const void*, const void*);
int ComparePresentationName(const void*, const void*);
int ComparePresentationType(const void*, const void*);
```
Przykład ciała jednej z podanych funkcji sortujacych:
```C
int ComparePresenterName (const void * a, const void * b){

	int x = *(int*)a;
	int y = *(int*)b;
	return strcmp(tabPr[x]->name,tabPr[y]->name);
}
```
#####Alokacja pamięci
Pamięć jest złomowania osobno dla każdego elementu listy. Wskaźniki na początek list są zmiennymi globalnymi że względu na częste wykorzystanie. 
```C
/*przykładowa alokacja pamięci*/
Presenter *newpresenter;
newpresenter=calloc(1,sizeof(Presenter));/*użycie funkcji calloc() ze względu na zeriowanie pamięci*/
if(newpresenter==NULL)return NULL;
```
Przy wyjściu z programu pamięć jest uwalniana w funkcji exit():
```C
int Exit(){

	Element * temp;
	temp = listofpresenters.head;
	while(temp!=NULL){

		if(delnode(temp,&listofpresenters))return 1;
		temp = temp->next;
	}
	if(dellist(&listofpresenters))return 1;
	temp = listofpresentations.head;
	while(temp!=NULL){

		if(delnode(temp,&listofpresentations))return 1;
		temp = temp->next;
	}
	if(dellist(&listofpresentations))return 1;
	temp = listofcatalogues.head;
	while(temp!=NULL){

		if(delnode(temp,&listofcatalogues))return 1;
		temp = temp->next;
	}
	if(dellist(&listofcatalogues))return 1;

	free(tabPr);
	free(tabPn);
	free(buffer);
	return 0;
}
'''
###Main
Funkcja main wywołuje funkcję uruchamiającą interfejs użytkownika dodatkowo pozwala na uruchomienie trybu debugowania w tym celu należy zmienić makro definicję DEBUG na 1
```C
#define DEBUG 0

int main(){

	if(DEBUG)Debug();
	else Begin();
	return 0;
}
```
###Struktura plików z danymi 
