#include "../headers/cat.h"

List listofcatalogues; 
extern List listofpresenters; 

void PrintCatHeader(FILE *stream){
	fprintf(stream,"|Nazwa,  Typ, Lista Elementów...|\n"); 
}

int PrintCat(Cat *tmp, FILE *stream){

	Element *temp; 
	Presenter *this; 
	Presentation *him; 
	temp = tmp->listofelements.head;
	
	fprintf(stream,"%s, %s",tmp->name, tmp->type); 

	if(strcmp(tmp->type,"presenter")){
		
		while(temp!=NULL){
			this = (Presenter*)temp->obj; 
			fprintf(stream,"%s;",this->pn); 		
			temp = temp->next; 
		}
	}

	if(strcmp(tmp->type,"presentation")){
		
		while(temp!=NULL){
			him = (Presentation*)temp->obj; 
			fprintf(stream,"%s;",him->pn); 		
			temp = temp->next; 
		}
	}
	fprintf(stream,"\n");
	return 1;  
}

int AddToCat(void *element, Cat *catalogue){

	if(addnode(element,&(catalogue->listofelements)))return 1; 
	
	return 0; 
} 

void PrintCatTable(FILE *stream){
	Element *temp; 
	temp = listofcatalogues.head; 
	PrintCatHeader(stream); 
	
	while(temp!=NULL){
		PrintCat(temp->obj,stream); 
	}	
}

List *FindInCats(char *id){
	Element * templ;
	Element * tempp;  
	Presenter *this; 
	Presentation *him; 
	templ = listofcatalogues.head; 
	while(templ!=NULL){

		if(strcmp(((Cat*)templ->obj)->type,"presenter")){

			tempp = ((Cat*)templ->obj)->listofelements.head; 
			while(tempp!=NULL){
				this = (Presenter*)(tempp->obj);
				if(strcmp(this->pn,id))return &(((Cat*)tempp->obj)->listofelements); 
				tempp = tempp->next; 
			}
			templ = templ->next;
		}

		if(strcmp(((Cat*)templ->obj)->type,"presentation")){

			tempp = ((Cat*)templ->obj)->listofelements.head; 
			while(tempp!=NULL){
				him = (Presentation*)(tempp->obj);
				if(strcmp(him->pn,id))return &(((Cat*)tempp->obj)->listofelements); 
				tempp = tempp->next; 
			}
			templ = templ->next;
		}

	}
	return NULL; 
}

Cat *AddCat(char fields[]){
	Cat *newcat;
	char dump[] =";"; 
	char * token; 
	char stemp[1024]; 
	int i=1; 
	int j; 
	newcat = calloc(1,sizeof(Cat)); 
	if(newcat==NULL)return NULL;

	
	strcpy(fields,stemp); 
	token = strtok(stemp,dump); 
	while(token!=NULL){
		if(i==1){
			for(j=0; j<strlen(token); j++){
				if(!isalpha(token[j])){Msg(INPUT_ERR,i);return NULL;}
			}
			strcpy(token,newcat->name); 
		}
		if(i==2){
			for(j=0; j<strlen(token); j++){
				if(!isalpha(token[j])){Msg(INPUT_ERR,i);return NULL;}
			}
			strcpy(token,newcat->type); 
		}
		if(i>=3){
			for(j=0; j<strlen(token); j++){
				if(!isdigit(token[j])){Msg(INPUT_ERR,i);return NULL;}
			}
			if(AddToCat(FindPresenter(token,&listofpresenters),newcat)){Msg(INPUT_ERR,i);return NULL;};   
		}
		token = strtok(NULL, dump); 
		i++; 
	}
	return newcat; 
}	
