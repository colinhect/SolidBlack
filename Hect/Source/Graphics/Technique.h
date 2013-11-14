namespace hect
{

///
/// An implementation of a material.
///
/// \remarks A technique is made up of multiple passes.
class Technique
{
public:

    ///
    /// An array of techniques.
    typedef std::vector<Technique> Array;

    ///
    /// Constructs a technique without any passes.
    Technique();

    ///
    /// Constructs a technique given its passes.
    ///
    /// \param passes The passes to include in the technique.
    Technique(const Pass::Array& passes);

    ///
    /// Returns the passes.
    Pass::Array& passes();

    ///
    /// Returns the passes.
    const Pass::Array& passes() const;

private:
    Pass::Array _passes;
};

}