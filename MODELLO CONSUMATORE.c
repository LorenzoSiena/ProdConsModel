                                       //CONSUMATORE
#include <unistd.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include "libsemaforo.h"

 #define N 10
 #define SEM_KEY_W (key_t) 6666
 #define SEM_KEY_R (key_t) 9999
 #define SEM_KEY (key_t) 1234
 
 int vettore [N]; //var globale
 
 
 int main(void){
 
 int writeID,readID;
 int run=1;
 //Variabili Shared Memory
 int shmID;
 int *p;
 void *shmP=(void *)0; //NULL?
 
 //CREO I SEMAFORI
 writeID=semget(SEM_KEY_W,1,IPC_CREAT|0666);
 if (writeID==-1){
    fprintf(stderr,"Creazione semaforo write fallita");
    exit(EXIT_FAILURE);
 }
 readID=semget(SEM_KEY_R,1,IPC_CREAT|0666);
 if (readID==-1){
    fprintf(stderr,"Creazione semaforo read fallita");
    exit(EXIT_FAILURE);
 } 
 //SETTO I SEMAFORI
 SEM_SET(writeID,1); //semaforo write ->1
 SEM_SET(readID,0); //semaforo read ->0
 
 //CREO SHM
 shmID=shmget(SEM_KEY,N*sizeof(int),IPC_CREAT|0666); //alloco array di N int
 if (shmID==-1){
    fprintf(stderr,"Errore allocazione memoria condivisa");
    exit(EXIT_FAILURE);
 }
 //Aggancio la memoria
 shmP=shmat(shmID,NULL,NULL);
 if (shmP==(void *)-1){
    fprintf(stderr,"Errore aggancio memoria condivisa");
    exit(EXIT_FAILURE);
 }
 p=(int *)shmP; //puntatore castato a int sulla memoria in cui voglio scrivere
 printf("Memoria Agganciata correttamente all'indirizzo %p\n",p);
 printf("Memoria Agganciata correttamente all'indirizzo %X\n",p);
 
 
 while (run)
 {
       
    SEM_WAIT(readID);
    
    //routine consumatore
    
    SEM_SIGNAL(writeID);
 
 }
 
 //sgancio memoria
 if (shmdt(shmP)==-1){
    fprintf(stderr,"Errore sgancio memoria condivisa");
    exit(EXIT_FAILURE);
 }
 //cancello memoria
 if (shmctl(shmID,IPC_RMID,0)==-1){
    fprintf(stderr,"Errore rimozione memoria condivisa");
    exit(EXIT_FAILURE);
 }
 
 //elimino semaforo WRITE
 if (SEM_DEL(writeID)==-1){
    fprintf(stderr,"Errore eliminazione semaforo WRITE");
    exit(EXIT_FAILURE);
 }
 
 //elimino semaforo WRITE
 if (SEM_DEL(readID)==-1){
    fprintf(stderr,"Errore eliminazione semaforo READ");
    exit(EXIT_FAILURE);
 }
 
 exit(EXIT_SUCCESS);
 }
 
