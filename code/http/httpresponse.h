/*
 * @Description  : HTTP应答类
 * @Date         : 2022-07-16 01:14:05
 * @LastEditTime : 2022-07-18 00:01:18
 */
#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <fcntl.h>
#include <sys/mman.h> /*mmap,munmap*/
#include <sys/stat.h>
#include <unistd.h>

#include <unordered_map>

#include "../buffer/buffer.h"
#include "../logsys/log.h"

class HttpResponse {
private:
    int  code_;         // 返回码
    bool isKeepAlive_;  // 是否保持长连接

    std::string path_;    // 文件路径
    std::string srcDir_;  // 项目根目录

    char       *mmFile_;      // 发送文件
    struct stat mmFileStat_;  // 发送文件的信息

    static const std::unordered_map<std::string, std::string> SUFFIX_TYPE;  // 返回类型键值对

    static const std::unordered_map<int, std::string> CODE_STATUS;  // 状态码键值对
    static const std::unordered_map<int, std::string> CODE_PATH;  // 错误码与页面对应关系

public:
    HttpResponse();
    ~HttpResponse();

    void init(const std::string &srcDir, const std::string &path, bool isKeepAlive = false,
              int code = -1);

    void makeResponse(Buffer &buff);

    void unmapFile();

    int    code() const;
    char  *file() const;
    size_t fileLen() const;

private:
    void addStateLine_(Buffer &buff);
    void addHeader_(Buffer &buff);
    void addContent_(Buffer &buff);

    void errorHtml_();
    void errorContent(Buffer &buff, std::string message);

    std::string getFileType_();
};

#endif  //HTTPRESPONSE_H
