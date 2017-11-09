# 实践

---

## 自定义16进制UIColor

```
func sHexColor(_ hexColor:String) -> UIColor {
    var red:UInt32 = 0
    var green:UInt32 = 0
    var blue:UInt32 = 0
    
    Scanner.init(string: hexColor.substring(with: Range.init(NSMakeRange(0, 2), in: hexColor)!)).scanHexInt32(&red)
    Scanner.init(string: hexColor.substring(with: Range.init(NSMakeRange(2, 2), in: hexColor)!)).scanHexInt32(&green)
    Scanner.init(string: hexColor.substring(with: Range.init(NSMakeRange(4, 2), in: hexColor)!)).scanHexInt32(&blue)
    return UIColor.init(red: CGFloat(red)/255.0, green: CGFloat(green)/255.0, blue: CGFloat(blue)/255.0, alpha: 1)
}
```

`swift` 中没有宏 但可以创建一个 `.swift` 文件
权限
Range与NSRange
[Scanner](http://blog.csdn.net/likendsl/article/details/7974761)

## 扩展String

```
extension String
{
    subscript(r:Range<Int>) -> String
    {
        get
        {
            let startIndex = self.index(self.startIndex, offsetBy: r.lowerBound)
            let endIndex = self.index(self.startIndex, offsetBy: r.upperBound)
            return self[startIndex..<endIndex]
        }
    }
}
```
下标
string
extension权限
Range<Int>

## swift 选择图片视频
