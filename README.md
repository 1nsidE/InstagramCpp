InstagramCpp:
----------------
Implementation of the Instagram REST API client in C++.

Very early version, only few API's supported.


Usage Example:
----------------
``` cpp
...
#include<InstagramClient.h>
...

int main(){
    /***
    retrieving OAuth response code
    ***/

    Instagram::InstagramClient inst_client{};
    Instagram::AuthorizationToken auth_token = inst_client.exchange_code(code, client_id, client_secret, redirect_uri);
   
    if(!auth_token.is_succeed()){
        std::cerr << "Failed to retrieve authorization token, reason : " << auth_token.get_error_message() << std::endl;
        return 1;
    }
    
    std::cout << "User with name : " << auth_token.get_user_name() << " authenticated" << std::endl;

    inst_client.set_auth_token(auth_token.get_auth_token());
    
    Instagram::MediaEntries media_entries = inst_client.get_user_recent_media();
    if(!media_entries.is_succeed()){
    	std::cerr << "Failed to retrieve recent media, reason : " << media_entries.get_error_message() << std::endl;
    	return 1;
    }
   
    for(const auto& media : media_entries.get_media_entries()){
        std::cout << media.get_caption() << "\n";
        std::cout << "likes count : "  << media.get_like_count() << "\n";
        std::cout << "comments count " << media.get_comments_count() << "\n"<< std::endl; 
    }

    return 0;
}
```

Dependencies:
----------------
JsonCpp - https://github.com/open-source-parsers/jsoncpp

OpenSSL - https://github.com/openssl/openssl

Build:
----------------
Tested only on Linux with 4.5 kernel.

	cmake .
	make

You will find shared library in "lib" folder.
