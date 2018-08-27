
# 问题

## iOS

1. contentInset & adjustedContentInset
2. 影响导航栏和tableview因素
3. 状态栏
4. define a stretchable image (导航栏背景颜色，图片拉伸)
5. NSURLProtocol
6. 启动页适配

### contentInset & adjustedContentInset & safeAreaInset

1. safeAreaInset
    1. 视图被安全区覆盖的部分，如果一个视图完全在安全区内，则 safeAreaInset 为 0
2. contentInset
    1. contentSize 的 scrollview 的可滚动的区域
    2. contentOffset 是scrollview 当前显示区域顶点相对于frame顶点的偏移量
    3. contentInset:![contentInset](../../Sources/contentInsetInScrollview.jpg)
3. adjustedContentInset
   1. tableView的内容与边缘距离的是adjustedContentInset属性
   2. adjustedContentInset 计算方式

contentInsetAdjustmentBehavior | adjustedContentInset
--- | ---
UIScrollViewContentInsetAdjustmentAutomatic && 在 scrollview 的 一个automaticallyAdjustsScrollViewInsets = YES | adjustedContentInset = safeAreaInset + contentInset
UIScrollViewContentInsetAdjustmentScrollableAxes | 在可滚动方向上adjustedContentInset = safeAreaInset + contentInset，在不可滚动方向上adjustedContentInset = contentInset
UIScrollViewContentInsetAdjustmentNever | adjustedContentInset = contentInset
UIScrollViewContentInsetAdjustmentAlways | adjustedContentInset = safeAreaInset + contentInset

### 影响导航栏和tableview因素

#### translucent

1. YES
    ![图片](../../Sources/1530495757.png)
2. NO

    ![图片](../../Sources/1530495069.png)

translucent |UIView(iPhone 8) | UITableView(iPhone 8)
--- |--- | ---
NO | H:603 | H:667
YES | H:667 | H:667 Y:-64(Bounds)

#### contentInsetAdjustmentBehavior

> Constants indicating how safe area insets are added to the adjusted content inset.

1.UIScrollViewContentInsetAdjustmentAlways

> Always include the safe area insets in the content adjustment.

![图片](../../Sources/1530497559.png)

2.UIScrollViewContentInsetAdjustmentNever

> Do not adjust the scroll view insets.

![图片](../../Sources/1530498058.png)

translucent | contentInsetAdjustmentBehavior | UIView(iPhone 8) | UITableView(iPhone 8)
--- |--- | --- | ---
YES | UIScrollViewContentInsetAdjustmentAlways | H:667 | H:667 Y:-64(Bounds)
YES | UIScrollViewContentInsetAdjustmentNever | H:667 | H:667 Y:0(Bounds)
  

#### extendedLayoutIncludesOpaqueBars &contentInsetAdjustmentBehavior &  automaticallyAdjustsScrollViewInsets

``
//    if (@available(iOS 11.0, *)) {//        self.tableView.contentInsetAdjustmentBehavior = UIScrollViewContentInsetAdjustmentNever;
//    } else {
//        self.automaticallyAdjustsScrollViewInsets = NO;
//    }
``

[参考](http://yangzq007.com/2016/10/24/iOS%E6%BB%9A%E5%8A%A8%E8%A7%86%E5%9B%BE%E4%B8%8B%E5%8E%8B%E5%85%A8%E8%A7%A3%E6%9E%90/)

### 状态栏

|属性|意义|
--- | ---
Status bar is initially hidden（info.plist） | 控制初始化状态栏是否隐藏。YES 是隐藏，NO是不隐藏。
UIViewControllerBasedStatusBarAppearance（info.plist） | YES(视图控制器决定了状态栏的风格),NO(表示每个视图控制器必须显式地使用UIApplication对象来设置状态栏的风格)
preferredStatusBarStyle | 返回vc的状态栏的样式  UIStatusBarStyleDefault 或 UIStatusBarStyleDefault
setNeedsStatusBarAppearanceUpdate | 示意 vc 更新自己的status bar。往往需要和 childViewControllerForStatusBarStyle 使用。（当更新世，会调用container vc的childViewControllerForStatusBarStyle 返回由哪个vc决定状态栏的样式）
childViewControllerForStatusBarStyle | 当系统需要vc决定status bar的样式调用。

[参考1](https://www.jianshu.com/p/c0414830aa74)
[参考2](https://www.jianshu.com/p/534054a8c897)

### **define a stretchable image** (导航栏背景颜色，图片拉伸)

capInset

1   2   3

4   5   6

7   8   9

![图片](../../Sources/capInset.jpg)

不变：1，3，7，9。 5 

变：2，4，6，8

[官方文档](https://developer.apple.com/documentation/uikit/uiimage?changes=_3&language=objc)

[拉伸实验](https://www.jianshu.com/p/a577023677c1)

### 更新约束

``` Objective-C
updateConstraintsIfNeeded
updateConstraints
needsUpdateConstraints
setNeedsUpdateConstraints
```

### 启动页适配

LaunchImage 管理启动页

iPhone X :1125 * 2436
Retina HD 5.5 : 1242 * 2208
Retina HD 4.7 : 750 * 1334
Retina HD 4 : 640 * 1136