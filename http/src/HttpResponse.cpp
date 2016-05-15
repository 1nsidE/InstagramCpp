#include "HttpResponse.h"

namespace Http{

HttpResponse::HttpResponse() : data(nullptr), status(Http::Status::UNKNOWN){}

HttpResponse::HttpResponse(HttpResponse& response) : HttpHeader(response), status(response.status){
    if(response.data != nullptr){
        data = new std::string(*response.data);
    }
}

HttpResponse::HttpResponse(HttpResponse&& response) : HttpHeader(response), data(response.data), status(response.status){
    response.data = nullptr;
    response.status = Http::Status::UNKNOWN;
}

HttpResponse::~HttpResponse(){
    if(data != nullptr){
        delete data;
    }
}

void HttpResponse::set_data(const std::string& _data){
    if(data == nullptr){
        data = new std::string{_data};
    }else{
        data->clear();
        data->append(_data);
        data->shrink_to_fit();
    }
}

void HttpResponse::set_status(Http::Status _status){
    status = _status;
}

std::string HttpResponse::get_string() const{
    std::string result("");
    result.append(HTTP_1_1).append(" ").append(std::to_string(static_cast<int>(status))).append(" ").append(get_str(status)).append(CRLF);

    for(const auto &p : headers_map){
        result.append(get_str(p.first)).append(p.second).append(CRLF);
    }
    
    if(data){
        if(!headers_map.count(Http::Header::CONTENT_LENGTH)){
            result.append(Http::get_str(Http::Header::CONTENT_LENGTH)).append(std::to_string(data->length())).append(CRLF);
        }
        result.append(CRLF);
        result.append(*data);
    }else{
        result.append(CRLF);   
    }
    return result;
}

std::string HttpResponse::get_data(){
    return data ? std::string(*data) : "";
}

const std::string& HttpResponse::get_data() const{
    static const std::string empty_data{""};
    return data ? *data : empty_data;
}

Http::Status HttpResponse::get_status() const {
    return status;
}

HttpResponse &HttpResponse::operator=(HttpResponse &&http_response) {
    if(this != &http_response){
        headers_map = std::move(http_response.headers_map);
        status = http_response.status;

        data = http_response.data;
        http_response.data = nullptr;

        http_response.status = Http::Status::UNKNOWN;
    }
    return *this;
}


HttpResponse &HttpResponse::operator=(const HttpResponse& http_response) {
    if(this != &http_response){
        headers_map = http_response.headers_map;
        status = http_response.status;

        if(data != nullptr){
            delete data;
            data = nullptr;
        }

        if(http_response.data != nullptr){
            data = new std::string{*http_response.data};
        }
    }

    return *this;
}

void HttpResponse::append_data(const std::string &_data) {
    if(data == nullptr){
        data = new std::string{_data};
    }else{
        data->append(_data);
    }
}

void HttpResponse::append_data(const char *_data) {
    if(data == nullptr){
        data = new std::string{_data};
    }else{
        data->append(_data);
    }
}

void HttpResponse::append_data(const char *_data, const size_t len) {
    if(data == nullptr){
        data = new std::string{};
    }
    data->append(_data, len);
}

size_t HttpResponse::data_len() const noexcept{
    return (data == nullptr ? 0 : data->length());
}

bool HttpResponse::contain_header(Http::Header header) noexcept {
    return headers_map.count(header) > 0;
}

size_t HttpResponse::get_content_len() const {
    return (headers_map.count(Http::Header::CONTENT_LENGTH) ? static_cast<size_t>(std::stoi(headers_map.at(Http::Header::CONTENT_LENGTH))) : 0);
}

}
