namespace hect
{

///
/// A hierarchical structure of data.
///
/// \remarks Data values are normally constructed from JSON.  The majority of
/// asset types are defined in JSON and parsed through data values.  Once
/// constructed, a data value is immutable.
class DataValue
{
public:

    ///
    /// The underlying type used for an array.
    typedef std::vector<DataValue> ArrayType;

    ///
    /// The underlying type used for an object.
    typedef std::map<std::string, DataValue> ObjectType;

    ///
    /// A data value type.
    enum Type
    {

        ///
        /// The data value holds no data.
        Null,

        ///
        /// A bool value.
        Bool,

        ///
        /// A floating point number.
        Number,

        ///
        /// A string.
        String,

        ///
        /// An collection of other data values.
        Array,

        ///
        /// A collection of key/value pairs of data values.
        Object
    };

    ///
    /// Constructs a null data value.
    DataValue();

    ///
    /// Constructs a bool data value.
    ///
    /// \param value The bool value.
    DataValue(bool value);

    ///
    /// Constructs a number data value.
    ///
    /// \param value The number value.
    DataValue(int value);

    ///
    /// Constructs a number data value.
    ///
    /// \param value The number value.
    DataValue(unsigned value);

    ///
    /// Constructs a number data value.
    ///
    /// \param value The number value.
    DataValue(double value);

    ///
    /// Constructs a string data value.
    ///
    /// \param value The string value.
    DataValue(const char* value);

    ///
    /// Constructs a string data value.
    ///
    /// \param value The string value.
    DataValue(const std::string& value);

    ///
    /// Constructs an array of data values.
    ///
    /// \param elements The elements.
    DataValue(const ArrayType& elements);

    ///
    /// Constructs an object of data values.
    ///
    /// \param members The members.
    DataValue(const ObjectType& members);

    ///
    /// Constructs a data value moved from another.
    ///
    /// \param dataValue The data value to move.
    DataValue(DataValue&& dataValue);

    ///
    /// Returns the type.
    Type type() const;

    ///
    /// Returns this data value or another one if this data value is null.
    ///
    /// \param dataValue The data value to return if this one is null.
    const DataValue& or(const DataValue& dataValue) const;

    ///
    /// Returns whether the value is null.
    bool isNull() const;

    ///
    /// Returns whether the value is a bool.
    bool isBool() const;

    ///
    /// Returns whether the value is a number.
    bool isNumber() const;

    ///
    /// Returns whether the value is a string.
    bool isString() const;

    ///
    /// Returns whether the value is an array.
    bool isArray() const;

    ///
    /// Returns whether the value is an object.
    bool isObject() const;

    ///
    /// Returns the value as a bool (false if the data value is not a bool).
    bool asBool() const;

    ///
    /// Returns the value as an int (zero if the data value is not a number).
    int asInt() const;

    ///
    /// Returns the value as an unsigned int (zero if the data value is not a
    /// number).
    unsigned asUnsigned() const;

    ///
    /// Returns the value as a double (zero if the data value is not a number).
    double asDouble() const;

    ///
    /// Returns the value as a string (empty string if the data value is not a
    /// string).
    const std::string& asString() const;

    ///
    /// Returns the number of elements or members.
    size_t size() const;

    ///
    /// Returns the member names (empty if the data value is not an object).
    std::vector<std::string> memberNames() const;

    ///
    /// Returns the element at the given index.
    ///
    /// \remarks Only applies to data values that are arrays.
    ///
    /// \param index The index to access the element at.
    const DataValue& operator[](size_t index) const;

    ///
    /// Returns the member of the given name.
    ///
    /// \remarks Only applies to data values that are objects.
    ///
    /// \param name The name of the member to access.
    const DataValue& operator[](const std::string& name) const;

    ///
    /// Returns an iterator at the beginning of the elements.
    ///
    /// \remarks Only applies to data values that are arrays.
    ArrayType::const_iterator begin() const;

    ///
    /// Returns an iterator at the end of the elements.
    ///
    /// \remarks Only applies to data values that are arrays.
    ArrayType::const_iterator end() const;

private:
    Type _type;
    Any _data;

    static const DataValue _null;
    static const ArrayType _emptyArray;
    static const std::string _emptyString;
};

}