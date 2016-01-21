#include "../headers/containers.h"

List listofpresenters;
List listofpresentations;
Presenter **tabPr;
Presentation **tabPn;
int presenterid=1;
int presentationid=1;


Presenter *AddPresenter(char *fields){

	Presenter *newpresenter;
	Presentation *him;
	char dump[] = ";\n";
	char *token;
	char stemp[1024];
	int i=1;
	int j;
	newpresenter = calloc(1,sizeof(Presenter));
	if(newpresenter==NULL)return NULL;

	strcpy(stemp,fields);
	token = strtok(stemp,dump);
	while(token != NULL){
		if(i==1){
			for(j=0; j<strlen(token); j++){
				if(isalpha(token[j]));
				else {
					Msg(INPUT_ERR,i);
                    free(newpresenter);
			 		return NULL;
				}
			}
			strcpy(newpresenter->name,token);
		}
		if(i==2){
			for(j=0; j<strlen(token); j++){
				if(isalpha(token[j]));
				else {
					Msg(INPUT_ERR,i);
					free(newpresenter);
					return NULL;
				}
			}
			strcpy(newpresenter->surname,token);
		}
		if(i==3){
			strcpy(newpresenter->affiliation,token);
		}
		if(i==4){
			if(token[0]=='0'||token[0]=='1'||token[0]=='2'){
				newpresenter->gen = token[0];
			}
            else {
				Msg(INPUT_ERR,i);
				free(newpresenter);
				return NULL;
			}
		}
		if(i==5){
			if(token[0]=='0'||token[0]=='1'){
				newpresenter->payment = token[0];
			}
			else {
				Msg(INPUT_ERR,i);
				free(newpresenter);
				return NULL;
			}
		}
		if(i>5){
            for(j=0; j<strlen(token); j++){
                if(isdigit(token[j]));
                else {
                    Msg(INPUT_ERR,i);
                    free(newpresenter);
                    return NULL;
                }
            }
            him = ((Presentation*)((FindPresentation(token,&listofpresentations))->obj));
            if(him!=NULL){
                him->owner = newpresenter;
                addnode(him,&(newpresenter->presentations));
            }
            else {
                Msg(PRES_ADD_ERR,i);
                free(newpresenter);
                return NULL;
            }
		}
		token = strtok(NULL, dump);
		i++;
	}
    if(i<7){
        Msg(INPUT_ERR,i);
        free(newpresenter);
        return NULL;
    }
    sprintf(newpresenter->pn,"%d",presenterid);
	presenterid++;

	return newpresenter;
}

Presentation *AddPresentation(char *fields){


	Presentation *newpresentation;
	char dump[] = ";\n";
	char *token;
	char stemp[256];
	int i=1;

	newpresentation = calloc(1,sizeof(Presentation));
	if(newpresentation==NULL)return NULL;

	strcpy(stemp,fields);
	token = strtok(stemp,dump);
	while(token != NULL){
		if(i==1){
			strcpy(newpresentation->name,token);
		}
		if(i==2){
			if(token[0]=='0'||token[0]=='1'){
				newpresentation->type = token[0];
			}
			else {
				Msg(INPUT_ERR,i);
				free(newpresentation);
				return NULL;
			}
		}
		/*if(i==3){
			for(j=0; j<strlen(token); j++){
				if(isdigit(token[j]));
				else {
					Msg(INPUT_ERR,i);
					free(newpresentation);
					return NULL;
				}
			myowner = FindPresenter(token,&listofpresenters);
			if(myowner!=NULL)newpresentation->owner = (Presenter*)(myowner->obj);
			else Msg(INPUT_ERR,i);
			}

		}*/

        token = strtok(NULL, dump);
        i++;
	}

    if(i<2){
        Msg(INPUT_ERR,i);
        free(newpresentation);
        return NULL;
    }
    sprintf(newpresentation->pn,"%d",presentationid);
	presentationid++;

	return newpresentation;
}

Element *FindPresenter(char *field, List *anlist){

	Element *temp;
	Presenter *this;
	if(anlist==NULL)return NULL;
	temp=anlist->head;
	if(field[strlen(field)-1]=='\n')field[strlen(field)-1]='\0';



	while(temp !=NULL){

		this = (Presenter*)temp->obj;
		if(!strcmp(field,this->name))return temp;
		else if (!strcmp(field,this->surname))return temp;
		else if (!strcmp(field,this->affiliation)) return temp;
		else if (!strcmp(field,this->pn)) return temp;
		else temp = temp->next;
	}
	return NULL;
}

