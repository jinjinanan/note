# git 的使用

## 教程

[git-book](https://git-scm.com/book/zh/v2)
[git教程](http://www.yiibai.com/git/git_push.html)

## git强制推送

`git push -u origin master -f`

## git 将本地仓库添加到远程

`git remote add origin  你的远程仓库的url`

origin 是你远程仓库的小名
真正的远程仓库是url
origin 是 url 的简称

`git push -u origin master`

-u 参数指定一个默认主机，这样后面就可以不加任何参数使用git push
