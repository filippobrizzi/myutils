#pragma once
#include <type_traits>
#include <unordered_map>
#include <map>

namespace myutil
{
namespace tl
{

template<std::size_t...>
struct int_sequence
{};

template<std::size_t N, std::size_t... Is>
struct make_int_sequence
    : make_int_sequence<N-1, N-1, Is...>
{};

template<std::size_t... Is>
struct make_int_sequence<0, Is...>
    : int_sequence<Is...>
{};

/// Used to iterate over the keys of a map
template < template <typename...> class Template, typename T >
struct is_specialization_of : std::false_type {};

template < template <typename...> class Template, typename... Args >
struct is_specialization_of< Template, Template<Args...> > : std::true_type {};

template < template <typename...> class Template, typename... Args >
struct is_specialization_of< Template, const Template<Args...> > : std::true_type {};

template<class A, class B>
struct or_ : std::integral_constant<bool, A::value || B::value>{};

template<class T>
struct check_container
  : or_<is_specialization_of<std::map, T>,
        is_specialization_of<std::unordered_map, T>
       >{};

struct Key {};
struct Value {};

template<class T>
struct check_spec
  : or_<std::is_same<Key, T>,
        std::is_same<Value, T>
       >{};

template <class MapClass, class T>
struct map_access
{
    static_assert(check_container<MapClass>::value,
    			  "Container not valid, only std::map or std::unordered_map");
    static_assert(check_spec<T>::value, "No a Key or Value");

    using map_t = MapClass;

    struct iterator
    {
        using iterator_t = typename std::conditional<std::is_const<map_t>::value,
                                                     typename map_t::const_iterator,
                                                     typename map_t::iterator
                                                    >::type;
        
        using pre_value_t = typename std::conditional<std::is_same<T, Key>::value,
                                                      typename map_t::key_type,
                                                      typename map_t::mapped_type
                                                    >::type;

        using value_t = typename std::conditional<std::is_const<map_t>::value,
                                                  typename std::add_const<pre_value_t>::type,
                                                  pre_value_t
                                                 >::type;
        iterator_t base_iterator;

        iterator(iterator_t itr)
            : base_iterator(itr)
        {}
        
        bool operator != (const iterator& o) const
        {
            return base_iterator != o.base_iterator;
        }

        template<class U = T>
        typename std::enable_if<std::is_same<Key, U>::value, typename std::add_const<value_t>::type>::type operator*()
        {
            return base_iterator->first;
        }
        template<class U = T>
        typename std::enable_if<!std::is_same<Key, U>::value, typename std::add_lvalue_reference<value_t>::type>::type operator*()
        {
            return base_iterator->second;
        }
        template<class U = T>
        typename std::enable_if<std::is_same<Key, U>::value, typename std::add_pointer<typename std::add_const<value_t>::type>::type>::type operator->()
        {
            return &base_iterator->first;
        }
        template<class U = T>
        typename std::enable_if<!std::is_same<Key, U>::value, typename std::add_pointer<value_t>::type>::type operator->()
        {
            return &base_iterator->second;
        }

        iterator & operator++()
        {
            ++base_iterator;
            return * this;
        }

        iterator operator++(int)
        {
            iterator itr(*this);
            ++base_iterator;
            return itr;
        }
    };

    map_access(map_t & x) : x_(x) {}
    iterator begin() { return iterator(x_.begin()); }
    iterator end()   { return iterator(x_.end());   }
    std::size_t size() const { return x_.size(); }
private:
    map_t & x_;
};

template <class Map>
map_access<Map, Key> map_keys_iteration(Map& x)
{
    return map_access<Map, Key>(x);
}
template <class Map>
map_access<const Map, Key> map_keys_iteration(const Map& x)
{
    return map_access<const Map, Key>(x);
}
template <class Map>
map_access<Map, Value> map_values_iteration(Map& x)
{
    return map_access<Map, Value>(x);
}
template <class Map>
map_access<const Map, Value> map_values_iteration(const Map& x)
{
    return map_access<const Map, Value>(x);
}
}
}
