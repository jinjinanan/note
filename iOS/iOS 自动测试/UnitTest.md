# 单元测试

## 测试

TDD：Test-Driven Development，测试驱动开发
BDD
DSL：Domain-specific language，域特定语言

## 测试的标准

F.I.R.S.T.

每个测试都应该遵守的基本原则:

- 很快速(Fast) —— 测试应该能够被经常执行。
- 能隔离(Isolated) —— 测试本身不能依赖于外部因素或者其他测试的结果。
- 可重复(Repeatable) —— 每次运行测试都应该产生相同的结果。
- 带自检(Self-verifying) —— 测试应该包括断言，不需要人为干预。
- 够及时(Timely) —— 测试应该和生产代码一同书写。

**不要将测试和实现细节耦合在一起**

坏的测试:

- 不要测试私有方法(永远通过公有 API 测试你的代码)

## 断言

``` Objective-C
XCTAssertNil(expression, ...) //expression为空时通过，否则测试失败。
XCTAssertNotNil(expression, ...) //expression不为空时通过，否则测试失败。
```

## 参考文章

[测试](https://objccn.io/issue-15-4/)
[置换测试: Mock, Stub 和其他](https://objccn.io/issue-15-5/)