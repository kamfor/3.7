#include "../headers/userface.h"

extern List listofpresenters; 
extern List listofpresentations; 

int Exit(){

	int i;
	Element * temp; 
	temp = listofpresenters.head; 
	while(temp!=NULL){
	
		if(delnode(temp,&listofpresenters))return 1;  	
	}
	if(dellist(&listofpresenters))return 1; 
	temp = listofpresentations.head; 
	while(temp!=NULL){
	
		if(delnode(temp,&listofpresentations))return 1;  	
	}
	if(dellist(&listofpresentations))return 1; 

	return 0; 	
}

int ReadFromStd(){
	char line[256]; 
	fgets(stdin,256, line); 
	if(atoi(line)>=0&&atoi(line)<16)return atoi(line); 
}

void Msg(msgtype message, int position){
	
	switch(message){

	case WELCOME:
	printf("WITAMY W PROGRAMIE\n");
	break; 
	
	case CLEAR:
	printf("\033[2J"); 
	printf("\033[0;0f");
	break; 

	case MAINMENU:
	printf("-----------------------------------------------------------------------------------------\n");
	printf("--------------------------WSPOMAGANIE ORGANIZACJI KONFERENCJI----------------------------\n");
	printf("-----------------------------------------------------------------------------------------\n");
	printf("-Wpisz 1 aby dodac prezentera          - wpisz 9 aby wyswietlic liste prezenterow       -\n");
	printf("-Wpisz 2 aby dodac prezentacje         - wpisz 10 aby wyswietlic liste prezentacji      -\n");
	printf("-Wpisz 3 aby usunac prezentera         - wpisz 11 aby wyswietlic liste kat. prezentacji -\n");
	printf("-Wpisz 4 aby usunac prezentacje        - wpisz 12 aby wyswietlic liste kat.prezenterow  -\n");
	printf("-Wpisz 5 aby dodac katalog prezenterow - wpisz 13 aby edytowac haslo dostepu            -\n");
	printf("-Wpisz 6 aby dodac katalog prezentacji - wpisz 14 aby wyszukac prezentera               -\n");
	printf("-Wpisz 7 aby edytowac prezentacje      - wpisz 15 aby wyszukac prezentacje              -\n");
	printf("-Wpisz 8 aby edytowac prezentera       - wpisz 0 aby zakonczyc                          -\n");
	printf("-----------------------------------------------------------------------------------------\n");
	break; 

	case FILE_OPEN_ERR:
	printf("Blad otwarcia pliku \n"); 
	break; 

	case FILE_OPEN_SUCCES:
	printf("Pomyslnie otwarto plik \n"); 
	break; 

	case FILE_READ_ERR:
	printf("Blad odczytu pliku \n"); 
	break; 

	case CREATE_FILE_PROMPT:
	printf("Czy chcesz utworzyc plik ? \n");
	break; 

	case CREATE_FILE_SUCCES:
	printf("Pomyslnie utworzono plik \n"); 
	break; 
	
	case CREATE_FILE_ERR:
	printf("Blad przy tworzeniu pliku \n"); 
	break; 
	
	case PRESENTER_ADD:
	printf("Wpisz w w linii IMIE, NAZWISKO, AFILIACJE, RODZAJ WYSTAPIENIA(0-brak 1-plakat 2-ustne)");
	printf("oraz STATUS PLATNOSCI (0-brak 1-zaplacono). Pozycje rodziel uzywajac srednika \n"); 
	printf("Np: Jan;Kowalski;Uniwersytet 3-go wieku;1;0; \n"); 
	break; 

	case PRESENTER_ADD_SUCCES:
	printf("Pomyslnie dodano prezentera do bazy danych \n"); 
	break; 

	case PRESENTATION_ADD:
	printf("Wpiszw linii NZAWE, TYP(0-plakat 1-ustne) oraz ID prezentera z listy poniżej: \n");
	printf("Pozycje rodzeiel srednikiem: Np: Swietna prezentacja;0;0234 \n"); 
	break; 
	
	case PRESENTATION_ADD_SUCCES:
	printf("Pomyslnie dodano prezentacje do bazy danych \n"); 
	break; 

	case PRESENTER_NEXIST:
	printf("Prezenter o podanym numerze nie istnieje \n"); 
	break; 

	case PRESENTATION_NEXIST:
	printf("Prezentacja o podanym numerze nie istnieje \n"); 
	break; 

	case INPUT_ERR:
	printf("Blad danych wejsciowych na pozycji %d \n",position); 
	break; 
	}
}

void DataInit(){
	/*initialize file */
}


void Begin(){

	Msg(CLEAR,0); 
	Msg(WELCOME,0); 

}

