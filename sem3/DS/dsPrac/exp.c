#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct exp
{
	struct exp *left,*right;
	char c;
};
struct stack
{
	struct exp *s[30];
	int top,size;
};
void init(struct stack *s,int max)
{
	s->top=-1;
	s->size=max;
}
int isFull(struct stack *s)
{
	return s->top==s->size-1;
}
int isEmpty(struct stack *s)
{
	return s->top==-1;
}
void push(struct stack *s,struct exp *E)
{
	if(isFull(s))
		return;
	s->s[++s->top]=E;
}
struct exp * pop(struct stack *s)
{
	if(isEmpty(s))
		return NULL;
	return s->s[s->top--];
}
struct exp* construct(char s[])
{
	struct stack *S=(struct stack *)malloc(sizeof(struct stack));
	init(S,10);
	struct exp *temp=(struct exp *)malloc(sizeof(struct exp));
	temp->left=NULL;
	temp->right=NULL;
	for(int i=0;i<strlen(s);i++)
	{
		temp->c=s[i];
		temp->left=NULL;
		temp->right=NULL;
		if(s[i]=='+'||s[i]=='-'||s[i]=='/'||s[i]=='*')
		{
			temp->left=(struct exp *)malloc(sizeof(struct exp));
	temp->right=(struct exp *)malloc(sizeof(struct exp));
			temp->right=pop(S);
			temp->left=pop(S);
		}
		push(S,temp);
	}
	return pop(S);
}
int eval(struct exp *T)
{
	while(T!=NULL)
	{
		if(T->c=='+')
			return (eval(T->left))+(eval(T->right));
		if(T->c=='*')
			return (eval(T->left))*(eval(T->right));
		if(T->c=='-')
			return (eval(T->left))-(eval(T->right));
		if(T->c=='/')
			return (eval(T->left))/(eval(T->right));
		return T->c-48;
	}
}
void inorder(struct exp *e)
{
	if(e)
	{
		inorder(e->left);
		printf("%c",e->c);
		inorder(e->right);
	}	
}
int main()
{
	struct exp *T=(struct exp *)malloc(sizeof(struct exp));	
	T=construct("45+6*");
	
	//int val=eval(T);
	//printf("%d",val);
	inorder(T);
	return 0;
}
