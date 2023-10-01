#include<stdlib.h>
#include<stdio.h>
struct bst{
  struct bst *left,*right;
  int data;
};

typedef struct bst *tree;

int isleaf(tree node){
  if(node->right==NULL&&node->left==NULL){
    return 1;
  }
  return 0;
}

void insert(tree root,int key){
  tree temp=root;
  tree node=(tree)malloc(sizeof(tree));
  node->left=NULL;
  node->right=NULL;
  node->data=key;
  do{
    if(temp->data>key){
      if(temp->left==NULL){
        break;
      }
      temp->left=node;
    }
    else{
      if(temp->right==NULL){
        break;
      }
      temp->right=node;
    }
  }while(!isleaf(temp));
  if(temp->data>key){
    temp->left=node;
  }
  else{
    temp->right=node;
  }
}

tree inject(tree root,int key){
  if(root==NULL)
	{
		tree root=(tree)malloc(sizeof(tree));
		root->data=key;
		root->left=NULL;
		root->right=NULL;
	}
	else
	{
		if(root->data>key)
			root->left=inject(root->left,key);
		if(root->data<key)
			root->right=inject(root->right,key);
	}
	return root;
}

int search(tree root,int key){
  tree temp=(tree)malloc(sizeof(tree));
  temp=root;
  if(temp->data==key){
    return 1;
  }
  else if(isleaf(temp)){
    return 0;
  }
  else if(temp->data>key){
    search(temp->left,key);
  }
  else if(temp->data<key){
    search(temp->right,key);
  }
}

tree inorderpredecessor(tree root){
  tree temp=root->left;
  while(temp->right!=NULL){
    temp=temp->right;
  }
  return temp;
  temp=root;
  inorderpredecessor(temp->right);
}

int findmin(tree root){
  tree temp=root;
  if(root!=NULL){
    if(root->left!=NULL){
      findmin(root->left);
    }
    return temp->data;
  }
}

int findmax(tree root){
  tree temp=root;
  if(root!=NULL){
    if(temp->right!=NULL){
      findmax(temp->right);
    }
    return temp->data;
  }
}

tree delnode(tree root,int key){
  if(root==NULL){
    return root;
  }
  else{
    if(root->data>key){
      root->left=delnode(root->left,key);
    }
    else if(root->data<key){
      root->right=delnode(root->right,key);
    }
    else{
      if(root->right==NULL){
        tree temp=root->left;
        free(root);
        return temp;
      }
      else if(root->left==NULL){
        tree temp=root->right;
        free(root);
        return temp;
      }
      else{
        int min=findmin(root->right);
        root->data=min;
        root->right=delnode(root->right,min);
        return root;
      }
    }
  }
}

void inorder(tree root){
  if(root){
    inorder(root->left);
    printf("%d ",root->data);
    inorder(root->right);
  }
}

void preorder(tree root){
  if(root){
    printf("%d ",root->data);
    preorder(root->right);
    preorder(root->left);
  }
}

void postorder(tree root){
  if(root){
    postorder(root->left);
    postorder(root->right);
    printf("%d ",root->data);
  }
}

int nodes(tree root){
  int count=0;
  if(root){
    count+=nodes(root->left);
    count++;
    count+=nodes(root->right);
  }
  return count;
}

int leaves(tree root){
  int count=0;
  if(root){
    count+=leaves(root->left);
    if(isleaf(root)){
      count++;
    }
    count+=leaves(root->right);
  }
  return count;
}

int nonleaf(tree root){
  return(nodes(root)-leaves(root));
}

//void display()


int main(){
  tree maram=(tree)malloc(sizeof(tree));
  
  inject(maram,8);
  inject(maram,9);
  inject(maram,7);
  inject(maram,11);
  inject(maram,10);
  inorder(maram);
  preorder(maram);
  postorder(maram);
  delnode(maram,7);
  inorder(maram);
  delnode(maram,10);
  inorder(maram);
  delnode(maram,6);
  inorder(maram);
  inject(maram,11);
  inject(maram,1);
  inorder(maram);
  int m=leaves(maram);
  printf("leaves=%d",m);
  m=nodes(maram);
  printf("nodes=%d",m);
  m=nonleaf(maram);
  printf("nonleaf=%d",m);
}
