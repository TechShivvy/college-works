#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <sys/queue.h>
struct treeADT
{
    int data;
    struct treeADT *left;
    struct treeADT *right;
};

struct treeADT *insert(struct treeADT *root, int value)
{
    struct treeADT *ptr = root;
    if (ptr == NULL)
    {
        struct treeADT *node = (struct treeADT *)malloc(sizeof(struct treeADT));
        node->data = value;
        node->left = NULL;
        node->right = NULL;
        ptr = node;
    }
    else if (ptr->data > value)
    {
        ptr->left = insert(ptr->left, value);
    }
    else if (ptr->data < value)
    {
        ptr->right = insert(ptr->right, value);
    }
    return ptr;
}
struct treeADT *findMin(struct treeADT *root)
{
    struct treeADT *min = root;
    if (min->left != NULL)
    {
        min = findMin(min->left);
    }
    return min;
}
struct treeADT *findMax(struct treeADT *root)
{
    struct treeADT *max = root;
    if (max->right != NULL)
    {
        max = findMax(max->right);
    }
    return max;
}
void inOrder(struct treeADT *root)
{
    struct treeADT *ptr = root;
    if (ptr != NULL)
    {
        inOrder(ptr->left);
        printf("%d ", ptr->data);
        inOrder(ptr->right);
    }
}

void postOrder(struct treeADT* root)
{
    struct treeADT* ptr = root;
    if(ptr!=NULL)
    {
        postOrder(ptr->left);
        postOrderr(ptr->right);
        printf("%d\t",ptr->data);
    }
}

void preOrder(struct treeADT *root)
{
    struct treeADT* ptr = root;
    if(ptr!=NULL)
    {
        printf("%d ", ptr->data);
        preOrder(ptr->left);
        preOrder(ptr->right);
    }
}

struct treeADT *delete (struct treeADT *root, int value)
{
    struct treeADT *temp;
    struct treeADT *ptr = root;
    if (value > ptr->data)
    {
        ptr->right = delete (ptr->right, value);
    }
    else if (value < ptr->data)
    {
        ptr->left = delete (ptr->left, value);
    }
    else
    {

        if (ptr->right != NULL)
        {
            temp = findMin(ptr->right);
            ptr->data = temp->data;
            ptr->right = delete (ptr->right, temp->data);
        }
        else if (ptr->left != NULL)
        {
            temp = findMax(ptr->left);
            ptr->data = temp->data;
            ptr->left = delete (ptr->left, temp->data);
        }
        else
        {
            ptr = NULL;
        }
    }
    return ptr;
}
struct treeADT *find(struct treeADT *root, int x)
{
    struct treeADT *ptr = root;
    if (ptr == NULL)
    {
        printf("\n!!NOT FOUND!! \n");
    }
    else if (ptr->data < x)
    {
        ptr = find(ptr->right, x);
    }
    else if (ptr->data > x)
    {
        ptr = find(ptr->left, x);
    }
    else // for x == ptr->data value
    {
        printf("\n--->>FOUND : %d\n", ptr->data);
    }
    return ptr;
}
/**
 *           24
 *          /  \
 *        16    40
 *       /  \     \
 *      2    17    90
 *
 * */
