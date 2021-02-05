# UI

- UITableView
- 事件传递&视图响应
- 图像显示原理
- 卡顿&原因
- 绘制原理&异步绘制
- 离屏渲染

## UITableView相关

- 重用机制
- 数据源同步

### 重用机制

```Objcetive-C
//实现重用机制的类
@interface ViewReusePool : NSObject

//从重用池当中取出一个可重用的view
-(UIView *)dequeueReuseableView;

//向重用池当中添加一个视图
-(void)addUsingView:(UIView *)view;

//设置方法，将当前使用中的视图移动到可重用队列当中
-(void)reset;
@end
```

```Objcetive-C
@interface ViewReusePool()

//等待重用的队列
@property (nonatomic,strong)NSMutableSet *waitUsedQueue;

//使用中的队列
@property (nonatomic,strong)NSMutableSet *usingQueue;
@end

@implementation ViewReusePool

-(id)init{
    self = [super init];
    if(self){
        _waitUsedQueue = [NSMutableSet set];
        _usingQueue = [NSMutableSet set];
    }
}

- (UIView *)dequeueReusableView{
    UIView *view = [_waitUsedQueue anyObject];
    if(UIview == nil){
        return nil;
    }
    else{
        //进行队列移动
        [_waitUsedQueue removeObject:view];
        [_usingQueue addObject:view];
        return view;
    }
}

-(void)addUsingView:(UIView *)view{
    if(view == nil){
        return;
    }
    [_usingQueue addObject:view];
}

-(void)reset{
    UIView *view = nil; 
    while((view = [_usingQueue anyObject])){
        [_usingQueue removeObject:view];
        [_waitUsedQueue addObject:view];
    }
}
```

### 数据源同步的问题

```mermaid
graph LR
subgraph 主线程
删除操作
end
subgraph 数据源
数据源1
end
subgraph 子线程
loadmore
end
删除操作 --> 数据源1
loadmore -->  数据源1
```

多线程对共享数据的一个访问

#### 并发访问，数据拷贝

```mermaid
sequenceDiagram
    participant 主线程
    participant 子线程

    主线程 ->>+ 子线程 : “拷贝数据”
    主线程 ->> 主线程: 删除一行数据
    Note left of 主线程:记录删除操作
    主线程 ->> 主线程 : reload UI
    主线程 ->> 主线程 : other work
    子线程 ->> 子线程 : 网络请求，数据解析，预排版
    Note right of 子线程:同步删除操作
    子线程 ->>- 主线程 : reload UI 
```

需要数据同步操作，和数据拷贝使用内存大

#### 串行访问

```mermaid
sequenceDiagram
    participant 主线程
    participant 串行队列
    participant 子线程

    子线程 ->> 子线程  : 网络请求，数据解析
    子线程 ->>+ 串行队列: 新增数据预排版等
    主线程 ->> 主线程:删除某一行
    主线程 -->> 串行队列:waiting
    Note right of 串行队列 : 同步数据删除
    串行队列 ->>- 主线程 : reload UI
```

子线程任务很耗时，删除动作会有延时

## UIView和CAlayer

```mermaid
graph LR
subgraph UIView
Myview
layer 
backgourndColor
end
subgraph CALayer
CAlayer
contents
backgourndcolor同名方法
end
id1[backing strore]
layer --> CAlayer
backgourndColor -->  backgourndcolor同名方法
contents --> id1

```

backing store 实际上是位图

- UIView为其提供内容，以及负责处理触摸等事件，参与响应链
- Calayer 负责显示内容contents

 体现了单一职责原则

## 事件传递&视图响应链

![img](../../../Sources/IMG_FECB022F9EAE-1.jpeg)

点击了C2位置

```Objcetive-C
//最终那个视图响应，返回那个视图
-(void)hitTest:(CGPoint)point withEvent:(UIEvent *)event;
//是否在当前视图内 ， 是YES
-(Bool)pointInside(CGPoint)point withEvent:(UIEvent *)event;
```

### 时间传递流程

```mermaid
graph TB
id1[点击屏幕]-->id2[UIApplication]
id2 --> id3[UIVindow]
id3 --> id4[hitTest:withEvent:]
id4 --> id5[pointInside:withEvent:]
id5 --> id6[Subviews]
id6 --> id7[UIViewA]
id6 --> id8[UIViewB]
id6 --> id9[其他同级UIView]
id7 --> id10[倒叙遍历'最后添加到UIwindow上的视图最优先被遍历']
id8 --> id10[倒叙遍历'最后添加到UIwindow上的视图最优先被遍历']
id9 --> id10[倒叙遍历'最后添加到UIwindow上的视图最优先被遍历']
id10 --> id11[hit = sub hitTest:p withEvent e]
id11 --> id12{hit != nil}
id12 --YES--> id13[结束]
```

### -(void)hitTest:(CGPoint)point withEvent:(UIEvent *)event 内部实现


```mermaid
graph TB
id1[start]-->id2{!v.hidden && v.userinterfactionEnabled &&v.alpha>0.001}
id2 --YES--> id3{v pointInside:point withEvent:event}
id3 --YES--> id4{for:int i = v.subviews.count -1 i>=0 i--}
id4 --> id5{sv = v.subviews%i% hittest:point withEvent:event}
id5 --> id6[sv != nil]

id6 --NO-->id4

id6 --YES--> id7[return sv]
id2 --NO--> id9[return nil]
id3 --NO--> id9
id4 --NO--> id10[return v]

id7 --> id11[结束 ]
id9 --> id11
id10 --> id11
```

