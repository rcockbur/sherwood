#pragma once
#include <SFML/Graphics.hpp>
#include "types.h"

struct Colors {
	Color blue = Color::Blue;
	Color lightBlue = Color(150, 150, 255);
	Color black = Color::Black;
	Color green = Color(0, 140, 0);
	Color red = Color::Red;
	Color pink = Color(255, 180, 180);
	Color white = Color::White;
	Color yellow = Color::Yellow;
	Color grey = Color(100, 100, 100);
	Color transparent = Color::Transparent;
	Color brown = Color(165, 42, 42);
};

extern Colors colors;