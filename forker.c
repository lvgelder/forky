#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int childdepth = 0;
int main(void) 
{
   char* line;
   line = malloc(sizeof(char)*20);
	
   printf("Child %d says: Tell me something interesting... ", childdepth);
   fgets(line, 20, stdin);
	
	printf("You entered: %s\n", line);
	printf("strcmp says %d\n", strcmp(line, "undo\n"));
	if(!strcmp(line,"undo\n")){
		exit(42);
	} else {
	pid_t pid = fork();
   int status;

   if (pid == 0) {
		childdepth ++;
      printf("Hello from the child process!\n");
		printf("You entered: %s\n", line);
		return main();
   } else {
      waitpid(pid, &status, 0);
		int exitstatus = WEXITSTATUS(status);
		if(exitstatus == 42){
			printf("I got asked to undo my last thing! childdepth %d", childdepth);
			main();
		} else {
			printf("just quit and don't undo");
			exit(4);
		}
      printf("Child process died and told us %d %d :(\n", WEXITSTATUS(status), pid);			
	}
	}

   return 0;
}
