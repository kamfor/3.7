#include "../headers/list.h"

int addnode(void *item, List *anlist){

	Element *new; 
	if((new=(Element *)malloc(sizeof(Element)))==NULL)return 1; 

	new->obj = item; 
	
	if(!(anlist->lenght)){
		new->prev = NULL; 
		new->next = NULL; 
		anlist->head = new; 
		anlist->tail = new;
		anlist->lenght++; 
	}
	else{
		new->next = NULL; 
		new->prev = anlist->tail; 
		anlist->tail = new;
		anlist->lenght++;
	}
}

int delnode(Element *item, List *anlist){
	if(item==NULL)
		return 1;

	if(item==anlist->head){
		anlist->head = item->next;
		item->next->prev = NULL; 
		anlist->lenght--; 
		return 0; 
	}
	else if(item = anlist->tail){
		anlist->tail = item->prev; 
		item->prev->next = NULL; 
		anlist->lenght--; 
		return 0; 
	}
	else{
		item->next->prev = item->prev; 
		item->prev->next = item->next; 
		anlist->lenght--; 
		return 0; 
	}

	free(item); 	
}

int dellist(List *anlist){

	Element *temp = anlist->head; 

	while(temp->next!=NULL){

		temp = temp->next; 
		free(temp->prev); 
	}
	
	free(anlist);
}

