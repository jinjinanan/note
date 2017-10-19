# JavaScript

## 语法

### js的位置
Js 文件可以在<head>,<body>和引用单独的js文件
<script src="myScript.js"></script> 引用单独的js文件

### DOM（Document Object Model，文档对象模型） & BOM（Browser Object Model，浏览器对象模型）

#### DOM

![DOM](https://github.com/jinjinanan/note/blob/master/Sources/Screen Shot 2017-10-19.png)

*操作HTML*

|操作|操作|
|---|---|
|JavaScript 能够改变页面中的所有 HTML 元素|	`document.getElementById(id).innerHTML=new HTML` 改变元素的内容；    `document.write(Date());` 重写整个html  [创建节点创建节点](http://www.w3school.com.cn/js/js_htmldom_elements.aspJavaScript)|
|能够改变页面中的所有 HTML 属性|`document.getElementById("image").src="landscape.jpg";`|
|JavaScript 能够改变页面中的所有 CSS 样式|	`document.getElementById("p2").style.color="blue";` |
|JavaScript 能够对页面中的所有事件做出反应||

*寻找HTML*

|操作|操作|
|---|---|
|通过 id 找到 HTML 元素|	`getElementById`|
|通过标签名找到 HTML 元素|`getElementsByTagName`|
|通过类名找到 HTML 元素||

*Dom事件*

- onload 和 onunload 事件会在用户进入或离开页面时被触发。
- onload 事件可用于检测访问者的浏览器类型和浏览器版本，并基于这些信息来加载网页的正确版本。
- onload 和 onunload 事件可用于处理 cookie。
- onchange 事件常结合对输入字段的验证来使用。
- onmouseover 和 onmouseout 事件可用于在用户的鼠标移至 HTML 元素上方或移出元素时触发函数。

#### BOM（Browser Object Model，浏览器对象模型。）

为了控制浏览器的行为而出现的一套API。例如：window是其中的一个对象

