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

/*JNIEXPORT jint JNICALL Java_ru_shurikvo_jlibusb_JLibUSB_getDeviceDescriptor(JNIEnv *env, jclass myclass, jlong deviceList, jint index, jobjectArray descList)
{
	int RC = 0;
	//struct libusb_device_descriptor desc;
	libusb_device **Devs = (libusb_device **)deviceList;

	jobject Desc = env->GetObjectArrayElement(descList, 0);

	//jobject pDesc = (jobject)desc;

	RC = libusb_get_device_descriptor(*(Devs + index), (libusb_device_descriptor *)(&Desc));

	env->SetObjectArrayElement(descList, 0, Desc);

	return RC;
}*/

JNIEXPORT jobject JNICALL Java_ru_shurikvo_jlibusb_JLibUSB_getDeviceDescriptor(JNIEnv *env, jclass myclass, jlong deviceList, jint index)
{
	int RC = 0;
	struct libusb_device_descriptor desc;
	libusb_device **Devs = (libusb_device **)deviceList;

	RC = libusb_get_device_descriptor(*(Devs + index), &desc);
	if (RC < 0) return NULL;

	jclass cls = env->FindClass("ru/shurikvo/jlibusb/DeviceDescriptor");
	if (!cls) return NULL;

	jmethodID constructor = env->GetMethodID(cls, "<init>", "()V");
	if (!constructor) return NULL;

	jobject jo = env->NewObject(cls, constructor);
	if (!jo) return NULL;

	env->SetByteField(jo, env->GetFieldID(cls, "bLength", "B"), desc.bLength);
	env->SetByteField(jo, env->GetFieldID(cls, "bDescriptorType", "B"), desc.bDescriptorType);
	env->SetByteField(jo, env->GetFieldID(cls, "bcdUSB", "S"), desc.bcdUSB);
	env->SetByteField(jo, env->GetFieldID(cls, "bDeviceClass", "B"), desc.bDeviceClass);
	env->SetByteField(jo, env->GetFieldID(cls, "bDeviceSubClass", "B"), desc.bDeviceSubClass);
	env->SetByteField(jo, env->GetFieldID(cls, "bDeviceProtocol", "B"), desc.bDeviceProtocol);
	env->SetByteField(jo, env->GetFieldID(cls, "bMaxPacketSize0", "B"), desc.bMaxPacketSize0);
	env->SetByteField(jo, env->GetFieldID(cls, "idVendor", "S"), desc.idVendor);
	env->SetByteField(jo, env->GetFieldID(cls, "idProduct", "S"), desc.idProduct);
	env->SetByteField(jo, env->GetFieldID(cls, "bcdDevice", "S"), desc.bcdDevice);
	env->SetByteField(jo, env->GetFieldID(cls, "iManufacturer", "B"), desc.iManufacturer);
	env->SetByteField(jo, env->GetFieldID(cls, "iProduct", "B"), desc.iProduct);
	env->SetByteField(jo, env->GetFieldID(cls, "iSerialNumber", "B"), desc.iSerialNumber);
	env->SetByteField(jo, env->GetFieldID(cls, "bNumConfigurations", "B"), desc.bNumConfigurations);
	return jo;
}

JNIEXPORT jint JNICALL Java_ru_shurikvo_jlibusb_JLibUSB_Open(JNIEnv *env, jclass myclass, jlong deviceList, jint index, jlongArray handlerList)
{
	int RC;
	jlong *pHandlerList = env->GetLongArrayElements(handlerList, false);
	libusb_device **Devs = (libusb_device **)deviceList;

	//return (jbyte)libusb_open(*(Devs + index));

	RC = libusb_open(*(Devs + index), (libusb_device_handle **)pHandlerList);
	if (RC < 0)
	{
		printf("libusb_init: RC = %d\n", RC);
		env->ReleaseLongArrayElements(handlerList, pHandlerList, JNI_ABORT);
		printf("PackKey: %s\n", libusb_strerror(RC));
	}
	else
		env->ReleaseLongArrayElements(handlerList, pHandlerList, JNI_COMMIT);
	return RC;
}

JNIEXPORT void JNICALL Java_ru_shurikvo_jlibusb_JLibUSB_Close(JNIEnv *env, jclass myclass, jlong handler)
{
	libusb_close((libusb_device_handle *)handler);
}

JNIEXPORT jint JNICALL Java_ru_shurikvo_jlibusb_JLibUSB_getStringDescriptorASCII(JNIEnv *env, jclass myclass, jlong handler, jbyte value, jobjectArray stringList)
{
	//libusb_config_descriptor Desc = ()
	//libusb_free_config_descriptor()
	return 0;
}
