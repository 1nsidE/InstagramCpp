#ifndef COMMENTS_INFO_H
#define COMMENTS_INFO_H

#include <vector>
#include "CommentInfo.h"

namespace Instagram{
#ifdef WIN32
INSTAGRAM_EXP_TMP template class EXPORT_INSTAGRAM std::vector<Instagram::CommentInfo>;
#endif

class EXPORT_INSTAGRAM CommentsInfo : public  BaseResult{
public:
    using iterator = std::vector<CommentInfo>::iterator;
    using const_iterator = std::vector<CommentInfo>::const_iterator;

    CommentsInfo();
    CommentsInfo(const CommentsInfo& comments_info);
    CommentsInfo(CommentsInfo&& comments_info);
    CommentsInfo(const char* err_msg);
    CommentsInfo(const std::string& err_msg);

    ~CommentsInfo();

    CommentsInfo& operator=(const CommentsInfo& comments_info);
    CommentsInfo& operator=(CommentsInfo&& comments_info);

    const std::vector<CommentInfo>& get_comments() const noexcept;

    CommentInfo& operator[](size_t n);
    const CommentInfo& operator[](size_t n) const;

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

    void add_comment(const CommentInfo& comment_info);
    void add_comment(CommentInfo&& comment_info);

    CommentsInfo& operator<<(const CommentInfo& comment_info);
    CommentsInfo& operator<<(CommentInfo&& comment_info);
private:
    std::vector<CommentInfo> comments;
};

}
#endif
