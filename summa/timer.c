#include<stdio.h>
#include <unistd.h>

int main(){
int i;
printf("Continue in...");
fflush(stdout);
for (i = 10; i > 0 ; --i)
{
    printf("%d",i);
    fflush(stdout);
    sleep(1);
    printf("\b");
    if  (i == 10) printf("\b  \b");   // for 10 you need to erase 2 characters
}}
