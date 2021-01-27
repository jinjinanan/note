# git 的使用

## 教程

[git-book](https://git-scm.com/book/zh/v2)
[git教程](http://www.yiibai.com/git/git_push.html)

## git 常用命令

### git 将本地仓库添加到远程

`git remote add origin  你的远程仓库的url`

origin 是你远程仓库的别名
真正的远程仓库是url
origin 是 url 的简称

`git push -u origin master`

-u 参数指定一个默认主机，这样后面就可以不加任何参数使用git push

### git强制推送

`git push origin master -f`

### git 查看远程分支和对应的名称

example

`git remote -v`

返回  远程分支的代称 链接(格式)

```
漫读	http://192.168.6.10:8083/ios/mandu.git (fetch)
漫读	http://192.168.6.10:8083/ios/mandu.git (push)
码云	https://gitee.com/null_788_9135/xs.git (fetch)
码云	https://gitee.com/null_788_9135/xs.git (push)
```

### git 查看历史

`git log`

- --graph 图形化log

example

```
commit 782217b9f731da3e577d7088abcd20e8f0c1643f (HEAD -> dev_chen, 码云/dev_chen)
Author: clb <chenlinbo@example.com>
Date:   Thu Apr 16 10:31:37 2020 +0800

    //暂存

commit d92de13dc4ea10482f5e7505c1e9714f4885e45c
Author: clb <chenlinbo@example.com>
Date:   Thu Apr 16 10:04:15 2020 +0800

    [fix]修改漫画天乩书架不同步

commit 04c89cd5a7a460578a0d85dee09ce7b58e6bae97
Author: clb <chenlinbo@example.com>
Date:   Wed Apr 15 20:33:38 2020 +0800

    [fix]删除bug
```
### git重置到某次提交
1. git 重置上一次提交(一个^)
`git reset --hard HEAD^`
2. git 重置上上一次提交 (两个^^)
`git reset --hard HEAD^^`
3. git 重置之前第100一个提交(HEAD~100)
`git reset --hard HEAD~100`

### git查看状态
`git status`

## 问题

### git无法pull仓库refusing to merge unrelated histories

原因：合并两个不同的开始提交的仓库，git会给出 refusing to merge unrelated histories 的提示
举例：因为刚创建的github的仓库有.gitignore 和License，本体是一个写了东西的仓库。
这个时候remote和local没有一个共同的commit。所以
git不能提交（git认为写错了origin）。这时候需要使用 `--allow-unrelated-histories` 命令。
告诉 git 这两个 repository 确定合并
命令：`git pull origin master --allow-unrelated-histories`
