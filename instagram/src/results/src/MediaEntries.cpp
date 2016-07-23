#include"MediaEntries.h"

namespace Instagram{

    MediaEntries::MediaEntries() : BaseResult{}, medias(0) {}

    MediaEntries::MediaEntries(const char* err_msg) : BaseResult{err_msg}, medias(0){}

    MediaEntries::MediaEntries(const std::string& err_msg) : BaseResult{err_msg}, medias(0){}

    MediaEntries::MediaEntries(const MediaEntries& media_entries) : BaseResult{media_entries}, medias{media_entries.medias}{}

    MediaEntries::MediaEntries(MediaEntries&& media_entries) : BaseResult{std::forward<BaseResult>(media_entries)}, medias{std::move(media_entries.medias)}{}

    MediaEntries::~MediaEntries(){}

    MediaEntries& MediaEntries::operator=(const MediaEntries& media_entries){
        if(this == &media_entries) return *this;

        BaseResult::operator=(media_entries);

        medias = media_entries.medias;
        return *this;
    }

    MediaEntries& MediaEntries::operator=(MediaEntries&& media_entries){
        if(this == &media_entries) return *this;

        BaseResult::operator=(std::forward<BaseResult>(media_entries));

        medias = std::move(media_entries.medias);
        return *this;
    }

    const std::vector<MediaEntry>& MediaEntries::get_media_entries() const{
        return medias;
    }

    MediaEntry& MediaEntries::operator[](size_t n){
        return medias[n];
    }

    const MediaEntry& MediaEntries::operator[](size_t n) const{
        return medias[n];
    }

    MediaEntries::iterator MediaEntries::begin(){
        return medias.begin();
    }

    MediaEntries::iterator MediaEntries::end(){
        return medias.end();
    }

    MediaEntries::const_iterator MediaEntries::begin() const{
        return medias.begin();
    }

    MediaEntries::const_iterator MediaEntries::end() const{
        return medias.end();
    }

    MediaEntries& MediaEntries::operator<<(const MediaEntry& media_entry){
        add_media_entry(media_entry);
        return *this;
    }

    MediaEntries& MediaEntries::operator<<(MediaEntry&& media_entry){
        add_media_entry(std::forward<MediaEntry>(media_entry));
        return *this;
    }

    void MediaEntries::add_media_entry(const MediaEntry& media_entry){
        medias.push_back(media_entry);
    }

    void MediaEntries::add_media_entry(MediaEntry&& media_entry){
        medias.push_back(std::forward<MediaEntry>(media_entry));
    }

}


