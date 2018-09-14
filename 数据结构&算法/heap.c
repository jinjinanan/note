#include <stdio.h>
#include <stdlib.h>

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
    H->data[0] = MaxSize;  //H->data 是 int 指针 。 这里data做数组使用 data[0] 直接存储？
    return H;
}

// 判断堆是否满了
int IsFull(MaxHeap H){
    if(H->size == H->Capacity){
        return 1;
    }
    return 0;
}

// 插入
void Insert(MaxHeap H, int item){
    int i;
    
}

int main(int argc, char const *argv[])
{
    int i = 4;
    MaxHeap h = malloc(sizeof(struct HeapStruct));
    h->data = malloc(sizeof(int));
    h->data[0] = i;
    h->data[1] = 2;
    printf("%p", h->data[1]);
    return 0;
}
