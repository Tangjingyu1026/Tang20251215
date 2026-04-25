# **ESOP软件安装**

***\*软件一览\****

![img](/ESOP.aeests/ESOP软件安装.assets/wps33.jpg) 

**一.** ***\*JDK\****

***\*Java Development Kit（Java 开发工具包），包含编译、运行 Java 程序的所有工具\*******\*，绝大多数 ESOP 系统后端是用 Java + Spring Boot 写的。你要编译代码、运行程序，就必须有 JDK，没 JDK，Java 代码根本跑不起来。\****

***\*①\*******\*安装 JDK\****

1.把 JDK 放在一个没有中文、没有空格的路径（记住这个路径，后面配置环境变量要用）

![img](F:\git_work\Tang20251215\工作记录\ESOP\ESOP 软件安装.assets\wps34.jpg) 

2.配置 JAVA_HOME

按 Win + R，输入 sysdm.cpl，回车

点击 高级 → 环境变量在系统变量 区域（下半部分）点击 新建

变量名：JAVA_HOME

变量值：填写你 JDK 的路径

找到 Path 变量 → 双击 → 点击 新建 → 添加

![img](F:\git_work\Tang20251215\工作记录\ESOP\ESOP 软件安装.assets\wps35.jpg) 

3. 配置 Path

![img](F:\git_work\Tang20251215\工作记录\ESOP\ESOP 软件安装.assets\wps36.jpg) 

4. 重新打开 CMD 验证

![img](F:\git_work\Tang20251215\工作记录\ESOP\ESOP 软件安装.assets\wps37.jpg) 

***\*②配置JDK（告诉 IDEA 用哪个 Java），作用：\******把****我们****写的高级代码翻译（编译）成电脑能执行的机器码，并让它运行起来。**

打开 IDEA → File → Project Structure → Project Scttings →project →SDK →选我们的版本

![img](F:\git_work\Tang20251215\工作记录\ESOP\ESOP 软件安装.assets\wps38.jpg) 

***\*③配置Maven（告诉 IDEA 用你装的 Maven），作用：自动下载零件自动打包，\****

![img](F:\git_work\Tang20251215\工作记录\ESOP\ESOP 软件安装.assets\wps39.jpg) 

***\*④配置 Maven 阿里云镜像（国内下载依赖快 10 倍）\****

找到F:\ruanjian\ESOPSoftWare\apache-maven-3.9.15\conf\目录找到 settings.xml 文件，添加阿里云镜像配置。

...

 <mirrors>

   <mirror>

​     <id>aliyunmaven</id>

​     <mirrorOf>central</mirrorOf>

​     <name>阿里云公共仓库</name>

​     <url>https://maven.aliyun.com/repository/public</url>

   </mirror>

 </mirrors>

</settings>

![img](F:\git_work\Tang20251215\工作记录\ESOP\ESOP 软件安装.assets\wps40.jpg) 

验证配置是否生效，打开 CMD，执行mvn help:effective-settings

![img](F:\git_work\Tang20251215\工作记录\ESOP\ESOP 软件安装.assets\wps41.jpg) 

***\*⑤安装中文插件\****

File → Settings → Plugins

搜索 Chinese → 安装 Chinese (Simplified) Language Pack

重启 IDEA

**二.** ***\*安装\*******\*Maven\****

***\*Java 项目的依赖管理和构建工具\*******\*,\*******\*ESOP 项目会用到很多第三方 jar 包\*******\*(\*******\*Spring Boot、MySQL驱动、POI导出Excel等\*******\*)\*******\*。Maven 自动下载、管理这些 jar 包\*******\*,\*******\*你不用手动去找\*******\*,\*******\*在 ESOP 开发中的具体作用\**** ***\*1.编译代码 mvn compile\****  ***\*2. 打包成可运行的 jar mvn package\**** ***\*3\**** ***\*.\*******\*管理依赖版本，避免冲突，Maven 让\*******\*我们\*******\*专注写业务代码，不用管 jar 包从哪来。\****

