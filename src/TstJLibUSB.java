import ru.shurikvo.jlibusb.JLibUSB;

public class TstJLibUSB {
    public static void main(String[] args) {
        int RC;
        long[] pContext = new long[1];
        long[] pDev = new long[1];

        JLibUSB lib = new JLibUSB();

        //System.out.println("pContext[0]: " + pContext[0]);
        RC = lib.init(pContext);
        System.out.println("lib.init: " + RC + ": " + lib.strError(RC));
        //System.out.println("pContext[0]: " + pContext[0]);

        //RC = lib.getDeviceList(pContext[0], pDev);
        RC = lib.getDeviceList(pContext[0], pDev);
        if (RC < 0) {
            System.out.println("lib.getDeviceList: " + RC + ": " + lib.strError(RC));
            lib.exit(pContext[0]);
            System.out.println("lib.exit: OK");
            return;
        }
        System.out.println("lib.getDeviceList: " + RC + ": OK");

        for(int i = 0; i < RC; ++i) {
            int nSpeed;
            byte nAddr, nBusNum;
            String sSpeed = "unknown";

            nAddr = lib.getDeviceAddress(pDev[0], i);
            nBusNum = lib.getBusNumber(pDev[0], i);
            nSpeed = lib.getDeviceSpeed(pDev[0], i);
            if (RC < 0) {
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
            System.out.println(i + ". Bus: " + nBusNum + " Addr: " + nAddr + " Speed: " + sSpeed);
        }

        lib.freeDeviceList(pDev[0],1);
        System.out.println("lib.freeDeviceList: OK");

        lib.exit(pContext[0]);
        System.out.println("lib.exit: OK");
    }
}
