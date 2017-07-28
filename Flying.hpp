/*
*CSCI2270 CS2: Data Structures
*Author: Imran Dawud
*Instructor: MonteroQuesada
*Homework: Final Project
*/
#ifndef	FLYING_HPP
#define FLYING_HPP

#include <vector>
#include <string>

struct vertex;

struct adjVertex
{
	vertex *v;
	int miles;
	int price;
};

struct vertex
{
	bool visited;
	std::string cityName;
	std::vector<adjVertex> adj;
	int distance;
	vertex * previous;
};

struct cityVisited
{
	std::string cityName;
	cityVisited* nextCity;
	cityVisited* prevC;
	cityVisited(std::string initcityName, cityVisited *initNext = nullptr, cityVisited *initPrev = nullptr):
		cityName(initcityName), nextCity(initNext), prevC(initPrev){}


};

class Graph
{
public:
	Graph();
	~Graph();
	void addEdge(std::string v1, std::string v2, int miles, int price);
	void addVertex(std::string cityName);
	void displayEdges();
	void buildGraph();
	void Dijkstra(std::string starting, std::string destination);
	void traveltoCity(std::string currentC, std::string nextCity);
	void printNextDestinations(std::string currentC);
	void printTraveled();

	int getTravelDistance();
	int getPrice();
	std::string getLocation();

private:
	std::string currentC;
	std::vector<vertex> verticies;
	cityVisited* head;
	cityVisited* tail;
	cityVisited* CityWeCameFrom;
	int tprice;
	int tdist;
};

#include "Flying.cpp"
#endif