// struct Queue *q;
// void levelOrder(struct treeADT* root)
// {
//     if(root!=NULL)
//     {
//         printf("%d ",root->data);
//         if(root->left!=NULL){push(q,root->left);}
//         if(root->right!= NULL){push(q,root->right);}
//         if(!isempty(q))
//         {
//             pop(q);
//         }
//         levelOrder(top(q));
//     }
// }
int isComplete(struct treeADT *root)
{
    struct treeADT *ptr = root;
    if (ptr->left != NULL && ptr->right != NULL)
    {
        if (isComplete(ptr->left) == 1 && isComplete(ptr->right) == 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (ptr->left == NULL && ptr->right == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int treeCmpr(struct treeADT *root1, struct treeADT *root2)
{
    struct treeADT *ptr1 = root1;
    struct treeADT *ptr2 = root2;
    if (ptr1 == NULL && ptr2 == NULL)
    {
        return 1;
    }
    else if (ptr1 != NULL && ptr2 != NULL && ptr1->data == ptr2->data)
    {
        if (treeCmpr(ptr1->left, ptr2->left) == 1 && treeCmpr(ptr1->right, ptr2->right) == 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

int countNodes(struct treeADT *root, int min, int max)
{
    int ans = 0;
    if (root->data >= min && root->data < max)
        ans = 1;
    if (root->left && root->data >= min)
        ans += countNodes(root->left, min, max);
    if (root->right && root->data < max)
        ans += countNodes(root->right, min, max);
    return ans;
}

int main()
{
    printf("\n------------------------TEST CASE FOR TREE ADT--------------------\n");
    struct treeADT *root = NULL;
    root = insert(root, 29);
    root = insert(root, 23);
    root = insert(root, 4);
    root = insert(root, 13);
    root = insert(root, 39);
    root = insert(root, 31);
    root = insert(root, 45);
    root = insert(root, 56);
    root = insert(root, 49);

    printf("\n--->>PREORDER EXPRESSION :\n");
    preOrder(root);
    printf("\n--->>INORDER EXPRESSION :\n");
    inOrder(root);
    printf("\n--->>POSTORDER EXPRESSION :\n");
    postOrder(root);
    // printf("\n--->>LEVEL ORDER  :\n");
    // levelOrder(root);
    struct treeADT *min = findMin(root);
    printf("\n--->>MIN VALUE = %d\n", min->data);
    struct treeADT *max = findMax(root);
    printf("\n--->>MAX VALUE = %d\n", max->data);
    inOrder(root);
    printf("\n--->>UPDATED TREE AFTER DELETION:");
    // delete (root, 4);
    inOrder(root);
    // find function
    struct treeADT *ptr = find(root, 56);

    // application
    printf("\n------------------------APPLICATION--------------------\n");
    struct treeADT *tree1 = NULL;
    struct treeADT *tree2 = NULL;
    while (1)
    {
        printf("\n-------------------MENU-------------------- :\n=> 1.INSERT VALUES OF TREES\n=> 2.CHECK FOR SAME TREE\n=> 3.CHECK FOR COMPLETE BST\n=> 4.COUNT THE NUMBER OF NODES IN TREE WITHIN THE GIVEN RANGE\n=> 0.EXIT\n\n");
        int choice;
        printf("\n--->>CHOICE : ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            int input;
            char ch = ' ';
            printf("\n-----------INSERT FOR TREE1---------------\n");

            while (ch != '\n')
            {
                scanf("%d", &input);
                scanf("%c", &ch);
                if (tree1 == NULL)
                {
                    tree1 = insert(tree1, input);
                }
                else
                {
                    insert(tree1, input);
                }
            }
            inOrder(tree1);
            ch = ' ';
            printf("\n-----------INSERT FOR TREE2---------------\n");
            while (ch != '\n')
            {
                scanf("%d", &input);
                scanf("%c", &ch);
                if (tree2 == NULL)
                {
                    tree2 = insert(tree2, input);
                }
                else
                {
                    insert(tree2, input);
                }
            }
            inOrder(tree2);
        }
        else if (choice == 2)
        {
            // same tree
            if (treeCmpr(tree1, tree2) == 1)
            {
                printf("\n--->>>SAME TREE\n");
            }
            else
            {
                printf("\n--->>>NOT SAME TREE\n");
            }
        }
        else if (choice == 3)
        {
            // complete tree
            if (isComplete(tree1) == 1)
            {
                printf("\n--->>>TREE1 IS COMPLETE\n");
            }
            else
            {
                printf("\n--->>>TREE1 IS NOT COMPLETE\n");
            }
            if (isComplete(tree2) == 1)
            {
                printf("\n--->>>TREE2 IS COMPLETE\n");
            }
            else
            {
                printf("\n--->>>TREE2 IS NOT COMPLETE\n");
            }
        }
        else if (choice == 4)
        {
            // count the nuber of nodes in the tree
            int min, max;
            printf("\n-->>Enter the start value :");
            scanf("%d", &min);
            printf("\n-->>Enter the end value   :");
            scanf("%d", &max);
            printf("\nTREE1 => NUMBER OF NODES IN RANGE [%d , %d] ARE :%d\n", min, max, countNodes(tree1, min, max));
            printf("\nTREE2 => NUMBER OF NODES IN RANGE [%d , %d] ARE :%d\n", min, max, countNodes(tree2, min, max));
        }
        else if (choice == 0)
        {
            exit(0);
        }
        else
        {
            printf("\n!!!WRONG CHOICE!!!\n");
        }
    }
    return 0;

}