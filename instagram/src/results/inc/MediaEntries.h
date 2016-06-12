#ifndef MEDIA_ENTRIES_H
#define MEDIA_ENTRIES_H

#include <vector>

#include "BaseResult.h"
#include "MediaEntry.h"

namespace Instagram{

class MediaEntries : public BaseResult{
public:
    MediaEntries();
    MediaEntries(const char* err_msg);
    MediaEntries(const std::string& err_msg);
    MediaEntries(const MediaEntries& media_entries);
    MediaEntries(MediaEntries&& media_entries);

    ~MediaEntries();

    MediaEntries& operator=(const MediaEntries& media_entries);
    MediaEntries& operator=(MediaEntries&& media_entries);
    
    const std::vector<MediaEntry>& get_media_entries() const;
    
    MediaEntries& operator<<(const MediaEntry& media_entry);
    MediaEntries& operator<<(MediaEntry&& media_entry);

    void add_media_entry(const MediaEntry& media_entry);
    void add_media_entry(MediaEntry&& media_entry);

private:
    std::vector<MediaEntry> medias;
};

}

#endif
