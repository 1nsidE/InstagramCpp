#ifndef INSTAGRAM_SERVICE
#define INSTAGRAM_SERVICE

#include <json/json.h>
#include <memory>

#include "HttpResponse.h"
#include "HttpRequest.h"
#include "HttpClient.h"
#include "AuthorizationToken.h"
#include "MediaEntries.h"
#include "InstagramParser.h"

namespace Instagram{

class InstagramClient{
public:
    InstagramClient();
    InstagramClient(const std::string& _auth_token);
    InstagramClient(InstagramClient& inst_serv) = delete;
    InstagramClient(InstagramClient&& inst_serv) = delete;
    
      
    void set_auth_token(const std::string& _auth_token);
    std::string get_auth_token() const;

//API's
     AuthorizationToken exchange_code(const std::string& code, 
			const std::string& client_id, 
			const std::string& client_secret,
			const std::string& redirect_uri);

    MediaEntries get_user_recent_media();	
private:
    InstagramParser parser;
    Http::HttpClient http_client;
    std::string auth_token;

    Http::HttpRequest get_standart_request(Http::Method method, const std::string& end_point, const Http::Arguments& args = {}) const noexcept;
    Http::HttpResponse GET(const std::string &end_point, const Http::Arguments& args = {});

    Http::HttpResponse POST(const std::string &end_point, const std::string& data, const std::string& content_type);
};

}

#endif
