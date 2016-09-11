#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define SECRET "NOTSOSECRET"
void mon_bg(int);
int counter = 0;
char prompt[20];
int main() {
// register signal handler for CTRL-C with OS
     if (signal(SIGCHLD, mon_bg) == SIG_ERR) {
             fprintf(stderr, "signal handler registration failed\n");
                     exit(1);
     }
// variables and declarations
	int status;
	int i = 0, ext = 0, inc = 0;
	static int inputcnt = 0;
	char instream[50];
	getlogin_r(prompt, 20);
// shell
	while (ext == 0) {
		inputcnt = 0;
		printf("%s: ", prompt);
		char w = ' ';
	//input
		while (!(w == '\n' || w == '\0')){ 			
			w = getchar();
  			instream[inc] = w;
  			inc++;
			inputcnt++;
	// return key
			if (instream[0] == '\n') 
			system("clear");


		}
		
		instream[inputcnt - 1] = '\0';
		w = '\0';
		inc = 0;
		
		//printf("[%s]\n",instream);
	// exting
		if ((((instream[0] == 'Q')|| (instream[0] == 'q')) && (instream[1] == '\0')) ||
	  	  (((instream[0] == 'Q')|| (instream[0] == 'q')) && 
	  	  ((instream[1] == 'U')|| (instream[1] == 'u')) &&
	  	  ((instream[2] == 'I')|| (instream[2] == 'i')) &&
	  	  ((instream[3] == 'T')|| (instream[3] == 't')) &&
		  ((instream[4] == '\0'|| (instream[4] == '\0'))))){
			ext = 1;
		}


	// dprompt
		else if (instream[0] == 'd' &&
			instream[1] == 'p' &&
			instream[2] == 'r' &&
			instream[3] == 'o' &&
			instream[4] == 'm' &&
			instream[5] == 'p' &&
			instream[6] == 't') {
			prompt[0] = '>'; 
			prompt[1] = ' ';
			prompt[2] = '\0';		
		}

	// cprompt
		else if (instream[0] == 'c' &&
				instream[1] == 'p' &&
				instream[2] == 'r' &&
				instream[3] == 'o' &&
				instream[4] == 'm' &&
				instream[5] == 'p' &&
				instream[6] == 't' &&
				instream[7] == ' '){
			i = 8;
			inc = 0;
			while(instream[i] != '\n') {
			prompt[inc] = instream[i];
			inc++; 
			i++;				
			}			
			prompt[inc] = ' ';
			prompt[inc + 1] = '\0';
			//printf("prompt[%s]\n",prompt);
			for (i = 0; i < 50; i++)
			instream[i] = '\0';
			inc = 0;
		}
		

	// Custom (inspiration)
		else if (instream[0] == 'I' &&
			instream[1] == 'm' &&
			instream[2] == ' ' &&
			instream[3] == 's' &&
			instream[4] == 'a' &&
			instream[5] == 'd' ) 
			printf("You can do it!!! \n");
			
		else {
			//printf("child in[%s]\n", instream);
			int k = 0;
			//instream[inputcnt - 1] = '\0';
			char *tol, *arr[5], *par[5];
			tol = strtok(instream, " ");
			arr[0] = tol;
			par[0] = tol;
			i = 1;			
			while (tol != NULL){
				tol = strtok (NULL, " ");
				arr[i] = tol;
				par[i] = tol;
				i++;
			}
			arr[i] = NULL;	
			// fork
			i-= 1;			
			k = fork();			
			if (k==0) {
  			//printf("child[%s]\n",arr[i-1]);
			// child code
				if (!(strcmp(arr[i-1], "&")))
					arr[i - 1] = NULL;
				if ( execvp(arr[0], arr) < 0)
					exit(1);
				//fprintf(stdout,"about to run: %s\n", instream); 
				inputcnt = 0;
				execvp(arr[0], arr);
				ext = 1;
				fprintf(stdout, "Hello world?\n");
				fflush(stdout);
				for (i = 0; i < 5; i++)
					arr[i] = '\0';  			
			}
  			else if (k == -1){
  				printf("error has occured!!!");
				ext = 1;
  			}
			else {
				// parent code
				//printf("parent[%s]\n", par[i - 1]);
				if (!(strcmp(par[i - 1], "&")))
					counter++;
				else
					 waitpid(k, &status, 0);
			}
		}
	}
}
void mon_bg(int sigval){
	if (sigval == SIGCHLD && counter != 0) {
		counter-- ;
		int stat;
		pid_t pid;
		pid = wait(&stat);
		fprintf(stdout, "\npid %d has terminated: exit %d \n%s: ", pid, WEXITSTATUS(stat), prompt);
		fflush(stdout);
	} else if(sigval == SIGCHLD) return; 
	else exit(1);
}

/*
// put inside input



*/





