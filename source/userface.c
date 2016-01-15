#include "../headers/userface.h"

extern List listofpresenters;
extern List listofpresentations;
extern List listofcatalogues;
extern Presenter *tabPr;
extern Presentation *tabPn;
char * buffer;

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

	/*SaveBin();
	SaveRaw(); */

	return 0;
}

int ReadFromStd(){
	char line[256];
	fgets(line,256,stdin);
	if(atoi(line)>=0&&atoi(line)<16)return atoi(line);
	Msg(INPUT_ERR,0);
	return 0;
}

char *ReadData(char *line){

	fgets(line,256,stdin);
	return line;
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
	printf("-Wpisz 1 aby dodac prezentera          - wpisz 8 aby wyswietlic liste prezenterow       -\n");
	printf("-Wpisz 2 aby dodac prezentacje         - wpisz 9 aby wyswietlic liste prezentacji      -\n");
	printf("-Wpisz 3 aby usunac prezentera         - wpisz 10 aby wyswietlic liste kat. prezenterow -\n");
	printf("-Wpisz 4 aby usunac prezentacje        - wpisz 11 aby wyswietlic liste kat.prezentacji -\n");
	printf("-Wpisz 5 aby dodac katalog               - wpisz 12 aby przejsc do operacji na plikach    -\n");
	printf("-Wpisz 6 aby edytowac prezentacje      - wpisz 13 aby wyszukac                          -\n");
	printf("-Wpisz 7 aby edytowac prezentera       - wpisz 0 aby zakonczyc                          -\n");
	printf("-----------------------------------------------------------------------------------------\n");
	break;

	case FILE_MENU:
	printf("Wpisz komende aby wykonac operacje lub wpisz help aby wyswietlic liste dostepnych komend\n");
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
	printf("STATUS PLATNOSCI (0-brak 1-zaplacono) oraz numery prezentacji z listy poniżej.\n");
	printf("Pozycje rozdziel srednikiem Np: Jan;Kowalski;Uniwersytet 3-go wieku;1;0;567;2454;21;\n");
	break;

	case PRESENTER_ADD_SUCCES:
	printf("Pomyslnie dodano prezentera do bazy danych \n");
	break;

    case PRESENTER_DEL:
	printf("Wpisz numer prezentera z tablicy powyzej ktorego chcesz usunac \n");
	break;

    case PRESENTER_DEL_SUCCES:
	printf("Pomyslnie usunieto prezentera \n");
	break;

    case PRESENTER_CHANGE:
	printf("Wpisz id prezentera ktorego chcesz edytowac z listy powyzej\n");
	break;

    case PRESENTER_CHANGE_SUCCES:
	printf("Pomyslnie edytowano prezentera \n");
	break;

    case PRESENTER_CHANGE_NEXT:
	printf(" Aby edytowac kolejnego prezentera wpisz 1. Aby zakonczyc wpisz 0.\n");
	break;

    case PRESENTER_CHANGE_ERR:
	printf("Blad przy edytowaniu prezentera. \n");
	break;

	case PRESENTATION_ADD:
	printf("Wpisz w linii NAZWE, TYP(0-plakat 1-ustne) oraz ID prezentera z listy poniżej: \n");
	printf("Pozycje rodzeiel srednikiem: Np: Swietna prezentacja;0;0234 \n");
	break;

	case PRESENTATION_ADD_SUCCES:
	printf("Pomyslnie dodano prezentacje do bazy danych \n");
	break;

    case PRESENTATION_DEL:
	printf("Wpisz id prezentacji z listy powyzej ktora chcesz usunac\n");
	break;

    case PRESENTATION_DEL_SUCCES:
	printf("Pomyslnie usunieto prezentacje \n");
	break;

	case PRESENTER_NEXIST:
	printf("Prezenter o podanym numerze nie istnieje \n");
	break;

	case PRESENTATION_NEXIST:
	printf("Prezentacja o podanym numerze nie istnieje \n");
	break;

    case PRESENTATION_CHANGE:
	printf("Wpisz id prezentacji ktora chcesz edytowac z listy powyzej\n");
	break;

    case PRESENTATION_CHANGE_SUCCES:
	printf("Pomyslnie edytowano prezentacje\n");
	break;

    case PRESENTATION_CHANGE_NEXT:
	printf(" Aby edytowac kolejna prezentacje wpisz 1. Aby zakonczyc wpisz 0.\n");
	break;

    case PRESENTATION_CHANGE_ERR:
	printf("Blad przy edytowaniu prezentacji. \n");
	break;

	case CAT_ADD:
	printf("Wpisz nazwę katalogu, jego typ (0 - prezenterzy, 1 - prezentacje),\n");
    printf("oraz numery id prezenterow lub prezentacji z listy powyzej.\n");
    printf("Pozycje rozdziel srednikiem np. Katalogprezenterow;0;12;123;643;");
	break;

	case CAT_ADD_NEXT:
	printf("Aby dodac kolejny katalog wpisz 1. Aby zakonczyc wpisz 0.\n");
	break;

	case CAT_ADD_SUCCES:
	printf("Pomyślnie dodano katalog do bazy danych.\n");
	break;

    case CAT_ADD_ERR:
	printf("Bad przy tworzeniu katalogu.\n");
	break;

	case INPUT_ERR:
	printf("Blad danych wejsciowych na pozycji %d \n",position);
	break;

	case MENU_ERR:
	printf("wpisz poprawna wartosc!\n");
	break;

	case INIT_ERR:
	printf("Blad inicjalizacji danych z pliku \n");
	break;

	case DEL_ERR:
	printf("Blad usuwania obiektu \n");
	break;

	case DEL_NEXT:
	printf("Aby usunac kolejny rekord wpisz 1. Aby zakonczyc wpisz 0.\n");
	break;

	case ADD_ERR:
	printf("Blad dodawania elementu do bazy danych\n");
	break;

	case WELCOME_PROMPT:
	printf("Nasiśnij dowolny klawisz aby rozpoczac\n");
	break;

	case BIN_ERR:
	printf("Blad otwarcia pliku binarnego\n");
	break;

	case RAW_ERR:
	printf("Blad otwarcia pliku tekstowego\n");
	break;

	case MENU_PROMPT:
	printf("Wpisz wartość od 0 do 16 i potwierdź klawiszem enter\n");
	break;

	case ADD_NEXT:
	printf("Aby dodac kolejny rekord wpisz 1. Aby zakonczyc wpisz 0.\n");
	break;

    case PRES_ADD_ERR:
	printf("Presentacja o podanym numerze nie istnieje\n");
	break;
	}
}

