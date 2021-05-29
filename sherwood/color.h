#pragma once
#include <SFML/Graphics.hpp>
#include "types.h"

struct Colors {
	Color red = Color(252, 12, 12);
	Color pink = Color(255, 12, 132);
	Color green = Color(12, 252, 32);
	Color darkGreen = Color(0, 150, 0);
	Color lightGreen = Color(150, 255, 150);
	Color blue = Color(0, 17, 255);
	Color lightBlue = Color(50, 129, 255);
	Color black = Color::Black;
	Color purple = Color(204, 0, 255);
	Color teal = Color(0, 212, 255);
	Color orange = Color(255, 159, 0);
	
	Color white = Color::White;
	Color yellow = Color(255, 255, 12);
	Color grey = Color(120, 120, 120);
	Color transparent = Color::Transparent;
	Color brown = Color(150, 82, 8);
};

extern Colors color;