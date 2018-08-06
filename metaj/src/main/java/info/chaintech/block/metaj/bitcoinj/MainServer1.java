package info.chaintech.block.metaj.bitcoinj;

import com.google.common.util.concurrent.FutureCallback;
import com.google.common.util.concurrent.Futures;
import org.bitcoinj.core.*;
import org.bitcoinj.crypto.DeterministicKey;
import org.bitcoinj.kits.WalletAppKit;
import org.bitcoinj.params.MainNetParams;
import org.bitcoinj.params.RegTestParams;
import org.bitcoinj.params.TestNet3Params;
import org.bitcoinj.utils.BriefLogFormatter;

import javax.annotation.Nullable;
import java.io.File;

import static com.google.common.util.concurrent.MoreExecutors.directExecutor;

/**
 * @author shniu
 * @date 2018-08-06 下午1:32
 * @email niushaohan@digcredit.com
 */

public class MainServer1 {

    private static final int ARGS_MIN_LENGTH = 2;
    private static final String TEST_NET_FLAG = "testnet";
    private static final String REG_TEST_FLAG = "regtest";

    private static Address forwardingAddress;
    private static WalletAppKit appKit;

    public static void main(String[] args) {

        // To configure log4j to have more compact
        BriefLogFormatter.init();

        // Check the command line arguments
        if (args.length < ARGS_MIN_LENGTH) {
            System.err.println("Usage: address-to-send-back-to [regtest|testnet]");
            return;
        }

        // Figure out which network we should connect to
        NetworkParameters params;
        String filePrefix;
        if (TEST_NET_FLAG.equals(args[1])) {
            params = TestNet3Params.get();
            filePrefix = "forwarding-service-testnet";
        } else if (REG_TEST_FLAG.equals(args[1])) {
            params = RegTestParams.get();
            filePrefix = "forwarding-service-regtest";
        } else {
            params = MainNetParams.get();
            filePrefix = "forwarding-service";
        }

        // Parse the address given as the first parameter
        forwardingAddress = Address.fromBase58(params, args[0]);

        System.out.println("Network: " + params.getId());
        System.out.println("Forwarding address: " + forwardingAddress);

        appKit = new WalletAppKit(params, new File("."), filePrefix) {
            @Override
            protected void onSetupCompleted() {
                if (wallet().getKeyChainGroupSize() < 1) {
                    wallet().importKey(new ECKey());
                }
            }
        };

        if (params == RegTestParams.get()) {
            appKit.connectToLocalHost();
        }

        // Download the block chain and wait until it's done
        appKit.startAsync();
        appKit.awaitRunning();

        // We want to know when we receive money
        appKit.wallet().addCoinsReceivedEventListener((wallet, tx, prevBalance, newBalance) -> {
            Coin value = tx.getValueSentToMe(wallet);
            System.out.println("Received tx for " + value.toFriendlyString() + ": " + tx);
            System.out.println("Transaction will be forwarded after it confirms.");

            Futures.addCallback(tx.getConfidence().getDepthFuture(1), new FutureCallback<TransactionConfidence>() {
                @Override
                public void onSuccess(@Nullable TransactionConfidence result) {
                    System.out.println("Confirmation received.");
                    forwardCoins(tx);
                }

                @Override
                public void onFailure(Throwable t) {
                    // This kind of future can't fail, just rethrow in case something weird happens.
                    throw new RuntimeException(t);
                }
            }, directExecutor());
        });


    }

    private static void forwardCoins(Transaction tx) {

    }

}
