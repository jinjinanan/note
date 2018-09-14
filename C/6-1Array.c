#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int a[] = {1,2,3,4};
    {
        printf("%lu\n",sizeof(a));
        printf("%lu\n",sizeof(a[0]));
         return 0;
    }   
    // 1. 如果在代码块”{}”中定义了变量，则该变量的生存周期和作用域将被限制在该代码块内。
    // 2. 代码块结束之后就释放了代码块中的内存

   
}
