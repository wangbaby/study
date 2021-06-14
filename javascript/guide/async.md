# 什么是异步

## JS 为何会有异步

首先记住一句话 —— **JS 是单线程的语言**，所谓“单线程”就是一根筋，对于拿到的程序，一行一行的执行，上面的执行为完成，就傻傻的等着。例如

```javascript
var i,
  t = Date.now();
for (i = 0; i < 100000000; i++) {}
console.log(Date.now() - t); // 250 （chrome浏览器）
```

上面的程序花费 250ms 的时间执行完成，执行过程中就会有卡顿，其他的事儿就先撂一边不管了。

执行程序这样没有问题，但是对于 JS 最初使用的环境 ———— 浏览器客户端 ———— 就不一样了。因此在浏览器端运行的 js ，可能会有大量的网络请求，**而一个网络资源啥时候返回，这个时间是不可预估的。这种情况也要傻傻的等着、卡顿着、啥都不做吗？**———— 那肯定不行。

因此，JS 对于这种场景就设计了异步 ———— 即，发起一个网络请求，就先不管这边了，先干其他事儿，网络请求啥时候返回结果，到时候再说。这样就能保证一个网页的流程运行。

## 异步的实现原理

先看一段比较常见的代码

```javascript
var ajax = $.ajax({
  url: '/data/data1.json',
  success: function () {
    console.log('success');
  },
});
```

上面代码中`$.ajax()`需要传入两个参数进去，`url`和`success`，其中`url`是请求的路由，`success`是一个函数。这个函数传递过去不会立即执行，而是等着请求成功之后才能执行。**对于这种传递过去不执行，等出来结果之后再执行的函数，叫做`callback`，即回调函数**

再看一段更加能说明回调函数的 nodejs 代码。和上面代码基本一样，唯一区别就是：上面代码时网络请求，而下面代码是文件 IO 操作。

```javascript
var fs = require('fs');
fs.readFile('/data/data1.json', (err, data) => {
  console.log(data.toString());
});
```

从上面两个 demo 看来，**实现异步的最核心原理，就是将`callback`作为参数传递给异步执行函数，当有结果返回之后再触发 `callback`执行**，就是如此简单！

## 常用的异步操作

开发中比较常用的异步操作有：

- 网络请求，如`ajax` `http.get`
- IO 操作，如`readFile` `readdir`
- 定时函数，如`setTimeout` `setInterval`

最后，**请思考，事件绑定是不是也是异步操作**？例如`$btn.on('click', function() {...})`。这个问题很有意思，我会再后面的章节经过分析之后给出答案，各位先自己想一下。

# 异步和 event-loop

提到异步，就必须提 event-loop 。event-loop 中文翻译叫做“事件轮询”，它能体现出单线程中异步操作是如何被执行的。

