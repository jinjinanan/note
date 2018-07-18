# CSS

## web横排布局
[自适应布局webkit-box的用法](https://www.cnblogs.com/leena/p/6123005.html)

## css权重
> 权重记忆口诀。从0开始，一个行内样式+1000，一个id+100，一个属性选择器/class或者伪类+10，一个元素名，或者伪元素+1

`body #content .data img:hover`

> 最终的权重值是0122；#content是一个id选择器加了100，.data是一个class类选择器加了10，：hover伪类选择器加了10， body和img是元素加了1

[参考](http://www.w3cplus.com/css/css-specificity-things-you-should-know.html)
