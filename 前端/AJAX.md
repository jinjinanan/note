# AJAX（Asynchronous JavaScript and XML）

1. 创建对象
`XMLHttpRequest` 用于与服务器交换数据

2. 请求
```
xmlhttp.open("GET","url",true);
xmlhttp.send();
```
|方法|参数|
|---|---|
|open(method,url,async)| method:请求类型,url:链接,async:异步或同步|
|send(string)|string:用于post请求|

3. 响应
|属性|参数|
|---|---|
|responseText|获得字符串形式的响应数据|
|responseXML|获得 XML 形式的响应数据|

4. onreadystatechange 事件

|属性|参数|
|---|---|
|onreadystatechange|存储函数（或函数名），每当 readyState 属性改变时，就会调用该函数|
|readyState| 0: 请求未初始化, 1: 服务器连接已建立, 2: 请求已接收, 3: 请求处理中, 4: 请求已完成，且响应已就绪 |
|status|200: "OK"|

**AJAX修改图片**
```
<img id="test" src="http://i1.mifile.cn/a4/xmad_15057462331026_BpodE.jpg">
<button type="button" onclick="loadData()">获取我的 CD</button>
<script>
        function loadData() {
            var xmlhttp;
            if (window.XMLHttpRequest)
            {
                xmlhttp = new XMLHttpRequest();
            }
            else
            {
                xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
            }
            xmlhttp.onreadystatechange = function () {
                if (xmlhttp.readyState == 4 && xmlhttp.status == 200)
                {
                    xmlDoc = xmlhttp.responseText;
                    dic = JSON.parse(xmlDoc)
                    document.getElementById('test').src = dic['pics'][0]['address'];
                }
            }
            xmlhttp.open('GET','GETExposure',true)
            xmlhttp.send();
        }
    </script>
```