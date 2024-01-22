#include <vector>
#include <memory>
#include <random>
#include <fstream>
#include <stdexcept>

#include "SimuClient.h"

#include "Fahrzeug.h"
#include "PKW.h"
#include "Fahrrad.h"

#include "Weg.h"
#include "vertagt_liste.h"

#include "Kreuzung.h"
#include "Simulation.h"

double dGlobaleZeit = 0;


/**
 * Testen der Operatorüberladung
 */
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

/**
 * Testen der Klasse Weg
 */
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

/**
 * Tests:
 * - 1Weg und 3 Fahrzeuge erzeugen, auf den Weg setzen und simulieren
 * 		-Verhalten
 * 		-Fahren
 * 		-Simulieren auf dem Weg
 * - Zusätzlich parkende Fahrzeuge und die vorbereitung von Ausnahmen
 * 		-Parken
 * 		-Meldung beim Losfahren und beim Streckenende
 */
void vAufgabe_5()
{
	Weg tempWeg("Straße 1", 100);

	tempWeg.vAnnahme(std::make_unique<PKW>("PKW 1", 50, 9));
	tempWeg.vAnnahme(std::make_unique<PKW>("PKW 2", 100, 10), 3);//Parkt
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

/**
 * Testen von:
 * - Exception Handling
 * 		- Ausnahmen: Losfahren, Streckenende
 * 		- Fangen mit try, catch
 * 		- Bearbeiten der Ausnahme
 * - Grafikausgabe
 * 		- Testen der GUI mit zwei Wegen
 * 		- Hin- und Rückweg
 * - Testen des verzögerten Updates bei Ausnahmesituationen
 * 		- Fehlermeldung bei der Simulation des Wegs, da der Iterator fehlt
 * - Test ob durch VListe der Fehler behoben wird
 */
void vAufgabe_6()
{
	bInitialisiereGrafik(800, 500);

	//Hin- und Rückweg definieren
	Weg hinWeg("Hin", 500, Tempolimit::Innerorts);
	Weg rueckWeg("Ruck", 500, Tempolimit::Innerorts);

	int coords[4] = {100, 100, 300, 300};

	//in GUI zeichnen
	bZeichneStrasse("Hin", "Ruck", 500, 2, coords);

	//Fahrzeuge auf Hinweg aufnehmen
	hinWeg.vAnnahme(std::make_unique<PKW>("PKW1", 50, 1, 500), 3);
	hinWeg.vAnnahme(std::make_unique<PKW>("PKW2", 100, 1, 500));
	hinWeg.vAnnahme(std::make_unique<Fahrrad>("Fahrrad1", 30));

	double dt = 0.1;

	//In 0.1 Schritten bis 11 Simulieren
	for (double t = 0; t < 11 * (1 + std::numeric_limits<double>::epsilon()); t += dt)
	{
		std::cout << "GlobaleZeit: " << dGlobaleZeit << std::endl;
		hinWeg.vSimulieren();//Simulation

		//Ausgabe
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

/**
 * Testen der neuen VListe mit VAktion
 * Test mittels Zufallszahlen, jede Funktion ausführen
 */
void vAufgabe_6a()
{
	//Initialisierung der Zufallszahlgenerierung
	static std::mt19937 device(0);
	std::uniform_int_distribution<int> dist(1, 10);

	//Liste initialisieren
	vertagt::VListe<int> testList;

	//10 Testelemente hinzufügen
	for (int i = 0; i<10; i++)
	{
		testList.push_back(dist(device));
	}


	testList.vAktualisieren();

	//Ausgeben
	std::cout << "Printout initial List" << std::endl;
	for (auto& it : testList)
	{
		std::cout << it << '\t';
	}
	std::cout << std::endl;

	//Alle Elemente >5 löschen
	for (auto it = testList.begin(); it != testList.end(); it++)
	{
		if (*it > 5) testList.erase(it);
	}

	//Erneute Ausgabe vor der Aktualisierung
	std::cout << "Printout after Erase but before vAktualisieren:" << std::endl;
	for (auto& it : testList)
	{
		std::cout << it << '\t';
	}
	std::cout << std::endl;

	//Aktualisierung
	testList.vAktualisieren();

	//Ausgabe nach Aktualisierung
	std::cout << "Printout after vAktualisieren:" << std::endl;
	for (auto& it : testList)
	{
		std::cout << it << '\t';
	}
	std::cout << std::endl;

	//Elemente vorne einfügen
	testList.push_front(11);
	testList.push_front(12);

	//Elemente hinten einfügen
	testList.push_back(11);
	testList.push_back(12);

	//Aktualisieren
	testList.vAktualisieren();

	//Ausgabe
	std::cout << "Printout after adding 11, 12 elements to front and back:" << std::endl;
	for (auto& it : testList)
	{
		std::cout << it << '\t';
	}
	std::cout << std::endl;
}
/**
 * Testen der in Aufgabenblock 3 hinzugefügten funktionen
 * Testen vom Überholverbot
 */
void vAufgabeBlock3Test()
{
	bInitialisiereGrafik(800, 500);

	//Hin- und Rückweg definieren
	Weg hinWeg("Hin", 500, Tempolimit::Landstrasse);
	Weg rueckWeg("Ruck", 500, Tempolimit::Landstrasse);

	int coords[4] = {100, 100, 300, 300};

	//in GUI zeichnen
	bZeichneStrasse("Hin", "Ruck", 500, 2, coords);

	//Fahrzeuge auf Hinweg aufnehmen
	hinWeg.vAnnahme(std::make_unique<PKW>("PKW1", 50, 10, 500), 3);
	hinWeg.vAnnahme(std::make_unique<PKW>("PKW5", 50, 10, 500), 3);
	hinWeg.vAnnahme(std::make_unique<PKW>("PKW2", 100, 10, 500));
	hinWeg.vAnnahme(std::make_unique<PKW>("PKW3", 45, 10, 500));
	hinWeg.vAnnahme(std::make_unique<Fahrrad>("Fahrrad1", 30));
	hinWeg.vAnnahme(std::make_unique<PKW>("PKW6", 100, 10, 500), 13);

	double dt = 0.2;
	//Simulieren
	for (int i = 0; i<2; i++)
	{
		for (double t = 0; t < 20 * (1 + std::numeric_limits<double>::epsilon()); t += dt)
		{
			std::cout << "GlobaleZeit: " << dGlobaleZeit << std::endl;
			hinWeg.vSimulieren();//Simulation

			vSetzeZeit(dGlobaleZeit);

			Weg::vKopf();
			std::cout << hinWeg << std::endl;

			dGlobaleZeit += dt;
		}
		hinWeg.vAnnahme(std::make_unique<PKW>("PKW4", 100, 1, 500), 13);//23
	}

	char c;
	std::cin >> c;
}
/**
 * Testen der in 6.2 vorgegebenen Karte und der Tankfunktion an Kreuzungen
 * Testen von Kreuzungen
 */
void vAufgabe_7()
{

	bInitialisiereGrafik(1280, 720);

	//Kreuzungen initialisieren
	auto Kr1 = std::make_shared<Kreuzung>("Kr1", 00);
	auto Kr2 = std::make_shared<Kreuzung>("Kr2", 100);
	auto Kr3 = std::make_shared<Kreuzung>("Kr3", 00);
	auto Kr4 = std::make_shared<Kreuzung>("Kr4", 00);

	//Kreuzungen zeichnen
	bZeichneKreuzung(680, 40);
	bZeichneKreuzung(680, 300);
	bZeichneKreuzung(680, 570);
	bZeichneKreuzung(320, 300);

	//Wege erstellen und direkt mit den Kreuzungen verbinden
	Kreuzung::vVerbinde("W12", "W21", 40, Kr1, Kr2, Tempolimit::Innerorts, true);
	Kreuzung::vVerbinde("W23a", "W32a", 115, Kr2, Kr3, Tempolimit::Autobahn, false);
	Kreuzung::vVerbinde("W23b", "W32b", 40, Kr2, Kr3, Tempolimit::Innerorts, true);
	Kreuzung::vVerbinde("W24", "W42", 55, Kr2, Kr4, Tempolimit::Innerorts, true);
	Kreuzung::vVerbinde("W34", "W43", 85, Kr3, Kr4, Tempolimit::Autobahn, false);
	Kreuzung::vVerbinde("W44a", "W44b", 130, Kr4, Kr4, Tempolimit::Landstrasse, false);

	//Wege zeichnen
	int coords1[4] = {680, 40, 680, 300};
	bZeichneStrasse("W12", "W21", 40, 2, coords1);

	int coords2[12] = {680, 300, 850, 300, 970, 390, 970, 500, 850, 570, 680, 570};
	bZeichneStrasse("W23a", "W32a", 115, 6, coords2);

	int coords3[4] = {680, 300, 680, 570};
	bZeichneStrasse("W23b", "W32b", 40, 2, coords3);

	int coords4[4] = {680, 300, 320, 300};
	bZeichneStrasse("W24", "W42", 55, 2, coords4);

	int coords5[10] = {680, 570, 500, 570, 350, 510, 320, 420, 320, 300};
	bZeichneStrasse("W34", "W43", 85, 5, coords5);

	int coords6[14] = {320, 300, 320, 150, 200, 60, 80, 90, 70, 250, 170, 300, 320, 300};
	bZeichneStrasse("W44a", "W44b", 130, 7, coords6);

	//Fahrzeuge erstellen und auf Kreuzung 1 platzieren
	Kr1->vAnnahme(std::make_unique<PKW>("PKW1", 150, 10, 55), 0);
	Kr1->vAnnahme(std::make_unique<Fahrrad>("Rad1", 30), 3);
	Kr1->vAnnahme(std::make_unique<PKW>("PKW2", 100, 10, 55), 6);
	Kr1->vAnnahme(std::make_unique<PKW>("PKW3", 90, 10, 55), 9);

	double eps = 0.05;

	//Simulieren
	for (dGlobaleZeit = 0; dGlobaleZeit < 30; dGlobaleZeit += eps)
	{
		Kr1->vSimulieren();
		Kr2->vSimulieren();
		Kr3->vSimulieren();
		Kr4->vSimulieren();

		std::cout << "Zeit: " << dGlobaleZeit << std::endl;
		vSetzeZeit(dGlobaleZeit);
	}

	char c;
	std::cin >> c;
}

/**
 * Testen der Einlesefunktion
 * einlesen der Datei VO.dat
 */
void vAufgabe_8()
{
	//Dateiname
	const std::string& filename = "VO.dat";
	std::ifstream infile(filename); //Datei mit ifstream öffnen

	Weg w1("w1", 200); //Weg erstellen

	//Leere Simulationsobjekte erstellen
	PKW pkw1;
	Fahrrad rad1("hi", 50);//Zur Fehlererzeugung
	//Fahrrad rad1;
	Kreuzung Kr1;

	//Weg auf Fahrzeuge setzen
	pkw1.vNeueStrecke(w1);
	rad1.vNeueStrecke(w1);

	//Excepion fangen
	try
	{
		//Datei einlesen
		infile >> pkw1;
		infile >> rad1;
		infile >> Kr1;
	}
	catch (std::runtime_error& re) //Exception handeling
	{
		std::cout << re.what() << std::endl; //Fehlermeldung ausgeben
		exit(-1); //Beenden
	}
	//Ausgabe
	std::cout << pkw1 << std::endl << rad1 << std::endl << Kr1 << std::endl;
}

/**
 * Testen des einlesens einer Datein und erstellen vom Verkehrsnetz
 * Prüfen ob alle Fehler erkannt werden
 */
void vAufgabe_9()
{
	Simulation simu;

	//const std::string& filename = "Simu.dat";//Datei zum einlesen
	const std::string& filename = "SimuKopie.dat";//Datei zum einlesen mit Fehlern
	std::ifstream infile(filename);

	//Fehler fangen
	try
	{
		simu.vEinlesen(infile);//Einlesen der Datei
	}
	catch(std::runtime_error& ex)
	{
		std::cout << ex.what() << std::endl;
		exit(-1);
	}
}
/**
 * Testen der grafischen Oberfläche
 */
void vAufgabe_9a()
{
	Simulation simu;

	const std::string& filename = "SimuDisplay.dat"; //Datei mit Grafikdaten
	//const std::string& filename = "SimuDisplay_plus.dat"; //erweiterte Datei mit Grafikdaten
	std::ifstream infile(filename);

	try
	{
		simu.vEinlesen(infile, true); //Einlesen und Grafik erstellen
	}
	catch(std::runtime_error& ex)
	{
		std::cout << ex.what() << std::endl;
		exit(-1);
	}

	//Simulieren
	simu.vSimulieren(40, 0.1);

	char c;
	std::cin >> c;
}

/**
 * Main methode
 * @return 0
 */
int main()
{
	//vAufgabeBlock3Test();
	vAufgabe_9a();
	return 0;
}



