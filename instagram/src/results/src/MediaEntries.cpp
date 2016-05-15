#include"MediaEntries.h"

namespace Instagram{

MediaEntries::MediaEntries(){}

MediaEntries::MediaEntries(const char* err_msg) : BaseResult(err_msg){

}

MediaEntries::MediaEntries(const std::string& err_msg) : BaseResult(err_msg){

}

MediaEntries::MediaEntries(const MediaEntries& media_entries) : medias{media_entries.medias}{}

MediaEntries::MediaEntries(MediaEntries&& media_entries) : medias{std::move(media_entries.medias)}{}

MediaEntries::~MediaEntries(){}

MediaEntries& MediaEntries::operator=(const MediaEntries& media_entries){
    if(this == &media_entries) return *this;
    
    medias = media_entries.medias;
    return *this;
}

MediaEntries& MediaEntries::operator=(MediaEntries&& media_entries){
    if(this == &media_entries) return *this;

    medias = std::move(media_entries.medias);
    return *this;
}

const std::vector<MediaEntry>& MediaEntries::get_media_entries() const{
    return medias;
}

void MediaEntries::add_media_entry(const MediaEntry& media_entry){
    medias.push_back(media_entry);
}

}


