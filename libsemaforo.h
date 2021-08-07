//NB questa libreria è valida solo per semafori modimensionali


#include <sys/sem.h>


/*Parametri inizializzazione semaforo*/
union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

/*inizializza il semaforo [0]*/
int SEM_SET(int sem_id, int sem_val) {
	union semun sem_union;
	sem_union.val = sem_val;
	return semctl(sem_id, 0, SETVAL, sem_union);
}

/*Elimina l'intero array di semaforo*/
int SEM_DEL(int sem_id){
	return semctl(sem_id, 0, IPC_RMID);
}

/*WAIT()*/
int SEM_WAIT(int sem_id){
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = -1;
	sem_b.sem_flg = SEM_UNDO;
	return semop(sem_id, &sem_b, 1);
}

/*SIGNAL*/
int SEM_SIGNAL(int sem_id){
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = 1; 
	sem_b.sem_flg = SEM_UNDO;
	return semop(sem_id, &sem_b, 1);
}
