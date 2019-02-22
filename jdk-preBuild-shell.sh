#!/bin/sh

# 语言设置，必须
export LANG=C

# BootStrap JDK安装路径
export ALT_BOOTDIR=/usr/lib/java/jdk1.7.0_80
#export ALT_BOOTDIR=/usr/lib/java/jdk1.6.0_45

# 允许自动下载依赖
export ALLOW_DOWNLOADS=true

# 并行编译的线程数，设置为和CPU核数一致即可(我这里是2)
export HOTSPOT_BUILD_JOBS=2
export ALT_PARALLEL_COMPILE_JOBS=2

# 比较本次build出来的映像与先前版本的差异。这对我们来说没有意义，
# 必须设置为false，否则sanity检查会报缺少先前版本JDK的映像的错误提示。
# 如果已经设置dev或者DEV_ONLY=true，这个不显式设置也行
export SKIP_COMPARE_IMAGES=true

#使用预编译头文件，不加这个编译会更慢一些
export USE_PRECOMPILED_HEADER=true

#要编译的内容，可以自行选择
export BUILD_LANGTOOLS=true
#export BUILD_JAXWS=false
#export BUILD_JAXP=false
#export BUILD_CORBA=false
export BUILD_HOTSPOT=true
export BUILD_JDK=true

# 要编译的版本
#export SKIP_DEBUG_BUILD=false
#export SKIP_FASTDEBUG_BUILD=true
#export DEBUG_NAME=debug

# 设置为false，可以避开javaws和浏览器Java插件之类的部分的build
BUILD_DEPLOY=false

# 把它设置为false就不会build出安装包。因为安装包里有些奇怪的依赖，
# 但即便不build出它也已经能得到完整的JDK映像，所以还是别build它好了
BUILD_INSTALL=false

#编译结果存放的路径，建议存放在openjdk源码中build文件夹
export ALT_OUTPUTDIR=/home/top/workspace/openjdk7/build

#这两个环境变量需要去掉，不然会出问题
unset JAVA_HOME
unset CLASSPATH

# 手动下载的依赖包路径
export ALT_DROPS_DIR=/home/top/workspace/openjdk7/drop

#make 2>&1 | tee $ALT_OUTPUTDIR/build.log

echo "shell has been successfully executed!"
