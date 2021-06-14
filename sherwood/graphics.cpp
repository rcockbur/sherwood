#include <assert.h>
#include <sstream>
#include <iomanip>
#include <vector>
#include "graphics.h"
#include "map.h"
#include "color.h"
#include "entity.h"
#include "entity_type.h"
#include "globals.h"
#include "entity_manager.h"
#include "utility.h"

Graphics::Graphics() 
{
	viewportShape.setSize(VIEWPORT_SIZE);
	viewportShape.setPosition(VIEWPORT_OFFSET);
	viewportShape.setOutlineColor(color.red);
	viewportShape.setOutlineThickness(1);
	viewportShape.setFillColor(color.transparent);

	verticalLine.setSize(Vec2f(LINE_WIDTH, GRID_SIZE.y + LINE_WIDTH));
	verticalLine.setFillColor(color.grey);

	horizontalLine.setSize(Vec2f(GRID_SIZE.x + LINE_WIDTH, LINE_WIDTH));
	horizontalLine.setFillColor(color.grey);

	sf::RectangleShape grassRect;
	sf::RectangleShape waterRect;

	grassRect.setSize(Vec2f(TILE_SIZE, TILE_SIZE));
	grassRect.setFillColor(color.darkGreen);
	terrainShapes.push_back(grassRect);

	waterRect.setSize(Vec2f(TILE_SIZE, TILE_SIZE));
	waterRect.setFillColor(color.blue);
	terrainShapes.push_back(waterRect);

	entityShape.setSize(Vec2f(ENTITY_SIZE, ENTITY_SIZE));
	entityShape.setFillColor(color.white);

	selectionShape.setSize(Vec2f(ENTITY_SIZE, ENTITY_SIZE));
	selectionShape.setOutlineThickness(LINE_WIDTH);
	selectionShape.setOutlineColor(color.yellow);
	selectionShape.setFillColor(color.transparent);

	pathDebugShape.setSize(Vec2f(PATH_DEBUG_SIZE, PATH_DEBUG_SIZE));

	if (!arial.loadFromFile("resources/sansation.ttf"))
		throw std::logic_error("font cannot be found");
	initText(fpsText, Vec2f(WINDOW_PADDING_LEFT, WINDOW_PADDING_TOP));
	initText(selectionText, RIGHT_PANEL_OFFSET);
}

void Graphics::initText(sf::Text& text, const Vec2f& position) {
	text.setFont(arial);
	text.setCharacterSize(14);
	text.setFillColor(sf::Color::White);
	text.setPosition(position);
}

void Graphics::draw() {
	renderWindow.clear();
	drawWorld();
	drawHUD();
	renderWindow.display();
}

void Graphics::drawWorld() {
	renderWindow.setView(mapView);
	drawTerrain();
	if (showGrid)
		drawGrid();
	drawEntities();
}

void Graphics::drawHUD() {
	renderWindow.setView(renderWindow.getDefaultView());
	drawViewportOutline();
	drawText();
}

void Graphics::drawTerrain() {
	for (int x = 0; x < map.terrainGrid.size(); ++x) {
		for (int y = 0; y < map.terrainGrid[x].size(); ++y) {
			terrainShapes.at(map.terrainGrid[x][y]).
				setPosition(Vec2f(TILE_SIZE * float(x), TILE_SIZE * (float)y));
			renderWindow.draw(terrainShapes.at(map.terrainGrid[x][y]));
		}
	}
}

void Graphics::drawEntities() {
	for (auto& entity : em.entities) {
		Vec2f graphicalPosition = entity->position - Vec2f(ENTITY_SIZE / 2, ENTITY_SIZE / 2);
		entityShape.setPosition(graphicalPosition);
		entityShape.setFillColor(entity->color);
		renderWindow.draw(entityShape);
		if (entity->isSelected) {
			selectionShape.setPosition(graphicalPosition);
			renderWindow.draw(selectionShape);
		}
	}	
}

