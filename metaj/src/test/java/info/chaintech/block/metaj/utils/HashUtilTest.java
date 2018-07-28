package info.chaintech.block.metaj.utils;

import org.apache.log4j.Logger;
import org.junit.Test;

import static org.junit.Assert.*;

public class HashUtilTest {

    private final Logger logger = Logger.getLogger(this.getClass());

    @Test
    public void sha256() {
        String sha = HashUtil.sha256("111111111111");
        logger.info(sha);
        assert null != sha;
        assertTrue(sha.length() == 64);
    }

}