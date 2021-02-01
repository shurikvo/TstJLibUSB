package ru.shurikvo.jlibusb;

public class EndpointDescriptor {
    public byte bLength;
    public byte bDescriptorType;
    public byte bEndpointAddress;
    public byte bmAttributes;
    public byte wMaxPacketSize;
    public byte bInterval;
    public byte bRefresh;
    public byte bSynchAddress;
    public String extra;
    public int extra_length;
}
