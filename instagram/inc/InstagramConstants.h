#ifndef INSTAGRAM_CONSTANTS
#define INSTAGRAM_CONSTANTS

namespace Instagram{

static const char* INSTAGRAM_HOST = "api.instagram.com";
static const char* AUTH_CODE_GRANT_TYPE = "authorization_code";
static const char* AUTH_TOKEN_ARG = "access_token";
static const char* SELF = "self";
static const char* QUERY_ARG = "q";
static const char* LAT_ARG = "lat";
static const char* LNG_ARG = "lng";
static const char* DST_ARG = "distance";
static const char* COUNT_ARG = "count";
static const char* MIN_ID_ARG = "MIN_ID";
static const char* MAX_ID_ARG = "MAX_ID";
static const char* MAX_LIKE_ID = "max_like_id";

static const char* RELATIONSHIP_ACTION_ARG = "action";
static const char* RELATIONSHIP_FOLLOW = "follow";
static const char* RELATIONSHIP_UNFOLLOW = "unfollow";
static const char* RELATIONSHIP_APPROVE = "approve";
static const char* RELATIONSHIP_IGNORE = "ignore";

enum class Relationship {follow, unfollow, approve, ignore};

static const char* NOT_AUTHENTICATED = "Not authenticated";
static const char* FORM_DATA_BOUNDARY = "################";

}

#endif
