#include <rapidjson/document.h>
#include <rapidjson/error/en.h>
#include "InstagramParsers.h"

using namespace rapidjson;

namespace Instagram {

class ValueWrapper{
public:
    ValueWrapper(const Value& value) : m_ref{value} {}
    ValueWrapper(const ValueWrapper& valueWrapper) = delete;
    ValueWrapper(ValueWrapper&& valueWrapper) : m_ref{std::move(valueWrapper.m_ref)} {}

    inline ValueWrapper operator[](const char* value){
        return m_ref.HasMember(value) ? ValueWrapper{m_ref[value]} : ValueWrapper{Value{}};
    }

    inline std::string getString(const char* value) const{
        if(m_ref.HasMember(value)){
            const Value& tempValue = m_ref[value];
            if(tempValue.IsString()){
                return tempValue.GetString();
            }
        }
        return "";
    }

    inline std::string getString() const{
        return m_ref.IsString() ? m_ref.GetString() : "";
    }

    inline int getInt(const char* value) const{
        if(m_ref.HasMember(value)){
            const Value& tempValue = m_ref[value];
            if(tempValue.IsInt()){
                return tempValue.GetInt();
            }
        }

        return -1;
    }

    inline int getInt() const{
        return m_ref.IsInt() ? m_ref.GetInt() : -1;
    }

    inline double getDouble(const char* value) const{
        if(m_ref.HasMember(value)){
            const Value& tempValue = m_ref[value];
            if(tempValue.IsDouble()){
                return tempValue.GetDouble();
            }
        }
        return -1.0;
    }

    inline bool isArray() const{
        return m_ref.IsArray();
    }

    inline Value::ConstArray getArray() const{
        return m_ref.GetArray();
    }

    inline bool isNull() const{
        return m_ref.IsNull();
    }

