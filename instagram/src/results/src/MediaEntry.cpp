//
// Created by inside on 4/24/16.
//

#include "MediaEntry.h"

namespace Instagram{

MediaEntry::MediaEntry() { }

MediaEntry::MediaEntry(const MediaEntry &media_entry) : tags(media_entry.tags),
                                                  comments_count(media_entry.comments_count),
                                                  likes_count(media_entry.likes_count),
                                                  created_time(media_entry.created_time),
                                                  media_type{media_entry.media_type}{}

MediaEntry::MediaEntry(MediaEntry &&media_entry) : tags(std::move(media_entry.tags)),
                                                   comments_count(media_entry.comments_count),
                                                   likes_count(media_entry.likes_count),
                                                   created_time(media_entry.created_time),
                                                   media_type{media_entry.media_type} {
    media_entry.comments_count = 0;
    media_entry.likes_count = 0;
    media_entry.created_time = 0;
    media_entry.media_type = MediaType::UNKNOWN;
}

MediaEntry::~MediaEntry() {}

MediaEntry& MediaEntry::operator=(const MediaEntry& media_entry){
    if(this == &media_entry) return *this;
    
    tags = media_entry.tags;
    comments_count = media_entry.comments_count;
    likes_count = media_entry.likes_count;
    created_time = media_entry.created_time;
    media_type = media_entry.media_type;

    return *this;
}

MediaEntry& MediaEntry::operator=(MediaEntry&& media_entry){
    if(this == & media_entry) return *this;

    tags = std::move(media_entry.tags);
    
    comments_count = media_entry.comments_count;
    media_entry.comments_count = 0;
    
    likes_count = media_entry.likes_count;
    media_entry.likes_count = 0;
    
    created_time = media_entry.created_time;
    media_entry.created_time = 0;
        
    media_type = media_entry.media_type;
    media_entry.media_type = MediaType::UNKNOWN;

    return *this;
}

MediaType MediaEntry::get_type() const{
    return media_type;
}

std::vector<std::string> MediaEntry::get_tags() const {
    return tags;
}

unsigned int MediaEntry::get_comments_count() const {
    return comments_count;
}

unsigned int MediaEntry::get_like_count() const {
    return likes_count;
}

unsigned long MediaEntry::get_created_time() const {
    return created_time;
}

void MediaEntry::set_type(MediaType type){
    media_type = type;
}

void MediaEntry::add_tag(const std::string &tag) {
    tags.push_back(tag);
}

void MediaEntry::set_comments_count(unsigned int count) {
    comments_count = count;
}

void MediaEntry::set_like_count(unsigned int count) {
    likes_count = count;
}

void MediaEntry::set_created_time(unsigned long time) {
    created_time = time;
}

}
