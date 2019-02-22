# openjdk7

该项目用于编译OpenJDK7

## 一、获取源码

编译的OpenJDK7源码：[openjdk-7-fcs-src-b147-27_jun_2011.zip](http://download.java.net/openjdk/jdk7/promoted/b147/openjdk-7-fcs-src-b147-27_jun_2011.zip)


---

## 二、编译环境

- Ubuntu 18.04LTS
- gcc 7.3.0
- GNU Make 4.1

其他环境配置如下：

#### 1.Bootstrap JDK

使用jdk1.7.0_80

#### 2.编译前安装

- 2.1 一键安装依赖

```shell
sudo apt-get install build-essential gawk m4 libasound2-dev libcups2-dev libxrender-dev xorg-dev xutils-dev x11proto-print-dev binutils libmotif3 libmotif-dev
```

> 其中libmotif3安装时，出现问题

```
E: Package 'libmotif3' has no installation candidate
```

选择手动下载[libmotif3](https://debian.pkgs.org/8/debian-main-amd64/libmotif3_2.3.4-6+deb8u1_amd64.deb.html)安装

```shell
sudo dpkg -i libmotif3_2.3.4-6+deb8u1_amd64.deb
```

- 2.2 ant

这里ant选择了手动安装（当然使用apt-get也可以），由于Bootstrap JDK是JDK1.7，而ant-1.10.x要求最低是JDK1.8，所以这里没有使用ant-1.10.x，选择使用[apache-ant-1.9.13](https://ant.apache.org/bindownload.cgi)

```shell
# 解压安装
tar -zxvf apache-ant-1.9.13-bin.tar.gz -C /opt
# 配置环境变量
sudo subl ~/.profile

# 配置如下
export ANT_HOME=/opt/apache-ant-1.9.13
export PATH=$PATH:$ANT_HOME/bin
```

#### 3.环境脚本

编译前需要设置环境变量（在当前shell窗口生效即可，不影响全局环境）

```shell
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
```


---

## 三、编译

```shell
$ env

# 设置的环境变量只在当前shell窗口有效，所以需要在该窗口完成make
$ source jdk-preBuild-shell.sh
shell has been successfully executed!

# 对比检查环境是否设置成功
$ env

$ make sanity
Sanity check passed.

# 编译
$ make
```

编译会多次报错中断，增量编译即可。成功如下：

```
-- Build times ----------
Target all_product_build
Start 2019-02-22 15:37:26
End   2019-02-22 15:44:55
00:00:05 corba
00:00:04 hotspot
00:00:02 jaxp
00:00:03 jaxws
00:07:13 jdk
00:00:02 langtools
00:07:29 TOTAL
```


---

## 四、问题

编译中出现很多问题，记录如下

### 问题1.部分依赖包下载不了

```shell
-jaf_src-url-bundle:
     [echo] Downloading from https://java.net/downloads/jax-ws/JDK7/jdk7-jaf-2010_08_19.zip
      [get] Getting: https://java.net/downloads/jax-ws/JDK7/jdk7-jaf-2010_08_19.zip
      [get] To: /home/top/workspace/openjdk7/build/jaxws/drop/bundles/jdk7-jaf-2010_08_19.zip.temp
      [get] https://java.net/downloads/jax-ws/JDK7/jdk7-jaf-2010_08_19.zip moved to http://www.oracle.com/splash/java.net/maintenance/index.html

BUILD FAILED
/home/top/workspace/openjdk7/build/jaxws/build/xml_generated/build-drop-jaf_src.xml:96: Redirection detected from https to http. Protocol switch unsafe, not allowed.
```

需要手动下载文件[jdk7-jaf-2010_08_19.zip](https://netix.dl.sourceforge.net/project/jdk7src/input-archives/jdk7-jaf-2010_08_19.zip)，置于openjdk7/drop目录（新建）下，并在环境变量sh中加入以下配置（如果还缺失其他包，同样处理）：

```shell
# 手动下载的依赖包路径
export ALT_DROPS_DIR=/home/top/workspace/openjdk7/drop
```

### 问题2.不支持内核版本

```shell
make[5]: Entering directory '/home/top/workspace/openjdk7/build/hotspot/outputdir'
>&2 echo "*** This OS is not supported:" `uname -a`; exit 1;
*** This OS is not supported: Linux top-ThinkPad-E450 4.15.0-45-generic #48-Ubuntu SMP Tue Jan 29 16:28:13 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux
/home/top/workspace/openjdk7/hotspot/make/linux/Makefile:239: recipe for target 'check_os_version' failed
```

查看openjdk7/hotspot/make/linux/Makefile中OS检查的相关内容：

```shell
checks: check_os_version check_j2se_version

# We do not want people accidentally building on old systems (e.g. Linux 2.2.x,
# Solaris 2.5.1, 2.6).
# Disable this check by setting DISABLE_HOTSPOT_OS_VERSION_CHECK=ok.

SUPPORTED_OS_VERSION = 2.4% 2.5% 2.6% 2.7%
OS_VERSION := $(shell uname -r)
EMPTY_IF_NOT_SUPPORTED = $(filter $(SUPPORTED_OS_VERSION),$(OS_VERSION))

check_os_version:
ifeq ($(DISABLE_HOTSPOT_OS_VERSION_CHECK)$(EMPTY_IF_NOT_SUPPORTED),)
    $(QUIETLY) >&2 echo "*** This OS is not supported:" `uname -a`; exit 1;
endif
```

> 解决1：可以在SUPPORTED_OS_VERSION中增加内核版本

```shell
# 查看系统内核版本
$ uname -r
4.15.0-45-generic

# 所以可以修改上述Makefile为：
SUPPORTED_OS_VERSION = 2.4% 2.5% 2.6% 2.7% 4%
```

> 解决2：跳过检查，即注释掉相关内容

```shell
check_os_version:
#ifeq ($(DISABLE_HOTSPOT_OS_VERSION_CHECK)$(EMPTY_IF_NOT_SUPPORTED),)
#    $(QUIETLY) >&2 echo "*** This OS is not supported:" `uname -a`; exit 1;
#endif
```

### 问题3.-Werror报错

包括-Werror=literal-suffix、-Werror=deprecated-declarations

```shell
/home/top/workspace/openjdk7/hotspot/src/share/vm/memory/threadLocalAllocBuffer.inline.hpp:97:25: error: invalid suffix on literal; C++11 requires a space between literal and string macro [-Werror=literal-suffix]
     gclog_or_tty->print("TLAB: %s thread: "INTPTR_FORMAT" [id: %2d]"

/home/top/workspace/openjdk7/hotspot/src/os/linux/vm/os_linux.inline.hpp:154:18: error: 'int readdir_r(DIR*, dirent*, dirent**)' is deprecated [-Werror=deprecated-declarations]
   if((status = ::readdir_r(dirp, dbuf, &p)) != 0) {
```

在hotspot/make/linux/makefiles/gcc.make文件中找到WARNINGS_ARE_ERRORS = -Werro，注释该段或改成WARNINGS_ARE_ERRORS = -Wno-all。再编译就会忽略掉警告，直到编译完成。

### 问题4.头文件宏定义冲突

cdefs.h中定义的宏"LEAF"与interfaceSupport.hpp冲突

```shell
/home/top/workspace/openjdk7/hotspot/src/share/vm/runtime/interfaceSupport.hpp:430:0: error: "__LEAF" redefined [-Werror]
 #define __LEAF(result_type, header)
```

可以在interfaceSupport.hpp中增加"#undef LEAF"语句来解决冲突（也有说打补丁的，未实测）

```c
subl /home/top/workspace/openjdk7/hotspot/src/share/vm/runtime/interfaceSupport.hpp

#ifdef __LEAF 
#undef __LEAF 
#define __LEAF(result_type, header)     \
  TRACE_CALL(result_type, header)       \
  debug_only(NoHandleMark __hm;)        \
  /* begin of body */ 
#endif 
```

### 问题5.-fpermissive报错

```shell
/home/top/workspace/openjdk7/hotspot/src/share/vm/code/dependencies.hpp:161:49: error: left operand of shift expression '(-1 << 1)' is negative [-fpermissive]
     all_types      = ((1<<TYPE_LIMIT)-1) & ((-1)<<FIRST_TYPE),
```

参考[PATCH resend2 Use (~0u) instead of (-1) when left-shifting](http://mail.openjdk.java.net/pipermail/hotspot-dev/2016-June/023387.html)。将-1改成~0u

```c
-    all_types           = ((1 << TYPE_LIMIT) - 1) & ((-1) << FIRST_TYPE),
+    all_types           = ((1 << TYPE_LIMIT) - 1) & ((~0u) << FIRST_TYPE),
```

### 问题6.'operator""tag'

```shell
/home/top/workspace/openjdk7/hotspot/src/share/vm/utilities/globalDefinitions.hpp:1200:45: error: unable to find string literal operator 'operator""tag' with 'const char [58]', 'long unsigned int' arguments
 #define UINT64_FORMAT "%" FORMAT64_MODIFIER "u"

/home/top/workspace/openjdk7/hotspot/src/share/vm/gc_implementation/g1/concurrentMark.cpp:4554:65: error: unable to find string literal operator 'operator""tag' with 'const char [93]', 'long unsigned int' arguments
 #define G1PPRL_SUM_MB_PERC_FORMAT(tag) G1PPRL_SUM_MB_FORMAT(tag)" / %1.2f %%"
```

参考[PATCH RFC 3/5 fix build errors with gcc6](http://mail.openjdk.java.net/pipermail/build-dev/2016-May/017170.html)，基本也是格式问题（修改concurrentMark即可）

```c
// For per-region info
 #define G1PPRL_TYPE_FORMAT            "   %-4s"
 #define G1PPRL_TYPE_H_FORMAT          "   %4s"
-#define G1PPRL_BYTE_FORMAT            "  "SIZE_FORMAT_W(9)
+#define G1PPRL_BYTE_FORMAT            "  " SIZE_FORMAT_W(9)
 #define G1PPRL_BYTE_H_FORMAT          "  %9s"
 #define G1PPRL_DOUBLE_FORMAT          "  %14.1f"
 #define G1PPRL_DOUBLE_H_FORMAT        "  %14s"
 
 // For summary info
-#define G1PPRL_SUM_ADDR_FORMAT(tag)    "  "tag":"G1PPRL_ADDR_BASE_FORMAT
-#define G1PPRL_SUM_BYTE_FORMAT(tag)    "  "tag": "SIZE_FORMAT
-#define G1PPRL_SUM_MB_FORMAT(tag)      "  "tag": %1.2f MB"
-#define G1PPRL_SUM_MB_PERC_FORMAT(tag) G1PPRL_SUM_MB_FORMAT(tag)" / %1.2f %%"
+#define G1PPRL_SUM_ADDR_FORMAT(tag)    "  " tag ":" G1PPRL_ADDR_BASE_FORMAT
+#define G1PPRL_SUM_BYTE_FORMAT(tag)    "  " tag ": " SIZE_FORMAT
+#define G1PPRL_SUM_MB_FORMAT(tag)      "  " tag ": %1.2f MB"
+#define G1PPRL_SUM_MB_PERC_FORMAT(tag) G1PPRL_SUM_MB_FORMAT(tag) " / %1.2f %%"
```

### 问题7.cannot convert 'bool' to 'methodOop {aka methodOopDesc*}'

```shell
/home/top/workspace/openjdk7/hotspot/src/share/vm/oops/constantPoolOop.cpp:272:39: error: cannot convert 'bool' to 'methodOop {aka methodOopDesc*}' in return
   if (cpool->cache() == NULL)  return false;  // nothing to load yet
```

修改constantPoolOop.cpp第272行代码

```c
-  if (cpool->cache() == NULL)  return false;
+  if (cpool->cache() == NULL)  return (methodOop)false;
```

### 问题8.cannot convert 'bool' to 'Node*'

```shell
/home/top/workspace/openjdk7/hotspot/src/share/vm/opto/loopnode.cpp:896:49: error: cannot convert 'bool' to 'Node*' in return
   if (expr == NULL || expr->req() != 3)  return false;
```

解决方式同上，对loopnode.cpp做如下修改

```c
-  if (expr == NULL || expr->req() != 3)  return false;
+  if (expr == NULL || expr->req() != 3)  return (Node*)false;
```

### 问题9.'operator""OBJ'

也是字符串跟变量连接时，需要增加一个空格

```shell
/home/top/workspace/openjdk7/hotspot/src/share/vm/prims/unsafe.cpp:1268:17: error: unable to find string literal operator 'operator""OBJ' with 'const char [40]', 'long unsigned int' arguments
 #define CLS LANG"Class;"
```

参考[PATCH RFC 3/5 fix build errors with gcc6](http://mail.openjdk.java.net/pipermail/build-dev/2016-May/017171.html)的修改方式，修改unsafe.cpp，具体修改参见github

### 问题10.libjvm.so文件未定义

```shell
Using java runtime at: /usr/lib/java/jdk1.7.0_80/jre
Error occurred during initialization of VM
Unable to load native library: /usr/lib/java/jdk1.7.0_80/jre/lib/amd64/libjava.so: symbol JVM_SetNativeThreadName version SUNWprivate_1.1 not defined in file libjvm.so with link time reference
```

注释掉hotspot/make/linux/Makefile中的所有test_gamma（即删掉所有的&& ./test_gamma）

### 问题11.-mimpure-text

```shell
gcc: error: unrecognized command line option '-mimpure-text'
```

gcc版本问题，这个命令在本机所用的7.3.0版的gcc中已经去除。所以只能注释掉该命令了

```shell
subl /home/top/workspace/openjdk7/jdk/make/common/shared/Compiler-gcc.gmk

- SHARED_LIBRARY_FLAG = -shared -mimpure-text
+ SHARED_LIBRARY_FLAG = -shared #-mimpure-text
```

### 问题12.时间超过十年问题

```shell
    < ../../../src/share/classes/java/util/CurrencyData.properties
Error: time is more than 10 years from present: 1136059200000
java.lang.RuntimeException: time is more than 10 years from present: 1136059200000
```

今年是19年，把该文件中所有时间改成09年之后即可

```shell
subl /home/top/workspace/openjdk7/jdk/src/share/classes/java/util/CurrencyData.properties
```

### 问题13.找不到libjsoundalsa.so

```shell
collect2: error: ld returned 1 exit status
../../../common/Library.gmk:221: recipe for target '/home/top/workspace/openjdk7/build/lib/amd64/libjsoundalsa.so' failed
make[5]: *** [/home/top/workspace/openjdk7/build/lib/amd64/libjsoundalsa.so] Error 1
```

创建libjsoundalsa.so如下

```shell
cp /home/top/workspace/openjdk7/build/lib/amd64/libjsound.so /home/top/workspace/openjdk7/build/lib/amd64/libjsoundalsa.so
```

### 问题14.cannot convert 'bool' to 'jobject'

```
../../../../../src/share/native/com/sun/java/util/jar/pack/jni.cpp: In function '_jobject* Java_com_sun_java_util_jar_pack_NativeUnpack_getUnusedInput(JNIEnv*, jobject)':
../../../../../src/share/native/com/sun/java/util/jar/pack/jni.cpp:224:12: error: cannot convert 'bool' to 'jobject {aka _jobject*}' in return
     return false;
            ^~~~~
/home/top/workspace/openjdk7/jdk/make/common/internal/NativeCompileRules.gmk:79: recipe for target '/home/top/workspace/openjdk7/build/tmp/sun/com.sun.java.util.jar.pack/unpack/obj64/jni.o' failed
```

参考[PATCH RFC 1/5 fix build errors with gcc6](http://mail.openjdk.java.net/pipermail/build-dev/2016-May/017168.html)，修改如下

```shell
$ subl jdk/src/share/native/com/sun/java/util/jar/pack/jni.cpp

   if (uPtr->aborting()) {
     THROW_IOE(uPtr->get_abort_message());
-    return false;
+    return 0;
   }
```