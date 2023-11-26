#include <vector>
#include <memory>

#include "SimuClient.h"

#include "Fahrzeug.h"
#include "PKW.h"
#include "Fahrrad.h"

#include "Weg.h"

double dGlobaleZeit = 0;

void vAufgabe_3()
{
	std::vector<std::unique_ptr<Fahrzeug>> vec;
	vec.push_back(move(std::make_unique<PKW>("PKW1", 30, 8.9)));
	vec.push_back(move(std::make_unique<PKW>("PKW2", 50, 7)));
	vec.push_back(move(std::make_unique<Fahrrad>("Rad1", 20)));
	vec.push_back(move(std::make_unique<Fahrrad>("Rad2", 25)));

	dGlobaleZeit += 1;

	std::cout << std::endl;

	for (auto it = vec.begin(); it != vec.end(); it++)
	{
		it->get()->vSimulieren();
	}

	Fahrzeug::vKopf();
	for (auto it = vec.begin(); it != vec.end(); it++)
	{
		std::cout << *it->get() << std::endl;
	}

	std::cout << std::endl;
	std::cout << "PKW1 < PKW2: " << (vec.at(0) < vec.at(1)) << std::endl;
	std::cout << "PKW2 < PKW1: " << (vec.at(1) < vec.at(0)) << std::endl << std::endl;

	std::cout << "PKW1 = PKW2" << std::endl;
	*vec.at(0).get() = *vec.at(1).get();

	Fahrzeug::vKopf();
	for (auto it = vec.begin(); it != vec.end(); it++)
	{
		std::cout << *it->get() << std::endl;
	}
	std::cout << std::endl << "FINISH!" << std::endl << std::endl;
}

void vAufgabe_4()
{
	Weg w("Weg", 100);
	PKW p("PKW1", 50, 9);
	Weg::vKopf();
	std::cout << w << std::endl;
	std::cout << std::endl;
	Fahrzeug::vKopf();
	std::cout << p << std::endl;
}

void vAufgabe_5()
{
	Weg tempWeg("Straße 1", 100);

	tempWeg.vAnnahme(std::make_unique<PKW>("PKW 1", 50, 9));
	tempWeg.vAnnahme(std::make_unique<PKW>("PKW 2", 100, 10), 3);
	tempWeg.vAnnahme(std::make_unique<Fahrrad>("Fahrrad 1", 30));

	double dt = 0.25;

	for (double t = 0; t < 5 * (1 + std::numeric_limits<double>::epsilon()); t += dt)
	{
		tempWeg.vSimulieren();
		
		std::cout << "GlobaleZeit: " << dGlobaleZeit << std::endl;
		Weg::vKopf();
		std::cout << tempWeg << std::endl;
		std::cout << std::endl;
		tempWeg.vFahrzeugeAusgeben();
		std::cout << std::endl << std::endl;
		
		dGlobaleZeit += dt;
	}
}

void vAufgabe_6()
{
	Weg tempWeg("Straße 1", 100, Tempolimit::Innerorts);

	tempWeg.vAnnahme(std::make_unique<PKW>("PKW 1", 50, 9), 3);
	tempWeg.vAnnahme(std::make_unique<PKW>("PKW 2", 100, 10));
	tempWeg.vAnnahme(std::make_unique<Fahrrad>("Fahrrad 1", 30));

	double dt = 0.25;

	for (double t = 0; t < 5 * (1 + std::numeric_limits<double>::epsilon()); t += dt)
	{
		std::cout << "GlobaleZeit: " << dGlobaleZeit << std::endl;
		tempWeg.vSimulieren();

		Weg::vKopf();
		std::cout << tempWeg << std::endl;
		std::cout << std::endl;
		tempWeg.vFahrzeugeAusgeben();
		std::cout << std::endl << std::endl;

		dGlobaleZeit += dt;
	}
}

int main()
{
	vAufgabe_6();
	return 0;
}
