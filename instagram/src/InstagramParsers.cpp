#include <json/json.h>
#include "InstagramParsers.h"

namespace Instagram {

MediaEntry getMediaEntry(const Json::Value& media);
UserInfo getUserInfo(const Json::Value& info);
CommentInfo getCommentInfo(const Json::Value& comment);
LocationInfo getLocation(const Json::Value& locations);

AuthorizationToken parseAuthToken(const std::string& json) {
    AuthorizationToken token{};
    
    Json::Reader reader;
    Json::Value root;
    if (!reader.parse(json, root, false)) {
        return "Failed to parse response";

    }

    token.setAuthToken(root["access_token"].asString());

    const Json::Value& user = root["user"];
    token.setId(user["id"].asString());
    token.setUsername(user["username"].asString());
    token.setUserBio(user["bio"].asString());
    token.setFullName(user["full_name"].asString());
    token.setProfilePictureUrl(user["profile_picture"].asString());
    token.setWebsite(user["website"].asString());

    return token;
}

MediaEntries parseMediaEntries(const std::string& json) {
    Json::Reader reader{};
    Json::Value root{};

    if (!reader.parse(json, root, false)) {
        return "Failed to parse media entries";
    };

    const Json::Value& data = root["data"];
    MediaEntries result{};
    if (data.isArray()) {
        for (const auto& media : data) {
            result << getMediaEntry(media);
        }
    }
    return result;
}

MediaEntry parseMediaEntry(const std::string& json) {
    Json::Reader reader;
    Json::Value root;
    
    if (!reader.parse(json, root, false)) {
        return "Failed to parse media entry";
    }

    const Json::Value& data = root["data"];
    return getMediaEntry(data);
}

MediaEntry getMediaEntry(const Json::Value& media) {
    MediaEntry entry{};

    const Json::Value& tags = media["tags"];
    if (tags.isArray()) {
        for (const auto& tag : tags) {
            entry.addTag(tag.asString());
        }
    }

    const Json::Value& users_in_photo = media["users_in_photo"];
    if (users_in_photo.isArray()) {
        for (const auto& user : users_in_photo) {
            entry.addUser(user.asString());
        }
    }

    const Json::Value& type = media["type"];
    if (!type.isNull()) {
        const std::string type_str = type.asString();
        if (type_str == "image") {
            entry.setType(MediaType::IMAGE);
        } else {
            entry.setType(MediaType::VIDEO);
            const Json::Value& videos = media["videos"];
            entry.setVideoLowResolution(videos["low_resolution"].asString());
            entry.setVideoStandartResolution(videos["standart_resolution"].asString());
        }
    }

    const Json::Value& create_time = media["created_time"];
    long created_time = create_time.isNull() ? -1 : std::stol(create_time.asString());
    entry.setCreateTime(created_time);

    const Json::Value& link = media["link"];
    entry.setLink(link.asString());

    const Json::Value& caption = media["caption"];
    entry.setCaption(caption["text"].asString());

    const Json::Value& images = media["images"];

    const Json::Value& low_resolution = images["low_resolution"];
    entry.setLowResolution(low_resolution["url"].asString());

    const Json::Value& thumbnail = images["thumbnail"];
    entry.setThumbnail(thumbnail["url"].asString());

    const Json::Value& standart_resolution = images["standard_resolution"];
    entry.setStandartResolution(standart_resolution["url"].asString());

    const Json::Value& comments = media["comments"];
    int comments_count = comments.isNull() ? -1 : comments["count"].asInt();

    entry.setCommentsCount(comments_count);

    const Json::Value& filter = media["filter"];
    entry.setFilter(filter.asString());

    const Json::Value& likes = media["likes"];
    int likes_count = likes.isNull() ? -1 : likes["count"].asInt();
    entry.setLikeCount(likes_count);

    const Json::Value& id = media["id"];
    entry.setId(id.asString());

    return entry;
}

UserInfo parseUserInfo(const std::string& json) {
    Json::Reader reader{};
    Json::Value root{};

    if (!reader.parse(json, root, false)) {
        return "Failed to parse user info";
    }

    const Json::Value& data = root["data"];
    return getUserInfo(data);
}

UsersInfo parseUsersInfo(const std::string& json) {
    Json::Reader reader{};
    Json::Value root;
    if (!reader.parse(json, root, false)) {
        return "Failed to parse users info";
    }

    const Json::Value& data = root["data"];
    UsersInfo users_info{};
    for (const Json::Value& user_info : data) {
        users_info << getUserInfo(user_info);
    }

    return users_info;
}

UserInfo getUserInfo(const Json::Value &info) {
    UserInfo user_info{};

    user_info.setId(info["id"].asString());
    user_info.setUsername(info["username"].asString());
    user_info.setProfilePictureUrl(info["profile_picture"].asString());

    const Json::Value& fullname = info["full_name"];
    if (fullname.isNull()) {
        user_info.setName(info["first_name"].asString());
    }
    else {
        user_info.setName(fullname.asString());
    }

    user_info.setLastName(info["last_name"].asString());
    user_info.setBio(info["bio"].asString());
    user_info.setWebsite(info["website"].asString());

    const Json::Value& counts = info["counts"];
    if (!counts.isNull()) {
        const Json::Value &followed_by = counts["followed_by"];
        user_info.setFollowedBy(followed_by.isNull() ? -1 : followed_by.asInt());

        const Json::Value &follows = counts["follows"];
        user_info.setFollows(follows.isNull() ? -1 : follows.asInt());

        const Json::Value &media_count = counts["media"];
        user_info.setMediaCount(counts.isNull() ? -1 : media_count.asInt());
    }

    return user_info;
}

RelationshipInfo parseRelationshipInfo(const std::string& json) {
    Json::Reader reader{};
    Json::Value root{};
    if (!reader.parse(json, root, false)) {
        return "Failed to parse relationship info";
    }

    const Json::Value& data = root["data"];
    RelationshipInfo rel_info{ data["incoming_status"].asString(), data["outgoing_status"].asString() };

    return rel_info;
}

TagInfo parseTagInfo(const std::string& json) {
    Json::Reader reader{};
    Json::Value root{};

    if (!reader.parse(json, root, false)) {
        return "Failed to parse tag info";
    }

    const Json::Value& data = root["data"];
    TagInfo tag_info(data["name"].asString(), data["media_count"].asInt());

    return tag_info;
}

TagsInfo parseTagsInfo(const std::string& json) {
    Json::Reader reader{};
    Json::Value root{};

    if (!reader.parse(json, root, false)) {
        return "Failed to parse tags info";
    }

    TagsInfo tags_info;
    const Json::Value& data = root["data"];
    if (data.isArray()) {
        for (const auto& tag : data) {
            tags_info << TagInfo{ tag["name"].asString(), tag["media_count"].asInt() };
        }
    }

    return tags_info;
}

CommentsInfo parseComments(const std::string& json) {
    Json::Reader reader{};
    Json::Value root{};
    if (!reader.parse(json, root, false)) {
        return "Failed to parse comments";
    }

    CommentsInfo comments_info{};
    const Json::Value& data = root["data"];
    if (data.isArray()) {
        for (const Json::Value& comment : data) {
            comments_info << getCommentInfo(comment);
        }
    }

    return comments_info;
}

CommentInfo getCommentInfo(const Json::Value& comment) {
    CommentInfo comment_info{};

    comment_info.setText(comment["text"].asString());
    comment_info.setId(comment["id"].asString());
    comment_info.setCreateTime(std::stol(comment["created_time"].asString()));

    const Json::Value& from = comment["from"];
    comment_info.setUserInfo(getUserInfo(from));

    return comment_info;
}

LocationInfo parseLocation(const std::string& json) {
    Json::Reader reader{};
    Json::Value root{};
    if (!reader.parse(json, root, false)) {
        return "Failed to parse location";
    }

    return getLocation(root["data"]);
}

LocationInfo getLocation(const Json::Value& location) {
    if (!location.isNull()) {
        LocationInfo info{};
        info.setId(location["id"].asString());
        info.setName(location["name"].asString());
        info.setLatitude(location["latitude"].asDouble());
        info.setLongitude(location["longitude"].asDouble());

        return info;
    } else {
        return "Invalid json, failed to parse location";
    }
}

LocationsInfo parseLocations(const std::string& json) {
    Json::Reader reader{};
    Json::Value root{};
    if (!reader.parse(json, root, false)) {
        return "Failed to parse locations";
    }

    const Json::Value& data = root["data"];
    if (data.isArray()) {
        LocationsInfo infos{};
        for (const auto& location : data) {
            infos << getLocation(location);
        }

        return infos;
    } else {
        return "Invalid json, failed to parse locations";
    }
}

std::string getError(const std::string& json) {
    Json::Reader reader{};
    Json::Value root{};

    if (!reader.parse(json, root, false)) {
        return "Failed to parse error";
    }

    const Json::Value& meta = root["meta"].isNull() ? root : root["meta"];

    int code = meta["code"].asInt();
    if (code == 200) {
        return "";
    }

    const Json::Value& err_msg = meta["error_message"];
    const Json::Value& err_type = meta["error_type"];

    if (!err_type.isNull() || !err_msg.isNull()) {
        return err_type.asString() + " : " + err_msg.asString();
    } else {
        return "Unknown error with code = " + std::to_string(code);
    }
}

}
