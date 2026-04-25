# **Ubuntu关于Qt 版本库不一致的问题**

问题：测试机Qt 库版本是 5.12.8，我编译的QT程序是 Qt 5.15.2

解决思路：

​	方案一：在测试机上安装 Qt 5.15

​	方案二：把我编译的Qt 库复制到测试机：

​			将虚拟机中完整的 x86 版 Qt 5.15.2 库文件（lib）和插件（plugins） 打包， 复制到			测试机，并设置 LD_LIBRARY_PATH 和 QT_PLUGIN_PATH 环境变量，让 程序强制使			用提供的 Qt 版本

​	方案三：静态编译：在虚拟机中静态编译程序，把所有 Qt 库打包进程序：

​			在 .pro 文件中添加：

​			CONFIG += static

​			重新编译。

 

1.直接操作测试机，在测试机上开启 SSH

​	①安装 SSH 服务

​	sudo apt update

​	sudo apt install openssh-server

​	②启动 SSH 服务

​	sudo systemctl start ssh

​	sudo systemctl enable ssh

​	③查看 SSH 状态

​	sudo systemctl status ssh

​	④查看测试机IP 地址

​	ip addr show

 

2.QT程序机查找对应版本的Qt 的库文件位置（找对应版本(我的X86)的 Qt 5.15.2）

​	sudo find / -name "libQt5Core.so.5.15.2" 2>/dev/null

​	我的Qt 库在：/opt/Qt/5.15.2/gcc_64/lib/

 

3.打包库

​	打包 Qt 库

​	tar -czf ~/qt-5.15.2-libs.tar.gz -C /home/boot/sysroot-arm64/opt/qt-5.15.2-arm64/lib .

​	打包 Qt 的 plugins 目录

​	tar -czf ~/qt-5.15.2-x86-plugins.tar.gz -C /opt/Qt/5.15.2/gcc_64 plugins

 

4.复制文件到测试机

​	①复制项目

​	scp ~/LightController boot@测试机IP地址:/home/boot/ 

​	②复制Qt 库打包文件

​	scp ~/qt-5.15.2-x86-plugins.tar.gz boot@测试机IP地址:/home/boot/

​	③复制Qt plugins插件打包文件

​	scp ~/qt-5.15.2-libs.tar.gz boot@测试机IP地址:/home/boot/

 

5.登录测试机器

​	ssh usert@测试机IP地址

 

6.测试机解压库文件

​	①跳转并创建目录

​	cd ~

​	mkdir -p qt-5.15.2-libs

​	cd qt-5.15.2-libs

​	②解压 Qt 库和plugins插件到本地目录

​	tar -xzf ~/qt-5.15.2-x86-libs.tar.gz

​	tar -xzf ~/qt-5.15.2-x86-plugins.tar.gz  //解压 plugins 到库目录

 

 

7..设置环境变量

​	①设置 DISPLAY 变量

​	export DISPLAY=:0

​	②重新设置库路径

​	export LD_LIBRARY_PATH=~/qt-5.15.2-libs:$LD_LIBRARY_PATH

​	export QT_PLUGIN_PATH=~/qt-5.15.2-libs/plugins

8.运行程序

​	~/LightController

 

 

远程登录   ssh user@ip           在远程机器上执行命令

复制文件   scp local_file user@ip:remote_path 通过网络传输文件

解压依赖   tar -xzf             把 Qt 库部署到测试机

指定库路径   export LD_LIBRARY_PATH=...     让程序使用提供的库

指定插件路径 export QT_PLUGIN_PATH=...     让 Qt 找到匹配的插件

指定显示器   export DISPLAY=:0         让 GUI 程序显示在本地屏幕上

 