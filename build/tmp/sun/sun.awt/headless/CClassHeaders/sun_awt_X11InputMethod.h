/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class sun_awt_X11InputMethod */

#ifndef _Included_sun_awt_X11InputMethod
#define _Included_sun_awt_X11InputMethod
#ifdef __cplusplus
extern "C" {
#endif
#undef sun_awt_X11InputMethod_XIMReverse
#define sun_awt_X11InputMethod_XIMReverse 1L
#undef sun_awt_X11InputMethod_XIMUnderline
#define sun_awt_X11InputMethod_XIMUnderline 2L
#undef sun_awt_X11InputMethod_XIMHighlight
#define sun_awt_X11InputMethod_XIMHighlight 4L
#undef sun_awt_X11InputMethod_XIMPrimary
#define sun_awt_X11InputMethod_XIMPrimary 32L
#undef sun_awt_X11InputMethod_XIMSecondary
#define sun_awt_X11InputMethod_XIMSecondary 64L
#undef sun_awt_X11InputMethod_XIMTertiary
#define sun_awt_X11InputMethod_XIMTertiary 128L
#undef sun_awt_X11InputMethod_XIMVisibleToForward
#define sun_awt_X11InputMethod_XIMVisibleToForward 256L
#undef sun_awt_X11InputMethod_XIMVisibleToBackward
#define sun_awt_X11InputMethod_XIMVisibleToBackward 512L
#undef sun_awt_X11InputMethod_XIMVisibleCenter
#define sun_awt_X11InputMethod_XIMVisibleCenter 1024L
#undef sun_awt_X11InputMethod_XIMVisibleMask
#define sun_awt_X11InputMethod_XIMVisibleMask 1792L
#undef sun_awt_X11InputMethod_INITIAL_SIZE
#define sun_awt_X11InputMethod_INITIAL_SIZE 64L
/*
 * Class:     sun_awt_X11InputMethod
 * Method:    initIDs
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_sun_awt_X11InputMethod_initIDs
  (JNIEnv *, jclass);

/*
 * Class:     sun_awt_X11InputMethod
 * Method:    resetXIC
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_sun_awt_X11InputMethod_resetXIC
  (JNIEnv *, jobject);

/*
 * Class:     sun_awt_X11InputMethod
 * Method:    disposeXIC
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_sun_awt_X11InputMethod_disposeXIC
  (JNIEnv *, jobject);

/*
 * Class:     sun_awt_X11InputMethod
 * Method:    setCompositionEnabledNative
 * Signature: (Z)Z
 */
JNIEXPORT jboolean JNICALL Java_sun_awt_X11InputMethod_setCompositionEnabledNative
  (JNIEnv *, jobject, jboolean);

/*
 * Class:     sun_awt_X11InputMethod
 * Method:    isCompositionEnabledNative
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_sun_awt_X11InputMethod_isCompositionEnabledNative
  (JNIEnv *, jobject);

/*
 * Class:     sun_awt_X11InputMethod
 * Method:    turnoffStatusWindow
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_sun_awt_X11InputMethod_turnoffStatusWindow
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
