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
		printf("JLibUSB.libusb_init: RC = %d: %s\n", RC, libusb_strerror(RC));
		env->ReleaseLongArrayElements(context, pContext, JNI_ABORT);
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
		printf("JLibUSB.libusb_get_device_list: RC = %d: %s\n", RC, libusb_strerror(RC));
		env->ReleaseLongArrayElements(deviceList, pDeviceList, JNI_ABORT);
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
	env->SetShortField(jo, env->GetFieldID(cls, "bcdUSB", "S"), desc.bcdUSB);
	env->SetByteField(jo, env->GetFieldID(cls, "bDeviceClass", "B"), desc.bDeviceClass);
	env->SetByteField(jo, env->GetFieldID(cls, "bDeviceSubClass", "B"), desc.bDeviceSubClass);
	env->SetByteField(jo, env->GetFieldID(cls, "bDeviceProtocol", "B"), desc.bDeviceProtocol);
	env->SetByteField(jo, env->GetFieldID(cls, "bMaxPacketSize0", "B"), desc.bMaxPacketSize0);
	env->SetShortField(jo, env->GetFieldID(cls, "idVendor", "S"), desc.idVendor);
	env->SetShortField(jo, env->GetFieldID(cls, "idProduct", "S"), desc.idProduct);
	env->SetShortField(jo, env->GetFieldID(cls, "bcdDevice", "S"), desc.bcdDevice);
	env->SetByteField(jo, env->GetFieldID(cls, "iManufacturer", "B"), desc.iManufacturer);
	env->SetByteField(jo, env->GetFieldID(cls, "iProduct", "B"), desc.iProduct);
	env->SetByteField(jo, env->GetFieldID(cls, "iSerialNumber", "B"), desc.iSerialNumber);
	env->SetByteField(jo, env->GetFieldID(cls, "bNumConfigurations", "B"), desc.bNumConfigurations);
	return jo;
}

JNIEXPORT jint JNICALL Java_ru_shurikvo_jlibusb_JLibUSB_open(JNIEnv *env, jclass myclass, jlong deviceList, jint index, jlongArray handlerList)
{
	int RC;
	jlong *pHandlerList = env->GetLongArrayElements(handlerList, false);
	libusb_device **Devs = (libusb_device **)deviceList;

	//return (jbyte)libusb_open(*(Devs + index));

	RC = libusb_open(*(Devs + index), (libusb_device_handle **)pHandlerList);
	if (RC < 0)
	{
		printf("JLibUSB.libusb_open: RC = %d: %s\n", RC, libusb_strerror(RC));
		env->ReleaseLongArrayElements(handlerList, pHandlerList, JNI_ABORT);
	}
	else
		env->ReleaseLongArrayElements(handlerList, pHandlerList, JNI_COMMIT);
	return RC;
}

JNIEXPORT void JNICALL Java_ru_shurikvo_jlibusb_JLibUSB_close(JNIEnv *env, jclass myclass, jlong handler)
{
	libusb_close((libusb_device_handle *)handler);
}

JNIEXPORT jstring JNICALL Java_ru_shurikvo_jlibusb_JLibUSB_getStringDescriptorASCII(JNIEnv *env, jclass myclass, jlong handler, jbyte value)
{
	int RC;
	unsigned char sBuf[100];

	RC = libusb_get_string_descriptor_ascii((libusb_device_handle *)handler, (unsigned char)value, sBuf, 99);

	return env->NewStringUTF((const char *)sBuf);
}

