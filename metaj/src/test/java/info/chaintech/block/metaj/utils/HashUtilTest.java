package info.chaintech.block.metaj.utils;

import org.junit.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import static org.junit.Assert.*;

public class HashUtilTest {

    private final static Logger logger = LoggerFactory.getLogger(HashUtilTest.class);

    @Test
    public void sha256() {
        String sha = HashUtil.sha256("111111111111");
        logger.info(sha);
        assert null != sha;
        assertEquals(64, sha.length());
    }

}