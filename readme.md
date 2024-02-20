# Android加密算法逆向仓库
为了熟悉常见的加密算法包括
- md5
- bas64
- aes
- rc4

等在 Android 中的使用，准备了这个仓库，通过这个 demo 来熟悉加密算法在汇编中的样式。

## 环境搭建
首先下载预编译好的`openssl-for-ios-android`下载地址
```shell
https://github.com/leenjewel/openssl_for_ios_and_android
```
新建用 一个 as 项目，添加 c++支持，然后在`cmakeLists.txt`中添加依赖库和头文件引入

由于`openssl-for-ios-android`的预编译的`libcrypto.a`依赖于`zlib`我们需要在链接的是时候增加`z` 即可

具体可以参考`cpp/CMakeLists.text`内的注释