//
// Created by inside on 3/12/16.
//

#ifndef HTTPSERVER_HTTPREQUEST_H
#define HTTPSERVER_HTTPREQUEST_H

#include <map>
#include "HttpHeader.h"

namespace Http{

using Argument = std::pair<std::string, std::string>;
using Arguments = std::initializer_list<Argument>;

class HttpRequest : public HttpHeader{
public:
    HttpRequest();
    HttpRequest(const HttpRequest& request);
    HttpRequest(HttpRequest&& request);
	
    virtual ~HttpRequest();

	HttpRequest& operator=(const HttpRequest& http_request);
	HttpRequest& operator=(HttpRequest&& http_request);

    void set_method(Http::Method _method);
	Http::Method get_method() const;
    
    void add_argument(const std::string& name, const std::string& value);
    void add_argument(const Argument& argument);

    std::string get_argument(const std::string& arg_name);
    const std::string& get_argument(const std::string& arg_name) const;

    void set_end_point(const std::string& _end_point);
    std::string get_end_point();
    const std::string& get_end_point() const;

	virtual void set_data(const std::string& _data);
    virtual std::string get_data();
    virtual const std::string& get_data() const;

    virtual std::string get_string() const;
private:
	std::string* data;
	Http::Method method;
    std::string end_point;
    std::map<std::string, std::string> arguments;

    std::string get_args() const;
};

}

#endif //HTTPSERVER_HTTPREQUEST_H
