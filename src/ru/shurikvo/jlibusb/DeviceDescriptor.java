package ru.shurikvo.jlibusb;

public class DeviceDescriptor {
    public byte bLength;
    public byte bDescriptorType;
    public byte bcdUSB;
    public byte bDeviceClass;
    public byte bDeviceSubClass;
    public byte bDeviceProtocol;
    public byte bMaxPacketSize0;
    public byte idVendor;
    public byte idProduct;
    public byte bcdDevice;
    public byte iManufacturer;
    public byte iProduct;
    public byte iSerialNumber;
    public byte bNumConfigurations;
}
