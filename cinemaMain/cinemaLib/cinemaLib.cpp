#include "pch.h"
#include "framework.h"
#include <iostream>
#include <string>

struct MOVIES {
	std::string name;
	int year;
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
	}
	}
}
void printMovies(MOVIES* movies)
{
	std::cout << "Movie name :  " << std::endl << movies->name << std::endl;
	printMovies(movies->nextMovie);
}

