#include "stdafx.h"
#include "JLibUSB.h"
#include "libusb.h"

JNIEXPORT jint JNICALL Java_ru_shurikvo_jlibusb_JLibUSB_init(JNIEnv *env, jclass myclass, jlongArray context)
{
	int RC = 0;
	jlong *pContext = env->GetLongArrayElements(context, false);
	
	RC = libusb_init((libusb_context **)pContext);
	if (RC < 0)
	{
		printf("libusb_init: RC = %d\n", RC);
		env->ReleaseLongArrayElements(context, pContext, JNI_ABORT);
		printf("PackKey: %s\n", libusb_strerror(RC));
	}
	else
		env->ReleaseLongArrayElements(context, pContext, JNI_COMMIT);
	return RC;
}

JNIEXPORT void JNICALL Java_ru_shurikvo_jlibusb_JLibUSB_exit(JNIEnv *env, jclass myclass, jlong context)
{
	libusb_exit((libusb_context *)context);
}

JNIEXPORT jstring JNICALL Java_ru_shurikvo_jlibusb_JLibUSB_strError(JNIEnv *env, jclass myclass, jint err)
{
	return env->NewStringUTF(libusb_strerror(err));
}

JNIEXPORT jint JNICALL Java_ru_shurikvo_jlibusb_JLibUSB_getDeviceList(JNIEnv *env, jclass myclass, jlong context, jlongArray deviceList)
{
	int RC;
	jlong *pDeviceList = env->GetLongArrayElements(deviceList, false);

	RC = libusb_get_device_list((libusb_context *)context, (libusb_device ***)pDeviceList);
	if (RC < 0)
	{
		printf("libusb_init: RC = %d\n", RC);
		env->ReleaseLongArrayElements(deviceList, pDeviceList, JNI_ABORT);
		printf("PackKey: %s\n", libusb_strerror(RC));
	}
	else
		env->ReleaseLongArrayElements(deviceList, pDeviceList, JNI_COMMIT);
	return RC;
}

JNIEXPORT void JNICALL Java_ru_shurikvo_jlibusb_JLibUSB_freeDeviceList(JNIEnv *env, jclass myclass, jlong deviceList, jint unrefDevices)
{

	libusb_free_device_list((libusb_device **)deviceList, unrefDevices);
}

JNIEXPORT jbyte JNICALL Java_ru_shurikvo_jlibusb_JLibUSB_getBusNumber(JNIEnv *env, jclass myclass, jlong deviceList, jint index)
{
	libusb_device **Devs = (libusb_device **)deviceList;

	return (jbyte)libusb_get_bus_number(*(Devs + index));
}

JNIEXPORT jbyte JNICALL Java_ru_shurikvo_jlibusb_JLibUSB_getDeviceAddress(JNIEnv *env, jclass myclass, jlong deviceList, jint index)
{
	libusb_device **Devs = (libusb_device **)deviceList;

	return (jbyte)libusb_get_device_address(*(Devs + index));
}

JNIEXPORT jint JNICALL Java_ru_shurikvo_jlibusb_JLibUSB_getDeviceSpeed(JNIEnv *env, jclass myclass, jlong deviceList, jint index)
{
	libusb_device **Devs = (libusb_device **)deviceList;

	return (jbyte)libusb_get_device_speed(*(Devs + index));
}
