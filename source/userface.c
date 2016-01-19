#include "../headers/userface.h"

extern List listofpresenters;
extern List listofpresentations;
extern List listofcatalogues;
extern Presenter *tabPr;
extern Presentation *tabPn;
char *buffer;


int Exit(){


    Msg(EXIT_PROMPT,0);
    if(strcmp(ReadData(buffer),"TAK"));
    else return 1;


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
	printf("-Wpisz 2 aby dodac prezentacje         - wpisz 9 aby wyswietlic liste prezentacji       -\n");
	printf("-Wpisz 3 aby usunac prezentera         - wpisz 10 aby wyswietlic liste katalogow        -\n");
	printf("-Wpisz 4 aby usunac prezentacje        - wpisz 11 aby przejsc do operacji na plikach    -\n");
	printf("-Wpisz 5 aby dodac katalog             - wpisz 12 aby wyszukac                          -\n");
	printf("-Wpisz 6 aby edytowac prezentacje      - wpisz 0 aby zakonczyc                          -\n");
	printf("-Wpisz 7 aby edytowac prezentera                                                        -\n");
	printf("-----------------------------------------------------------------------------------------\n");
	break;

	case FILE_MENU:
	printf("Wpisz komende aby wykonac operacje\n");
    printf("Np zapisz/odczytaj nazwapliku.txt\n");
    printf("Np zapisz/odczytaj nazwapliku.lua haslo\n");
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

	case FILE_READ_SUCCES:
    printf("Pomyslnie odczytano plik \n");
    break;

	case FILE_CREATE_SUCCES:
	printf("Pomyslnie utworzono plik \n");
	break;

	case FILE_CREATE_ERR:
	printf("Blad przy tworzeniu pliku \n");
	break;

    case FILE_SAVE_SUCCES:
	printf("Pomyslnie zapisano plik \n");
	break;

	case FILE_SAVE_ERR:
	printf("Blad przy zapisywaniu pliku \n");
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

    case PRESENTER_PRINT_TABLE:
    printf("Wpisz porzadek sortowania aby wyswietlic liste prezenterow \n");
    break;

    case PRESENTER_PRINT_SORTORDER_LIST:
    printf("1 - wedlug imienia, 2 - wedlug nazwiska, 3 - wedlug afiliacji 4 -wedlug typu , 5 - wedlug platnosci, 0 - aby zakonczyc \n");
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

    case PRESENTATION_PRINT_TABLE:
    printf("Wpisz porzadek sortowania aby wyswietlic liste prezentacji \n");
    break;

    case PRESENTATION_PRINT_SORTORDER_LIST:
    printf("1 - wedlug nazwy, 2 - wedlug typu, 0 - aby zakonczyc\n");
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

    case CAT_PRINT_TABLE:
	printf("Lista katalogow:\n");
	printf("Aby zakonczyc wpisz 0.\n");
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

	case SEARCH:
    printf("wpisz 0 aby wyszukac prezentacje lub 1 aby wyszukac prezentera\n");
    break;

    case SEARCH_NEXT:
    printf("Aby wyszukac nastepny rekord wpisz 1 aby zakonczyc wpisz 0\n");
    break;

    case SEARCH_ERR:
    printf("Blad przy wyszukiwniu brak rekordu w bazie\n");
    break;

    case SEARCH_PRESENTER:
    printf("Wpisz ciag znakow zawierajacy jeden z elementów rekordu np imie.\n");
    break;

    case SEARCH_PRESENTATION:
    printf("Wpisz jeden z elementow rekordu np nazwe\n");
    break;

	case CONTINUE:
    printf("Aby kontynuowac wpisz 1, aby zakonczyc wpisz 0.\n");
    break;

    case EXIT_PROMPT:
    printf("Aby  wyjść wpisz cokolwoek(oprocz TAK), aby zakonczyc wpisz TAK\n");
    break;
	}
}

void DataInit(){
	/*if(OpenBin())Msg(BIN_ERR,0);
	if(OpenRaw())Msg(RAW_ERR,0);*/

	buffer = malloc(256*sizeof(char));
	listofpresentations.lenght=0;
	listofpresenters.lenght=0;
	listofcatalogues.lenght=0;
}

