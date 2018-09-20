# git 的使用

## 教程

[git-book](https://git-scm.com/book/zh/v2)
[git教程](http://www.yiibai.com/git/git_push.html)

## git 的常见问题

### git 将本地仓库添加到远程

`git remote add origin  你的远程仓库的url`

origin 是你远程仓库的别名
真正的远程仓库是url
origin 是 url 的简称

`git push -u origin master`

-u 参数指定一个默认主机，这样后面就可以不加任何参数使用git push

### git强制推送

`git push origin master -f`

### git无法pull仓库refusing to merge unrelated histories

原因：合并两个不同的开始提交的仓库，git会给出 refusing to merge unrelated histories 的提示
举例：因为刚创建的github的仓库有.gitignore 和License，本体是一个写了东西的仓库。
这个时候remote和local没有一个共同的commit。所以
git不能提交（git认为写错了origin）。这时候需要使用 `--allow-unrelated-histories` 命令。
告诉 git 这两个 repository 确定合并
命令：`git pull origin master --allow-unrelated-histories`
