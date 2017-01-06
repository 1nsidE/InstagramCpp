#ifndef MEDIA_ENTRY
#define MEDIA_ENTRY

#include <vector>
#include <string>
#include "UserInfo.h"
//TODO: make this class iterable

namespace Instagram{
#ifdef WIN32
INSTAGRAM_EXP_TMP template class EXPORT_INSTAGRAM std::vector<std::string>;
#endif

enum class MediaType{ UNKNOWN, IMAGE, VIDEO };

class EXPORT_INSTAGRAM MediaEntry : public BaseResult{
public:
    MediaEntry();
    MediaEntry(const std::string& errMsg);
    MediaEntry(const char* errMsg);
    MediaEntry(const MediaEntry& mediaEntry);
    MediaEntry(MediaEntry&& mediaEntry);
    ~MediaEntry();

    MediaEntry& operator=(const MediaEntry& mediaEntry);
    MediaEntry& operator=(MediaEntry&& mediaEntry);

    MediaType type() const noexcept;
    const std::string& link() const noexcept;
    const std::string& id() const noexcept;
    const std::string& caption() const noexcept;
    const std::string& standartResolution() const noexcept;
    const std::string& thumbnail() const noexcept;
    const std::string& lowResolution() const noexcept;
    const std::string& filter() const noexcept;

    const std::string& videoLowResolution() const noexcept;
    const std::string& videoStandartResolution() const noexcept;

    const std::vector<std::string>& tags() const noexcept;
    const std::vector<std::string>& usersInPhoto() const noexcept;

    const UserInfo& userInfo() const noexcept;

    int commentsCount() const noexcept;
    int likesCount() const noexcept;
    long createTime() const noexcept;

    void setType(MediaType type);
    void setLink(const std::string& link);
    void setId(const std::string& id);
    void setCaption(const std::string& caption);
    void setStandartResolution(const std::string& url);
    void setThumbnail(const std::string& url);
    void setLowResolution(const std::string& url);
    void setFilter(const std::string& filter);

    void setVideoLowResolution(const std::string& url);
    void setVideoStandartResolution(const std::string& url);

    void setCommentsCount(int count);
    void setLikeCount(int count);
    void setCreateTime(long time);

    void addTag(const std::string& tag);
    void addUser(const std::string& userId);

    void setUserInfo(const UserInfo& userInfo);
    void setUserInfo(UserInfo&& userInfo);
private:
    std::string m_link{};
    std::string m_id{};
    std::string m_caption{};
    std::string m_lowResolution{};
    std::string m_thumbnail{};
    std::string m_standartResolution{};
    std::string m_filter{};

    std::string m_videoLow{};
    std::string m_videoStandart{};

    std::vector<std::string> m_tags;
    std::vector<std::string> m_users;

    UserInfo m_userInfo{};

    int m_commentsCount = -1;
    int m_likesCount = -1;
    long m_createTime = -1;
    MediaType m_mediaType = MediaType::UNKNOWN;
    
    friend void swap(MediaEntry& media1, MediaEntry& media2);
};

}
#endif
