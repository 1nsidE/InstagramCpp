#include "InstagramClient.h"
#include "InstagramConstants.h"
#include "InstagramEndpoints.h"
#include "FormData.h"

namespace Instagram {

InstagramClient::InstagramClient() : parser {}, http_client { INSTAGRAM_HOST, Http::HttpProtocol::HTTPS }, auth_token { "" } {}
const std::string& InstagramClient::get_auth_token() const {
    return auth_token;
}

void InstagramClient::set_auth_token(const std::string &_auth_token) {
    auth_token = _auth_token;
}

void InstagramClient::check_auth() {
    if (auth_token.empty()) {
        throw std::runtime_error("not authorized");
    }
}

std::string InstagramClient::get_result(const Http::HttpResponse& response) {
    switch (response.get_code()) {
    case Http::Status::BAD_REQUEST:
        return parser.get_error(response.get_data());
    default:
        return response.get_status();
    }
}

AuthorizationToken InstagramClient::exchange_code(const std::string& code,
        const std::string& client_Id,
        const std::string& client_secret,
        const std::string& redirect_uri) {

    Http::FormData form_data { "#################" };
    form_data["code"] = code;
    form_data["client_id"] = client_Id;
    form_data["client_secret"] = client_secret;
    form_data["redirect_uri"] = redirect_uri;
    form_data["grant_type"] = AUTH_CODE_GRANT_TYPE;

    try {
        const Http::HttpResponse response = http_client.post({ GET_AUTH_CODE }, form_data);
        if (response.get_code() == Http::Status::OK) {
            return parser.parse_auth_token(response.get_data());
        } else {
            return get_result(response);
        }
    } catch (const std::exception& err) {
        return err.what();
    }
}

UserInfo InstagramClient::get_user_info() {
    return get_user_info(SELF);
}

UserInfo InstagramClient::get_user_info(const std::string& user_id) {
    try {
        check_auth();
        Http::HttpUrl url { Users::users + user_id };
        url[AUTH_TOKEN_ARG] = auth_token;

        const Http::HttpResponse response = http_client << url;
        if (response.get_code() == Http::Status::OK) {
            return parser.parse_user_info(response.get_data());
        } else {
            return get_result(response);
        }
    } catch (const std::exception& err) {
        return err.what();
    }
}

MediaEntries InstagramClient::get_recent_media(unsigned count) {
    return get_recent_media(SELF, count);
}

MediaEntries InstagramClient::get_recent_media(const std::string& user_id, unsigned count) {
    try {
        check_auth();
        Http::HttpUrl url { Users::users, user_id, Users::recent_media };
        url[AUTH_TOKEN_ARG] = auth_token;
        url[COUNT_ARG] = std::to_string(count);

        return get_media(url);
    } catch (const std::exception& err) {
        return err.what();
    }
} 

MediaEntries InstagramClient::get_recent_media(const std::string& min_id, const std::string& max_id, unsigned count) {
    return get_recent_media(SELF, min_id, max_id, count);
}

MediaEntries InstagramClient::get_recent_media(const std::string& user_id, const std::string& min_id, const std::string& max_id, unsigned count) {
    try {
        check_auth();

        Http::HttpUrl url { Users::users,user_id, Users::recent_media };
        url[AUTH_TOKEN_ARG] = auth_token;
        if (!min_id.empty()) url[MIN_ID_ARG] = min_id;
        if (!max_id.empty()) url[MAX_ID_ARG] = max_id;
        url[COUNT_ARG] = std::to_string(count);

        return get_media(url);
    } catch (const std::exception& err) {
        return err.what();
    }
}

MediaEntries InstagramClient::get_liked_media() {
    try {
        check_auth();

        Http::HttpUrl url { Users::users, Users::self_liked };
        url[AUTH_TOKEN_ARG] = auth_token;

        return get_media(url);
    } catch (const std::exception& err) {
        return err.what();
    }
}

MediaEntries InstagramClient::get_liked_media(const std::string& max_id) {
    try {
        check_auth();

        Http::HttpUrl url { Users::users, Users::self_liked };
        url[AUTH_TOKEN_ARG] = auth_token;
        url[MAX_LIKE_ID] = max_id;

        return get_media(url);
    } catch (const std::exception& err) {
        return err.what();
    }
}

MediaEntries InstagramClient::get_media(const Http::HttpUrl& url) {
    const Http::HttpResponse response = http_client << url;

    if (response.get_code() == Http::Status::OK) {
        return parser.parse_media_entries(response.get_data());
    } else {
        return get_result(response);
    }
}

UsersInfo InstagramClient::search_users(const std::string& query, unsigned count) {
    try {
        check_auth();

        Http::HttpUrl url { Users::users, Users::search };
        url[AUTH_TOKEN_ARG] = auth_token;
        url[QUERY_ARG] = query;
        url[COUNT_ARG] = std::to_string(count);

        return get_users_info(url);
    } catch (const std::exception& err) {
        return err.what();
    }
}

UsersInfo InstagramClient::get_follows() {
    try {
        check_auth();
        Http::HttpUrl url { Relationships::users, Relationships::follows };
        url[AUTH_TOKEN_ARG] = auth_token;
        return get_users_info(url);
    } catch (const std::exception& err) {
        return err.what();
    }
}

UsersInfo InstagramClient::get_followed_by() {
    try {
        check_auth();
        Http::HttpUrl url { Relationships::users, Relationships::followed_by };
        url[AUTH_TOKEN_ARG] = auth_token;
        return get_users_info(url);
    } catch (const std::exception& err) {
        return err.what();
    }
}

UsersInfo InstagramClient::get_requested_by() {
    try {
        check_auth();
        Http::HttpUrl url { Relationships::users, Relationships::requested_by };
        url[AUTH_TOKEN_ARG] = auth_token;
        return get_users_info(url);
    } catch (const std::exception& err) {
        return err.what();
    }
}

UsersInfo InstagramClient::get_users_info(const Http::HttpUrl& url) {
    try {
        check_auth();
        const Http::HttpResponse response = http_client << url;

        if (response.get_code() == Http::Status::OK) {
            return parser.parse_users_info(response.get_data());
        } else {
            return get_result(response);
        }
    } catch (const std::exception& err) {
        return err.what();
    }
}

RelationshipInfo InstagramClient::get_relationship_info(const std::string& user_id) {
    try {
        check_auth();
        Http::HttpUrl url { Relationships::users, user_id, Relationships::relationship };
        url[AUTH_TOKEN_ARG] = auth_token;

        const Http::HttpResponse response = http_client << url;

        if (response.get_code() == Http::Status::OK) {
            return parser.parse_relationship_info(response.get_data());
        } else {
            return get_result(response);
        }
    } catch (const std::exception& err) {
        return err.what();
    }
}

MediaEntry InstagramClient::get_media(const std::string& media_id) {
    try {
        check_auth();

        Http::HttpUrl url { Media::get_media, media_id };
        url[AUTH_TOKEN_ARG] = auth_token;

        const Http::HttpResponse response = http_client << url;
        if (response.get_code() == Http::Status::OK) {
            return parser.parse_media_entry(response.get_data());
        } else {
            return get_result(response);
        }
    } catch (const std::exception& err) {
        return err.what();
    }
}

MediaEntry InstagramClient::get_media_short(const std::string& shortcode) {
    try {
        check_auth();

        Http::HttpUrl url { Media::get_media_shortcode, shortcode };
        url[AUTH_TOKEN_ARG] = auth_token;

        const Http::HttpResponse response = http_client << url;
        if (response.get_code() == Http::Status::OK) {
            return parser.parse_media_entry(response.get_data());
        } else {
            return get_result(response);
        }
    } catch (const std::exception& err) {
        return err.what();
    }
}

MediaEntries InstagramClient::search_media(double lat, double lng, int distance) {
    try {
        check_auth();

        Http::HttpUrl url { Media::media_search };
        url[LAT_ARG] = std::to_string(lat);
        url[LNG_ARG] = std::to_string(lng);
        url[DST_ARG] = std::to_string(distance);
        url[AUTH_TOKEN_ARG] = auth_token;

        return get_media(url);
    } catch (std::exception& err) {
        return err.what();
    }
}

CommentsInfo InstagramClient::get_comments(const std::string& media_id) {
    try {
        check_auth();

        Http::HttpUrl url { Comments::media, media_id, Comments::comments };
        url[AUTH_TOKEN_ARG] = auth_token;

        const Http::HttpResponse response = http_client << url;
        if (response.get_code() == Http::Status::OK) {
            return parser.parse_comments(response.get_data());
        } else {
            return get_result(response);
        }
    } catch (const std::exception& err) {
        return err.what();
    }
}

BaseResult InstagramClient::comment(const std::string& media_id, const std::string& text) {
    try {
        check_auth();

        Http::HttpUrl url { Comments::media, media_id, Comments::comments };
        Http::FormData form_data {};
        form_data[AUTH_TOKEN_ARG] = auth_token;
        form_data[Comments::TEXT_ARG] = text;

        const Http::HttpResponse response = http_client.post(url, form_data);
        if (response.get_code() == Http::Status::OK) {
            return {};
        } else {
            return get_result(response);
        }
    } catch (const std::exception& err) {
        return err.what();
    }
}

BaseResult InstagramClient::delete_comment(const std::string& media_id, const std::string& comment_id) {
    try {
        check_auth();

        Http::HttpUrl url { Comments::media, media_id, Comments::comments, comment_id };
        url[AUTH_TOKEN_ARG] = auth_token;
        const Http::HttpResponse response = http_client.del(url);
        if (response.get_code() == Http::Status::OK) {
            return {};
        } else {
            return get_result(response);
        }
    } catch (const std::exception& err) {
        return err.what();
    }
}

UsersInfo InstagramClient::get_likes(const std::string& media_id) {
    try {
        check_auth();

        Http::HttpUrl url { Likes::media, media_id, Likes::likes };
        url[AUTH_TOKEN_ARG] = auth_token;

        return get_users_info(url);
    } catch (const std::exception& err) {
        return err.what();
    }
}

BaseResult InstagramClient::like(const std::string& media_id) {
    try {
        check_auth();

        Http::HttpUrl url { Likes::media, media_id, Likes::likes };
        Http::FormData form_data {};
        form_data[AUTH_TOKEN_ARG] = auth_token;

        const Http::HttpResponse response = http_client.post(url, form_data);
        if (response.get_code() == Http::Status::OK) {
            return {};
        } else {
            return get_result(response);
        }
    } catch (const std::exception& err) {
        return err.what();
    }
}

BaseResult InstagramClient::unlike(const std::string& media_id) {
    try {
        check_auth();

        Http::HttpUrl url { Likes::media, media_id, Likes::likes };
        url[AUTH_TOKEN_ARG] = auth_token;

        const Http::HttpResponse response = http_client.del(url);
        if (response.get_code() == Http::Status::OK) {
            return {};
        } else {
            return get_result(response);
        }
    } catch (const std::exception& err) {
        return err.what();
    }
}

TagInfo InstagramClient::get_tag_info(const std::string& tag_name) {
    try {
        check_auth();
        Http::HttpUrl url { Tags::tags, tag_name };
        url[AUTH_TOKEN_ARG] = auth_token;

        const Http::HttpResponse response = http_client << url;
        if (response.get_code() == Http::Status::OK) {
            return parser.parse_tag_info(response.get_data());
        } else {
            return get_result(response);
        }
    } catch (const std::exception& err) {
        return err.what();
    }
}

TagsInfo InstagramClient::search_tags(const std::string& query) {
    try {
        check_auth();
        Http::HttpUrl url { Tags::tags, Tags::tags_search };
        url[QUERY_ARG] = query;
        url[AUTH_TOKEN_ARG] = auth_token;

        const Http::HttpResponse response = http_client << url;
        if (response.get_code() == Http::Status::OK) {
            return parser.parse_tags_info(response.get_data());
        } else {
            return get_result(response);
        }
    } catch (const std::exception& err) {
        return err.what();
    }

}

MediaEntries InstagramClient::get_recent_media_tag(const std::string& tag_name) {
    try {
        check_auth();

        Http::HttpUrl url { Tags::tags, tag_name, Tags::recent_media };
        url[AUTH_TOKEN_ARG] = auth_token;

        const Http::HttpResponse response = http_client << url;
        if (response.get_code() == Http::Status::OK) {
            return parser.parse_media_entries(response.get_data());
        } else {
            return get_result(response);
        }
    } catch (const std::exception& err) {
        return err.what();
    }
}

LocationInfo InstagramClient::get_location(const std::string& location_id) {
    try {
        check_auth();

        Http::HttpUrl url { Locations::locations, location_id };
        url[AUTH_TOKEN_ARG] = auth_token;

        const Http::HttpResponse response = http_client << url;
        if (response.get_code() == Http::Status::OK) {
            return parser.parse_location(response.get_data());
        } else {
            return get_result(response);
        }
    } catch (const std::exception& err) {
        return err.what();
    }
}

MediaEntries InstagramClient::get_media_loc(const std::string& location_id) {
    try {
        check_auth();

        Http::HttpUrl url { Locations::locations, location_id, Locations::recent_media };
        Http::HttpResponse response = http_client << url;

        if (response.get_code() == Http::Status::OK) {
            return parser.parse_media_entries(response.get_data());
        } else {
            return get_result(response);
        }
    } catch (std::exception& err) {
        return err.what();
    }
}

LocationsInfo InstagramClient::search_locations(double lat, double lng, int distance) {
    try {
        check_auth();

        Http::HttpUrl url { Locations::locations, Locations::search };
        url[LAT_ARG] = std::to_string(lat);
        url[LNG_ARG] = std::to_string(lng);
        url[DST_ARG] = std::to_string(distance);
        url[AUTH_TOKEN_ARG] = auth_token;

        Http::HttpResponse response = http_client << url;
        if (response.get_code() == Http::Status::OK) {
            return parser.parse_locations(response.get_data());
        } else {
            return get_result(response);
        }
    } catch (std::exception& err) {
        return err.what();
    }
}

}
