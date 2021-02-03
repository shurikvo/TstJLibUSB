import ru.shurikvo.jlibusb.ConfigDescriptor;
import ru.shurikvo.jlibusb.DeviceDescriptor;
import ru.shurikvo.jlibusb.JLibUSB;

public class TstJLibUSB {
    public static void main(String[] args) {
        int RC, nDev;
        long[] pContext = new long[1];
        long[] pDev = new long[1];

        JLibUSB lib = new JLibUSB();

        RC = lib.init(pContext);
        System.out.println("lib.init: " + RC + ": " + lib.strError(RC));

        nDev = lib.getDeviceList(pContext[0], pDev);
        if (nDev < 0) {
            System.out.println("lib.getDeviceList: " + nDev + ": " + lib.strError(nDev));
            lib.exit(pContext[0]);
            System.out.println("lib.exit: OK");
            return;
        }
        System.out.println("lib.getDeviceList: " + RC + ": OK");

        for (int i = 0; i < nDev; ++i) {
            System.out.println(i + " ----------");
            int nSpeed, nCfg;
            byte nAddr, nBusNum;
            long[] pHdr = new long[1];
            String sB, sSpeed = "unknown";

            nAddr = lib.getDeviceAddress(pDev[0], i);
            nBusNum = lib.getBusNumber(pDev[0], i);
            nSpeed = lib.getDeviceSpeed(pDev[0], i);
            if (nSpeed < 0) {
                System.out.println("lib.getDeviceSpeed: " + i + ": " + nSpeed + ": " + lib.strError(nSpeed));
                continue;
            }
            switch(nSpeed) {
                case 1:
                    sSpeed = "1.5 M";
                    break;
                case 2:
                    sSpeed = "12 M";
                    break;
                case 3:
                    sSpeed = "480 M";
                    break;
                case 4:
                    sSpeed = "5 G";
                    break;
                case 5:
                    sSpeed = "10 G";
                    break;
            }

            DeviceDescriptor desc = new DeviceDescriptor();
            desc = lib.getDeviceDescriptor(pDev[0], i);
            if (desc == null) {
                System.out.println("lib.getDeviceDescriptor: null");
                continue;
            }

            sB = String.format("Dev (bus %02X, device %02X): %04X - %04X speed: %5.5s",
                    nBusNum,nAddr,desc.idVendor, desc.idProduct, sSpeed);
            System.out.println(sB);

            RC = lib.open(pDev[0], i, pHdr);
            if (RC < 0) {
                System.out.println("lib.open: " + i + ": " + RC + ": " + lib.strError(RC));
                continue;
            }
            System.out.println("lib.open: " + RC);

            if(desc.iManufacturer > 0) {
                sB = lib.getStringDescriptorASCII(pHdr[0], desc.iManufacturer);
                if (sB != null)
                    System.out.print("\tManufacturer: " + sB);
            }
            if(desc.iProduct > 0) {
                sB = lib.getStringDescriptorASCII(pHdr[0], desc.iProduct);
                if (sB != null)
                    System.out.print("\tProduct: " + sB);
            }
            if(desc.iSerialNumber > 0) {
                sB = lib.getStringDescriptorASCII(pHdr[0], desc.iSerialNumber);
                if (sB != null)
                    System.out.print("\tS/N: " + sB);
            }
            System.out.println();

            nCfg = desc.bNumConfigurations;
            System.out.println("Configurations: " + nCfg);

            for (int j = 0; j < nCfg; ++j) {
                long[] pConf = new long[1];
                ConfigDescriptor conf = lib.getConfigDescriptor(pDev[0], i, (byte)j, pConf);
                System.out.println("Length            : " + conf.bLength);
                System.out.println("DescriptorType    : " + conf.bDescriptorType);
                System.out.println("TotalLength       : " + conf.wTotalLength);
                System.out.println("NumInterfaces     : " + conf.bNumInterfaces);
                System.out.println("ConfigurationValue: " + conf.bConfigurationValue);
                System.out.println("Configuration     : " + conf.iConfiguration);
                System.out.println("Attributes        : " + String.format("%02X h",conf.bmAttributes));
                System.out.println("Max Power         : " + (int)(conf.maxPower & 0xFF));
                System.out.println("Extra Length      : " + conf.extraLength);

/*
    public byte bLength;
    public byte bDescriptorType;
    public short wTotalLength;
    public byte bNumInterfaces;
    public byte bConfigurationValue;
    public byte iConfiguration;
    public byte bmAttributes;
    public byte MaxPower;
    public InterfaceDescriptor[] interfaceArray;
    public String extra;
    public int extra_length;
*/
                lib.freeConfigDescriptor(pConf[0]);
                System.out.println("lib.freeConfigDescriptor: OK");
            }

            lib.close(pHdr[0]);
            System.out.println("lib.close: OK");
        }
        System.out.println("------------");

        lib.freeDeviceList(pDev[0],1);
        System.out.println("lib.freeDeviceList: OK");

        lib.exit(pContext[0]);
        System.out.println("lib.exit: OK");
    }
}
