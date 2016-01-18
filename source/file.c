#include "../headers/file.h"

FILE *fileraw;

extern List listofpresenters;
extern List listofpresentations;
extern List listofcatalogues;

FILE *CreateBin(char *filename,FILE *filepointer){

	filepointer = fopen(filename,"wb");
	if(filepointer==NULL) return NULL;
	return filepointer;
}

int CreateRaw(char *filename,FILE *filepointer) {

	filepointer = fopen(filename,"w");
	if(filepointer==NULL) return 1;
	return 0;
}

int OpenBin(char *filename, FILE *filepointer){

	filepointer = fopen(filename,"rb+");
	if(filepointer == NULL)return 1;
	return 0;
}

int OpenRaw(char *filename,FILE *filepointer){

	filepointer = fopen(filename,"r+");
	if(filepointer == NULL)return 1;
    return 0;
}

int SaveBin(char *passwd,FILE *filepointer){
	char line[1024];
	FILE *rawpointer;
	rawpointer = fopen("temp","w");
	if(rawpointer==NULL)return 1;
	SaveRaw(rawpointer);
	rawpointer = fopen("temp","r");

	rewind(filepointer);
	strcpy(line,passwd);
	fwrite((void*)line,sizeof(line),1,filepointer);
	while(!feof(rawpointer)){
		fgets(line,1024,rawpointer);
		fwrite((void*)line,sizeof(line),1,filepointer);
	}
    fclose(rawpointer);
    remove("temp");
	fclose(filepointer);
	return 0;

}

int SaveRaw(FILE *filepointer){

	PrintFileHeader(filepointer);
	PrintPresenterHeader(filepointer);
	PrintPresenterFile(filepointer);
	PrintPresentationHeader(filepointer);
	PrintPresentationFile(filepointer);
	PrintCatHeader(filepointer);
	PrintCatTable(filepointer);
	fclose(filepointer);
	return 0;
}

int LoadBin(char *passwd,FILE *filepointer){

	char line[1024];
	int control=0;
	fread((void *)line,sizeof(line),1,filepointer);
	if(strcmp(line,passwd))return 2;
	for(;!feof(filepointer);){
		fread((void *)line,sizeof(line),1,filepointer);
		if(line[0]=='1'){control= 1;fread((void *)line,sizeof(line),1,filepointer);}
		if(line[0]=='2'){control= 2;fread((void *)line,sizeof(line),1,filepointer);}
		if(line[0]=='3'){control= 3;fread((void *)line,sizeof(line),1,filepointer);}
		if(line[0]!='#'){

            switch (control){
                case 1:
                if(addnode((void*)AddPresenter(line),&listofpresenters))return 1;
                break;
                case 2:
                if(addnode((void*)AddPresentation(line),&listofpresentations))return 1;
                break;
                case 3:
                if(addnode((void*)AddCat(line),&listofcatalogues))return 1;
                break;
            }
		}
		fread((void *)line,sizeof(line),1,filepointer);
	}
	fclose(filepointer);
	return 0;
}

int LoadRaw(FILE *filepointer){
	int control=0; /*0-Presenter 1-Presentation 2-Catalogues*/
	char line[1024];

	for(;!feof(filepointer);){
		fgets(line,1024,fileraw);
		if(line[0]=='1'){control= 1;fgets(line,1024,filepointer);}
		if(line[0]=='2'){control= 2;fgets(line,1024,filepointer);}
		if(line[0]=='3'){control= 3;fgets(line,1024,filepointer);}
		if(line[0]!='#'){

			switch (control){
				case 1:
				if(addnode(AddPresenter(line),&listofpresenters))return 1;
				break;
				case 2:
				if(addnode(AddPresentation(line),&listofpresentations))return 1;
				break;
				case 3:
				if(addnode(AddCat(line),&listofcatalogues))return 1;
				break;
			}
		}
		fgets(line,1024,filepointer);
	}
	fclose(filepointer);
	return 0;
}

void PrintFileHeader(FILE *stream){
	fprintf(stream,"#Plik z danymim do programu WSPOMAGANIE ORGANIZACJI KONFERENCJI\n");
	fprintf(stream,"#komentarze rozpoczynaja sie od #\n");
}

void PrintPresenterHeader(FILE *stream){
	fprintf(stream,"1 Imie;Nazwisko;Afiliacje;Rodzaj prezentacji;Status platnosci;id prezentacji...\n");
}

void PrintPresentationHeader(FILE *stream){
	fprintf(stream,"2 Nazwa;Typ;Id prezentera\n");
}
