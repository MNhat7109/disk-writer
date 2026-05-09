#pragma once
#include <string>
#include <queue>
#include <memory>

struct ErrorReport
{
    std::string source, desc;
};

class ErrorChannel;

class ErrorManager
{
public:
    friend class ErrorChannel;

    ErrorManager();
    ErrorChannel* SpawnChannel(std::string name="<anonymous>");
    void DestroyChannel(ErrorChannel* channel);
private:
    std::queue<ErrorChannel*> m_fire_bandwagon;
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
    void ReportToBoss(std::string msg);
    void AskForRetirement();
    ErrorManager& m_parent;
    std::string m_client_name;
};