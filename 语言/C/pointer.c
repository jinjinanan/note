#include <stdio.h>
#include <stdlib.h>


void learnPointer1(){
    // int a;
    // a = 6;
    // double b;
    // b = 3.0;
    // printf("sizeof(int)=%ld\n",sizeof(int));
    // printf("sizeof(int)=%ld\n",sizeof(a));
    // printf("sizeof(double)=%ld\n",sizeof(double));


    // 运算符 &
    int i = 0;
    int ii;
    int p;
    p = (int)&i;

    // c 的分配变量是分配在stack stack是自顶向下的分配（从上向下分配），先分配的变量地址高，后分配的地址低
    printf("%p\n",&i); //0x7ffee6a9a61c
    printf("%p\n",&ii);   //  0x7ffee6a9a618

    // 地址大小是否与int相同取决于编译器 32为相同 64为不同
    printf("%lu\n",sizeof(int));
    printf("%lu\n",sizeof(&i));

    // 取地址必须对一个变量取地址，如果不是一个变量，就不会取地址
}

void learnPointer(){
       // 指针
    int i;
    int *p = &i;

    // int* p,q;  p是一个指针，q是一个普通int类型的变量
    // int *p,q;

    // p指向i：实际是p里存放的值，是i的地址。 *p是一个指针，而不是int *类型
}


void f(int *p){
    printf("p=%p\n",p);
    printf("*p=%d\n",*p);
    *p = 26;
}

void g(int k){
    printf("k=%d\n",k);
}

void learnPointerAsParmater(){
       // 指针作为参数
    int i = 6;
    printf("&i = %p\n",&i);
    f(&i);
    g(i);
}



int main(int argc, char const *argv[])
{
   
    
    // 地址
    // learnPointer1()
    // 指针
    // learnPointer()

    // 指针作为参数
    // learnPointerAsParmater();

   

}
