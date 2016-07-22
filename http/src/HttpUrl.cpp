#include "HttpUrl.h"
#include "Http.h"

namespace Http{

HttpUrl::HttpUrl() : arguments_map{nullptr}, end_point{"/"}{}

HttpUrl::HttpUrl(const std::string& endpoint) : arguments_map{nullptr}, end_point{endpoint}{}

HttpUrl::HttpUrl(std::initializer_list<std::string> endpoints) : arguments_map{nullptr}{
    for(std::string str : endpoints){
        end_point += str;
    }
}

HttpUrl::HttpUrl(std::initializer_list<const char*> endpoints) : arguments_map{nullptr}{
    for(const char* str : endpoints){
        if(str == nullptr){
            throw std::invalid_argument("endpoint part cannot be nullptr");
        }
        end_point += str;
    }
}

HttpUrl::HttpUrl(const HttpUrl& url) : arguments_map{ url.arguments_map ? new std::map<std::string, std::string>(*url.arguments_map) : nullptr}, end_point{url.end_point}{}

HttpUrl::HttpUrl(HttpUrl&& url) : arguments_map{url.arguments_map}, end_point{std::move(url.end_point)}{
        url.arguments_map = nullptr;
}

HttpUrl::~HttpUrl(){
    if(arguments_map){
        delete arguments_map;
        arguments_map = nullptr;
    }   
}

HttpUrl& HttpUrl::operator=(const HttpUrl& url){
    if(this == &url){
        return *this;
    }

    arguments_map = url.arguments_map ? new std::map<std::string, std::string>(*url.arguments_map) : nullptr;
    end_point = url.end_point;

    return *this;
}

HttpUrl& HttpUrl::operator=(HttpUrl&& url){
    if(this == &url){
        return *this;
    }
    
    arguments_map = url.arguments_map;
    url.arguments_map = nullptr;
    end_point = std::move(url.end_point);

    return *this;
}

const std::string& HttpUrl::operator[](const std::string& key) const{
    const static std::string& empty_arg{""};
    return (arguments_map && arguments_map->count(key) ? arguments_map->at(key) : empty_arg);
}

void HttpUrl::set_end_point(const std::string& _end_point){
    end_point = _end_point;
}

std::string HttpUrl::get_end_point(){
    return end_point;
}

const std::string& HttpUrl::get_end_point() const{
    return end_point;
}

std::string& HttpUrl::operator[](const std::string& key){
    if(!arguments_map){
        arguments_map = new std::map<std::string, std::string>();
    }
    return arguments_map->operator[](key);
}

const std::string& HttpUrl::get_argument(const std::string& key) const{
    const static std::string empty_arg{""};
    return (arguments_map && arguments_map->count(key) ? arguments_map->at(key) : empty_arg);
}

void HttpUrl::add_argument(const std::string& key, const std::string& value){
    if(!arguments_map){
        arguments_map = new std::map<std::string, std::string>{};
    }
    arguments_map->insert({key, value});
}

void HttpUrl::add_argument(const std::initializer_list<Argument>& url){
    if(!arguments_map){
        arguments_map = new std::map<std::string, std::string>{};
    }
    for(const Argument& argument : url){
        arguments_map->insert(argument);
    }
}

void HttpUrl::add_argument(const Argument& argument){
    if(!arguments_map){
        arguments_map = new std::map<std::string, std::string>{};
    }
    arguments_map->insert(argument);
}

std::string HttpUrl::get_arguments() const noexcept{
    if(arguments_map == nullptr || arguments_map->empty()){
        return "";
    }

    std::string result{};
    size_t i = arguments_map->size();
    for(const auto& argument : *arguments_map){
        result += argument.first + ARG_EQUAL + argument.second;
        if(--i){
            result += ARG_DELIMETER;
        }
    }

    return result;
}

std::string HttpUrl::get_url() const {
    if(arguments_map == nullptr || arguments_map->empty()){
        return end_point;
    }else{
        std::string result{end_point};
        if(result[result.length() - 1] != '/'){
            result += '/';
        }
        result += ARG_START_DELIMETER + get_arguments();
        return result;
    }
}

}

