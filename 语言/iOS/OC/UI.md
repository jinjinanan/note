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
sequenceDiagram
    participant 主线程
    participant 数据源
    participant 子线程

    主线程 ->> 数据源 : 删除操作
    子线程 ->> 数据源: loadmore
    
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

