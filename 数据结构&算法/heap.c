#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct HeapStruct *MaxHeap;
struct HeapStruct{
    int *data;      //存储堆元素的数组
    int size;       //堆的当前元素个数
    int Capacity;   //堆的最大容量
};

// 最大堆的创建
MaxHeap Create(int MaxSize){
    MaxHeap H = malloc(sizeof(struct HeapStruct));
    H->data = malloc((MaxSize+1)*sizeof(int)); // 堆从下表1的地方开始存放   动态的申请数组
    H->size = 0;
    H->Capacity = MaxSize;
    H->data[0] = UINT_MAX;  //H->data 是 int 指针 。 可以忽略data的类型当作数组来用
    return H;
}

// 判断堆是否满了
int IsFull(MaxHeap H){
    if(H->size == H->Capacity){
        return 1;
    }
    return 0;
}

// 判断堆是否满了
int IsEmpty(MaxHeap H){
    if(H->size == 0){
        return 1;
    }
    return 0;
}

// 插入
void Insert(MaxHeap H, int item){
    int i;
    if(IsFull(H)){
        printf("最大堆已满");
        return;
    }
    i = ++H->size;
    for(;H->data[i/2]<item;i/=2){  //哨兵
        H->data[i] = H->data[i/2];
    }
    H->data[i] = item;
    
}

// 删除
int Delete(MaxHeap H,int item){
    int Parent,Child;
    int MaxItem,temp;
    if(IsEmpty(H)){
        printf("最大堆以为空");
        return -1;
    }
    MaxItem = H->data[1];
    temp = H->data[H->size--];
    for(Parent =1;Parent*2<=H->size;Parent=Child){//Parent*2<=H->size 有子节点
        Child = Parent *2;
        if((Child != H->size)&&(H->data[Child] < H->data[Child+1])){
            Child++;
        }
        if(temp >= H->data[Child]) {
            break;
        }
        else{
            H->data[Parent] = H->data[Child];
        }
    }
    H->data[Parent] = temp;
    return MaxItem;
}

// 最大堆建立
// 将N个元素按顺序存入，先买足完全二叉树的结构特性
// 调整各个结点为止，满足最大二叉树的有序性。

int main(int argc, char const *argv[])
{
   
    return 0;
}
