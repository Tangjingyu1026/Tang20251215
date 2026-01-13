第一步：在ubuntu设置共享

![image-20260113114806701](F:\git_work\Tang20251215\共享文件夹\window和ubuntu共享.assets\image-20260113114806701.png)



第二步:在window上创建共享文件夹

![image-20260113115035431](F:\git_work\Tang20251215\共享文件夹\window和ubuntu共享.assets\image-20260113115035431.png)

第三步：在虚拟机执行以下命令

①sudo /usr/bin/vmhgfs-fuse .host:/ /mnt -o allow_other -o uid=1000 -o gid=1000 -o umask=022       //输入密码

②cd/mnt/share      //跳转到共享的目录