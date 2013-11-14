namespace hect
{

///
/// An error.
class Error :
    public std::runtime_error
{
public:

    ///
    /// Constructs an error without a message.
    Error();

    ///
    /// Constructs an error with a message.
    ///
    /// \param message The error message.
    Error(const std::string& message);
};

}