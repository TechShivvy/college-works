#include<stdio.h>
#include<stdlib.h>

typedef struct heap{
    char emp[101];
    int sal[101];
    int cur,sz;
}heap;

void init(heap *h,int size){
    h->sal[0]=-1;
    h->emp[0] = '#';
    h->cur = 0;
    h->sz = size;
}

void insert(heap *h,char y,int x){
    h->sal[++(h->cur)] = x;
    h->emp[h->cur] = y;
    int i=h->cur;
    while(i>0 && h->sal[i/2]>h->sal[i]){
        int tmp;
        tmp = h->sal[i/2];
        h->sal[i/2] = h->sal[i];
        h->sal[i] = tmp;
        char temp;
        temp = h->emp[i/2];
        h->emp[i/2] = h->emp[i];
        h->emp[i] = temp;
        i/=2;
    }
}

void delete(heap *h){
    int ans = h->sal[1];
    char answer = h->emp[1];
    int last = h->sal[h->cur];
    char lt = h->emp[h->cur];
    h->cur--;
    //h->sal[1] = last;
    int ch,p;
    for(p=1;2*p<=h->cur;p=ch){
        ch = 2*p;
        if(ch!=h->cur && h->sal[ch]>h->sal[ch+1]){
            ch++;
        }
        if(last>h->sal[ch]){
            h->sal[p] = h->sal[ch];
            h->emp[p] = h->emp[ch];
        }else break;
    }
    h->sal[p] = last;
    h->emp[p] = lt;
    printf("(%c,%d)",answer,ans);
}

void display(heap *h){
    for(int i=1;i<=h->cur;i++){
        printf("(%c,%d)\n",h->emp[i],h->sal[i]);
    }
}

void disdelorder(heap *h){
    while(h->cur!=0){
        delete(h);
        printf("\n");
    }
}

int main(){
    heap *h = (heap *)malloc(sizeof(heap));
    init(h,100);
    printf("Employee Insertion Order:\n");
    insert(h,'A',15000);
    insert(h,'K',12000);
    insert(h,'R',4000);
    insert(h,'T',3500);
    insert(h,'L',4600);
    insert(h,'P',6000);
    insert(h,'Y',8600);
    display(h);
    printf("\nEmployees are removed in the order:\n");
    disdelorder(h);
    printf("\n");
    display(h);
    return 0;
}
