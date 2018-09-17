//
// Created by shniu on 18-7-12.
//

#include <iostream>

#include "network/define.h"
#include "network/p2p.h"
#include "network/settings.h"

using namespace std;
using namespace boost::asio;

// main
int main(int argc, char** argv) {
    cout << "Startup the metachain" << endl;

    io_service ios;

    metachain::network::settings settings;

    metachain::network::p2p network(settings);

    /// start the network, and listen on a port
    network.start();

}
