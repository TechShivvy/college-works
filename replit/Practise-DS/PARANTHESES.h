#include<stdio.h>
#define MAX 20

struct Stack{
	char stack[MAX];
	int top;
}S;

struct Stack createstack(){
	S.top = -1;
  return S;
}

void disp(struct Stack s){
	int i;
	for(i=0;i<=S.top;i++)
		printf("%c ",S.stack[i]);
	printf("\n");
}

int getTop(struct Stack s){
	return S.top;
}
int isEmpty(struct Stack s){
	return S.top==-1;
}

int isFull(struct Stack s){
	return S.top==MAX-1;
}

void push(struct Stack s,char item){
	if (S.top == (MAX - 1))
		return;
	else{
		S.stack[++S.top] = item;
	}
}
char pop(struct Stack s){
	if (S.top == - 1){
		return -1;
	}
	else{
		return S.stack[S.top--]; 
	}
}