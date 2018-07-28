package info.chaintech.block.metaj.core;

/**
 * @author shniu
 * @date 2018-07-28 下午5:17
 * <p>
 * 区块数据结构, 区块链的最基本单元, 一个 Block 中包含 0~n 个交易
 */
public class Block {
    private int index;

    /**
     * 当前块的 hash
     */
    private String hash;

    /**
     * 上一个块的 hash
     */
    private String previousHash;

    /**
     * 块的消息
     */
    private String data;

    /**
     * 时间戳
     */
    private long timestamp;

    public Block(String data, String previousHash) {
        this.data = data;
        this.previousHash = previousHash;
        this.timestamp = System.currentTimeMillis();
    }

    public int getIndex() {
        return index;
    }

    public void setIndex(int index) {
        this.index = index;
    }

    public String getHash() {
        return hash;
    }

    public void setHash(String hash) {
        this.hash = hash;
    }

    public String getPreviousHash() {
        return previousHash;
    }

    public void setPreviousHash(String previousHash) {
        this.previousHash = previousHash;
    }

    public String getData() {
        return data;
    }

    public void setData(String data) {
        this.data = data;
    }

    public long getTimestamp() {
        return timestamp;
    }

    public void setTimestamp(long timestamp) {
        this.timestamp = timestamp;
    }

    @Override
    public String toString() {
        return "Block{" +
                "index=" + index +
                ", hash='" + hash + '\'' +
                ", previousHash='" + previousHash + '\'' +
                ", data='" + data + '\'' +
                ", timestamp=" + timestamp +
                '}';
    }
}
