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
        return "Failed to parse media entries";
    };

    const Json::Value& data = root["data"];
    MediaEntries result{};
    if(data.isArray()){
        for(const auto& media : data){
            result << get_media_entry(media);
        }
    }
    return result;
}

MediaEntry InstagramParser::parse_media_entry(const std::string& json){
    Json::Value root;
    if(!reader.parse(json, root, false)){
        return "Failed to parse media entry";
    }

    const Json::Value& data = root["data"];
    return get_media_entry(data);
}

MediaEntry InstagramParser::get_media_entry(const Json::Value& media){
    MediaEntry entry{};
    
    const Json::Value& tags = media["tags"];
    if(tags.isArray()){
        for(const auto& tag : tags){
            entry.add_tag(tag.asString());
        }
    }

    const Json::Value& users_in_photo = media["users_in_photo"];
    if(users_in_photo.isArray()){
        for(const auto& user : users_in_photo){
            entry.add_user_in_photo(user.asString());
        }
    }
               
    const Json::Value& type = media["type"];
    if(!type.isNull()){
        const std::string type_str = type.asString();
        if(type_str == "image"){
            entry.set_type(MediaType::IMAGE);
        }else{
            entry.set_type(MediaType::VIDEO);
        }
    }    
     
    const Json::Value& create_time = media["created_time"];
    long created_time = create_time.isNull() ? -1 : std::stol(create_time.asString());
    entry.set_created_time(created_time);
    
    const Json::Value& link = media["link"];
    if(!link.isNull()) entry.set_url(link.asString());

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
    int comments_count = comments.isNull() ? -1 : comments["count"].asInt();
    
    entry.set_comments_count(comments_count);
    
    const Json::Value& filter = media["filter"];
    entry.set_filter(filter.asString());

    const Json::Value& likes = media["likes"];
    int likes_count = likes.isNull() ? -1 : likes["count"].asInt();
    entry.set_like_count(likes_count);
   
    const Json::Value& id = media["id"];
    if(!id.isNull()) entry.set_id(id.asString());

    return entry;
}

UserInfo InstagramParser::parse_user_info(const std::string& json){
    Json::Value root;

    if(!reader.parse(json, root, false)){
        return "Failed to parse user info";
    }
    
    const Json::Value& data = root["data"];
    return get_user_info(data);
}

UsersInfo InstagramParser::parse_users_info(const std::string& json){
    Json::Value root;
    if(!reader.parse(json, root, false)){
        return "Failed to parse users info";
    }
    
    const Json::Value& data = root["data"];
    UsersInfo users_info{};
    for(const Json::Value& user_info : data){
        users_info << get_user_info(user_info);
    }

    return users_info;
}

UserInfo InstagramParser::get_user_info(const Json::Value &info) {
    UserInfo user_info{};

    user_info.set_id(info["id"].asString());
    user_info.set_username(info["username"].asString());
    user_info.set_prof_pic_url(info["profile_picture"].asString());

    const Json::Value& fullname = info["full_name"];
    if(fullname.isNull()){
        user_info.set_name(info["first_name"].asString());
    }else{
        user_info.set_name(fullname.asString());
    }

    user_info.set_last_name(info["last_name"].asString());
    user_info.set_bio(info["bio"].asString());
    user_info.set_website(info["website"].asString());

    const Json::Value& counts = info["counts"];
    if(!counts.isNull()) {
        const Json::Value &followed_by = counts["followed_by"];
        user_info.set_followed_by(followed_by.isNull() ? -1 : followed_by.asInt());

        const Json::Value &follows = counts["follows"];
        user_info.set_follows(follows.isNull() ? -1 : follows.asInt());

        const Json::Value &media_count = counts["media"];
        user_info.set_media_count(counts.isNull() ? -1 : media_count.asInt());
    }

    return user_info;
}

RelationshipInfo InstagramParser::parse_relationship_info(const std::string& json){
    Json::Value root{};
    if(!reader.parse(json, root, false)){
        return "Failed to parse relationship info";
    }

    const Json::Value& data = root["data"];
    RelationshipInfo rel_info{data["incoming_status"].asString(), data["outgoing_status"].asString()};

    return rel_info;
}

TagInfo InstagramParser::parse_tag_info(const std::string& json){
    Json::Value root{};

    if(!reader.parse(json, root, false)){
        return "Failed to parse tag info";
    }

    const Json::Value& data = root["data"];
    TagInfo tag_info(data["name"].asString(), data["media_count"].asInt());

    return tag_info;
}

TagsInfo InstagramParser::parse_tags_info(const std::string& json){
    Json::Value root{};

    if(!reader.parse(json, root, false)){
        return "Failed to parse tags info";
    }

    TagsInfo tags_info;
    const Json::Value& data = root["data"];
    if(data.isArray()){
        for(const auto& tag : data){
            tags_info << TagInfo{tag["name"].asString(), tag["media_count"].asInt()};
        }
    }

    return tags_info;
}

CommentsInfo InstagramParser::parse_comments(const std::string& json){
    Json::Value root{};
    if(!reader.parse(json, root, false)){
        return "Failed to parse comments";
    } 
    
    CommentsInfo comments_info{};
    const Json::Value& data = root["data"];
    if(data.isArray()){
        for(const Json::Value& comment : data){
            comments_info << get_comment_info(comment);
        }
    }

    return comments_info;
}

CommentInfo InstagramParser::get_comment_info(const Json::Value& comment){
    CommentInfo comment_info{};

    comment_info.set_text(comment["text"].asString());
    comment_info.set_id(comment["id"].asString());
    comment_info.set_created_time(std::stol(comment["created_time"].asString()));
    
    const Json::Value& from = comment["from"];
    comment_info.set_user_info(get_user_info(from));

    return comment_info;
}

std::string InstagramParser::get_error(const std::string& json){
    Json::Value root;

    if(!reader.parse(json, root, false)){
        return "Failed to parse error";
    }

    const Json::Value& meta = root["meta"].isNull() ? root : root["meta"];

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