void Begin(){

    int control;
	Msg(CLEAR,0);
	Msg(WELCOME,0);
	Msg(WELCOME_PROMPT,0);
	ReadFromStd();
	DataInit();
	do{
        Msg(CLEAR,0);
        Msg(MAINMENU,0);
        Msg(MENU_PROMPT,0);
        control = ReadFromStd();
        switch (control){

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

            case 8:
                Msg(CLEAR,0);
                UserPresenterPrintTable();
            break;

            case 9:
                Msg(CLEAR,0);
                UserPresentationPrintTable();
            break;

            case 10:
                Msg(CLEAR,0);
                UserPrintCatTable();
            break;

            case 11:
                Msg(CLEAR,0);
                UserFileHandling();
            break;

            case 12:
                Msg(CLEAR,0);
                UserSearch();
            break;


        }
	}while(control);

	while(Exit());
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

void UserPresenterPrintTable(){
    int sortorder;
    do{
    	Msg(PRESENTER_PRINT_TABLE,0);
    	Msg(PRESENTER_PRINT_SORTORDER_LIST,0);
    	sortorder = ReadFromStd();
    	PrintSortedPresenterTable(sortorder);
    }while(sortorder);

}
void UserPresentationPrintTable(){
    int sortorder;
    do{
    	Msg(PRESENTATION_PRINT_TABLE,0);
    	Msg(PRESENTATION_PRINT_SORTORDER_LIST,0);
    	sortorder = ReadFromStd();
    	PrintSortedPresentationTable(sortorder);
    }while(sortorder);
}

void UserPrintCatTable(){
    do{
    	Msg(CAT_PRINT_TABLE,0);
    	PrintCatTable(stdout);
    }while(ReadFromStd());
 }

void UserFileHandling(){
    do{
        Msg(FILE_MENU,0);
        switch (CommandParse(ReadData(buffer))){
        case 1: /*wrong command*/break;
        case 2: /*file n exist*/ break;
        case 3: /*blad podczas otwarcia pliku*/break;
        case 4: /*bledne haslo*/ break;
        }

    }while(ReadFromStd());
}

void UserSearch(){
    Presenter *temp;
    Presentation *ptemp;
    do{
        Msg(SEARCH,0);
        if(ReadFromStd()){
            Msg(SEARCH_PRESENTER,0);
            temp = (Presenter*)(FindPresenter(ReadData(buffer),&listofpresenters))->obj;
            if(temp==NULL)Msg(SEARCH_ERR,0);
            else PrintPresenterLine(temp,stdout);
        }
        else{
            Msg(SEARCH_PRESENTATION,0);
            ptemp = (Presentation*)(FindPresentation(ReadData(buffer),&listofpresentations))->obj;
            if(ptemp==NULL)Msg(SEARCH_ERR,0);
            else PrintPresentationLine(ptemp,stdout);
        }
        Msg(SEARCH_NEXT,0);
    }while(ReadFromStd());
}

int CommandParse(char *input){
    char dump[] = " ";
    char filedump[] = ".";
	char *token;
	char *filetoken;
	char stemp[1024];
	char filestemp[128];
	char temptxtfilename[128];
	char tempbinfilemane[128];
	char temppasswd[128];
	int i=1;
	int result=0;
	FILE *filetemp;
	filetemp = NULL;

	strcpy(stemp,input);
	token = strtok(stemp,dump);
	while(token != NULL){
		if(i==1){
            if(strcmp(token,"zapisz")==0)result = 1;
            else if(strcmp(token,"odczytaj")==0)result = 2;
            else {Msg(INPUT_ERR,i); return 0;}
        }
		if(i==2){
            strcpy(filestemp,token);
            filetoken = strtok(filestemp,filedump);
            while(filetoken!=NULL){
                if(strcmp(filetoken,"txt")==0)result += 4;
                else if(strcmp(filetoken,"ula")==0)result += 8;
                filetoken = strtok(NULL,filedump);
            }
            if(result==0){Msg(INPUT_ERR,i); return 0;}
            else if((result<8)&&(result>4))strcpy(temptxtfilename,token);
            else if (result>8)strcpy(tempbinfilemane,token);
            else return 0;
		}
		if(i==3){
            strcpy(temppasswd,token);
		}
		token = strtok(NULL, dump);
		i++;
	}

	/*results from commands*/
	switch (result){

        case 5: /*zapisz .txt*/
            if(CreateRaw(temptxtfilename,filetemp))Msg(FILE_CREATE_ERR,0);
            if(SaveRaw(filetemp))Msg(FILE_SAVE_ERR,0);
            else Msg(FILE_SAVE_SUCCES,0);
        break;

        case 6: /*odczytaj .txt*/
            if(OpenRaw(temptxtfilename,filetemp))Msg(FILE_OPEN_ERR,0);
            if(LoadRaw(filetemp))Msg(FILE_READ_ERR,0);
            else Msg(FILE_READ_SUCCES,0);
        break;

        case 9: /*zapisz .ula */;
            if(SaveBin(temppasswd,CreateBin(tempbinfilemane,filetemp)))Msg(FILE_SAVE_ERR,0);
            else Msg(FILE_SAVE_SUCCES,0);
        break;

        case 10: /*odczytaj .ula*/
            if(OpenBin(tempbinfilemane,filetemp))Msg(FILE_OPEN_ERR,0);
            if(LoadBin(temppasswd,filetemp))Msg(FILE_READ_ERR,0);
            else Msg(FILE_READ_SUCCES,0);
        break;

        default:
            Msg(INPUT_ERR,0);
        break;
	}
fclose(filetemp);
return 0;
}

