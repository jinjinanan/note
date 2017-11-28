# Swift

## 时间
|功能|时间|更多|
|---|---|---|
|数据类型|2017/10/31|||


---

### 数据类型

#### 声明常量和变量

let 来声明常量，用 var 来声明变量
```
let maximumNumberOfLoginAttempts = 10
var currentLoginAttempt = 0
```

#### 类型标注
```
var welcomeMessage: String
```

#### 可选类型

可选类型 **可以**等于 `nil`  
非可选类型 **不可以**等于 `nil` 

|操作|可选类型|隐式可选类型|
|---|---|---|
|声明|`let possibleString: String?`|`let assumedString: String!`|
|安全拆包| 使用`if` 判断 是否为`nil`|使用`if` 判断 是否为`nil`|
|强制拆包|`let forcedString: String = possibleString!`|`let implicitString: String = assumedString`|

![可接受类型对比](https://github.com/jinjinanan/note/blob/master/Sources/1504838752844314.jpg)。

**再次提醒一下，Optional(!) 和 Optional(?) 都可以使用这两种方式进行安全地拆包，只是编译器不会对没有处理 nil 情况的 Optional(!) 报错**

1. Optional的本质是一个包含了 nil 和普通类型的枚举，这是为了确保使用者在变量为 nil 的情况下会完成相应的处理；

2. 无论是 Optional(!) 还是 Optional(?) 都是一种Optional，在未设初始值时，默认为nil。Optional(!) 只是给予了自动拆包的权限，省略了判断其值是否为nil的过程，但是不能够保证它的值不为nil；

3. Optional(!) 在声明时和 Optional(?) 等价，在使用时和具体类型等价；

4. 一定要确保 Optional 不为 nil 的情况下才可直接拆包，不然会引发崩溃。
[参考](http://www.cocoachina.com/swift/20170908/20505.html)


---
### 基本运算符

#### 空合运算符
`a ?? b ` 与 `a != nil ? a! : b` 相等

#### 区间运算

##### 闭区间运算

`(a...b)` 定义一个包含从a到b**(包括a和b)**的所有值的区间

```
for index in 1...5 { 
   print("\(index) * 5 = \(index * 5)")   
}  
// 1 * 5 = 5   
// 2 * 5 = 10   
// 3 * 5 = 15   
// 4 * 5 = 20   
// 5 * 5 = 25   
```

###### 半开区间

 `(a..<b)` 定义一个从 包含第一个值而不包括最后的值。到b **(不包括b)** 的区间

### 字符和字符串

字符串是值类型

### 集合

### 控制流

```
if #available(iOS 10, macOS 10.12, *) {
// 在 iOS 使用 iOS 10 的 API, 在 macOS 使用 macOS 10.12 的 API
} else {
// 使用先前版本的 iOS 和 macOS 的 API
}
```



### 枚举




### Swift 调用 OC
Cocoapods 文档

### 关键字
`as!` 转换失败抱运行时错误。  
`as?` 转换失败 返回nil






### 生词
| 单词       | 词性   |  词义  |
| --------   | -----:  | :----:  |
|type annotation||类型标注|