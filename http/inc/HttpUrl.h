#ifndef HTTP_ARGUMENTS_H
#define HTTP_ARGUMENTS_H

#include <map>
#include <memory>
#include "Definitions.h"
#include "Http.h"

namespace Http{

using Argument = std::pair<std::string, std::string>;
class EXPORT_HTTP HttpUrl{
public:
    HttpUrl();
    HttpUrl(const std::string& url);
    HttpUrl(const std::string& host, const std::string& endpoint, HttpProtocol protocol);

    HttpUrl(const HttpUrl& url);
    HttpUrl(HttpUrl&& url);

    ~HttpUrl();

    HttpUrl& operator=(const HttpUrl& url);
    HttpUrl& operator=(HttpUrl&& url);

    const std::string& operator[](const std::string& key) const;
    std::string& operator[](const std::string& key);

    void set_endpoint(const std::string& endpoint);
    const std::string& get_endpoint() const noexcept;

    void set_host(const std::string& host);
    const std::string& get_host() const noexcept;

    void set_protocol(HttpProtocol protocol);
    HttpProtocol get_protocol() const noexcept;

    std::string get_arguments() const noexcept;
    const std::string& get_argument(const std::string& key) const;
    void add_argument(const std::string& key, const std::string& value);
    void add_argument(const std::initializer_list<Argument>& url);
    void add_argument(const Argument& argument);

    std::string get_url() const;
private:
    void parse(const std::string& url);
    void parse_url(const std::string& url);
    void parse_arguments(const std::string args);
    
    using ArgumentsMap = std::map<std::string, std::string>;
    using ArgumentsMapPtr = std::unique_ptr<ArgumentsMap>;
    ArgumentsMapPtr m_argumentsMapPtr{nullptr};
    
    std::string m_host{""};
    std::string m_endpoint{""};
    HttpProtocol m_protocol{HttpProtocol::UNKNOWN};
};

}

#endif
