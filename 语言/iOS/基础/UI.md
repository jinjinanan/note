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

### 方形button圆的点击事件

```Objective-C

-(UIview *)hiteTest:(CGPoint)point withEvent:(UIEvent *)event{
    if(!self.userInteractionEnabled ||
        [self isHidden] ||
        self.alpha <= 0.01){
            return nil;
    }
    if([self pointInside:point withEvent:event]){
        //遍历当前对象子视图
        __block UIView *hit = nil;
        [self.subViews enumerateObjectsWithOptions:NSEnumerationReverse 
        usingBlock:^(__kindof UIView *_Nonnull obj,NSUinteger idx,BOOL *_Nonnull stop){
            //坐标转换
            CGPoint vonvertPoint = [self convertPoint:point toView:obj];
            //调用子视图的hittest方法
            hit = [obj hitTest:vonvertPoint withEvent:event];
            //如果找到了接受时间的对象 ，则停止遍历
            if(hit){
                *stop = YES
            }
        }];
        
    }
    
    if(hit){
        return hit;
    }
    else{
        return self;
    }

}

-(BOOL)pointInside:(CGPoint)point withEvent:(UIEvent *)event{
    CGFloat x1 = point.x;
    CGFloat y1 = point.y;

    CGFloat x2 = self.frame.size.width /2
    CGFloat y2 = self.frame.size.height / 2

    double dis = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    
    //在以当前空间中心为圆新半径为当前控件宽度的圆内
    if(dis <= self.frame.size.width / 2>){
        return YES
    }
    else{
        return NO
    }
}
```

### 事件响应的流程

```Objcetive-C
-(void)touchesBegan:(NSSet *)touchs withEvent:(UIEvent *)event;
-(void)touchesMoved:(NSSet *)touchs withEvent:(UIEvent *)event;
-(void)touchesEnded:(NSSet *)touchs withEvent:(UIEvent *)event;
```

### 图像显示原理

![img](../../../Sources/IMG_BDD9E4A3956A-12.jpeg)

![img](../../../Sources/IMG_0805.jpg)

CPU工作

```mermaid
graph LR
subgraph Layout
UI布局
文本计算
end
subgraph display
绘制(drawrect)
end
subgraph prepare
图片编解码
end
subgraph commit
提交位图
end
```

GPU渲染管线

```mermaid
graph LR
subgraph 顶点着色

end
subgraph 图元装配

end
subgraph 光栅化

end
subgraph 片段着色

end
subgraph 片段处理

end
```

GPU渲染完提交FrameBuffer

### UI卡顿，掉帧的原因

![img](../../../Sources/IMG_07FD329AA4FE-1.jpeg)

#### 优化方案

CPU工作
    - 对创建，调整，销毁放到子线程做
    - 预排版（布局计算，文本计算）放到子线程
    - 预渲染（文本等异步绘制，图片编码解码）

GPU优化
    - 纹理渲染 （避免离屏渲染）
    - 试图混合（减轻视图层级的复杂性）

UIView的绘制原理

![img](../../../Sources/IMG_D31047C01D04-1.jpeg)

系统默认绘制流程

![img](../../../Sources/IMG_82A02CAB913E-1.jpeg)

异步绘制

```Objective-C
- [layer.delegate displayLayer:]
```

    - 代理负责生成对应的bitmap
    - 设置bitmap作为layer.contents属性的值

![img](../../../Sources/IMG_EA16C04020A8-1.jpeg)

### 离屏渲染

- On-Screen Reddering
意为当前屏幕渲染，指的是GPU的渲染操作是在当前用于显示的屏幕缓冲区中进行

- Off-Screen Rending
意为离屏渲染，指的是GPU在当前屏幕缓冲区以外新开辟一个缓冲区进行渲染操作

#### 何时触发

- 圆角（当和maskToBounds一起使用时）
- 图层蒙版
- 阴影
- 光栅化

#### 为何要避免

触发离屏渲染会曾增加GPU的工作量，导致CPU和GPU工作超过16.7ms，导致掉帧

涉及到
    - 创建新的渲染缓冲区
    - 上下文切换
