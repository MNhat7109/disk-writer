#include <error.hpp>
#include <algorithm>
#include <iostream>

#define MAX_CHILDREN 64

static const char* const s_severity_string[] = {
    "INFO",
    "WARN",
    "CRITICAL",
    "FATAL"
};

ErrorManager::ErrorManager() : 
m_quit_request_count(0)
{
    m_children.reserve(MAX_CHILDREN);
}

ErrorChannel *ErrorManager::SpawnChannel(std::string name)
{
    auto new_channel = std::make_unique<ErrorChannel>(*this, name);

    ErrorChannel* raw_ptr = new_channel.get();
    m_children.push_back(std::move(new_channel));
    return raw_ptr;
}

void ErrorManager::DestroyChannel(ErrorChannel *channel)
{
    if (!channel) return;

    auto it = std::find_if(
        m_children.begin(), 
        m_children.end(), 
        [channel](const std::unique_ptr<ErrorChannel>& ptr) -> bool
        {
            return channel == ptr.get();
        }
    );
    if (it == m_children.end()) return;

    std::swap(*it, m_children.back());
    m_children.pop_back();
}

const int &ErrorManager::GetQuitCount()
{
    return m_quit_request_count;
}

void ErrorManager::UnwindErrorStream()
{
    while (!m_stream.empty())
    {
        auto current_report = m_stream.front();
        m_stream.pop();
        PrintError(current_report);
    }
}

void ErrorManager::PrintError(const ErrorReport& report)
{
    std::cerr << "[" << s_severity_string[report.severity] << "] " 
    << "<" << report.source << "> :"
    << report.desc << "\n";
}
