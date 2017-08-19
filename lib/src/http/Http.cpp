#include <cstring>
#include <unordered_map>
#include <algorithm>
#include "Http.h"

namespace Http {

    std::string changeCase(const char *str, bool toUpper) {
        std::string result{str};

        std::transform(result.begin(), result.end(), result.begin(), toUpper ? ::toupper : ::tolower);
        return result;
    }

    std::string changeCase(const std::string &str, bool toUpper) {
        std::string result{str};
        std::transform(result.begin(), result.end(), result.begin(), toUpper ? ::toupper : ::tolower);

        return result;
    }

    const char *toString(Method method) noexcept {
        switch (method) {
            case Method::POST:
                return "POST";
            case Method::GET:
                return "GET";
            case Method::PUSH:
                return "PUSH";
            case Method::UPDATE:
                return "UPDATE";
            case Method::HEAD:
                return "HEAD";
            case Method::DELETE:
                return "DELETE";
            default:
                return "UNKNOWN";
        }
    }

    const char *toString(Header header) noexcept {
        switch (header) {
            case Header::CONTENT_LENGTH:
                return "content-length";
            case Header::CONTENT_TYPE:
                return "content-type";
            case Header::USER_AGENT:
                return "user-agent";
            case Header::CONNECTION:
                return "connection";
            case Header::HOST:
                return "host";
            case Header::ACCEPT:
                return "accept";
            case Header::CACHE_CONTROL:
                return "cache-control";
            case Header::SET_COOKIE:
                return "set-cookie";
            case Header::EXPIRES:
                return "expires";
            case Header::ACCEPT_ENCODING:
                return "accept-encoding";
            case Header::ACCEPT_LANGUAGE:
                return "accept-language";
            case Header::CONTENT_LANGUAGE:
                return "content-language";
            case Header::COOKIE:
                return "cookie";
            case Header::TRANSFER_ENCODING:
                return "transfer-encoding";
            case Header::LOCATION:
                return "location";
            default:
                return "unknown";
        }
    }

    const char *toString(Status status) noexcept {
        switch (status) {
            case Status::OK:
                return "OK";
            case Status::BAD_REQUEST:
                return "BAD REQUEST";
            case Status::UNAUTHORIZED:
                return "UNAUTHORIZED";
            case Status::FORBIDDEN:
                return "FORBIDDEN";
            case Status::INTERNAL_SERVER_ERROR:
                return "INTERNAL_SERVER_ERROR";
            case Status::NOT_FOUND:
                return "NOT FOUND";
            case Status::MOVED:
                return "MOVED";
            default:
                return "UNKNOWN";
        }
    }

    const char *toString(HttpProtocol protocol) noexcept {
        switch (protocol) {
            case HttpProtocol::HTTP:
                return HTTP_PROTO;
            case HttpProtocol::HTTPS:
                return HTTPS_PROTO;
            case HttpProtocol::UNKNOWN:
                return "";
        }
        return "";
    }

    Status from_int(int _status) {
        Status status = static_cast<Status>(_status);
        switch (status) {
            case Status::BAD_REQUEST:
            case Status::FORBIDDEN:
            case Status::INTERNAL_SERVER_ERROR:
            case Status::MOVED:
            case Status::NOT_FOUND:
            case Status::OK:
            case Status::UNAUTHORIZED:
                return status;
            default:
                return Status::UNKNOWN;
        }
    }

    Method fromStr(const char *str) {
        const static std::unordered_map<std::string, Method> map{
                {"POST",   Method::POST},
                {"GET",    Method::GET},
                {"HEAD",   Method::HEAD},
                {"PUSH",   Method::PUSH},
                {"UPDATE", Method::UPDATE},
                {"DELETE", Method::DELETE}
        };

        std::string method = changeCase(str, true);
        if (map.count(method)) {
            return map.at(method);
        } else {
            return Method::UNKNOWN;
        }
    }

    Method fromStr(const std::string &str) {
        return fromStr(str.c_str());
    }

    std::string trim(const std::string &str) {
        size_t space_start_pos = str.find_first_not_of(' ');
        space_start_pos = space_start_pos == std::string::npos ? 0 : space_start_pos;
        size_t space_end_pos = str.find_last_not_of(' ');

        size_t r_start_pos = str.find_first_not_of('\r');
        r_start_pos = (r_start_pos == std::string::npos ? 0 : r_start_pos);
        size_t r_end_pos = str.find_last_not_of('\r');

        size_t n_start_pos = str.find_first_not_of('\n');
        n_start_pos = (n_start_pos == std::string::npos ? 0 : n_start_pos);
        size_t n_end_pos = str.find_last_not_of('\n');

        size_t first = std::max(space_start_pos, r_start_pos);
        first = std::max(first, n_start_pos);

        size_t last = std::min(space_end_pos, r_end_pos);
        last = std::min(last, n_end_pos);

        return str.substr(first, (last - first) + 1);
    }

    std::vector<std::string> split(const std::string &str, const char delimeter, bool once) {
        std::vector<std::string> result{};

        const char *ptr = str.c_str();
        const char *end = str.size() + ptr;
        do {
            const char *begin = ptr;

            while (*ptr != delimeter && ptr < end) ++ptr;

            result.push_back(trim(std::string {begin, ptr}));
            if (once && ++ptr < end) {
                result.push_back(trim(std::string {ptr, end - 1}));
                break;
            }
        } while (end > ++ptr);

        return result;
    }
}

