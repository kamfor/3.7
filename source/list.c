#include "../headers/list.h"

int addnode(void *item, List *anlist){

    Element *new;
    if(item==NULL) return 1;
    new=calloc(1,sizeof(Element));
	if((new==NULL))return 1;

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
		(anlist->tail)->next = new;
		anlist->tail = new;
		anlist->lenght++;
	}
	return 0;
}

int delnode(Element *item, List *anlist){
	if(item==NULL)
		return 1;
    if(anlist==NULL)
        return 1;

	if(item==anlist->head){
		anlist->head = item->next;
		if(item->next!=NULL)(item->next)->prev = NULL;
		anlist->lenght--;
		return 0;
	}
	else if(item==anlist->tail){
		anlist->tail = item->prev;
		if(item->prev!=NULL)(item->prev)->next = NULL;
		anlist->lenght--;
		return 0;
	}
	else{
		if(item->next!=NULL)(item->next)->prev = item->prev;
		if(item->prev!=NULL)(item->prev)->next = item->next;
		anlist->lenght--;
		return 0;
	}
	free(item->obj);
	free(item);
}

int dellist(List *anlist){

	Element *temp = anlist->head;

	while(temp!=NULL){

		temp = temp->next;
		free(temp->prev);
	}
	return 0;
}

