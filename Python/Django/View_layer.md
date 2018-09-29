# 视图层

## URL路由

Django 处理请求的过程：

1. 首先是决定要使用哪个URLconf模块，一般是setting文件的ROOT_URLCONF关键字决定家在哪个模块

2. 加载该模块并寻找 urlpatterns 。t
3. 依次匹配每个URL，在与请求的URL首次成功匹配的模式停下来
4. 倒入并调用匹配行中给定的视图

URL匹配模式书写规范
`re_path(r'^articles/([0-9]{4})/([0-9]{2})/$', views.month_archive),`

1. 每个正则前面都加r，表示字符串中任何字符不要转义
2. 不用添加前导的反斜杠
3. 如果要在URL中捕获一个值，用圆括号扩住匹配该值的正则。处理的视图是位置参数
4. 如果要给捕获的值起一个名字，则正则格式`(?P<name>pattern)`。处理的视图是关键字参数。

5. 视图的关键字也可以使用默认参数。但是优先使用匹配来的值
6. URL中捕获的参数都是字符串类型

命名组的语法

## 路由转发

`re_path(r'AboutModel/', include('AboutModel.urls')),`

一级路由 URL中没有$，同时一级路由将正则匹配中剩下的部分转发给，include中包含的URLConf做进一步处理

`url(r'^blog/(?P<year>[0-9]{4})/$', views.year_archive, {'foo': 'bar'}),`
向视图 year_archive 传递额外的关键字为foo的参数



## 视图函数和快捷方式

HttpREsponse