# Swift

## 可选类型

使用可选类型（optionals）来处理值可能缺失的情况

强制解析：当你确定一个可选类型中有值，可以在变量后加`!`来获取值

隐式解析可选类型（implicitly unwrapped optionals）：当可选类型被第一次赋值之后就可以确定之后一直有值的时候，主要被用在 Swift 中类的构造过程中。

## 访问控制

private fileprivate internal public open

private：当前类中访问（swift4 extension也可以）

fileprivate:当前的 Swift 源文件里可以访问

internal：（默认访问级别）

    internal 访问级别所修饰的属性或方法在源代码所在的整个模块都可以访问。
    如果是框架或者库代码，则在整个框架内部都可以访问，框架由外部代码所引用时，则不可以访问。
    如果是 App 代码，也是在整个 App 代码，也是在整个 App 内部可以访问。

public:可以被任意访问，但是无法继承和重写

open：可以任意访问，继承和重写

## 函数

## 闭包

### 表达式

```Swift
  { (parameters/接收的参数) -> (return type/闭包返回值类型) in
        statements/保存在闭包中需要执行的代码
  }
```

### 类型

```Swift
(parameters/接收的参数) -> (return type/闭包返回值类型)
```

### 闭包的创建，赋值，调用

#### 创建

#### 使用变量声明闭包

```Swift
    let closerName:(_ num1:Int)->(Int)
    closerName = {
        (_ num1:Int) -> (Int) in
        return num1
    }
    closerName(1) //调用闭包
```

#### 类型推断机制：

```Swift
let closerName:(_ num1:Int)->(Int)
closerName = {
    return ($0)
}
closerName(1) //调用闭包
```

基于类型推断机制，在闭包表达式中可以省略类型。同时可以使用 `($0) ($1)` 等方式来使用参数

### 参考

[Swift中闭包的简单使用](https://www.jianshu.com/p/7c599b96815b)

## extension

添加计算属性 - computed properties
添加方法 - methods
添加初始化方法 - initializers
添加附属脚本 - subscripts
添加并使用嵌套类型 - nested types
遵循并实现某一协议 - conform protocol
