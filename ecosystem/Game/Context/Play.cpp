#include "stdafx.h"
#include "Play.h"

#include <iostream>

Play::Play(sf::Vector2f windowSize) :
	m_turnTime
	{ 
		sf::seconds(0.6f) 
	}
{
	srand(time(NULL));

	m_clock.restart();
	m_grid = new Grid(sf::Vector2f(0, 0), windowSize, 10, 11);
	m_animals = new std::vector<Animal>();
	m_plants = new std::vector<Plant>();

	m_animalsLimit = 20;

	// ------------------------

	if (!m_grass.loadFromFile(".\\Assets\\sprite_sheet/background/grass.jpg"))
	{
		std::cout << "error loading file texture ..." << std::endl;
	}
	
	m_grass.setRepeated(true);

	m_background.setTexture(m_grass);
	m_background.setTextureRect(sf::IntRect(0, 0, windowSize.x, windowSize.y));
	m_background.setPosition(0, 0);

	// ------------------------
	
	createAnimal(sf::Vector2i(0, 0), Species::Lion, Gender::Male);
	createAnimal(sf::Vector2i(3, 2), Species::Lion, Gender::Female);

	createAnimal(sf::Vector2i(1, 8), Species::Cow, Gender::Male);
	createAnimal(sf::Vector2i(5, 8), Species::Cow, Gender::Male);
	createAnimal(sf::Vector2i(8, 4), Species::Cow, Gender::Female);
	createAnimal(sf::Vector2i(7, 5), Species::Cow, Gender::Female);

	createPlant(sf::Vector2i(0, 0));
	createPlant(sf::Vector2i(6, 6));
	createPlant(sf::Vector2i(8, 6));
	createPlant(sf::Vector2i(1, 9));
	createPlant(sf::Vector2i(9, 3));
	createPlant(sf::Vector2i(3, 3));

}

Play::~Play() {
	delete m_grid;

	delete m_animals;
}

void Play::update(float deltaTime) {
	
	if (m_clock.getElapsedTime().asSeconds() < m_turnTime.asSeconds()) return;

	m_clock.restart();

	updateAnimals(deltaTime);
	updatePlants(deltaTime);
}

void Play::render(sf::RenderTarget& target) {

	target.draw(m_background);

	m_grid->render(target);

	for (std::vector<Plant>::iterator i_it = m_plants->begin(); i_it != m_plants->end(); i_it++)
	{
		(*i_it).render(target);
	}

	for (std::vector<Animal>::iterator i_it = m_animals->begin(); i_it != m_animals->end(); i_it++)
	{
		(*i_it).render(target);
	}
	
}

void Play::renderDebugMenu(sf::RenderTarget& target) {

}

void Play::handleEvent(sf::Event event) {

}

const char* Play::getContext() {
	return "dd";
}

bool Play::isAnimalHere(sf::Vector2i indexes) {

	if (indexes.x < 0 || indexes.x >= m_grid->getSize().x || indexes.y < 0 || indexes.y >= m_grid->getSize().y) return true;

	for (std::vector<Animal>::iterator i_it = m_animals->begin(); i_it != m_animals->end(); i_it++)
	{
		if ((*i_it).getIndexes() == indexes) return true;
	}
	return false;
}

bool Play::isPlantHere(sf::Vector2i indexes) {
	if (indexes.x < 0 || indexes.x >= m_grid->getSize().x || indexes.y < 0 || indexes.y >= m_grid->getSize().y) return true;

	for (std::vector<Plant>::iterator i_it = m_plants->begin(); i_it != m_plants->end(); i_it++)
	{
		if ((*i_it).getIndexes() == indexes) return true;
	}
	return false;
}

void Play::updateAnimals(float deltaTime) {

	for (std::vector<Animal>::iterator i_it = m_animals->begin(); i_it != m_animals->end(); i_it++) {
		(*i_it).update(deltaTime);
	}
	
	updateBabies(deltaTime);
	updateDeads(deltaTime);
}

