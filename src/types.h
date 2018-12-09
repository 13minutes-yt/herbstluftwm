#ifndef HERBSTLUFT_TYPES_H
#define HERBSTLUFT_TYPES_H

#include "arglist.h"
#include <set>
#include <map>

#define Ptr(X) std::shared_ptr<X>
#define WPtr(X) std::weak_ptr<X>

/* A path in the object tree */
using Path = ArgList;

/* Types for I/O with the user */
using Output = std::ostream&;

/** The Input for a command consists of a command name
 * (known as argv[0] in a C main()) and of arguments (argv[1] up to
 * argv[argc] in a C main()).
 *
 * This class is in transition and not yet in its final state!
 * Currently, this class behaves as the ArgList. But later, ArgList will become
 * protected and so one can only use >> to access the arguments
 *
 * This means that currently, the base class holds the entire argv. Later, the
 * base class will only hold the arguments and not the command name and
 * furthermore the ArgList parent class will become private.
 */
class Input : public ArgList {
public:
    //! Initialize from a C-style main() argv array:
    //! argv[0] is the command name and the remaining entries are the
    //! parameters
    Input(const ArgList& argv);
    Input& operator>>(std::string& val);
    std::string command() const;
};

/* Primitive types that can be converted from/to user input/output */
template<typename T>
struct Converter {
    /** Parse a text into the right type
     * Throws std::invalid_argument or std::out_of_range
     * 'Source' may be given relative to 'relativeTo', e.g. "toggle" for booleans.
     */
    static T parse(const std::string& source, T const* relativeTo);

    /** Return a user-friendly string representation */
    static std::string str(T payload) { return std::to_string(payload); }
};

// Integers
template<>
inline int Converter<int>::parse(const std::string &payload, int const*) {
    return std::stoi(payload);
}
template<>
inline unsigned long Converter<unsigned long>::parse(const std::string &payload, unsigned long const*) {
    return std::stoul(payload);
}

// Booleans
template<>
inline std::string Converter<bool>::str(bool payload) {
    return { payload ? "true" : "false" };
}
template<>
inline bool Converter<bool>::parse(const std::string &payload, bool const* previous) {
    std::set<std::string> t = {"true", "on", "1"};
    std::set<std::string> f = {"false", "off", "0"};
    if (f.find(payload) != f.end())
        return false;
    else if (t.find(payload) != t.end())
        return true;
    else if (payload == "toggle" && previous)
        return !*previous;
    else throw std::invalid_argument(
            previous
            ? "only on/off/true/false/toggle are valid booleans"
            : "only on/off/true/false are valid booleans");
}

// Strings
template<>
inline std::string Converter<std::string>::str(std::string payload) { return payload; }
template<>
inline std::string Converter<std::string>::parse(const std::string &payload, std::string const*) {
    return payload;
}

// Directions (used in frames, floating)
enum class Direction { Right, Left, Up, Down };
template<>
inline Direction Converter<Direction>::parse(const std::string &payload, Direction const*) {
    std::map<char, Direction> mapping = {
        {'u', Direction::Up},   {'r', Direction::Right},
        {'d', Direction::Down}, {'l', Direction::Left},
    };
    auto it = mapping.find(payload.at(0));
    if (it == mapping.end())
        throw std::invalid_argument("Invalid direction \"" + payload + "\"");
    return it->second;
}


// Note: include x11-types.h for colors

#endif