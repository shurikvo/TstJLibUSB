package ru.shurikvo.jlibusb;

public class JLibUSB {
    static
    {
        System.loadLibrary("JLibUSB");
    }

    native public static int init(long[] pContext);
    native public static void exit(long context);
    native public static String strError(int err);
    native public static int getDeviceList(long context, long[] pDeviceList);
    native public static void freeDeviceList(long deviceList, int unrefDevices);
    native public static int getDeviceDescriptor(long dev, DeviceDescriptor[] desc);
    native public static int getConfigDescriptor(long dev, byte configIndex, ConfigDescriptor[][] config);
    native public static int getConfigDescriptorByValue(long dev, byte bConfigurationValue, ConfigDescriptor[][] config);
    native public static void freeConfigDescriptor(ConfigDescriptor[] config);
    native public static byte getBusNumber(long dev, int index);
    native public static byte getDeviceAddress(long dev, int index);
    native public static int getDeviceSpeed(long dev, int index);
    native public static int Open(long dev, int index, long[] pDevHandle);
    native public static void Close(long devHandle);
    native public static long getDevice(long devHandle);
    native public static int getStringDescriptorASCII(long devHandle, byte descIndex, String[] data);
}
