#pragma once
#include <SFML/Graphics.hpp>
#include "globals.h"

struct Colors {
	Color blue = Color::Blue;
	Color black = Color::Black;
	Color green = Color::Green;
	Color red = Color::Red;
	Color white = Color::White;
	Color yellow = Color::Yellow;
	Color grey = Color(100, 100, 100);
	Color transparent = Color::Transparent;
	Color brown = Color(165, 42, 42);
};

extern Colors colors;