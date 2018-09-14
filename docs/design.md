
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

表示网络各节点之间消息通信的协议，能满足根据业务的需要扩展不同的消息类型，满足处理不同的业务需要；根据现有项目的一些设计，将通信协议分为两部分：消息头和消息体，具体设计如下：

```
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

