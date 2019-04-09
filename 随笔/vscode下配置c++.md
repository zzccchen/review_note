# vscode下配置c++ [190409]

## 安装 mingw-w64

* 下载 [离线版](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/8.1.0/threads-posix/sjlj/x86_64-8.1.0-release-posix-sjlj-rt_v6-rev0.7z/download) 

* 将解压后的文件夹下的 bin 文件夹路径添加到环境变量

其他说明：

Architecture：系统架构

> 64 位系统选 `x86_64`，32 位选 `i686`

Threads：操作系统 API

> 开发 Windows 程序选 `win32`，开发 Linux、Unix、Mac OS 等其他 posix 协议的操作系统程序选 `posix`

Exception：异常处理模型

> 64 位系统：
>
> * seh：性能优化好，优选
> * sjlj：稳定性好
>
> 32 位系统：
>
> * dwarf：性能优化好
> * sjlj：稳定性好

## 安装 Code Runner 插件

完事~