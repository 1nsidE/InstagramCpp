#ifndef HTTP_ARGUMENTS_H
#define HTTP_ARGUMENTS_H

#include <string>
#include <map>

#ifdef WIN32
#include<IOSFWD>
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

namespace Http{

    using Argument = std::pair<std::string, std::string>;

#ifdef WIN32
	/*EXPIMP_TEMPLATE template class EXPORT_HTTP std::allocator<char>;
	EXPIMP_TEMPLATE template struct EXPORT_HTTP std::char_traits<char>;
	EXPIMP_TEMPLATE template class EXPORT_HTTP std::basic_string<char, std::char_traits<char>, std::allocator<char>>;*/
	EXPIMP_TEMPLATE template struct EXPORT_HTTP std::pair<std::string, std::string>;
#endif

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
