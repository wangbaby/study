# 镜像构建
## 容器中不要使用root账号

gosu是个工具，用来提升指定账号的权限，作用与sudo命令类似，而docker中使用gosu的起源来自安全问题.

docker容器中运行的进程，如果以root身份运行的会有安全隐患，该进程拥有容器内的全部权限，更可怕的是如果有数据卷映射到宿主机，那么通过该容器就能操作宿主机的文件夹了，一旦该容器的进程有漏洞被外部利用后果是很严重的。
因此，容器内使用非root账号运行进程才是安全的方式，这也是我们在制作镜像时要注意的地方。

docker容器默认使用root用户运行，当使用绑定挂载方式将主机文件/目录挂载；到容器，容器在挂载点创建的文件的权限/属主/属组均属于root

# 在镜像中创建非root账号

以redis官方镜像的Dockerfile为例，来看看如何创建账号
```
RUN groupadd -r redis && useradd -r -g redis redis
```
可见redis官方镜像使用groupadd和useradd创建了名为redis的组合账号，接下来就是用redis账号来启动服务了，理论上应该是以下套路：

- 用USER redis将账号切换到redis；
- 在docker-entrypoint.sh执行的时候已经是redis身份了，如果遇到权限问题，例如一些文件只有root账号有读、写、执行权限，用sudo xxx命令来执行即可；
**但事实并非如此！**
在Dockerfile脚本中未发现USER redis命令，这意味着执行docker-entrypoint.sh文件的身份是root；
其次，在docker-entrypoint.sh中没有发现su - redis命令，也没有sudo命令；

这是怎么回事呢？难道容器内的redis服务是用root账号启动的？

# 确认redis服务的启动账号
```
docker pull redis
docker run --name myredis -itd redis
docker exec -it myredis /bin/bash
apt update
apt install procps
ps -ef
```
结果展示了两个关键信息：
第一，redis服务是redis账号启动的，并非root；
第二，redis服务的PID等于1，这很重要，宿主机执行docker stop命令时，该进程可以收到SIGTERM信号量，于是redis应用可以做一些退出前的准备工作，例如保存变量、退出循环等，也就是优雅停机(Gracefully Stopping)；

现在我们已经证实了redis服务并非root账号启动，而且该服务进程在容器内还是一号进程，但是我们在Dockerfile和docker-entrypoint.sh脚本中都没有发现切换到redis账号的命令，也没有sudo和su，这是怎么回事呢？

# 答案是gosu
```
#!/bin/sh
set -e

# first arg is `-f` or `--some-option`
# or first arg is `something.conf`
if [ "${1#-}" != "$1" ] || [ "${1%.conf}" != "$1" ]; then
	set -- redis-server "$@"
fi

# allow the container to be started with `--user`
if [ "$1" = 'redis-server' -a "$(id -u)" = '0' ]; then
	find . \! -user redis -exec chown redis '{}' +
	exec gosu redis "$0" "$@"
fi

exec "$@"
```
分析一下：

- 假设启动容器的命令是docker run --name myredis -idt redis redis-server /usr/local/etc/redis/redis.conf
- 容器启动后会执行docker-entrypoint.sh脚本，此时的账号是root
- 当前账号是root，因此会执行exec gosu redis "$0" "$@"
- $0表示当前脚本的名称,即docker-entrypoint.sh, $@表示外部传入的所有参数，即redis-server /usr/local/etc/redis/redis.conf
- gosu redis “$0” “@”，表示以redis账号的身份执行以下命令：docker-entrypoint.sh redis-server /usr/local/etc/redis/redis.conf
- gosu redis “$0” "@"前面加上个exec，表示以gosu redis “$0” "@"这个命令启动的进程替换正在执行的docker-entrypoint.sh进程，这样就保证了gosu redis “$0” "@"对应的进程ID为1
- gosu redis “$0” "@"导致docker-entrypoint.sh再执行一次，但是当前的账号已经不是root了，于是会执行兜底逻辑 exec “$@”
- 此时的$@是redis-server /usr/local/etc/redis/redis.conf，因此redis服务会启动，而且账号是redis；
- $@前面有个exec，会用redis-server命令启动的进程取代当前的docker-entrypoint.sh进程，所以，最终redis进程的PID等于1，而docker-entrypoint.sh这个脚本的进程已经被替代，因此就结束掉了


# 关于gosu
通过上面的分析，我们对gosu的作用有了基本了解：功能和sudo类似，提升指定账号的权限，用来执行指定的命令，其官网地址是：https://github.com/tianon/gosu ，如下图所示，官方的描述也是说su和sudo命令有一些问题，所以才有了gosu工具来作为替代品