JNIEXPORT jobject JNICALL Java_ru_shurikvo_jlibusb_JLibUSB_getConfigDescriptor(JNIEnv *env, jclass myclass, jlong deviceList, jint index, jbyte configIndex, jlongArray configList)
{
	int i, j, RC = 0;
	struct libusb_config_descriptor *pDesc, desc;
	libusb_device **Devs = (libusb_device **)deviceList;
	jstring sExtra;

	//--------------------------------------------------------------------------------------
	RC = libusb_get_config_descriptor(*(Devs + index), configIndex, &pDesc);
	if (RC < 0) return NULL;

	desc = *pDesc;

	jclass cls = env->FindClass("ru/shurikvo/jlibusb/ConfigDescriptor");
	if (!cls) return NULL;

	jmethodID constructor = env->GetMethodID(cls, "<init>", "()V");
	if (!constructor) return NULL;

	jobject jo = env->NewObject(cls, constructor);
	if (!jo) return NULL;
	//--------------------------------------------------------------------------------------
	jclass clsI = env->FindClass("ru/shurikvo/jlibusb/InterfaceDescriptor");
	if (!clsI) return NULL;

	jmethodID constructorI = env->GetMethodID(clsI, "<init>", "()V");
	if (!constructorI) return NULL;

	jobject joI = env->NewObject(clsI, constructorI);
	if (!joI) return NULL;

	jobjectArray jaInterface = env->NewObjectArray((jsize)desc.bNumInterfaces, clsI, joI);
	if (!jaInterface) return NULL;

	jfieldID fid = env->GetFieldID(cls, "interfaceArray", "[Lru/shurikvo/jlibusb/InterfaceDescriptor;");
	if (!fid) return NULL;
	//--------------------------------------------------------------------------------------
	jclass clsE = env->FindClass("ru/shurikvo/jlibusb/EndpointDescriptor");
	if (!clsE) return NULL;

	jmethodID constructorE = env->GetMethodID(clsE, "<init>", "()V");
	if (!constructorE) return NULL;

	jobject joE = env->NewObject(clsE, constructorI);
	if (!joE) return NULL;

	jfieldID fed = env->GetFieldID(clsI, "endpointArray", "[Lru/shurikvo/jlibusb/EndpointDescriptor;");
	if (!fed) return NULL;
	//--------------------------------------------------------------------------------------

	env->SetShortField(jo, env->GetFieldID(cls, "wTotalLength", "S"), (jshort)desc.wTotalLength);
	env->SetByteField(jo, env->GetFieldID(cls, "bLength", "B"), (jbyte)desc.bLength);
	env->SetByteField(jo, env->GetFieldID(cls, "bDescriptorType", "B"), (jbyte)desc.bDescriptorType);
	env->SetByteField(jo, env->GetFieldID(cls, "bNumInterfaces", "B"), (jbyte)desc.bNumInterfaces);
	env->SetByteField(jo, env->GetFieldID(cls, "bConfigurationValue", "B"), (jbyte)desc.bConfigurationValue);
	env->SetByteField(jo, env->GetFieldID(cls, "iConfiguration", "B"), (jbyte)desc.iConfiguration);
	env->SetByteField(jo, env->GetFieldID(cls, "bmAttributes", "B"), (jbyte)desc.bmAttributes);
	env->SetByteField(jo, env->GetFieldID(cls, "maxPower", "B"), (jbyte)desc.MaxPower);
	env->SetIntField(jo, env->GetFieldID(cls, "extraLength", "I"), (jint)desc.extra_length);

	if (desc.extra_length)
	{
		sExtra = env->NewStringUTF((const char *)desc.extra);
		env->SetObjectField(jo, env->GetFieldID(cls, "extra", "Ljava/lang/String;"), (jobject)sExtra);
	}

	printf("JLibUSB: NumInterfaces: %d\n", desc.bNumInterfaces);
	for (i = 0; i < desc.bNumInterfaces; ++i)
	{
		joI = env->NewObject(clsI, constructorI);
		env->SetByteField(joI, env->GetFieldID(clsI, "bDescriptorType", "B"), (jbyte)(desc.interface + i)->altsetting->bDescriptorType);
		env->SetByteField(joI, env->GetFieldID(clsI, "bAlternateSetting", "B"), (jbyte)(desc.interface + i)->altsetting->bAlternateSetting);
		env->SetByteField(joI, env->GetFieldID(clsI, "bInterfaceClass", "B"), (jbyte)(desc.interface + i)->altsetting->bInterfaceClass);
		env->SetByteField(joI, env->GetFieldID(clsI, "bInterfaceNumber", "B"), (jbyte)(desc.interface + i)->altsetting->bInterfaceNumber);
		env->SetByteField(joI, env->GetFieldID(clsI, "bInterfaceProtocol", "B"), (jbyte)(desc.interface + i)->altsetting->bInterfaceProtocol);
		env->SetByteField(joI, env->GetFieldID(clsI, "bInterfaceSubClass", "B"), (jbyte)(desc.interface + i)->altsetting->bInterfaceSubClass);
		env->SetByteField(joI, env->GetFieldID(clsI, "bLength", "B"), (jbyte)(desc.interface + i)->altsetting->bLength);
		env->SetByteField(joI, env->GetFieldID(clsI, "bNumEndpoints", "B"), (jbyte)(desc.interface + i)->altsetting->bNumEndpoints);
		env->SetByteField(joI, env->GetFieldID(clsI, "extraLength", "I"), (jint)(desc.interface + i)->altsetting->extra_length);
		env->SetByteField(joI, env->GetFieldID(clsI, "iInterface", "B"), (jbyte)(desc.interface + i)->altsetting->iInterface);

		if ((desc.interface + i)->altsetting->extra_length)
		{
			sExtra = env->NewStringUTF((const char *)(desc.interface + i)->altsetting->extra);
			env->SetObjectField(joI, env->GetFieldID(clsI, "extra", "Ljava/lang/String;"), (jobject)sExtra);
		}
		env->SetObjectArrayElement(jaInterface, i, (jobject)joI);
		printf("JLibUSB: Interface.%d\n", i);
		printf("JLibUSB: NumEndpoints: %d\n", (desc.interface + i)->altsetting->bNumEndpoints);


		jobjectArray jaEndpoint = env->NewObjectArray((jsize)(desc.interface + i)->altsetting->bNumEndpoints, clsE, joE);
		if (!jaEndpoint) return NULL;

		libusb_endpoint_descriptor *pEndP = (libusb_endpoint_descriptor *)(desc.interface + i)->altsetting->endpoint;
		for (j = 0; j < (desc.interface + i)->altsetting->bNumEndpoints; ++j) 
		{
			joE = env->NewObject(clsE, constructorE);
			env->SetByteField(joE, env->GetFieldID(clsE, "bDescriptorType", "B"), (jbyte)(pEndP + j)->bDescriptorType);
			env->SetByteField(joE, env->GetFieldID(clsE, "bEndpointAddress", "B"), (jbyte)(pEndP + j)->bEndpointAddress);
			env->SetByteField(joE, env->GetFieldID(clsE, "bInterval", "B"), (jbyte)(pEndP + j)->bInterval);
			env->SetByteField(joE, env->GetFieldID(clsE, "bLength", "B"), (jbyte)(pEndP + j)->bLength);
			env->SetByteField(joE, env->GetFieldID(clsE, "bmAttributes", "B"), (jbyte)(pEndP + j)->bmAttributes);
			env->SetByteField(joE, env->GetFieldID(clsE, "bRefresh", "B"), (jbyte)(pEndP + j)->bRefresh);
			env->SetByteField(joE, env->GetFieldID(clsE, "bSynchAddress", "B"), (jbyte)(pEndP + j)->bSynchAddress);
			env->SetByteField(joE, env->GetFieldID(clsE, "wMaxPacketSize", "S"), (jbyte)(pEndP + j)->wMaxPacketSize);
			env->SetByteField(joE, env->GetFieldID(clsE, "extraLength", "I"), (jbyte)(pEndP + j)->extra_length);

			if ((pEndP + j)->extra_length)
			{
				sExtra = env->NewStringUTF((const char *)(pEndP + j)->extra);
				env->SetObjectField(joE, env->GetFieldID(clsI, "extra", "Ljava/lang/String;"), (jobject)sExtra);
			}
			env->SetObjectArrayElement(jaEndpoint, j, (jobject)joE);
			printf("JLibUSB: Endpoint.%d.%d\n", i, j);

			env->SetObjectField(joI, fed, (jobject)jaEndpoint);


/*  public byte bLength;
    public byte bDescriptorType;
    public byte bEndpointAddress;
    public byte bmAttributes;
    public short wMaxPacketSize;
    public byte bInterval;
    public byte bRefresh;
    public byte bSynchAddress;
    public String extra;
    public int extraLength;
*/
		}

		env->SetObjectField(jo, fid, (jobject)jaInterface);
	}
	env->DeleteLocalRef(clsI);
	env->DeleteLocalRef(cls);

	return jo;
}

JNIEXPORT void JNICALL Java_ru_shurikvo_jlibusb_JLibUSB_freeConfigDescriptor(JNIEnv *env, jclass myclass, jlong configDesc)
{
	libusb_free_config_descriptor((libusb_config_descriptor *)configDesc);
}
