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
    int cols;
    int rows;
};

struct current_coord
{

    int cols;
    int rows;

};


typedef struct labirinto_t lab_t;
typedef struct exit_coord exit_t;
typedef struct current_coord current_t;

/*
devo fare una funzione che modifichi il labirinto con la posizione aggiornata del player
+ stampare il tragitto del player con .
+ fare funzione per calcolare il tragitto
+ point system 
*/

int punteggio=1000;//not so good

void points(lab_t labt, current_t current){

    punteggio--;
    if(labt.lab[current.cols+current.rows*labt.cols]=='$') punteggio = punteggio+10;
    if(labt.lab[current.cols+current.rows*labt.cols]=='!') punteggio = punteggio/2;

}


char *modify_labirint(lab_t mylabirint, current_t current){
    //devo togliere quello di prima 
    //pos soluzione cerco tutto l'array per o e lo elimino poi ci metto o nuovo
    
    for(int i=0; i<mylabirint.rows; i++){
        for (int j=0; j<mylabirint.cols;j++)
            if(mylabirint.lab[j+i*mylabirint.cols]=='o'){
                mylabirint.lab[j+i*mylabirint.cols]=' ';
            }
    }
    mylabirint.lab[current.cols+current.rows*mylabirint.cols] = 'o';
    return mylabirint.lab;

}

void print_labirint(lab_t mylabirint){

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
char *get_labirint(lab_t mylabirint){
    
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
int find_exit_and_start(lab_t mylabirint, int *rows, bool start_or_exit){

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

bool mosse_recursive(lab_t labt, exit_t exit, current_t current){
    printf("cols %d rows %d\n", current.cols, current.rows);
    points(labt, current);
    char mouve;//uso WASD
    if(labt.lab[current.cols+current.rows*labt.cols]=='_') return 0;//fine
    //devo passare il lab non modificato

    labt.lab = modify_labirint(labt, current);
    print_labirint(labt);

    scanf(" %c", &mouve);
    switch (mouve){
        //farei una fnuzione che controlla cosa c'è nella posizione 
        //current con switch case e agirei di conseguenza con le mosse i punti etc..
        case ('W'):{
            if(labt.lab[current.cols+(current.rows-1)*labt.cols]!='#'){
            current.rows--;
            mosse_recursive(labt, exit, current);
            }else if(labt.lab[current.cols+(current.rows-1)*labt.cols]=='#'){
            mosse_recursive(labt, exit, current);
            }
        }
            break;
        case ('S'):{
            if(labt.lab[current.cols+(current.rows+1)*labt.cols]!='#'){
            current.rows++;
            mosse_recursive(labt, exit, current);
            }else if(labt.lab[current.cols+(current.rows+1)*labt.cols]=='#'){
            mosse_recursive(labt, exit, current);
            }
            
        }
            break;
        case('A'):{
            if(labt.lab[(current.cols-1)+current.rows*labt.cols]!='#'){
            current.cols--;
            mosse_recursive(labt, exit, current);
            }else if(labt.lab[(current.cols-1)+current.rows*labt.cols]=='#'){
            mosse_recursive(labt, exit, current);
            }
            
        }
            break;
        case('D'):{
            if(labt.lab[(current.cols+1)+current.rows*labt.cols]!='#'){
            current.cols++;
            mosse_recursive(labt, exit, current);
            }else if(labt.lab[(current.cols+1)+current.rows*labt.cols]=='#'){//forse riducibile potrebbe creare problemi
            mosse_recursive(labt, exit, current);
            }
        }
            break;
//se scrivi qualsiasi altra cosa non cambio le coord e ti chiedo prossima mossa
        default:    mosse_recursive(labt, exit, current);
            break;
    }


}


int main(int argc, char *argv){//per selezionare challenge
    
    bool start_or_exit;
    lab_t mylabirint;
    
    scanf(" %d",&mylabirint.cols);
    scanf(" %d",&mylabirint.rows);
    
    
    mylabirint.lab = get_labirint(mylabirint);
    //print_labirint(mylabirint);

    exit_t exit_coord;
    current_t current_coord;
    start_or_exit=1;//1 faccio exit
    exit_coord.cols = find_exit_and_start(mylabirint, &exit_coord.rows,start_or_exit);
    printf("exit %d %d ", exit_coord.cols, exit_coord.rows); 

    start_or_exit=0;//0 faccio start
    current_coord.cols = find_exit_and_start(mylabirint, &current_coord.rows,start_or_exit);
    printf("start %d %d ", current_coord.cols, current_coord.rows);

    mosse_recursive(mylabirint, exit_coord, current_coord);
    printf("points %d", punteggio);
    free(mylabirint.lab);   
    return 0;
}