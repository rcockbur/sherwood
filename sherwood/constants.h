#pragma once
constexpr float LINE_WIDTH_HALF = 1;
constexpr float LINE_WIDTH = (LINE_WIDTH_HALF * 2);
constexpr float OUTLINE_WIDTH = 1;
constexpr float TILE_SIZE = 20;
constexpr float PATH_DEBUG_SIZE = 8;
constexpr float WINDOW_PADDING_TOP = 5;
constexpr float WINDOW_PADDING_LEFT = 5;
constexpr float WINDOW_PADDING_BOT = 10;
constexpr float TOP_PANEL_HEIGHT = 20;
constexpr int WINDOW_SIZE[2] = { 1200,700 };
constexpr float VIEWPORT_SIZE[2] = { 900,660 };
constexpr float VIEWPORT_OFFSET[2] = { WINDOW_PADDING_LEFT, WINDOW_PADDING_TOP + TOP_PANEL_HEIGHT };
constexpr float RIGHT_PANEL_OFFSET[2] = { VIEWPORT_OFFSET[0] + VIEWPORT_SIZE[0] + 3, VIEWPORT_OFFSET[1] };

constexpr float CAMERA_SPEED = 10;

constexpr int TICS_PER_MINUTE = 30;

constexpr int NUM_RESOURCES = 4;
constexpr const char* resourceNames[NUM_RESOURCES] = { "food", "wood", "gold", "stone"};