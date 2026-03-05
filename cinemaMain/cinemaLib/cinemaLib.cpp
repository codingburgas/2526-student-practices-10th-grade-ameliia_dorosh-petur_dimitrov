#include "pch.h"
#include "framework.h"
#include <iostream>
#include <fstream>
#include <string>

struct MOVIES {
	std::string name;
	int year;
	int length;
	MOVIES* nextMovie;
};

void getChoice()
{
	int choice;
	MOVIES* movieList = new MOVIES;
	std::cin >> choice;
	switch (choice)
	{
	case 1:
	{
		system("cls");
		printMovies(movieList);
		break;
	}
	case 2:
	{

		break;
	}
	case 3:
	{

		break;
	}
	case 4:
	{
		addMoviesPage();
		break;
	}
	}
}

void printMovies(MOVIES* movies)
{
	std::cout << "   " << movies->name << " - " << movies->year << " length: " << movies->length << std::endl;
	if (movies->nextMovie == NULL)
	{
		return;
	}
	printMovies(movies->nextMovie);
}

void addMovies(MOVIES* movies, int year, int length, std::string name)
{
	MOVIES* newMov;
	newMov->name = name;
	newMov->length = length;
	newMov->year = year;
	movies->nextMovie = newMov;
}
void addMoviesPage()
{
	std::cout << std::ifstream("text.txt").rdbuf();
	std::string name;
	int year, length;
}