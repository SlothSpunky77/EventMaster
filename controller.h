#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"
#include "view.h"
#include <crow.h>
#include <map>
#include <string>

class EventController
{
private:
    EventModel &model;
    EventView &view;
    std::map<std::string, std::string> parseJson(const std::string &jsonStr);

public:
    EventController(EventModel &model, EventView &view);
    void setupRoutes(crow::SimpleApp &app);
};

#endif
