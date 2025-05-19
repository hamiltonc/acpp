#ifndef TABLE_HPP
#define TABLE_HPP

#include <experimental/string_view>
#include <unordered_map>

class table {
public:
    table();

    std::experimental::string_view lookup(const std::string& key) const;

private:
    std::unordered_map<std::string, std::string> data_;
};

#endif /* TABLE_HPP */
