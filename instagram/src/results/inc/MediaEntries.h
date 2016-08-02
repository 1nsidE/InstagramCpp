#ifndef MEDIA_ENTRIES_H
#define MEDIA_ENTRIES_H

#include <vector>

#include "BaseResult.h"
#include "MediaEntry.h"

namespace Instagram{
    #ifdef WIN32
    INSTAGRAM_EXP_TMP template class EXPORT_INSTAGRAM std::vector<Instagram::MediaEntry>;
    #endif

    class EXPORT_INSTAGRAM MediaEntries : public BaseResult{
    public:
        using iterator = std::vector<MediaEntry>::iterator;
        using const_iterator = std::vector<MediaEntry>::const_iterator;
        
        MediaEntries();
        MediaEntries(const char* err_msg);
        MediaEntries(const std::string& err_msg);
        MediaEntries(const MediaEntries& media_entries);
        MediaEntries(MediaEntries&& media_entries);

        ~MediaEntries();

        MediaEntries& operator=(const MediaEntries& media_entries);
        MediaEntries& operator=(MediaEntries&& media_entries);

        const std::vector<MediaEntry>& get_media_entries() const;
        
        MediaEntry& operator[](size_t n);
        const MediaEntry& operator[](size_t n) const;

        iterator begin();
        iterator end();

        const_iterator begin() const;
        const_iterator end() const;

        MediaEntries& operator<<(const MediaEntry& media_entry);
        MediaEntries& operator<<(MediaEntry&& media_entry);

        void add_media_entry(const MediaEntry& media_entry);
        void add_media_entry(MediaEntry&& media_entry);

    private:
        std::vector<MediaEntry> medias;
    };

}

#endif
