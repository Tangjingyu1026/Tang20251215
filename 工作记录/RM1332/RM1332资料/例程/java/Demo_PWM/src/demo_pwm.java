import com.rockmong.rockmong.UsbDevice;
import com.rockmong.rockmong.IO;
import com.rockmong.rockmong.PWM;
import com.sun.jna.ptr.IntByReference;

public class demo_pwm {
    /** 
     * Launch the application. 
     */  
    public static void main(String[] args) {
    	int ret;
        int[] SerialNumbers = new int[16];
        ret = UsbDevice.INSTANCE.UsbDevice_Scan(SerialNumbers);
        if (0 > ret) {
            System.out.println("Error: " + ret);
            return;
        }
        else if (0 == ret){
            System.out.println("No Device!");
            return;
        }
        else{
            for (int i = 0; i < ret; i++){
                System.out.println("Dev" + i + " SN: " + SerialNumbers[i]);
            }
        }

        // 初始化PWM0为1KHz，50%占空比
        // 72MHz / (72*1000) = 1KHz
        // 500 / 1000 * 100% = 50%
        ret = PWM.INSTANCE.PWM_Init(SerialNumbers[0], 0, 1000, 500, 0, 0);
        if (0 > ret) {
            System.out.println("Error: " + ret);
        }
        
        // PWM0开始输出
        ret = PWM.INSTANCE.PWM_Start(SerialNumbers[0], 0, 0);
        if (0 > ret) {
            System.out.println("Error: " + ret);
        }
        
        // PWM0占空比设置为30%
        // 300 / 1000 * 100% = 30%
        ret = PWM.INSTANCE.PWM_SetDuty(SerialNumbers[0], 0, 300);
        if (0 > ret) {
            System.out.println("Error: " + ret);
        }
        
        // PWM0停止输出
        ret = PWM.INSTANCE.PWM_Stop(SerialNumbers[0], 0);
        if (0 > ret) {
            System.out.println("Error: " + ret);
        }
    }
}
