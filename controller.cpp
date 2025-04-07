#include "controller.h"
#include <crow.h>
#include <iostream>
#include <string>
#include <map>

using namespace std;

EventController::EventController(EventModel &model, EventView &view)
    : model(model), view(view) {}

void EventController::setupRoutes(crow::SimpleApp &app)
{
    CROW_ROUTE(app, "/")([]()
                         {
        EventView view;
        return view.getIndexPage(); });

    CROW_ROUTE(app, "/api/events")([this]()
                                   {
        auto events = model.fetchEvents();
        return view.eventsToJson(events); });

    CROW_ROUTE(app, "/api/events/<int>")([this](int id)
                                         {
        auto event = model.fetchEvent(id);
        return view.eventToJson(event); });

    CROW_ROUTE(app, "/api/events").methods(crow::HTTPMethod::POST)([this](const crow::request &req)
                                                                   {
        auto data = parseJson(req.body);
        bool success = model.createEvent(data["title"], data["category"], data["date"],
                                         data["time"], data["venue"], data["status"],
                                         stoi(data["maxAttendees"]));
        return view.resultToJson(success, success ? "Event created successfully" : "Failed to create event"); });

    CROW_ROUTE(app, "/api/events/<int>").methods(crow::HTTPMethod::PUT)([this](const crow::request &req, int id)
                                                                        {
        auto data = parseJson(req.body);
        bool success = true;
        for (auto &[key, value] : data)
        {
            success &= model.updateEvent(id, key, value);
        }
        return view.resultToJson(success, success ? "Event updated successfully" : "Failed to update event"); });

    CROW_ROUTE(app, "/api/events/<int>").methods(crow::HTTPMethod::DELETE)([this](int id)
                                                                           {
        bool success = model.deleteEvent(id);
        return view.resultToJson(success, success ? "Event deleted successfully" : "Failed to delete event"); });
}

// JSON parser
map<string, string> EventController::parseJson(const string &jsonStr)
{
    map<string, string> data;
    size_t start = 0, end = 0;

    cout << "Parsing JSON: " << jsonStr << endl;

    while (true)
    {
        start = jsonStr.find("\"", end);
        if (start == string::npos)
            break;

        end = jsonStr.find("\"", start + 1);
        if (end == string::npos)
            break;

        string key = jsonStr.substr(start + 1, end - start - 1);

        start = jsonStr.find(":", end);
        if (start == string::npos)
            break;
        start++;

        while (start < jsonStr.length() && (jsonStr[start] == ' ' || jsonStr[start] == '\t' || jsonStr[start] == '\n'))
            start++;

        if (start < jsonStr.length())
        {
            if (jsonStr[start] == '"')
            {
                start++;
                end = jsonStr.find("\"", start);
                if (end == string::npos)
                    break;
                string value = jsonStr.substr(start, end - start);
                data[key] = value;
                end++;
            }
            else
            {
                end = jsonStr.find_first_of(",}", start);
                if (end == string::npos)
                    break;
                string value = jsonStr.substr(start, end - start);
                value.erase(0, value.find_first_not_of(" \t\n"));
                value.erase(value.find_last_not_of(" \t\n") + 1);
                data[key] = value;
            }
        }
    }

    for (const auto &[key, value] : data)
    {
        cout << key << ": " << value << endl;
    }

    return data;
}
