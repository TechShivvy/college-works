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

void sort(char** A, int n)
{
	int i,j;
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(strcasecmp(A[j],A[j+1])>0)
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
void ls(const char *dir)
{
	struct dirent *d;
	DIR *dh=opendir(dir);
	if(!dh)
	{
		//printf("Dir Error!\n");
		closedir(dh);
		printf("ls: cannot access '%s': No such file or directory\n",dir);
		return;
	}
	char **dirs=(char**)calloc(200, sizeof(char*));
	int n=0;
	while(d=readdir(dh))
	{
		if(strcmp(d->d_name,".")==0||strcmp(d->d_name,"..")==0)   // only for ls -a . , ..
                	continue;
		dirs[n]=(char*)calloc(30, sizeof(char));
		strcpy(dirs[n++],d->d_name);
	}
	closedir(dh);
	sort(dirs,n);
	for(int i=0;i<n;i++)
		printf("%s \n",dirs[i]);
	struct stat sb;
	
	int total=0;
	char path[100];
	for(int i=0; i<n; i++)
	{
		strcpy(path,dir);
		strcat(path,"/");
		strcat(path,dirs[i]);
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
	printf("total %d\n",total/2);
	for(int i=0; i<n; i++)
	{
		strcpy(path,dir);
		strcat(path,"/");
		strcat(path,dirs[i]);
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
		printf("\n");
	}
	
}
int main(int argc,char *arg[])
{
	if(argc==1)            //curr dir
	{
		printf(".:\n");
		ls(".");
	}
	else 
	{
        	while(--argc) 
        	{
             		printf( "%s:\n", * ++arg );
             		ls(*arg);
         	}
         }
	return 0;
	
}

