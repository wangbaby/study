# server

```
wget https://down.24kplus.com/linux/shadowsocks/centos-shadowsocks-libev.sh
chmod +x centos-shadowsocks-libev.sh && ./centos-shadowsocks-libev.sh
```

# client

```
sudo apt install shadowsocks-libev

vim ~/shadowsocks.json
{
 "server": "",
 "server_port": 17338,
 "local_address": "127.0.0.1",
 "local_port": 1080,
 "password": "wangwang19910817",
 "timeout": 300,
 "method": "aes-256-gcm",
 "fast_open": false,
 "workers": 1
}

ss-local -c ~/shadowsocks.json
```
