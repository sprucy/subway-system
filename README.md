# subway-system
## System Description
Shanghai's metro transport network has taken shape, with more than ten completed metro lines and hundreds of stations. It is now necessary to set up a transfer guide printing system, which prints out a metro transfer guide by inputting the starting point and the terminal station, and the guide includes the starting point, the transfer station and the terminal station.

1. Graphically display the metro network structure and dynamically add metro lines and stations.
2. Displays the metro transfer guide according to the input of starting point and terminal station.
3. Display the travelling path through the graphical interface.

## Main Functions:
A graphical interface showing the Shanghai metro network map. The metro network map can be zoomed in and out through the mouse wheel, and it also has two main functions: adding stations and transfer query.
### Add station:
After entering the main menu, select the "add station" option.
It is mainly divided into three parts: adding lines, adding individual stations and connecting stations.
Add a new line: you can select a new line to add the metro in the drop-down box, enter the name of the new line and select the colour to add the new line to the map.
#### Add New Station: 
You can add a new station to an existing line, or add a new station to a new line you just added. Enter the x and y coordinates of the site and then fill the site into the map.
#### Connect Sites: 
Select a line, then select two sites as endpoints to connect two originally unconnected sites. Click the Exit button to exit.
### Transfer query
Once in the main menu, select the "Interchange Enquiry" option.
Depending on the requirements, there are two different interchange strategies available: Minimum Interchange Time and Minimum Interchange Count. In the left drop-down box, select the origin and destination stations, select the transfer strategy, click on Transfer, and in the right dialogue box, the transfer strategy will be listed, as well as whether or not each station is on an intermediate station of another route.
