#include "view.h"
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

string EventView::getIndexPage()
{
    // Read the HTML file
    ifstream htmlFile("index.html");
    if (!htmlFile.is_open())
    {
        cerr << "Failed to open index.html file." << endl;
        return "Error: Could not load index.html";
    }

    stringstream buffer;
    buffer << htmlFile.rdbuf();
    return buffer.str();
}

string EventView::eventToJson(const Event &event)
{
    stringstream ss;
    ss << "{";
    ss << "\"id\":" << event.id << ",";
    ss << "\"title\":\"" << event.title << "\",";
    ss << "\"category\":\"" << event.category << "\",";
    ss << "\"date\":\"" << event.date << "\",";
    ss << "\"time\":\"" << event.time << "\",";
    ss << "\"venue\":\"" << event.venue << "\",";
    ss << "\"status\":\"" << event.status << "\",";
    ss << "\"maxAttendees\":" << event.maxAttendees;
    ss << "}";
    return ss.str();
}

string EventView::eventsToJson(const vector<Event> &events)
{
    stringstream ss;
    ss << "[";
    for (size_t i = 0; i < events.size(); i++)
    {
        ss << eventToJson(events[i]);
        if (i < events.size() - 1)
        {
            ss << ",";
        }
    }
    ss << "]";
    return ss.str();
}

string EventView::resultToJson(bool success, const string &message)
{
    stringstream ss;
    ss << "{";
    ss << "\"success\":" << (success ? "true" : "false") << ",";
    ss << "\"message\":\"" << message << "\"";
    ss << "}";
    return ss.str();
}