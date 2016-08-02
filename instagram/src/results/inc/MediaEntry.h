#ifndef MEDIA_ENTRY
#define MEDIA_ENTRY

#include <vector>
#include <string>
#include "BaseResult.h"
//TODO: make this class iterable

namespace Instagram{
    enum class MediaType{ UNKNOWN, IMAGE, VIDEO };

    class EXPORT_INSTAGRAM MediaEntry : public BaseResult{
    public:
        MediaEntry();
        MediaEntry(const std::string& err);
        MediaEntry(const char* err);
        MediaEntry(const MediaEntry& media_entry);
        MediaEntry(MediaEntry&& media_entry);
        ~MediaEntry();

        MediaEntry& operator=(const MediaEntry& media_entry);
        MediaEntry& operator=(MediaEntry&& media_entry);

        MediaType get_type() const noexcept;
        const std::string& get_link() const noexcept;
        const std::string& get_id() const noexcept;
        const std::string& get_caption() const noexcept;
        const std::string& get_standart_resolution() const noexcept;
        const std::string& get_thumbnail() const noexcept;
        const std::string& get_low_resolution() const noexcept;
        const std::string& get_filter() const noexcept;

        const std::string& get_video_low() const noexcept;
        const std::string& get_video_standart() const noexcept;

        const std::vector<std::string>& get_tags() const noexcept;
        const std::vector<std::string>& get_users_in_photo() const noexcept;

        int get_comments_count() const noexcept;
        int get_like_count() const noexcept;
        long get_created_time() const noexcept;

        void set_type(MediaType type);
        void set_link(const std::string& link_);
        void set_id(const std::string& id);
        void set_caption(const std::string& caption);
        void set_standart_resolution(const std::string& url);
        void set_thumbnail(const std::string& url);
        void set_low_resolution(const std::string& url);
        void set_filter(const std::string& _filter);
        
        void set_video_low(const std::string& url);
        void set_video_standart(const std::string& url);

        void set_comments_count(int count);
        void set_like_count(int count);
        void set_created_time(long time);

        void add_tag(const std::string& tag);
        void add_user_in_photo(const std::string& user_id);
    private:
        std::string link;
        std::string id;
        std::string caption;
        std::string low_resolution;
        std::string thumbnail;
        std::string standart_resolution;
        std::string filter;

        std::string video_low{};
        std::string video_standart{};

        std::vector<std::string> tags;
        std::vector<std::string> users_in_photo;
        int comments_count = -1;
        int likes_count = -1;
        long created_time = -1;
        MediaType media_type = MediaType::UNKNOWN;
    };

}

#endif
