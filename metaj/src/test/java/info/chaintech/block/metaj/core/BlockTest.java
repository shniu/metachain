package info.chaintech.block.metaj.core;

import info.chaintech.block.metaj.utils.HashUtil;
import org.junit.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import static org.junit.Assert.*;

/**
 * @author shniu
 * @date 2018-07-28 下午5:50
 */

public class BlockTest {
    private static final Logger log = LoggerFactory.getLogger(BlockTest.class);

    @Test
    public void testBlockObject() {
        Block genesisBlock = new Block("Genesis block", null);
        String genesisHash = HashUtil.sha256(genesisBlock.toString());
        Block secondBlock = new Block("Second", genesisHash);

        log.info("{}", secondBlock);
    }
}