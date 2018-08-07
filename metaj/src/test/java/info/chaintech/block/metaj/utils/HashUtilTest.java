package info.chaintech.block.metaj.utils;

import org.junit.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import static org.junit.Assert.*;

public class HashUtilTest {

    private final static Logger log = LoggerFactory.getLogger(HashUtilTest.class);

    @Test
    public void sha256() {
        String sha = HashUtil.sha256("111111111111");
        log.info(sha);
        assert null != sha;
        assertEquals(64, sha.length());
    }

    @Test
    public void ripeMD160() {
        String ripe = HashUtil.ripeMD160("22222");
        log.info(ripe);
        assert null != ripe;
    }

    @Test
    public void doubleHash() {
        String hash1 = HashUtil.sha256("hello");
        log.info(hash1);
        assert null != hash1;
        String hash2 = HashUtil.ripeMD160(hash1);
        log.info(hash2);
    }

}