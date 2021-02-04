package ru.shurikvo.jlibusb;

public class InterfaceDescriptor {
    public byte bLength;
    public byte bDescriptorType;
    public byte bInterfaceNumber;
    public byte bAlternateSetting;
    public byte bNumEndpoints;
    public byte bInterfaceClass;
    public byte bInterfaceSubClass;
    public byte bInterfaceProtocol;
    public byte iInterface;
    public EndpointDescriptor[] endpointArray = new EndpointDescriptor[0];
    public String extra = "";
    public int extraLength;
}
