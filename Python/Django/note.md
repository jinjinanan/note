# 笔记

## 项目

### 项目文件

- 外层的mysite/目录与Django无关，只是你项目的容器，可以任意命名。
- manage.py：一个命令行工具，用于与Django进行不同方式的交互脚本，非常重要！
- 内层的mysite/目录是真正的项目文件包裹目录，它的名字是你引用内部文件的包名，例如：mysite.urls。
- mysite/__init__.py:一个定义包的空文件。
- mysite/settings.py:项目的主配置文件，非常重要！
- mysite/urls.py:路由文件，所有的任务都是从这里开始分配，相当于Django驱动站点的内容表格，非常重要！
- mysite/wsgi.py:一个基于WSGI的web服务器进入点，提供底层的网络通信功能，通常不用关心。

### 创建应用

`$ python manage.py startapp appName`

include 多级路由。它把接收到的url地址去除前面的正则表达式，将剩下的字符串传递给下一级路由进行判断

```Python
from django.conf.urls import include, url

urlpatterns = [
    url(r'^polls/', include('polls.urls')),
]
```

## 数据库&model&后台

### 数据库操作

```Python
DATABASES = {
    'default': {
        'ENGINE': 'django.db.backends.sqlite3',
        'NAME': os.path.join(BASE_DIR, 'db.sqlite3'),
    }
}
```

ENGINE 数据库引擎
NAME 数据库名字。

在迁移之前需要在 Django 的 setting 中 INSTALLED_APPS 字段下添加该应用

`python manage.py makemigrations appName`
用文件记录models的改动

`python manage.py migrate`
对数据库执行真正的迁移动作

`python manage.py sqlmigrate polls 0001`
可以看看migrate实际执行的sql语句

已存在的model添加字段需要添加默认值
`from django.utils import timezone`可以设置现在的时间

### 后台

`python manage.py createsuperuser`
创建一个可以登陆后台的账户

### 在后台中管理model

在app的admin.py中，注册model
`admin.site.register([ModelName,ModelName1])`

#### admin.site.register([ModelName,ModelName1])

位置：/django/contrib/admin/sites.py

```Python
class AdminSite:...

class DefaultAdminSite(LazyObject):
    def _setup(self):
        AdminSiteClass = import_string(apps.get_app_config('admin').default_site)
        self._wrapped = AdminSiteClass()

site = DefaultAdminSite()
```

DefaultAdminSite 是一个继承自LazyObject的懒加载包装类。
`apps.get_app_config('admin').default_site` 导入的是`AdminSite`类。
`admin.site.register()`在
`AdminSite`定义
`def register(self, model_or_iterable, admin_class=None, **options):`

## 视图

### url正则

### get_object_or_404

### url硬编码&urlnames的命名空间

区分多个app的命名空间

```Python
app_name = 'polls'
urlpatterns = [
    url(r'^(?P<question_id>[0-9]+)/$', views.detail, name='detail'),
]
```

urls.py中定义命名空间

`<li><a href="{% url 'polls:detail' question.id %}">{{ question.question_text }}</a></li>`

模版中定义url,urlnames的命名空间

### {% csrf_token %}

CSRF

### request.POST

通过键名提交访问的数据

### HttpResponseRedirect

`HttpResponseRedirect(reverse('polls:results', args=(question.id,)))`
重定向URL