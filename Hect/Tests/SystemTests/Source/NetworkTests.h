void runTestServer(unsigned maxConnectionCount, uint8_t channelCount, std::function<void(Socket&, SocketEvent&)> eventHandler)
{
    Socket socket(6006, maxConnectionCount, channelCount);

    bool connection = false;
    bool disconnection = false;

    SocketEvent event;
    while (socket.pollEvent(event, TimeSpan::fromMilliseconds(5000)))
    {
        eventHandler(socket, event);

        if (event.type == SocketEventType::Connect)
        {
            connection = true;
        }
        else if (event.type == SocketEventType::Disconnect)
        {
            disconnection = true;
            break;
        }
    }
            
    CHECK(connection);
    CHECK(disconnection);
}

void runTestClient(unsigned maxConnectionCount, uint8_t channelCount, std::function<void(Socket&, SocketEvent&)> eventHandler)
{
    Socket socket(maxConnectionCount, channelCount);
    Peer server = socket.connectToPeer(IpAddress::localAddress(), 6006);

    bool connection = false;
    bool disconnection = false;

    SocketEvent event;
    while (socket.pollEvent(event, TimeSpan::fromMilliseconds(500)))
    {
        eventHandler(socket, event);

        if (event.type == SocketEventType::Connect)
        {
            connection = true;
        }
    }

    CHECK(PeerState::Connected == server.state());

    if (connection)
    {
        socket.disconnectFromPeer(server);

        while (socket.pollEvent(event, TimeSpan::fromMilliseconds(500)))
        {
            if (event.type == SocketEventType::Disconnect)
            {
                disconnection = true;
            }
        }
    }
            
    CHECK(connection);
    CHECK(disconnection);
}


SUITE(Network)
{
    TEST(ConnectionAndDisconnection)
    {
        TaskPool taskPool(4);

        Task serverTask = taskPool.enqueue([]
        {
            runTestServer(1, 1, [] (Socket&, SocketEvent&) { });
        });

        Task clientTask = taskPool.enqueue([]
        {
            runTestClient(1, 1, [] (Socket&, SocketEvent&) { });
        });

        clientTask.wait();
        serverTask.wait();
    }

    TEST(SendAndReceivePacket)
    {
        TaskPool taskPool(4);

        Task serverTask = taskPool.enqueue([]
        {
            runTestServer(1, 1, [] (Socket& socket, SocketEvent& event)
            {
                if (event.type == SocketEventType::Connect)
                {
                    Packet packet(PacketFlag::Reliable);

                    PacketWriteStream stream = packet.writeStream();
                    stream.writeString("Hello");

                    socket.sendPacket(event.peer, 0, packet);
                    socket.flush();
                }
            });
        });

        Task clientTask = taskPool.enqueue([]
        {
            runTestClient(1, 1, [] (Socket& socket, SocketEvent& event)
            {
                if (event.type == SocketEventType::Receive)
                {
                    PacketReadStream stream = event.packet.readStream();
                    std::string message = stream.readString();
                    CHECK_EQUAL("Hello", message);
                }
            });
        });

        clientTask.wait();
        serverTask.wait();
    }
}