void Play::updateBabies(float deltaTime) {

	std::vector<Animal> animals = *m_animals;

	for (int j = 0; j < animals.size(); j++) {

		Animal currentAnimal = animals.at(j);

		for (int i = 0; i < animals.size(); i++) {

			Animal animal = animals.at(i);

			if (currentAnimal != animal && currentAnimal.isNextTo(animal.getIndexes()) && 
				currentAnimal.couldHaveABaby() && animal.couldHaveABaby() && currentAnimal.getSpecies() == animal.getSpecies() &&
				currentAnimal.getGender() != animal.getGender())
			{
				for (int f = 0; f < 8; f++)
				{
					int nextX[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
					int nextY[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
					sf::Vector2i indexes(currentAnimal.getIndexes().x + nextX[f], currentAnimal.getIndexes().y + nextY[f]);

					if (!isAnimalHere(indexes))
					{
						createAnimal(indexes, currentAnimal.getSpecies());

						m_animals->at(j).restartBreedingClock();
						m_animals->at(i).restartBreedingClock();

						return;
					}
				}
			}
		}
	}
}

void Play::updateDeads(float deltaTime) {
	std::vector<Animal> animals = *m_animals;
	std::vector<Plant> plants = *m_plants;

	for (int j = 0; j < animals.size(); j++) {

		Animal currentAnimal = animals.at(j);

		if (currentAnimal.isStarved()) {
			std::vector<Animal>::const_iterator i_it = animals.begin();

			for (int v = 0; v != j; v++)
			{
				i_it++;
			}
			animals.erase(i_it);
		}
		else
		{
			for (int i = 0; i < animals.size(); i++) {

				Animal animal = animals.at(i);

				if (currentAnimal != animal && currentAnimal.isNextTo(animal.getIndexes()) &&
					currentAnimal.getDiet() == Diet::Carnivore && currentAnimal.getDiet() != animal.getDiet() &&
					currentAnimal.isHungry())
				{
					std::vector<Animal>::const_iterator i_it = animals.begin();

					for (int v = 0; v != i; v++)
					{
						i_it++;
					}

					animals.at(j).ate();
					animals.erase(i_it);
					break;
				}
			}

			for (int i = 0; i < plants.size(); i++) {

				Plant plant = plants.at(i);

				if (currentAnimal.isNextTo(plant.getIndexes()) && currentAnimal.getDiet() == Diet::Herbivore && currentAnimal.isHungry())
				{
					std::vector<Plant>::const_iterator i_it = plants.begin();

					for (int v = 0; v != i; v++) {
						i_it++;
					}

					animals.at(j).ate();
					plants.erase(i_it);
					break;
				}
			}
		}
	}

	m_plants->swap(plants);
	m_animals->swap(animals);
}

void Play::updatePlants(float deltaTime) {

	std::vector<Plant> plants = *m_plants;

	for (std::vector<Plant>::iterator i_it = m_plants->begin(); i_it != m_plants->end(); i_it++) {
		(*i_it).update(deltaTime);
	}

	for (std::vector<Plant>::iterator i_it = plants.begin(); i_it != plants.end(); i_it++)
	{
		Plant currentPlant = *i_it;

		if (currentPlant.pollination()) {
			for (int f = 0; f < 8; f++)
			{
				int nextX[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
				int nextY[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
				sf::Vector2i indexes(currentPlant.getIndexes().x + nextX[f], currentPlant.getIndexes().y + nextY[f]);

				if (!isPlantHere(indexes))
				{
					createPlant(indexes);
				}
			}
		}
	}
}


void Play::createAnimal(sf::Vector2i indexes, Species species) {

	if (m_animalsLimit <= m_animals->size()) return;

	int randomGender = rand() % 2;
	Gender gender;

	if (randomGender == 1) gender = Gender::Male;
	else gender = Gender::Female;

	createAnimal(indexes, species, gender);
}

void Play::createAnimal(sf::Vector2i indexes, Species species, Gender gender) {

	if (m_animalsLimit <= m_animals->size()) return;

	sf::Vector2f size(m_grid->getSize().x / 11, m_grid->getSize().y / 10);
	Animal* animal = new Animal(indexes, size, m_grid, m_animals, species, gender);

	m_animals->push_back(*animal);
}

void Play::createPlant(sf::Vector2i indexes) {

	sf::Vector2f size(m_grid->getSize().x / 11, m_grid->getSize().y / 10);
	Plant* plant = new Plant(indexes, size);

	m_plants->push_back(*plant);
}