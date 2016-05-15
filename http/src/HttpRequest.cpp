//
// Created by inside on 3/12/16.
//

#include "HttpRequest.h"

namespace Http{

HttpRequest::HttpRequest() : data(nullptr), method(Http::Method::UNKNOWN), end_point{""}{}
HttpRequest::HttpRequest(const HttpRequest& request) : HttpHeader(request), method(request.method), end_point{request.end_point}{
    data = nullptr;
    if(request.data != nullptr){
        data  = new std::string(*request.data);
    }
}

HttpRequest::HttpRequest(HttpRequest&& request) : HttpHeader(request), data(request.data), method(request.method),
                                                end_point(std::move(request.end_point)){
    request.data = nullptr;
}

HttpRequest::~HttpRequest() {
    if(data != nullptr){
        delete data;
    }
}

HttpRequest& HttpRequest::operator=(const HttpRequest& http_request){
    if(this != &http_request){
        headers_map = http_request.headers_map;
        method = http_request.method;
        end_point = http_request.end_point;

        if(data != nullptr){
            delete data;
            data = nullptr;
        }

        if(http_request.data != nullptr){
            if(data != nullptr){
                delete data;
            }
            data = new std::string{*http_request.data};
        }
    }
    return *this;
}

HttpRequest& HttpRequest::operator=(HttpRequest&& http_request){
    if(this != &http_request){
        headers_map = std::move(http_request.headers_map);

        method = method;
        http_request.method = Http::Method::UNKNOWN;
        
        end_point = std::move(http_request.end_point);
        data = http_request.data;
        http_request.data = nullptr;
    }
    return *this;
}

void HttpRequest::set_method(Http::Method _method) {
    method = _method;
}

std::string HttpRequest::get_string() const {
    if(method == Http::Method::UNKNOWN){
        return "";
    }

    std::string result = get_str(method);
    
    result += " " + end_point_with_args() + " " + HTTP_1_1 + CRLF;

    for(const auto &pair : headers_map){
        result += get_str(pair.first) + pair.second + CRLF;
    }

    if(data != nullptr){
        result += get_str(Header::CONTENT_LENGTH) + std::to_string(data->length()) + CRLF + CRLF;
        result.append(*data); 
    }else{
        result += CRLF;
    }
    return result;
}

std::string HttpRequest::end_point_with_args() const{
    if(arguments.empty()){
        return end_point;
    }else{
        std::string result = end_point + ARG_START_DELIMETER;

        for(auto it = arguments.begin(); it != arguments.end(); ++it){
            result += it->first + ARG_EQUAL + it->second;
            if(it != --arguments.end()){
                result += ARG_DELIMETER;
            }
        }

        return result;
    }
}

void HttpRequest::set_data(const std::string &_data){
    if(data == nullptr){
        data = new std::string("");
    }
    data->clear();
    data->append(_data);
}

std::string HttpRequest::get_data(){
    return data ? std::string{*data} : std::string{};
}

const std::string& HttpRequest::get_data() const{
    static const std::string empty_data{""};
    return data ? *data : empty_data;
}

void HttpRequest::add_argument(const std::string& name, const std::string& value){
    arguments[name] = value;    
}

void HttpRequest::add_argument(const Argument& argument){
    arguments.insert(argument);
}

std::string HttpRequest::get_argument(const std::string& arg_name){
    return arguments.count(arg_name) ? arguments[arg_name] : "";
}

const std::string& HttpRequest::get_argument(const std::string& arg_name) const {
    static const std::string empty_arg = "";
    return arguments.count(arg_name) ? arguments.at(arg_name) : empty_arg;
}

void HttpRequest::set_end_point(const std::string& _end_point){
    end_point = _end_point;
}

std::string HttpRequest::get_end_point(){
    return end_point;
}

const std::string& HttpRequest::get_end_point() const{
    return end_point;
}

Http::Method HttpRequest::get_method() const{
    return method;
}

}
