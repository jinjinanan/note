# 数据库和model的使用

## Django 使用 Mysql

### 1.下载pymysql

`pip install pymysql`

### 2.配置 setting 

```Python
import pymysql         # 一定要添加这两行！通过pip install pymysql！
pymysql.install_as_MySQLdb()

DATABASES = {
    'default': {
        'ENGINE': 'django.db.backends.mysql',
        'NAME': 'mysite',
        'HOST': '192.168.1.1',
        'USER': 'root',
        'PASSWORD': 'pwd',
        'PORT': '3306',
    }
}
```

## Django 数据迁移

### 1. 配置setting，启用模型

```Python
INSTALLED_APPS = [
    'YourAppName.apps.YourAppNameConfig',,
]
```

### 2. 运行 makemigrations 保存模型修改记录文件

`python manage.py makemigrations YourAppName`

### 3. 执行模型修改记录文件

`python manage.py migrate YourAppName`

### 查看 模型修改记录文件的sql语句

`python manage.py sqlmigrate YourAppName identifier`

### 已存在的model添加字段需要设置默认值

## project 多个app使用分别使用不不同的数据库

### 1.配置setting

```Python
import pymysql         # 一定要添加这两行！通过pip install pymysql！
pymysql.install_as_MySQLdb()

DATABASES = {
    'default': {
        'ENGINE': 'django.db.backends.sqlite3',
        'NAME': os.path.join(BASE_DIR, 'sqlite3'),
    },
    'dbName1': {
        'ENGINE': 'django.db.backends.mysql',
        'NAME': 'dbName',
        'HOST': '192.168.1.1',
        'USER': 'root',
        'PASSWORD': 'pwd',
        'PORT': '3306',
    },
}
```

1. dbName1:此配置的别称
2. dbName:mysql中对应的数据库名字

### 2.设置路由规则

`DATABASE_ROUTERS = ['PrjectName.database_router.DatabaseAppsRouter']`

1. PrjectName:是项目名称
2. database_router:定义路由规则database_router.py文件名称。
3. DatabaseAppsRouter:路有规则的类名称，这个类在database_router.py中定义

### 3. 设置App对应数据库的路由规则

```Python
DATABASE_APPS_MAPPING = {
    'appName1':'dbName1',
}
```

1. appName1:App的名字
2. dbName1数据库的配置的别称
3. 不配置的app则使用default配置

### 4. 创建数据库路由规则

### 5. model创建

```Python
class Users(models.Model):
    name = models.CharField(max_length=50)
    passwd = models.CharField(max_length=100)

    def __str__(self):
        return "appName1 %s " % self.name

    class Meta:
        app_label = "appName1"
```

1. 在Meta中设置app_label

### 6. 生成数据表

`python3 manage.py migrate appName1 --database=dbName`

在迁移数据的是有要设置--database参数，指定在那个数据库生成表