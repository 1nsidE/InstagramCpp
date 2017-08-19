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

    const std::string& endpoint() const noexcept;
    void setEndpoint(const std::string& endpoint);

    const std::string& host() const noexcept;
    void setHost(const std::string& host);

    HttpProtocol protocol() const noexcept;
    void setProtocol(HttpProtocol protocol);

    std::string arguments() const noexcept;
    const std::string& argument(const std::string& key) const;
    void addArgument(const std::string& key, const std::string& value);
    void addArgument(const std::initializer_list<Argument>& url);
    void addArgument(const Argument& argument);

    std::string url() const;
private:
    void parse(const std::string& url);
    void parseUrl(const std::string& url);
    void parseArguments(const std::string args);
    
    using ArgumentsMap = std::map<std::string, std::string>;
    using ArgumentsMapPtr = std::unique_ptr<ArgumentsMap>;
    ArgumentsMapPtr m_argumentsMapPtr{nullptr};
    
    std::string m_host{""};
    std::string m_endpoint{""};
    HttpProtocol m_protocol{HttpProtocol::UNKNOWN};

    friend void swap(HttpUrl& first, HttpUrl& second);
};

}

#endif
