# apt 与 dpkg

dpkg: 这个机制最早是由 Debian Linux 社群所开发出来的，通过 dpkg 的机制， Debian 提供的软件就能够简单的安装起来，同时还能提供安装后的软件信息， 只要是衍生于 Debian 的其他 Linux distributions 大多使用 dpkg 这个机制来管理软件的， 如 Ubuntu 等。

## dpkg

```
dpkg -l 列出当前系统中所有的包
```

## apt

Advanced Packaging Tool

apt  命令的引入就是为了解决命令过于分散的问题，它包括了  apt-get  命令出现以来使用最广泛的功能选项，以及  apt-cache  和  apt-config  命令中很少用到的功能

```
apt list --installed // 列出所有已安装的包：
apt list --all-versions // 列出所有已安装的包的版本信息

sudo apt update // 列出所有可更新的软件清单命令
sudo apt update <package_name>  // 更新指定的软件命令

sudo apt upgrade // 升级软件包

sudo apt show <package_name> // 显示软件包具体信息,例如：版本号，安装大小，依赖关系等等

sudo apt remove <package_name> // 删除软件包命令
sudo apt purge <package_name>  // 移除软件包及配置文件: 
sudo apt autoremove // 清理不再使用的依赖和库文件: 

apt search <keyword> // 查找软件包命令
```

# yum 与 rpm

rpm: 这个机制最早是由 Red Hat 这家公司开发出来的，后来实在很好用，因此很多 distributions 就使用这个机制来作为软件安装的管理方式, 包括 Fedora, CentOS, SuSE 。

## rpm

为何说 CentOS 是“社群维护的企业版”呢? Red Hat 公司的 RHEL 释出后，连带会将 SRPM 释出。 社群的朋友就将这些 SRPM 收集起来并重新编译成为所需要的软件，再重复释出成为 CentOS，所以才能号称与 Red Hat 的 RHEL 企业版同步.

RPM 全名是“ RedHat Package Manager ”, 简称则为 RPM . RPM 是以一种数据库记录的方式来将你所需要的软件安装到你的 Linux 系统的一套管理机制。

## yum

yum :  Yellow dog Updater, Modified

### 仓库

```
仓库位于/etc/yum.repos.d

yum repolist enabled # 显示所有启动的仓库
yum repolist disabled # 显示所有禁用的仓库
yum repolist all # 显示所有仓库
```

### epel

EPEL (Extra Packages for Enterprise Linux)是基于 Fedora 的一个项目，为“红帽系”的操作系统提供额外的软件包，适用于 RHEL、CentOS 和 Scientific Linux.

```
yum install epel-release -y
```

### 仓库管理工具 yum-config-manager

```
yum-config-manager --add-repo repository-url 或者直接下载到仓库目录下

删除: 直接删除仓库目录下

修改:
yum-config-manager --enable repository
yum-config-manager --disable repository
```