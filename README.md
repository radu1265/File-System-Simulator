# File-System-Simulator

  Scopul proiectului:
  
Acest proiect implementează un simulator simplificat de sistem de fișiere folosind limbajul C și Arbori Binari de Căutare (BST). Se concentrează pe funcționalități de bază precum:

Crearea și ștergerea fișierelor/directoarelor
Listarea conținutului directorului curent
Navigarea prin ierarhia directoarelor
Proiectul prioritizează organizarea eficientă prin utilizarea Arborelui Binar de Căutare pentru gestionarea fișierelor, asigurând o căutare rapidă a acestora.

functiile din arb.c sunt functii ajutatoare
functiile din Tema3.c sunt direct apelate in functie de comanda data din terminal

  Functionalitai:

touch/mkdir:
            primeste arborele de subdirectoare, numele fisierului nou, directorul de care apartine
            se apeleaza doua functii recursive de cautare, astfel se ferifica existenta numelui
            daca arborele de fisiere este null atunci se initializeaza si noul fisier devine varful arborelui
            altfel este apelata functia de inserare

rm/rmdir:   
            functii recursive care elimina 1 element din arbore
            se cauta elementul de eliminat, iar dupa gasire se studiaza trei cazuri:
            daca are 1 singur fiu se discuta daca acesta este stang sau drept (primele 2 cazuri)
            atunci cu ajutorul unui auxiliar se pastreaza legatura
            este sters elementul cautat, iar aux este intors
            cazul final cand are 2 fii, se cauta cel mai mic element care il depaseste 
            pe cel de eliminat
            cel de eliminat primeste informatia acestuia 
            si se reapeleaza functia pentru a sterge elementul folosit anterior

cd:         
            parcurge arborele de directories pana cand il gaseste pe cel cerut
            verificarile se fac in main
            discutia pt .. tot in main

pwd:        
            apelez recursiv parintii directories si cand ajung la ultimul(root)
            incep sa ii afisez
