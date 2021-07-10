#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wait.h>
#include <errno.h>
#include <semaphore.h>

int main(int argc, char* argv[])
{
	int i;		// loop variable
	key_t shmkey;	// shared memory key
	int shmid; 	// shared memory id
	sem_t* sem;	// sync semaphore
	pid_t pid;	
	int* p;		// shared variable
	unsigned int n;	// fork count
	unsigned int value; 	// semaphore value

	// initialize a shared variable in shared memory
	shmkey = ftok("/dev/null", 5); // valid directory name and a number
	if(shmkey < 0)
	{
		perror("ftok\n");
		exit(1);
	}
	printf("shmkey for p = %d\n", shmkey);
	shmid = shmget(shmkey, sizeof(int), 0644 | IPC_CREAT);
	if(shmid < 0)
	{
		perror("shmget\n");
		exit(1);
	}

	p = (int*)shmat(shmid, NULL, 0);	// attach p to shared memory
	*p = 0;
	printf("p = %d is allocated in shared memory.\n\n", *p);

	printf("How many children do you want to fork?\n");
	printf("Fork count: ");
	scanf("%u", &n);

	printf("What do you want the semaphore init value to be?\n");
	printf("Semaphore init value : ");
	scanf("%u", &value);

	// initialize semaphore
	sem = sem_open("p_sem", O_CREAT, 0644, value);
	if(sem == SEM_FAILED)
	{
		perror("sem_open\n");
		exit(0);
	}
	
	printf("semaphores initialized.\n\n");

	for(i = 0; i < n; ++i)
	{
		switch(fork())
		{
			case -1:
			{
				/* check for error      */
				sem_unlink ("p_sem");   
				sem_close(sem);  
				/* unlink prevents the semaphore existing forever */
				/* if a crash occurs during the execution         */
				printf ("Fork error.\n");
			}

			case 0:
			{
				sem_wait (sem);           /* P operation */
				printf ("  Child(%d) is in critical section.\n", i);
				
				if(i % 2 == 0)
					*p += 1;
				else
					*p -= 1;

				printf ("  Child(%d) new value of *p= %d.\n", i, *p);
				sem_post (sem);           /* V operation */
				exit (0);
			}

			default:
			{
				break;
			}
		}
	}

	/* wait for all children to exit */
	wait(NULL);

	printf ("\nParent: All children have exited.\n");

	/* shared memory detach */
	shmdt (p);
	shmctl (shmid, IPC_RMID, 0);

	/* cleanup semaphores */
	sem_unlink ("p_sem");   
	sem_close(sem);  
	/* unlink prevents the semaphore existing forever */
	/* if a crash occurs during the execution         */
	exit (0);
}