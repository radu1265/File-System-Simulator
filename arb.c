//ANGHELESCU Radu Mihai 314CB
#include "arb.h"

arb_dir init_ROOT(){

    arb_dir root = (arb_dir)malloc (sizeof(nod_dir));
    if(!root)
        return NULL;

    strcpy(root->nume, "root");
    root->dr = NULL;
    root->st = NULL;
    root->arb_fisier = NULL;
    root->parinte = NULL;
    root->sub_directories = NULL;
    
    return root;
}

arb_dir init_dir_arb(char *s, arb_dir parinte){

    arb_dir aux = (arb_dir)malloc (sizeof(nod_dir));
    if(!aux)
        return NULL;

    strcpy(aux->nume, s);
    aux->dr = NULL;
    aux->st = NULL;
    aux->arb_fisier = NULL;
    aux->parinte = parinte;
    aux->sub_directories = NULL;
    
    return aux;
}

arb_file init_file_arb(char *s, arb_dir parinte){

    arb_file aux = (arb_file)malloc (sizeof(nod_file));
    if(!aux)
        return NULL;

    strcpy(aux->nume, s);
    aux->dir_parinte = parinte;
    aux->st = NULL;
    aux->dr = NULL;

    return aux;
}

int cautare_file(char *s, nod_file* root_file){

    if(root_file == NULL) return 0;

    if(strcmp(root_file->nume, s) == 0)
        return 1; // exista numele in interiorul arborelui de fisiere

    if(strcmp(root_file->nume, s) > 0)
        return cautare_file(s, root_file->st);

    if(strcmp(root_file->nume, s) < 0)
        return cautare_file(s, root_file->dr);

    return 0; //nu exista numele
}

int cautare_dir(char *s, nod_dir* root){

    if(root == NULL) return 0;

    if(strcmp(root->nume, s) == 0)
        return 1; // exista numele in interiorul arborelui de foldere

    if(strcmp(root->nume, s) > 0)
        return cautare_dir(s, root->st);

    if(strcmp(root->nume, s) < 0)
        return cautare_dir(s, root->dr);

    return 0; //nu exista numele
}

int inserare_file(arb_file arb, char *s, arb_dir dir_parinte){
    	
	arb_file aux;
    arb_file cp, parinte; //parinte = parintele copiei

    if(arb == NULL){

        arb = init_file_arb(s, dir_parinte);
        if(!arb) 
            return -1;

        return 1;
    }

    cp = arb;

    while(cp){

        parinte = cp;
        if(strcmp(s, cp->nume) == 0){
		    return 0;
        }

        if(strcmp(s, cp->nume) > 0)
            cp = cp->dr;

	    else if(strcmp(s, cp->nume) < 0)
            cp = cp->st;
    }

    aux = init_file_arb(s, dir_parinte);

    if(strcmp(parinte->nume, aux->nume) > 0)
        parinte->st = aux;

    if(strcmp(parinte->nume, aux->nume) < 0)
        parinte->dr = aux;

    return 1;
}

void afisare_file(arb_file arb){

    if(arb == NULL)
        return;

    afisare_file(arb->st);
    printf("%s ",arb->nume);
    afisare_file(arb->dr);
}

void afisare_dir(arb_dir arb){

    if(arb == NULL)
        return;

    afisare_dir(arb->st);
    printf("%s ",arb->nume);
    afisare_dir(arb->dr);
}

int inserare_dir(arb_dir arb, char *s, arb_dir dir_parinte){
    	
	arb_dir aux;
    arb_dir cp, parinte = NULL;

    if(arb == NULL){

        arb = init_dir_arb(s, dir_parinte);
        if(!arb)
            return -1;
            
        return 1;
    }

    cp = arb;

    while(cp){

        parinte = cp;
        if(strcmp(s, cp->nume) == 0){
		return 0;
        }

        if(strcmp(s, cp->nume) > 0)
            cp = cp->dr;

	    else if(strcmp(s, cp->nume) < 0)
            cp = cp->st;
    }

    aux = init_dir_arb(s, dir_parinte);
    
    if(strcmp(parinte->nume, aux->nume) > 0)
        parinte->st = aux;

    if(strcmp(parinte->nume, aux->nume) < 0)
        parinte->dr = aux;

    return 1;
}

arb_file min_file(arb_file arb){

    arb_file aux = arb;

    while(aux && aux->st != NULL)
        aux = aux->st;

    return aux;
}

arb_dir min_dir(arb_dir arb){

    arb_dir aux = arb;

    while(aux && aux->st != NULL)
        aux = aux->st;

    return aux;
}

void free_file(arb_file arb){

    if(arb == NULL) return;

    free_file(arb->st);
    free_file(arb->dr);

    free(arb); 
}

void free_dir(arb_dir arb){

    if(arb == NULL) return;
    
    free_dir(arb->st);
    free_dir(arb->sub_directories);
    free_dir(arb->dr);

    free_file(arb->arb_fisier);

    free(arb); 
}
