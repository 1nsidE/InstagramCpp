#ifndef INSTAGRAM_SERVICE
#define INSTAGRAM_SERVICE

#include "HttpResponse.h"
#include "HttpRequest.h"
#include "HttpClient.h"
#include "HttpUrl.h"

#include "AuthorizationToken.h"
#include "MediaEntries.h"
#include "UserInfo.h"
#include "UsersInfo.h"

#include "InstagramParser.h"

namespace Instagram{

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
//Users
    UserInfo get_user_info();
    UserInfo get_user_info(const std::string& user_id);
    MediaEntries get_recent_media();
    MediaEntries get_recent_media(const std::string& user_id);
    MediaEntries get_liked_media();
    UsersInfo search_users(const std::string& query);
//Relationships
    UsersInfo get_follows();
    UsersInfo get_followed_by();
    UsersInfo get_requested_by();
private:
    InstagramParser parser;
    Http::HttpClient http_client;
    std::string auth_token;
   
    UsersInfo get_users_info(const Http::HttpUrl& url);    
    MediaEntries get_media(const Http::HttpUrl& url);

    void check_auth();
};

}

#endif
