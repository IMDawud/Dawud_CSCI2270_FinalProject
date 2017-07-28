/*
*CSCI2270 CS2: Data Structures
*Author: Imran Dawud
*Instructor: MonteroQuesada
*Homework: Final Project
*/

#include <iostream>
#include <string>
#include "Flying.hpp"

using namespace std;

Graph g;

string display(string location)
{
	string inputC; //input choice

	cout << " " << endl;
	cout << "==== Travel Miles " << g.getTravelDistance() << " ==== Price $" << g.getPrice() << " ====" << endl;
	if(g.getTravelDistance() != 0)
	{
		cout << "Currently, we are in " << location << endl;
	}
	else
	{
		cout << "Let's get started." << endl;
	}
	cout << "Here are our possible destination. "  << endl;
	cout << endl;
	//cout << location << endl;
	g.printNextDestinations(location);
	cout << endl;
	g.Dijkstra(location, "Denver");
	cout << endl;
	cout << "Please make a descision on where you would like to go. " << endl; 
	cout << "Enter: ";
	getline(cin, inputC);
	cout << endl;
	cout << "Okay. Traveling to..." << inputC << endl;
	return inputC;
}

int main()
{
	g.buildGraph();
	cout << endl;
	cout << "TIME TO TAKE A VACATION!!!!! You've been stressing very hard from doing so many summer courses " << endl;
	cout << "we thought it would be nice for you to go on a vacation without thinking about Data Structures." << endl;
	cout << "We will be providing you a list of possible destinations to go to, as well as a recommendation if " << endl;
	cout << "you want a short distance trip with as few stops as possible. Travel Safe!!!" << endl;

	while(1)
	{
		string location = g.getLocation();
		string inputC = display(location);
		g.traveltoCity(location, inputC);

		location = g.getLocation();

		if(location == "Denver")
		{
			cout << endl;
			cout << "===== Miles " << g.getTravelDistance() << " ==== Price $" << g.getPrice() << " ====" << endl;
			g.printTraveled();
			cout << endl;
			cout << "Hope you had a blast!!!" << endl;
			break;
		}
		
	}
	return 0;
}