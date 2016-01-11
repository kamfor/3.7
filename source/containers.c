#include "../headers/containers.h"

List listofpresenters; 
List listofpresentations; 
Presenter *tabPr; 
Presentation *tabPn; 

Presenter *AddPresenter(char *fields){

	Presenter *newpresenter;
	char dump[] = ";"; 
	char *token; 
	char stemp[1024];
	int i=1; 
	int j;
	newpresenter = calloc(1,sizeof(Presenter)); 
	if(newpresenter==NULL)return NULL;  

	strcpy(fields,stemp); 
	token = strtok(stemp,dump); 
	while(token != NULL){
		if(i==1){
			for(j=0; j<strlen(token); j++){
				if(isalpha(token[j])); 
				else {
					Msg(INPUT_ERR,i); 
			 		return NULL; 
				}
			}
			strcpy(token,newpresenter->name); 
		}
		if(i==2){
			for(j=0; j<strlen(token); j++){
				if(isalpha(token[j])); 
				else {
					Msg(INPUT_ERR,i); 
					return NULL; 
				}
			}
			strcpy(token,newpresenter->surname); 
		}
		if(i==3){
			for(j=0; j<strlen(token); j++){
				if(isalpha(token[j])); 
				else {
					Msg(INPUT_ERR,i); 
					return NULL; 
				}
			}
			strcpy(token,newpresenter->affiliation); 
		}
		if(i==4){
			if(token[0]=='0'||token[0]=='1'||token[0]=='2'){
				newpresenter->gen = token[0]; 
			}
		else {
				Msg(INPUT_ERR,i); 
				return NULL; 
			}
		}
		if(i==5){
			if(token[0]=='0'||token[0]=='1'){
				newpresenter->payment = token[0]; 
			}
			else {
				Msg(INPUT_ERR,i); 
				return NULL; 
			}
		}
		if(i==6){
			for(j=0; j<strlen(token); j++){
				if(isdigit(token[j])); 
				else {
					Msg(INPUT_ERR,i); 
					return NULL; 
				}
			}
			strcpy(token,newpresenter->pn); 
		}
		if(i>6){
			for(j=0; j<strlen(token); j++){
				if(isdigit(token[j])); 
				else {
					Msg(INPUT_ERR,i); 
					return NULL; 
				}
			}
			if(addnode(FindPresentation(token,&listofpresentations),&newpresenter->presentations)){
				Msg(ADD_ERR,0); 
			} 
		}
	
		token = strtok(NULL, dump); 
		i++; 
	}

	return newpresenter;

}

Presentation *AddPresentation(char *fields){


	Presentation *newpresentation;
	Element *myowner; 
	char dump[] = ";"; 
	char *token; 
	char stemp[256]; 
	int i=1; 
	int j; 
	
	newpresentation = calloc(1,sizeof(Presentation)); 
	if(newpresentation==NULL)return NULL; 

	strcpy(fields,stemp); 
	token = strtok(stemp,dump); 
	while(token != NULL){
		if(i==1){
			for(j=0; j<strlen(token); j++){
				if(isalpha(token[j])); 
				else {
					Msg(INPUT_ERR,i); 
					return NULL; 
				}
			}
			strcpy(token,newpresentation->name); 
		}
		if(i==2){
			if(token[0]=='0'||token[0]=='1'){
				newpresentation->type = token[0]; 
			}
			else {
				Msg(INPUT_ERR,i); 
				return NULL; 
			}
		}
		if(i==3){
			for(j=0; j<strlen(token); j++){
				if(isdigit(token[j])); 
				else {
					Msg(INPUT_ERR,i); 
					return NULL; 
				}
			}
			strcpy(token,newpresentation->pn);
		}
		if(i==4){
			for(j=0; j<strlen(token); j++){
				if(isdigit(token[j])); 
				else {
					Msg(INPUT_ERR,i); 
					return NULL; 
				}
			myowner = FindPresenter(token,&listofpresenters); 
			newpresentation->owner = (Presenter*)(myowner->obj); 
			}

	
			token = strtok(NULL, dump); 
 			i++; 
		}
	}


	return newpresentation;
}

Element *FindPresenter(char *field, List *anlist){

	Element *temp; 
	Presenter *this;
	temp  = anlist->head; 

	
	while(temp !=NULL){
	
		this = (Presenter*)temp->obj; 		
		if(strcmp(field,this->name))return temp; 
		else if (strcmp(field,this->surname))return temp; 
		else if (strcmp(field,this->affiliation)) return temp; 
		else if (strcmp(field,this->pn)) return temp; 
		else return NULL;
		temp = temp->next; 
	}
	return NULL; 
}

Element * FindPresentation(char *field, List *anlist){

	Element *temp; 
	Presentation *this; 
	temp = anlist->head; 

	while(temp !=NULL){
		
		this = (Presentation*)temp->obj;		
		if(strcmp(field,this->name))return temp;  
		else if(strcmp(field,this->pn)) return temp; 
		else return NULL;
		temp = temp->next; 
	}
	return NULL; 
}

int DeletePresenter(Presenter *dead){
	
	if(delnode(FindPresenter(dead->pn,&listofpresenters),&listofpresenters)){Msg(DEL_ERR,0);return 1;} 
	if(delnode(FindPresenter((dead->pn),((List*)FindInCats(dead->pn))),((List*)FindInCats(dead->pn)))){Msg(DEL_ERR,0);return 1;}
	return 0; 
}

int DeletePresentation(Presentation *dead){
	
	if(delnode(FindPresentation(dead->pn,&listofpresentations),&listofpresentations)){Msg(DEL_ERR,0);return 1;} 
	if(delnode(FindPresentation(dead->pn,FindInCats(dead->pn)),FindInCats(dead->pn))){Msg(DEL_ERR,0);return 1;}
	return 0; 
}


