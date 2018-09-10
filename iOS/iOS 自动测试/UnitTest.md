# 单元测试

## 测试介绍

TDD：Test-Driven Development，测试驱动开发
BDD：(Behavior Driven Development)，行为驱动开发
DSL：Domain-specific language，域特定语言

### 测试的标准

F.I.R.S.T.

每个测试都应该遵守的基本原则:

- 很快速(Fast) —— 测试应该能够被经常执行。
- 能隔离(Isolated) —— 测试本身不能依赖于外部因素或者其他测试的结果。
- 可重复(Repeatable) —— 每次运行测试都应该产生相同的结果。
- 带自检(Self-verifying) —— 测试应该包括断言，不需要人为干预。
- 够及时(Timely) —— 测试应该和生产代码一同书写。

** 不要将测试和实现细节耦合在一起**

坏的测试:

- 不要测试私有方法(永远通过公有 API 测试你的代码)

### 断言

``` Objective-C
XCTAssertNil(expression, ...) //expression为空时通过，否则测试失败。
XCTAssertNotNil(expression, ...) //expression不为空时通过，否则测试失败。
```

## BDD & TDD

BDD (Behavior Driven Development)行为驱动开发
TDD（Test-Driven Development）测试驱动开发

### kiwi

kiwi

## 依赖注入

1. 构造器注入
    >基本上，构造器注入应该作为首选武器存在。其优势就是让所涉及的依赖非常清晰。
    >缺点:这个类的依赖对象也太多了些,它可能已经违背了单一职能原则.
2. 属性注入
    >优点：属性注入的长处是将初始化与注入分离，这在不能改变调用者部分的时候非常有用
    >缺点：初始化与注入分离！属性注入使得初始化不充分
    - 必须防范属性被任意重设值。这需要复写系统默认为属性生成的 setter，要保证相应的实例变量为 nil 以及传入的参数不是 nil。
    - getter 是否需要线程安全？如果需要，那么与实现需要兼顾效率和线程安全的 getter 相比，使用构造器注入就显得容易多了。
    - 请确定默认值不会引用到其他库的代码
3. 方法注入
    >假如所依赖的对象针对每次调用都会有所不同的话，使用方法注入会比较好

### 构造器注入

## Mock & Stub

## 参考文章

[测试](https://objccn.io/issue-15-4/)
[置换测试: Mock, Stub 和其他](https://objccn.io/issue-15-5/)