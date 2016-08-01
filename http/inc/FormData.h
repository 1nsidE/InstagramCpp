//
// Created by inside on 3/12/16.
//

#ifndef HTTPSERVER_FORMDATA_H
#define HTTPSERVER_FORMDATA_H

#include <string>
#include <map>

#ifdef WIN32
#include<xstring>
#ifdef HTTP_LIB_EXPORT
#define EXPORT_HTTP __declspec(dllexport)
#define EXPIMP_TEMPLATE
#else
#define EXPORT_HTTP __declspec(dllimport)
#define EXPIMP_TEMPLATE extern
#endif

#else
#ifdef __linux__
#define EXPORT_HTTP
#define EXPIMP_TEMPLATE
#endif
#endif

#ifdef WIN32
/*EXPIMP_TEMPLATE template class EXPORT_HTTP std::allocator<char>;
EXPIMP_TEMPLATE template struct EXPORT_HTTP std::char_traits<char>;
EXPIMP_TEMPLATE template class EXPORT_HTTP std::basic_string<char, std::char_traits<char>, std::allocator<char>>;*/
EXPIMP_TEMPLATE template class EXPORT_HTTP std::map<std::string, std::string>;
#endif

namespace  Http{

    class EXPORT_HTTP FormData {
    public:
        FormData(const std::string& _boundary = "##############");
        FormData(const FormData& form_data);
        FormData(FormData&& form_data);

        void add_pair(const std::string& name, const std::string& value);
        std::string& operator[](const std::string& name);
        const std::string& operator[](const std::string& name) const;

        const std::string get_string() const;
        std::string get_content_type() const;
    private:
        std::map<std::string, std::string> data;
        std::string boundary;
        const char* CONTENT_DISP = "Content-Disposition: form-data; name=";
        const char* CONTENT_TYPE = "multipart/form-data; boundary=";
    };

}
#endif //HTTPSERVER_FORMDATA_H
