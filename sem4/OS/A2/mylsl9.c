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
#include <errno.h>
void printsrc(char A[],int n)
{
	if(A[n]=='/')
		return;
	printsrc(A,n-1);
	printf("%c",A[n]);
}
void check(int *A,int n,char **dirs)
{
	struct dirent *d;
	DIR *dh;//=opendir(dir);
	//char **dirs=(char**)calloc(200, sizeof(char*));
	//int n=0,file=0;
	for(int i=0;i<n;i++)
	{
	A[i]=1;
	DIR *dh=opendir(dirs[i]);
	if(!dh)
	{
		 if(!(errno==ENOTDIR))
			A[i]=0;
		else
			A[i]=2;
	}
	closedir(dh);
	}
}
void sort2(char** A, int n)
{
	int i,j;
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			char buf1[100];
			char *res=realpath(A[j],buf1);
			char buf2[100];
			res=realpath(A[j+1],buf2);
			if(strcasecmp(buf1,buf2)>0)
			{
				char* temp;
				temp=(char*)calloc(30, sizeof(char));
				strcpy(temp,A[j]);
				strcpy(A[j],A[j+1]);
				strcpy(A[j+1],temp);
			}
		}	
	}
}
/*void sort3(char** A, int n)
{
	int i,j;
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(_lstricoll(A[j],A[j+1])>0)
			{
				char* temp;
				temp=(char*)calloc(30, sizeof(char));
				strcpy(temp,A[j]);
				strcpy(A[j],A[j+1]);
				strcpy(A[j+1],temp);
			}
		}	
	}
}*/

void sort(char** A, int n)
{
	int i,j;
	int s1,s2,y;
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			s1=0,s2=0,y=0;
			if(A[j][0]=='/')
			{
				++A[j];
				s1=1;
			}
			if(A[j+1][0]=='/')
			{
				++A[j+1];
				s2=1;
			}
			if(strcasecmp(A[j],A[j+1])>0)
			{
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
			if(!y)
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
		//printf("Dir Error!\n");
		//closedir(dh);
		//printf("ls: cannot access '%s': No such file or directory\n",dir);
		//return;
		switch (errno)
		{
			case EACCES:  printf("ls: cannot access '%s': Permission denied",dir); 
				      break;
		    	case ENOENT:  printf("ls: cannot access '%s': No such file or directory",dir); 
		    		      break;
		    	case ENOTDIR: //printf("'%s' is not a directory\n", dir);
		    			dirs[n]=(char*)calloc(30, sizeof(char));
					strcpy(dirs[n++],dir);
					file=1;
					goto here;
		    		      	break;
		}
		closedir(dh);
		return -1;
	}
	
	while(d=readdir(dh))
	{
		if(strcmp(d->d_name,".")==0||strcmp(d->d_name,"..")==0)   // only for ls -a . , ..
                	continue;
		dirs[n]=(char*)calloc(30, sizeof(char));
		strcpy(dirs[n++],d->d_name);
	}
	closedir(dh);
	here:
	sort(dirs,n);
	//for(int i=0;i<n;i++)
	//	printf("%s \n",dirs[i]);
	struct stat sb;
	
	int total=0;
	char path[100];
	if(!file){
	for(int i=0; i<n; i++)
	{
		if(!file)
		{strcpy(path,dir);
		strcat(path,"/");
		strcat(path,dirs[i]);}
		else
			strcpy(path,dirs[i]);
		//printf("\npath:%s\n",path);
		if(lstat(path,&sb)==-1)
		{
			printf("ERRRORRR\n");
			/*int err = errno;
    			fprintf(stderr, '%s0, explain_errno_lstat(err, pathname, &buf));
    			exit(EXIT_FAILURE);*/
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
		/*if(!file)
			printf("\n");
		else if(i!=n-1)
		{
			printf("\n");
		}*/
		//else
		//	return 1;
		
	}
	return 0;
}
int main(int argc,char *arg[])
{
	if(argc==1)            //curr dir
		ls(".");
	
	else if(argc==2)
	{int r=ls(*(++arg));
	if(r==1||r==-1)
		printf("\n");
	}
	
	else{
	//for(int i=0;i<argc;i++)
	//	printf("%s \n",arg[i]);
	char **dirs=(char**)calloc(200, sizeof(char*));
	for(int i=0;i<argc;i++)
	{
		dirs[i]=(char*)calloc(30, sizeof(char));
		strcpy(dirs[i],arg[i]);
	}
	sort(++dirs,--argc);
	int C[argc];
	check(C,argc,dirs);
	//for(int i=0;i<argc;i++)
	//	printf("%d \n",C[i]);
	//arg--;
	int i=0,k;
	//printf("\n");
		while(i<argc) 
        	{
        		if(C[i]==0)
             		{//printf( "%s:\n", dirs[i] );
             		ls(dirs[i]);
             		printf("\n");
             		}
             		i++;
        	}
        	i=0;
        	while(i<argc) 
        	{
        		if(C[i]==2)
             		{//printf( "%s:\n", dirs[i] );
             		ls(dirs[i]);
             		printf("\n");
             		k=1;
             		}
             		i++;
        	}
        	//if(k)
        	//	printf("\n");
	//for(int i=0;i<argc;i++)
	//	printf("%s \n",dirs[i]);
	i=0;
        	while(i<argc)
        	{
        		if(C[i]==1)
             		{if(k--==1)
        			printf("\n");
             		printf( "%s:\n", dirs[i] );
             		ls(dirs[i]);
             		//if(!k)
             			//printf("\n");
             			printf("%s",((argc-i-2)?"\n":""));
             		//else
             		//	printf("\n");
             		}
             		i++;
         	}
         }
	return 0;	
}

