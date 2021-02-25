# Codable 协议

- 互转
- 字段不匹配
- 特殊数据类型
- 自定义编码过程

## 互转

```Swift
import UIKit

//JSON
let res = """
{
"name": "Jone",
"age": 17,
"born_in" : "China",
"sex": "male"
}
"""

//定义结构体实现Codable，一般情况下字段要与JSON的key一致，否则需要额外处理
struct Student: Codable {
    let name: String
    let age: Int
    let born_in :String
    let sex: String
}

//JSON -> 结构体/类 解码 decode
let decoder = JSONDecoder()
do {
    
    let stu:Student =  try decoder.decode(Student.self, from: res.data(using: .utf8)!)    
    print("name = \(stu.name) , age = \(stu.age) , born_in = \(stu.born_in) , sex = \(stu.sex)")
    
} catch  {    
    print(error)
}


print("---------------------------")

//结构体/类 -> JSON 编码 encode
let student = Student(name: "zhangsan", age: 20, born_in: "AnHui", sex:"female")
let encoder = JSONEncoder()
encoder.outputFormatting = .prettyPrinted

do {
    
    let data = try encoder.encode(student)  
    print(String(data: data, encoding: .utf8)!)
    
} catch  {    
    print(error)
}
```

## 特殊数据类型

### 枚举

```Swfit
enum Gender: String, Decodable {
    case male
    case female
    case other
}
```

## 字段不匹配

```Swift
import UIKit

//JSON
let res = """
{
"name": "Jone",
"age": 17,
"born_in" : "China",
"sex": "male"
}
"""

//定义结构体实现Codable，一般情况下字段要与JSON的key一致，否则需要额外处理
struct Student: Codable {
    let name: String
    let age: Int
    let bornIn :String
    let sex: String
    
    //所有属性写全 会同时影响编码与解码
    enum CodingKeys :String, CodingKey {
        case name
        case age
        case bornIn = "born_in"
        case sex
    }
}

//JSON -> 结构体/类 解码 decode
let decoder = JSONDecoder()
do {
    
    let stu:Student =  try decoder.decode(Student.self, from: res.data(using: .utf8)!)
    print("name = \(stu.name) , age = \(stu.age) , bornIn = \(stu.bornIn) , sex = \(stu.sex)")
    
} catch  {
    print(error)
}


print("---------------------------")

//结构体/类 -> JSON 编码 encode
let student = Student(name: "zhangsan", age: 20, bornIn: "AnHui", sex:"female")
let encoder = JSONEncoder()
encoder.outputFormatting = .prettyPrinted

do {
    
    let data = try encoder.encode(student)
    print(String(data: data, encoding: .utf8)!)
    
} catch  {
    print(error)
}
```

## 自定义编码过程