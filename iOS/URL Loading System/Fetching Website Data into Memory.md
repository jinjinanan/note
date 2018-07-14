# Fetching Website Data into Memory

**Receive** data **directly** into memory by creating a data task from a URL session.
从 URL session 创建的 data task 接受数据 进入内存

## Overview

**For** small interactions with remote servers, you can use the NSURLSessionDataTask class to receive response data into memory (as opposed to using the NSURLSessionDownloadTask class, which stores the data directly to the file system).A data task is **ideal** **for** <u>uses like</u> calling a web service endpoint.

对于小的与远程服务交互，你可以使用 NSURLSessionDataTask 类去接受响应数据进内存。一 data task 对于调用服务节点是理想的

You use a URL session instance to create the task. If your needs are **fairly** simple, you can use the sharedSession instance of the NSURLSession class. If you want to interact with the transfer **through** delegate callbacks, you’ll need to create a session **instead of** using the shared instance. You use a NSURLSessionConfiguration instance when creating a session, **also passing in** a class that implements NSURLSessionDelegate or one of its subprotocols. Sessions can be reused to create multiple tasks, **so fo** each unique configuration you need, create a session and store it as a property.

你使用 URL session 实例去创建 task.如果你的需求简单，你可以使用 NSURLSession 类的共享实例。如果你想与传输交互通过代理回掉，你将需要创建一会话代替使用分享实例。当创建一 session时候，使用 NSURLSessionConfiguration 实例，也可以传入一个实现 NSURLSessionDelegate 或他的子协议的类。Sessions可以被用于创建多个task。所以每个唯一配置创建一个session和存储他作为一个属性
