#include <error.hpp>

ErrorChannel::ErrorChannel(ErrorManager &parent, std::string client_name) :
m_parent(parent),
m_client_name(client_name),
m_err(false)
{
}

void ErrorChannel::Notify(std::string desc)
{
    ReportToBoss(desc, SEVERITY_NOTICE);
}

void ErrorChannel::Swear(std::string desc)
{
    ReportToBoss(desc, SEVERITY_WARN);
}

void ErrorChannel::Scream(std::string desc)
{
    ReportToBoss(desc, SEVERITY_CRITICAL);
    m_err = true;
}

void ErrorChannel::ThatsItIQuit(std::string desc)
{
    ReportToBoss(desc, SEVERITY_FATAL);
    m_err=true;
    VoteQuit();
}

const bool & ErrorChannel::HasError()
{
    return m_err;
}

void ErrorChannel::ReportToBoss(std::string msg, int severity)
{
    m_parent.m_stream.push(ErrorReport{
        .source = m_client_name,
        .desc = msg,
        .severity = severity
    });
}

void ErrorChannel::VoteQuit()
{
    m_parent.m_quit_request_count++;
}
