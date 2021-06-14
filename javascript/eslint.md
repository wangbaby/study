# 禁用eslint 语法校验

在代码顶部添加一行注释, ESLint 在校验的时候就会跳过后面的代码
```
/* eslint-disable */
```

还可以在注释后加入详细规则，这样就能避开指定的校验规则了
```
/* eslint-disable no-new */
```