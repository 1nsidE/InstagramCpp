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
        Http::HttpResponse response = http_client.post({GET_AUTH_CODE}, form_data.get_string(), form_data.get_content_type());
        switch(response.get_status()){
            case Http::Status::OK:
                return parser.parse_auth_token(response.get_data());
            case Http::Status::BAD_REQUEST:
                return parser.get_error(response.get_data());
            default:
                return Http::get_str(response.get_status());
        }
        
    }catch(const std::exception& err){
        return err.what();
    }
}

UserInfo InstagramClient::get_user_info(){
    return get_user_info(self);
}

UserInfo InstagramClient::get_user_info(const std::string& user_id){
    try{
        check_auth();
        Http::HttpUrl url{Users::users + user_id};
        url[AUTH_TOKEN_ARG] = auth_token; 
        
        Http::HttpResponse response = http_client.get(url);
        switch(response.get_status()){
            case Http::Status::OK:
                return parser.parse_user_info(response.get_data());
            case Http::Status::BAD_REQUEST:
                return parser.get_error(response.get_data());
            default:
                return Http::get_str(response.get_status());
        }

    }catch(const std::exception& err){
        return err.what();
    }

}

MediaEntries InstagramClient::get_recent_media(){
    return get_recent_media(self);
}

MediaEntries InstagramClient::get_recent_media(const std::string& user_id) {
    try{
        check_auth();
        Http::HttpUrl url{Users::users + user_id + '/' + Users::recent_media};
        url[AUTH_TOKEN_ARG] = auth_token;
        
        return get_media(url); 
    }catch(const std::exception& err){
        return err.what();
    }

}

MediaEntries InstagramClient::get_liked_media(){
    try{
        check_auth();
        std::string endpoint{Users::users};

        Http::HttpUrl url{endpoint + Users::self_liked};
        url[AUTH_TOKEN_ARG] = auth_token;
        
        Http::HttpResponse response = http_client.get(url);
        
        return get_media(url);
    }catch(const std::exception& err){
        return err.what();
    }
}

MediaEntries InstagramClient::get_media(const Http::HttpUrl& url){
    Http::HttpResponse response = http_client.get(url);

    switch(response.get_status()){
        case Http::Status::OK:
            return parser.parse_media_entries(response.get_data());
        case Http::Status::BAD_REQUEST:
            return parser.get_error(response.get_data());
        default:
            return Http::get_str(response.get_status());
    }

}

UsersInfo InstagramClient::search_users(const std::string& query){
    try{
        check_auth();

        std::string end_point{Users::users};
        Http::HttpUrl url{end_point + Users::search};
        url[Users::query_arg] = query;
        url[AUTH_TOKEN_ARG] = auth_token; 
        
        return get_users_info(url);
    }catch(const std::exception& err){
        return err.what();
    }
}

UsersInfo InstagramClient::get_follows(){
    try{
        check_auth();
        Http::HttpUrl url{Relationships::follows};
        url[AUTH_TOKEN_ARG] = auth_token;
        return get_users_info(url);
    }catch(const std::exception& err){
        return err.what();
    }
}

UsersInfo InstagramClient::get_followed_by(){
    try{
        check_auth();
        Http::HttpUrl url{Relationships::followed_by};
        url[AUTH_TOKEN_ARG] = auth_token;
        return get_users_info(url);
    }catch(const std::exception& err){
        return err.what();
    }
}

UsersInfo InstagramClient::get_requested_by(){
    try{
        check_auth();
        Http::HttpUrl url{Relationships::requested_by};
        url[AUTH_TOKEN_ARG] = auth_token;
        return get_users_info(url);
    }catch(const std::exception& err){
        return err.what();
    }
}

UsersInfo InstagramClient::get_users_info(const Http::HttpUrl& url){
    Http::HttpResponse response = http_client.get(url);

    switch(response.get_status()){
        case Http::Status::OK:
            return parser.parse_users_info(response.get_data());
        case Http::Status::BAD_REQUEST:
            return parser.get_error(response.get_data());
        default:
            return Http::get_str(response.get_status());
    }

}

RelationshipInfo InstagramClient::get_relationship_info(const std::string& user_id){
    std::string url = Relationships::Relationship::first_part;
    url += user_id;
    url += Relationships::Relationship::second_part;

    Http::HttpUrl http_url{url};
    http_url[AUTH_TOKEN_ARG] = auth_token;
    
    Http::HttpResponse response = http_client.get(http_url);

    switch(response.get_status()){
        case Http::Status::OK:
            return parser.parse_relationship_info(response.get_data());
        case Http::Status::BAD_REQUEST:
            return parser.get_error(response.get_data());
        default:
            return Http::get_str(response.get_status());
    }

}

}
