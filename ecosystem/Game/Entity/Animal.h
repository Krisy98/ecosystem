#pragma once

#include "Diet.h"
#include "Species.h"
#include "Gender.h"

#include "../../Engine/Entity/Entity.h"
#include "../../Engine/GameStructure/Grid.h"

#include <iostream>


class Animal : public Entity {

public:

	Animal(sf::Vector2i indexesPosition, sf::Vector2f size, Grid* grid, std::vector<Animal>* animals, Species species, Gender gender);

	void update(float deltaTime) override;
	void render(sf::RenderTarget& target) override;
	void handleEvent(sf::Event event) override;



	void restartBreedingClock();
	void ate();
	

	bool isNextTo(sf::Vector2i entityIndexesPos);
	bool couldHaveABaby();
	bool isHungry();
	bool isStarved();

	sf::Vector2i getIndexes();
	Grid getGrid();
	Diet getDiet();
	Species getSpecies();
	Gender getGender();

	bool& operator !=(Animal animal);

private:
	sf::Clock m_breedingClock;
	sf::Time breedingPeriod;

	sf::Clock m_hungryClock;
	sf::Time digestionTime;

	sf::Time starve;

	sf::Sprite m_skin;
	sf::Texture m_animalTexture;

	Grid* grid = {};
	Species species;
	Diet m_diet;
	Gender gender;
	sf::Vector2i indexesPos;

	std::vector<Animal>* animals = {};

};