Element *FindPresentation(char *field, List *anlist){

	Element *temp;
	Presentation *this;
	temp = anlist->head;
	if(field[strlen(field)-1]=='\n')field[strlen(field)-1]='\0';

	while(temp !=NULL){

		this = (Presentation*)temp->obj;
		if(!strcmp(field,this->name))return temp;
		else if(!strcmp(field,this->pn)) return temp;
		else temp = temp->next;
	}
	return NULL;
}

int DeletePresenter(Element *dead){

	if(delnode(dead,&listofpresenters))return 1;
	if(delnode(FindPresenter((((Presenter*)(dead->obj))->pn),((List*)FindInCats(((Presenter*)(dead->obj))->pn))),((List*)FindInCats(((Presenter*)(dead->obj))->pn))))return 0;
	return 0;
}

int DeletePresentation(Element *dead){

	if(delnode(dead,&listofpresentations))return 1;
	if(delnode(FindPresentation(((Presentation*)(dead->obj))->pn,FindInCats(((Presentation*)(dead->obj))->pn)),FindInCats(((Presentation*)(dead->obj))->pn)))return 0;
	return 0;
}


int UpdatePresenter(Presenter *new, char *id){
	Element *temp;
	temp = FindPresenter(id,&listofpresenters);

	if(new!=NULL)temp->obj = new;
	return 0;
}

int UpdatePresentation(Presentation *new, char *id){
	Element *temp;
	temp = FindPresentation(id,&listofpresentations);

	if(new!=NULL)temp->obj = new;
	return 0;
}


void PrintPresenterFile(FILE *stream){
	Element *temp;
	Element *prestemp;
	Presenter *this;
	Presentation *him;
	temp = listofpresenters.head;
	for(;temp!=NULL;temp=temp->next){

		this = (Presenter*)temp->obj;

		fprintf(stream,"%s;%s;%s;",this->name,this->surname,this->affiliation);
		fprintf(stream,"%c;%c;",this->gen,this->payment);
		fprintf(stream,"%s;",this->pn);
		for(prestemp = this->presentations.head;prestemp!=NULL;prestemp = prestemp->next){
			him = (Presentation*)prestemp->obj;
			fprintf(stream,"%s;",him->pn);
		}
		fprintf(stream,"\n");
	}
}

void PrintSortedPresenterTable(int sortorder){
	int i,j;
	int *tab;
	Element  *temp;
	tab = calloc(listofpresenters.lenght,sizeof(int));
	tabPr = calloc(listofpresenters.lenght,sizeof(Presenter*));
	temp = listofpresenters.head;
	for(i=0;temp!=NULL;i++){tabPr[i]=(Presenter*)(temp->obj);temp=temp->next;}
	j=i;
	for(i=0;i<j;tab[i]=i,i++);

	if(sortorder==1)qsort(tab,i,sizeof(int),ComparePresenterName);
	if(sortorder==2)qsort(tab,i,sizeof(int),ComparePresenterSurname);
	if(sortorder==3)qsort(tab,i,sizeof(int),ComparePresenterAffiliation);
	if(sortorder==4)qsort(tab,i,sizeof(int),ComparePresenterGen);
	if(sortorder==5)qsort(tab,i,sizeof(int),ComparePresenterPayment);
	if(sortorder==6)qsort(tab,i,sizeof(int),ComparePresenterPresentations);

	printf("id   |             Imie|          Nazwisko|              Afiliacja|      Typ|      Platnosc|         Prezentacje|\n");
	for(i=0;i<j;i++)PrintPresenterLine(tabPr[tab[i]],stdout);
	free(tab);
}

void PrintPresenterLine(Presenter *any, FILE *stream){

	int i;
	Element *temp;
	Presentation *him;

	if(any!=NULL){
        temp = (any->presentations).head;
        fprintf(stream,"|%4s|%20s|%20s|%30s|",any->pn,any->name,any->surname,any->affiliation);
        if(any->gen=='0')fprintf(stream,"brak  |");
        if(any->gen=='1')fprintf(stream,"ustne |");
        if(any->gen=='2')fprintf(stream,"plakat|");
        if(any->payment=='0')fprintf(stream,"brak     |");
        if(any->payment=='1')fprintf(stream,"zaplacono|");
        for(;temp!=NULL;temp=temp->next){
            him=(Presentation*)temp->obj;
            for(i=0; i<101;i++)fprintf(stream," ");
            fprintf(stream,"|%20s|\n",him->name);
	    }
	    printf("\n");
	}
}


