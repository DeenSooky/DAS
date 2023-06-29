# Deen Sooky's Portfolio 

- Software project DAS

The goal is to read data from two files, "ShapeStrokeData.txt" and "DrawShapes.txt," which contain information on shapes and drawing instructions respectively. 
The software should read the data from these files, process it, and send commands in the form of G-Code to the Arduino to control the drawing arm and produce drawings on a grid. The size of the shapes should be 20mm high. 
The user should be able to input the filename for the drawing instructions. The software should be able to handle multiple sets of shapes from different instruction files in the same grid. The pen should finish in the pen-up position.

 - MovieAPP

The provided code represents a web page for a movie site. It includes HTML, CSS, and JavaScript code. The HTML structure consists of a top navigation bar with a search feature and a section for displaying movie cards. The CSS styles define the appearance of various elements on the page.

The JavaScript code uses the Fetch API to retrieve movie data from the TMDB API. The `returnMovies` function sends a request to the API and receives a response containing movie information. It then iterates over the movie results, creates HTML elements dynamically (such as divs, images, and titles), and appends them to the section on the page. Additionally, an event listener is set up on the search form to handle user input and perform a new search when submitted.

The next step in the development process is to connect the frontend code with backend technologies like Node.js and MongoDB. With Node.js, you can create a server-side application that handles API requests and communicates with the database. MongoDB can be used as the database to store and retrieve movie data. By integrating Node.js and MongoDB into the existing codebase, you can enhance the functionality of the movie site, such as allowing users to add and manage movie data, implement user authentication, and more
 
 - Lab1PrepDAS & Lab2PrepDAS
 
 Investigated waveforms associated with pulse width modulation and quadrature encoding in by connecting various signal sources and sensors to the Arduino Mega 2560 using different peripheral boards. 
 Additionally, writing code using the C language and applying it to an application with the Arduino. 
 Furthermore, interfacing of a servo motor, an incremental encoder, an H bridge, an LS7366R up/down counter, and the Arduino.
 
 - Designing a thrust reverser actuation system lock (TRASL) using Solidworks
 
  Designed a 3D model of a Thrust Reverser Actuation System Lock (TRASL) that had been carefully designed to achieve versatility and compatibility with both locking actuators and the third lock. 
 The TRASL device had been engineered to withstand even the most challenging scenarios, with the maximum torque set at a robust 120 Nm in the event of a failure. The total weight of the TRASL, without fluids, is targeted at 3 kg, with a maximum limit of 3.5 kg to maintain the unit's manoeuvrability. The reserve stress factors had been set at a minimum of 1.5, providing an extra layer of safety for the user.
 For ease of maintenance, the TRASL unit could be attached to the Locking Actuators and Third Lock using M6 x 20 Aerospace Waspalloy fasteners, with the minimum size of any other fasteners set at M5 for added stability.

- Backtesting algorithmic trading strategies

Developed three trading strategies to backtest against a daily, weekly and monthly timeframe by using the backtesting library to backtest extracted data from the alph vantage API for the nike stock from 1999 to the present day. The results were then presented as a pandas dataframe with a variety of financial metrics like final equity and the win/lose ratio, furthermore the results were also plotted as a graph to provide a more visual aid.

- Simple_bot

Developed a simulation of a cleaning robot system using the Tkinter library in Python. The system consists of multiple bots, represented as blue polygons on a canvas, moving around and collecting dirt represented as grey circles. The bots have various behaviors, including random wandering, turning, and moving towards charging stations (represented as gold circles) when their battery is low.

The main classes in the code are as follows:
Counter: Keeps track of the dirt collected by the bots and displays the count on the canvas.

Bot: Represents a cleaning bot with attributes such as position, angle, battery level, and movement parameters. It has methods to draw the bot on the canvas, move it, sense nearby charging stations, calculate distance to objects, and collect dirt.

Charger: Represents a charging station with a randomly generated position on the canvas. It has a draw method to display the charging station.

WiFiHub: Represents a Wi-Fi hub with a specified position on the canvas. It has a draw method to display the Wi-Fi hub.

Dirt: Represents dirt on the canvas with a randomly generated position. It has a draw method to display the dirt.

The code also includes functions for handling button clicks, initializing the canvas, registering the active and passive objects, and running the simulation.
To run the simulation, the function runOneExperiment is called with the desired number of bots. The bots will move around, collect dirt, and interact with charging stations based on their programmed behaviors.

- Air conditioning and refrigeration report 

The purpose of this experiment was to study air conditioning processes and analyze the indicators of moisture and heat content in the surrounding air. The researchers utilized a psychrometric chart to examine the energy and absolute humidity of the air, and a p-h diagram (absolute pressure - specific enthalpy diagram) to investigate the energy change of the refrigerant in the cooling heat exchanger.

Upon analyzing the experimental data, it was found that the theoretical data did not align closely with the observed results. This discrepancy suggests the presence of errors, either in the equipment used or in the data collection process itself. Notably, the most significant deviation between the experimental and theoretical data was observed at point C, which represents the cooling of both temperature bulbs after the initial heating. The recorded temperatures for the dry and wet bulb were 15.6°C and 13.9°C, respectively, whereas the theoretical data indicated temperatures of 20.5°C and 17.5°C for the dry and wet bulb, respectively.

- Numerical Methods 

Implemented a finite-volume computer modelling technique in MATLAB to solve the steady-state 1D heat conduction equation under certain boundary conditions

- Finite Element Analysis 

Built a finite element model of notched, circular cross-section bar subjected to a nominal axial stress to determine the stress distribution in the component

- Computer Fluid Dynamics

Generated a refined aerofoil case mesh with boundary conditions and its contour plot to determine the lift and drag forces experienced by the aerofoil.


