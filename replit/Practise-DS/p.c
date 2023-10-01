#include<stdio.h>
#include "PARANTHESES.h"

int isBalParan(char *exp){
	int i=0;
	while(exp[i]){
		if(exp[i]=='(')
		{
      push(S, exp[i]);
      disp(S);
    }
		else if(exp[i]==')')
    {
			if(isEmpty(S))
				return 0;
			else
			{
        pop(S);
        disp(S);
      }	
    }	
		i++;
	}	
	if(!isEmpty(S))
		return 0;
	return 1;
}

void main(){
	char exp[MAX];
  S=createstack();
	printf("Enter expression with parantheses:");
	scanf("%s", exp);
	if(isBalParan(exp))
		printf("Balanced parantheses.");
	else
		printf("Unbalanced parantheses.");
}