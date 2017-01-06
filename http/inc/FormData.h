//
// Created by inside on 3/12/16.
//

#ifndef HTTPSERVER_FORMDATA_H
#define HTTPSERVER_FORMDATA_H

#include <string>
#include <map>
#include "Definitions.h"

namespace  Http {

class EXPORT_HTTP FormData {
public:
    FormData();
    FormData(const std::string& boundary);
    FormData(const FormData& formData);
    FormData(FormData&& formData);

    void addPair(const std::string& name, const std::string& value);
    std::string& operator[](const std::string& name);
    const std::string& operator[](const std::string& name) const;

    const std::string getString() const;
    std::string contentType() const;
private:
    std::map<std::string, std::string> m_data{};
    std::string m_boundary{};
    const char* CONTENT_DISP = "Content-Disposition: form-data; name=";
    const char* CONTENT_TYPE = "multipart/form-data; boundary=";

    friend void swap(FormData& first, FormData& second);
};

}
#endif //HTTPSERVER_FORMDATA_H
