/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class sun_nio_ch_SctpNet */

#ifndef _Included_sun_nio_ch_SctpNet
#define _Included_sun_nio_ch_SctpNet
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     sun_nio_ch_SctpNet
 * Method:    socket0
 * Signature: (Z)I
 */
JNIEXPORT jint JNICALL Java_sun_nio_ch_SctpNet_socket0
  (JNIEnv *, jclass, jboolean);

/*
 * Class:     sun_nio_ch_SctpNet
 * Method:    listen0
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_sun_nio_ch_SctpNet_listen0
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     sun_nio_ch_SctpNet
 * Method:    connect0
 * Signature: (ILjava/net/InetAddress;I)I
 */
JNIEXPORT jint JNICALL Java_sun_nio_ch_SctpNet_connect0
  (JNIEnv *, jclass, jint, jobject, jint);

/*
 * Class:     sun_nio_ch_SctpNet
 * Method:    close0
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_sun_nio_ch_SctpNet_close0
  (JNIEnv *, jclass, jint);

/*
 * Class:     sun_nio_ch_SctpNet
 * Method:    preClose0
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_sun_nio_ch_SctpNet_preClose0
  (JNIEnv *, jclass, jint);

/*
 * Class:     sun_nio_ch_SctpNet
 * Method:    bindx
 * Signature: (I[Ljava/net/InetAddress;IIZZ)V
 */
JNIEXPORT void JNICALL Java_sun_nio_ch_SctpNet_bindx
  (JNIEnv *, jclass, jint, jobjectArray, jint, jint, jboolean, jboolean);

/*
 * Class:     sun_nio_ch_SctpNet
 * Method:    getIntOption0
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_sun_nio_ch_SctpNet_getIntOption0
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     sun_nio_ch_SctpNet
 * Method:    setIntOption0
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_sun_nio_ch_SctpNet_setIntOption0
  (JNIEnv *, jclass, jint, jint, jint);

/*
 * Class:     sun_nio_ch_SctpNet
 * Method:    getLocalAddresses0
 * Signature: (I)[Ljava/net/SocketAddress;
 */
JNIEXPORT jobjectArray JNICALL Java_sun_nio_ch_SctpNet_getLocalAddresses0
  (JNIEnv *, jclass, jint);

/*
 * Class:     sun_nio_ch_SctpNet
 * Method:    getRemoteAddresses0
 * Signature: (II)[Ljava/net/SocketAddress;
 */
JNIEXPORT jobjectArray JNICALL Java_sun_nio_ch_SctpNet_getRemoteAddresses0
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     sun_nio_ch_SctpNet
 * Method:    branch0
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_sun_nio_ch_SctpNet_branch0
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     sun_nio_ch_SctpNet
 * Method:    setPrimAddrOption0
 * Signature: (IILjava/net/InetAddress;I)V
 */
JNIEXPORT void JNICALL Java_sun_nio_ch_SctpNet_setPrimAddrOption0
  (JNIEnv *, jclass, jint, jint, jobject, jint);

/*
 * Class:     sun_nio_ch_SctpNet
 * Method:    setPeerPrimAddrOption0
 * Signature: (IILjava/net/InetAddress;IZ)V
 */
JNIEXPORT void JNICALL Java_sun_nio_ch_SctpNet_setPeerPrimAddrOption0
  (JNIEnv *, jclass, jint, jint, jobject, jint, jboolean);

/*
 * Class:     sun_nio_ch_SctpNet
 * Method:    getPrimAddrOption0
 * Signature: (II)Ljava/net/SocketAddress;
 */
JNIEXPORT jobject JNICALL Java_sun_nio_ch_SctpNet_getPrimAddrOption0
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     sun_nio_ch_SctpNet
 * Method:    getInitMsgOption0
 * Signature: (I[I)V
 */
JNIEXPORT void JNICALL Java_sun_nio_ch_SctpNet_getInitMsgOption0
  (JNIEnv *, jclass, jint, jintArray);

/*
 * Class:     sun_nio_ch_SctpNet
 * Method:    setInitMsgOption0
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_sun_nio_ch_SctpNet_setInitMsgOption0
  (JNIEnv *, jclass, jint, jint, jint);

/*
 * Class:     sun_nio_ch_SctpNet
 * Method:    shutdown0
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_sun_nio_ch_SctpNet_shutdown0
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     sun_nio_ch_SctpNet
 * Method:    init
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_sun_nio_ch_SctpNet_init
  (JNIEnv *, jclass);

#ifdef __cplusplus
}
#endif
#endif
