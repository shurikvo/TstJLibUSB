package ru.shurikvo.jlibusb;

public class ConfigDescriptor {
    public byte bLength;
    public byte bDescriptorType;
    public byte wTotalLength;
    public byte bNumInterfaces;
    public byte bConfigurationValue;
    public byte Configuration;
    public byte bmAttributes;
    public byte MaxPower;
    public InterfaceDescriptor[] interfaceArray;
    public String extra;
    public int extra_length;
}