1.把 Maven放在一个没有中文、没有空格的路径（记住这个路径，后面配置环境变量要用）

![img](F:\git_work\Tang20251215\工作记录\ESOP\ESOP 软件安装.assets\wps42.jpg) 

2.配置 Maven 环境变量

第1步：打开环境变量窗口

Win + R → 输入 sysdm.cpl → 回车。点击 高级 → 环境变量

第2步：新建 MAVEN_HOME

变量名 MAVEN_HOME

变量值 F:\ruanjian\ESOPSoftWare\apache-maven-3.9.15

![img](F:\git_work\Tang20251215\工作记录\ESOP\ESOP 软件安装.assets\wps43.jpg) 

第3步：修改 Path

在系统变量区域找到 Path → 双击 → 点击 新建 → 添加：%MAVEN_HOME%\bin，保存

![img](F:\git_work\Tang20251215\工作记录\ESOP\ESOP 软件安装.assets\wps44.jpg) 

五、验证 Maven

mvn -version

![img](F:\git_work\Tang20251215\工作记录\ESOP\ESOP 软件安装.assets\wps45.jpg) 

 

**三．*****\*安装 IntelliJ IDEA\****

***\*Java 开发的主流 IDE（集成开发环境），写代码的地方，可以用记事本写，但没语法提示、不能一键运行、调试很麻烦。为什么 ESOP 需要它？\**** ***\*打开项目、写业务代码、改配置、运行调试、提交代码，全在IDEA 里完成。IDEA 是你写 ESOP 代码的工作台。\****

1.安装 IntelliJ IDEA成功后使用goland激活码破解证书信息

2.具体破解过程看，获取激活码

F:\ruanjian\ESOPSoftWare\goland激活码\goland激活码\windows\windows\windows\2022

3. 填写激活码![img](F:\git_work\Tang20251215\工作记录\ESOP\ESOP 软件安装.assets\wps46.jpg)

**四．*****\*安装 Postman，\****

***\*API 接口测试工具，用来测试写的 ESOP 接口，写完接口后，测试能不能正常返回数据\****

**五．** ***\*Navicat 15\****

***\*MySQL/PostgreSQL 数据库管理工具，看数据库表\**** ***\*需要查数据库里的员工、持股数据\****

![img](F:\git_work\Tang20251215\工作记录\ESOP\ESOP 软件安装.assets\wps47.jpg) 

***\*①安装Navicat（断网装）\****

***\*②\*******\*破解\****

以管理员身份运行Navicat Keygen Patch v5.6.0 DFoX.exe

***\*③注册成功\****

![img](F:\git_work\Tang20251215\工作记录\ESOP\ESOP 软件安装.assets\wps48.jpg) 

**六．*****\*安装Another Redis Desktop Manager\**** ***\*查看 Redis 缓存\****

 

| ***\*软件\**** | ***\*一句话作用\****         |                            |
| -------------- | ---------------------------- | -------------------------- |
| JDK            | 让 Java 代码能跑起来         |                            |
| Maven          | 自动下载 jar 包 + 打包项目   |                            |
| IDEA           | 写代码的工作台               |                            |
| Postman        | 测试你写的接口               |                            |
| Navicat        | 看数据库里的数据             |                            |
| Redis Desktop  | 看缓存里的数据               |                            |
|                |                              |                            |
| ***\*步骤\**** | ***\*做什么\****             | ***\*用什么软件\****       |
| 1              | 写查询逻辑                   | IDEA                       |
| 2              | 启动项目测试                 | JDK（运行）+ Maven（编译） |
| 3              | 看看数据库里有没有这个员工   | Navicat                    |
| 4              | 用接口测试工具调一下你的接口 | Postman                    |
| 5              | 如果需要查缓存里有没有数据   | Redis Desktop              |

 

# **ESOP软件安装**

***\*软件一览\****

![img](F:\git_work\Tang20251215\工作记录\ESOP\ESOP 软件安装.assets\wps33-1777118938695-84.jpg) 

