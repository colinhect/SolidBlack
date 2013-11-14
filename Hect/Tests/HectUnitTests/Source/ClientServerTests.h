SUITE(ClientServer)
{
    /*
    TEST(LocalConnectAndDisconnect)
    {
        TaskPool taskPool(4);

        Task serverTask = taskPool.enqueue([]
        {
            Server server(7001, 32, 2);
            
            Server::Event event = server.pollEvent(TimeSpan::fromSeconds(2));
            if (event.type == Server::Event::Connect)
            {
                LOG_INFO(format("%s connected", event.clientAddress.toString().c_str()));
            }
        });

        Task clientTask = taskPool.enqueue([]
        {
            IpAddress address = IpAddress::localAddress();
            LOG_INFO(format("Connecting to %s", address.toString().c_str()));

            Client client(2);
            if (client.connect(address, 7001, TimeSpan::fromSeconds(2)))
            {
                LOG_INFO("Connected to server");
            }
            else
            {
                LOG_INFO("Failed to connect to server");
            }
        });
        
        clientTask.wait();
        serverTask.wait();
    }
    */
}