# 为什么要用gosu取代sudo
```
docker run --rm gosu/alpine gosu root ps aux
```
上述命令会启动一个安装了gosu的linux容器，并且启动后自动执行命令gosu root ps aux，作用是以root账号的身份执行ps aux，也就是将当前进程都打印出来，执行结果如下：
```
PID USER TIME COMMAND
1    root 0:00 ps aux
```
上述信息显示，我们执行docker run时的gosu root ps aux会执行ps命令，该命令成了容器内的唯一进程，这说明通过gosu启动的是符合我们要求的（PID为1），接下来再看看用sudo执行ps命令的效果
```
docker run --rm ubuntu:truusty
```
```
USER         PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
root           1  0.0  0.0  46020  2924 ?        Ss   03:47   0:00 sudo ps aux
root           7  0.0  0.0  15576  2164 ?        R    03:47   0:00 ps aux
```
尽管我们只想启动ps进程，但是容器内出现了两个进程，sudo命令会创建第一个进程，然后该进程再创建了ps进程，而且ps进程的PID并不等于1，这是达不到我们要求的，此时在宿主机向该容器发送信号量，收到信号量的是sudo进程。

通过上面对可以小结：

- gosu启动命令时只有一个进程，所以docker容器启动时使用gosu，那么该进程可以做到PID等于1；
- sudo启动命令时先创建sudo进程，然后该进程作为父进程去创建子进程，1号PID被sudo进程占据；
综上所述，在docker的entrypoint中有如下建议：
- 创建group和普通账号，不要使用root账号启动进程；
- 如果普通账号权限不够用，建议使用gosu来提升权限，而不是sudo；
- entrypoint.sh脚本在执行的时候也是个进程，启动业务进程的时候，在命令前面加上exec，这样新的进程就会取代entrypoint.sh的进程，得到1号PID；
- exec "$@"是个保底的逻辑，如果entrypoint.sh的入参在整个脚本中都没有被执行，那么exec "$@"会把入参执行一遍，如果前面执行过了，这一行就不起作用


