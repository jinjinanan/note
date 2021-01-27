# JQuery

### 基础语法

`$(selector).action()`

美元符号定义 jQuery

选择符（selector）"查询"和"查找" HTML 元素([选择器](http://www.w3school.com.cn/jquery/jquery_ref_selectors.asp))

jQuery 的 action() 执行对元素的操作([事件](http://www.w3school.com.cn/jquery/jquery_ref_events.asp))

`$(document).ready(function(){});` 简写 `($(function(){})`

防止文档在完全加载（就绪）之前运行 jQuery 代码

### JQuery HTML

**选择器**

|语法|	描述|
|---|---|
|$(this)	|当前 HTML 元素|
|$("p")	|所有 `<p>` 元素|
|$("p.intro")	|所有 `class="intro"` 的 <p> 元素|
|$(".intro")	|所有 `class="intro"` 的元素|
|$("#intro")	|id="intro" 的元素|
|$("ul li:first")	|每个 	`<ul>` 的第一个 `<li>` 元素|
|$("[href$='.jpg']")	|所有带有以 `".jpg"` 结尾的属性值的 	`href` 属性|
|$("div#intro .head")	|`id="intro"` 的 <div> 元素中的所有 `class="head"` 的元素|

[文档操作](http://www.w3school.com.cn/jquery/jquery_ref_manipulation.asp)
[属性操作](http://www.w3school.com.cn/jquery/jquery_ref_attributes.asp)
[CSS操作](http://www.w3school.com.cn/jquery/jquery_ref_css.asp)
[遍历](http://www.w3school.com.cn/jquery/jquery_ref_traversing.asp)

### JQuery 动画

### Jquery AJAX
#### POST & GET
声明
```
$.post(URL,data,callback);
```
例子
```
 $.post("demo_test_post.asp",
  {
    name:"Donald Duck",
    city:"Duckburg"
  },
  function(data,status){
    alert("Data: " + data + "\nStatus: " + status);
  });
```
简写
```
$.ajax({
  type: 'POST',
  url: url,
  data: data,
  success: success,
  dataType: dataType
});
```

[AJAX手册](http://www.w3school.com.cn/jquery/jquery_ref_ajax.asp)


