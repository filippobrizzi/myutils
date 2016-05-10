#include <type_traits>

namespace myutil
{

namespace tl
{

/**
 * Check wheter T is a container
 */
template<typename T, typename _ = void>
struct is_container : std::false_type {};

template<typename... Ts>
struct is_container_helper {};

template<typename T>
struct is_container<
        T,
        typename std::conditional<
            false,
            is_container_helper<
                typename T::value_type,
                typename T::size_type,
                typename T::allocator_type,
                typename T::iterator,
                typename T::const_iterator,
                decltype(std::declval<T>().size()),
                decltype(std::declval<T>().begin()),
                decltype(std::declval<T>().end()),
                decltype(std::declval<T>().cbegin()),
                decltype(std::declval<T>().cend())
                >,
            void
            >::type
        > : public std::true_type {};

/**
 * In a variadic template checks wheter all the variables are of the same type
 */
template<class T, class... Rest>
struct is_all : std::false_type {};

template<class T, class First>
struct is_all<T, First> : std::is_same<T, First> {};

template<typename T, typename First, typename... Rest>
struct is_all<T, First, Rest...>
: std::integral_constant<bool, std::is_same<T, First>::value && is_all<T, Rest...>::value>
{};

}
}