RUN set -eux; \
    apt-get update; \
    apt-get install -y gosu; \
    rm -rf /var/lib/apt/lists/*; \
    # verify that the binary works
    gosu nobody true


    Docker volume 绑定挂载
Docker 提供了数据卷绑定挂载的机制(volume bind mounts)来将主机上的文件 (file) 或者目录 (directory) 挂载进容器 (container)。也就是 docker run 命令中熟知的 -v 参数。根据 Docker 官方文档，绑定挂载一般适合于三种场景：

共享主机 配置文件。譬如将主机的 DNS 配置文件 /etc/resolv.conf 挂载到容器里省去配置。
共享项目 源代码 和 构建产物。譬如将 maven 项目的 target 目录挂载到容器内。
当主机的特定目录结构和容器内需要的目录结构完全一致的时候。
但是实际使用时，会遇到文件权限问题：

容器向挂载的目录写入文件或者目录后，主机上没有权限访问。因为 Docker 内部默认总是使用 root 用户运行。
譬如执行如下命令创建一个容器，挂载当前目录到容器内，并在容器内向主机当前目录创建 tmp.txt：

$ docker run --rm \
    -v "$PWD":/project \
    debian \
    bash -c "touch /project/tmp.txt"
$ ls -l tmp.txt
-rw-r--r-- 1 root root 0 Sep 28 01:55 tmp.txt
主机当前目录出现了容器内创建的 tmp.txt，但是其权限、用户和组均是 root，其他用户不可写。

使用 user 参数指定容器运行期间的用户
常见解决方法是可以通过 Docker 提供的 User 命令、--user 参数来指定容器内部的用户和组的 id，譬如：

$ docker run --rm \
    --user=$UID:$(id -g $USER) \
    -v "$PWD":/project \
    debian \
    bash -c "touch /project/tmp.txt"
$ ls -l tmp.txt
-rw-r--r-- 1 current_user current_user 0 Sep 28 02:09 tmp.txt
可以看到输出，current_user 处会显示主机当前用户的名字，所以解决了主机用户对挂载的卷没有权限的问题。

user 参数的缺陷
使用 user 参数有一些缺陷，如果你进入容器内部的 terminal，会显示如下内容：

$ docker run --rm \
    -it \
    --user=$UID:$(id -g $USER) \
    -v "$PWD":/project \
    debian \
    bash -c "touch /project/tmp.txt && bash"
I have no name!@6cc07662a201:/$    
bash 的用户名会显示 I have no name!，这是因为我们通过 --user 参数指定了容器内部的用户 id，但该 id 不存在于容器内的 /etc/passwd 文件中。

除此之外，使用 user 参数仍然存在权限问题：

除了绑定挂载的主机路径之外的所有路径，对于容器内部的用户都没有写权限。
这也是不可接受的，因为容器运行过程中我们可能会进行一些临时文件的写入，这些临时文件我们并不想要写到主机的挂载目录，但除了挂载路径之外的任何路径容器都没有写入权限。

譬如我们在主机上创建 models 目录。

$ mkdir models
$ ls -ld models/
drwxr-xr-x 3 current_user current_user 4096 Sep 28 02:28 models/
我们使用 Docker 挂载 models 目录，然而在 Docker 容器内部除了 models 文件夹都没有访问权限。

$ docker run --rm \
    --user=$UID:$(id -g $USER) \
    -v "$PWD/models":/project/models \
    debian \
    bash -c "touch /project/tmp.txt"
touch: cannot touch '/project/tmp.txt': Permission denied
这可以通过增加挂载路径：

$ docker run --rm \
    --user=$UID:$(id -g $USER) \
    -v "$PWD":/project \
    -v "$PWD/models":/project/models \
    debian \
    bash -c "touch /project/tmp.txt"
$
这样容器运行过程往 /project 写的临时文件都会出现在主机上。

可见，user 参数并不能解决所有问题。它存在两个问题：

指定的用户不存在于容器内的 /etc/passwd 中，shell 无法显示用户名。
user 参数会指定容器运行时刻的用户和主机一致，因此持有主机挂载的用户目录，但容器内非挂载的目录均无权限。
Docker 挂载绑定最佳实践
我们需要一种手段，既可以像 user 参数一样在容器运行时可以将用户切换到和主机相同的用户，又希望 Docker 容器保留 root 用户，并给主机用户想要访问的目录授权（对特定目录 chown、chmod 等）。

Docker 官方文档对 Entrypoint 介绍时给出了一种最佳实践。

编写如下的 Dockerfile：

FROM debian

RUN apt-get update && apt-get -y --no-install-recommends install \
    ca-certificates \
    curl \
    dirmngr \
    gpg

RUN gpg --keyserver ha.pool.sks-keyservers.net --recv-keys B42F6819007F00F88E364FD4036A9C25BF357DD4
RUN curl -o /usr/local/bin/gosu -SL "https://github.com/tianon/gosu/releases/download/1.4/gosu-$(dpkg --print-architecture)" \
    && curl -o /usr/local/bin/gosu.asc -SL "https://github.com/tianon/gosu/releases/download/1.4/gosu-$(dpkg --print-architecture).asc" \
    && gpg --verify /usr/local/bin/gosu.asc \
    && rm /usr/local/bin/gosu.asc \
    && chmod +x /usr/local/bin/gosu

COPY docker-entrypoint.sh /usr/local/bin/docker-entrypoint.sh
RUN chmod a+x /usr/local/bin/docker-entrypoint.sh

WORKDIR /project
ENTRYPOINT ["/usr/local/bin/docker-entrypoint.sh"]
该 Dockerfile 中安装了一个 gosu 的工具，并设置了程序的 Entrypoint。由于 Docker 内使用 sudo 可能导致一些不可预知的 TTY 和信号转发问题，所以 Docker 官方推荐了使用 gosu 这个工具，用于保持容器在 root 用户下运行，并用 sudo 来切换到指定用户。

其中 docker-entrypoint.sh 内容如下：

#!/bin/bash

# 获取主机用户id
USER_ID=${LOCAL_USER_ID:-9001}
# 给主机用户授权制定的非绑定挂载目录
chown -R $USER_ID /project

# 创建和主机用户相同uid的用户，名为user
useradd --shell /bin/bash -u $USER_ID -o -c "" -m user
usermod -a -G root user
export HOME=/home/user

exec /usr/local/bin/gosu user "$@"
可以看到 docker-entrypoint.sh 中创建了一个名为 user 的用户，该用户的 uid 由 docker run 的参数传入，这里利用了 linux 系统的一个特点，容器内外用户权限的记录和用户的名字无关，只和 uid 有关，因此容器内我们将用户命名为 user 没有影响。docker-entrypoint.sh 最后一行调用 gosu 来切换到 user 用户并执行 Dockerfile 中的用户命令。

有了如上两个脚本，我们构建镜像并执行：

$ docker build -t test_volume .
运行容器时指定 LOCAL_USER_ID 参数：

$ docker run --rm \
    -e LOCAL_USER_ID=<code>id -u $USER</code> \
    -v "$PWD/models":/project/models \
    test_volume \
    sh -c "touch tmp.txt && touch models/model.txt"
$ ls -l models/model.txt
-rw-r--r-- 1 current_user current_user 0 Sep 28 06:41 models/model.txt
可见不仅容器内往挂载目录 /project/models 写入的文件 model.txt 所有者是主机用户，而且在容器内往非挂载目录 /project/tmp.txt 写入文件也不会遇到权限问题。

总结
Docker 运行时容器内默认使用 root 用户运行，但是我们不是总是想要用 root 用户，因为有时候我们希望容器计算产生一些文件，并通过 volume 的绑定挂载在主机上获取。特别是我们用 jenkins 等工具写一些持续集成的脚本时候。容器内用 root 用户运行会导致产生的文件也是 root 用户的，主机上没有读取权限。因此我们需要让容器在运行的时候切换到主机上的用户。

Docker 对于这种情况仍然没有提供足够便利的基础设施，我们采用了 Docker 官方目前推荐的一个方式，通过编写一个 docker-entrypoint.sh 脚本作为 Dockerfile 的 Entrypoint，脚本中创建和主机上相同 uid 的用户，并通过 gosu 工具切换到该用户执行命令。uid 需要在 docker run 阶段通过参数传入。我们在脚本中设置了缺省 uid ，上面的脚本随机选择了一个 9001，注意要将该缺省值避免设置成和 Docker 镜像中存在的用户冲突的 uid。
