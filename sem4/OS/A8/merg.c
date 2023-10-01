#include<stdio.h>
#include<stdlib.h>

struct node {
    int data;
    struct node* next;
};
struct node* Clone(struct node* list) {
    if (list == NULL) return NULL;

    struct node* result = (struct node*)malloc(sizeof(struct node));
    result->data = list->data;
    result->next = Clone(list->next);
    return result;
}
struct node* merge(struct node* h1, struct node* h2)
{
    if (!h1)
        return h2;
    if (!h2)
        return h1;
 
    // start with the linked list
    // whose head data is the least
    if (h1->data < h2->data) {
        h1->next = merge(h1->next, h2);
        return h1;
    }
    else {
        h2->next = merge(h1, h2->next);
        return h2;
    }
}
struct node* newNode(int key)
{
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = key;
    temp->next = NULL;
    return temp;
}
 
// A utility function to print linked list
void printList(struct node* Node)
{
    while (Node != NULL) {
        printf("%d  ", Node->data);
        Node = Node->next;
    }
}

int main()
{
    struct node* head1 = newNode(1);
    head1->next = newNode(3);
    head1->next->next = newNode(5);
 
    // 1->3->5 LinkedList created
 
    struct node* head2 = newNode(0);
    head2->next = newNode(2);
    head2->next->next = newNode(4);
 
    // 0->2->4 LinkedList created
 
    struct node* mergedhead=Clone(head2);
    mergedhead=merge(mergedhead,head1);
    printList(mergedhead);
    return 0;
}
