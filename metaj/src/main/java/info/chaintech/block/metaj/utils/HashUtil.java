package info.chaintech.block.metaj.utils;

import org.bouncycastle.jce.provider.BouncyCastleProvider;
import org.bouncycastle.util.encoders.Hex;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.UnsupportedEncodingException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.Security;
import java.util.Objects;

/**
 * @author shniu
 * @date 2018-07-28 下午5:50
 * @email niushaohan@digcredit.com
 */

public class HashUtil {

    private static final Logger log = LoggerFactory.getLogger(HashUtil.class);

    /**
     * sha256 哈希算法
     */
    public static String sha256(String data) {

        Objects.requireNonNull(data);

        try {
            MessageDigest digest = MessageDigest.getInstance("SHA-256");

            // 二进制 hash
            byte[] hash = digest.digest(data.getBytes("UTF-8"));
            return byteToHex(hash);
        } catch (UnsupportedEncodingException | NoSuchAlgorithmException e) {
            log.error(e.getMessage(), e);
        }

        return null;
    }

    /**
     * RipeMD160
     */
    public static String ripeMD160(String data) {
        try {
            Security.addProvider(new BouncyCastleProvider());
            MessageDigest ripeMD160 = MessageDigest.getInstance("RipeMD160");
            byte[] hash = ripeMD160.digest(data.getBytes("UTF-8"));
            return Hex.toHexString(hash);
        } catch (UnsupportedEncodingException | NoSuchAlgorithmException e) {
            log.error(e.getMessage(), e);
        }

        return null;
    }

    /**
     * 二进制转 16 进制
     *
     * @param hash 字节数组
     * @return 16进制字符串
     */
    private static String byteToHex(byte[] hash) {
        StringBuilder stringBuilder = new StringBuilder();
        for (byte aHash : hash) {
            String tmp = Integer.toHexString(aHash & 0xFF);
            if (tmp.length() == 1) {
                stringBuilder.append("0");
            }
            stringBuilder.append(tmp);
        }

        return stringBuilder.toString();
    }


}
