# HTML





### 块级元素和内连元素
块级元素：
	独自占一行
	```address , blockquote , center , dir , div , dl , fieldset , form , h1 , h2 , h3 , h4 , h5 , h6 , hr , isindex , menu , noframes , noscript , ol , p , pre , table , ul , li```
内联元素：
	默认几个内连元素可以在同一行上显示
	```a , abbr , acronym , b , bdo , big , br , cite , code , dfn , em , font , i , img , input , kbd , label , q , s , samp , select , small , span , strike , strong , sub , sup ```
可变元素
	`applet ,button ,del ,iframe , ins ,map ,object , script`
css可以自由定义块，内联元素，块内联
	`display:block`  -- 显示为块级元素
	`display:inline`  -- 显示为内联元素
`dipslay:inline-block` -- 显示为内联块元素，表现为同行显示并可修改宽高内外边距等属性

### 标签

##### `meta` 标签
`<meta name="viewport" content="width=device-width, initial-scale=1.0">` 
[width=device-width, initial-scale=1.0详解](http://blog.csdn.net/u012402190/article/details/70172371)

##### `script`

`<script type="text/javascript" src="uri"></script>` 导入js


##### `link`
`<link rel="stylesheet" href="uri" />` 导入css文件

##### `style`

样式
外部样式表
```
<head>
<link rel="stylesheet" type="text/css" href="mystyle.css">
</head>
```
内部样式表
```
<head>
<style type="text/css">
body {background-color: red}
p {margin-left: 20px}
</style>
</head>
```
内联样式表
```
<p style="color: red; margin-left: 20px">
This is a paragraph
</p>
```