#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main( void )
{
    int status;
    char *args[5];

    //args[0] = "stat --format=\"%n\"";        // first arg is the full path to the executable
    args[0]="stat";
    args[1]="--format";
    args[2]="%A %h %U %G%6s %.16y %N ";
    args[3]="sim.c";
    args[4]="mycp.c";
    args[5]="hsl.txt";
    args[6] = NULL;             // list of args must be NULL terminated

    //if ( fork() == 0 )
        //execv("/bin/stat",args); // child: call execv with the path and the args
    //else
      //  wait( &status );        // parent: wait for the child (not really necessary)
	//execl("/bin/stat","stat","--format","%n","sim.c",NULL);
    execvp("stat",args);	
    return 0;
}

