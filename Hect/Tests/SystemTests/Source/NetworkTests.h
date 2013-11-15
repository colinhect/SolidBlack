void runTestServer(unsigned maxConnectionCount, uint8_t channelCount)
{
    Socket socket(6006, maxConnectionCount, channelCount);

    bool connection = false;
    bool disconnection = false;

    Socket::Event event;
    while (socket.pollEvent(event, TimeSpan::fromMilliseconds(5000)))
    {
        if (event.type == Socket::Event::Connect)
        {
            connection = true;
        }
        else if (event.type == Socket::Event::Disconnect)
        {
            disconnection = true;
            break;
        }
    }
            
    CHECK(connection);
    CHECK(disconnection);
}

void runTestClient(unsigned maxConnectionCount, uint8_t channelCount)
{
    Socket socket(maxConnectionCount, channelCount);
    Peer server = socket.connectToPeer(IpAddress::localAddress(), 6006);

    bool connection = false;
    bool disconnection = false;

    Socket::Event event;
    while (socket.pollEvent(event, TimeSpan::fromMilliseconds(500)))
    {
        if (event.type == Socket::Event::Connect)
        {
            connection = true;
        }
    }

    CHECK_EQUAL(Peer::Connected, server.state());

    if (connection)
    {
        socket.disconnectFromPeer(server);

        while (socket.pollEvent(event, TimeSpan::fromMilliseconds(500)))
        {
            if (event.type == Socket::Event::Disconnect)
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
            runTestServer(1, 1);
        });

        Task clientTask = taskPool.enqueue([]
        {
            runTestClient(1, 1);
        });

        clientTask.wait();
        serverTask.wait();
    }
}