void Graphics::drawGrid() {
	for (int i = 0; i < map.tileCount.x + 1; i++) {
		verticalLine.setPosition(Vec2f(TILE_SIZE * i - LINE_WIDTH_HALF, -LINE_WIDTH_HALF));
		renderWindow.draw(verticalLine);
	}
	for (int i = 0; i < map.tileCount.y + 1; i++) {
		horizontalLine.setPosition(Vec2f(-LINE_WIDTH_HALF, TILE_SIZE * i - LINE_WIDTH_HALF));
		renderWindow.draw(horizontalLine);
	}
}

void Graphics::drawText() {
	drawTextFPS();
	drawTextSelection();
}

void Graphics::drawTextFPS() {
	std::ostringstream s;
	s << "Target FPS: " << targetFPS;
	s << "   Actual FPS: " << (int)actualFPS;
	fpsText.setString(s.str());
	renderWindow.draw(fpsText);
}

void Graphics::drawTextSelection() {
	if (selectedEntity != nullptr) {
		std::ostringstream s = selectedEntity->getSelectionText();
		//s << "Type: " << selectedEntity->type.name << "\n";
		//s << "ID: " << selectedEntity->id << "\n";
		//s << "Tile: " << worldToTile(selectedEntity->position) << "\n";
		//s << "Pos: " << (Vec2i)(selectedEntity->position) << "\n";
		//Unit* selectedUnit = dynamic_cast<Unit*>(selectedEntity);
		//if (selectedUnit) {
		//	if (selectedUnit->home) {
		//		s << "Home: " << selectedUnit->home->id << "\n";
		//	}
		//	else {
		//		s << "Home: -\n";
		//	}
		//}
		selectionText.setString(s.str());
		renderWindow.draw(selectionText);
	}
}

void Graphics::drawViewportOutline() {
	renderWindow.draw(viewportShape);
}

void Graphics::drawPathDebug(const std::list<node>& open, const std::list<node>& closed, 
	const Vec2i& s, const Vec2i& e, std::list<Vec2i> * path) {
	renderWindow.clear();
	drawWorld();
	
	pathDebugShape.setFillColor(color.red);
	for (std::list<node>::const_iterator i = open.begin(); i != open.end(); i++) {
		if ((*i).tile != s) {
			pathDebugShape.setPosition(tileToWorld((*i).tile) - Vec2f(PATH_DEBUG_SIZE / 2, PATH_DEBUG_SIZE / 2));
			renderWindow.draw(pathDebugShape);
		}
		
	}
	pathDebugShape.setFillColor(color.purple);
	for (std::list<node>::const_iterator i = closed.begin(); i != closed.end(); i++) {
		if ((*i).tile != s) {
			pathDebugShape.setPosition(tileToWorld((*i).tile) - Vec2f(PATH_DEBUG_SIZE / 2, PATH_DEBUG_SIZE / 2));
			renderWindow.draw(pathDebugShape);
		}	
	}
	if (path != nullptr) {
		pathDebugShape.setFillColor(color.teal);
		for (std::list<Vec2i>::iterator i = (*path).begin(); i != (*path).end(); i++) {
			pathDebugShape.setPosition(tileToWorld((*i)) - Vec2f(PATH_DEBUG_SIZE / 2, PATH_DEBUG_SIZE / 2));
			renderWindow.draw(pathDebugShape);
		}
	}
	

	pathDebugShape.setFillColor(color.white);
	pathDebugShape.setPosition(tileToWorld(s) - Vec2f(PATH_DEBUG_SIZE / 2, PATH_DEBUG_SIZE / 2));
	renderWindow.draw(pathDebugShape);

	pathDebugShape.setFillColor(color.yellow);
	pathDebugShape.setPosition(tileToWorld(e) - Vec2f(PATH_DEBUG_SIZE / 2, PATH_DEBUG_SIZE / 2));
	renderWindow.draw(pathDebugShape);

	drawHUD();
	renderWindow.display();
}

