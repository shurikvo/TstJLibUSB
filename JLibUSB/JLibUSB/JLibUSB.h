/* DO NOT EDIT THIS FILE - it is machine generated */
#include "jni.h"
/* Header for class JLibUSB */

#ifndef _Included_JLibUSB
#define _Included_JLibUSB
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     ru_shurikvo_jlibusb_JLibUSB
 * Method:    init
 * Signature: ([J)I
 */
JNIEXPORT jint JNICALL Java_ru_shurikvo_jlibusb_JLibUSB_init (JNIEnv *, jclass, jlongArray);

/*
 * Class:     JLibUSB
 * Method:    exit
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ru_shurikvo_jlibusb_JLibUSB_exit (JNIEnv *, jclass, jlong);

/*
 * Class:     ru_shurikvo_jlibusb_JLibUSB
 * Method:    libusb_strerror
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_ru_shurikvo_jlibusb_JLibUSB_strError (JNIEnv *, jclass, jint);

/*
 * Class:     ru_shurikvo_jlibusb_JLibUSB
 * Method:    getDeviceList
 * Signature: (J[[J)I
 */
JNIEXPORT jint JNICALL Java_ru_shurikvo_jlibusb_JLibUSB_getDeviceList (JNIEnv *, jclass, jlong, jlongArray);

/*
 * Class:     ru_shurikvo_jlibusb_JLibUSB
 * Method:    freeDeviceList
 * Signature: ([JI)V
 */
JNIEXPORT void JNICALL Java_ru_shurikvo_jlibusb_JLibUSB_freeDeviceList (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     ru_shurikvo_jlibusb_JLibUSB
 * Method:    getDeviceDescriptor
 * Signature: (J[LDeviceDescriptor;)I
 */
//JNIEXPORT jint JNICALL Java_ru_shurikvo_jlibusb_JLibUSB_getDeviceDescriptor (JNIEnv *, jclass, jlong, jint, jobjectArray);
JNIEXPORT jobject JNICALL Java_ru_shurikvo_jlibusb_JLibUSB_getDeviceDescriptor(JNIEnv *, jclass, jlong, jint);
/*
 * Class:     ru_shurikvo_jlibusb_JLibUSB
 * Method:    getConfigDescriptor
 * Signature: (JB[[LConfigDescriptor;)I
 */
//JNIEXPORT jint JNICALL Java_ru_shurikvo_jlibusb_JLibUSB_getConfigDescriptor(JNIEnv *, jclass, jlong, jbyte, jobjectArray);
JNIEXPORT jobject JNICALL Java_ru_shurikvo_jlibusb_JLibUSB_getConfigDescriptor(JNIEnv *, jclass, jlong, jint, jbyte, jlongArray);

/*
 * Class:     ru_shurikvo_jlibusb_JLibUSB
 * Method:    getConfigDescriptorByValue
 * Signature: (JB[[LConfigDescriptor;)I
 */
//JNIEXPORT jint JNICALL Java_ru_shurikvo_jlibusb_JLibUSB_getConfigDescriptorByValue (JNIEnv *, jclass, jlong, jbyte, jobjectArray);

/*
 * Class:     ru_shurikvo_jlibusb_JLibUSB
 * Method:    freeConfigDescriptor
 * Signature: ([LConfigDescriptor;)V
 */
JNIEXPORT void JNICALL Java_ru_shurikvo_jlibusb_JLibUSB_freeConfigDescriptor (JNIEnv *, jclass, jlong);

/*
 * Class:     ru_shurikvo_jlibusb_JLibUSB
 * Method:    getBusNumber
 * Signature: (J)B
 */
JNIEXPORT jbyte JNICALL Java_ru_shurikvo_jlibusb_JLibUSB_getBusNumber (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     ru_shurikvo_jlibusb_JLibUSB
 * Method:    getDeviceAddress
 * Signature: (J)B
 */
JNIEXPORT jbyte JNICALL Java_ru_shurikvo_jlibusb_JLibUSB_getDeviceAddress (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     ru_shurikvo_jlibusb_JLibUSB
 * Method:    getDeviceSpeed
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_ru_shurikvo_jlibusb_JLibUSB_getDeviceSpeed (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     ru_shurikvo_jlibusb_JLibUSB
 * Method:    Open
 * Signature: (J[J)I
 */
JNIEXPORT jint JNICALL Java_ru_shurikvo_jlibusb_JLibUSB_open (JNIEnv *, jclass, jlong, jint, jlongArray);

/*
 * Class:     ru_shurikvo_jlibusb_JLibUSB
 * Method:    Close
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ru_shurikvo_jlibusb_JLibUSB_close (JNIEnv *, jclass, jlong);

/*
 * Class:     ru_shurikvo_jlibusb_JLibUSB
 * Method:    getDevice
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_ru_shurikvo_jlibusb_JLibUSB_getDevice (JNIEnv *, jclass, jlong);

/*
 * Class:     ru_shurikvo_jlibusb_JLibUSB
 * Method:    getStringDescriptorASCII
 * Signature: (JB[Ljava/lang/String;)I
 */
JNIEXPORT jstring JNICALL Java_ru_shurikvo_jlibusb_JLibUSB_getStringDescriptorASCII (JNIEnv *, jclass, jlong, jbyte);

#ifdef __cplusplus
}
#endif
#endif
