//
// Created by inside on 4/24/16.
//

#include "MediaEntry.h"

namespace Instagram{

    MediaEntry::MediaEntry() :  tags(0), users_in_photo(0), comments_count{-1}, likes_count{-1}, created_time{-1} {}

    MediaEntry::MediaEntry(const std::string& err) : BaseResult{err}{}

    MediaEntry::MediaEntry(const char* err) : BaseResult{err} {}

    MediaEntry::MediaEntry(const MediaEntry &media_entry) : BaseResult{media_entry},
                                                            url{media_entry.url},
                                                            id{media_entry.id},
                                                            caption{media_entry.caption},
                                                            low_resolution{media_entry.low_resolution},
                                                            thumbnail{media_entry.thumbnail},
                                                            standart_resolution{media_entry.standart_resolution},
                                                            filter{media_entry.filter},
                                                            tags{media_entry.tags},
                                                            users_in_photo{media_entry.users_in_photo},
                                                            comments_count{media_entry.comments_count},
                                                            likes_count{media_entry.likes_count},
                                                            created_time{media_entry.created_time},
                                                            media_type{media_entry.media_type}{}

    MediaEntry::MediaEntry(MediaEntry &&media_entry) :  BaseResult{std::move(media_entry)},
                                                        url{std::move(media_entry.url)},
                                                        id{std::move(media_entry.id)},
                                                        caption{std::move(media_entry.caption)},
                                                        low_resolution{std::move(media_entry.low_resolution)},
                                                        thumbnail{std::move(media_entry.thumbnail)},
                                                        standart_resolution{std::move(media_entry.standart_resolution)},
                                                        filter{std::move(media_entry.filter)},
                                                        tags(std::move(media_entry.tags)),
                                                        users_in_photo{std::move(media_entry.users_in_photo)},
                                                        comments_count(media_entry.comments_count),
                                                        likes_count(media_entry.likes_count),
                                                        created_time(media_entry.created_time),
                                                        media_type{media_entry.media_type} {
        media_entry.comments_count = -1;
        media_entry.likes_count = -1;
        media_entry.created_time = -1;
        media_entry.media_type = MediaType::UNKNOWN;
    }

    MediaEntry::~MediaEntry() {}

    MediaEntry& MediaEntry::operator=(const MediaEntry& media_entry){
        if(this == &media_entry) return *this;

        BaseResult::operator=(media_entry);

        url = media_entry.url;
        id = media_entry.id;
        caption = media_entry.caption;
        low_resolution = media_entry.low_resolution;
        thumbnail = media_entry.thumbnail;
        standart_resolution = media_entry.standart_resolution;
        filter = media_entry.filter;

        tags = media_entry.tags;
        users_in_photo = media_entry.users_in_photo;

        comments_count = media_entry.comments_count;
        likes_count = media_entry.likes_count;
        created_time = media_entry.created_time;
        media_type = media_entry.media_type;

        return *this;
    }

    MediaEntry& MediaEntry::operator=(MediaEntry&& media_entry){
        if(this == & media_entry) return *this;

        BaseResult::operator=(std::move(media_entry));

        url = std::move(media_entry.url);
        id = std::move(media_entry.id);
        caption = std::move(media_entry.caption);
        low_resolution = std::move(media_entry.low_resolution);
        thumbnail = std::move(media_entry.thumbnail);
        standart_resolution = std::move(media_entry.standart_resolution);
        filter = std::move(media_entry.filter);

        tags = std::move(media_entry.tags);
        users_in_photo = std::move(media_entry.users_in_photo);

        comments_count = media_entry.comments_count;
        media_entry.comments_count = -1;

        likes_count = media_entry.likes_count;
        media_entry.likes_count = -1;

        created_time = media_entry.created_time;
        media_entry.created_time = -1;

        media_type = media_entry.media_type;
        media_entry.media_type = MediaType::UNKNOWN;

        return *this;
    }

    MediaType MediaEntry::get_type() const{
        return media_type;
    }

    const std::string& MediaEntry::get_url() const{
        return url;
    }

    const std::string& MediaEntry::get_id() const{
        return id;
    }

    const std::string& MediaEntry::get_caption() const{
        return caption;
    }

    const std::vector<std::string>& MediaEntry::get_tags() const {
        return tags;
    }

    const std::vector<std::string>& MediaEntry::get_users_in_photo() const{
        return users_in_photo;
    }

    int MediaEntry::get_comments_count() const {
        return comments_count;
    }

    int MediaEntry::get_like_count() const {
        return likes_count;
    }

    long MediaEntry::get_created_time() const {
        return created_time;
    }

    const std::string& MediaEntry::get_standart_resolution() const{
        return standart_resolution;
    }

    const std::string& MediaEntry::get_thumbnail() const{
        return thumbnail;
    }

    const std::string& MediaEntry::get_low_resolution() const{
        return low_resolution;
    }

    const std::string& MediaEntry::get_filter() const{
        return filter;
    }

    void MediaEntry::set_type(MediaType type){
        media_type = type;
    }

    void MediaEntry::set_url(const std::string& _url){
        url = _url;
    }

    void MediaEntry::set_id(const std::string& _id){
        id = _id;
    }

    void MediaEntry::set_caption(const std::string& _caption){
        caption = _caption;
    }

    void MediaEntry::add_tag(const std::string &tag) {
        tags.push_back(tag);
    }

    void MediaEntry::set_comments_count(int count) {
        comments_count = count;
    }

    void MediaEntry::set_like_count(int count) {
        likes_count = count;
    }

    void MediaEntry::set_created_time(long time) {
        created_time = time;
    }

    void MediaEntry::set_standart_resolution(const std::string& url){
        standart_resolution = url;
    }

    void MediaEntry::set_thumbnail(const std::string& url){
        thumbnail = url;
    }

    void MediaEntry::set_low_resolution(const std::string& url){
        low_resolution = url;
    }

    void MediaEntry::set_filter(const std::string& _filter){
        filter = _filter;
    }

    void MediaEntry::add_user_in_photo(const std::string& user){
        users_in_photo.push_back(user);
    }

}
