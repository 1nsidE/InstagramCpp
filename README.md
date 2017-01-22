[![Build Status](https://travis-ci.org/1nsidE/InstagramCpp.svg?branch=master)](https://travis-ci.org/1nsidE/InstagramCpp)

##InstagramCpp:
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
    Instagram::AuthorizationToken authToken = instClient.authenticate(code, clientId, clientSecret, redirectUri);

    if(!authToken){
        std::cerr << "Failed to retrieve authorization token, reason : " << authToken.errorMessage() << std::endl;
        return 1;
    }

    std::cout << "User with name : " << authToken.userInfo().username() << " authenticated" << std::endl;

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
RapidJSON - https://github.com/miloyip/rapidjson

OpenSSL - https://github.com/openssl/openssl

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

Experimental Windows builds is supported. To build under Windows you need to provide path to the headers and .lib's of the dependencies (RapidJSON and GnuTLS).

Tested only with Visual Studio 2015.

    cmake -G "Visual Studio 14 [Win64]" . -DRAPIDJSON_INCLUDE=${PATH_TO_RAPIDJSON_HEADERS} -DOPENSSL_LIB=${PATH_TO_OPENSSL_LIBS_FOLDER} -DOPENSSL_INCLUDE=${PATH_TO_OPENSSL_HEADERS}

This will create Visual Studio project.
