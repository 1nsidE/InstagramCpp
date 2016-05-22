#ifndef HTTP_ARGUMENTS_H
#define HTTP_ARGUMENTS_H

#include <string>
#include <map>

namespace Http{

using Argument = std::pair<std::string, std::string>;

class HttpUrl{
public:
    HttpUrl();
    HttpUrl(const std::string& _end_point);
    HttpUrl(const HttpUrl& url);
    HttpUrl(HttpUrl&& url);

    HttpUrl& operator=(const HttpUrl& url);
    HttpUrl& operator=(HttpUrl&& url);

    const std::string& operator[](const std::string& key) const;
    
    HttpUrl& operator[](const std::string& key);
    HttpUrl& operator=(const std::string& value);
    
    void set_end_point(const std::string& _end_point);
    std::string get_end_point();
    const std::string& get_end_point() const;

    std::string get_argument(const std::string& key);
    const std::string& get_argument(const std::string& key) const;

    void add_argument(const std::string& key, const std::string& value);
    void add_argument(const std::initializer_list<Argument>& url);
    void add_argument(const Argument& argument);
    
    std::string get_arguments() const noexcept;
    std::string get_url() const;
private:
    std::map<std::string, std::string>* arguments_map;
    std::string end_point;
    const std::string* tmp_key;
};

}

#endif
