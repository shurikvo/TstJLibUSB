package ru.shurikvo.jlibusb;

public class DeviceDescriptor {
    public byte bLength;
    public byte bDescriptorType;
    public short bcdUSB;
    public byte bDeviceClass;
    public byte bDeviceSubClass;
    public byte bDeviceProtocol;
    public byte bMaxPacketSize0;
    public short idVendor;
    public short idProduct;
    public short bcdDevice;
    public byte iManufacturer;
    public byte iProduct;
    public byte iSerialNumber;
    public byte bNumConfigurations;
}
