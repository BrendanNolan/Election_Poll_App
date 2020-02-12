This application will allow the user to browse through political data (esp. current MPs and candidates 
in upcoming election) and make their own edits if they wish to construct an imaginary but more 
appealing political world.

There will be simple games where you can play as a politician and have them compete against their 
constituency rivals to gain public popularity.

The front- and back-end heavy lifting is written in C++ with the Qt framework. A Python script is 
run at start-up to load the latest data. This script can be edited by the user while the application 
is running, if desired. This Python script can also be re-run asynchronously to load the latest data 
into the app. 

At the moment, the script just loads some random and simple data but eventually I hope to have it 
do some web scraping to get the required data. 
