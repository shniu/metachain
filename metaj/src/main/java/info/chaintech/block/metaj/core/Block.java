package info.chaintech.block.metaj.core;

/**
 * @author shniu
 * @date 2018-07-28 下午5:17
 * <p>
 * 区块数据结构, 区块链的最基本单元, 一个 Block 中包含 0~n 个交易
 */
public class Block {
    /**
     * 当前块的 hash
     */
    private String hash;

    /**
     * 默克尔树 hash
     */
    private String merkleTreeHash;

    /**
     * 随机数
     */
    private long nonce;

    /**
     * 当前区块的高度
     */
    private long height;

    /**
     * 区块包含的交易数
     */
    private int transactionCount;

    /**
     * 区块版本号
     */
    private int version;

    /**
     * 上一个块的 hash
     */
    private String previousHash;

    /**
     * 时间戳
     */
    private long timestamp;

    /**
     * 块的消息
     */
    private String data;


    public Block(String data, String previousHash) {
        this.data = data;
        this.previousHash = previousHash;
        this.timestamp = System.currentTimeMillis();
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
                ", hash='" + hash + '\'' +
                ", previousHash='" + previousHash + '\'' +
                ", data='" + data + '\'' +
                ", timestamp=" + timestamp +
                '}';
    }
}
