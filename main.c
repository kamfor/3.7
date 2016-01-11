/* wspomaganie organizacji konferencji*/
#include<stdio.h>
#include<string.h>
#include "headers/debug.h" 
#include "headers/userface.h"
#define DEBUG 0
 
int main(){

	if(DEBUG)Debug();
	else Begin(); 
	return 0; 	
}
