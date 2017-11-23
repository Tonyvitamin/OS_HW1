#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>	
#include <stdlib.h>

char * cmdtowork[65526];

int command(char * input)
{

	char * tmpforinput;
	int cmt=1;
		//printf("\n%s\n", input );
	tmpforinput = strtok(input , " \t\n");

	//printf("%s\n", "error ocurr here");
	//printf("%s\n", tmpforinput );
	cmdtowork[0] = strdup(tmpforinput);
	while((tmpforinput = strtok(NULL , " \t\n"))!=NULL)
	{
		cmdtowork[cmt] =strdup( tmpforinput);
		int tmp = strlen(cmdtowork[cmt]);
		cmt++;

	}
	if(cmdtowork[cmt-1]=="&")
		{
			printf("%s\n",cmdtowork[cmt-1] );
			cmdtowork[cmt-1]=NULL;
		}
	else 
		cmdtowork[cmt] = NULL;
}


int main()
{

	//printf("%c" , '>');
	for(;;)
	{	
		int x=0;
		int status = 0;
		char *tmpforinput;
		char input[127];
		memset(input , 0 , sizeof(input));
		//int lengthofinput;
		//size_t cmt = 0;
 		/*if(x==1)
 		{
 			printf("%c" , '>');
 			x=0;
 		}*/

		pid_t pid , child_pid;
		pid = vfork();
	
		if(pid<0) /*error happened */
		{
			fprintf(stderr , "Fork failed");
			exit(-1);
		}

		else if(pid == 0) /*child process*/
		{
			//printf("Child PID=%d",getpid());
			printf(">");
			fgets(input, 12700 , stdin);
			//memset(input , '\0' , sizeof(input));

			if(strlen(input)==1)
			{
				continue;
			}
			if(input[(int)strlen(input)-2]=='&')
			{

				input[(int)strlen(input)-2]='\n';
						//printf("%d\n", x );

				x=1;
			}
			if(input[0]=='e'&&input[1]=='x'&&input[2]=='i'&&input[3]=='t')
			{
				status = 1;
				exit(0);
			}

			command(input);
				
				if(x)
				{
					child_pid = fork();
					//printf("grandchild work here\n");
					
					if(child_pid == 0)
						execvp(cmdtowork[0] , cmdtowork);
					else if(child_pid < 0)
					{
						fprintf(stderr, "%s\n", "child handle grandchild process go wrong" );
						exit(1);
					}
					else 
					{
							//printf("child which handle grandchild work here\n");
							//wait(NULL);
							exit(0);
					}

				}
				else
				{
					//printf("child work here \n");
					execvp(cmdtowork[0] , cmdtowork);
				}
				printf("%s\n", "child process go wrong");
				exit(1);
		}

		else { /*parent process*/
				//printf("%d\n", x );
			/*if(x)
				{
								
					waitpid(pid , NULL ,WNOHANG);
					printf(">");
					x=0;
				}*/
			//else
			//	{
					//printf("Parent PID=%d\n",getpid());	
					wait(NULL);
					//printf("%s\n", "parent wait here" );
					if(status)
					{
						exit(0);
					}
					//printf("Parent PID=%d",getpid());
			//	}
		}
	}
}
