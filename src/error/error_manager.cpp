#include <error.hpp>
#include <algorithm>

#define MAX_CHILDREN 64

ErrorManager::ErrorManager() : m_children({})
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