    inline bool hasMember(const char* member){
        return m_ref.HasMember(member);
    }

private:
    const Value& m_ref;
};

MediaEntry getMediaEntry(ValueWrapper media);
UserInfo getUserInfo(ValueWrapper info);
CommentInfo getCommentInfo(ValueWrapper comment);
LocationInfo getLocation(ValueWrapper locations);

int getResponseCode(const Document& document);
std::string getErrorMessage(const Document& document);

AuthorizationToken parseAuthToken(const std::string& json) {
    AuthorizationToken token{};

    Document document{};
    if (document.Parse(json.c_str()).HasParseError()) {
        return std::string{"Failed to parse access token: "} + GetParseError_En(document.GetParseError());
    }
    
    if(!document.HasMember("access_token")){
        return "No 'data' field found in json";
    }

    token.setAuthToken(document["access_token"].GetString());
    token.setUserInfo(getUserInfo(document["user"]));
    return token;
}

MediaEntries parseMediaEntries(const std::string& json) {
    Document document{};

    if (document.Parse(json.c_str()).HasParseError()) {
        return std::string{"Failed to parse media entries: "} + GetParseError_En(document.GetParseError());
    };

    if(!document.HasMember("data")){
        return "No 'data' field found in json";
    }

    ValueWrapper data{document["data"]};
    MediaEntries result{};
    if (data.isArray()) {
        for (const auto& media : data.getArray()) {
            result << getMediaEntry(media);
        }
    }
    return result;
}

MediaEntry parseMediaEntry(const std::string& json) {
    Document document{};

    if (document.Parse(json.c_str()).HasParseError()) {
        return std::string{"Failed to parse media entry: "} + GetParseError_En(document.GetParseError());
    }

    if(!document.HasMember("data")){
        return "No 'data' field found in json";
    }

    return getMediaEntry(document["data"]);
}

MediaEntry getMediaEntry(ValueWrapper media) {
    MediaEntry entry{};

    const ValueWrapper tags{media["tags"]};
    if (tags.isArray()) {
        for (const auto& tag : tags.getArray()) {
            entry.addTag(tag.GetString());
        }
    }

    const ValueWrapper usersInPhoto{media["users_in_photo"]};
    if (usersInPhoto.isArray()) {
        for (const auto& user : usersInPhoto.getArray()) {
            entry.addUser(user.GetString());
        }
    }

    const ValueWrapper type{media["type"]};
    if (!type.isNull()) {
        const std::string type_str = type.getString();
        if (type_str == "image") {
            entry.setType(MediaType::IMAGE);
        } else if(type_str == "video") {
            entry.setType(MediaType::VIDEO);
            ValueWrapper videos{media["videos"]};
            entry.setVideoLowResolution(videos.getString("low_resolution"));
            entry.setVideoStandartResolution(videos.getString("standart_resolution"));
        }
    }

    const ValueWrapper create_time{media["created_time"]};
    long created_time = create_time.isNull() ? -1 : std::stol(create_time.getString());
    entry.setCreateTime(created_time);

    const ValueWrapper link{media["link"]};
    entry.setLink(link.getString());

    const ValueWrapper caption{media["caption"]};
    entry.setCaption(caption.getString("text"));

    {
        ValueWrapper images{media["images"]};

        ValueWrapper low_resolution{images["low_resolution"]};
        entry.setLowResolution(low_resolution.getString("url"));

        ValueWrapper thumbnail{images["thumbnail"]};
        entry.setThumbnail(thumbnail.getString("url"));

        ValueWrapper standart_resolution{images["standard_resolution"]};
        entry.setStandartResolution(standart_resolution.getString("url"));
    }

    const ValueWrapper comments{media["comments"]};
    entry.setCommentsCount(comments.getInt("count"));

    const ValueWrapper likes = media["likes"];
    entry.setLikeCount(likes.getInt("count"));

    entry.setFilter(media.getString("filter"));
    entry.setId(media.getString("id"));

    entry.setUserInfo(getUserInfo(media["user"]));

    return entry;
}

UserInfo parseUserInfo(const std::string& json) {
    Document document{};

    if (document.Parse(json.c_str()).HasParseError()){
        return std::string{"Failed to parse user info: "} + GetParseError_En(document.GetParseError());
    }

    if(!document.HasMember("data")){
        return "No 'data' field found in json";
    }

    return getUserInfo(document["data"]);
}

UsersInfo parseUsersInfo(const std::string& json) {
    Document document{};

    if (document.Parse(json.c_str()).HasParseError()){
        return std::string{"Failed to parse users info: "} + GetParseError_En(document.GetParseError());
    }

    if(!document.HasMember("data")){
        return "No 'data' field found in json";
    }

    ValueWrapper data{document["data"]};
    UsersInfo users_info{};
    if(data.isArray()){
        for (const Value& userInfo : data.getArray()) {
            users_info << getUserInfo(userInfo);
        }
    }
    return users_info;
}

UserInfo getUserInfo(ValueWrapper info) {
    UserInfo userInfo{};

    userInfo.setId(info.getString("id"));
    userInfo.setUsername(info.getString("username"));
    userInfo.setProfilePictureUrl(info.getString("profile_picture"));

    userInfo.setFullName(info.getString("full_name"));
    userInfo.setBio(info.getString("bio"));
    userInfo.setWebsite(info.getString("website"));

    if (info.hasMember("counts")) {
        ValueWrapper counts{info["counts"]};
        userInfo.setFollowedBy(counts.getInt("followed_by"));
        userInfo.setFollows(counts.getInt("follows"));
        userInfo.setMediaCount(counts.getInt("media"));
    }

    return userInfo;
}

RelationshipInfo parseRelationshipInfo(const std::string& json) {
    Document document{};

    if (document.Parse(json.c_str()).HasParseError()) {
        return std::string{"Failed to parse relationship info: "} + GetParseError_En(document.GetParseError());
    }

    if(!document.HasMember("data")){
        return "No 'data' field found in json";
    }

    ValueWrapper data{document["data"]};
    RelationshipInfo relInfo{ data.getString("incoming_status"), data.getString("outgoing_status") };

    return relInfo;
}

TagInfo parseTagInfo(const std::string& json) {
    Document document{};

    if (document.Parse(json.c_str()).HasParseError()) {
        return std::string{"Failed to parse tag info: "} + GetParseError_En(document.GetParseError());
    }

    if(!document.HasMember("data")){
        return "No 'data' field found in json";
    }

    ValueWrapper data{document["data"]};
    TagInfo tagInfo(data.getString("name"), data.getInt("media_count"));

    return tagInfo;
}

TagsInfo parseTagsInfo(const std::string& json) {
    Document document{};

    if (document.Parse(json.c_str()).HasParseError()) {
        return std::string{"Failed to parse tags info: "} + GetParseError_En(document.GetParseError());
    }

    if(!document.HasMember("data")){
        return "No 'data' field found in json";
    }

    TagsInfo tagsInfo;
    ValueWrapper data{document["data"]};
    if (data.isArray()) {
        for (const auto& tag : data.getArray()) {
            tagsInfo << TagInfo{ tag["name"].GetString(), tag["media_count"].GetInt() };
        }
    }

    return tagsInfo;
}

CommentsInfo parseComments(const std::string& json) {
    Document document{};

    if (document.Parse(json.c_str()).HasParseError()) {
        return std::string{"Failed to parse comments: "} + GetParseError_En(document.GetParseError());
    }

    if(!document.HasMember("data")){
        return "No 'data' field found in json";
    }

    CommentsInfo commentsInfo{};
    ValueWrapper data{document["data"]};
    if (data.isArray()) {
        for (const Value& comment : data.getArray()) {
            commentsInfo << getCommentInfo(comment);
        }
    }

    return commentsInfo;
}

CommentInfo getCommentInfo(ValueWrapper comment) {
    if(comment.isNull()){
        return "Invalid json document, failed to parse comment";
    }

    CommentInfo commentInfo{};

    commentInfo.setText(comment.getString("text"));
    commentInfo.setId(comment.getString("id"));
    commentInfo.setCreateTime(std::stol(comment.getString("created_time")));

    commentInfo.setUserInfo(getUserInfo(comment["from"]));

    return commentInfo;
}

LocationInfo parseLocation(const std::string& json) {
    Document document{};

    if (document.Parse(json.c_str()).HasParseError()) {
        return std::string{"Failed to parse location: "} + GetParseError_En(document.GetParseError());
    }

    if(!document.HasMember("data")){
        return "No 'data' field found in json";
    }

    return getLocation(document["data"]);
}

LocationInfo getLocation(ValueWrapper location) {
    if (!location.isNull()) {
        LocationInfo info{};
        info.setId(location.getString("id"));
        info.setName(location.getString("name"));
        info.setLatitude(location.getDouble("latitude"));
        info.setLongitude(location.getDouble("longitude"));

        return info;
    } else {
        return "Invalid json, failed to parse location";
    }
}

LocationsInfo parseLocations(const std::string& json) {
    Document document{};

    if (document.Parse(json.c_str()).HasParseError()) {
        return std::string{"Failed to parse locations: "} + GetParseError_En(document.GetParseError());
    }

    if(!document.HasMember("data")){
        return "No 'data' field found in json";
    }

    LocationsInfo infos{};
    ValueWrapper data{document["data"]};
    if (data.isArray()) {
        for (const auto& location : data.getArray()) {
            infos << getLocation(location);
        }
    }

    return infos;
}

std::string getErrorMessage(const std::string& json) {
    Document document{};

    if (document.Parse(json.c_str()).HasParseError()) {
        return std::string{"Failed to parse error: "} + GetParseError_En(document.GetParseError());
    }
    
    return getErrorMessage(document);
}

int getResponseCode(const Document& document){
    if(!document.HasMember("meta")){
        return -1;
    }

    ValueWrapper meta{document["meta"]};
    return meta.getInt("code");
}

std::string getErrorMessage(const Document& document){
    if(!document.HasMember("meta")){
        return "Invalid Instagram response - No 'meta' found";
    }

    ValueWrapper meta{document["meta"]};

    int code = meta.getInt("code");
    if (code == 200) {
        return " Call was successful";
    }
    
    std::string result{"code = " + std::to_string(code) + " "};

    ValueWrapper errMsg{meta["error_message"]};
    if(!errMsg.isNull()){
        result += "error message = " + errMsg.getString() + " ";
    }

    ValueWrapper errType{meta["error_type"]};
    if(!errType.isNull()){
        result += "error type = " + errType.getString();
    }

    return result;
}

}
