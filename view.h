// view.h
#ifndef VIEW_H
#define VIEW_H

#include <string>
#include <vector>
#include "model.h"

class EventView
{
public:
    std::string getIndexPage();
    std::string eventToJson(const Event &event);
    std::string eventsToJson(const std::vector<Event> &events);
    std::string resultToJson(bool success, const std::string &message);
};

#endif // VIEW_H