#include<stdio.h>
struct hash{
	int arr[1000];
	int size;
};
void init(struct hash* h,int n);
void insert(struct hash *h,int x);
void display(struct hash *h);
void find(struct hash *h,int x);

