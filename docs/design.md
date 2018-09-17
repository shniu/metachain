
### Plan

* 迭代一目标： 构建一个p2p网络, 可以广播消息, 每个连接的节点都能收到消息并显示出来
*   1. 启动一个节点服务，手动指定连接的节点地址
*   2. 当有一个节点连接到自己后注册到自己的已连接节点列表中
*   3. 任何一个节点都可以接受输入，将消息广播出去, 提供一个命令行输入
* 迭代二目标： 在已有的p2p网络基础之上, 做节点消息保存
*   1. 节点可以将收到的消息按照接受顺序保存在一个文件中
* 迭代三目标： 添加节点发现功能
* 迭代四目标： 给每个节点添加rpc(or http)调用服务和客户端cli命令行调用工具
* 迭代五目标： 升级消息格式，将消息封装成一个block，消息存储成为blockchain
* 迭代六目标： 为客户端程序添加公私钥对创建功能，并可以生成地址


### Design

#### p2p network

p2p 网络的通信使用 tcp 协议，需要设计一个在 tcp 协议之上信息交换的协议；p2p 网络的设计主要包括以下关键点：

- peer to peer communication message protocol


// todo 这个设计还有待改善，https://blog.csdn.net/heluan123132/article/details/46545627

表示网络各节点之间消息通信的协议，能满足根据业务的需要扩展不同的消息类型，满足处理不同的业务需要；根据现有项目的一些设计，将通信协议分为两部分：消息头和消息体，具体设计如下：

```cpp
// 消息头, message_header
// 所有的消息都以此为开始，在通信过程中先解析消息头
struct message_header {
    char guid[36];     // message guid
    char type;         // message type
    char ttl;          // message time to alive
    char hops;         // tiems of the message was forwarded
    size_t length;     // payload data size
}

// 消息体，使用 char *, 需要动态为 payload 分配内存
char * payload;

// 消息协议的设计
class message {
public:
    message();
    
    // malloc payload, 为payload动态分配内存
    virtual size_t malloc_payload();
    
    // get payload
    virtual char * payload();
    
    // get payload length
    virtual size_t payload_length();
    
    // ...

private:
    // guid
    std::string _guid;
    // 消息头
    message_header  _header;
    // 消息体
    char * _payload
}

// 对消息的扩展
class DemoMessage : public message {
public:
    DemoMessage(const char msg_type, const string &guid, const string &payload) {
      // ...
    }
}
```

- 对基础网络库的选择

我们使用 C++ 编程语言，在 C++ 中有很多高性能的并发网络库，如 `boost.asio`, `libuv`, `libevent`, `poco`, `evpp`, `muduo` 等。他们都是非常好的高性能的类库，我们择其一使用即可，经过一番的考虑和现有只是的掌握最终选择了 `boost.asio`, 它具有如下好处：

1. 支持跨平台，屏蔽了底层操作系统的不一致性
2. 支持异步非阻塞IO模型，效率高，底层基于 epoll or iocp
3. 有完善的教程
4. 有完善的代码用例和样例项目

- 网络设计

网络中的每个节点在启动的时候，都可以自动连接到网络中的其他节点上, 每个节点之间保持连接，如果连接断开，最好能重新连接。

```
// Main features
1. 网络中注册登记
2. 节点发现
3. 节点之间互发消息
4. 使用GUID标识资源
5. DHT 
6. nodes: routing overlay, routes requests
```

### Ref

#### P2P 设计参考

- [Peer to peer](https://en.wikipedia.org/wiki/Peer-to-peer)
- [Learning network programming with java](http://trackmakers.com/trackmakers.com/LIBRARY/MEDIADUMP/EBOOKS/Learning%20Network%20Programming%20with%20Java.pdf)
- [p2p 的java实现](https://github.com/metanet/p2p)

A simple unstructured P2P network implementation

- [P2P(Peer To Peer) File Sharing](https://www.geeksforgeeks.org/p2ppeer-to-peer-file-sharing/)
- [How BitTorrent Works?](https://www.geeksforgeeks.org/how-bittorrent-works/)
- [Peergos](https://github.com/Peergos/Peergos)

A decentralised, secure file storage and social network https://peergos.org

- [Ethereum Wire Protocol](https://github.com/ethereum/wiki/wiki/Ethereum-Wire-Protocol)

Peer-to-peer communications between nodes running Ethereum clients run using the underlying wire protocol.

- [RLPx: Cryptographic Network & Transport Protocol](https://github.com/ethereum/devp2p/blob/master/rlpx.md)

RLPx is a cryptographic peer-to-peer network and protocol suite which provides a general-purpose transport and interface for applications to communicate via a p2p network. RLPx is designed to meet the requirements of decentralized applications and is used by Ethereum.

- [ethereum aleth](https://github.com/ethereum/aleth)

以太坊的 C++ 实现, p2p 部分使用了 

- [bitcoin 的实现库](https://github.com/libbitcoin)

包含了比特币的实现，并做了模块化，network 部分使用了 boost.asio

- [ethereumj](https://github.com/ethereum/ethereumj)

ethereum 的 java 实现

- [libcoin network setting](https://github.com/libbitcoin/libbitcoin-server/wiki/Network-Settings)

- [ZMTP](https://rfc.zeromq.org/spec:15/ZMTP/)

ZeroMQ 中关于 TCP 之上数据读取和发送的协议设计。
