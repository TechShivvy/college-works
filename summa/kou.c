#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<conio.h>

struct node{
    char N[25];
    int df;
    struct node *pc;
    struct node *ps;
};

struct node *A[20];
int in=0,c=0;

void create(struct node *p,int N){
    int i;
    struct node *temp,*t;
    temp=p;
    for(i=0;i<N;i++){
        t=malloc(sizeof(struct node));
        printf("enter name:");
        scanf("%s",t->N);
        printf("enter dir(1) or file(0):");
        scanf("%d",&t->df);

        if(t->df==1){
            A[c]=t;
            c++;
        }

        t->pc=NULL;
        t->ps=NULL;

        if(i==0){
            temp->pc=t;
            temp=t;
        }
        else{
            temp->ps=t;
            temp=t;
        }
        
    }
}

void display(struct node *p,char *dir){
    int i;
    char path[100];
    p=p->pc;
    do{
    	strcpy(path,dir);
	strcat(path,"/");
	strcat(path,p->N);
        //printf("\n%s(%d)",path,p->df);
        printf(" %-10s\t\t%-4c\t\t%-4s\n",p->N,(p->df?'d':'f'),path);
        if(p->df==1 && p->pc!=NULL){
        display(p,path);
        }
        p=p->ps;
    }while(p!=NULL);
}

int main(){
    int nu,nc;
    int i,j,k;
    struct node *hier;

    hier=malloc(sizeof(struct node));
    hier->df=1;
    hier->pc=NULL;
    hier->ps=NULL;

    printf("enter number of users:");
    scanf("%d",&nu);
    create(hier,nu);

    for(in=0;in<c;in++){
        printf("enter number of child nodes %s:",A[in]->N);
        scanf("%d",&nc);
        create(A[in],nc);
    }
    printf("\nhierarchial structure\n");
    printf("\n -----CONTENTS OF DIRECTORIES----- \n");
    printf("\n File Names\t\tType\t\tPath\n\n");
    char *buf;
    display(hier,buf);
    //getch();
}
