#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*

struct per definire le informazioni del labirinto 

*/

struct labirinto_t
{
    char *lab;
    int rows;
    int cols;
};

struct exit_coord
{
    int exit_cols;
    int exit_rows;
};

struct current_coord
{

    int current_cols;
    int current_rows;

};


void print_labirint(struct labirinto_t mylabirint){

    for(int i=0; i<mylabirint.rows; i++){
        for (int j=0; j<mylabirint.cols;j++)
            printf("%c", mylabirint.lab[j+i*mylabirint.cols]);
        printf("\n");
    }
}
    /*
    se voglio labirinto che venga messo dall'utente devo usare una malloc
    
    */

//funzione che mi da il labirinto iniziale mi servono le cols e rows
char *labirint(struct labirinto_t mylabirint){
    
    int k=0;
    mylabirint.lab = (char*) malloc (mylabirint.cols*mylabirint.rows*sizeof(char));//array di dimesioni date in input size of char == 1 
    if(mylabirint.lab==0) exit(EXIT_FAILURE);//check per in caso di malloc non funzionante 
    for(int i=0; i<mylabirint.rows; i++){
            scanf(" %[^\n]s", &mylabirint.lab[i+k]);//[^\n] include whitespaces 
            k+=mylabirint.cols-1;
    }
    return mylabirint.lab;
}


//trovo fine del labirinto possiamo farla ricorsiva anche trovo inizio

/*
    scorro tutto l'array e vedo quando è == '_' 
    quando è così tiro fuori exit_cols e exit_rows
    
*/
//start_or_exit con macros??
int find_exit_and_start(struct labirinto_t mylabirint, int *rows, bool start_or_exit){

    for(int i=0; i<mylabirint.rows; i++){
        for (int j=0; j<mylabirint.cols;j++){
            if (start_or_exit==1){
            if(mylabirint.lab[j+i*mylabirint.cols]== '_' ){
                *rows=i;
                return j;
            };
            }else{
            if(mylabirint.lab[j+i*mylabirint.cols]== 'o' ){
                *rows=i;
                return j;
            };
            }
        }
    }
}

bool mosse_recursive(struct exit_coord exit, struct current_coord current){
    printf("cols %d rows %d\n", current.current_cols, current.current_rows);

    /*
    caso base esco quando le coordinate correnti sono uguali alle coordinate di uscita(entrambe quindi &&)
    chiedo la mossa 
    modifico le coordinate e richiedo la funzione 
    */

    if(current.current_cols==exit.exit_cols && current.current_rows==exit.exit_rows) return 0;//fine
    char mouve;//uso WASD
    scanf(" %c", &mouve);
    switch (mouve){

        case ('W'):{
            current.current_rows++;
            mosse_recursive(exit, current);
        }
            break;
        case ('S'):{
            current.current_rows--;
            mosse_recursive(exit, current);
        }
            break;
        case('A'):{
            current.current_cols--;
            mosse_recursive(exit, current);
        }
            break;
        case('D'):{
            current.current_cols++;
            mosse_recursive(exit, current);
        }
            break;

        default:
            break;
    }
    
}



int main(int argc, char *argv){//per selezionare challenge
    bool start_or_exit;
    struct labirinto_t mylabirint;
    
    scanf(" %d",&mylabirint.cols);
    scanf(" %d",&mylabirint.rows);
    
    
    mylabirint.lab=labirint(mylabirint);
    print_labirint(mylabirint);

    struct exit_coord exit_coord;
    struct current_coord current_coord;
    start_or_exit=1;//1 faccio exit
    exit_coord.exit_cols = find_exit_and_start(mylabirint, &exit_coord.exit_rows,start_or_exit);
    printf("exit %d %d ", exit_coord.exit_cols, exit_coord.exit_rows); 

    start_or_exit=0;//0 faccio start
    current_coord.current_cols = find_exit_and_start(mylabirint, &current_coord.current_rows,start_or_exit);
    printf("start %d %d ", current_coord.current_cols, current_coord.current_rows);

    mosse_recursive(exit_coord, current_coord);

    free(mylabirint.lab);   
    return 0;
}