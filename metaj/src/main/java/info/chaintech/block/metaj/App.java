package info.chaintech.block.metaj;


import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * 入口
 *
 * @author shniu
 */
public class App {

    private static final Logger log = LoggerFactory.getLogger(App.class);

    public static void main(String[] args) {
        log.info("启动 metaj 网络成功!");
        //
        byte b = 0b10000;
        log.info("十进制: {}", b & 0xff);
        log.info("十六进制: {}", Integer.toHexString(b & 0xff));
        log.info("二进制: {}", Integer.toBinaryString(b & 0xff));
    }
}
