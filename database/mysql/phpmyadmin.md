在 Ubuntu 20.04 LTS 系统上安装 Apache 2.4、MySQL 8.0 和 PHP 7.4

```
sudo apt update
sudo apt install -y php7.4
sudo apt install -y php7.4-curl php7.4-gd php7.4-json php7.4-mbstring php7.4-xml

sudo apt install -y apache2 libapache2-mod-php7.4

sudo apt install -y php7.4-mysql

sudo apt install -y phpmyadmin

sudo ln -s /usr/share/phpmyadmin /var/www/html

// 修改apache2 默认端口
sudo vim  /etc/apache2/ports.conf 

sudo systemctl restart apache2

// test
sudo echo "<?php phpinfo(); ?>" > /var/www/html/info.php

```
