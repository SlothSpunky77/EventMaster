#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD "password"
#define DATABASE "EventMaster"

struct Event
{
    int id = 0;
    std::string title;
    std::string category;
    std::string date;
    std::string time;
    std::string venue;
    std::string status;
    int maxAttendees = 0;
};

class EventModel
{
private:
    MYSQL *conn;

public:
    EventModel();
    ~EventModel();

    bool createEvent(const std::string &title, const std::string &category, const std::string &date,
                     const std::string &time, const std::string &venue, const std::string &status, int maxAttendees);
    std::vector<Event> fetchEvents();
    Event fetchEvent(int id);
    bool updateEvent(int id, const std::string &field, const std::string &newValue);
    bool deleteEvent(int id);
};

#endif