# Flask-Sqlalchemy

### 查询数据
---

|功能|时间|更多|
|---|---|---|
|[增改删查](#1)|2017/10/28||

<h4 id='1'>增改删查</h4>
**增**  
```
	def confirm(self):
		db.session.add(self)
```

**删**  
```
    def delete(self):
        m = Admin.query.filter_by(username=self.username).first()
        db.session.delete(m)
        db.session.commit()
```


## 单词
| 单词       | 词性   |  词义  |
| --------   | -----:  | :----:  |
|assumption|||
|expect|||
|data back out of our database||返回数据|

| 句子       | 释义   |  笔记  |
| --------   | -----:  | :----:  |
|**When you access it** you will get back a new query object **over all records**|当您访问它时，您会得到一个**新的所有记录的**查询对象。|get back [V] 取回<br>|
|You **can then** use methods like filter() to filter the records **before** you **fire** the select **with** all() or first().|在使用 all() 或者 first() 发起查询之前可以使用方法 filter() 来过滤记录。|fire[V]发起;<br>then[adv]然后|

V+adv & v + prep的区别
V + N + adv
V + Prep + N