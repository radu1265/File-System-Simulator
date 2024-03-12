//ANGHELESCU Radu Mihai 314CB
#include "arb.h"

int touch(arb_dir arb, char *s, arb_dir dir_parinte){

    //creeaza si adauga fisier in arborele de fisiere

    if(cautare_file(s, arb->arb_fisier) == 1){
        printf("File %s already exists!\n", s);
        return 1;
    }

    if(cautare_dir(s, arb->sub_directories) == 1){
        printf("Directory %s already exists!\n", s);
        return 1;
    }

    if(arb->arb_fisier == NULL){

        // arborele trebuie initializat

        arb->arb_fisier = init_file_arb(s, dir_parinte);
        return 0;
    }

    inserare_file(arb->arb_fisier, s, dir_parinte);

    return 0;
}

int mkdir(arb_dir arb, char *s, arb_dir dir_parinte){
    
    //creeaza si adauga sub_directories in arb directorie

    if(cautare_file(s, arb->arb_fisier) == 1){
        printf("File %s already exists!\n", s);
        return 1;
    }

    if(cautare_dir(s, arb->sub_directories) == 1){
        printf("Directory %s already exists!\n", s);
        return 1;
    }

    if(arb->sub_directories == NULL){

        //arb trebuie initializt

        arb->sub_directories = init_dir_arb(s, arb);
        
        return 0;
    }

    inserare_dir(arb->sub_directories, s, dir_parinte);
    
    return 0;
}

arb_file rm(arb_file arb, char *s, arb_dir dir_curent){

    //sterge nod din arborele de fisiere

    if(arb == NULL)
        return arb;

    if(strcmp(arb->nume, s) > 0){
        arb->st = rm(arb->st, s, dir_curent);
    }

    else if(strcmp(arb->nume, s) < 0){
        arb->dr = rm(arb->dr, s, dir_curent);
    }

    // s-a parcurs arborele pana la elementul de sters

    else{

        //cazul in care se elimina nodurile cu un fiu/fara fii

        if(arb->st == NULL){

            //se creaza legatura dintre arborele de dir si fisier 
            //in situatia in care nodul sters este varful

            if(dir_curent->arb_fisier == arb){
                dir_curent->arb_fisier = arb->dr;
            }

            arb_file aux = arb->dr;
            free(arb);
            return aux;
        }

        else if(arb->dr == NULL){

            //se creaza legatura dintre arborele de dir si fisier 
            //in situatia in care nodul sters este varful

            if(dir_curent->arb_fisier == arb){
                dir_curent->arb_fisier = arb->st;
            }

            arb_file aux = arb->st;
            free(arb);
            return aux;
        }

        //cazul cu 2 fii
        //caut elementul cu informatia minima,
        //dar mai mare decat elementul de sters

        arb_file aux = min_file(arb->dr);
        strcpy(arb->nume, aux->nume);

        //se copiaza valoarea peste elementul de sters
        //se reapeleaza functia si se sterge elementul minim

        arb->dr = rm(arb->dr, aux->nume, dir_curent);
    }
    return arb;
}

arb_dir rmdir(arb_dir arb, char *s, arb_dir dir_curent){

    //sterge nod din arborele de dir

    if(arb == NULL)
        return arb;

    if(strcmp(arb->nume, s) > 0){
        arb->st = rmdir(arb->st, s, dir_curent);
    }

    else if(strcmp(arb->nume, s) < 0){
        arb->dr = rmdir(arb->dr, s, dir_curent);
    }

    // s-a parcurs arborele pana la elementul de sters

    else{

        //cazul in care se elimina nodurile cu un fiu/fara fii

        if(arb->st == NULL){

            //se creaza legatura dintre arborele de dir si fisier 
            //in situatia in care nodul sters este varful

            if(dir_curent->sub_directories == arb){
                dir_curent->sub_directories = arb->dr;
            }
            arb_dir aux = arb->dr;
            free(arb);
            return aux;
        }
        else if(arb->dr == NULL){

            //se creaza legatura dintre arborele de dir si fisier 
            //in situatia in care nodul sters este varful

            if(dir_curent->sub_directories == arb){
                dir_curent->sub_directories = arb->st;
            }
            arb_dir aux = arb->st;
            free(arb);
            return aux;
        }
        //cazul cu 2 fii
        //caut elementul cu informatia minima,
        //dar mai mare decat elementul de sters

        arb_dir aux = min_dir(arb->dr);
        strcpy(arb->nume, aux->nume);

        //se copiaza valoarea peste elementul de sters
        //se reapeleaza functia si se sterge elementul minim

        arb->dr = rmdir(arb->dr, aux->nume, dir_curent);
    }
   
    return arb;
}

arb_dir cd(arb_dir arb, char *s){

    arb_dir aux = arb;

    //se parcurge arborele de dir
    //si se intoarce adresa nodului cerut

    while(strcmp(aux->nume, s) != 0){

        if(strcmp(aux->nume, s) > 0)
            aux = aux->st;

        if(strcmp(aux->nume, s) < 0)
            aux = aux->dr;
    }
   return aux;
} 

void pwd(arb_dir arb){

    //afiseaza lista de directoare in ordine

    if(arb == NULL) return;

    pwd(arb->parinte);
    printf("/%s", arb->nume);
}

int main(){

    char *line = malloc(256);

    //line = buffer

    arb_dir root = init_ROOT();
    arb_dir dir_curent = root;

    while(fgets(line, 256, stdin)){

        char* comanda = strtok(line," \n");

        if(strcmp(comanda, "touch") == 0){

            char* nume = strtok(NULL, " \n");
            touch(dir_curent, nume, dir_curent);            
        }

        if(strcmp(comanda, "ls") == 0) {

            afisare_dir(dir_curent->sub_directories);
            afisare_file(dir_curent->arb_fisier);
            printf("\n");
        }

        if(strcmp(comanda, "mkdir") == 0){

            char* nume = strtok(NULL, " \n");
            mkdir(dir_curent, nume, dir_curent);
            
        }

        if(strcmp(comanda, "rm") == 0){

            char* nume = strtok(NULL, " \n");

            if(cautare_file(nume, dir_curent->arb_fisier) == 0){

                printf("File %s doesn't exist!\n", nume);
                continue;
            }
            dir_curent->arb_fisier = rm(dir_curent->arb_fisier, nume, dir_curent);            
        }
        if(strcmp(comanda, "rmdir") == 0){

            char* nume = strtok(NULL, " \n");

            if(cautare_dir(nume, dir_curent->sub_directories) == 0){

                printf("Directory %s doesn't exist!\n", nume);
                continue;
            }
            dir_curent->sub_directories = rmdir(dir_curent->sub_directories, nume, dir_curent); 
        }
        if(strcmp(comanda, "cd") == 0){
            
            char* nume = strtok(NULL, " \n");

            if(strcmp(nume, "..") == 0){
                if(dir_curent->parinte == NULL){

                    printf("Directory not found!\n");
                    continue;
                }
                else{                    
                    dir_curent = dir_curent->parinte;
                }
            }
            else{
                if(cautare_dir(nume, dir_curent->sub_directories) == 0){

                    printf("Directory not found!\n");
                    continue;  
                }                    
                else{
                    dir_curent = cd(dir_curent->sub_directories, nume);
                }
            } 
        }
        if(strcmp(comanda, "pwd") == 0){

            pwd(dir_curent);
            printf("\n");
        }
        if(strcmp(comanda, "quit") == 0){
            
            free(line);
            free_dir(root);           
            return 0;
        }        
    }
            return 0;
}
