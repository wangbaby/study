# 使用腾讯云镜像源加速

## 临时使用

```
pip install -i https://mirrors.cloud.tencent.com/pypi/simple <some-package>
```

## 设为默认

```
pip install -i https://mirrors.cloud.tencent.com/pypi/simple --upgrade pip
pip config set global.index-url https://mirrors.cloud.tencent.com/pypi/simple
pip config set install.trusted-host mirrors.cloud.tencent.com
```

# python3 pip3

```
sudo apt update
sudo apt install python3 python3-pip
```

# pip3

```
pip install -r requirements.txt
// beautifulsoup4==4.9.2
// requests==2.24.0
```