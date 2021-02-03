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
    native public static DeviceDescriptor getDeviceDescriptor(long dev, int index);
    native public static ConfigDescriptor getConfigDescriptor(long dev, int index, byte configIndex, long[] pConfigDesc);
    //native public static int getConfigDescriptorByValue(long dev, byte bConfigurationValue, ConfigDescriptor[][] config);
    native public static void freeConfigDescriptor(long pConfigDesc);
    native public static byte getBusNumber(long dev, int index);
    native public static byte getDeviceAddress(long dev, int index);
    native public static int getDeviceSpeed(long dev, int index);
    native public static int open(long dev, int index, long[] pDevHandle);
    native public static void close(long devHandle);
    native public static long getDevice(long devHandle);
    native public static String getStringDescriptorASCII(long devHandle, byte descIndex);
}
