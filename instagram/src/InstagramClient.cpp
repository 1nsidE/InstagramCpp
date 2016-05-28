#include <json/json.h>
#include <exception>

#include "InstagramClient.h"
#include "InstagramConstants.h"
#include "InstagramEndpoints.h"
#include "FormData.h"

namespace Instagram{

InstagramClient::InstagramClient() : parser{}, http_client{INSTAGRAM_HOST, Http::HttpProtocol::HTTPS}, auth_token{""}{}

const std::string& InstagramClient::get_auth_token() const{
    return auth_token;
}

void InstagramClient::set_auth_token(const std::string &_auth_token){
    auth_token = _auth_token;
}

void InstagramClient::check_auth(){
    if(auth_token.empty()){
        throw std::runtime_error("not authorized");
    }
}

AuthorizationToken InstagramClient::exchange_code(const std::string& code, 
        const std::string& client_Id, 
        const std::string& client_secret,
        const std::string& redirect_uri){ 

    Http::FormData form_data{"#################"};
    form_data["code"] = code;
    form_data["client_id"] = client_Id;
    form_data["client_secret"] = client_secret;
    form_data["redirect_uri"] = redirect_uri;
    form_data["grant_type"] = AUTH_CODE_GRANT_TYPE;

    try{
        Http::HttpResponse http_response = http_client.post({GET_AUTH_CODE}, form_data.get_string(), form_data.get_content_type());
       
        if(http_response.get_status() != Http::Status::OK){
            parser.get_error(http_response.get_data());
        }
        
        return parser.parse_auth_token(http_response.get_data());
    }catch(const std::exception& err){
        return err.what();
    }
}

UserInfo InstagramClient::get_user_info(){
   try{ 
        check_auth();

        Http::HttpUrl url{USERS_SELF_INFO};
        url[AUTH_TOKEN_ARG] = auth_token;
        Http::HttpResponse response = http_client.get(url);
        
        if(response.get_status() != Http::Status::OK){
            return parser.get_error(response.get_data());
        }
        
        return parser.parse_user_info(response.get_data());
   }catch(std::exception& err){
       return err.what();
   }
}

MediaEntries InstagramClient::get_user_recent_media() {
    try{
        check_auth();
        Http::HttpUrl url{USERS_SELF_RECENT_MEDIA};
        url[AUTH_TOKEN_ARG] = auth_token;
        Http::HttpResponse http_response = http_client.get(url);

        if(http_response.get_status() != Http::Status::OK){
            return parser.get_error(http_response.get_data());
        }
        
        return parser.parse_media_entries(http_response.get_data()); 
    }catch(const std::exception& err){
        return err.what();
    }
}

}
