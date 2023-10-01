#include<stdio.h>
#include<stdlib.h>
//#include<unistd.h>
#include<time.h>
//#include<fcntl.h>
#include<sys/stat.h>
#include<pwd.h>
#include<grp.h>
#include<string.h>
#include<dirent.h>
//#include<ctype.h>
#include<errno.h>

void printsrc(char A[],int n) //to print the source file name of a symbolic link from the abs path of the src file
{
	if(A[n]=='/')
		return;
	printsrc(A,n-1);
	printf("%c",A[n]);	//this fxn bascially prints a string in rev
}

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

int ls(const char *dir)
{
	struct dirent *d;
	DIR *dh=opendir(dir);
	char **dirs=(char**)calloc(200, sizeof(char*));
	int n=0,file=0;
	if(!dh)
	{
		switch(errno)
		{
			case EACCES:  	printf("ls: cannot open directory '%s': Permission denied",dir); 
				      	break;
		    	case ENOENT:  	printf("ls: cannot access '%s': No such file or directory",dir); 
		    		      	break;
		    	case ENOTDIR: //printf("'%s' is not a directory\n", dir);
		    			dirs[n]=(char*)calloc(30, sizeof(char));
					strcpy(dirs[n++],dir);
					file=1;
					goto here;	//if the passed arg is not a dir, its prolly a file, so directly jump to stats
		    		      	break;
		}
		closedir(dh);
		return -1;             // return -1 if error
	}
	
	while(d=readdir(dh))
	{
		if(strcmp(d->d_name,".")==0||strcmp(d->d_name,"..")==0)   // only for ls -a . , ..
                	continue;
		dirs[n]=(char*)calloc(30, sizeof(char));
		strcpy(dirs[n++],d->d_name);
	}
	closedir(dh);
	sort(dirs,n);			//sort the files in the dir
	
	here:;
	;
	struct stat sb;
	int total=0;
	char path[100];
	if(!file){
	for(int i=0; i<n; i++)
	{	
		if(!file)			//to form relative path for the files in dir
		{strcpy(path,dir);		
		strcat(path,"/");
		strcat(path,dirs[i]);}
		else
			strcpy(path,dirs[i]); 
		if(lstat(path,&sb)==-1)
		{
			printf("ERRRORRR\n");
			exit(0);
		}
		total+=sb.st_blocks;
	}
	printf("total %d\n",total/2);}
	for(int i=0; i<n; i++)
	{
		if(!file)
		{strcpy(path,dir);
		strcat(path,"/");
		strcat(path,dirs[i]);}
		else
			strcpy(path,dirs[i]);	
		if(lstat(path,&sb)==-1)
		{
			printf("ERRRORRR\n");
			
			exit(0);
		}
		printf( (S_ISDIR(sb.st_mode)) ? "d" : ((S_ISLNK(sb.st_mode)) ? "l" : "-"));        // d,l,-
		printf( (sb.st_mode & S_IRUSR) ? "r" : "-");					      // rwx user	
		printf( (sb.st_mode & S_IWUSR) ? "w" : "-");
		printf( (sb.st_mode & S_IXUSR) ? "x" : "-");
		printf( (sb.st_mode & S_IRGRP) ? "r" : "-");                                       // rwx groups
		printf( (sb.st_mode & S_IWGRP) ? "w" : "-");
		printf( (sb.st_mode & S_IXGRP) ? "x" : "-");
		printf( (sb.st_mode & S_IROTH) ? "r" : "-");                                       // rwx others
		printf( (sb.st_mode & S_IWOTH) ? "w" : "-");
		printf( (sb.st_mode & S_IXOTH) ? "x" : "-");
		printf(" %ld",(long)sb.st_nlink);                                                  // no of links
		struct passwd *pws;
		struct group *grp;
		pws = getpwuid(sb.st_uid);                                                         // uid
		grp = getgrgid(sb.st_uid);                                                         // gid 
		printf(" %s %s ",pws->pw_name,grp->gr_name);                                       // uname gname
		printf("%5lld",(long long) sb.st_size);                                            // file size in bytes 
		char *day=ctime(&sb.st_mtime);
		printf(" %.12s", day+4);                                                           // modification time
		printf(" %s", dirs[i]);								      // file name	
		if(S_ISLNK(sb.st_mode))                                                            // to print source file of soft link
		{
			char buf[100];
			char *res=realpath(dirs[i],buf);
			printf(" -> ");                                                              
			printsrc(buf,strlen(buf));
		}
		if(file)
			return 1;
		printf("\n");
	}
	return 0;
}

int main(int argc,char *arg[])
{
	if(argc==1)            //curr dir
		ls(".");
	
	else if(argc==2)	//only 1 arg
	{
		int r=ls(*(++arg));
		if(r==1||r==-1) //if error or file 
			printf("\n");
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
		int i=0,k;
		while(i<argc) 
		{
			if(C[i]==0)	//to print error files 1st
			{
				ls(dirs[i]);
		     		printf("\n");
			}
			i++;
		}
		i=0;
		while(i<argc) 
		{
			if(C[i]==2)	//to print files 2nd
			{
		    		ls(dirs[i]);
		    		printf("\n");
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

