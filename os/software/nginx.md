# 安装

```
sudo apt install -y nginx
// 默认html
/var/www/html/index.html
```

# 虚拟主机

```
cd /etc/nginx/sites-available/

sudo vim apache2.conf
server {
    listen 80;
    server_name stock.awesome-daryl.cn;
    location /
    {
        proxy_pass http://127.0.0.1:9999;
    }

}

sudo ln -s /etc/ngix/sites-available/apache2.conf /etc/nginx/sites-enabled/apache2.conf

sudo systemctl restart nginx

```