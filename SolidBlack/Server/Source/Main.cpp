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
        Engine engine("Solid Black Server", "Settings.json");

        UdpServer server(6006, 32, 2);

        TimeSpan time = engine.elapsedTime();
        while ((engine.elapsedTime() - time).seconds() < 30)
        {
            UdpEvent event = server.pollEvent();
            switch (event.type)
            {
            case UdpEvent::Connect:
                LOG_INFO(format("%s connected", event.address.toString().c_str()));
                break;
            
            case UdpEvent::Disconnect:
                LOG_INFO(format("%s disconnected", event.address.toString().c_str()));
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