**一.** ***\*JDK\****

***\*Java Development Kit（Java 开发工具包），包含编译、运行 Java 程序的所有工具\*******\*，绝大多数 ESOP 系统后端是用 Java + Spring Boot 写的。你要编译代码、运行程序，就必须有 JDK，没 JDK，Java 代码根本跑不起来。\****

***\*①\*******\*安装 JDK\****

1.把 JDK 放在一个没有中文、没有空格的路径（记住这个路径，后面配置环境变量要用）

![img](F:\git_work\Tang20251215\工作记录\ESOP\ESOP 软件安装.assets\wps34-1777118938695-83.jpg) 

2.配置 JAVA_HOME

按 Win + R，输入 sysdm.cpl，回车

点击 高级 → 环境变量在系统变量 区域（下半部分）点击 新建

变量名：JAVA_HOME

变量值：填写你 JDK 的路径

找到 Path 变量 → 双击 → 点击 新建 → 添加

![img](F:\git_work\Tang20251215\工作记录\ESOP\ESOP 软件安装.assets\wps35-1777118938695-86.jpg) 

3. 配置 Path

![img](F:\git_work\Tang20251215\工作记录\ESOP\ESOP 软件安装.assets\wps36-1777118938695-85.jpg) 

4. 重新打开 CMD 验证

![img](F:\git_work\Tang20251215\工作记录\ESOP\ESOP 软件安装.assets\wps37-1777118938695-88.jpg) 

***\*②配置JDK（告诉 IDEA 用哪个 Java），作用：\******把****我们****写的高级代码翻译（编译）成电脑能执行的机器码，并让它运行起来。**

打开 IDEA → File → Project Structure → Project Scttings →project →SDK →选我们的版本

![img](F:\git_work\Tang20251215\工作记录\ESOP\ESOP 软件安装.assets\wps38-1777118938695-87.jpg) 

***\*③配置Maven（告诉 IDEA 用你装的 Maven），作用：自动下载零件自动打包，\****

![img](F:\git_work\Tang20251215\工作记录\ESOP\ESOP 软件安装.assets\wps39-1777118938695-89.jpg) 

***\*④配置 Maven 阿里云镜像（国内下载依赖快 10 倍）\****

找到F:\ruanjian\ESOPSoftWare\apache-maven-3.9.15\conf\目录找到 settings.xml 文件，添加阿里云镜像配置。

...

 <mirrors>

   <mirror>

​     <id>aliyunmaven</id>

​     <mirrorOf>central</mirrorOf>

​     <name>阿里云公共仓库</name>

​     <url>https://maven.aliyun.com/repository/public</url>

   </mirror>

 </mirrors>

</settings>

![img](F:\git_work\Tang20251215\工作记录\ESOP\ESOP 软件安装.assets\wps40-1777118938695-90.jpg) 

验证配置是否生效，打开 CMD，执行mvn help:effective-settings

![img](F:\git_work\Tang20251215\工作记录\ESOP\ESOP 软件安装.assets\wps41-1777118938695-91.jpg) 

***\*⑤安装中文插件\****

File → Settings → Plugins

搜索 Chinese → 安装 Chinese (Simplified) Language Pack

重启 IDEA

**二.** ***\*安装\*******\*Maven\****

***\*Java 项目的依赖管理和构建工具\*******\*,\*******\*ESOP 项目会用到很多第三方 jar 包\*******\*(\*******\*Spring Boot、MySQL驱动、POI导出Excel等\*******\*)\*******\*。Maven 自动下载、管理这些 jar 包\*******\*,\*******\*你不用手动去找\*******\*,\*******\*在 ESOP 开发中的具体作用\**** ***\*1.编译代码 mvn compile\****  ***\*2. 打包成可运行的 jar mvn package\**** ***\*3\**** ***\*.\*******\*管理依赖版本，避免冲突，Maven 让\*******\*我们\*******\*专注写业务代码，不用管 jar 包从哪来。\****

