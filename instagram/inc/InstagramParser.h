#include <string>
#include <json/json.h>
#include "MediaEntries.h"
#include "AuthorizationToken.h"

namespace Instagram{

class InstagramParser{
public:
    InstagramParser();
    InstagramParser(const InstagramParser& instagram_parser) = delete;
    InstagramParser(InstagramParser&& instagram_parser) = delete;

    AuthorizationToken parse_auth_token(const std::string& json);
    MediaEntries parse_media_entries(const std::string& json);
    
private:
    Json::Reader reader;
};

}
