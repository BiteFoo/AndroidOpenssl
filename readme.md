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

## 自己编译zlib等
这里再补充一个如何编译`openssl curl zlib`等静态库，我们下载仓库
```shell
https://github.com/MajdiSobain/build-curl-openssl-zlib-android
```
执行模块更新时可能出现无法下载`zlib openssl`等，此时我们考虑自己动手下载
```shell
➜  build-curl-openssl-zlib-android git:(master) ✗ rm -rf zlib
➜  build-curl-openssl-zlib-android git:(master) ✗ git clone https://github.com/madler/zlib
正克隆到 'zlib'...
remote: Enumerating objects: 6508, done.
remote: Counting objects: 100% (2438/2438), done.
remote: Compressing objects: 100% (385/385), done.
remote: Total 6508 (delta 2176), reused 2137 (delta 2045), pack-reused 4070
接收对象中: 100% (6508/6508), 4.23 MiB | 6.54 MiB/s, 完成.
处理 delta 中: 100% (4608/4608), 完成.
➜  build-curl-openssl-zlib-android git:(master) ✗ cd building-scripts
➜  building-scripts git:(master) ✗ ./build-zlib.sh /User/CC/Library/Android/sdk/ndk/23.1.7779620  api=24 arch=arm64
###################################################
#
# Build zlib for android-24 arch arm64
#
###################################################
make: *** No rule to make target `clean'.  Stop.
Checking for gcc...
Checking for shared library support...
Building shared library libz.1.3.1.1-motley.dylib with gcc.
Checking for size_t... Yes.
Checking for off64_t... No.
Checking for fseeko... Yes.
Checking for strerror... Yes.
Checking for unistd.h... Yes.
Checking for stdarg.h... Yes.
Checking whether to use vs[n]printf() or s[n]printf()... using vs[n]printf().
Checking for vsnprintf() in stdio.h... Yes.
Checking for return value of vsnprintf()... Yes.
Checking for attribute(visibility) support... Yes.
gcc -O3 -DHAVE_HIDDEN -I. -c -o example.o test/example.c
gcc -O3 -DHAVE_HIDDEN  -c -o adler32.o adler32.c
gcc -O3 -DHAVE_HIDDEN  -c -o crc32.o crc32.c
gcc -O3 -DHAVE_HIDDEN  -c -o deflate.o deflate.c
gcc -O3 -DHAVE_HIDDEN  -c -o infback.o infback.c
gcc -O3 -DHAVE_HIDDEN  -c -o inffast.o inffast.c
gcc -O3 -DHAVE_HIDDEN  -c -o inflate.o inflate.c
gcc -O3 -DHAVE_HIDDEN  -c -o inftrees.o inftrees.c
gcc -O3 -DHAVE_HIDDEN  -c -o trees.o trees.c
gcc -O3 -DHAVE_HIDDEN  -c -o zutil.o zutil.c
gcc -O3 -DHAVE_HIDDEN  -c -o compress.o compress.c
gcc -O3 -DHAVE_HIDDEN  -c -o uncompr.o uncompr.c
gcc -O3 -DHAVE_HIDDEN  -c -o gzclose.o gzclose.c
gcc -O3 -DHAVE_HIDDEN  -c -o gzlib.o gzlib.c
gcc -O3 -DHAVE_HIDDEN  -c -o gzread.o gzread.c
gcc -O3 -DHAVE_HIDDEN  -c -o gzwrite.o gzwrite.c
libtool -o libz.a adler32.o crc32.o deflate.o infback.o inffast.o inflate.o inftrees.o trees.o zutil.o compress.o uncompr.o gzclose.o gzlib.o gzread.o gzwrite.o
gcc -O3 -DHAVE_HIDDEN  -o example example.o -L. libz.a
gcc -O3 -DHAVE_HIDDEN -I. -c -o minigzip.o test/minigzip.c
gcc -O3 -DHAVE_HIDDEN  -o minigzip minigzip.o -L. libz.a
gcc -O3 -fPIC -DHAVE_HIDDEN  -DPIC -c -o objs/adler32.o adler32.c
gcc -O3 -fPIC -DHAVE_HIDDEN  -DPIC -c -o objs/crc32.o crc32.c
gcc -O3 -fPIC -DHAVE_HIDDEN  -DPIC -c -o objs/deflate.o deflate.c
gcc -O3 -fPIC -DHAVE_HIDDEN  -DPIC -c -o objs/infback.o infback.c
gcc -O3 -fPIC -DHAVE_HIDDEN  -DPIC -c -o objs/inffast.o inffast.c
gcc -O3 -fPIC -DHAVE_HIDDEN  -DPIC -c -o objs/inflate.o inflate.c
gcc -O3 -fPIC -DHAVE_HIDDEN  -DPIC -c -o objs/inftrees.o inftrees.c
gcc -O3 -fPIC -DHAVE_HIDDEN  -DPIC -c -o objs/trees.o trees.c
gcc -O3 -fPIC -DHAVE_HIDDEN  -DPIC -c -o objs/zutil.o zutil.c
gcc -O3 -fPIC -DHAVE_HIDDEN  -DPIC -c -o objs/compress.o compress.c
gcc -O3 -fPIC -DHAVE_HIDDEN  -DPIC -c -o objs/uncompr.o uncompr.c
gcc -O3 -fPIC -DHAVE_HIDDEN  -DPIC -c -o objs/gzclose.o gzclose.c
gcc -O3 -fPIC -DHAVE_HIDDEN  -DPIC -c -o objs/gzlib.o gzlib.c
gcc -O3 -fPIC -DHAVE_HIDDEN  -DPIC -c -o objs/gzread.o gzread.c
gcc -O3 -fPIC -DHAVE_HIDDEN  -DPIC -c -o objs/gzwrite.o gzwrite.c
gcc -dynamiclib -install_name /User/CC/Desktop/AndroidCode/build-curl-openssl-zlib-android/zlib/../prebuilt-libs/zlib/android-24/arm64/lib/libz.1.dylib -compatibility_version 1 -current_version 1.3.1 -O3 -fPIC -DHAVE_HIDDEN -o libz.1.3.1.1-motley.dylib adler32.lo crc32.lo deflate.lo infback.lo inffast.lo inflate.lo inftrees.lo trees.lo zutil.lo compress.lo uncompr.lo gzclose.lo gzlib.lo gzread.lo gzwrite.lo  -lc
rm -f libz.dylib libz.1.dylib
ln -s libz.1.3.1.1-motley.dylib libz.dylib
ln -s libz.1.3.1.1-motley.dylib libz.1.dylib
gcc -O3 -DHAVE_HIDDEN -o examplesh example.o  -L. libz.1.3.1.1-motley.dylib
gcc -O3 -DHAVE_HIDDEN -o minigzipsh minigzip.o  -L. libz.1.3.1.1-motley.dylib
rm -f /User/CC/Desktop/AndroidCode/build-curl-openssl-zlib-android/zlib/../prebuilt-libs/zlib/android-24/arm64/lib/libz.a
cp libz.a /User/CC/Desktop/AndroidCode/build-curl-openssl-zlib-android/zlib/../prebuilt-libs/zlib/android-24/arm64/lib
chmod 644 /User/CC/Desktop/AndroidCode/build-curl-openssl-zlib-android/zlib/../prebuilt-libs/zlib/android-24/arm64/lib/libz.a
cp libz.1.3.1.1-motley.dylib /User/CC/Desktop/AndroidCode/build-curl-openssl-zlib-android/zlib/../prebuilt-libs/zlib/android-24/arm64/lib
chmod 755 /User/CC/Desktop/AndroidCode/build-curl-openssl-zlib-android/zlib/../prebuilt-libs/zlib/android-24/arm64/lib/libz.1.3.1.1-motley.dylib
rm -f /User/CC/Desktop/AndroidCode/build-curl-openssl-zlib-android/zlib/../prebuilt-libs/zlib/android-24/arm64/share/man/man3/zlib.3
cp zlib.3 /User/CC/Desktop/AndroidCode/build-curl-openssl-zlib-android/zlib/../prebuilt-libs/zlib/android-24/arm64/share/man/man3
chmod 644 /User/CC/Desktop/AndroidCode/build-curl-openssl-zlib-android/zlib/../prebuilt-libs/zlib/android-24/arm64/share/man/man3/zlib.3
rm -f /User/CC/Desktop/AndroidCode/build-curl-openssl-zlib-android/zlib/../prebuilt-libs/zlib/android-24/arm64/lib/pkgconfig/zlib.pc
cp zlib.pc /User/CC/Desktop/AndroidCode/build-curl-openssl-zlib-android/zlib/../prebuilt-libs/zlib/android-24/arm64/lib/pkgconfig
chmod 644 /User/CC/Desktop/AndroidCode/build-curl-openssl-zlib-android/zlib/../prebuilt-libs/zlib/android-24/arm64/lib/pkgconfig/zlib.pc
rm -f /User/CC/Desktop/AndroidCode/build-curl-openssl-zlib-android/zlib/../prebuilt-libs/zlib/android-24/arm64/include/zlib.h /User/CC/Desktop/AndroidCode/build-curl-openssl-zlib-android/zlib/../prebuilt-libs/zlib/android-24/arm64/include/zconf.h
cp zlib.h zconf.h /User/CC/Desktop/AndroidCode/build-curl-openssl-zlib-android/zlib/../prebuilt-libs/zlib/android-24/arm64/include
chmod 644 /User/CC/Desktop/AndroidCode/build-curl-openssl-zlib-android/zlib/../prebuilt-libs/zlib/android-24/arm64/include/zlib.h /User/CC/Desktop/AndroidCode/build-curl-openssl-zlib-android/zlib/../prebuilt-libs/zlib/android-24/arm64/include/zconf.h
```
编译好的结果在`prebuilt-libs`下载对应的架构内
```shell
➜  prebuilt-libs git:(master) ✗ ls
README.md zlib
```