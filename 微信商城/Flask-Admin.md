# Flask-Admin
---


### Managing Files & Folders

使用
```
import os.path as op

from flask_admin import Admin
from flask_admin.contrib.fileadmin import FileAdmin

admin = Admin()

path = op.join(op.dirname(__file__), 'static')
admin.add_view(FileAdmin(path, '/static/', name='Static Files'))
```

扩展 `BaseFileAdmin`
使上传后保存名字到数据库
```
class HomeExposure(FileAdmin):
    def on_file_upload(self, directory, path, filename):			#BaseFileAdmin 保存到服务器成功后调用此方法
        relationPath = url_for('static', filename='UploadImgs/' + filename, _external=True)
        from .Model import Exposure
        from . import db
        m = Exposure(filename, relationPath)
        db.session.add(m)
```


## 单词
| 单词       | 词性   |  词义  |例子|
| --------   | -----:  | :----:  | --- |
|Alternatively||
|dedicate|V|把...献给|
|dedicated|adj|献身的，专心致志的|a dedicated teacher |
|Model views allow you to add a **dedicated** set of admin pages for managing any model in your database.|||
|backend||端|
|administrative pieces||管理部件|
|Straight|adj||
|maintain|||
|consistent|adj|一贯|
|experience|n|经验|
|suit|N|套装|
|the CRUD operations|N|Create,Retrieve,Update,Delete|
|ability|N|能力|


