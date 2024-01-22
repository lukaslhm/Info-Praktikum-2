/*
 * Simulation.cpp
 *
 *  Created on: 20.01.2024
 *      Author: llohm
 */
#include <stdexcept>
#include <sstream>

#include "SimuClient.h"
#include "Simulation.h"
#include "Kreuzung.h"
#include "Weg.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "Constants.h"

/**
 * Einlesen aus einem EIngabestream (z.B. Datei) und erstellen eines passenden Verkehrsnetzes
 * @param in Eingabestream mit Daten für das Verkehrsnetz
 * @param bMitGrafik Soll eine Grafik für das Verkehrsnetz erstellt werden
 */
void Simulation::vEinlesen(std::istream &in, bool bMitGrafik)
{
	p_bMitGrafik = bMitGrafik;
	if (bMitGrafik) bInitialisiereGrafik(1920, 1080);//Grafikoberfläche initialisieren wenn erforderlich
	unsigned int linecount = 0; // zeilen die verarbeitet wurden
	//Gesamten Stream verarbeiten
	while(!in.eof())
	{
		linecount++; // weitere Zeile bearbeitet
		std::string keyword;
		in >> keyword; //Keyword für den Datentyp auslesen

		if (keyword == INTERSECTION) //Bei Kreuzungen
		{
			auto Kr = std::make_shared<Kreuzung>();//leere Kreuzung erstellen
			in >> *Kr.get(); //einlesen
			if (p_pKreuzungen.find(Kr.get()->getName()) != p_pKreuzungen.end()) //Prüfen ob eine Kreuzung mit dem selben Namen schon vorhanden ist
			{
				std::stringstream errmsg;
				errmsg << "Line: " << linecount << " - Name der Kreuzung " << Kr.get()->getName() << " schon vergeben";
				throw std::runtime_error(errmsg.str()); //Exception werfen
			}
			p_pKreuzungen[Kr.get()->getName()] = Kr; //Wenn noch nicht vergeben zur Liste hinzufügen

			//Bei vorhandener Grafik einzeichnen
			if(bMitGrafik)
			{
				int x;
				int y;
				in >> x >> y;
				bZeichneKreuzung(x, y);
			}
		}

		else if (keyword == STREET) //Straßen
		{
			//Temporäre Variabeln
			std::string NameQ;
			std::string NameZ;
			std::string NameW1;
			std::string NameW2;
			double Laenge;
			int TLimitInt;
			int UeberholverbotInt;
			bool Ueberholverbot;
			Tempolimit TLimit = Tempolimit::Autobahn;

			//Setzen der Variablen aus dem Eingabestream
			in >> NameQ >> NameZ >> NameW1 >> NameW2 >> Laenge >> TLimitInt >> UeberholverbotInt;

			switch(UeberholverbotInt) //Umwandeln der Zahl in bool
			{
			case 0:
				Ueberholverbot = false;
				break;
			case 1:
				Ueberholverbot = true;
				break;
			default:
				std::stringstream errmsg;
				errmsg << "Line: " << linecount << " - Ueberholverbot corrupted got: " << UeberholverbotInt;
				throw std::runtime_error(errmsg.str());
				break;
				//Wenn weder 1 noch 0 übergeben wurden Fehlermeldung werfen
			}

			//Tempolimit in enum umwandeln
			switch(TLimitInt)
			{
			case 1:
				TLimit = Tempolimit::Innerorts;
				break;
			case 2:
				TLimit = Tempolimit::Landstrasse;
				break;
			case 3:
				TLimit = Tempolimit::Autobahn;
				break;
			default:
				std::stringstream errmsg;
				errmsg << "Line: " << linecount << " - Tempolimit corrupted got: " << TLimitInt;
				throw std::runtime_error(errmsg.str());
				break;
				//Exception wenn kein erwarteter Wert übergeben wurde
			}
			if (p_pKreuzungen.find(NameQ) == p_pKreuzungen.end())//Prüfen ob passende Anfangskreuzung existiert
			{
				std::stringstream errmsg;
				errmsg << "Line: " << linecount << " - Es existiert keine Kreuzung namens \"" << NameQ << "\"";
				throw std::runtime_error(errmsg.str()); //Exception werfen
			}
			if (p_pKreuzungen.find(NameZ) == p_pKreuzungen.end())//Prüfen ob passende Endkreuzung existiert
			{
				std::stringstream errmsg;
				errmsg << "Line: " << linecount << " - Es existiert keine Kreuzung namens \"" << NameZ << "\"";
				throw std::runtime_error(errmsg.str());//Exception werfen
			}


			//Kreuzung mit Weg verbinden
			Kreuzung::vVerbinde(NameW1, NameW2, Laenge, p_pKreuzungen[NameQ], p_pKreuzungen[NameZ], TLimit, Ueberholverbot);

			//Wenn Grafik existiert Weg einzeichnen
			if (bMitGrafik)
			{
				int anzahlCoords;
				in >> anzahlCoords; //Anzahl der Koordinaten

				int* coords = new int[anzahlCoords * 2];

				for (int i = 0; i<anzahlCoords; i++)//Alle Koordinaten auslesen
				{
					in >> coords[i*2];
					in >> coords[i*2+1];
				}

				bZeichneStrasse(NameW1, NameW2, Laenge, anzahlCoords, coords);//Weg mit Koordinaten einzeichnen
				delete[] coords;
			}
		}

		else if (keyword == CAR) //PKW
		{
			auto pkw = std::make_unique<PKW>(); //Temporäres Objekt erstellen
			std::string NameS;
			double TL;
			in >> *pkw.get() >> NameS >> TL; //Daten aus Stream einlesen
			if (p_pKreuzungen.find(NameS) == p_pKreuzungen.end()) //Prüfen ob die Startkreuzung existiert
			{
				std::stringstream errmsg;
				errmsg << "Line: " << linecount << " - Es existiert keine Kreuzung namens \"" << NameS << "\"";
				throw std::runtime_error(errmsg.str()); //Exception werfen
			}

			p_pKreuzungen[NameS]->vAnnahme(std::move(pkw), TL); //PKW auf Startkreuzung hinzufügen
		}

		else if (keyword == BIKE)//Fahrrad
		{
			auto bike = std::make_unique<Fahrrad>(); //Temporäres Objekt erstellen
			std::string NameS;
			double TL;
			in >> *bike.get() >> NameS >> TL; //Daten aus Stream einlesen
			if (p_pKreuzungen.find(NameS) == p_pKreuzungen.end()) //Prüfen ob die Startkreuzung existiert
			{
				std::stringstream errmsg;
				errmsg << "Line: " << linecount << " - Es existiert keine Kreuzung namens \"" << NameS << "\"";
				throw std::runtime_error(errmsg.str()); //Exception werfen
			}
			p_pKreuzungen[NameS]->vAnnahme(std::move(bike), TL); //Fahrrad auf Startkreuzung hinzufügen
		}

		else //Fehlermeldung wenn das Keyword unbekannt ist
		{
			std::stringstream errmsg;
			errmsg << "Line: " << linecount << " - Unknown Keyword \"" << keyword << "\"";
			throw std::runtime_error(errmsg.str());
		}
	}
}

/**
 * Simulieren des Verkehrsnetzes anhand der gespeicherten Kreuzungen
 * @param dDauer Dauer die das Verkehrsnetz simuliert werden soll
 * @param dZeitschritt Zeitschritte in denen das Verkehrsnetz simuliert werden soll
 */
void Simulation::vSimulieren(double dDauer, double dZeitschritt)
{
	//Simulieren
	for (dGlobaleZeit = 0; dGlobaleZeit <= dDauer; dGlobaleZeit += dZeitschritt)
	{
		vSetzeZeit(dGlobaleZeit);
		std::cout << "Zeit: " << dGlobaleZeit << std::endl;
		for (auto& it : p_pKreuzungen)
		{
			it.second->vSimulieren();
		}
	}
}
