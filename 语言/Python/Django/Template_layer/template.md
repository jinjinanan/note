# 模版

## 配置模版引擎

```Python
TEMPLATES = [
    {
        'BACKEND': 'django.template.backends.django.DjangoTemplates',
        'DIRS': [],
        'APP_DIRS': True,
        'OPTIONS': {
            # ... some options here ...
        },
    },
]
```

Django 有两个内置引擎`django.template.backends.django.DjangoTemplates`和`django.template.backends.jinja2.Jinja2`
DIRS:定义一个目录列表，告诉引擎按列表顺序搜索这些目录以查找模版源文件
APP_DIRS:告诉引擎是否进入以安装的APP中查找模版
OPTIONS的参数

|parameter|effect|example|
|---|---|---|
|autoescape|是否启动html自动转义，默认true||
|context_processors|||
|debug|bug调试，默认同setting||
|loaders|||
|string_if_invalid|||
|file_charset|||
|libraries|||
|builtins|||

## 静态路径