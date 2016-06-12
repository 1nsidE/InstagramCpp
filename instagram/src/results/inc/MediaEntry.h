#ifndef MEDIA_ENTRY
#define MEDIA_ENTRY

#include <vector>
#include <string>

//TODO: make this class iterable

namespace Instagram{

enum class MediaType{ UNKNOWN, IMAGE, VIDEO };

class MediaEntry{
public:
    MediaEntry();
    MediaEntry(const MediaEntry& media_entry);
    MediaEntry(MediaEntry&& media_entry);
    ~MediaEntry();
    
    MediaEntry& operator=(const MediaEntry& media_entry);
    MediaEntry& operator=(MediaEntry&& media_entry);
    
    MediaType get_type() const;
    const std::string& get_url() const;
    const std::string& get_id() const;
    const std::string& get_caption() const;
    const std::string& get_standart_resolution() const;
    const std::string& get_thumbnail() const;
    const std::string& get_low_resolution() const;
    const std::string& get_filter() const;

    const std::vector<std::string>& get_tags() const;
    const std::vector<std::string>& get_users_in_photo() const;

    int get_comments_count() const;
    int get_like_count() const;
    long get_created_time() const;

    void set_type(MediaType type);
    void set_url(const std::string& url);
    void set_id(const std::string& id);
    void set_caption(const std::string& caption);
    void set_standart_resolution(const std::string& url);
    void set_thumbnail(const std::string& url);
    void set_low_resolution(const std::string& url);
    void set_filter(const std::string& _filter);

    void set_comments_count(int count);
    void set_like_count(int count);
    void set_created_time(long time);

    void add_tag(const std::string& tag);
    void add_user_in_photo(const std::string& user_id);
private:
    std::string url;
    std::string id;
    std::string caption;
    std::string low_resolution;
    std::string thumbnail;
    std::string standart_resolution;
    std::string filter;

    std::vector<std::string> tags;
    std::vector<std::string> users_in_photo;
    int comments_count = 0;
    int likes_count = 0;
    long created_time = 0;
    MediaType media_type;
};

}

#endif
