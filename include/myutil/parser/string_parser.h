#pragma once
#include <string>

namespace myutil
{
namespace parser
{
class split_iterator
{
public:
    split_iterator(const std::string & ain, char ac)
        : ip(0), in(ain), c(ac)
    {
        auto newip = in.find(c);
        if(newip == std::string::npos)
        {
            np = in.size()-  ip;
        }
        else
        {
            np = newip - ip;
        }
    }

    split_iterator()
        : ip(std::string::npos), np(std::string::npos)
    {}

    std::string operator * () const
    {
        return in.substr(ip, np);
    }

    split_iterator &operator++()
    {
        if(ip == std::string::npos)
            return *this;
        else
        {
            ip += np+1;
            if(ip >= in.size())
            {
                ip = std::string::npos;
            }
            else
            {
                auto newip = in.find(c,ip);
                if(newip == std::string::npos)
                {
                    np = in.size() - ip;
                }
                else
                {
                    np = newip - ip;
                }
            }
        }
        return *this;   
    }

    bool operator != (const split_iterator & s) const 
    {
        return !(s == *this);
    }
    
    bool        operator == (const split_iterator & s) const
    {
        return s.ip == ip && ip == std::string::npos;
    }

    std::string::size_type ip, np;
    std::string in;
    char c;
};

class string_splitter
{
public:
    string_splitter(const std::string aa, char ac)
        : a(aa), c(ac)
    {}
    split_iterator begin() { return split_iterator(a, c); }
    split_iterator end() { return split_iterator(); }

    std::string a;
    char c;
};

}
}