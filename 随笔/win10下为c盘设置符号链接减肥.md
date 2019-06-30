# win10下为c盘设置符号链接减肥 [190630]

## 1. 备份

将 `C:\Windows\Installer` 中的文件拷贝到其他盘的目录中

如拷贝到 `H:\Installers` 中，注意末尾的 `s`

## 2. 清理

删除 `C:\Windows\Installer` 文件夹

## 3. 建立软链接

在 `H` 盘中新建文件夹 `H:\Installer`

在 **管理员：命令提示符** 中执行以下代码

```bash
mklink /j c:\windows\Installer H:\Installer
```

## 4. 拷贝

将 `H:\Installers` 中文件拷贝到 `H:\Installer` 中

注：*此步推荐使用拷贝而不是剪切，毕竟数据无价*

## 5. 检查

此步可以查看 `C` 盘剩余空间是否下降，如果下降可能是软链接出现问题，建议谷歌解决

重启电脑查看软件启动是否出现问题，快捷方式是否显示不全等

如有问题请回滚

注：*此随笔基于 win10 1903 版本*

## 5. 清理备份

检查无问题，可以删除 `H:\Installers` 文件夹

注：*C:\Windows\Installer* 大小视你所安装的软件大小所决定
