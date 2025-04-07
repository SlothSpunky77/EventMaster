#include <iostream>
#include <crow.h>
#include "model.h"
#include "view.h"
#include "controller.h"

using namespace std;

int main()
{
    try
    {
        EventModel model;
        EventView view;
        EventController controller(model, view);

        crow::SimpleApp app;
        controller.setupRoutes(app);

        cout << "Starting EventMaster server on port 8080." << endl;
        app.port(8080).multithreaded().run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}