#ifndef COMMENTS_INFO_H
#define COMMENTS_INFO_H

#include "BaseResult.h"
#include "CommentInfo.h"
#include <vector>

namespace Instagram{

class CommentsInfo : public  BaseResult{
public:
    CommentsInfo();
    CommentsInfo(const CommentsInfo& comments_info);
    CommentsInfo(CommentsInfo&& comments_info);
    CommentsInfo(const char* err_msg);
    CommentsInfo(const std::string& err_msg);

    ~CommentsInfo();

    CommentsInfo& operator=(const CommentsInfo& comments_info);
    CommentsInfo& operator=(CommentsInfo&& comments_info);

    const std::vector<CommentInfo>& get_comments() const noexcept;
    void add_comment(const CommentInfo& comment_info);
    void add_comment(CommentInfo&& comment_info);

    CommentsInfo& operator<<(const CommentInfo& comment_info);
    CommentsInfo& operator<<(CommentInfo&& comment_info);
private:
    std::vector<CommentInfo> comments;
};

}
#endif