void DataInit(){
	/*if(OpenBin())Msg(BIN_ERR,0);
	if(OpenRaw())Msg(RAW_ERR,0);*/

	buffer = malloc(256*sizeof(char));
}

void Begin(){

	Msg(CLEAR,0);
	Msg(WELCOME,0);
	Msg(WELCOME_PROMPT,0);
	ReadFromStd();
	DataInit();
	do{
        Msg(CLEAR,0);
        Msg(MAINMENU,0);
        Msg(MENU_PROMPT,0);
        switch (ReadFromStd()){

            case 0:
                Exit();
            break;

            case 1:
                Msg(CLEAR,0);
                UserPresenterAdd();
            break;

            case 2:
                Msg(CLEAR,0);
                UserPresentationAdd();
            break;

            case 3:
                Msg(CLEAR,0);
                UserPresenterDel();
            break;

            case 4:
                Msg(CLEAR,0);
                UserPresentationDel();
            break;

            case 5:
                Msg(CLEAR,0);
                UserCatalougeAdd();
            break;

            case 6:
                Msg(CLEAR,0);
                UserPresenterUpdate();
            break;

            case 7:
                Msg(CLEAR,0);
                UserPresentationUpdate();
            break;


        }
	}while(ReadFromStd());

	Exit();
}

void UserPresenterAdd(){
    do{
        Msg(PRESENTER_ADD,0);
        if(addnode(AddPresenter(ReadData(buffer)),&listofpresenters))Msg(MENU_ERR,0);
        else Msg(PRESENTER_ADD_SUCCES,0);
        Msg(ADD_NEXT,0);
    }while(ReadFromStd());
}

void UserPresentationAdd(){
    do{
        Msg(PRESENTATION_ADD,0);
        PrintPresenterIdTable();
        if(addnode(AddPresentation(ReadData(buffer)),&listofpresentations))Msg(MENU_ERR,0);
        Msg(ADD_NEXT,0);
    }while(ReadFromStd());
}

void UserCatalougeAdd(){
    do{
        Msg(CAT_ADD,0);
        PrintPresenterIdTable();
        PrintPresentationIdTable();
        if(addnode(AddCat(ReadData(buffer)),&listofcatalogues))Msg(MENU_ERR,0);
        else Msg(CAT_ADD_SUCCES,0);
        Msg(CAT_ADD_NEXT,0);
    }while(ReadFromStd());
}

void UserPresenterDel(){
    do{
        PrintPresenterIdTable();
        Msg(PRESENTER_DEL,0);
        if(DeletePresenter(FindPresenter(ReadData(buffer),&listofpresenters)))Msg(DEL_ERR,0);
        else Msg(PRESENTER_DEL_SUCCES,0);
        Msg(DEL_NEXT,0);
    }while(ReadFromStd());
}

void UserPresentationDel(){
    do{
        PrintPresentationIdTable();
        Msg(PRESENTATION_DEL,0);
        if(DeletePresentation(FindPresentation(ReadData(buffer),&listofpresentations)))Msg(DEL_ERR,0);
        else Msg(PRESENTATION_DEL_SUCCES,0);
        Msg(DEL_NEXT,0);
    }while(ReadFromStd());
}

void UserPresenterUpdate(){
    char id[10];
    do{
        Msg(CLEAR,0);
        Msg(PRESENTER_CHANGE,0);
        PrintPresenterIdTable();
        fgets(id,10,stdin);
        if(FindPresenter(id,&listofpresenters)!=NULL){
            Msg(PRESENTER_ADD,0);
            if(UpdatePresenter(AddPresenter(ReadData(buffer)),id))Msg(PRESENTER_CHANGE_ERR,0);
            else Msg(PRESENTER_CHANGE_SUCCES,0);
        }
        else Msg(PRESENTER_NEXIST,0);
        Msg(PRESENTER_CHANGE_NEXT,0);
    }while(ReadFromStd());
}
void UserPresentationUpdate(){
    char id[10];
    do{
        Msg(CLEAR,0);
        Msg(PRESENTATION_CHANGE,0);
        PrintPresentationIdTable();
        fgets(id,10,stdin);
        if(FindPresentation(id,&listofpresentations)!=NULL){
        Msg(PRESENTATION_ADD,0);
        if(UpdatePresentation(AddPresentation(ReadData(buffer)),id))Msg(PRESENTATION_CHANGE_ERR,0);
        else Msg(PRESENTATION_CHANGE_SUCCES,0);
        }
        else Msg(PRESENTATION_NEXIST,0);
        Msg(PRESENTATION_CHANGE_NEXT,0);
    }while(ReadFromStd());
}

