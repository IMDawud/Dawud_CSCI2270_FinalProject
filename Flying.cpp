/*
*CSCI2270 CS2: Data Structures
*Author: Imran Dawud
*Instructor: MonteroQuesada
*Homework: Final Project
*/


/*Project Idea:
* Creating a project where we can do a trip, giving calculations for the total cost of the trip
* and printing the locations of the places traveled.

*/

#include <iostream>
#include <string>
#include <climits>
#include "Flying.hpp"

using namespace std;

Graph::Graph()
{
	string currentC;
	head = new cityVisited("Denver ");
	tail = new cityVisited("Denver ");
	CityWeCameFrom = head;
	
}

Graph::~Graph()
{

}

void Graph::buildGraph()
{
	addVertex("Denver "); //Start
	addVertex("Denver"); //End for round trip
	addVertex("New York");
	addVertex("Chicago");
	addVertex("Miami");
	addVertex("Dallas");
	addVertex("Los Angeles");
	addVertex("Phoenix");
	addVertex("Seattle");
	addVertex("New Orleans");
	addEdge("Denver ", "New York", 1790, 177); //first number is distance in miles, second is price in $
	addEdge("Denver ", "Chicago", 1018, 138);
	addEdge("Denver ", "Miami", 2082, 188);
	addEdge("Denver ", "Dallas", 824, 89);
	addEdge("Denver ", "Los Angeles", 1028, 97);
	addEdge("Denver ", "Phoenix", 833,117);
	addEdge("Denver ", "Seattle", 1317, 137);
	addEdge("Denver ", "New Orleans", 1310, 138);
	addEdge("Phoenix", "Dallas", 450, 212);
	addEdge("Phoenix", "New York", 2455, 245)
	addEdge("Dallas", "Denver", 824, 110);
	addEdge("Dallas", "Miami" , 1321, 187);
	addEdge("New Orleans" , "Seattle" , 450, 212);
	addEdge("Seattle" , "Denver", 1317, 137);
	addEdge("New York", "Denver", 1790, 210);
	addEdge("Chicago", "Denver", 1018, 138);
	addEdge("Miami", "Denver", 2082, 139);
	addEdge("Los Angeles", "Denver", 1028, 112);



	currentC = verticies[0].cityName;
}

void Graph::addVertex(string cityName)
{
	bool found = false;
	for(int i = 0; i < verticies.size(); i++)
	{
		if(verticies[i].cityName == cityName)
		{
			found = true;
			cout << verticies[i].cityName << " found." << endl;
		}
	}
	if(found == false)
	{
		vertex v;
		v.cityName = cityName;
		verticies.push_back(v);
	}
}

void Graph::addEdge(std::string v1, std::string v2, int miles, int price)
{
	for(int i = 0; i < verticies.size(); i++)
	{
		if(verticies[i].cityName == v1)
		{
			for(int j = 0; j < verticies.size(); j++)
			{
				if(verticies[j].cityName == v2 && i != j)
				{
					adjVertex av;
					av.v = &verticies[j];
					av.miles = miles;
					av.price = price;

					verticies[i].adj.push_back(av);

				}
			}
		}
	}
}

void Graph::displayEdges()
{
	for(int i = 0; i < verticies.size(); i++)
	{
		cout << verticies[i].cityName<< "-->";
		for(int j = 0; j < verticies[i].adj.size(); j++)
		{
			cout << verticies[i].adj[j].v->cityName << "***";
		}
		cout << endl;
	}
}

int Graph::getTravelDistance()
{
	return tdist;
}

int Graph::getPrice()
{
	return tprice;
}

string Graph::getLocation()
{
	return currentC;
}

