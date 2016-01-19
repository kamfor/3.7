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
######Katalog prezenterow (analogicznie prezentacji)
```C
typedef struct {
	char name[20]; //nazwa katalogu
	int presenters[20]; //tablica identyfikatorow prezewnterow lub prezentacji
	int amount; //licznik ilosci danych w tablicy
}CatPresenter;
```
####Dodatkowe zmienne
```C
Presenter *tabPr; //wskaznik na tablice prezenterow
Presentation *tabPn; //wskaznik na tablice prezentacji
CatPresenter *catPr; //wskaznik na tablice katalogow prezenterow
CatPresentation *catPn; //wskaznik na tablice katalogow prezentacji
int PresenterCounter; //zmienna aktualnej ilosci prezenterow
int PresentationCounter; //zmienna aktualnej ilosci prezentacji
int CatPresenterCounter; //zmienna aktualnej ilosci katalogow prezenterow 
int CatPresentationCounter; //zmienna aktualnej ilosci katalogow prezentacji
char buff[100]; //bufor danych wejsciowych
```

###Funkcje 
Program bazuje na instrukcji switch ktora uruchamia poszczegolne funkcje odpowiedzialne za mainpulacje danymi sa to:
```C
void ClearScreen(); // czyszczenie konsoli
void AddNewPresenter(); //dodawanie nowego prezentera
void AddNewPresentation(); //dodawanie nowej prezentacji
void CreateCatPresenter(); //tworzenie katalogu prezenterow
void CreateCatPresentation(); //tworzenie katalogu prezentacji
void DeletePresenter(); //usuwanie rekordu z tablicy prezenterow
void DeletePresentation(); //usuwanie rekordu z tablicy prezentacji
void UpdatePresenter(); //edycja istniejacego prezentera
void UpdatePresentation(); //edycja istniejacej prezentacji
void PrintPresenterTable(int); //wyswietlenie rekordow w danym porzadku sortowania
void PrintPresentationTable(int);//-//-
void PrintCatPresenter(); //wyswietlenie katalogow prezenterow
void PrintCatPresentation(); //wyswietlenie katalogow prezentacji
void PrintMenu(); //wyswietlenie menu programu
int Exit(); //funkcja czyszczaca zaalokowana pamiec i wychodzaca z programu
int StringhiCheck(char*); //sprawdzanie danych wejsciowych, funkcja zwraca liczbe odpowiadajaca rodzjajowi znakow z bufora
// funkcje porownujace odpowiadajace roznym porzadkom prezentacji
int ComparePresenterName(const void *,const void *); // wedlug Imienia
int ComparePresenterSurname(const void *,const void *); wedlug Nazwiska
int ComparePresenterAffiliation(const void *,const void *); wedlug afiliacji
int ComparePresenterGen(const void *,const void *); //wedlug rodzaju
int ComparePresenterPayment(const void *,const void *); //wedlug rodzaju platnosci
int ComparePresenterPresentations(const void *,const void *); //wedlug ilosci prezentacji
int ComparePresentationName(const void *,const void *); //wedlug nazwy prezentacji
int ComparePresentationType(const void *,const void *); //wedlug typu prezentacji
```
sortowanie tablicy rekordow wykorzystuje funkcje qsort(); jako jej paramtery podawane sa: tablica id prezenterow lub prezentacji oraz wskaznik na funkcje porownujaca w zaleznosci od porzadku sortowania np: 
```C
if(sortorder==1)qsort(tab,PresenterCounter,sizeof(int),ComparePresenterName);//sortowanie wg. Imienia Prezentera
```
Pobieranie danych realizowane jest wedlug nastepujacego wzoru:
```C
do{ 
	printf("Wpisz imie prezentera\n");
	scanf("%s", &buff); //pobranie danych do bufora
	if(StringCheck(buff)==2)strcpy(temp->name, buff); //jezeli zawartosc bufora zawiera wielka litere i reszte malych to nastepuje skopiowanie do pola w strukturze
	else printf("bledne imie\n"); 
}while(StringCheck(buff)!=2); //ykonuj dopuki zostana wprowadzone poprawne dane
```
Alokacja pamieci przebiega wedlug schematu:
```C
int actmem[] = {20,20,10,10};//tablica dla pierwszej alokacji
tabPr = calloc(actmem[0], sizeof(Presenter)); //alokacja i zerowanie pamieci dla tablicy struktur
tabPn = calloc(actmem[1], sizeof(Presentation)); 
catPr = calloc(actmem[2], sizeof(CatPresenter)); 
catPn = calloc(actmem[3], sizeof(CatPresentation)); 
...
if(CatPresentationCounter==actmem[3]){//jezeli tablica jest zalelniona to zwieksz ilosc pamieci *2 
	actmem[3]*=2; 
	if((tmp = realloc(catPn, sizeof(CatPresentation) * actmem[3])) == NULL ){
		printf("przykro mi nie udalo sie zaalokowac pamieci\n"); 
		break; 
	}
	else catPn = tmp; 
}
```
Funkcje sa wywolywane w main za pomoca instrukcji switch i zmiennej sterujacej control np:
```C
switch(control){
	case 0:
		if(Exit())return 0; 
	break; 	
}
```