![image](https://imagelx.yidianzixun.com/static/CmcRYl1AI12AFYh5AAJ0lSKwoj4967/87441249.png)

## 举例说明

给出一段简单的 js 代码，并用比较通俗、简单的说法介绍一下执行过程。详细过程还需各位去看视频，因为我没必要把半小时的视频都写到这里。

```javascript
console.log('line 1');
setTimeout(console.log, 1000, 'line 2');
console.log('line 3');
```

以上一共三行代码，该程序被执行的时候，会依次挨行执行

- 第一步，执行第一行，将结果`line 1`打印出来
- 第二步，执行第二行，注意此时会将这个操作暂时存储到其他地方，因为`setTimeout`是一个异步执行操作。
- 第三步，执行第三行，将结果`line 3`打印出出来
- 第四步，等待最后一行程序（一共三行）都全部执行完了，然后立马实时查看刚才暂存的异步操作有没有。如果有可执行的，就立即拿到出来继续执行。
- 第五步，执行完毕之后，再实时查看暂存位置中是否还有未执行的异步回调。

以上只拿了`setTimeout`举例子，但是**对于网络请求、IO 操作、事件绑定道理**都是一样的。

## 思考三个问题

**第一题，以下代码的输出顺序是什么**

```javascript
setTimeout(console.log, 0, 'a');
console.log('b');
console.log('c');
```

答案是`b c a`，有疑问的需要再去看上面的介绍或者那个视频。

**第二题，以下代码中，最后输出的结果是否是 500**

```javascript
var i,
  t = Date.now();
for (i = 0; i < 100000000; i++) {}
function fn() {
  console.log(Date.now() - t); // 输出多少？？？
}
setTimeout(fn, 500);
```

答案是大于 500ms ，因为 for 函数需要花费一些时间，等 for 执行完之后再开始计算 500ms 之后执行 fn

**第三题，事件绑定是不是异步操作？**

这个问题大家根据 event-loop 的讲解和视频来思考，我们下一节再给出解答。

# 事件绑定算不算异步？

事件绑定和异步操作的实现机制是一样的，那么事件绑定是不是就是异步操作呢？（声明一下，这里说的事件绑定是如下代码的形式）

```javascript
$btn.on('click', function (e) {
  console.log('你点击了按钮');
});
```

## 共同之处

从技术实现以及书写方法上来讲，它们是一样的。例如事件绑定和 IO 操作的写法基本相同

```javascript
$btn.on('click', function (e) {
  console.log('你点击了按钮');
});
fs.readFile('data1.json', function (err, data) {
  // 获取数据
});
```

最终执行的方式也基本一样，都会被放在 **callback-queue** 中通过 event-loop 来调用。

## 不同之处

在我看来至少有两处不同。

第一，event-loop 执行时，调用的源不一样。异步操作是系统自动调用，无论是`setTimeout`时间到了还是`$.ajax`请求返回了，系统会自动调用。而事件绑定就需要用户手动触发

第二，从设计上来将，事件绑定有着明显的“**订阅-发布**”的设计模式，而异步操作却没有。

## 我的观点

我个人看代码比较偏重设计，一个东西是什么要看它是为什么而设计的。因此，我倾向于**事件绑定不是异步操作**。虽然它也是通过 event-loop 实现调用的，但是它的设计目的却和异步操作完全不一样。

其实，事件绑定在 js 中扮演着非常重要的角色，各个地方都会用到事件绑定的形式。例如 web 页面监控鼠标、键盘，以及 nodejs 中的 `EventEmitter` 应用非常广泛（特别是涉及到数据流时）。

# jQuery-1.5 之后的 ajax

`$.ajax`这个函数各位应该都比较熟悉了，要完整的讲解 js 的异步操作，就必须先从`$.ajax`这个方法说起。

## 传统的`$.ajax`

先来一段最常见的`$.ajax`的代码，当然是使用万恶的`callback`方式

```javascript
var ajax = $.ajax({
  url: 'data.json',
  success: function () {
    console.log('success');
  },
  error: function () {
    console.log('error');
  },
});

console.log(ajax); // 返回一个 XHR 对象
```

至于这么做会产生什么样子的诟病，我想大家应该都很明白了。不明白的自己私下去查，但是你也可以继续往下看，你只需要记住这样做很不好就是了，要不然 jquery 也不会再后面进行改进

## 1.5 版本之后的`$.ajax`

但是从`v1.5`开始，以上代码就可以这样写了：可以链式的执行`done`或者`fail`方法

```javascript
var ajax = $.ajax('data.json');
ajax
  .done(function () {
    console.log('success 1');
  })
  .fail(function () {
    console.log('error');
  })
  .done(function () {
    console.log('success 2');
  });

console.log(ajax); // 返回一个 deferred 对象
```

大家注意看以上两段代码中都有一个`console.log(ajax)`，但是返回值是完全不一样的。

- `v1.5`之前，返回的是一个`XHR`对象，这个对象不可能有`done`或者`fail`的方法的
- `v1.5`开始，返回一个`deferred`对象，这个对象就带有`done`和`fail`的方法，并且是等着请求返回之后再去调用

## 改进之后的好处

**这是一个标志性的改造，不管这个概念是谁最先提出的，它在 jquery 中首先大量使用并让全球开发者都知道原来 ajax 请求还可以这样写。这为以后的`Promise`标准制定提供了很大意义的参考，你可以以为这就是后面`Promise`的原型。**

记住一句话————**虽然 JS 是异步执行的语言，但是人的思维是同步的**————因此，开发者总是在寻求如何使用逻辑上看似同步的代码来完成 JS 的异步请求。而 jquery 的这一次更新，让开发者在一定程度上得到了这样的好处。

之前无论是什么操作，我都需要一股脑写到`callback`中，现在不用了。现在成功了就写到`done`中，失败了就写到`fail`中，如果成功了有多个步骤的操作，那我就写很多个`done`，然后链式连接起来就 OK 了。

## 和后来的`Promise`的关系

以上的这段代码，我们还可以这样写。即不用`done`和`fail`函数，而是用`then`函数。`then`函数的第一个参数是成功之后执行的函数（即之前的`done`），第二个参数是失败之后执行的函数（即之前的`fail`）。而且`then`函数还可以链式连接。

```javascript
var ajax = $.ajax('data.json');
ajax
  .then(
    function () {
      console.log('success 1');
    },
    function () {
      console.log('error 1');
    }
  )
  .then(
    function () {
      console.log('success 2');
    },
    function () {
      console.log('error 2');
    }
  );
```

如果你对现在 ES6 的`Promise`有了解，应该能看出其中的相似之处。不了解也没关系，你只需要知道它已经和`Promise`比较接近了。后面马上会去讲`Promise`

## 如何实现的？

明眼人都知道，jquery 不可能改变异步操作需要`callback`的本质，它只不过是自己定义了一些特殊的 API，并对异步操作的`callback`进行了封装而已。

那么 jquery 是如何实现这一步的呢？请听下回分解！

# jQuery deferred

上一节讲到 jquery v1.5 版本开始，`$.ajax`可以使用类似当前`Promise`的`then`函数以及链式操作。那么它到底是如何实现的呢？在此之前所用到的`callback`在这其中又起到了什么作用？本节给出答案

## 写一个传统的异步操作

给出一段非常简单的异步操作代码，使用`setTimeout`函数。

```javascript
var wait = function () {
  var task = function () {
    console.log('执行完成');
  };
  setTimeout(task, 2000);
};
wait();
```

以上这些代码执行的结果大家应该都比较明确了，即 2s 之后打印出`执行完成`。**但是我如果再加一个需求 ———— 要在执行完成之后进行某些特别复杂的操作，代码可能会很多，而且分好几个步骤 ———— 那该怎么办？** 大家思考一下！

如果你不看下面的内容，而且目前还没有`Promise`的这个思维，那估计你会说：直接在`task`函数中写就是了！不过相信你看完下面的内容之后，会放弃你现在的想法。

## 使用`$.Deferred`封装

好，接下来我们让刚才简单的几行代码变得更加复杂。**为何要变得更加复杂？是因为让以后更加复杂的地方变得简单**。这里我们使用了 jquery 的`$.Deferred`，至于这个是个什么鬼，大家先不用关心，**只需要知道`$.Deferred()`会返回一个`deferred`对象**，先看代码，`deferred`对象的作用我们后面会说。

```javascript
function waitHandle() {
  var dtd = $.Deferred(); // 创建一个 deferred 对象

  var wait = function (dtd) {
    // 要求传入一个 deferred 对象
    var task = function () {
      console.log('执行完成');
      dtd.resolve(); // 表示异步任务已经完成
    };
    setTimeout(task, 2000);
    return dtd; // 要求返回 deferred 对象
  };

  // 注意，这里一定要有返回值
  return wait(dtd);
}
```

以上代码中，又使用一个`waitHandle`方法对`wait`方法进行再次的封装。`waitHandle`内部代码，我们分步骤来分析.

- 使用`var dtd = $.Deferred()`创建`deferred`对象。通过上一节我们知道，一个`deferred`对象会有`done` `fail`和`then`方法
- 重新定义`wait`函数，但是：第一，要传入一个`deferred`对象（`dtd`参数）；第二，当`task`函数（即`callback`）执行完成之后，要执行`dtd.resolve()`告诉传入的`deferred`对象，革命已经成功。第三；将这个`deferred`对象返回。
- 返回`wait(dtd)`的执行结果。因为`wait`函数中返回的是一个`deferred`对象（`dtd`参数），因此`wait(dtd)`返回的就是`dtd`————如果你感觉这里很乱，没关系，慢慢捋，一行一行看，相信两三分钟就能捋顺！

最后总结一下，`waitHandle`函数最终`return wait(dtd)`即最终返回`dtd`（一个`deferred`）对象。针对一个`deferred`对象，它有`done` `fail`和`then`方法（上一节说过），它还有`resolve()`方法（其实和`resolve`相对的还有一个`reject`方法，后面会提到）

## 应用`then`方法

接着上面的代码继续写

```javascript
var w = waitHandle();
w.then(
  function () {
    console.log('ok 1');
  },
  function () {
    console.log('err 1');
  }
).then(
  function () {
    console.log('ok 2');
  },
  function () {
    console.log('err 2');
  }
);
```

上面已经说过，`waitHandle`函数最终返回一个`deferred`对象，而`deferred`对象具有`done` `fail` `then`方法

执行这段代码，我们打印出来以下结果。可以将结果对标以下代码时哪一行。

```
执行完成
ok 1
ok 2
```

此时，你再回头想想我刚才说提出的需求（_要在执行完成之后进行某些特别复杂的操作，代码可能会很多，而且分好几个步骤_），是不是有更好的解决方案了？

- `dtd.resolve()` 表示革命已经成功，会触发`then`中第一个参数（函数）的执行，
- `dtd.reject()` 表示革命失败了，会触发`then`中第二个参数（函数）执行

## 有什么问题？

总结一下一个`deferred`对象具有的函数属性，并分为两组：

- `dtd.resolve` `dtd.reject`
- `dtd.then` `dtd.done` `dtd.fail`

我为何要分成两组 ———— **这两组函数，从设计到执行之后的效果是完全不一样的。第一组是主动触发用来改变状态（成功或者失败），第二组是状态变化之后才会触发的监听函数。**

既然是完全不同的两组函数，就应该彻底的分开，否则很容易出现问题。例如，你在刚才执行代码的最后加上这么一行试试。

```javascript
w.reject();
```

# jQuery promise

## 返回`promise`

我们对上一节的的代码做一点小小的改动，只改动了一行，下面注释。

```javascript
function waitHandle() {
  let dtd = $.Deferred();

  let wait = function (dtd) {
    let task = function () {
      console.log('done');
      dtd.resolve();
    };
    setTimeout(task, 2000);
    return dtd.promise();
  };

  return wait(dtd);
}

const w = waitHandle();
w.then(
  () => {
    console.log('suc 1');
  },
  () => {
    console.log('err 1');
  }
).then(
  () => {
    console.log('suc 2');
  },
  () => {
    console.log('err 2');
  }
);
```

改动的一行在这里`return dtd.promise()`，之前是`return dtd`。`dtd`是一个`deferred`对象，而`dtd.promise`就是一个`promise`对象。

`promise`对象和`deferred`对象最重要的区别，记住了————**`promise`对象相比于`deferred`对象，缺少了`.resolve`和`.reject`这俩函数属性**。这么一来，可就完全不一样了。

上一节我们提到一个问题，就是在程序的最后一行加一句`w.reject()`会导致乱套，你现在再在最后一行加`w.reject()`试试 ———— 保证乱套不了 ———— 而是你的程序不能执行，直接报错。因为，`w`是`promise`对象，不具备`.reject`属性。

## 返回`promise`的好处

上一节提到`deferred`对象有两组属性函数，而且提到应该把这两组彻底分开。现在通过上面一行代码的改动，就分开了。

- `waitHandle`函数内部，使用`dtd.resolve()`来该表状态，做主动的修改操作
- `waitHandle`最终返回`promise`对象，只能去被动监听变化（`then`函数），而不能去主动修改操作

**一个“主动”一个“被动”，完全分开了。**

## promise 的概念

**无论 jQuery 里面的`deferred`和`promise`这个概念和想法最早是哪位提出来的，但是最早展示给全世界开发者的是 jquery ，这算是`Promise`这一概念最先的提出者。**

其实本次课程主要是给大家分析 ES6 的`Promise` `Generator`和`async-await`，但是为何要从 jquery 开始（大家现在用 jquery 越来越少）？就是要给大家展示一下这段历史的一些起点和发展的知识。有了这些基础，你再去接受最新的概念会非常容易，因为所有的东西都是从最初顺其自然发展进化而来的，我们要去用一个发展进化的眼光学习知识，而不是死记硬背。

## Promise 加入 ES6 标准

从 jQuery v1.5 发布经过若干时间之后，Promise 终于出现在了 ES6 的标准中，而当下 ES6 也正在被大规模使用。

## 写一段传统的异步操作

还是拿之前讲 jQuery `deferred`对象时的那段`setTimeout`程序

```javascript
var wait = function () {
  var task = function () {
    console.log('执行完成');
  };
  setTimeout(task, 2000);
};
wait();
```

之前我们使用 jQuery 封装的，接下来将使用 ES6 的`Promise`进行封装，大家注意看有何不同。

## 用`Promise`进行封装

```javascript
const wait = function () {
  // 定义一个 promise 对象
  const promise = new Promise((resolve, reject) => {
    // 将之前的异步操作，包括到这个 new Promise 函数之内
    const task = function () {
      console.log('执行完成');
      resolve(); // callback 中去执行 resolve 或者 reject
    };
    setTimeout(task, 2000);
  });
  // 返回 promise 对象
  return promise;
};
```

注意看看程序中的注释，那都是重点部分。从整体看来，感觉这次比用 jQuery 那次简单一些，逻辑上也更加清晰一些。

- 将之前的异步操作那几行程序，用`new Promise((resolve,reject) => {.....})`包装起来，最后`return`即可
- 异步操作的内部，在`callback`中执行`resolve()`（表明成功了，失败的话执行`reject`）

接着上面的程序继续往下写。`wait()`返回的肯定是一个`promise`对象，而`promise`对象有`then`属性。

```javascript
const w = wait();
w.then(
  () => {
    console.log('ok 1');
  },
  () => {
    console.log('err 1');
  }
).then(
  () => {
    console.log('ok 2');
  },
  () => {
    console.log('err 2');
  }
);
```

`then`还是和之前一样，接收两个参数（函数），第一个在成功时（触发`resolve`）执行，第二个在失败时(触发`reject`)时执行。而且，`then`还可以进行链式操作。

以上就是 ES6 的`Promise`的基本使用演示。看完你可能会觉得，这跟之前讲述 jQuery 的差不多 ———— 对了，这就是我要在之前先讲 jquery 的原因，让你感觉一篇一篇看起来如丝般顺滑！

接下来，将详细说一下 ES6 `Promise` 的一些比较常见的用法，敬请期待吧！

# Promise 在 ES6 中的具体应用

## 准备工作

因为以下所有的代码都会用到`Promise`，因此干脆在所有介绍之前，先封装一个`Promise`，**封装一次，为下面多次应用**。

```javascript
const fs = require('fs');
const path = require('path'); // 后面获取文件路径时候会用到
const readFilePromise = function (fileName) {
  return new Promise((resolve, reject) => {
    fs.readFile(fileName, (err, data) => {
      if (err) {
        reject(err); // 注意，这里执行 reject 是传递了参数，后面会有地方接收到这个参数
      } else {
        resolve(data.toString()); // 注意，这里执行 resolve 时传递了参数，后面会有地方接收到这个参数
      }
    });
  });
};
```

## 参数传递

我们要使用上面封装的`readFilePromise`读取一个 json 文件`../data/data2.json`，这个文件内容非常简单：`{"a":100, "b":200}`

先将文件内容打印出来，代码如下。大家需要注意，`readFilePromise`函数中，执行`resolve(data.toString())`传递的参数内容，会被下面代码中的`data`参数所接收到。

```javascript
const fullFileName = path.resolve(__dirname, '../data/data2.json');
const result = readFilePromise(fullFileName);
result.then((data) => {
  console.log(data);
});
```

再加一个需求，在打印出文件内容之后，我还想看看`a`属性的值，代码如下。之前我们已经知道`then`可以执行链式操作，如果`then`有多步骤的操作，那么前面步骤`return`的值会被当做参数传递给后面步骤的函数，如下面代码中的`a`就接收到了`return JSON.parse(data).a`的值

```javascript
const fullFileName = path.resolve(__dirname, '../data/data2.json');
const result = readFilePromise(fullFileName);
result
  .then((data) => {
    // 第一步操作
    console.log(data);
    return JSON.parse(data).a; // 这里将 a 属性的值 return
  })
  .then((a) => {
    // 第二步操作
    console.log(a); // 这里可以获取上一步 return 过来的值
  });
```

总结一下，这一段内容提到的“参数传递”其实有两个方面：

- 执行`resolve`传递的值，会被第一个`then`处理时接收到
- 如果`then`有链式操作，前面步骤返回的值，会被后面的步骤获取到

## 异常捕获

我们知道`then`会接收两个参数（函数），第一个参数会在执行`resolve`之后触发（还能传递参数），第二个参数会在执行`reject`之后触发（其实也可以传递参数，和`resolve`传递参数一样），但是上面的例子中，**我们没有用到`then`的第二个参数。这是为何呢 ———— 因为不建议这么用**。

对于`Promise`中的异常处理，我们建议用`catch`方法，而不是`then`的第二个参数。请看下面的代码，以及注释。

```javascript
const fullFileName = path.resolve(__dirname, '../data/data2.json');
const result = readFilePromise(fullFileName);
result
  .then((data) => {
    console.log(data);
    return JSON.parse(data).a;
  })
  .then((a) => {
    console.log(a);
  })
  .catch((err) => {
    console.log(err.stack); // 这里的 catch 就能捕获 readFilePromise 中触发的 reject ，而且能接收 reject 传递的参数
  });
```

在若干个`then`串联之后，我们一般会在最后跟一个`.catch`来捕获异常，而且执行`reject`时传递的参数也会在`catch`中获取到。这样做的好处是：

- 让程序看起来更加简洁，是一个串联的关系，没有分支（如果用`then`的两个参数，就会出现分支，影响阅读）
- 看起来更像是`try - catch`的样子，更易理解

## 串联多个异步操作

如果现在有一个需求：先读取`data2.json`的内容，当成功之后，再去读取`data1.json`。这样的需求，如果用传统的`callback`去实现，会变得很麻烦。而且，现在只是两个文件，如果是十几个文件这样做，写出来的代码就没法看了（臭名昭著的`callback-hell`）。但是用刚刚学到的`Promise`就可以轻松胜任这项工作

```javascript
const fullFileName2 = path.resolve(__dirname, '../data/data2.json');
const result2 = readFilePromise(fullFileName2);
const fullFileName1 = path.resolve(__dirname, '../data/data1.json');
const result1 = readFilePromise(fullFileName1);

result2
  .then((data) => {
    console.log('data2.json', data);
    return result1; // 此处只需返回读取 data1.json 的 Promise 即可
  })
  .then((data) => {
    console.log('data1.json', data); // data 即可接收到 data1.json 的内容
  });
```

上文“参数传递”提到过，如果`then`有链式操作，前面步骤返回的值，会被后面的步骤获取到。**但是，如果前面步骤返回值是一个`Promise`的话，情况就不一样了 ———— 如果前面返回的是`Promise`对象，后面的`then`将会被当做这个返回的`Promise`的第一个`then`来对待** ———— 如果你这句话看不懂，你需要将“参数传递”的示例代码和这里的示例代码联合起来对比着看，然后体会这句话的意思。

## `Promise.all`和`Promise.race`的应用

我还得继续提出更加奇葩的需求，以演示`Promise`的各个常用功能。如下需求：

读取两个文件`data1.json`和`data2.json`，现在我需要一起读取这两个文件，等待它们全部都被读取完，再做下一步的操作。此时需要用到`Promise.all`

```javascript
// Promise.all 接收一个包含多个 promise 对象的数组
Promise.all([result1, result2]).then((datas) => {
  // 接收到的 datas 是一个数组，依次包含了多个 promise 返回的内容
  console.log(datas[0]);
  console.log(datas[1]);
});
```

读取两个文件`data1.json`和`data2.json`，现在我需要一起读取这两个文件，但是只要有一个已经读取了，就可以进行下一步的操作。此时需要用到`Promise.race`

```javascript
// Promise.race 接收一个包含多个 promise 对象的数组
Promise.race([result1, result2]).then((data) => {
  // data 即最先执行完成的 promise 的返回值
  console.log(data);
});
```

## `Promise.resolve`的应用

从 jquery 引出，到此即将介绍完 ES6 的`Promise`，现在我们再回归到 jquery 。

大家都是到 jquery v1.5 之后`$.ajax()`返回的是一个`deferred`对象，而这个`deferred`对象和我们现在正在学习的`Promise`对象已经很接近了，但是还不一样。那么 ———— `deferred`对象能否转换成 ES6 的`Promise`对象来使用？？

答案是能！需要使用`Promise.resolve`来实现这一功能，请看以下代码：

```javascript
// 在浏览器环境下运行，而非 node 环境
const jsPromise = Promise.resolve($.ajax('/whatever.json'));
jsPromise.then((data) => {
  // ...
});
```

实际上，并不是`Promise.resolve`对 jquery 的`deferred`对象做了特殊处理，**而是`Promise.resolve`能够将`thenable`对象转换为`Promise`对象**。什么是`thenable`对象？———— 看个例子

```javascript
// 定义一个 thenable 对象
const thenable = {
  // 所谓 thenable 对象，就是具有 then 属性，而且属性值是如下格式函数的对象
  then: (resolve, reject) => {
    resolve(200);
  },
};

// thenable 对象可以转换为 Promise 对象
const promise = Promise.resolve(thenable);
promise.then((data) => {
  // ...
});
```

其实，在我们的日常开发中，这种将`thenable`转换为`Promise`的需求并不多。**真正需要的是，将一些异步操作函数（如`fs.readFile`）转换为`Promise`**（就像文章一开始`readFilePromise`做的那样）。这块，我们后面会在介绍`Q.js`库时，告诉大家一个简单的方法。

## 其他

**你只会使用却上升不到理论高度，永远都是个搬砖的，搬一块砖挣一毛钱，不搬就不挣钱！ 在我看来，所有的知识应该都需要上升到理论高度，将实际应用和标准对接，知道真正的出处，才能走的长远。**

下一节我们介绍 Promise/A+ 规范

# 对标一下 Promise/A+ 规范

**Promise/A 是由 CommonJS 组织制定的异步模式编程规范，后来又经过一些升级，就是当前的 Promise/A+ 规范。上一节讲述的`Promise`的一些功能实现，就是根据这个规范来的。**

## 介绍规范的核心内容

**关于状态**

- promise 可能有三种状态：等待（pending）、已完成（fulfilled）、已拒绝（rejected）
- promise 的状态只可能从“等待”转到“完成”态或者“拒绝”态，不能逆向转换，同时“完成”态和“拒绝”态不能相互转换

**关于`then`方法**

- promise 必须实现`then`方法，而且`then`必须返回一个 promise ，同一个 promise 的`then`可以调用多次（链式），并且回调的执行顺序跟它们被定义时的顺序一致
- `then`方法接受两个参数，第一个参数是成功时的回调，在 promise 由“等待”态转换到“完成”态时调用，另一个是失败时的回调，在 promise 由“等待”态转换到“拒绝”态时调用

## 状态变化

> promise 可能有三种状态：等待（pending）、已完成（fulfilled）、已拒绝（rejected）

拿到上一节的`readFilePromise`函数，然后执行`const result = readFilePromise(someFileName)`会得到一个`Promise`对象。

- 刚刚创建时，就是 等待（pending）状态
- 如果读取文件成功了，`readFilePromise`函数内部的`callback`中会自定调用`resolve()`，这样就变为 已完成（fulfilled）状态
- 如果很不幸读取文件失败了（例如文件名写错了，找不到文件），`readFilePromise`函数内部的`callback`中会自定调用`reject()`，这样就变为 已拒绝（rejeced）状态

> promise 的状态只可能从“等待”转到“完成”态或者“拒绝”态，不能逆向转换，同时“完成”态和“拒绝”态不能相互转换

## `then`方法

> promise 必须实现`then`方法，而且`then`必须返回一个 promise ，同一个 promise 的`then`可以调用多次（链式），并且回调的执行顺序跟它们被定义时的顺序一致

- `promise`对象必须实现`then`方法这个无需解释，没有`then`那就不叫`promise`
- “而且`then`必须返回一个`promise`，同一个 promise 的`then`可以调用多次（链式）” ———— 这两句话说明了一个意思 ———— `then`肯定要再返回一个`promise`，要不然`then`后面怎么能再链式的跟一个`then`呢？

> `then`方法接受两个参数，第一个参数是成功时的回调，在 promise 由“等待”态转换到“完成”态时调用，另一个是失败时的回调，在 promise 由“等待”态转换到“拒绝”态时调用

# Promise 真的取代 callback 了吗

Promise 虽然改变了 JS 工程师对于异步操作的写法，但是却改变不了 JS 单线程、异步的执行模式。

## JS 异步的本质

从最初的 ES3、4 到 ES5 再到现在的 ES6 和即将到来的 ES7，语法标准上更新很多，但是 JS 这种单线程、异步的本质是没有改变的。nodejs 中读取文件的代码一直都可以这样写

```javascript
fs.readFile('some.json', (err, data) => {});
```

**既然异步这个本质不能改变，伴随异步在一起的永远都会有`callback`，因为没有`callback`就无法实现异步。因此`callback`永远存在。**

## Promise 只是表面的写法上的改变

JS 工程师不会讨厌 JS 异步的本质，但是很讨厌 JS 异步操作中`callback`的书写方式，特别是遇到万恶的`callback-hell`（嵌套`callback`）时。

计算机的抽象思维和人的具象思维是完全不一样的，人永远喜欢看起来更加符合逻辑、更加易于阅读的程序，因此现在特别强调代码可读性。而`Promise`就是一种代码可读性的变化。大家感受一下这两种不同（**这其中还包括异常处理，加上异常处理会更加复杂**）

第一种，传统的`callback`方式

```javascript
fs.readFile('some1.json', (err, data) => {
  fs.readFile('some2.json', (err, data) => {
    fs.readFile('some3.json', (err, data) => {
      fs.readFile('some4.json', (err, data) => {});
    });
  });
});
```

第二种，`Promise`方式

```javascript
readFilePromise('some1.json')
  .then((data) => {
    return readFilePromise('some2.json');
  })
  .then((data) => {
    return readFilePromise('some3.json');
  })
  .then((data) => {
    return readFilePromise('some4.json');
  });
```

这两种方式对于代码可读性的对比，非常明显。**但是最后再次强调，`Promise`只是对于异步操作代码可读性的一种变化，它并没有改变 JS 异步执行的本质，也没有改变 JS 中存在`callback`的现象**。

## Promise 中不能缺少 callback

上文已经基本给出了上一节提问的答案，但是这里还需要再加一个补充：`Promise`不仅仅是没有取代`callback`或者弃而不用，反而`Promise`中要使用到`callback`。因为，JS 异步执行的本质，必须有`callback`存在，否则无法实现。

再次粘贴处之前章节的封装好的一个`Promise`函数（进行了一点点简化）

```javascript
const readFilePromise = function (fileName) {
  return new Promise((resolve, reject) => {
    fs.readFile(fileName, (err, data) => {
      resolve(data.toString());
    });
  });
};
```

上面的代码中，`promise`对象的状态要从`pending`变化为`fulfilled`，就需要去执行`resolve()`函数。那么是从哪里执行的 ———— **还得从`callback`中执行`resolve`函数 ———— 这就是`Promise`也需要`callback`的最直接体现**。

## 接下来...

一块技术“火”的程度和第三方开源软件的数量、质量以及使用情况有很大的正比关系。例如为了简化 DOM 操作，jquery 风靡全世界。Promise 用的比较多，第三方库当然就必不可少，它们极大程度的简化了 Promise 的代码。

接下来我们一起看看`Q.js`这个库的使用，学会了它，将极大程度提高你写 Promise 的效率。

# 使用 Q.js 库

如果实际项目中使用`Promise`，还是强烈建议使用比较靠谱的第三方插件，会极大增加你的开发效率。除了将要介绍的`Q.js`，还有`bluebird`也推荐使用，去 github 自行搜索吧。

另外，使用第三方库不仅仅是提高效率，**它还让你在浏览器端（不支持`Promise`的环境中）使用`promise`**。

## 下载和安装

可以直接去它的 [github 地址](https://github.com/kriskowal/q) （近 1.3W 的 star 数量说明其用户群很大）查看文档。

如果项目使用 CommonJS 规范直接 `npm i q --save`，如果是网页外链可寻找可用的 cdn 地址，或者干脆下载到本地。

以下我将要演示的代码，都是使用 CommonJS 规范的，因此我要演示代码之前加上引用，以后的代码演示就不重复加了。

```javascript
const Q = require('q');
```

## 使用`Q.nfcall`和`Q.nfapply`

`Q.nfcall`就是使用`call`的语法来返回一个`promise`对象，例如

```javascript
const fullFileName = path.resolve(__dirname, '../data/data1.json');
const result = Q.nfcall(fs.readFile, fullFileName, 'utf-8'); // 使用 Q.nfcall 返回一个 promise
result
  .then((data) => {
    console.log(data);
  })
  .catch((err) => {
    console.log(err.stack);
  });
```

`Q.nfapply`就是使用`apply`的语法返回一个`promise`对象，例如

```javascript
const fullFileName = path.resolve(__dirname, '../data/data1.json');
const result = Q.nfapply(fs.readFile, [fullFileName, 'utf-8']); // 使用 Q.nfapply 返回一个 promise
result
  .then((data) => {
    console.log(data);
  })
  .catch((err) => {
    console.log(err.stack);
  });
```

怎么样，体验了一把，是不是比直接自己写`Promise`简单多了？

## 使用`Q.defer`

`Q.defer`算是一个比较偏底层一点的 API ，用于自己定义一个`promise`生成器，如果你需要在浏览器端编写，而且浏览器不支持`Promise`，这个就有用处了。

```javascript
function readFile(fileName) {
  const defer = Q.defer();
  fs.readFile(fileName, (err, data) => {
    if (err) {
      defer.reject(err);
    } else {
      defer.resolve(data.toString());
    }
  });
  return defer.promise;
}
readFile('data1.json')
  .then((data) => {
    console.log(data);
  })
  .catch((err) => {
    console.log(err.stack);
  });
```

## 使用`Q.denodeify`

我们在很早之前的一节中自己封装了一个`fs.readFile`的`promise`生成器，这里再次回顾一下

```javascript
const readFilePromise = function (fileName) {
  return new Promise((resolve, reject) => {
    fs.readFile(fileName, (err, data) => {
      if (err) {
        reject(err);
      } else {
        resolve(data.toString());
      }
    });
  });
};
```

虽然看着不麻烦，但是还是需要很多行代码来实现，如果使用`Q.denodeify`，一行代码就搞定了！

```javascript
const readFilePromise = Q.denodeify(fs.readFile);
```

`Q.denodeify`就是一键将`fs.readFile`这种有回调函数作为参数的异步操作封装成一个`promise`生成器，非常方便！

## 使用`Q.all`和`Q.any`

这两个其实就是对应了之前讲过的`Promise.all`和`Promise.race`，而且应用起来一模一样，不多赘述。

```javascript
const r1 = Q.nfcall(fs.readFile, 'data1.json', 'utf-8');
const r2 = Q.nfcall(fs.readFile, 'data2.json', 'utf-8');
Q.all([r1, r2])
  .then((arr) => {
    console.log(arr);
  })
  .catch((err) => {
    console.log(err);
  });
```

## 使用`Q.delay`

`Q.delay`，顾名思义，就是延迟的意思。例如，读取一个文件成功之后，再过五秒钟之后，再去做 xxxx。这个如果是自己写的话，也挺费劲的，但是`Q.delay`就直接给我们分装好了。

```javascript
const result = Q.nfcall(fs.readFile, 'data1.json', 'utf-8');
result
  .delay(5000)
  .then((data) => {
    // 得到结果
    console.log(data.toString());
  })
  .catch((err) => {
    // 捕获错误
    console.log(err.stack);
  });
```

# ES6 中的 Generator

**在 ES6 出现之前，基本都是各式各样类似`Promise`的解决方案来处理异步操作的代码逻辑，但是 ES6 的`Generator`却给异步操作又提供了新的思路，马上就有人给出了如何用`Generator`来更加优雅的处理异步操作。**

## `Generator`简介

先来一段最基础的`Generator`代码

```javascript
function* Hello() {
  yield 100;
  yield (function () {
    return 200;
  })();
  return 300;
}

var h = Hello();
console.log(typeof h); // object

console.log(h.next()); // { value: 100, done: false }
console.log(h.next()); // { value: 200, done: false }
console.log(h.next()); // { value: 300, done: true }
console.log(h.next()); // { value: undefined, done: true }
```

- 定义`Generator`时，需要使用`function*`，其他的和定义函数一样。内部使用`yield`，至于`yield`的用处以后再说
- 执行`var h = Hello()`生成一个`Generator`对象，经验验证`typeof h`发现不是普通的函数
- 执行`Hello()`之后，`Hello`内部的代码不会立即执行，而是出于一个**暂停**状态
- 执行第一个`h.next()`时，会激活刚才的暂停状态，开始执行`Hello`内部的语句，但是，直到遇到`yield`语句。一旦遇到`yield`语句时，它就会将`yield`后面的表达式执行，并返回执行的结果，然后又立即进入**暂停**状态。
- 因此第一个`console.log(h.next())`打印出来的是`{ value: 100, done: false }`，`value`是第一个`yield`返回的值，`done: false`表示目前处于暂停状态，尚未执行结束，还可以再继续往下执行。
- 执行第二个`h.next()`和第一个一样，不在赘述。此时会执行完第二个`yield`后面的表达式并返回结果，然后再次进入**暂停**状态
- 执行第三个`h.next()`时，程序会打破暂停状态，继续往下执行，但是遇到的不是`yield`而是`return`。这就预示着，即将执行结束了。因此最后返回的是`{ value: 300, done: true }`，`done: true`表示执行结束，无法再继续往下执行了。
- 再去执行第四次`h.next()`时，就只能得到`{ value: undefined, done: true }`，因为已经结束，没有返回值了。

以下几个要点：

- `Generator`不是函数，不是函数，不是函数
- `Hello()`不会立即出发执行，而是一上来就暂停
- 每次`h.next()`都会打破暂停状态去执行，直到遇到下一个`yield`或者`return`
- 遇到`yield`时，会执行`yeild`后面的表达式，并返回执行之后的值，然后再次进入暂停状态，此时`done: false`。
- 遇到`return`时，会返回值，执行结束，即`done: true`
- 每次`h.next()`的返回值永远都是`{value: ... , done: ...}`的形式

## `Generator`最终如何处理异步操作

上面只是一个最基本最简单的介绍，但是我们看不到任何与异步操作相关的事情，那我们接下来就先展示一下最终我们将使用`Generator`如何做异步操作。

之前讲解`Promise`时候，依次读取多个文件，我们是这么操作的（看不明白的需要回炉重造哈），主要是使用`then`做链式操作。

```javascript
readFilePromise('some1.json')
  .then((data) => {
    console.log(data); // 打印第 1 个文件内容
    return readFilePromise('some2.json');
  })
  .then((data) => {
    console.log(data); // 打印第 2 个文件内容
    return readFilePromise('some3.json');
  })
  .then((data) => {
    console.log(data); // 打印第 3 个文件内容
    return readFilePromise('some4.json');
  })
  .then((data) => {
    console.log(data); // 打印第 4 个文件内容
  });
```

而如果学会`Generator`那么读取多个文件就是如下这样写。先不要管如何实现的，光看一看代码，你就能比较出哪个更加简洁、更加易读、更加所谓的优雅！

```javascript
co(function* () {
  const r1 = yield readFilePromise('some1.json');
  console.log(r1); // 打印第 1 个文件内容
  const r2 = yield readFilePromise('some2.json');
  console.log(r2); // 打印第 2 个文件内容
  const r3 = yield readFilePromise('some3.json');
  console.log(r3); // 打印第 3 个文件内容
  const r4 = yield readFilePromise('some4.json');
  console.log(r4); // 打印第 4 个文件内容
});
```

## 接下来...

接下来我们不会立刻讲解如何使用`Generator`做异步操作，而是看一看`Generator`是一个什么东西！说来话长，这要从 ES6 的另一个概念`Iterator`说起。

# Iterator 遍历器

ES6 中引入了很多此前没有但是却非常重要的概念，`Iterator`就是其中一个。**`Iterator`对象是一个指针对象，实现类似于单项链表的数据结构，通过`next()`将指针指向下一个节点**

## 简介`Symbol`数据类型

`Symbol`是一个特殊的数据类型，和`number` `string`等并列，

```javascript
console.log(Array.prototype.slice); // [Function: slice]
console.log(Array.prototype[Symbol.iterator]); // [Function: values]
```

数组的`slice`属性大家都比较熟悉了，就是一个函数，可以通过`Array.prototype.slice`得到。这里的`slice`是一个字符串，但是我们获取`Array.prototype[Symbol.iterator]`可以得到一个函数，只不过这里的`[Symbol.iterator]`是`Symbol`数据类型，不是字符串。但是没关系，**`Symbol`数据类型也可以作为对象属性的`key`**。如下：

```javascript
var obj = {};
obj.a = 100;
obj[Symbol.iterator] = 200;
console.log(obj); // {a: 100, Symbol(Symbol.iterator): 200}
```

在此小节中，你只需要知道`[Symbol.iterator]`是一个特殊的数据类型`Symbol`类型，但是也可以像`number` `string`类型一样，作为对象的属性`key`来使用

## 原生具有`[Symbol.iterator]`属性的数据类型

原生具有`[Symbol.iterator]`属性数据类型有：数组、某些类似数组的对象（如`arguments`、`NodeList`）、`Set`和`Map`。其中，`Set`和`Map`也是 ES6 中新增的数据类型。

```javascript
// 数组
console.log([1, 2, 3][Symbol.iterator]); // function values() { [native code] }
// 某些类似数组的对象，NoeList
console.log(document.getElementsByTagName('div')[Symbol.iterator]); // function values() { [native code] }
```

原生具有`[Symbol.iterator]`属性数据类型有一个特点，就是可以使用`for...of`来取值，例如

```javascript
var item;
for (item of [100, 200, 300]) {
  console.log(item);
}
// 打印出：100 200 300
// 注意，这里每次获取的 item 是数组的 value，而不是 index ，这一点和 传统 for 循环以及 for...in 完全不一样
```

而具有`[Symbol.iterator]`属性的对象，都可以一键生成一个`Iterator`对象。如何生成以及生成之后什么样子，还有生成之后的作用，下文分解。

## 生成`Iterator`对象

定义一个数组，然后生成数组的`Iterator`对象

```javascript
const arr = [100, 200, 300];
const iterator = arr[Symbol.iterator](); // 通过执行 [Symbol.iterator] 的属性值（函数）来返回一个 iterator 对象
```

好，现在生成了`iterator`，那么该如何使用它呢 ———— 有两种方式：`next`和`for...of`。

先说第一种，`next`

```javascript
console.log(iterator.next()); // { value: 100, done: false }
console.log(iterator.next()); // { value: 200, done: false }
console.log(iterator.next()); // { value: 300, done: false }
console.log(iterator.next()); // { value: undefined, done: true }
```

看到这里，再结合上一节内容，是不是似曾相识的感觉？(额，没有的话，那你就回去重新看上一节的内容吧) **`iterator`对象可以通过`next()`方法逐步获取每个元素的值，以`{ value: ..., done: ... }`形式返回，`value`就是值，`done`表示是否到已经获取完成。**

再说第二种，`for...of`

```javascript
let i;
for (i of iterator) {
  console.log(i);
}
// 打印：100 200 300
```

上面使用`for...of`遍历`iterator`对象，可以直接将其值获取出来。这里的“值”就对应着上面`next()`返回的结果的`value`属性

## `Generator`返回的也是`Iterator`对象

看到这里，你大体也应该明白了，上一节演示的`Generator`，就是生成一个`Iterator`对象。因此才会有`next()`，也可以通过`for...of`来遍历。拿出上一节的例子再做一次演示：

```javascript
function* Hello() {
  yield 100;
  yield (function () {
    return 200;
  })();
  return 300;
}
const h = Hello();
console.log(h[Symbol.iterator]); // [Function: [Symbol.iterator]]
```

执行`const h = Hello()`得到的就是一个`iterator`对象，因为`h[Symbol.iterator]`是有值的。既然是`iterator`对象，那么就可以使用`next()`和`for...of`进行操作

```javascript
console.log(h.next()); // { value: 100, done: false }
console.log(h.next()); // { value: 200, done: false }
console.log(h.next()); // { value: 300, done: false }
console.log(h.next()); // { value: undefined, done: true }

let i;
for (i of h) {
  console.log(i);
}
```

## 接下来...

这一节我们花费很大力气，从`Iterator`又回归到了`Generator`，目的就是为了看看`Generator`到底是一个什么东西。了解其本质，才能更好的使用它，否则总有一种抓瞎的感觉。

接下来我们就`Generator`具体有哪些使用场景。

# Generator 的本质是什么？是否取代了 callback

**其实标题中的问题，是一个伪命题，因为`Generator`和`callback`根本没有任何关系，只是我们通过一些方式（而且是很复杂的方式）强行将他俩产生了关系，才会有现在的`Generator`处理异步。**

## `Generator`的本质

介绍`Generator`的[第一节](./01-generator-in-es6.md)中，多次提到 **暂停** 这个词 ———— **“暂停”才是`Generator`的本质** ———— 只有`Generator`能让一段程序执行到指定的位置先暂停，然后再启动，再暂停，再启动。

而这个 **暂停** 就很容易让它和异步操作产生联系，因为我们在处理异步操作时，即需要一种“开始读取文件，然后**暂停**一下，等着文件读取完了，再干嘛干嘛...”这样的需求。因此将`Generator`和异步操作联系在一起，并且产生一些比较简明的解决方案，这是顺其自然的事儿，大家要想明白这个道理。

不过，**JS 还是 JS，单线程还是单线程，异步还是异步，`callback`还是`callback`。这一切都不会因为有一个`Generator`而有任何变化**。

## 和`callback`的结合

之前在介绍`Promise`的最后，拿`Promise`和`callback`做过一些比较，最后发现`Promise`其实是利用了`callback`才能实现的。而这里，**`Generator`也必须利用`callback`才能实现**。

拿介绍`co`时的代码举例（代码如下），如果`yield`后面用的是`thunk`函数，那么`thunk`函数需要的就是一个`callback`参数。如果`yield`后面用的是`Promise`对象，`Promise`和`callback`的联系之前已经介绍过了。

```javascript
co(function* () {
  const r1 = yield readFilePromise('some1.json');
  console.log(r1); // 打印第 1 个文件内容
  const r2 = yield readFileThunk('some2.json');
  console.log(r2); // 打印第 2 个文件内容
});
```

因此，`Generator`离不开`callback`，`Promise`离不开`callback`，异步也离不开`callback`。

# Thunk 函数

要想让`Generator`和异步操作产生联系，就必须过`thunk`函数这一关。这一关过了之后，立即就可以着手异步操作的事情，因此大家再坚持坚持。至于`thunk`函数是什么，下文会详细演示。

## 一个普通的异步函数

就用 nodejs 中读取文件的函数为例，通常都这么写

```javascript
fs.readFile('data1.json', 'utf-8', (err, data) => {
  // 获取文件内容
});
```

其实这个写法就是将三个参数都传递给`fs.readFile`这个方法，其中最后一个参数是一个`callback`函数。这种函数叫做 **多参数函数**，我们接下来做一个改造

## 封装成一个`thunk`函数

改造的代码如下所示。不过是不是感觉越改造越复杂了？不过请相信：你看到的复杂仅仅是表面的，**这一点东西变的复杂，是为了让以后更加复杂的东西变得简单**。对于个体而言，随性比较简单，遵守规则比较复杂；但是对于整体（包含很多个体）而言，大家都随性就不好控制了，而大家都遵守规则就很容易管理 ———— 就是这个道理!

```javascript
const thunk = function (fileName, codeType) {
  // 返回一个只接受 callback 参数的函数
  return function (callback) {
    fs.readFile(fileName, codeType, callback);
  };
};
const readFileThunk = thunk('data1.json', 'utf-8');
readFileThunk((err, data) => {
  // 获取文件内容
});
```

先自己看一看以上代码，应该是能看懂的，但是你可能就是看懂了却不知道这么做的意义在哪里。意义先不管，先把它看懂，意义下一节就会看到。

- 执行`const readFileThunk = thunk('data1.json', 'utf-8')`返回的其实是一个函数
- `readFileThunk`这个函数，只接受一个参数，而且这个参数是一个`callback`函数

## `thunk`函数的特点

**经过对传统的异步操作函数进行封装，得到一个只有一个参数的函数，而且这个参数是一个`callback`函数，那这就是一个`thunk`函数。就像上面代码中`readFileThunk`一样。**

## 使用`thunkify`库

上面代码的封装，是我们手动来做的，但是每遇到一个情况就需要手动做吗？在这个开源的时代当然不会这样，直接使用第三方的`thunkify`就好了。

首先要安装`npm i thunkify --save`，然后在代码的最上方引用`const thunkify = require('thunkify')`。最后，上面我们手动写的代码，完全可以简化成这几行，非常简单！

```javascript
const thunk = thunkify(fs.readFile);
const readFileThunk = thunk('data1.json', 'utf-8');
readFileThunk((err, data) => {
  // 获取文件内容
});
```

## 接下来...

了解了`thunk`函数，我们立刻就将`Generator`和异步操作进行结合

# Generator 与异步操作

这一节正式开始讲解`Generator`如何进行异步操作，以前我们花了好几节的时间各种打基础，现在估计大家也都等急了，好戏马上开始！

## 在`Genertor`中使用`thunk`函数

这个比较简单了，之前都讲过的，直接看代码即可。代码中表达的意思，是要依次读取两个文件的内容

```javascript
const readFileThunk = thunkify(fs.readFile);
const gen = function* () {
  const r1 = yield readFileThunk('data1.json');
  console.log(r1);
  const r2 = yield readFileThunk('data2.json');
  console.log(r2);
};
```

## 挨个读取两个文件的内容

接着以上的代码继续写，注释写的非常详细，大家自己去看，看完自己写代码亲身体验。

```javascript
const g = gen();

// 试着打印 g.next() 这里一定要明白 value 是一个 thunk函数 ，否则下面的代码你都看不懂
// console.log( g.next() )  // g.next() 返回 {{ value: thunk函数, done: false }}

// 下一行中，g.next().value 是一个 thunk 函数，它需要一个 callback 函数作为参数传递进去
g.next().value((err, data1) => {
  // 这里的 data1 获取的就是第一个文件的内容。下一行中，g.next(data1) 可以将数据传递给上面的 r1 变量，此前已经讲过这种参数传递的形式
  // 下一行中，g.next(data1).value 又是一个 thunk 函数，它又需要一个 callback 函数作为参数传递进去
  g.next(data1).value((err, data2) => {
    // 这里的 data2 获取的是第二个文件的内容，通过 g.next(data2) 将数据传递个上面的 r2 变量
    g.next(data2);
  });
});
```

上面 6 行左右的代码，却用了 6 行左右的注释来解释，可见代码的逻辑并不简单，不过你还是要去尽力理解，否则接下来的内容无法继续。再说，我已经写的那么详细了，你只要照着仔细看肯定能看明白的。

也许上面的代码给你带来的感觉并不好，第一它逻辑复杂，第二它也不是那么易读、简洁呀，用`Generator`实现异步操作就是这个样子的？———— 当然不是，继续往下看。

## 自驱动流程

以上代码中，读取两个文件的内容都是手动一行一行写的，而我们接下来要做一个自驱动的流程，定义好`Generator`的代码之后，就让它自动执行。完整的代码如下所示：

```javascript
// 自动流程管理的函数
function run(generator) {
  const g = generator();
  function next(err, data) {
    const result = g.next(data); // 返回 { value: thunk函数, done: ... }
    if (result.done) {
      // result.done 表示是否结束，如果结束了那就 return 作罢
      return;
    }
    result.value(next); // result.value 是一个 thunk 函数，需要一个 callback 函数作为参数，而 next 就是一个 callback 形式的函数
  }
  next(); // 手动执行以启动第一次 next
}

// 定义 Generator
const readFileThunk = thunkify(fs.readFile);
const gen = function* () {
  const r1 = yield readFileThunk('data1.json');
  console.log(r1.toString());
  const r2 = yield readFileThunk('data2.json');
  console.log(r2.toString());
};

// 启动执行
run(gen);
```

其实这段代码和上面的手动编写读取两个文件内容的代码，原理上是一模一样的，只不过这里把流程驱动给封装起来了。我们简单分析一下这段代码

- 最后一行`run(gen)`之后，进入`run`函数内部执行
- 先`const g = generator()`创建`Generator`实例，然后定义一个`next`方法，并且立即执行`next()`
- 注意这个`next`函数的参数是`err, data`两个，和我们`fs.readFile`用到的`callback`函数形式完全一样
- 第一次执行`next`时，会执行`const result = g.next(data)`，而`g.next(data)`返回的是`{ value: thunk函数, done: ... }`，`value`是一个`thunk`函数，`done`表示是否结束
- 如果`done: true`，那就直接`return`了，否则继续进行
- `result.value`是一个`thunk`函数，需要接受一个`callback`函数作为参数传递进去，因此正好把`next`给传递进去，让`next`一直被执行下去

大家照着这个过程来捋一捋，不是特别麻烦，然后自己试着写完运行一下，基本就能了解了。

## 使用`co`库

刚才我们定义了一个`run`还是来做自助流程管理，是不是每次使用都得写一遍`run`函数呢？———— 肯定不是的，直接用大名鼎鼎的`co`就好了。用`Generator`的工程师，肯定需要用到`co`，两者天生一对，难舍难分。

使用之前请安装`npm i co --save`，然后在文件开头引用`const co = require('co')`。`co`到底有多好用，我们将刚才的代码用`co`重写，就变成了如下代码。非常简洁

```javascript
// 定义 Generator
const readFileThunk = thunkify(fs.readFile);
const gen = function* () {
  const r1 = yield readFileThunk('data1.json');
  console.log(r1.toString());
  const r2 = yield readFileThunk('data2.json');
  console.log(r2.toString());
};
const c = co(gen);
```

而且`const c = co(gen)`返回的是一个`Promise`对象，可以接着这么写

```javascript
c.then((data) => {
  console.log('结束');
});
```

## `co`库和`Promise`

刚才提到`co()`最终返回的是`Promise`对象，后知后觉，我们已经忘记`Promise`好久了，现在要重新把它拾起来。**如果使用`co`来处理`Generator`的话，其实`yield`后面可以跟`thunk`函数，也可以跟`Promise`对象。**

`thunk`函数上文一直在演示，下面演示一下`Promise`对象的，也权当再回顾一下久别的`Promise`。其实从形式上和结果上，都跟`thunk`函数一样。

```javascript
const readFilePromise = Q.denodeify(fs.readFile);

const gen = function* () {
  const r1 = yield readFilePromise('data1.json');
  console.log(r1.toString());
  const r2 = yield readFilePromise('data2.json');
  console.log(r2.toString());
};

co(gen);
```

## 接下来...

经过了前几节的技术积累，我们用一节的时间就讲述了`Generator`如何进行异步操作。接下来要介绍一个开源社区中比较典型的使用`Generator`的框架 ———— Koa

# Generator 的具体应用

前面用两节的内容介绍了`Generator`可以让执行处于暂停状态，并且知道了`Generator`返回的是一个`Iterator`对象，这一节就详细介绍一下`Generator`的一些基本用法。

## `next`和`yield`参数传递

我们之前已经知道，`yield`具有返回数据的功能，如下代码。`yield`后面的数据被返回，存放到返回结果中的`value`属性中。这算是一个方向的参数传递。

```javascript
function* G() {
  yield 100;
}
const g = G();
console.log(g.next()); // {value: 100, done: false}
```

还有另外一个方向的参数传递，就是`next`向`yield`传递，如下代码。

```javascript
function* G() {
  const a = yield 100;
  console.log('a', a); // a aaa
  const b = yield 200;
  console.log('b', b); // b bbb
  const c = yield 300;
  console.log('c', c); // c ccc
}
const g = G();
g.next(); // value: 100, done: false
g.next('aaa'); // value: 200, done: false
g.next('bbb'); // value: 300, done: false
g.next('ccc'); // value: undefined, done: true
```

捋一捋上面代码的执行过程：

- 执行第一个`g.next()`时，未传递任何参数，返回的`{value: 100, done: false}`，这个应该没有疑问
- 执行第二个`g.next('aaa')`时，传递的参数是`'aaa'`，这个`'aaa'`就会被赋值到`G`内部的`a`标量中，然后执行`console.log('a', a)`打印出来，最后返回`{value: 200, done: false}`
- 执行第三个、第四个时，道理都是完全一样的，大家自己捋一捋。

**有一个要点需要注意，就`g.next('aaa')`是将`'aaa'`传递给上一个已经执行完了的`yield`语句前面的变量，而不是即将执行的`yield`前面的变量**。这句话要能看明白，看不明白就说明刚才的代码你还没看懂，继续看。

## `for...of`的应用示例

针对`for...of`在`Iterator`对象的操作之前已经介绍过了，不过这里用一个非常好的例子来展示一下。用简单几行代码实现斐波那契数列。通过之前学过的`Generator`知识，应该不难解读这份代码。

```javascript
function* fibonacci() {
  let [prev, curr] = [0, 1];
  for (;;) {
    [prev, curr] = [curr, prev + curr];
    // 将中间值通过 yield 返回，并且保留函数执行的状态，因此可以非常简单的实现 fibonacci
    yield curr;
  }
}
for (let n of fibonacci()) {
  if (n > 1000) {
    break;
  }
  console.log(n);
}
```

## `yield* `语句

如果有两个`Generator`，想要在第一个中包含第二个，如下需求：

```javascript
function* G1() {
  yield 'a';
  yield 'b';
}
function* G2() {
  yield 'x';
  yield 'y';
}
```

针对以上两个`Generator`，我的需求是：一次输出`a x y b`，该如何做？有同学看到这里想起了刚刚学到的`for..of`可以实现————不错，确实可以实现（大家也可以想想到底该如何实现）

但是，这要演示一个更加简洁的方式`yield* `表达式

```javascript
function* G1() {
  yield 'a';
  yield* G2(); // 使用 yield* 执行 G2()
  yield 'b';
}
function* G2() {
  yield 'x';
  yield 'y';
}
for (let item of G1()) {
  console.log(item);
}
```

之前学过的`yield`后面会接一个普通的 JS 对象，而`yield* `后面会接一个`Generator`，而且会把它其中的`yield`按照规则来一步一步执行。**如果有多个`Generator`串联使用的话（例如`Koa`源码中），用`yield* `来操作非常方便**。

## `Generator`中的`this`

对于以下这种写法，大家可能会和构造函数创建对象的写法产生混淆，这里一定要注意 —— **Generator 不是函数，更不是构造函数**

```javascript
function* G() {}
const g = G();
```

而以下这种写法，更加不会成功。只有构造函数才会这么用，构造函数返回的是`this`，而`Generator`返回的是一个`Iterator`对象。完全是两码事，千万不要搞混了。

````javascript
function* G() {
    this.a = 10
}
const g = G()
console.log(g.a) // 报错
```# koa 中使用 Generator

[koa](https://github.com/koajs/koa) 是一个 nodejs 开发的 web 框架，所谓 web 框架就是处理 http 请求的。开源的 nodejs 开发的 web 框架最初是 [express](https://github.com/expressjs/express)。

我们此前说过，既然是处理 http 请求，是一种网络操作，肯定就会用到异步操作。express 使用的异步操作是传统的`callbck`，而 koa 用的是我们刚刚讲的`Generator`（koa `v1.x`用的是`Generator`，已经被广泛使用，而 koa `v2.x`用到了 ES7 中的`async-await`，不过因为 ES7 没有正式发布，所以 koa `v2.x`也没有正式发布，不过可以试用）

koa 是由 express 的原班开发人员开发的，比 express 更加简洁易用，**因此 koa 是目前最为推荐的 nodejs web 框架**。阿里前不久就依赖于 koa 开发了自己的 nodejs web 框架 [egg](https://github.com/eggjs/egg)

国内可以通过[koa.bootcss.com](http://koa.bootcss.com/)查阅文档，*不过这网站依赖了 Google 的服务，因此如果不科学上网，估计会访问会很慢*。

## koa 中如何应用`Generator`

koa 是一个 web 框架，处理 http 请求，但是这里我们不去管它如何处理 http 请求，而是直接关注它使用`Genertor`的部分————**中间件**。

例如，我们现在要用 3 个`Generator`输出`12345`，我们如下代码这么写。应该能看明白吧？看不明白回炉重造！

```javascript
let info = ''
function* g1() {
    info += '1'  // 拼接 1
    yield* g2()  // 拼接 234
    info += '5'  // 拼接 5
}
function* g2() {
    info += '2'  // 拼接 2
    yield* g3()  // 拼接 3
    info += '4'  // 拼接 4
}
function* g3() {
    info += '3'  // 拼接 3
}

var g = g1()
g.next()
console.log(info)  // 12345
````

但是如果用 koa 的 **中间件** 的思路来做，就需要如下这么写。

```javascript
app.use(function* (next) {
  this.body = '1';
  yield next;
  this.body += '5';
  console.log(this.body);
});
app.use(function* (next) {
  this.body += '2';
  yield next;
  this.body += '4';
});
app.use(function* (next) {
  this.body += '3';
});
```

解释几个关键点

- `app.use()`中传入的每一个`Generator`就是一个 **中间件**，中间件按照传入的顺序排列，顺序不能乱
- 每个中间件内部，`next`表示下一个中间件。`yield next`就是先将程序暂停，先去执行下一个中间件，等`next`被执行完之后，再回过头来执行当前代码的下一行。**因此，koa 的中间件执行顺序是一种[洋葱圈模型](https://eggjs.org/zh-cn/intro/egg-and-koa.html#midlleware)，不过这里看不懂也没问题**。
- 每个中间件内部，`this`可以共享变量。即第一个中间件改变了`this`的属性，在第二个中间件中可以看到效果。

## koa 的这种应用机制是如何实现的

前方高能————上面介绍 koa 的中间价估计有些新人就开始蒙圈了，不过接下来还有更加有挑战难度的，就是以上这种方式是如何实现的。你就尽量去看，看懂了更好，看不懂也没关系————当然，你完全可以选择跳过本教程直接去看下一篇，这都 OK

加入我们自己实现一个简单的 koa ———— MyKoa ，那么仅需要几十行代码就可以搞定上面的问题。直接写代码，注意看重点部分的注释

```javascript
class MyKoa extends Object {
  constructor(props) {
    super(props);

    // 存储所有的中间件
    this.middlewares = [];
  }

  // 注入中间件
  use(generator) {
    this.middlewares.push(generator);
  }

  // 执行中间件
  listen() {
    this._run();
  }

  _run() {
    const ctx = this;
    const middlewares = ctx.middlewares;
    co(function* () {
      let prev = null;
      let i = middlewares.length;
      //从最后一个中间件到第一个中间件的顺序开始遍历
      while (i--) {
        // ctx 作为函数执行时的 this 才能保证多个中间件中数据的共享
        //prev 将前面一个中间件传递给当前中间件，才使得中间件里面的 next 指向下一个中间件
        prev = middlewares[i].call(ctx, prev);
      }
      //执行第一个中间件
      yield prev;
    });
  }
}
```

最后我们执行代码实验一下效果

```javascript
var app = new MyKoa();
app.use(function* (next) {
  this.body = '1';
  yield next;
  this.body += '5';
  console.log(this.body); // 12345
});
app.use(function* (next) {
  this.body += '2';
  yield next;
  this.body += '4';
});
app.use(function* (next) {
  this.body += '3';
});
app.listen();
```

## 接下来...

`Generator`的应用基本讲完，从一开始的基础到后面应用到异步操作，再到本节的高级应用 koa ，算是比较全面了。接下来，我们要再回到最初的起点，探讨`Generator`的本质，以及它和`callback`的关系。

还是那句话，搞明白原理，才能用的更加出色！

# ES6 中的 Generator

**在 ES6 出现之前，基本都是各式各样类似`Promise`的解决方案来处理异步操作的代码逻辑，但是 ES6 的`Generator`却给异步操作又提供了新的思路，马上就有人给出了如何用`Generator`来更加优雅的处理异步操作。**

## `Generator`简介

先来一段最基础的`Generator`代码

```javascript
function* Hello() {
  yield 100;
  yield (function () {
    return 200;
  })();
  return 300;
}

var h = Hello();
console.log(typeof h); // object

console.log(h.next()); // { value: 100, done: false }
console.log(h.next()); // { value: 200, done: false }
console.log(h.next()); // { value: 300, done: true }
console.log(h.next()); // { value: undefined, done: true }
```

- 定义`Generator`时，需要使用`function*`，其他的和定义函数一样。内部使用`yield`，至于`yield`的用处以后再说
- 执行`var h = Hello()`生成一个`Generator`对象，经验验证`typeof h`发现不是普通的函数
- 执行`Hello()`之后，`Hello`内部的代码不会立即执行，而是出于一个**暂停**状态
- 执行第一个`h.next()`时，会激活刚才的暂停状态，开始执行`Hello`内部的语句，但是，直到遇到`yield`语句。一旦遇到`yield`语句时，它就会将`yield`后面的表达式执行，并返回执行的结果，然后又立即进入**暂停**状态。
- 因此第一个`console.log(h.next())`打印出来的是`{ value: 100, done: false }`，`value`是第一个`yield`返回的值，`done: false`表示目前处于暂停状态，尚未执行结束，还可以再继续往下执行。
- 执行第二个`h.next()`和第一个一样，不在赘述。此时会执行完第二个`yield`后面的表达式并返回结果，然后再次进入**暂停**状态
- 执行第三个`h.next()`时，程序会打破暂停状态，继续往下执行，但是遇到的不是`yield`而是`return`。这就预示着，即将执行结束了。因此最后返回的是`{ value: 300, done: true }`，`done: true`表示执行结束，无法再继续往下执行了。
- 再去执行第四次`h.next()`时，就只能得到`{ value: undefined, done: true }`，因为已经结束，没有返回值了。

以下几个要点：

- `Generator`不是函数，不是函数，不是函数
- `Hello()`不会立即出发执行，而是一上来就暂停
- 每次`h.next()`都会打破暂停状态去执行，直到遇到下一个`yield`或者`return`
- 遇到`yield`时，会执行`yeild`后面的表达式，并返回执行之后的值，然后再次进入暂停状态，此时`done: false`。
- 遇到`return`时，会返回值，执行结束，即`done: true`
- 每次`h.next()`的返回值永远都是`{value: ... , done: ...}`的形式

## `Generator`最终如何处理异步操作

上面只是一个最基本最简单的介绍，但是我们看不到任何与异步操作相关的事情，那我们接下来就先展示一下最终我们将使用`Generator`如何做异步操作。

之前讲解`Promise`时候，依次读取多个文件，我们是这么操作的（看不明白的需要回炉重造哈），主要是使用`then`做链式操作。

```javascript
readFilePromise('some1.json')
  .then((data) => {
    console.log(data); // 打印第 1 个文件内容
    return readFilePromise('some2.json');
  })
  .then((data) => {
    console.log(data); // 打印第 2 个文件内容
    return readFilePromise('some3.json');
  })
  .then((data) => {
    console.log(data); // 打印第 3 个文件内容
    return readFilePromise('some4.json');
  })
  .then((data) => {
    console.log(data); // 打印第 4 个文件内容
  });
```

而如果学会`Generator`那么读取多个文件就是如下这样写。先不要管如何实现的，光看一看代码，你就能比较出哪个更加简洁、更加易读、更加所谓的优雅！

```javascript
co(function* () {
  const r1 = yield readFilePromise('some1.json');
  console.log(r1); // 打印第 1 个文件内容
  const r2 = yield readFilePromise('some2.json');
  console.log(r2); // 打印第 2 个文件内容
  const r3 = yield readFilePromise('some3.json');
  console.log(r3); // 打印第 3 个文件内容
  const r4 = yield readFilePromise('some4.json');
  console.log(r4); // 打印第 4 个文件内容
});
```

## 接下来...

接下来我们不会立刻讲解如何使用`Generator`做异步操作，而是看一看`Generator`是一个什么东西！说来话长，这要从 ES6 的另一个概念`Iterator`说起。

# ES7 中引入 async-await

前面介绍完了`Generator`的异步处理，可以说是跌跌撞撞，经过各种基础介绍和封装，好不容易出了一个比较简洁的异步处理方案，学习成本非常高————这显然不是我们想要的！

因此 ES7 就干脆自己参照`Generator`封装了一套异步处理方案————`async-await`。说是参照，其实可以理解为是`Generator`的语法糖！

## `Generator`和`async-await`的对比

先来一段`Generator`处理异步的代码

```javascript
co(function* () {
  const r1 = yield readFilePromise('some1.json');
  console.log(r1); // 打印第 1 个文件内容
  const r2 = yield readFilePromise('some2.json');
  console.log(r2); // 打印第 2 个文件内容
});
```

再来一段`async-await`的执行代码如下，两者做一个比较。

```javascript
const readFilePromise = Q.denodeify(fs.readFile);

// 定义 async 函数
const readFileAsync = async function () {
  const f1 = await readFilePromise('data1.json');
  const f2 = await readFilePromise('data2.json');
  console.log('data1.json', f1.toString());
  console.log('data2.json', f2.toString());

  return 'done'; // 先忽略，后面会讲到
};
// 执行
const result = readFileAsync();
```

从上面两端代码比较看来，`async function`代替了`function* `，`await`代替了`yield`，其他的再没有什么区别了。哦，还有，使用`async-await`时候不用再引用`co`这种第三方库了，直接执行即可。

## 使用`async-await`的不同和好处

第一，**`await`后面不能再跟`thunk`函数，而必须跟一个`Promise`对象**（因此，`Promise`才是异步的终极解决方案和未来）。跟其他类型的数据也 OK，但是会直接同步执行，而不是异步。

第二，执行`const result = readFileAsync()`返回的是个`Promise`对象，而且上面代码中的`return 'done'`会直接被下面的`then`函数接收到

```javascript
result.then((data) => {
  console.log(data); // done
});
```

第三，从代码的易读性来将，`async-await`更加易读简介，也更加符合代码的语意。而且还不用引用第三方库，也无需学习`Generator`那一堆东西，使用成本非常低。