void Graph::traveltoCity(std::string prevC, std::string nextCity)
{
	for(int i = 0; i < verticies.size();i++)
	{
		if(verticies[i].cityName == prevC)
		{
			for(int j = 0; j < verticies[i].adj.size(); j++)
			{
				if(verticies[i].adj[j].v -> cityName == nextCity)
				{
					currentC = verticies[i].adj[j].v -> cityName;
					tdist = tdist + verticies[i].adj[j].miles;
					tprice = tprice + verticies[i].adj[j].price;

					cityVisited * added = new cityVisited(verticies[i].adj[j].v -> cityName);
					added -> prevC = CityWeCameFrom;
					added -> prevC -> nextCity = added;
					CityWeCameFrom = added;
					string dispPrice = to_string(tprice);
					tail = CityWeCameFrom;
	
				}
			}
		}
	}
}


void Graph::printNextDestinations(std::string currentC)
{
	//cout << "hey" << endl;
	for(int i = 0; i < verticies.size(); i++)
	{
		//cout << "Bones" << endl;
		//cout << verticies[i].cityName << endl;
		//cout << currentC << endl;
		if(verticies[i].cityName == currentC)
		{
			
			for(int j = 0; j < verticies[i].adj.size();j++)
			{
				cout << " --" << verticies[i].adj[j].v -> cityName << " (" << verticies[i].adj[j].miles << " miles)" << endl;
			}
		}
	}
}

void Graph::printTraveled()
{
	cityVisited * current = head;
	if(head -> nextCity == nullptr)
	{
		cout << "Something is wrong." << endl;
		return;
	}
	else
	{
		cout << "Your trip..." << endl;
		while(1)
		{
			cout << current -> cityName;
			if((current-> nextCity != nullptr))
			{
				cout << " -> " ;
			}
			else
			{
				cout << endl;
				break;
			}
			current = current -> nextCity;
		}
	}
	return;
}


void Graph::Dijkstra(string starting, string destination)
{
	vertex* start = nullptr;
	vertex* ending = nullptr;
	for(int i = 0; i < verticies.size(); i++)
	{
		verticies[i].visited = false;
		verticies[i].distance = INT_MAX;
		verticies[i].previous = nullptr;
		if(verticies[i].cityName == starting)
		{
			start = &verticies[i];
		}
		if(verticies[i].cityName == destination)
		{
			ending = &verticies[i];
		}
	}

	if(start != nullptr && ending != nullptr)
	{
		start -> visited = true;
		start -> distance = 0;
		vector<vertex *> solved;
		vector<vertex *> path;
		solved.push_back(start); 
		adjVertex *v;
		vertex *u;
		vertex *minVertex;
		vertex *prev1;
		while(ending -> visited == false)
		{
			//cout << "he" << endl;
			int minDist = INT_MAX;
			for(int i = 0; i < solved.size(); i++)
			{
				//cout << "helo4 " << endl;
				u = solved[i];
				for(int j = 0; j < u-> adj.size(); j++)
				{
					//cout << "helo3" << endl;
					v = &solved[i] -> adj[j];
					if(v -> v -> visited == false)
					{
						//cout << "helo2" << endl;
						int dist = u -> distance + v -> miles;
						if(dist < minDist)
						{
							minDist = dist;
							minVertex = v -> v;
							prev1 = u;
							//cout << "hello" << endl;
						}
					}
				}
			}
			solved.push_back(minVertex);
			minVertex -> distance = minDist;
			minVertex -> previous = prev1;
			minVertex -> visited = true;
		}

		cout << "Our Recommendation: " << endl;
		cout << "The shortest round trip to take from your starting location to where you are now is..." << endl;
		vertex *vert = ending;
		while(vert != nullptr)
		{
			path.push_back(vert);
			vert = vert -> previous;
		}
		for(int i = 0; i < path.size(); i++)
		{
			if(i == path.size()-1)
			{
				cout << path[path.size()-1-i] -> cityName;
			}
			else
			{
				cout << path[path.size()-1-i] -> cityName << " -> ";
			}
		}
		cout << " with a distance of " << solved[solved.size()-1] -> distance << " miles." << endl;
	}
	else if(ending != nullptr)
	{

		cout << "Starting city not located." << endl;
		exit(1);
	}
	else
	{
		cout << "Ending city not located." << endl;
		exit(1);
	}
}