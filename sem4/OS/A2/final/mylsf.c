#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include<ctype.h>
#include<errno.h>
/*int strcmpi(char const *a, char const *b) //case insensitive comparision
{
    for (;; a++, b++) {
        int d = tolower((unsigned char)*a) - tolower((unsigned char)*b);
        if (d != 0 || !*a)
            return d;
    }
}*/

void check(int *A,int n,char **dirs)   	// to check whether the arg is a dir(1), file(2) or error(0) 
{
	DIR *dh;
	for(int i=0;i<n-1;i++)
	{
		//A[i]=-1			//default
		dh=opendir(dirs[i]);
		if(!dh)
		{
		 	if(!(errno==ENOTDIR))
				A[i]=0;	//error
			else
				A[i]=2;	//file
		}
		else
			A[i]=1;		//dir
		if(A[i]==1)
			A[n-1]=i;		//stores the index of last possible dir
		closedir(dh);
	}
}

void sort(char** A,int n)			//sorts 2d char array
{
	int i,j;
	int s1,s2,y;
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			s1=0,s2=0,y=0;			//s1 corresponds to str1(A[j]) and s2 to str2(A[j+1]) ; y=1 if the swap happens else y=0
			if(A[j][0]=='/')
			{
				++A[j];		//if the 1st char is '/', incrementing ptr
				s1=1;
			}
			if(A[j+1][0]=='/')
			{
				++A[j+1];		//same
				s2=1;
			}
			if(strcasecmp(A[j],A[j+1])>0)
			{				//if the swap is about to happen, decrement the ptrs
				if(s1)			
					--A[j];
				if(s2)
					--A[j+1];
				char* temp;
				temp=(char*)calloc(30, sizeof(char));
				strcpy(temp,A[j]);
				strcpy(A[j],A[j+1]);
				strcpy(A[j+1],temp);
				y=1;
			}
			if(!y)				//if the swap didnt happen, decrement the ptrs
			{
				if(s1)
					--A[j];
				if(s2)
					--A[j+1];
			}
		}	
	}
}

void ls(const char *dir)
{
	struct dirent *d;
	DIR *dh=opendir(dir);
	char **dirs=(char**)calloc(200, sizeof(char*));
	int n=0;
	if(!dh)
	{
		switch(errno)
		{
			case EACCES:  	printf("ls: cannot open directory '%s': Permission denied\n",dir); 
				      	break;
		    	case ENOENT:  	printf("ls: cannot access '%s': No such file or directory\n",dir); 
		    		      	break;
		    	/*case ENOTDIR: //printf("'%s' is not a directory\n", dir);
		    			dirs[n]=(char*)calloc(30, sizeof(char));
					strcpy(dirs[n++],dir);
					file=1;
					goto here;	//if the passed arg is not a dir, its prolly a file, so directly jump to stats
		    		      	break;*/
		}
		closedir(dh);
		return;             // return -1 if error
	}
	
	while(d=readdir(dh))
	{
		if(strcmp(d->d_name,".")==0||strcmp(d->d_name,"..")==0)   // only for ls -a . , ..
                	continue;
		dirs[n]=(char*)calloc(30, sizeof(char));
		strcpy(dirs[n++],d->d_name);
	}
	closedir(dh);
	if(n==0)
		return;
	sort(dirs,n);
	here:
	for(int i=0; i<n; i++)
		printf("%s\n",dirs[i]);
		
	/*if(file)
		return 1;
	else
	{
		printf("\n");
		return 0;
	}*/
}
int main(int argc,char *arg[])
{
	if(argc==1)            //curr dir
		ls(".");
	
	else if(argc==2)	//only 1 arg
	{
		int C[2];		//Check array
		check(C,2,++arg);
		if(C[0]==0||C[0]==1)
			ls(*(arg));
		else
			printf("%s\n",*arg);
	}
	
	else
	{
		char **dirs=(char**)calloc(200, sizeof(char*));	//creating a copy of argv, sort(argv) didnt work
		for(int i=0;i<argc;i++)
		{
			dirs[i]=(char*)calloc(30, sizeof(char));
			strcpy(dirs[i],arg[i]);
		}
		sort(++dirs,--argc);	//skipping 1st arg as it is filename(or ./a.out), so argc-1
		int C[argc+1];		//Check array
		check(C,argc+1,dirs);
		int i=0,k=0;
		while(i<argc) 
		{
			if(C[i]==0)	//to print error files 1st
			{
				ls(dirs[i]);
		     		//printf("\n");
			}
			i++;
		}
		i=0;
		while(i<argc) 
		{
			if(C[i]==2)	//to print files 2nd
			{
		    		printf("%s\n",dirs[i]);
		     		k=1;
			}
			i++;
		}
		i=0;
		while(i<argc)
		{
			if(C[i]==1)	//to print dirs at last
			{
				if(k--==1)
					printf("\n");
		     		printf("%s:\n",dirs[i]);
		     		ls(dirs[i]);
		     		//printf("%s",((argc-i-2)?"\n":""));	//no new line at the last
		     		printf("%s",i==C[argc]?"":"\n");
		     	}
		     	i++;
		 }
         }
	return 0;	
}
