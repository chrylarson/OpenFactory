OpenFactory
===========

Open Source Factory Production Monitoring

This is a collection of open source software and hardware that together creates a factory production monitoring system. The design is based on Arduino, Drupal, node.js, and Ubuntu. 

	Arduino - This is the hardware that collects the data directly from the production machine.
	http://arduino.cc/

	Drupal - This is the CMS that distributes and displays the production data.
	http://drupal.org/

	node.js - This is the method used to send the data from the Arduino to the server.
	http://nodejs.org/

	Ubuntu -  This is the server that powers the system.
	http://www.ubuntu.com/

============
Overview:

	Step 1: Setup Ubuntu with a LAMP stack

	Step 2: Install node.js, npm and the mysql library for node.js

	Step 3: Install Drupal

	Step 4: Program the Arduino and Ethernet shield

============
To Do:

	Drupal:
		Create a module for accessing external databases with Views
		Create a module for displaying and creating new Arduino data sets
		Create a theme for OpenFactory
	
	Arduino:
		Write a program to auto-connect to the internet
		Write a program to collect data from the local IO pins
		Write a program to send the data to a node.js server
		Write a program to sync the arduino time with the server time
		Write a program to store data on the local flash card
		Write a program to send data on the local flash card upon re-connecting to the node.js server
		
	node.js
		Write a program to listen for Arduino connections
		Write a program to store the received Arduino messages to a database
		Write a program that respoinsed with server time to the Arduino
		
	Ubuntu
		Create a distribution with all the pieces installed and set to working default values