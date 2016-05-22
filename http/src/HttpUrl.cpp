#include <HttpUrl.h>

#include "Http.h"

namespace Http{

HttpUrl::HttpUrl() : arguments_map{nullptr}, end_point{"/"}, tmp_key{nullptr}{}
HttpUrl::HttpUrl(const std::string& _end_point) : arguments_map{nullptr}, end_point{_end_point}{}

HttpUrl::HttpUrl(const HttpUrl& url) : arguments_map{ url.arguments_map ? new std::map<std::string, std::string>(*url.arguments_map) : nullptr},
    end_point{url.end_point}, 
    tmp_key{nullptr}{}

HttpUrl::HttpUrl(HttpUrl&& url) : arguments_map{url.arguments_map}, 
    end_point{std::move(url.end_point)}, 
    tmp_key{nullptr}{
        url.arguments_map = nullptr;
        url.tmp_key = nullptr;
    }

HttpUrl& HttpUrl::operator=(const HttpUrl& url){
    if(this == &url){
        return *this;
    }

    arguments_map = url.arguments_map ? new std::map<std::string, std::string>(*url.arguments_map) : nullptr;
    end_point = url.end_point;
    tmp_key = nullptr;

    return *this;
}

HttpUrl& HttpUrl::operator=(HttpUrl&& url){
    if(this == &url){
        return *this;
    }
    
    arguments_map = url.arguments_map;
    url.arguments_map = nullptr;
    end_point = std::move(url.end_point);

    tmp_key = nullptr;
    url.tmp_key = nullptr;

    return *this;
}

const std::string& HttpUrl::operator[](const std::string& key) const{
    static const std::string& empty_arg{""};
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

HttpUrl& HttpUrl::operator[](const std::string& key){
    tmp_key = & key;
    return *this;
}

HttpUrl& HttpUrl::operator=(const std::string& value){
    if(!arguments_map){
        arguments_map = new std::map<std::string, std::string>{};
    }
    if(tmp_key){
        arguments_map->insert({*tmp_key, value});
        tmp_key = nullptr;
    }
    return *this;
}

std::string HttpUrl::get_argument(const std::string& key){
    return (arguments_map && arguments_map->count(key) ? arguments_map->at(key) : "");
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
        std::string result = end_point + ARG_START_DELIMETER + get_arguments();
        return result;
    }
}

}

