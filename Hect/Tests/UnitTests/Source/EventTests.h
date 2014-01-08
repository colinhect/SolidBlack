SUITE(Event)
{
    enum class EventA
    {
        A = 1,
        B = 3
    };

    enum class EventB
    {
        A = 2,
        B = 4
    };

    class TestListener :
        public Listener<EventA>,
        public Listener<EventB>
    {
    public:

        void receiveEvent(const EventA& event)
        {
            lastEventA = event;
        }

        void receiveEvent(const EventB& event)
        {
            lastEventB = event;
        }

        EventA lastEventA;
        EventB lastEventB;
    };

    TEST(AddNotifyAndRemove)
    {
        Dispatcher<EventA> dispatcher;

        TestListener listener;

        dispatcher.addListener(listener);
        dispatcher.notifyEvent(EventA::A);
        CHECK(EventA::A == listener.lastEventA);
        dispatcher.notifyEvent(EventA::B);
        CHECK(EventA::B == listener.lastEventA);
        
        dispatcher.removeListener(listener);
        dispatcher.notifyEvent(EventA::A);

        CHECK(EventA::B == listener.lastEventA);
    }

    TEST(MultipleListenerTypes)
    {
        Dispatcher<EventA> dispatcherA;
        Dispatcher<EventB> dispatcherB;

        TestListener listener;
        
        dispatcherA.addListener(listener);
        dispatcherB.addListener(listener);
        
        dispatcherA.notifyEvent(EventA::A);
        CHECK(EventA::A == listener.lastEventA);
        
        dispatcherB.notifyEvent(EventB::A);
        CHECK(EventB::A == listener.lastEventB);

        dispatcherB.notifyEvent(EventB::B);
        CHECK(EventB::B == listener.lastEventB);
    }

    TEST(AddRegisteredListener)
    {
        Dispatcher<EventA> dispatcher;

        TestListener listener;
        
        dispatcher.addListener(listener);
        dispatcher.addListener(listener);

        dispatcher.notifyEvent(EventA::A);
        CHECK(EventA::A == listener.lastEventA);
    }

    TEST(RemoveUnregisteredListener)
    {
        Dispatcher<EventA> dispatcher;

        TestListener listener;
        dispatcher.removeListener(listener);
    }
}
