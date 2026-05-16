#pragma once
#include <string>
#include <queue>
#include <memory>

enum ErrorSeverity
{
    SEVERITY_NOTICE,
    SEVERITY_WARN,
    SEVERITY_CRITICAL,
    SEVERITY_FATAL
} ;

struct ErrorReport
{
    std::string source, desc;
    int severity;
};

class ErrorChannel;

class ErrorManager
{
public:
    friend class ErrorChannel;

    ErrorManager();
    ErrorChannel* SpawnChannel(std::string name="<anonymous>");
    void DestroyChannel(ErrorChannel* channel);

    const int& GetQuitCount();
private:
    int m_quit_request_count;
    std::vector<std::unique_ptr<ErrorChannel>> m_children;
    std::queue<ErrorReport> m_stream;
};

class ErrorChannel
{
public:
    ErrorChannel(ErrorManager& parent, std::string client_name);
    void Notify(std::string desc);
    void Swear(std::string desc);
    void Scream(std::string desc);
    void ThatsItIQuit(std::string desc);
private:
    void ReportToBoss(std::string msg, int severity);
    void VoteQuit();
    ErrorManager& m_parent;
    std::string m_client_name;
};