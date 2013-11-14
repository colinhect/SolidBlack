#include <Hect.h>

using namespace hect;

#ifdef HECT_WINDOWS
#ifdef HECT_DEBUG
#include <vld.h>
#endif
#endif

int main()
{
    try
    {
        Engine engine("Solid Black Client", "Settings.json");

        IpAddress address = IpAddress::localAddress();

        UdpClient client(address, 6006, 2);

        TimeSpan time = engine.elapsedTime();
        while ((engine.elapsedTime() - time).seconds() < 500)
        {
            UdpEvent event = client.pollEvent();
            switch (event.type)
            {
            case UdpEvent::Connect:
                LOG_INFO("Connected");
                break;
            case UdpEvent::Disconnect:
                LOG_INFO("Disconnected");
                break;
            }
        }
    }
    catch (std::exception& e)
    {
        Engine::fatalError(e.what());
    }

    return 0;
}