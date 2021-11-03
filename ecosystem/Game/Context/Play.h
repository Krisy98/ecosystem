#pragma once
#include <vector>
#include <list>

#include "../../Engine/GameStructure/Context.h"
#include "../../Engine/GameStructure/Grid.h"

#include "../Entity/Animal.h"
#include "../Entity/Plant.h"
#include "../Entity/Diet.h"
#include "../Entity/Gender.h"

class Play : public Context {

public :
	Play(sf::Vector2f windowSize);
	~Play();

	void update(float deltaTime) override;
	void render(sf::RenderTarget& target) override;
	void renderDebugMenu(sf::RenderTarget& target) override;
	void handleEvent(sf::Event event) override;

	const char* getContext() override;
	
private:
	sf::Clock m_clock;
	sf::Time m_turnTime;

	Grid* m_grid;
	std::vector<Animal>* m_animals {};
	std::vector<Plant>* m_plants = {};

	sf::Sprite m_background;
	sf::Texture m_grass;

	int m_animalsLimit;

	bool isAnimalHere(sf::Vector2i indexes);
	bool isPlantHere(sf::Vector2i indexes);

	void updateAnimals(float deltaTime);
	void updateBabies(float deltaTime);
	void updateDeads(float deltaTime);

	void updatePlants(float deltaTime);

	void createAnimal(sf::Vector2i indexes, Species species);
	void createAnimal(sf::Vector2i indexes, Species species, Gender gender);
	void createPlant(sf::Vector2i indexes);

};