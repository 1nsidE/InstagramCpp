#include <json/json.h>

#include "InstagramClient.h"
#include "InstagramConstants.h"
#include "InstagramEndpoints.h"
#include "FormData.h"

namespace Instagram{

InstagramClient::InstagramClient() : parser{}, http_client{INSTAGRAM_HOST, Http::HttpProtocol::HTTPS}, auth_token{""}{}

std::string InstagramClient::get_auth_token() const{
    return auth_token;
}

void InstagramClient::set_auth_token(const std::string &_auth_token){
    auth_token = _auth_token;
}

Http::HttpRequest InstagramClient::get_standart_request(Http::Method method, const std::string& end_point, const Http::Arguments& args) const noexcept {
    Http::HttpRequest standart_request{};
    standart_request.add_header(Http::Header::HOST, INSTAGRAM_HOST);
    standart_request.add_header(Http::Header::ACCEPT, "*/*");
    standart_request.add_header(Http::Header::USER_AGENT, "Follograph");
    standart_request.add_header(Http::Header::CACHE_CONTROL, "no-cache");
    standart_request.add_header(Http::Header::CONNECTION, "keep-alive");

    standart_request.set_method(method);
    standart_request.set_end_point(end_point);
    
    for(const Http::Argument& arg: args){
        standart_request.add_argument(arg);
    }

    return standart_request;
}

Http::HttpResponse InstagramClient::GET(const std::string &end_point , const Http::Arguments& args) {
    return http_client << get_standart_request(Http::Method::GET, end_point, args);
}

Http::HttpResponse InstagramClient::POST(const std::string &end_point, const std::string &data, const std::string &content_type) {
    Http::HttpRequest http_request = get_standart_request(Http::Method::POST, end_point);
    http_request.set_data(data);
    http_request.add_header(Http::Header::CONTENT_TYPE, content_type);
    return http_client << http_request;
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
    
    Http::HttpResponse http_response = POST(GET_AUTH_CODE, form_data.get_string(), form_data.get_content_type());

    if(http_response.get_status() != Http::Status::OK){
        "Failed to get auth_token, response was : " + http_response.get_string();
    }

    return parser.parse_auth_token(http_response.get_data());
}

MediaEntries InstagramClient::get_user_recent_media() {
    if(auth_token.empty()){
        return "authorization token is not set";
    }

    Http::HttpResponse http_response = GET(GET_RECENT_MEDIA, {{AUTH_TOKEN_ARG, auth_token}});

    if(http_response.get_status() != Http::Status::OK){
        return "failed to get users recent media, response was : " + http_response.get_string();
    }
    
    return parser.parse_media_entries(http_response.get_data());    
}

}
