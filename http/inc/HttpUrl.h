#ifndef HTTP_ARGUMENTS_H
#define HTTP_ARGUMENTS_H

#include <map>
#include "Definitions.h"

namespace Http{
    HTTP_EXP_TMP template struct EXPORT_HTTP std::pair<std::string, std::string>;
    HTTP_EXP_TMP template class EXPORT_HTTP std::map<std::string, std::string>;

    using Argument = std::pair<std::string, std::string>;
    class EXPORT_HTTP HttpUrl{
    public:
        HttpUrl();
        HttpUrl(const std::string& endpoint);
        HttpUrl(std::initializer_list<std::string> endpoints);
        HttpUrl(std::initializer_list<const char*> endpoints);
        HttpUrl(const HttpUrl& url);
        HttpUrl(HttpUrl&& url);

        ~HttpUrl();

        HttpUrl& operator=(const HttpUrl& url);
        HttpUrl& operator=(HttpUrl&& url);

        const std::string& operator[](const std::string& key) const;
        std::string& operator[](const std::string& key);

        void set_end_point(const std::string& _end_point);
        std::string get_end_point();
        const std::string& get_end_point() const;

        const std::string& get_argument(const std::string& key) const;

        void add_argument(const std::string& key, const std::string& value);
        void add_argument(const std::initializer_list<Argument>& url);
        void add_argument(const Argument& argument);

        std::string get_arguments() const noexcept;
        std::string get_url() const;
    private:
        std::map<std::string, std::string>* arguments_map;
        std::string end_point;
    };

}

#endif
