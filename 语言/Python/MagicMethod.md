
# MagicMethod

## `__init__`

初始化函数

## `__new__`

构造函数，

## `__call__`

class实现`__call__`方法，该class的instance可以当函数使用

``` python
class Animal(object):

    __call__(self, words):
        print ('Hello: %s)% words

if __name__ == "__main__":
    cat = Animal()
    cat("I am cat!")

>>> Hello: I am cat!
```

## `__class__`

每个对象都有`__class__`用来返回对象的类型
`type()`可以查看类或实例的类型

## `__dict__`

存储类或者实例的属性方法
 
类的属性存储在类的 `__dict__` 中，实例的属性存储在实例的 `__dict__` 中；类的 `__dict__` 有属性，如果实例没有赋值，实例的 `__dict__` 就没有该属性。
当实例的 `__dict__` 中没有该属性时，访问属性会指向类的属性；如果有，则访问实例的 `__dict__` 。

## `__slots__`

限制属性的定义 *优化内存使用*
定义了 `__slots__` 不会再有 `__dict__`。
类和实例的 `__slots__` 属性名一样。
类的 `__slots__` 属性赋值后，实例 `__slots__` 中的属性就不能修改； 实例的 `__slots__` 赋值后，不影响类的，如果类的再修改，实例的就变为和类的值一样，并且不可修改。

[参考](http://docs.pythontab.com/learnpython/212/)

## __getattr__ && __setattr__

### __getattr__

在访问对象的item属性的时候，如果对象并没有这个相应的属性，方法，那么将会调用这个方法来处理

### __setattr__

设置参数时会调用的的一个方法，所有通过 . 运算符设置参数都调用此方法。容易造成循环调用

## __getattribute__

## __enter__ & __exit__

上下文管理协议 with as 语句

### __enter__

当with开始运行的时候触发此方法的运行

### __exit__

当with运行结束之后触发此方法的运行

## 参考

> 类提供默认行为，是实例的工厂 --《Learning Python》

[MagicMethod](http://www.oschina.net/translate/python-magicmethods?cmp)

[零基础学python](http://docs.pythontab.com/learnpython/)