package info.chaintech.block.metaj.bitcoinj;

import com.google.common.util.concurrent.FutureCallback;
import com.google.common.util.concurrent.Futures;
import org.bitcoinj.core.*;
import org.bitcoinj.net.discovery.DnsDiscovery;
import org.bitcoinj.params.TestNet3Params;
import org.bitcoinj.store.BlockStoreException;
import org.bitcoinj.store.SPVBlockStore;
import org.bitcoinj.wallet.Wallet;
import org.bitcoinj.wallet.listeners.WalletCoinsReceivedEventListener;

import java.io.File;

import static com.google.common.util.concurrent.MoreExecutors.directExecutor;

/**
 * @author shniu
 * @date 2018-08-06 下午4:02
 * @email niushaohan@digcredit.com
 */

public class MainServer2 implements WalletCoinsReceivedEventListener {

    public static void main(String[] args) {
        MainServer2 mainServer2 = new MainServer2();
        mainServer2.run();
    }

    private void run() {

        try {
            init();

            System.out.println("Waiting for coins...");

            while (true) {
                Thread.sleep(20);
            }
        } catch (BlockStoreException | InterruptedException e) {
            e.printStackTrace();
        }

    }

    private void init() throws BlockStoreException {
        NetworkParameters params  = TestNet3Params.get();
        ECKey key = new ECKey();
        System.out.println("We created a new key:\n" + key);

        Address addressFromKey = key.toAddress(params);
        System.out.println("Public Address generated: " + addressFromKey);
        System.out.println("Private key is: " + key.getPrivateKeyEncoded(params).toString());

        Wallet wallet = new Wallet(params);
        wallet.importKey(key);

        File blockFile = new File("/tmp/bitcoin-blocks");
        SPVBlockStore blockStore = new SPVBlockStore(params, blockFile);

        BlockChain blockChain = new BlockChain(params, wallet, blockStore);
        PeerGroup peerGroup = new PeerGroup(params, blockChain);
        peerGroup.addPeerDiscovery(new DnsDiscovery(params));
        peerGroup.addWallet(wallet);

        System.out.println("Start peer group");
        peerGroup.start();

        System.out.println("Downloading block chain");
        peerGroup.downloadBlockChain();
        System.out.println("Block chain downloaded");

        wallet.addCoinsReceivedEventListener(this);
    }

    @Override
    public void onCoinsReceived(Wallet wallet, Transaction tx, Coin prevBalance, Coin newBalance) {
        final Coin value = tx.getValueSentToMe(wallet);

        System.out.println("Received tx for " + value.toFriendlyString() + ": " + tx);
        System.out.println("Previous balance is " + prevBalance.toFriendlyString());
        System.out.println("New estimated balance is " + newBalance.toFriendlyString());
        System.out.println("Coin received, wallet balance is :" + wallet.getBalance());

        Futures.addCallback(tx.getConfidence().getDepthFuture(1), new FutureCallback<TransactionConfidence>() {
            @Override
            public void onSuccess(TransactionConfidence result) {
                System.out.println("Transaction confirmed, wallet balance is :" + wallet.getBalance());
            }

            @Override
            public void onFailure(Throwable t) {
                t.printStackTrace();
            }
        }, directExecutor());
    }
}
