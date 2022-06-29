本文教各位如何利用git来下载项目代码。工具：git，mingw，cmake，dev c++ ，vscode

工具安装包已经包含在项目文件中，但建议能下载的还是手动去下载，一是版本更新，二是通过手动下载才是完整的学习路径。

# 何为Git

Git是目前应用最广泛的版本控制工具，由Linux之父Linus Torvalds于2005年发布。

# Git下载

下载地址：https://git-scm.com/

安装版本 v2.31.1

<img src="images/gitOW.png" alt="image.png" style="zoom: 33%;" />


点击箭头所示位置下载git

<img src="images/git_install_1.png" alt="image.png" style="zoom:50%;" />

点击Next


<img src="images/git_install_2.png" alt="image.png" style="zoom:50%;" />

选择安装路径，点击Next

<img src="images/git_install_3.png" alt="image.png" style="zoom:50%;" />

默认即可，继续点击Next

<img src="images/git_install_4.png" alt="image.png" style="zoom:50%;" />

此处为创建开始菜单快捷式，若不想创建就勾选左下复选框。继续点击Next

<img src="images/git_install_5.png" alt="image.png" style="zoom:50%;" />

此处选择编辑器，推荐使用默认的vim编辑器。点击Next继续

<img src="images/git_install_6.png" alt="image.png" style="zoom:50%;" />

接下来一路点击Next到结束。

到这里我们git就安装结束了！

<img src="images/git_install_7.png" alt="image.png" style="zoom:50%;" />

到此我们git已经安装完毕。

现在我们来测试一下。Windows+R输入cmd进入命令窗口，输入git出现

<img src="images/git_test.png" alt="image.png" style="zoom:50%;" />

说明我们的git安装成功了。

# 下载项目

新建一个文件夹，在该文件夹下右键

<img src="images/git_clone_1.png" alt="image.png" style="zoom: 50%;" />

在弹出的窗口输入`git clone https://gitee.com/cyberdash/data-structure-c.git`，并按下回车

<img src="images/git_clone_2.png" alt="image.png" style="zoom:50%;" />

如图所示，进度100%时即为下载成功。此时我们查看一下文件夹，发现已经存在项目文件了。

<img src="images/git_clone_3.png" alt="image.png" style="zoom:50%;" />

接下来我们来安装环境

# 编译环境安装

## 安装mingw

下载地址：https://www.mingw-w64.org/downloads/#mingw-builds 或执行项目文件中的安装包。

注意安装完需要将项目目录中bin文件下的mingw32-make.exe改名为make.exe并配置环境变量。[如何设置环境变量](#如何设置环境变量)

### 可能遇到的问题

1. 安装失败

<img src="images/git_make_1.png" alt="image.png" style="zoom:50%;" />

点击安装包右键以管理员形式运行。若此方法还是不成功则复制项目中的MingW.zip文件，解压到磁盘中后再添加环境变量。

## 安装CMake

下载地址：https://cmake.org/
记得勾选添加环境变量。

<img src="images/git_make_2.png" alt="image.png" style="zoom:50%;" />

# Dev C++安装

下载地址：https://sourceforge.net/projects/orwelldevcpp/files/latest/download

安装过程没有什么可说的，一直下一步即可。

安装结束后即可运行项目

# VSCode安装

Dev C++由于历史悠久目前已经停止更新了，我们也可以使用VScode来运行项目。首先到官网下载VScode,地址:https://code.visualstudio.com/

按照提示安装。安装结束后，找到安装扩展的选项，搜索C/C++,CMake,CMake Tools。依次安装扩展。

<img src="images/git_vscode_1.png" alt="image.png" style="zoom:50%;" />

<img src="images/git_vscode_2.png" alt="image.png" style="zoom:33%;" />

<img src="images/git_vscode_3.png" alt="image.png" style="zoom:33%;" />

<img src="images/git_vscode_4.png" alt="image.png" style="zoom:33%;" />

# 在VSCode中运行项目

1. 使用vscode打开项目文件夹，打开VScode，点击打开文件夹。

    <img src="images/git_vscode_5.png" alt="image.png" style="zoom:50%;" />

2. 选择你的项目文件夹，打开后如下所示

    <img src="images/git_vscode_6.png" alt="image.png" style="zoom:50%;" />

3. 我们以第一个文件dp为例，对项目进行编译。

4. 点击Terminal->new Terminal，或者ctrl+shift+ \` 调出下方命令输入框。

<img src="images/git_vscode_7.png" alt="image.png" style="zoom:50%;"/>

首先cd到你想编译的项目目录中，本文以dp为例：输入`cd dp`

再依次输入命令`cmake . -G "Unix Makefiles"` 和 `make`

<img src="images/git_vscode_8.png" alt="image.png" style="zoom:50%;" />

5. 此时在项目中生成出可执行文件，即可运行。

<img src="images/git_vscode_9.png" alt="image.png" style="zoom:50%;"  />

**注意**：若命令执行中出现报错则说明环境安装的有问题，建议重新安装Cmake和MinGW


# 其他

##### 如何设置环境变量

首先复制你想添加环境变量的地址，以mingw为例

找到mingw安装目录中的bin，复制上方地址

<img src="images/git_ospath_1.png" alt="image.png" style="zoom:50%;" />

点击我的电脑右键->属性

<img src="images/git_ospath_2.png" alt="image.png" style="zoom:50%;" />

点击高级系统设置

<img src="images/git_ospath_3.png" alt="image.png" style="zoom:50%;" />

点击环境变量

<img src="images/git_ospath_4.png" alt="image.png" style="zoom:50%;" />

在下方找到Path

双击，在新窗口中点击新建，将刚才复制的路径加到此处。

<img src="images/git_ospath_5.png" alt="image.png" style="zoom:50%;" />

然后点击ok即可。

在cmd中输入make -version

<img src="images/git_ospath_6.png" alt="image.png" style="zoom:50%;" />

出现信息即为添加成功。