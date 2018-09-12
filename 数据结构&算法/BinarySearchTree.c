#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* left;
    struct node* right;
}Node;

typedef struct{
    Node* root;
}Tree;

typedef Node* position;

// 查找
int find(Node* node,int value){
    if(!node){return -1;}
    if(value > node->data){
        return find(node -> right,value);
    }
    else if(value < node->data){
        return find(node -> left,value);
    }
    else{
        return node->data;
    }

}



position get_maxiPosition(Node* node){
    if(node == NULL){
        return NULL;
    }
    else{
        position m1 = get_maxiPosition(node->left);
        position m2 = get_maxiPosition(node->right);
        position m3 = node;
        position max = m1;
        if(m2->data > max->data){max = m2;}
        if(m3->data > max->data){max = m3;}
        return max;
    }
}

// 插入
void insert(Tree* tree,int value){
    Node* node = malloc(sizeof(Node));// 动态分配内存 malloc
    node -> data = value;
    node -> left = NULL;
    node -> right = NULL;

    if(tree -> root == NULL){
        tree -> root= node;
    }
    else{
        Node *temp = tree -> root; 
        while(temp != NULL){
            if(value < temp->data){
                if(temp -> left == NULL){
                    temp -> left = node;
                    return;
                }
                else{
                    temp = temp->left;
                }
            }
            else{
                if(temp->right  == NULL){
                    temp->right = node;
                    return;
                }
                else{
                    temp= temp->right;
                }
            }
        }
    }
}

// 删除
/*
删除考虑三种情况
*/
position delete(Node* node,int value){
    position temp;
    if(!node){return NULL;}
    else if(value > node->data){
        printf("1");
        delete(node->right,value);
    }
    else if(value < node->data){
        printf("2");
        delete(node->left,value);
    }
    else{
        printf("3");
        if(node->left && node->right){
            temp = get_maxiPosition(node->left);
            node->data = temp->data;
            node->left = delete(node->left,temp->data);
        }
        else{
            temp = node;
            if(!node->left){
                node = node->right;
            }
            else if(!node->right){
                node = node->left;
            }
            free(temp);
        }
    }
    return node;
}

// 求最大值
int get_maxinum(Node* node){
    if(node == NULL){
        return -1;
    }
    else{
        int m1 = get_maxinum(node->left);
        int m2 = get_maxinum(node->right);
        int m3 = node->data;
        int max = m1;
        if(m2 > max){max = m2;}
        if(m3 > max){max = m3;}
        return max;
    }
}

int get_minnum(Node *node){
    int min;
    return min;
}

// 求树的高度
int get_height(Node* node){
    if(node == NULL){
        return 0;
    }
    else{
        int left_h = get_height(node->left);
        int right_h = get_height(node->right);
        int max = left_h;
        if(right_h > max){
            max = right_h;
        }
        return max + 1;
    }
}

// 先续遍历
void preOrder(Node* node){
    if(node != NULL){
        printf("%d\n",node->data); // node 是指针
        preOrder(node ->left);
        preOrder(node -> right);
    }
}

// 中序遍历
void inOrder(Node *node){
    if(node != NULL){
        inOrder(node ->left);
        printf("%d\n",node->data); // node 是指针
        inOrder(node -> right);
    }
}

// 后续遍历
void postOrder(Node *node){
    if(node != NULL){
        postOrder(node ->left);
        postOrder(node -> right);
        printf("%d\n",node->data); // node 是指针
    }
}

int main(int argc, char const *argv[])
{
    int arr[7] = {6,3,8,2,5,1,7}; //正数
    Tree tree;
    tree.root = NULL;
    int i;
    for(i=0;i<7;i++){
        insert(&tree,arr[i]);
    }

    // preOrder(tree.root);
    // inOrder(tree.root);

    delete(tree.root,6);
    // preOrder(tree.root);
    // inOrder(tree.root);

    
    // int h = get_height(tree.root);
    // printf("height = %d \n",h);
    // int m = get_maxinum(tree.root);
    // printf("maxiNum = %d \n",m);


    // int result = find(tree.root,1);
    // printf("result = %d \n",result);


    return 0;
}
