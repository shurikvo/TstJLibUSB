package ru.shurikvo.jlibusb;

public class ConfigDescriptor {
    public byte bLength;
    public byte bDescriptorType;
    public short wTotalLength;
    public byte bNumInterfaces;
    public byte bConfigurationValue;
    public byte iConfiguration;
    public byte bmAttributes;
    public byte maxPower;
    public InterfaceDescriptor[] interfaceArray = new InterfaceDescriptor[0];
    public String extra = "";
    public int extraLength;
}

