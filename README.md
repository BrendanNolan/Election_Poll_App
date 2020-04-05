This application, called "Poll Zapp" will allow the user to browse through political data (esp. current MPs and candidates 
in upcoming election) and make their own edits if they wish to construct an imaginary but more 
appealing political world.

There will be simple games where you can play as a politician and have them compete against their 
constituency rivals to gain public popularity.

The front- and back-end heavy lifting is written in C++ with the Qt framework. Python scripts are 
run at start-up to load the latest data. These scripts can be edited by the user while the application 
is running, if desired. This Python scripts can also be re-run asynchronously to load the latest data 
into the app. At present these scripts simulate web scraping but do not actually do any web scraping - 
they use random picture and data choices to simulate a changing political landscape. 

Projects:
    poll_zapp_gui (application):
        Contains the GUI components, in particular widgets which offer views of the underlying data.
        Qt dependencies: core, gui, widgets, sql
    poll_zapp_core (static library): 
        Contains the low-level models and database managing classes which provide data to the 
        GUI components. 
        Qt dependencies: core, sql
    utils_qt_dep (static library):
        Contains low-level utilities for Qt classes.
        Qt dependencies: core
    utils_geometric (static library): 
        Contains low-level, simple geometry classes.
        Qt dependencies: none
