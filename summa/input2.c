#include<stdio.h>
 #include "input.h"

 void print_word()
 {
    char ch;
    char str[15];
    int i = 0,flag=0;

    printf ("\n Enter a word of your choice : ") ;

    for(i=0; i<15&&flag==0; ++i)
    {
    ch = getch();
    switch(ch)
    {
      case '\n':
         str[i] = '\0';
         flag=1;
         break;
     /* case '\b':
         if(i>0) i--;
         str[i--]='\0';
         printf("\b \b");
         break;*/
      default:
         str[i] = ch;
         printf("%c",ch);
    }
    }
    str[15]='\0';

    printf("\t") ;
    printf ("%s ", str) ;
    printf ("%s", str) ;

}

int main()
{
    print_word();
}
