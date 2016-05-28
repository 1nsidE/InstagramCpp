#ifndef INSTAGRAM_SERVICE
#define INSTAGRAM_SERVICE

#include <json/json.h>
#include <memory>

#include "HttpResponse.h"
#include "HttpRequest.h"
#include "HttpClient.h"
#include "HttpUrl.h"

#include "AuthorizationToken.h"
#include "MediaEntries.h"
#include "UserInfo.h"

#include "InstagramParser.h"

namespace Instagram{

using Arguments = std::initializer_list<Http::Argument>;

class InstagramClient{
public:
    InstagramClient();
    InstagramClient(const std::string& _auth_token);
    InstagramClient(InstagramClient& inst_serv) = delete;
    InstagramClient(InstagramClient&& inst_serv) = delete;
    
    void set_auth_token(const std::string& _auth_token);
    const std::string& get_auth_token() const;

//API's
     AuthorizationToken exchange_code(const std::string& code, 
			const std::string& client_id, 
			const std::string& client_secret,
			const std::string& redirect_uri);

    UserInfo get_user_info();
    MediaEntries get_user_recent_media();	
private:
    InstagramParser parser;
    Http::HttpClient http_client;
    std::string auth_token;
    
    void check_auth();
};

}

#endif
