package info.chaintech.block.metaj.utils;

import java.io.UnsupportedEncodingException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Objects;

/**
 * @author shniu
 * @date 2018-07-28 下午5:50
 * @email niushaohan@digcredit.com
 */

public class HashUtil {

    /**
     * sha256 哈希算法
     */
    public static String sha256(String data) {

        Objects.requireNonNull(data);

        try {
            MessageDigest digest = MessageDigest.getInstance("SHA-256");

            // 二进制 hash
            byte[] hash = digest.digest(data.getBytes("UTF-8"));

            // 二进制转 16 进制
            StringBuilder stringBuilder = new StringBuilder();
            for (byte aHash : hash) {
                String tmp = Integer.toHexString(aHash & 0xFF);
                if (tmp.length() == 1) {
                    stringBuilder.append("0");
                }
                stringBuilder.append(tmp);
            }

            return stringBuilder.toString();
        } catch (UnsupportedEncodingException | NoSuchAlgorithmException e) {
            e.printStackTrace();
        }

        return null;
    }
}
