#include <iostream>
#include <vector>
#include <string>
#include <mysql/mysql.h>
#include "model.h"

using namespace std;

EventModel::EventModel()
{
    conn = mysql_init(nullptr);
    if (!conn)
    {
        cerr << "MySQL initialization failed." << endl;
        exit(1);
    }

    conn = mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 3306, NULL, 0);
    if (!conn)
    {
        cerr << "Database connection failed: " << mysql_error(conn) << endl;
        exit(1);
    }
    else
    {
        cout << "Connected to database." << endl;
    }
}

EventModel::~EventModel()
{
    if (conn)
        mysql_close(conn);
}

bool EventModel::createEvent(const string &title, const string &category, const string &date,
                             const string &time, const string &venue, const string &status, int maxAttendees)
{
    cout << "date: " << date << endl;
    cout << "title" << title << endl;
    cout << "attendees" << maxAttendees << endl;
    string query = "INSERT INTO events (title, category, date, time, venue, status, maxAttendees) VALUES ('" +
                   title + "','" + category + "','" + date + "','" + time + "','" + venue + "','" + status + "'," +
                   to_string(maxAttendees) + ")";
    if (mysql_query(conn, query.c_str()) == 0)
    {
        return true;
    }
    else
    {
        cerr << "Error adding event: " << mysql_error(conn) << endl;
        return false;
    }
}

vector<Event> EventModel::fetchEvents()
{
    vector<Event> events;
    string query = "SELECT * FROM events";

    if (mysql_query(conn, query.c_str()) == 0)
    {
        MYSQL_RES *res = mysql_store_result(conn);
        if (!res)
        {
            cerr << "Error storing result: " << mysql_error(conn) << endl;
            return events;
        }

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res)))
        {
            Event event;
            event.id = row[0] ? atoi(row[0]) : 0;
            event.title = row[1] ? row[1] : "";
            event.category = row[2] ? row[2] : "";
            event.date = row[3] ? row[3] : "";
            event.time = row[4] ? row[4] : "";
            event.venue = row[5] ? row[5] : "";
            event.status = row[6] ? row[6] : "";
            event.maxAttendees = row[7] ? atoi(row[7]) : 0;
            events.push_back(event);
        }
        mysql_free_result(res);
    }
    else
    {
        cerr << "Error fetching events: " << mysql_error(conn) << endl;
    }

    return events;
}

Event EventModel::fetchEvent(int id)
{
    Event event;
    string query = "SELECT * FROM events WHERE id = " + to_string(id);

    if (mysql_query(conn, query.c_str()) == 0)
    {
        MYSQL_RES *res = mysql_store_result(conn);
        if (!res)
        {
            cerr << "Error storing result: " << mysql_error(conn) << endl;
            return event;
        }

        MYSQL_ROW row = mysql_fetch_row(res);
        if (row)
        {
            event.id = row[0] ? atoi(row[0]) : 0;
            event.title = row[1] ? row[1] : "";
            event.category = row[2] ? row[2] : "";
            event.date = row[3] ? row[3] : "";
            event.time = row[4] ? row[4] : "";
            event.venue = row[5] ? row[5] : "";
            event.status = row[6] ? row[6] : "";
            event.maxAttendees = row[7] ? atoi(row[7]) : 0;
        }
        mysql_free_result(res);
    }
    else
    {
        cerr << "Error fetching event: " << mysql_error(conn) << endl;
    }

    return event;
}

bool EventModel::updateEvent(int id, const string &field, const string &newValue)
{
    string query = "UPDATE events SET " + field + "='" + newValue + "' WHERE id=" + to_string(id);
    if (mysql_query(conn, query.c_str()) == 0)
    {
        return true;
    }
    else
    {
        cerr << "Error updating event: " << mysql_error(conn) << endl;
        return false;
    }
}

bool EventModel::deleteEvent(int id)
{
    string query = "DELETE FROM events WHERE id=" + to_string(id);
    if (mysql_query(conn, query.c_str()) == 0)
    {
        return true;
    }
    else
    {
        cerr << "Error deleting event: " << mysql_error(conn) << endl;
        return false;
    }
}