#pragma once
constexpr float LINE_WIDTH_HALF = 1;
constexpr float LINE_WIDTH = (LINE_WIDTH_HALF * 2);
constexpr float OUTLINE_WIDTH = 1;
constexpr float TILE_SIZE = 10;
constexpr float PATH_DEBUG_SIZE = 5;

constexpr float ENTITY_SIZE_SMALL = 6;
constexpr float ENTITY_SIZE_MEDIUM = 8;
constexpr float ENTITY_SIZE_LARGE = 10;

constexpr float CAMERA_SPEED = 10;

constexpr int TICS_PER_SECOND = 30;

constexpr int NUM_RESOURCES = 4;
constexpr const char* resourceNames[NUM_RESOURCES] = { "food", "wood", "gold", "stone"};