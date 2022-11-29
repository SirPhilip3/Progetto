#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void print_labirint(char *labirint, int rows, int cols){

    for(int i=0; i<rows; i++){
        for (int j=0; j<cols;j++)
            printf("%c", labirint[j+i*cols]);
        printf("\n");
    }
}
    /*
    se voglio labirinto che venga messo dall'utente devo usare una malloc
    
    */

//funzione che mi da il labirinto iniziale mi servono le cols e rows
char* labirint(int cols, int rows){
    
    
    int k=0;
    char *labrint=(char*) malloc (cols*rows*sizeof(char));
    if(labrint==0) exit(EXIT_FAILURE);
    for(int i=0; i<rows; i++){
            scanf(" %[^\n]s", &labrint[i+k]);
            k+=cols-1;
    }

    return labrint;
}

//trovo fine del labirinto possiamo farla ricorsiva anche trovo inizio

/*
    scorro tutto l'array e vedo quando è == '_' 
    quando è così tiro fuori exit_cols e exit_rows

*/
int find_exit(char *labirint, int rows, int cols, int *exit_rows){

    for(int i=0; i<rows; i++){
        for (int j=0; j<cols;j++){
            if(labirint[j+i*cols]== '_' ){
                *exit_rows=i;
                return j;
            };
        }
    }

}

//devo tirare fuori current_cols e current_rows per utilizzarle per fare il nuovo labirinto
void mosse(int exit_cols, int exit_rows){

    //find uscita e ripeti finchè le coordinate sono uguali a quelle dell'uscita
    int current_cols, current_rows;
    //movimento
    char mouvment;
    do
    {
        scanf("%c ", &mouvment);

        switch (mouvment)
        {
        case 'N':{

        }
            break;
        case 'S':{

        }
            break;
        case 'E':{

        }
            break;
        case 'O':{

        }
            break;
        
        default:
            break;
        }



    } while (exit_cols==current_cols && exit_rows==current_rows);
    

}



int main(){

    int rows, cols;
    scanf(" %d",&rows);
    scanf(" %d",&cols);
    
    
    char *lab=labirint(cols,rows);
    
    print_labirint(lab, rows, cols);
    int exit_rows, exit_cols;
    exit_cols = find_exit(lab, rows, cols, &exit_rows);

    //mosse(exit_cols, exit_rows);
    
    printf("%d %d", exit_cols, exit_rows); 
    free(lab);   
    return 0;
}