1.把 Maven放在一个没有中文、没有空格的路径（记住这个路径，后面配置环境变量要用）

![img](F:\git_work\Tang20251215\工作记录\ESOP\ESOP 软件安装.assets\wps42-1777118938695-92.jpg) 

2.配置 Maven 环境变量

第1步：打开环境变量窗口

Win + R → 输入 sysdm.cpl → 回车。点击 高级 → 环境变量

第2步：新建 MAVEN_HOME

变量名 MAVEN_HOME

变量值 F:\ruanjian\ESOPSoftWare\apache-maven-3.9.15

![img](F:\git_work\Tang20251215\工作记录\ESOP\ESOP 软件安装.assets\wps43-1777118938695-93.jpg) 

第3步：修改 Path

在系统变量区域找到 Path → 双击 → 点击 新建 → 添加：%MAVEN_HOME%\bin，保存

![img](F:\git_work\Tang20251215\工作记录\ESOP\ESOP 软件安装.assets\wps44-1777118938695-94.jpg) 

五、验证 Maven

mvn -version

![img](F:\git_work\Tang20251215\工作记录\ESOP\ESOP 软件安装.assets\wps45-1777118938695-95.jpg) 

 

**三．*****\*安装 IntelliJ IDEA\****

***\*Java 开发的主流 IDE（集成开发环境），写代码的地方，可以用记事本写，但没语法提示、不能一键运行、调试很麻烦。为什么 ESOP 需要它？\**** ***\*打开项目、写业务代码、改配置、运行调试、提交代码，全在IDEA 里完成。IDEA 是你写 ESOP 代码的工作台。\****

1.安装 IntelliJ IDEA成功后使用goland激活码破解证书信息

2.具体破解过程看，获取激活码

F:\ruanjian\ESOPSoftWare\goland激活码\goland激活码\windows\windows\windows\2022

3. 填写激活码![img](F:\git_work\Tang20251215\工作记录\ESOP\ESOP 软件安装.assets\wps46-1777118938695-96.jpg)

**四．*****\*安装 Postman，\****

***\*API 接口测试工具，用来测试写的 ESOP 接口，写完接口后，测试能不能正常返回数据\****

**五．** ***\*Navicat 15\****

***\*MySQL/PostgreSQL 数据库管理工具，看数据库表\**** ***\*需要查数据库里的员工、持股数据\****

![img](F:\git_work\Tang20251215\工作记录\ESOP\ESOP 软件安装.assets\wps47-1777118938695-97.jpg) 

***\*①安装Navicat（断网装）\****

***\*②\*******\*破解\****

以管理员身份运行Navicat Keygen Patch v5.6.0 DFoX.exe

***\*③注册成功\****

![img](F:\git_work\Tang20251215\工作记录\ESOP\ESOP 软件安装.assets\wps48-1777118938695-98.jpg) 

**六．*****\*安装Another Redis Desktop Manager\**** ***\*查看 Redis 缓存\****

 

| ***\*软件\**** | ***\*一句话作用\****         |                            |
| -------------- | ---------------------------- | -------------------------- |
| JDK            | 让 Java 代码能跑起来         |                            |
| Maven          | 自动下载 jar 包 + 打包项目   |                            |
| IDEA           | 写代码的工作台               |                            |
| Postman        | 测试你写的接口               |                            |
| Navicat        | 看数据库里的数据             |                            |
| Redis Desktop  | 看缓存里的数据               |                            |
|                |                              |                            |
| ***\*步骤\**** | ***\*做什么\****             | ***\*用什么软件\****       |
| 1              | 写查询逻辑                   | IDEA                       |
| 2              | 启动项目测试                 | JDK（运行）+ Maven（编译） |
| 3              | 看看数据库里有没有这个员工   | Navicat                    |
| 4              | 用接口测试工具调一下你的接口 | Postman                    |
| 5              | 如果需要查缓存里有没有数据   | Redis Desktop              |

 

  