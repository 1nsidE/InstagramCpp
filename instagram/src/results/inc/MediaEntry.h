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
    std::vector<std::string> get_tags() const;
    unsigned int get_comments_count() const;
    unsigned int get_like_count() const;
    unsigned long get_created_time() const;

    void set_type(MediaType type);
    void add_tag(const std::string& tag);
    void set_comments_count(unsigned int count);
    void set_like_count(unsigned int count);
    void set_created_time(unsigned long time);
private:
    std::vector<std::string> tags;
    unsigned int comments_count = 0;
    unsigned int likes_count = 0;
    unsigned long created_time = 0;
    MediaType media_type;
};

}

#endif
