#include <sstream>
#include "HttpUrl.h"

namespace Http {

HttpUrl::HttpUrl() {}

HttpUrl::HttpUrl(const std::string& url){
    parse(url);
}

HttpUrl::HttpUrl(const std::string& host, const std::string& endpoint, HttpProtocol protocol) : m_host{host}, m_endpoint{endpoint}, m_protocol{protocol} {}

HttpUrl::HttpUrl(const HttpUrl& url) : m_host{url.m_host}, m_endpoint {url.m_endpoint}, m_protocol{url.m_protocol}{
    if(url.m_argumentsMapPtr){
        m_argumentsMapPtr = std::make_unique<ArgumentsMap>(*url.m_argumentsMapPtr);
    }
}

HttpUrl::HttpUrl(HttpUrl&& url) : HttpUrl{} {
    swap(*this, url);
}

HttpUrl::~HttpUrl() {}

HttpUrl& HttpUrl::operator=(const HttpUrl& url) {
    HttpUrl copy{url};
    
    swap(*this, copy);
    return *this;
}

HttpUrl& HttpUrl::operator=(HttpUrl&& url) {
    swap(*this, url);
    
    HttpUrl temp{};
    swap(url, temp);

    return *this;
}

const std::string& HttpUrl::operator[](const std::string& key) const {
    const static std::string& emptyArg {""};
    return (m_argumentsMapPtr && m_argumentsMapPtr->count(key) ? m_argumentsMapPtr->at(key) : emptyArg);
}

void HttpUrl::setEndpoint(const std::string& endpoint) {
    m_endpoint = endpoint;
}

const std::string& HttpUrl::endpoint() const noexcept{
    return m_endpoint;
}

void HttpUrl::setHost(const std::string& host){
    m_host = host;
}

const std::string& HttpUrl::host() const noexcept{
    return m_host;
}

void HttpUrl::setProtocol(HttpProtocol protocol){
    m_protocol = protocol;
}

HttpProtocol HttpUrl::protocol() const noexcept{
    return m_protocol;
}

std::string& HttpUrl::operator[](const std::string& key) {
    if (!m_argumentsMapPtr) {
        m_argumentsMapPtr = std::make_unique<ArgumentsMap>();
    }
    return m_argumentsMapPtr->operator[](key);
}

const std::string& HttpUrl::argument(const std::string& key) const {
    const static std::string emptyArg {""};
    return (m_argumentsMapPtr && m_argumentsMapPtr->count(key) ? m_argumentsMapPtr->at(key) : emptyArg);
}

void HttpUrl::addArgument(const std::string& key, const std::string& value) {
    if (!m_argumentsMapPtr) {
        m_argumentsMapPtr = std::make_unique<ArgumentsMap>();
    }
    m_argumentsMapPtr->insert({ key, value });
}

void HttpUrl::addArgument(const std::initializer_list<Argument>& url) {
    if (!m_argumentsMapPtr) {
        m_argumentsMapPtr = std::make_unique<ArgumentsMap>();
    }

    for (const Argument& argument : url) {
        m_argumentsMapPtr->insert(argument);
    }
}

void HttpUrl::addArgument(const Argument& argument) {
    if (!m_argumentsMapPtr) {
        m_argumentsMapPtr = std::make_unique<ArgumentsMap>();
    }

    m_argumentsMapPtr->insert(argument);
}

std::string HttpUrl::arguments() const noexcept {
    if (m_argumentsMapPtr == nullptr || m_argumentsMapPtr->empty()) {
        return "";
    }

    std::string result {};
    size_t i = m_argumentsMapPtr->size();
    for (const auto& argument : *m_argumentsMapPtr) {
        result += argument.first + ARG_EQUAL + argument.second;
        if (--i) {
            result += ARG_DELIMETER;
        }
    }

    return result;
}

std::string HttpUrl::url() const {
    std::ostringstream os;
    os << toString(m_protocol) << HTTP_PROTO_DELIMETER << m_host << m_endpoint;
    
    std::string argumentsStr = arguments();

    if(!argumentsStr.empty()) {
        os << ARG_START_DELIMETER + argumentsStr;
    }
    return os.str();
}

void HttpUrl::parse(const std::string &url) {
    std::vector<std::string> urlAndArgs = split(url, ARG_START_DELIMETER, true);
    parseUrl(urlAndArgs[0]);

    if(urlAndArgs.size() > 1){
        parseArguments(urlAndArgs[1]);
    }   
}

void HttpUrl::parseUrl(const std::string& url){
    size_t colonPos = url.find_first_of(':');

    if(colonPos != std::string::npos){
        std::string protocol = changeCase(url.substr(0, colonPos));

        if(protocol == "http"){
            m_protocol = HttpProtocol::HTTP;
        }else if(protocol == "https"){
            m_protocol = HttpProtocol::HTTPS;
        }
        colonPos += 3;
    }else{
        colonPos = 0;
    }

    size_t hostEnd = url.find_first_of('/', colonPos);
    m_host = changeCase(url.substr(colonPos, hostEnd - colonPos));
    if(hostEnd != std::string::npos){
        m_endpoint = changeCase(url.substr(hostEnd));
    }
}

void HttpUrl::parseArguments(const std::string args) {
    std::vector<std::string> url_str = split(args, ARG_DELIMETER);
    for (std::string arg_pair : url_str) {
        std::vector<std::string> argsVec = split(arg_pair, ARG_EQUAL, true);
        if (argsVec.size() != 2) {
            throw std::runtime_error("invalid url format!");
        }

        addArgument(argsVec[0], argsVec[1]);
    }
}

void swap(HttpUrl& first, HttpUrl& second){
    using std::swap;
    swap(first.m_argumentsMapPtr, second.m_argumentsMapPtr);
    swap(first.m_host, second.m_host);
    swap(first.m_endpoint, second.m_endpoint);
    swap(first.m_protocol, second.m_protocol);
}

}

