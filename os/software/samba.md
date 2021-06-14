```
sudo apt-get install -y samba

// 配置访问
sudo vim /etc/samba/smb.conf
// 在最后面新增配置：
[share]
comment = sharedir
path = /home/pi/share
writable = yes
browable = yes

// 新增用户
sudo smbpasswd -a pi

// 重启使配置生效：
sudo systemctl restart smbd
sudo systemctl restart nmbd
```
