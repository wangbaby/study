# 桌面环境登录后启动命令

在 Ubuntu 找到“启动应用程序”管理器 ,里面可以添加要执行的命令

# chrome 以代理模式启动

```
google-chrome --proxy-server=socks5://127.0.0.1:1080
chromium-browser --proxy-server=socks5://127.0.0.1:1080
```

# 修改 capslock

setxkbmap -option ctrl:nocaps

# 创建桌面快捷方式

```
sudo vim /usr/share/applications/panda.desktop

[Desktop Entry]
Name=QQ
Exec=/home/fu/桌面/DeepinQQ-20180228-x86_64.AppImage
Icon=/home/fu/图片 qq.png
Type=Application
StartupNotify=true

sudo chmod u+x  /usr/share/applications/panda.desktop
```


