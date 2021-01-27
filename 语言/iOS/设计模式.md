# 设计模式

- 责任链
- 桥接
- 适配器模式
- 单例模式
- 命令模式

## 六大设计原则

- 单一直则原则
- 开闭原则
- 依赖倒置原则
- 里氏替换原则
- 接口隔离原则
- 迪米特法则

### 单一职责原则

一个类只负责一件事

### 开闭原则

对修改关闭，对扩展开放

### 接口隔离原则

使用多个专门的协议，而不是一个庞大臃肿的协议

协议中的方法尽可能少

### 依赖倒置原则

抽象不应该依赖具体实现，具体实现可以依赖抽象

### 里氏替换原则

父类可以被子类无缝替换，且原有功能不受任何影响

### 迪米特法则

一个对象应当对其他对象有尽可能少的了解

高内聚，低耦合

## 责任链

UI时间传递机制是怎样实现的？你对其中运用到的设计模式是怎样理解的？

## 桥接

## 适配器

一个现有的类需要适应变化

- 对象适配器
- 类适配器

适配对象 -> 成员变量 -> 被适配对象

## 单例模式

``` Objective-C
//需要重写次两个方法

+(id)allocWithZone:(struct _NSZone *)zone{
    return [self sharedInstance]
}

+(id)copyWithZone:(nullable NSZone)zone{
    return [self sharedInstance]
}
```

## 命令模式

行为参数化，降低代码重合度

``` Objective-C

@class Command
typedef void (^CommandCompletionCallBack)(Command* cmd);

@interface Command : NSObject
@property (nonatomic,copy)CommandCompletionCallBack completion;

-(void)execute;
-(void)cancel; 
-(void)done;

@end
```

``` Objective-C
@implementation Command

-(void)execute{
    [self doen]
}

-(void)cancel{
    self.completion = nil
}

-(void)done{
    dispatch_async(dispatch_get_main_queue(),^{
        if(_completion){
            _completion(self)
        }
        self.completion = nil;
        [[CommandManager sharedInstance].arrayCommands removeObject:self];
    })
}
@end
```

```Objective-C
@interface CommandManager : NSObject
// 命令管理容器
@property (nonatomic,strong)NSMutableArray <Command *> *arrayCommands;
+(instancetype)sharedInstance;
// 执行命令
+(void)executeCommand:(Command *)cmd completion:(CommandCompletionCallBack)completion;
// 取消命令
+(void)cancelCommand:(Command *)cmd;
```

```Objective-C
@implementation

+(void)executeCommand:(Command *)cmd completion:(CommandCompletionCallBack)completion{
    if(cmd){
        //如果命令正在执行不作处理，负责添加并执行命令
        if(![self _isExecutingCommand:cmd]){
            [[[self sharedInstance] arrayCommands]addObject:cmd];
            //设置命令执行完成回掉
            cmd.completion = completion;
            //执行命令
            [cmd execute];
        }
    }
}

+(void)cancelCommand:(Command *)cmd{
    if(cmd){
        //从命令容器当中移除
        [[[self sharedInstance] arrayCommands] removeObject:cmd];
        [cmd cancel];
    }
}

+(BOOL)_isExecutingCommand:(Command *)cmd{
    if(cmd){
        NSArray *cmds = [[self sharedInstance] arrayCommands]
        for(Command *aCmd in cmds){
            //当前命令正在执行
            if(cmd == aCmd){
                return YES
            }
        }
    }
}
@end
```