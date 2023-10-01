#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<pwd.h>
#include<grp.h>
#include<string.h>
#include<dirent.h>
#include<ctype.h>
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

char ** ls(const char *dir,char c)
{
	struct dirent *d;
	DIR *dh=opendir(dir);
	char **dirs=(char**)calloc(200, sizeof(char*));
	int n=0,file=0;
	if(!dh)
	{
		switch(errno)
		{
			case EACCES:  	printf("ls: cannot open directory '%s': Permission denied\n",dir); 
				      	break;
		    	case ENOENT:  	printf("ls: cannot access '%s': No such file or directory\n",dir); 
		    		      	break;
		    	case ENOTDIR: //printf("'%s' is not a directory\n", dir);
		    			if(c=='l')
		    			{
		    				dirs[n]=(char*)calloc(30, sizeof(char));
						strcpy(dirs[n++],dir);
						file=1;
						goto here;	//if the passed arg is not a dir, its prolly a file, so directly jump to stats
					}
		    		      	break;
		}
		closedir(dh);
		return NULL;             // return -1 if error
	}
	
	while(d=readdir(dh))
	{
		if(c==' '||c=='l')
		{
			if(strcmp(d->d_name,".")==0||strcmp(d->d_name,"..")==0)   // only for ls -a . , ..
                		continue;
                }
		dirs[n]=(char*)calloc(30, sizeof(char));
		strcpy(dirs[n++],d->d_name);
	}
	closedir(dh);
	sort(dirs,n);			//sort the files in the dir
	if(n==0&&c!='l')
		return NULL;
	if(c!='l')
	{
		//display array
		for(int i=0;i<n;i++)
			printf("%s \n",dirs[i]);
		return dirs;
	}
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
		{
			printf("\n");
			return NULL;
		}
		printf("\n");
	}
}

void lsR(char *dir, char **fil)
{
	struct dirent *d;
	int i=0;
	char path[1000];
	while(fil[i])
	{
		struct stat sb;
		strcpy(path,dir);
		strcat(path,"/");
		strcat(path,fil[i]);
		if(lstat(path,&sb)==-1)
			;
		if(S_ISDIR(sb.st_mode))
		{	 
			printf("\n%s:\n",path);
			char **fil2=ls(path,' ');
			if(fil2)
				lsR(path,fil2);
		}
		i++;
	}
}

int main(int argc, char *arg[])
{
	char op=' ';
	if(argc==1)
	{
		ls(".",' ');
		return 0;
	}
	else
	{
		if(arg[1][0]=='-')
		{
			if(strcmp(arg[1],"-a")==0)
				op='a';
			else if(strcmp(arg[1],"-l")==0)
				op='l';
			else if(strcmp(arg[1],"-R")==0)
				op='R';
			else
			{
				printf("Invalid option!\n");
				return -1;
			}
			++arg;
			--argc;
		}
		
	}
	if(argc==1)
	{
		if(op=='R')
		{
			char **fil;
			printf(".:\n");
			fil=ls(".",' ');
			lsR(".",fil);
		}
		else
			ls(".",op);
	}
	else if(argc==2)
	{
		++arg;
		if(op=='l')
			ls(*arg,op);
		else
		{
			int C[2];		//Check array
			check(C,2,arg);
			if(C[0]==0||C[0]==1 && op!='R')
				ls(*(arg),op);
			else if(C[0]==1&&op=='R')
			{
				printf("%s:\n", *arg);
				char **fil=ls(*arg,' ');
				if(fil)
					lsR(*arg,fil);
			}
			else if(C[0]==2)
			{	if(op=='R')
					printf("%s:\n",*arg);
				else
					printf("%s\n",*arg);
			}
				
		}
	}
	else
	{
		char **dirs=(char**)calloc(200, sizeof(char*));	//creating a copy of argv, sort(argv) didnt work
		for(int i=0;i<argc;i++)
		{
			dirs[i]=(char*)calloc(30, sizeof(char));
			strcpy(dirs[i],arg[i]);
		}
		sort(++dirs,--argc);
		
		int C[argc+1];		//Check array
		check(C,argc+1,dirs);
		int i=0,k=0;
		
		while(i<argc) 
		{
			if(C[i]==0)	//to print error files 1st
			{
				if(op!='R')
					ls(dirs[i],op);
				else
					ls(dirs[i],' ');
			}
			i++;
		}
		i=0;
		while(i<argc) 
		{
			if(C[i]==2)	//to print files 2nd
			{
				if(op!='l')
		    			printf("%s\n",dirs[i]);
		    		else 
		    			ls(dirs[i],'l');
		     		k=1;
			}
			i++;
		}
		i=0;
		char **fil;
		while(i<argc)
		{
			if(C[i]==1)	//to print dirs at last
			{
				if(k--==1)
					printf("\n");
		     		printf("%s:\n",dirs[i]);
		     		if(op!='R')
		     			ls(dirs[i],op);
		     		else
		     			fil=ls(dirs[i],' ');
		     		if(op=='R' && fil)
		     			lsR(dirs[i],fil);
		     		//printf("%s",((argc-i-2)?"\n":""));	//no new line at the last
		     		printf("%s",i==C[argc]?"":"\n");
		     	}
		     	i++;
		 }
	}
	return 0;
}