void PrintPresentationFile(FILE * stream){
	Element * temp;
	Presentation *this;
	temp = listofpresentations.head;
	for(;temp!=NULL;temp = temp->next){
		this = (Presentation*)temp->obj;
		fprintf(stream,"%s;%c;",this->name,this->type);
		fprintf(stream,"%s;%s;\n",(this->owner)->pn,this->pn);
	}
}

void PrintSortedPresentationTable(int sortorder){
	int i,j;
	int *tab;
	Element  *temp;
	tab = calloc(listofpresentations.lenght,sizeof(int));
	tabPn = calloc(listofpresentations.lenght,sizeof(Presentation*));
	temp = listofpresentations.head;
	for(i=0,temp=listofpresentations.head;temp!=NULL;tabPn[i]=(Presentation*)(temp->obj),temp=temp->next,i++);
	j = i;
	for(i=0; i<j;tab[i]=i,i++);

	if(sortorder==1)qsort(tab,j,sizeof(int),ComparePresentationName);
	if(sortorder==2)qsort(tab,j,sizeof(int),ComparePresentationType);

    printf("id   |           Nazwa|          Typ|              Prezenter|\n");
	for(i=0; i<j; i++)PrintPresentationLine(tabPn[tab[i]],stdout);
	free(tab);
}

void PrintPresentationLine(Presentation *any, FILE *stream){
	if(any!=NULL){
        fprintf(stream,"%4s|%30s|",any->pn, any->name);
        if(any->type=='0')fprintf(stream,"ustna |");
        if(any->type=='1')fprintf(stream,"plakat|");
        if((Presenter*)(any->owner)!=NULL){
            fprintf(stream,"%4s|\n",((Presenter*)(any->owner))->pn);
        }
        else printf("\n");
	}
}

void PrintPresenterIdTable(){
	Element *temp;
	Presenter *this;
	printf("Lista id prezenterów:\n");
	for(temp=listofpresenters.head;temp!=NULL;temp=temp->next){
		this = (Presenter*)temp->obj;
		fprintf(stdout,"%s;\n",this->pn);
	}
	printf("------------------------------------------------------------------------------------\n");
}

void PrintPresentationIdTable(){
	Element *temp;
	Presentation *this;
	printf("Lista id prezentacji:\n");
	for(temp = listofpresentations.head;temp!=NULL;temp = temp->next){
		this = (Presentation*)temp->obj;
		fprintf(stdout,"%s;\n",this->pn);
	}
	printf("------------------------------------------------------------------------------------\n");
}


int ComparePresenterName (const void * a, const void * b){

	int x = *(int*)a;
	int y = *(int*)b;
	return strcmp(tabPr[x]->name,tabPr[y]->name);
}

int ComparePresenterSurname (const void * a, const void * b){

	int x = *(int*)a;
	int y = *(int*)b;
	return strcmp(tabPr[x]->surname,tabPr[y]->surname);
}

int ComparePresenterAffiliation (const void * a, const void * b){

	int x = *(int*)a;
	int y = *(int*)b;
	return strcmp(tabPr[x]->affiliation,tabPr[y]->affiliation);
}

int ComparePresenterGen (const void * a, const void * b){

	int x = *(int*)a;
	int y = *(int*)b;
	if(tabPr[x]->gen==tabPr[y]->gen)return 0;
	else if(tabPr[x]->gen>tabPr[y]->gen)return 1;
	else return -1;
}

int ComparePresenterPayment (const void * a, const void * b){

	int x = *(int*)a;
	int y = *(int*)b;
	if(tabPr[x]->payment==tabPr[y]->payment)return 0;
	else if(tabPr[x]->payment>tabPr[y]->payment)return 1;
	else return -1;
}

int ComparePresenterPresentations (const void * a, const void * b){

	int x = *(int*)a;
	int y = *(int*)b;
	if(tabPr[x]->presentations.lenght>tabPr[y]->presentations.lenght) return 1;
	else if (tabPr[x]->presentations.lenght==tabPr[y]->presentations.lenght) return 0;
	else return 0;
}

int ComparePresentationName (const void * a, const void * b){

	int x = *(int*)a;
	int y = *(int*)b;
	return strcmp(tabPn[x]->name,tabPn[y]->name);
}

int ComparePresentationType (const void * a, const void * b){

	int x = *(int*)a;
	int y = *(int*)b;
	if(tabPn[x]->type==tabPn[y]->type)return 0;
	else if(tabPn[x]->type>tabPn[y]->type)return 1;
	else return -1;
}

