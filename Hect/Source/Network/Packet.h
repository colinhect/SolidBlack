namespace hect
{

class Packet
{
public:
    typedef std::vector<uint8_t> Data;

    Packet(bool reliable = false);

    bool isReliable() const;

    Data& data();
    const Data& data() const;

private:
    bool _reliable;
    Data _data;
};

}