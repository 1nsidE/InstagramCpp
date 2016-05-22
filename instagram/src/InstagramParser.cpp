#include "InstagramParser.h"

namespace Instagram{

InstagramParser::InstagramParser() : reader{} {}

AuthorizationToken InstagramParser::parse_auth_token(const std::string& json){
    AuthorizationToken token{};   
    Json::Value root;
    if(!reader.parse(json, root, false)){
        return "Failed to parse response";

    }

    token.set_auth_token(root["access_token"].asString());
    
    const Json::Value& user = root["user"];
    token.set_id(user["id"].asString());
    token.set_user_name(user["username"].asString());
    token.set_user_bio(user["bio"].asString());
    token.set_user_full_name(user["full_name"].asString());
    token.set_user_profpic_url(user["profile_picture"].asString());
    token.set_website(user["website"].asString());
    
    return token;   
}

MediaEntries InstagramParser::parse_media_entries(const std::string& json){
    Json::Value root;
    if(!reader.parse(json, root, false)){
        return "Failed to parse response";
    };

    Json::Value data = root["data"];
    MediaEntries result{};
    if(data.isArray()){
        for(const auto& media : data){
            MediaEntry entry{};
            const Json::Value& id = media["id"];
            if(!id.isNull()) entry.set_id(id.asString());
            
            const Json::Value& type = media["type"];
            if(!type.isNull()){
                const std::string type_str = type.asString();
                if(type_str == "image"){
                    entry.set_type(MediaType::IMAGE);
                }else{
                    entry.set_type(MediaType::VIDEO);
                }
            }    
            
            {
                const Json::Value& tags = media["tags"];
                if(tags.isArray()){
                    for(auto& tag : tags){
                        entry.add_tag(tag.asString());
                    }
                }
            }

            const Json::Value& caption = media["caption"];
            if(!caption.isNull()) entry.set_caption(caption["text"].asString());

            const Json::Value& images = media["images"];
            
            const Json::Value& low_resolution = images["low_resolution"];
            if(!low_resolution.isNull()) entry.set_low_resolution(low_resolution["url"].asString());
            
            const Json::Value& thumbnail = images["thumbnail"];
            if(!thumbnail.isNull()) entry.set_thumbnail(thumbnail["url"].asString());

            const Json::Value& standart_resolution = images["standard_resolution"];
            if(!standart_resolution.isNull()) entry.set_standart_resolution(standart_resolution["url"].asString());

            const Json::Value& comments = media["comments"];
            unsigned int comments_count = comments.isNull() ? 0 : comments["count"].asUInt();
            entry.set_comments_count(comments_count);

            const Json::Value& likes = media["likes"];
            unsigned int likes_count = likes.isNull() ? 0 : likes["count"].asUInt();
            entry.set_like_count(likes_count);
            
            const Json::Value& create_time = media["created_time"];
            unsigned long created_time = create_time.isNull() ? 0 : std::stoul(create_time.asString());
            entry.set_created_time(created_time);
            
            result.add_media_entry(entry);
        }
    }
    return result;
}

std::string InstagramParser::get_error(const std::string& json){
    Json::Value root;

    if(!reader.parse(json, root, false)){
        return "Failed to parse error";
    }

    const Json::Value& meta = root["meta"];
    int code = meta["code"].asInt();
    if(code == 200){
        return "";
    }

    const Json::Value& err_msg = meta["error_message"];
    const Json::Value& err_type = meta["error_type"];
    
    if(!err_type.isNull() || !err_msg.isNull()){
        return err_type.asString() + " : " + err_msg.asString();
    }else{
        return "Unknown error with code = " + std::to_string(code);
    }



}

}
