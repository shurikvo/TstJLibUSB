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

        for(int i = 0; i < nDev; ++i) {
            System.out.println(i + " ----------");
            int nSpeed;
            byte nAddr, nBusNum;
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
        }
        System.out.println("------------");

        lib.freeDeviceList(pDev[0],1);
        System.out.println("lib.freeDeviceList: OK");

        lib.exit(pContext[0]);
        System.out.println("lib.exit: OK");
    }
}
