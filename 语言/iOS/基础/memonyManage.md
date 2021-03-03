# 内存管理

- 内存布局
- 内存管理方案
- 数据结构
- ARC & MRC
- 引用计数
- 弱引用
- 自动释放池
- 循环引用

## 内存布局

![img](../../../Sources/ScreenShot2021-01-28at102618PM.png)

栈区向下增长，堆区向上增长

- stack:方法调用
- heap:通过alloc等分配的对象
- bss:未初始化的全局变量等
- data:以初始化的全局变量等
- text:程序代码

## 内存管理方案

- TaggedPointer:对一些小对象如(NSNumber)
- NONPOINTER_ISA:在64位架构下
- 散列表:引用计数表，弱引用表

> objc-runtime-680版本讲解

### TaggedPointer

- Tagged Pointer专门用来存储小的对象，例如NSNumber和NSDate
- Tagged Pointer指针的值不再是地址了，而是真正的值。所以，实际上它不再是一个对象了，它只是一个披着对象皮的普通变量而已。所以，它的内存并不存储在堆中，也不需要 malloc 和 free。
- 在内存读取上有着 3 倍的效率，创建时比以前快 106 倍。

[Tagged Pointer的实现细节](https://blog.devtang.com/2014/05/30/understand-tagged-pointer/)

### NONPOINTER_ISA

#### arm64架构下,64个比特位的存储信息

0-15位

｜0｜0｜0｜0｜0｜0｜0｜0｜0｜0｜0｜0｜0｜0｜0｜0｜

｜shiftcls(3-15)｜has_cXX_dtor(2)｜has_assoc(1)｜indexed(0)｜

16 - 31位

｜0｜0｜0｜0｜0｜0｜0｜0｜0｜0｜0｜0｜0｜0｜0｜0｜

｜shiftcls(31-16)｜

32 - 47 位

｜0｜0｜0｜0｜0｜0｜0｜0｜0｜0｜0｜0｜0｜0｜0｜0｜

|extra_rc(45-47)|has_sidetable_rc(44)|deallocating(43)|weakly_referenced(42)|magic(36-41)|shiftcls(32-35)|

63 - 48

｜0｜0｜0｜0｜0｜0｜0｜0｜0｜0｜0｜0｜0｜0｜0｜0｜

|extra_rc(64-48)|

- indexed：如果是0 代表是一个纯的is指针，里面的内容是类的地址; 如果是1 不仅是类对象的地址，而且有内存管理方面的信息
- has_assoc: 是否有关联对象，0没有，1有
- has_cXX_dtor:当前对象是否有使用到c++的一些东西,在ARC下也可以表示使用ARC管理的
- shiftcls : 类对象的指针地址
- weakly_referenced:标记当前是否有弱引用指针
- deallocating:是否正在进行deallocate 操作
- has_sidetable_rc:如果当前的引用计数存储达到上限，需要外挂一个sidetable的数据结构去存储相关的引用计数
- extra_rc:额外的引用计数

#### SideTables()结构

![img](../../../Sources/IMG_184062A4C446-1.jpeg)

#### SideTable结构（散列表）

![img](../../../Sources/IMG_A08EA5644307-1.jpeg)

#### 为什么不是一个SideTable

如果所有引用计数都在一个表中，那么多个对象在不同线程中操作该表，操作过程中加锁，造成排队操作现象；
而如果拆成多个表引入分离锁，那么就减小了这种排队的可能，提升了访问效率

#### 怎样实现快速分流

SideTable的本质是一张Hash表

#### Sninlock_t

- Spinlock_t 是“忙等”的锁。
- 适用于轻量访问。如 +1，-1的操作

#### 引用计数表

RefcountMap是一个Hash表

使用hash查找获得引用计数的值
ptr->(DisguisedPtr(objc_object)->size_t(引用计数的值)

引用计数是用hash表实现，为什么要用hash表，因为hash表的查找是O(1)

size_t (unsigned long)

|0|0|0|...|0|0|0|0|0|
|RC(62)|deallocating(1)|weakly_referenced(1)|

- 标记当前是否有弱引用指针
- deallocating:是否正在进行deallocate 操作
- RC 该对象的实际的引用计数值

在取引用计数值的时候要偏移两位

#### 弱引用表

weak_table_t 也是一张hash表

![img](../../../Sources/IMG_503A2F611834-1.jpeg)

- weak_entry_t 结构体数组，存储实际的弱引用结构体指针

### MRC

手动引用计数

- alloc 分配一个内存空间
- retain +1
- release -1
- retainCount 获取当前引用计数值
- autorelease 当前对象在autorelease结束的时候 调用release操作
- dealloc 在调用dealloc时需要调用super dealloc 来释放父类的成员变量

### ARC

自动引用计数

ARC是LLVM和Runtime协作的结果

ARC中禁止手动调用 retain/release/retainCount/dealloc

ARC中新增weak，strong属性关键字

### 引用技术管理

实现原理分析

- alloc
- retain
- release
- retainCount
- dealloc

#### alloc

经过一系列调用，最终调用了C函数calloc。此时并没有设置引用计数为1.

#### retain

```C++
Sidetable& table = SideTables()[this];
size_t& refcntStorage = table.refcnts[this];
refcntStorage += SIDE_TABLE_RC_ONE;
//SIDE_TABLE_RC_ONE是一个宏，并不是+1 因为 size_t 中有两位偏移量
```

#### release实现

```C++
Sidetable& table = SideTables()[this];
RefcountMap::iterator it = table.refcnts.find(this);
it-second -= SIDE_TABLE_RC_ONE
//SIDE_TABLE_RC_ONE是一个宏，并不是-1 因为 size_t 中有两位偏移量
```

#### retainCoun实现

```C++
Sidetable& table = SideTables()[this];
size_t refcnt_result = 1;
RefcountMap::iterator it = table.refcnts.find(this);
refcnt_result += it->second >> SIDE_TABLE_RC_SHIFT;
```

#### dealloc实现

![img](../../../Sources/IMG_C7F95A5F056D-1.jpeg)

- nonpointer_isa 判断是否使用了非指针型的isa
- weakly_referenced 是否有weak指针指向他
- has_assoc 判断当前对象是否有关联对象
- has_cXX_dtor 判断当前对象内部实现是否涉及到C++ 以及是否使用ARC管理内存
- has_sidetable_rc 当前对象引用计数使用sidetable

#### object_dispose()实现

```mermaid
graph TB;
    开始-->objc_destructInstance函数;
    objc_destructInstance函数-->C函数free;
    C函数free-->结束;
```

#### objc_destructInstance实现

```mermaid
graph TB
    id1(开始)-->id2{hasCXXDtor};
    id2--YES-->id3[objc_cXXDestruct函数];
    id2--NO-->id4{hasAssociatedObjects};
    id4--YES-->id5[_objc_remove_assocations函数];
    id4--NO-->id6{clearDeallocating函数};
    id5-->id6
    id6-->id7(结束)
```

#### clearDeallocating函数

```mermaid
graph TB
    id1(开始)-->id2[sidetable_clearDeallocating函数];
    id2-->id3[weakly_clear_no_lock函数];
    id3-->id4[table.refcnts.erase函数];
    id4-->id7(结束)
```

- weakly_clear_no_lock函数 将指向该对象的弱引用指针值为nil
- table.refcnts.erase函数 从引用计数表中擦除该对象引用计数

### 弱引用管理

```
{
    id _weak obj1 = obj;
}
```

经过编译之后

```
{
    id obj1;
    objc_initWeak(&obj1,obj);
}
```

添加weak变量

```mermaid
graph TB
    id1(objc_initWeak函数) --> id2(storeWeak函数)
    id2 --> id3(weak_register_no_lock函数)
```

#### 清除weak变量，同时设置指向为nil

```mermaid
graph TB
    id1(dealloc函数) --> id2(...)
    id2 --> id3(weak_clear_no_lock函数)
```

当一个对象被dealloc之后，dealloc内部实现中会调用weak_clear_no_lock()函数,
该函数会根据当前指针查找弱引用表，把弱引用都都拿出来（是一个数组）。然后便利数组所有弱引用指针
并置为nil

### 自动释放池

```Objective-C
-(void)viewDidLoad{
    [super viewDidLoad];
    NSmutableArray *array = [NSMutableArray array];
    NSLog(@"%@",array)
}
```

- array 的内存是在什么时机释放的？
- AutoreleasePool的实现原理是怎样的？
- AutoreleasePool为什么可以嵌套使用？

编译器会将@autoreleasepoll「」改写为：

```Objcetive-C
void *ctx = objc_autoreleasePoolPush();
{}中的代码
objc_autoreleasePoolpop(ctx)
```

objc_autoReleasePoolPush 内部实现

```mermaid
graph TB
    id1(objc_autoreleasePoolPush函数) --> id2(AutoreleasePoolPage::push)
```

#### objc_autoReleasePoolPush 内部实现

```mermaid
graph TB
    id1(objc_autoreleasePoolPop\ctx\) --> id2(AutoreleasePoolPage::pop\ctx\)
```

一次pop实际相当于一次批量的pop操作

#### 自动释放池的数据结构

- 是以栈为结点通过双向链表的形式组合而成的
- 适合线程一一对应

#### 双向链表

<--- parentPtr
----> childPtr

#### AutoreleasePoolPage的属性

id *next;
AutoreleasePoolPage* const parent;
AutoreleasePoolPage* child;
pthread_t const thread; 和线程一一对象

#### AutoreleasePoolPage::push

![img](../../../Sources/IMG_926DCD7F483E-1.jpeg)

#### [obj autorelease]实现

```mermaid
graph TB
    id1(开始) --> id2{next==栈顶}
    id2 --YES--> id3[增加一个栈结点到链表上]
    id2 --NO--> id4(add\obj\)
```

![img](../../../Sources/IMG_DF040CFCC81A-1.jpeg)

#### AutoreleasePoolPage::pop

1. 根据传入的哨兵对象找到对应的位置
2. 给上次push操作之后添加的对象一次发送release消息
3. 回退next指针到正确位置

#### array 的内存是在什么时机释放的？

在当次runloop将要结束的时候调用AutoreleasePoolPage::Pop()

#### AutoreleasePool为什么可以嵌套使用？

多层嵌套就是多次插入哨兵对象

#### 什么时候使用手动AutloreleasePool

在for循环中alloc 图片数据等内存消耗较大的场景手动插入autoreleasePool

### 循环引用

- 自循环引用
- 相互循环引用
- 多循环引用

#### 自循环引用

对象给自己的成员变量赋值自己，就造成了自循环引用

#### 相互循环引用

 对象A的属性a 指向对象B
 对象B的属性b 指向对象A

- 代理
- block
- NStimer
- 大环循环引用

#### 如何破除循环引用？

- 避免产生循环引用
- 在合适的时机手动断环

#### 具体的解决方案都有哪些

- __weak
- __block
- __unsafe_unretained

##### __block破解

- MRC下 ,__block修饰的对象不会增加其引用技术，避免了循环引用
- ARC下，__block修饰对象会被强引用，无法避免循环引用，需手动解环

#### __unsafe_unretained

- 修饰对象不会增加其引用计数，避免了循环引用
- 如果被修饰对象在某一时机被释放，会产生悬垂指针

### 循环引用示例

 - block

 NSTimer的循环引用

```mermaid
graph LR
    id1(VC) --> id2(对象)
    id2 --> id3(NSTimer)
    id3 --> id2
```

错误

```mermaid
graph LR
    id1(VC) --> id2(对象)
    id2 -.-> id3(NSTimer)
    id3 --> id2
```

原因

```mermaid
graph LR
    id1(VC) --> id2(对象)
    id2 -.-> id3(NSTimer)
    id3  --> id2
    id4(Runloop)-->id3
```

非重复定时器 可以同过手动置为nil 并调用释放方法
重复定时器

```mermaid
graph LR
    id1(VC) --> id2(对象)
    id3(中间对象) -.->id2
    id3 -.-> id4(NSTimer)
    id4  --> id3
    id5(Runloop)-->id4
```

在中间对象的回调方法中判断 id2 是否被释放，如果为nil 则手动释放NSTimer
