#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define SECRET "NOTSOSECRET"
pid_t myCreateProcess(char *); 
char prompt[20], instream[50];
	int status;
	int i = 0, ext = 0, inc = 0;
	static int inputcnt = 0;
main() {

// variables and declarations
	
	prompt[0] = '>';
	prompt[1] = ' ';
	
// shell
	while (ext == 0) {
		
		printf("%s", prompt);
		
		char w = 'x';
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

		//printf("current input[%s]\n",instream);
		w = '\0';
		inc = 0;

	// exiting
		if ((((instream[0] == 'Q')|| (instream[0] == 'q')) && (instream[1] == '\n')) ||
	  	  (((instream[0] == 'Q')|| (instream[0] == 'q')) && 
	  	  ((instream[1] == 'U')|| (instream[1] == 'u')) &&
	  	  ((instream[2] == 'I')|| (instream[2] == 'i')) &&
	  	  ((instream[3] == 'T')|| (instream[3] == 't'))))
			ext = 1;

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

	// Custom (inspiration)
		else if (instream[0] == 'I' &&
			instream[1] == 'm' &&
			instream[2] == ' ' &&
			instream[3] == 's' &&
			instream[4] == 'a' &&
			instream[5] == 'd' ) 
			printf("You can do it!!! \n");

		
		else {
			
			instream[inputcnt - 1] = '\0';
			pid_t x = myCreateProcess(instream);
			printf("%d", x);
		}




		for (i = 0; i < 50; i++)
				instream[i] = '\0';
	}
}


pid_t myCreateProcess(char *w) {

//printf("%d \n",inputcnt);
			//system(instream);
			//fprintf(stdout,"about to run: %s\n", instream); 
			//execl(instream,instream,NULL);
			//fprintf(stdout, "Hello world?\n");
			//fflush(stdout);
			int k = 0;
			
			k = fork();
			
			if (k==0) {
  			// child code
				fprintf(stdout,"about to run: %s\n", w); 
    	  		execlp(w, w,NULL);
				ext = 1;
				fprintf(stdout, "Hello world?\n");
				fflush(stdout);
  			}
  			else if (k == -1){
  				printf("error has occured!!!");
				ext = 1;
				exit(1);
  			}
			else {
				// parent code
				//waitpid(k, &status, 0); // it fixed a bug that i had and now it is back
				return k;			
			}
} 




