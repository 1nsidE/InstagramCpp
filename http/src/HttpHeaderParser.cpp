#include <sstream>
#include <cstring>

#include "HttpHeaderParser.h"

namespace Http{

HttpResponse HttpHeaderParser::parse_response(const std::string &header){
    if(header.empty()){
        return HttpResponse{};
    }

    std::istringstream string_stream(header);
    std::string line{};
    
    std::getline(string_stream, line);  
    std::vector<std::string> tokens = tokenize(line, ' ');

    if(tokens.size() < 3){
        throw std::runtime_error("invalid response : " + line);
    }
    
    HttpResponse http_response{};
    http_response.set_status(from_int(std::stoi(trim(tokens[1]))));
    
    parse_headers(string_stream, http_response);

    size_t pos;
    if((pos = static_cast<size_t>(string_stream.tellg())) < header.length()){
        http_response.set_data(header.substr(pos, header.length() - pos));
    }

    return http_response;
}

HttpRequest HttpHeaderParser::parse_request(const std::string &header){
    if(header.empty()){
        return HttpRequest{};
    }
    
    std::istringstream string_stream(header);
    std::string line{};

    std::getline(string_stream, line);
    std::vector<std::string> tokens = tokenize(line, ' ');
    if(tokens.size() != 3){
        throw std::runtime_error({"invalid request header: " + line});
    }
    
    HttpRequest http_request{};   
    http_request.set_method(from_str<Method>(tokens[0]));
    
    std::string url_str = tokens[1];
    HttpUrl url = parse_url(url_str);
    http_request.set_url(std::move(url));

    parse_headers(string_stream, http_request);
    size_t pos;
    if((pos = static_cast<size_t>(string_stream.tellg())) < header.length()){
        http_request.set_data(header.substr(pos, header.length() - pos));
    }

    return http_request;
}

std::vector<std::string> HttpHeaderParser::tokenize(const std::string& str, const char delimeter, bool once){
    std::vector<std::string> result{};
    
    size_t j = 0;
    size_t i = 0;
    while(i < str.length()){
        j = str.find_first_of(delimeter, i + 1);
        if(j != std::string::npos){
            std::string token = trim(str.substr(i, j - i));
            result.push_back(token);
            i = j;
            if(once){
                break;
            }
        }else {
            break;
        }
    }

    if(i != 0){
        std::string token = trim(str.substr(i + 1, str.length() - (i + 1)));
        result.push_back(token);
    }else{
        result.push_back(str);
    }

    return result;
}

void HttpHeaderParser::parse_headers(std::istringstream& string_stream, HttpHeader& header){
    std::string line{};
    while(std::getline(string_stream, line)){
        if(!line.compare("\r")){
            break;
        }
        std::vector<std::string> tokens = tokenize(line, ':', true);
        if(tokens.size() != 2){
            throw std::runtime_error("invalid header : " + line);
        }
        header.add_header(from_str<Header>(tokens[0]), tokens[1]);
    }
}

std::string HttpHeaderParser::trim(const std::string &str) {
    size_t space_start_pos = str.find_first_not_of(' ');
    space_start_pos = space_start_pos == std::string::npos ? 0 : space_start_pos;
    size_t space_end_pos = str.find_last_not_of(' ');

    size_t r_start_pos = str.find_first_not_of('\r');
    r_start_pos = std::string::npos ? 0 : r_start_pos;
    size_t r_end_pos = str.find_last_not_of('\r');

    size_t n_start_pos = str.find_first_not_of('\n');
    n_start_pos = std::string::npos ? 0 : n_start_pos;
    size_t n_end_pos = str.find_last_not_of('\n');
    
    size_t first = std::max(space_start_pos, r_start_pos);
    first = std::max(first, n_start_pos);

    size_t last = std::min(space_end_pos, r_end_pos);
    last = std::min(last, n_end_pos);
    
    return str.substr(first, (last - first) + 1);
}

HttpUrl HttpHeaderParser::parse_url(const std::string& str){
    HttpUrl url{};
    size_t delimeter_pos = str.find_first_of('?',0);
    if(delimeter_pos == std::string::npos){
        url.set_end_point(str);
        return url;
    }else{
        std::vector<std::string> tokens = tokenize(str, ARG_START_DELIMETER, true);
        if(tokens.size() != 2){
            throw std::runtime_error("invalid url in request!");
        }
        url.set_end_point(tokens[0]);

        std::vector<std::string> url_str = tokenize(tokens[1], ARG_DELIMETER);
        for(std::string arg_pair : url_str){
            std::vector<std::string> args = tokenize(arg_pair, ARG_EQUAL);
            if(args.size() != 2){
                throw std::runtime_error("invalid url format!");
            }
            url.add_argument(args[0], args[1]);
        }
        return url;
    }
}

}
