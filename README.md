InstagramCpp:
----------------
Implementation of the Instagram REST API client in C++.

Project is under active development.

Supported API's:
----------------
All official endpoints are supported.

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

    Instagram::InstagramClient instClient{};
    Instagram::AuthorizationToken authToken = instClient.exchangeCode(code, clientId, clientSecret, redirectUri);

    if(!authToken){
        std::cerr << "Failed to retrieve authorization token, reason : " << authToken.errorMessage() << std::endl;
        return 1;
    }
    
    std::cout << "User with name : " << authToken.username() << " authenticated" << std::endl;

    instClient.setAuthToken(authToken.authToken());
    
    Instagram::MediaEntries mediaEntries = instClient.getRecentMedia();
    if(!mediaEntries){
        std::cerr << "Failed to retrieve recent media, reason : " << mediaEntries.errorMessage() << std::endl;
        return 1;
    }

    for(const auto& media : mediaEntries){
        std::cout << media.caption() << "\n";
        std::cout << "likes count : "  << media.likesCount() << "\n";
        std::cout << "comments count " << media.commentsCount() << "\n"<< std::endl; 
    }

    return 0;
}
```

Dependencies:
----------------
JsonCpp - https://github.com/open-source-parsers/jsoncpp

GnuTLS - https://www.gnutls.org

Build Instructions:
----------------

Linux:
----------------

Tested only on Linux with 4.5 kernel.

    cmake .
    make

You will find shared library with headers file divided into 2 folders in "lib" folder.

Windows:
----------------

Experimental Windows builds is supported. To build under Windows you need to provide path to the headers and .lib's of the dependencies (GnuTLS and JsonCpp).

Tested only with Visual Studio 2015.

    cmake -G "Visual Studio 14 [Win64]" . -DJSON_LIB_DIR=<PATH_TO_JSONCPP_LIB_FILE> -DJSON_INCLUDE_DIR=<PATH_TO_JSONCPP_HEADERS> -GNUTLS_LIB=<PATH_TO_GNUTLS_LIB_FILE> -DGNUTLS_INCLUDE=<PATH_TO_GNUTLS_HEADERS>

This will create Visual Studio project.


