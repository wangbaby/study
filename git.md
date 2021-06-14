# commitId

```
HEAD 当前commit
HEAD^ // HEAD~1 之前一个commit
HEAD~2
```

# git commit

```
// update author
git commit --amend --author="{username} <{email}>"

```

# git config

```
// user
git config --global user.name "wangwang"
git config --global user.email wangwangbupt@163.com

// editor
git config --global core.editor vim

// proxy
git config --global http.https://github.com.proxy socks5://127.0.0.1:8080
git config --global --unset http.https://github.com.proxy

// http
git config --global credential.helper store

// close https
git config --global http.sslverify false

```

# git submodule

```
// 删除子模块
// 1.逆初始化模块，其中{MOD_NAME}为模块目录，执行后可发现模块目录被清空
git submodule deinit {MOD_NAME}
// 2.删除.gitmodules 中记录的模块信息（--cached 选项清除.git/modules 中的缓存）
git rm --cached {MOD_NAME}

// 修改模块 URL
// 1.修改'.gitmodules'文件中对应模块的”url“属性
// 2.使用 git submodule sync 命令，将新的 URL 更新到文件.git/config
git submodule sync
```

# git remote

```
// 查看远程仓库
git remote -v

// 添加新的远程仓库关联, 远程仓库的名称推荐使用默认的名称 origin
git remote add <name> <url>

// 删除远程仓库的关联

git remote remove <name>

// 修改远程仓库的关联 (比如之前你关联的远程仓库使用的协议是 http ，你想将关联的远程仓库的 url 改为 ssh 协议的)
git remote set-url origin https://wangbaby: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@github.com/wangbaby/study.git
```

# git branch

```
// 查看 commit 属于哪个分支
git branch -r --contains COMMIT_ID
```

# git log

```
// 查看某人提交
git log --author=“author”
```

# git push

```
// 删除远程分支
git push origin --delete BRANCH_NAME
```

# git reset

```
git reset {commitId} // 撤销commitId 之前commit, 将之前所有修改 unstage
git reset --soft {commitId} // 撤销commitId 之前commit, 将commitId 之前所有修改staged
git reset --hard {commitId}
```

# git fetch

```
git fetch -all
git fetch origin
git fetch origin master
git fetch origin master:test
```

# git pull

```
git pull origin master
git pull -f origin master:master
```
