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

![可接受类型对比](https://github.com/jinjinanan/note/blob/master/Sources/1504838752844314.jpg)


1. Optional的本质是一个包含了 nil 和普通类型的枚举，这是为了确保使用者在变量为 nil 的情况下会完成相应的处理；

2. 无论是 Optional(!) 还是 Optional(?) 都是一种Optional，在未设初始值时，默认为nil。Optional(!) 只是给予了自动拆包的权限，省略了判断其值是否为nil的过程，但是不能够保证它的值不为nil；

3. Optional(!) 在声明时和 Optional(?) 等价，在使用时和具体类型等价；

4. 一定要确保 Optional 不为 nil 的情况下才可直接拆包，不然会引发崩溃。
[参考](http://www.cocoachina.com/swift/20170908/20505.html)


---
### 基本运算符

#### 空盒运算符
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

 `(a..<b)`定义一个从 包含第一个值而不包括最后的值。到b **(不包括b)** 的区间

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

### 函数

#### 函数的参数和返回值
###### 返回元组
```
func minMax(array: [Int]) -> (min: Int, max: Int) {
     var currentMin = array[0]
     var currentMax = array[0]
     for value in array[1..<array.count] {
         if value < currentMin {
             currentMin = value
         } else if value > currentMax {
             currentMax = value
	} }
    return (currentMin, currentMax)
}
let bounds = minMax(array: [8, -6, 2, 109, 3, 71]) 
print("min is \(bounds.min) and max is \(bounds.max)")
```
###### 返回可选的元组
```
func minMax(array: [Int]) -> (min: Int, max: Int)? {
	...
}
```

#### 函数的参数标签和参数名称
###### 指定参数标签
```
func someFunction(argumentLabel parameterName: Int) 
{
// 在函数体内，parameterName 代表参数值
}
```
###### 忽略参数标签
```
func someFunction(_ firstParameterName: Int, secondParameterName: Int) {
// 在函数体内，firstParameterName 和 secondParameterName 代表参数中的第一个和第二个参数值
}
```
###### 默认参数值
```
func someFunction(parameterWithoutDefault: Int, parameterWithDefault: Int = 12) {
// 如果你在调用时候不传第二个参数，parameterWithDefault 会值为 12 传入到函数体中。
 }
```
###### 可变参数
```
func arithmeticMean(_ numbers: Double...) -> Double {
     var total: Double = 0
     for number in numbers {
         total += number
     }
     return total / Double(numbers.count)
}
arithmeticMean(1, 2, 3, 4, 5)
// 返回 3.0, 是这 5 个数的平均数。 arithmeticMean(3, 8.25, 18.75)
// 返回 10.0, 是这 3 个数的平均数。
```
###### 输入输出参数
**输入输出参数不能有默认值，而且可变参数不能用`inout`标记。**
```
func swapTwoInts(_ a: inout Int, _ b: inout Int) {

}

var someInt = 3
var anotherInt = 107
swapTwoInts(&someInt, &anotherInt)
```

#### 函数类型  

**函数的类型由函数的参数类型和返回类型组成**  

例1
```
func addTwoInts(_ a: Int, _ b: Int) -> Int 
{
}
(Int, Int) -> Int
```
例2
```
func printHelloWorld() 
{
}
() -> Void 
```
###### 使用函数类型  

**使用函数类型就像使用其他类型一样**  

`var mathFunction: (Int, Int) -> Int = addTwoInts`

###### 函数类型作为参数类型
```
func printMathResult(_ mathFunction: (Int, Int) -> Int, _ a: Int, _ b: Int) {
     print("Result: \(mathFunction(a, b))")
}
```
###### 函数类型作为返回类型
```
func stepForward(_ input: Int) -> Int {
     return input + 1
 }
func stepBackward(_ input: Int) -> Int {
     return input - 1
}
func chooseStepFunction(backward: Bool) -> (Int) -> Int {
     return backward ? stepBackward : stepForward
}
```
#### 嵌套函数

### 闭包
语法
```
{ (parameters) -> returnType in
     statements
}
```

#### 尾随闭包

#### 值捕获

#### 闭包是引用类型
函数和闭包都是引用类型

#### 逃逸闭包
当一个闭包作为参数传到一个函数中，但是这个闭包在函数返回之后才被执行
`@escaping`
```
var completionHandlers: [() -> Void] = []

//声明
func someFunctionWithEscapingClosure(completionHandler: @escaping () -> Void) {
    completionHandlers.append(completionHandler)
}
func someFunctionWithNonescapingClosure(closure: () -> Void) {
    closure()
}

//类
class SomeClass {
var x = 10
     func doSomething() {
         someFunctionWithEscapingClosure { self.x = 100 }
         someFunctionWithNonescapingClosure { x = 200 }
     }
}

// 执行函数时候，仅执行一般闭包，不会调用逃逸闭包， 逃逸闭包需手动执行 
let instance = SomeClass() instance.doSomething() print(instance.x)
// 打印出 "200"

completionHandlers.first?() print(instance.x)
// 打印出 "100"

```

逃逸闭包与




### Swift 调用 OC
Cocoapods 文档

### 关键字
`as!` 转换失败抱运行时错误。  
`as?` 转换失败 返回nil






### 生词
| 单词       | 词性   |  词义  |
| --------   | -----:  | :----:  |
|type annotation||类型标注|