int UpdatePresenter(Presenter *new){
	Element *temp; 
	temp = FindPresenter(new->pn,&listofpresenters); 

	temp->obj = new; 
	return 0; 
}

int UpdatePresentation(Presentation *new){
	Element *temp; 
	temp = FindPresentation(new->pn, &listofpresentations); 
	
	temp->obj = new; 
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
		fprintf(stream,"%c:%c;",this->gen,this->payment); 
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
	tab = malloc(listofpresenters.lenght*sizeof(int)); 
	tabPr = malloc(listofpresenters.lenght*sizeof(Presenter));
	temp = listofpresenters.head; 
	for(i=0;temp!=NULL;temp=temp->next,tabPr[i]=*(((Presenter*)(temp->obj))),i++);
	j=i+1; 
	for(i=0;i<j;tab[i]=i,i++);
	
	if(sortorder==1)qsort(tab,j,sizeof(int),ComparePresenterName);
	if(sortorder==2)qsort(tab,j,sizeof(int),ComparePresenterSurname);
	if(sortorder==3)qsort(tab,j,sizeof(int),ComparePresenterAffiliation);
	if(sortorder==4)qsort(tab,j,sizeof(int),ComparePresenterGen);
	if(sortorder==5)qsort(tab,j,sizeof(int),ComparePresenterPayment);
	if(sortorder==6)qsort(tab,j,sizeof(int),ComparePresenterPresentations);
	for(i=0;i<j;i++)PrintPresenterLine(&(tabPr[tab[i]]),stdout);
	free(tab); 
}

void PrintPresenterLine(Presenter *any, FILE *stream){
	
	int i; 
	Element *temp;
	Presentation *him; 
	temp = any->presentations.head; 
	
	fprintf(stream,"|%4s|%30s|%30s|%40s|",any->pn,any->name,any->surname,any->affiliation); 
	if(any->gen=='0')fprintf(stream,"brak  |"); 
	if(any->gen=='1')fprintf(stream,"ustne |"); 
	if(any->gen=='2')fprintf(stream,"plakat|"); 
	if(any->payment=='0')fprintf(stream,"brak     |"); 
	if(any->payment=='1')fprintf(stream,"zaplacono|"); 
	for(;temp!=NULL;temp = temp->next){
		him  = (Presentation*)temp->obj; 
		for(i=0; i<121;i++)fprintf(stream," "); 
		fprintf(stream,"|%20s|\n",him->name); 
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

void PrintPresentationsTable(int sortorder){
	int i,j; 
	int *tab;
	Element  *temp; 
	tab = malloc(listofpresentations.lenght*sizeof(int)); 
	tabPn = malloc(listofpresentations.lenght*sizeof(Presentation));
	temp = listofpresentations.head; 
	for(i=0,temp=listofpresentations.head;temp!=NULL;tabPn[i]=*(((Presentation*)(temp->obj))),temp=temp->next,i++);
	j = i+1;
	for(i=0; i<j;tab[i]=i,i++); 
	
	if(sortorder==1)qsort(tab,j,sizeof(int),ComparePresenterName);
	if(sortorder==2)qsort(tab,j,sizeof(int),ComparePresenterSurname);
	
	for(i=0; i<j; i++)PrintPresentationLine(&(tabPn[tab[i]]),stdout); 
	free(tab); 

}

void PrintPresentationLine(Presentation *any, FILE *stream){
	fprintf(stream,"%4s|%30s|",any->pn, any->name); 
	if(any->type=='0')fprintf(stream,"ustna |"); 
	if(any->type=='1')fprintf(stream,"plakat|"); 
	fprintf(stream,"%4s|\n",(any->owner)->pn); 
}

int ComparePresenterName (const void * a, const void * b){

	int x = *(int*)a;
	int y = *(int*)b;
	return strcmp(tabPr[x].name,tabPr[y].name); 
}

int ComparePresenterSurname (const void * a, const void * b){

	int x = *(int*)a;
	int y = *(int*)b;
	return strcmp(tabPr[x].surname,tabPr[y].surname); 
}

int ComparePresenterAffiliation (const void * a, const void * b){

	int x = *(int*)a;
	int y = *(int*)b;
	return strcmp(tabPr[x].affiliation,tabPr[y].affiliation); 
}

int ComparePresenterGen (const void * a, const void * b){

	int x = *(int*)a;
	int y = *(int*)b;
	if(tabPr[x].gen==tabPr[y].gen)return 0; 
	else if(tabPr[x].gen>tabPr[y].gen)return 1; 
	else return -1;  
}

int ComparePresenterPayment (const void * a, const void * b){

	int x = *(int*)a;
	int y = *(int*)b;
	if(tabPr[x].payment==tabPr[y].payment)return 0; 
	else if(tabPr[x].payment>tabPr[y].payment)return 1; 
	else return -1;  	 
}

int ComparePresenterPresentations (const void * a, const void * b){

	int x = *(int*)a;
	int y = *(int*)b;
	if(tabPr[x].presentations.lenght>tabPr[y].presentations.lenght) return 1; 
	else if (tabPr[x].presentations.lenght==tabPr[y].presentations.lenght) return 0; 
	else return 0; 
}

int ComparePresentationName (const void * a, const void * b){

	int x = *(int*)a;
	int y = *(int*)b;
	return strcmp(tabPn[x].name,tabPn[y].name); 
}

int ComparePresentationType (const void * a, const void * b){

	int x = *(int*)a;
	int y = *(int*)b;
	if(tabPn[x].type==tabPn[y].type)return 0; 
	else if(tabPn[x].type>tabPn[y].type)return 1; 
	else return -1;   
}

