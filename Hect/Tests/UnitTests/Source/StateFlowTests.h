SUITE(StateFlow)
{
    class TestState :
        public State
    {
    public:
        TestState(const std::string& name, std::vector<std::string>& messages) :
            _name(name),
            _messages(&messages)
        {
            _messages->push_back(format("Construct %s", _name.c_str()));
        }

        ~TestState()
        {
            _messages->push_back(format("Destruct %s", _name.c_str()));
        }

    private:
        void activate()
        {
            _messages->push_back(format("Activate %s", _name.c_str()));
        }

        void deactivate()
        {
            _messages->push_back(format("Deactivate %s", _name.c_str()));
        }

        std::string _name;
        std::vector<std::string>* _messages;
    };

    TEST(BasicStateFlow)
    {
        std::vector<std::string> messages;

        State::Ref a(new TestState("A", messages));
        State::Ref b(new TestState("B", messages));
        State::Ref c(new TestState("C", messages));

        StateFlow stateFlow;
        stateFlow.push(a);
        stateFlow.push(b);
        stateFlow.push(c);

        CHECK_EQUAL(3, messages.size());
        CHECK_EQUAL("Construct A", messages[0]);
        CHECK_EQUAL("Construct B", messages[1]);
        CHECK_EQUAL("Construct C", messages[2]);
        messages.clear();
        
        CHECK(stateFlow.transition());

        CHECK_EQUAL(1, messages.size());
        CHECK_EQUAL("Activate C", messages[0]);
        messages.clear();

        c->setDone(true);
        c.reset();
        
        CHECK(stateFlow.transition());

        CHECK_EQUAL(3, messages.size());
        CHECK_EQUAL("Deactivate C", messages[0]);
        CHECK_EQUAL("Destruct C", messages[1]);
        CHECK_EQUAL("Activate B", messages[2]);
        messages.clear();

        b->setDone(true);
        b.reset();
        a->setDone(true);
        a.reset();

        CHECK(!stateFlow.transition());

        CHECK_EQUAL(5, messages.size());
        CHECK_EQUAL("Deactivate B", messages[0]);
        CHECK_EQUAL("Destruct B", messages[1]);
        CHECK_EQUAL("Activate A", messages[2]);
        CHECK_EQUAL("Deactivate A", messages[3]);
        CHECK_EQUAL("Destruct A", messages[4]);
    }
}