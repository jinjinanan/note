#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *left;
    struct node *ringht;
} Node; //struct node 起别名

// 先续遍历
void preOrder(Node* node){
    if(node != NULL){
        printf("%d\n",node->data); // node 是指针
        preOrder(node ->left);
        preOrder(node -> ringht);
    }
}

// 中序遍历
void inOrder(Node *node){
    if(node != NULL){
        inOrder(node ->left);
        printf("%d\n",node->data); // node 是指针
        inOrder(node -> ringht);
    }
}

// 后续遍历
void postOrder(Node *node){
    if(node != NULL){
        postOrder(node ->left);
        postOrder(node -> ringht);
        printf("%d\n",node->data); // node 是指针
    }
}

int main(int argc, char const *argv[])
{
    Node n1;
    Node n2;
    Node n3;
    Node n4;

    n1.data = 5; // 实体变量
    n2.data = 6;
    n3.data = 7;
    n4.data = 8;

    n1.left = &n2; // 取指针
    n1.ringht = &n3;
    n2.left = &n4;
    n2.ringht = NULL;
    n3.left = NULL;
    n3.ringht = NULL;
    n4.left = NULL;
    n4.ringht = NULL;

    postOrder(&n1);
    return 0;
}
