#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <time.h>
#include<fcntl.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include<string.h>
#include<dirent.h>
#include<ctype.h>

int strcmpi(char const *a, char const *b) //case insensitive comparision
{
    for (;; a++, b++) 
    {
        int d = tolower((unsigned char)*a) - tolower((unsigned char)*b);
        if (d != 0 || !*a)
            return d;
    }
}

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
			if(strcmpi(A[j],A[j+1])>0)
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

int cp(int argc,char *arg[],int i)
{
	//checking no of args
	if(argc!=3)
	{
		printf("Invalid no of args!\n");
		return -1;	
	}
	
	//checking src file	
	int fds=open(arg[1],O_RDONLY);
	if(fds==-1)
	{
		printf("Source File doesnt exist!\n");
		close(fds);
		return -1;	
	}
	int fdd;
	//checking dest file
	if(i) // cp -i 
	{
		fdd=open(arg[2],O_WRONLY);
		if(fdd!=-1) //if the file exists 
		{
			char ch;
			printf("Overwrite %s file?(y/n) ",arg[2]);
			scanf(" %c",&ch);
			if(!(ch=='y'||ch=='Y')) //other than y/Y
			{
				close(fdd);
				return -1;
			}
		}
		close(fdd);
	}
	fdd=creat(arg[2],0600); //even if the file exists or doesnt	
	//reading src and writing into dest
	char buf[500];	
	int nr,nw=0;
	while((nr=read(fds,buf,500))!=0)
        	nw+=write(fdd,buf,nr);
        	
        if(nw!=-1)
		printf("COPIED!\n");
	else
		printf("Error while copying\n");
		
	close(fds);
	close(fdd);
	return 0;
}

int grep(int argc,char *arg[],char c)
{
	//checking no of args
	if(argc!=3)
	{
		printf("Invalid no of args!\n");
		return -1;	
	}
	
	//checking src file
	int fd=open(arg[2],O_RDONLY);
	if(fd==-1)
	{
		printf("Source File doesnt exist!\n");
		close(fd);
		return -1;	
	}
	
	char line[100],buf[1024];	
	int l=0,i=0,nr,count=0;
	nr=read(fd,buf,1024);
	close(fd);
	
	while(l<nr)
	{	
		for(i=0;buf[l]!='\n'&&l<nr;i++,l++)
		{
			line[i]=buf[l]; 		// extracting lines
		}
		line[i]='\0';
		l++;
		if(c=='v' && (!strstr(line,arg[1])))  // -v
			printf("%s\n",line);
		else if(c!='v' && strstr(line,arg[1]))
		{
			if(c==' ')                    //  basic grep
				printf("%s\n",line);
			else if(c=='c')
				count++;
			else 			       //  -n
				printf("%d:%s\n",++count,line);
		}
	}
	if(c=='c')
		printf("%d\n",count);		
	return 0;
}

void ls(const char *dir,char c)
{
	struct dirent *d;
	DIR *dh=opendir(dir);
	if(!dh)
	{
		//printf("Dir Error!\n");
		closedir(dh);
		return;
	}
	char **dirs=(char**)calloc(200, sizeof(char*));
	int n=0;
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
	sort(dirs,n);
	if(c!='l')
	{
		//display array
		for(int i=0;i<n;i++)
			printf("%s \n",dirs[i]);
	}
	else    //ls -l
	{
		struct stat sb;
	
		int total=0;
		for(int i=0; i<n; i++)
		{
			if(lstat(dirs[i],&sb)==-1)
			{
				printf("ERRRORRR\n");
				exit(0);
			}
			total+=sb.st_blocks;
		}
		printf("total %d\n",total/2);
		
		for(int i=0; i<n; i++)
		{
			if(lstat(dirs[i],&sb)==-1)
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
}

void lsR(const char *dir,int k)
{
	struct dirent *d;
	DIR *dh=opendir(dir);
	if(!dh)
	{
		closedir(dh);
		return;
	}
	while(d=readdir(dh))
	{	
		if (d->d_type == DT_DIR) 
		{
			if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0)
				continue;
			!k?printf("\n."):printf("\n./%s",dir);
			printf("/%s:\n",d->d_name);
			ls(d->d_name,' ');
			lsR(d->d_name,k+1);
		}	
	}
	closedir(dh);
}

int main(int argc,char *arg[])
{
	int ch;
	//do
	//{
		printf("\n---------------------\nMenu:\n1.cp\n2.cp -i\n3.grep\n4.grep -c\n5.grep -v\n6.grep -n\n7.ls\n8.ls -a\n9.ls- l\n10.ls -R\n11.Exit\nChoice: ");
		scanf("%d",&ch);
		printf("\n");
		switch(ch)
		{
			case 1:cp(argc,arg,0);
				break;
			case 2:cp(argc,arg,1);
				break;
			case 3:grep(argc,arg,' ');
				break;
			case 4:grep(argc,arg,'c');
				break;
			case 5:grep(argc,arg,'v');
				break;
			case 6:grep(argc,arg,'n');
				break;
			case 7:ls(".",' ');
				break;
			case 8:ls(".",'a');
				break;
			case 9:ls(".",'l');  
				break;
			case 10:printf(".:\n");
				ls(".",' ');
				lsR(".",0);
				break;
			case 11:printf("\nExiting...\n");
				break;
			default:printf("\nInvalid choice!\n");					
		}
	//}while(ch!=11);
	return 0;
}
