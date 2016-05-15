//
// Created by inside on 3/12/16.
//

#ifndef HTTPSERVER_FORMDATA_H
#define HTTPSERVER_FORMDATA_H

#include <string>
#include <unordered_map>

namespace Http{

class FormData {
public:
    FormData(const std::string& _boundary = "##############");
    FormData(const FormData& form_data);
    FormData(FormData&& form_data);

    void add_pair(const std::string& name, const std::string& value);
    FormData& operator[](const std::string& name);
    FormData& operator=(const std::string& value);
    
    const std::string& operator[](const std::string& name) const;
    const std::string get_string() const;
    std::string get_content_type() const;
private:
    std::unordered_map<std::string, std::string> data;
    std::string boundary;
    const char* CONTENT_DISP = "Content-Disposition: form-data; name=";
    const char* CONTENT_TYPE = "multipart/form-data; boundary=";
    const std::string* tmp_name;
};

}
#endif //HTTPSERVER_FORMDATA_H
