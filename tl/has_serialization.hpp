#pragma once

#include <type_traits>
#include <string>

namespace myutil
{
namespace tl
{

/**
 * USAGE:
 *  call serialize(obj) on an object,
 *  the compiler will check if one of the following function is implemented:
 *  - obj.serialize()
 *  - obj.to_string()
 *  - to_string(obj)
 *  - std::to_string(obj)
 *  If non of the previous is implemented the empty string is returned.
 */

template <typename T, typename = std::string>
struct has_serialize
        : std::false_type
{};
template <typename T>
struct has_serialize<T, decltype(std::declval<T>().serialize())>
        : std::true_type
{};


template <typename T, typename = std::string>
struct has_to_string
        : std::false_type
{};
template <typename T>
struct has_to_string<T, decltype(std::declval<T>().to_string())>
        : std::true_type
{};

template <typename T, typename = std::string>
struct has_std_to_string
        : std::false_type
{};
template <typename T>
struct has_std_to_string<T, decltype(std::to_string(std::declval<T>()))>
        : std::true_type
{};

template <class T>
typename std::enable_if<has_std_to_string<T>::value, std::string>::type
to_std_string(const T& obj)
{
    return std::to_string(obj);
}

template <class T>
typename std::enable_if<!has_std_to_string<T>::value, std::string>::type
to_std_string(const T& obj)
{
    return "";
}

template <class T>
typename std::enable_if<has_to_string<T>::value, std::string>::type
to_string(const T& obj)
{
    return obj.to_string();
}

template <class T>
typename std::enable_if<!has_to_string<T>::value, std::string>::type
to_string(const T& obj)
{
    return to_std_string(obj);
}

template <class T>
typename std::enable_if<has_serialize<T>::value, std::string>::type
serialize(const T& obj)
{
    return obj.serialize();
}

template <class T>
typename std::enable_if<!has_serialize<T>::value, std::string>::type
serialize(const T& obj)
{
    return to_string(obj);
}

}
}