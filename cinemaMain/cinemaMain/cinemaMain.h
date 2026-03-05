#pragma once

struct MOVIES {
	std::string name;
	int year;
	MOVIES* nextMovie;
};
void getChoice();