#include <vector>
#include <memory>
#include <random>

#include "SimuClient.h"

#include "Fahrzeug.h"
#include "PKW.h"
#include "Fahrrad.h"

#include "Weg.h"
#include "vertagt_liste.h"

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
	Weg tempWeg("Stra�e 1", 100);

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
	bInitialisiereGrafik(800, 500);

	Weg hinWeg("Hin", 500, Tempolimit::Innerorts);
	Weg rueckWeg("Ruck", 500, Tempolimit::Innerorts);

	int coords[4] = {100, 100, 300, 300};

	bZeichneStrasse("Hin", "Ruck", 500, 2, coords);

	hinWeg.vAnnahme(std::make_unique<PKW>("PKW1", 50, 1, 500), 3);
	hinWeg.vAnnahme(std::make_unique<PKW>("PKW2", 100, 1, 500));
	hinWeg.vAnnahme(std::make_unique<Fahrrad>("Fahrrad1", 30));

	double dt = 0.1;

	for (double t = 0; t < 11 * (1 + std::numeric_limits<double>::epsilon()); t += dt)
	{
		std::cout << "GlobaleZeit: " << dGlobaleZeit << std::endl;
		hinWeg.vSimulieren();

		Weg::vKopf();
		std::cout << hinWeg << std::endl;
		std::cout << std::endl;
		hinWeg.vFahrzeugeAusgeben();
		std::cout << std::endl << std::endl;

		vSetzeZeit(dGlobaleZeit);

		dGlobaleZeit += dt;
	}

	char c;
	std::cin >> c;
}

void vAufgabe_6a()
{
	static std::mt19937 device(0);
	std::uniform_int_distribution<int> dist(1, 10);

	vertagt::VListe<int> testList;

	for (int i = 0; i<10; i++)
	{
		testList.push_back(dist(device));
	}

	testList.vAktualisieren();

	std::cout << "Printout initial List" << std::endl;
	for (auto& it : testList)
	{
		std::cout << it << '\t';
	}
	std::cout << std::endl;

	for (auto it = testList.begin(); it != testList.end(); it++)
	{
		if (*it > 5) testList.erase(it);
	}

	std::cout << "Printout after Erase but before vAktualisieren:" << std::endl;
	for (auto& it : testList)
	{
		std::cout << it << '\t';
	}
	std::cout << std::endl;

	testList.vAktualisieren();

	std::cout << "Printout after vAktualisieren:" << std::endl;
	for (auto& it : testList)
	{
		std::cout << it << '\t';
	}
	std::cout << std::endl;

	testList.push_front(11);
	testList.push_front(12);

	testList.push_back(11);
	testList.push_back(12);

	testList.vAktualisieren();

	std::cout << "Printout after adding 11, 12 elements to front and back:" << std::endl;
	for (auto& it : testList)
	{
		std::cout << it << '\t';
	}
	std::cout << std::endl;
}

int main()
{
	vAufgabe_6();
	return 0;
}



