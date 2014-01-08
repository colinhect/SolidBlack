SUITE(SubjectObserver)
{
    enum class TestEventA
    {
        A = 2,
        B = 5
    };

    enum class TestEventB
    {
        A = 2,
        B = 5
    };

    class TestObserver :
        public Observer<TestEventA>,
        public Observer<TestEventB>
    {
    public:

        void receiveEvent(const TestEventA& event)
        {
            lastEventA = event;
        }

        void receiveEvent(const TestEventB& event)
        {
            lastEventB = event;
        }

        TestEventA lastEventA;
        TestEventB lastEventB;
    };

    TEST(AddNotifyAndRemove)
    {
        Subject<TestEventA> subject;

        TestObserver observer;

        subject.addObserver(observer);
        subject.notifyEvent(TestEventA::A);
        CHECK(TestEventA::A == observer.lastEventA);
        subject.notifyEvent(TestEventA::B);
        CHECK(TestEventA::B == observer.lastEventA);
        
        subject.removeObserver(observer);
        subject.notifyEvent(TestEventA::A);

        CHECK(TestEventA::B == observer.lastEventA);
    }

    TEST(MultipleObserverTypes)
    {
        Subject<TestEventA> subjectA;
        Subject<TestEventB> subjectB;

        TestObserver observer;
        
        subjectA.addObserver(observer);
        subjectB.addObserver(observer);
        
        subjectA.notifyEvent(TestEventA::A);
        CHECK(TestEventA::A == observer.lastEventA);
        
        subjectB.notifyEvent(TestEventB::A);
        CHECK(TestEventB::A == observer.lastEventB);

        subjectB.notifyEvent(TestEventB::B);
        CHECK(TestEventB::B == observer.lastEventB);
    }
}
