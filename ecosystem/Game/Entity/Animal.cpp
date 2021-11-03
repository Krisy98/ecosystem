#include "stdafx.h"
#include "Animal.h"

#include <iostream>

Animal::Animal(sf::Vector2i indexesPosition, sf::Vector2f size, Grid* grid, std::vector<Animal>* animals, Species species, Gender gender) :
	digestionTime{
		sf::seconds(5.0f)
	},
	starve {
		sf::seconds(30.0f)
	}
{
	sf::Vector2f position(indexesPosition.x * size.x, indexesPosition.y * size.y);

	srand(time(NULL));

	setPosition(position);
	setSize(size);
	setSpeed(size);

	this->indexesPos = indexesPosition;
	this->grid = grid;

	this->animals = animals;
	this->m_diet = m_diet;
	this->species = species;
	this->gender = gender;

	restartBreedingClock();
	m_hungryClock.restart();


	switch (species)
	{
		case Species::Cow:
			m_diet = Diet::Herbivore;
			this->breedingPeriod = sf::seconds(4.0f);

			if (gender == Gender::Female) {
				if (!m_animalTexture.loadFromFile(".\\Assets\\sprite_sheet/cow.png")) {
					std::cout << "error loading file texture ..." << std::endl;
				}
			}
			else {
				if (!m_animalTexture.loadFromFile(".\\Assets\\sprite_sheet/bull.png")) {
					std::cout << "error loading file texture ..." << std::endl;
				}
			}
			break;

		case Species::Lion:
		default:
			m_diet = Diet::Carnivore;
			this->breedingPeriod = sf::seconds(15.0f);

			if (gender == Gender::Female) {
				if (!m_animalTexture.loadFromFile(".\\Assets\\sprite_sheet/lioness.png")) {
					std::cout << "error loading file texture ..." << std::endl;
				}
			}
			else {
				if (!m_animalTexture.loadFromFile(".\\Assets\\sprite_sheet/lion.png")) {
					std::cout << "error loading file texture ..." << std::endl;
				}
			}
			break;
	}


	m_skin.setTexture(m_animalTexture);
	m_skin.setTextureRect(sf::IntRect(0, 0, 200, 200));
	m_skin.setPosition(position);


	m_skin.setScale(size.x/200, size.y/200);


}

void Animal::update(float deltaTime) {
	int coefX[9] = { 1, 1, 0, -1, -1, -1, 0, 1, 0 };
	int coefY[9] = { 0, 1, 1, 1, 0, -1, -1, -1, 0 };
	int dir = rand() % 9;

	sf::Vector2f newPos = getPosition();
	sf::Vector2f speed = getSpeed();
	sf::Vector2i indexes = sf::Vector2i(getIndexes().x + coefX[dir], getIndexes().y + coefY[dir]);
	
	if (indexes.x >= 0 && indexes.x < grid->getNColumns() && indexes.y >= 0 && indexes.y < grid->getNRows()) {
		bool canMove = true;

		for (std::vector<Animal>::iterator i_it = animals->begin(); i_it != animals->end(); i_it++) 
		{
			if (indexes == (*i_it).getIndexes())
			{
				canMove = false;
			}
		}

		if (canMove) {

			newPos = sf::Vector2f(newPos.x + (speed.x * coefX[dir]), newPos.y + (speed.y * coefY[dir]));

			setPosition(newPos);
			indexesPos = indexes;

			m_skin.setPosition(newPos);
		}
	}

}

void Animal::render(sf::RenderTarget& target) {
	target.draw(m_skin);
}

void Animal::handleEvent(sf::Event event) {

}

void Animal::restartBreedingClock() {
	m_breedingClock.restart();
}

void Animal::ate() {
	m_hungryClock.restart();
}

bool Animal::isNextTo(sf::Vector2i entityIndexesPos) {
	sf::Vector2i currIndexesPos = getIndexes();

	return grid->isNextTo(currIndexesPos, entityIndexesPos);
}

bool Animal::couldHaveABaby() {
	return (m_breedingClock.getElapsedTime().asSeconds() >= breedingPeriod.asSeconds());
}

bool Animal::isHungry() {
	return (m_hungryClock.getElapsedTime().asSeconds() >= digestionTime.asSeconds());
}

bool Animal::isStarved() {
	return (m_hungryClock.getElapsedTime().asSeconds() >= starve.asSeconds());
}

sf::Vector2i Animal::getIndexes() {
	return indexesPos;
}

Grid Animal::getGrid() {
	return *grid;
}

Diet Animal::getDiet() {
	return m_diet;
}

Species Animal::getSpecies() {
	return species;
}

Gender Animal::getGender() {
	return this->gender;
}

bool& Animal::operator!=(Animal animal) {
	sf::Vector2f pos = getPosition();

	bool equal = !(pos.x == animal.getPosition().x &&
		pos.y == animal.getPosition().y);

	return equal;
}