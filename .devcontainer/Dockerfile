FROM ubuntu

WORKDIR /study

RUN set -eux; \
    ln -snf /usr/share/zoneinfo/Asia/Shanghai /etc/localtime && echo Asia/Shanghai > /etc/timezone; \
    sed -i s@/archive.ubuntu.com/@/mirrors.cloud.tencent.com/@g /etc/apt/sources.list; \
    apt update; \
    apt install -y gosu;\ 
    gosu nobody true; \
    apt install -y build-essential gdb git tig vim cmake lsof nodejs npm iputils-ping net-tools telnet wget libgflags-dev python3-pip tmux ;\
    pip install -i https://mirrors.cloud.tencent.com/pypi/simple --upgrade pip; \
    pip config set global.index-url http://mirrors.cloud.tencent.com/pypi/simple; \
    pip config set install.trusted-host mirrors.cloud.tencent.com; \
    pip install Django autopep8; \
    npm install -g n; \
    n latest; \
    apt autoremove; \
    rm -rf /var/lib/apt/lists/*

COPY docker-entrypoint.sh /usr/local/bin
RUN chmod a+x /usr/local/bin/docker-entrypoint.sh

ENTRYPOINT [ "docker-entrypoint.sh" ]
CMD [ "/bin/bash" ]