                          //Produttore

#include <unistd.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include "libsemafor.h"

#define N 10
#define SEM_KEY_W (key_t) 6666
#define SEM_KEY_R (key_t) 9999
#define SEM_KEY (key_t) 1234

int vettore[N]; //var globale

int main(void){

int writeID,readID;

//Variabili Shared Memory
int shmID;
int *p;
void *shmP=(void *)0;

//Mi allaccio al semaforo WRITE
writeID=semget(SEM_KEY_W,1,IPC_CREAT|0666);
if (writeID==-1){
   fprintf(stderr,"Errore Aggancio semaforo");
   exit(EXIT_FAILURE);
}
//Mi allaccio al semaforo READ
readID=semget(SEM_KEY_R,1,IPC_CREAT|0666);
if (readID==-1){
   fprintf(stderr,"Errore Aggancio semaforo");
   exit(EXIT_FAILURE);
}
//Uso la key per SHM (già creata dal produttore)
shmID=shmget(SEM_KEY,N*sizeof(int),IPC_CREAT|0666);
if (shmID==-1){
   fprintf(stderr,"Errore aggancio semaforo");
   exit(EXIT_FAILURE);
}
//Aggancio la memoria
shmP=shmat(shmID,NULL,NULL);
if (shmP==(void)-1){
   fprintf(stderr,"Errore aggancio memoria");
   exit(EXIT_FAILURE);
}
p=(int *)shmP;

printf("Memoria Agganciata correttamente all'indirizzo %p\n",p);
printf("Memoria Agganciata correttamente all'indirizzo %X\n",p);
 
 
 while (1)
 {
    //routine produttore +semafori
 }
 
 
 
 
//sgancio memoria
if (shmdt(shmP)==-1){
   fprintf(stderr,"Errore sgancio memoria");
   exit(EXIT_FAILURE);
}

exit(EXIT_SUCCESS);
}
