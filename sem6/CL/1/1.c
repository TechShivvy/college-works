#include "1.h"

char c,*filename="/home/cse1100/SSN/sem6/CL/input.c";

int main(int argc, char* argv[]){
    // if(argc < 2){
    //     printf("Give program name and file name as arguments!\n");
    //     exit(EXIT_FAILURE);
    // }
    // int fd = open(argv[1], O_CREAT);
    // if(fd == -1){
    //     perror("file");
    //     exit(EXIT_FAILURE);
    // }
    // char prog[500];
    // int count = read(fd, (char*) prog, 500);
    // printf("The program is :\n%s\n\n", prog);
    // parse_program(prog);
    fp=fopen(filename,"r");
	if(!fp)
	{
        printf("\n The file could not be opened / Not available");
		return 0;
	}
	parse();
    return 0;
}

