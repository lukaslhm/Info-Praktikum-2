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

void Simulation::vEinlesen(std::istream &in, bool bMitGrafik)
{
	p_bMitGrafik = bMitGrafik;
	if (bMitGrafik) bInitialisiereGrafik(1920, 1080);
	unsigned int linecount = 0;
	while(!in.eof())
	{
		linecount++;
		std::string keyword;
		in >> keyword;

		if (keyword == INTERSECTION)
		{
			auto Kr = std::make_shared<Kreuzung>();
			in >> *Kr.get();
			if (p_pKreuzungen.find(Kr.get()->getName()) != p_pKreuzungen.end())
			{
				std::stringstream errmsg;
				errmsg << "Line: " << linecount << " - Name der Kreuzung " << Kr.get()->getName() << " schon vergeben";
				throw std::runtime_error(errmsg.str());
			}
			p_pKreuzungen[Kr.get()->getName()] = Kr;

			if(bMitGrafik)
			{
				int x;
				int y;
				in >> x >> y;
				bZeichneKreuzung(x, y);
			}
		}

		else if (keyword == STREET)
		{
			std::string NameQ;
			std::string NameZ;
			std::string NameW1;
			std::string NameW2;
			double Laenge;
			int TLimitInt;
			int UeberholverbotInt;
			bool Ueberholverbot;
			Tempolimit TLimit = Tempolimit::Autobahn;

			in >> NameQ >> NameZ >> NameW1 >> NameW2 >> Laenge >> TLimitInt >> UeberholverbotInt;

			switch(UeberholverbotInt)
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
			}

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
			}
			if (p_pKreuzungen.find(NameQ) == p_pKreuzungen.end())
			{
				std::stringstream errmsg;
				errmsg << "Line: " << linecount << " - Es existiert keine Kreuzung namens \"" << NameQ << "\"";
				throw std::runtime_error(errmsg.str());
			}
			if (p_pKreuzungen.find(NameZ) == p_pKreuzungen.end())
			{
				std::stringstream errmsg;
				errmsg << "Line: " << linecount << " - Es existiert keine Kreuzung namens \"" << NameZ << "\"";
				throw std::runtime_error(errmsg.str());
			}

			Kreuzung::vVerbinde(NameW1, NameW2, Laenge, p_pKreuzungen[NameQ], p_pKreuzungen[NameZ], TLimit, Ueberholverbot);

			if (bMitGrafik)
			{
				int anzahlCoords;
				in >> anzahlCoords;

				int* coords = new int[anzahlCoords * 2];

				for (int i = 0; i<anzahlCoords; i++)
				{
					in >> coords[i*2];
					in >> coords[i*2+1];
				}

				bZeichneStrasse(NameW1, NameW2, Laenge, anzahlCoords, coords);
				delete[] coords;
			}
		}

		else if (keyword == CAR)
		{
			auto pkw = std::make_unique<PKW>();
			std::string NameS;
			double TL;
			in >> *pkw.get() >> NameS >> TL;
			if (p_pKreuzungen.find(NameS) == p_pKreuzungen.end())
			{
				std::stringstream errmsg;
				errmsg << "Line: " << linecount << " - Es existiert keine Kreuzung namens \"" << NameS << "\"";
				throw std::runtime_error(errmsg.str());
			}

			p_pKreuzungen[NameS]->vAnnahme(std::move(pkw), TL);
		}

		else if (keyword == BIKE)
		{
			auto bike = std::make_unique<Fahrrad>();
			std::string NameS;
			double TL;
			in >> *bike.get() >> NameS >> TL;
			if (p_pKreuzungen.find(NameS) == p_pKreuzungen.end())
			{
				std::stringstream errmsg;
				errmsg << "Line: " << linecount << " - Es existiert keine Kreuzung namens \"" << NameS << "\"";
				throw std::runtime_error(errmsg.str());
			}
			p_pKreuzungen[NameS]->vAnnahme(std::move(bike), TL);
		}

		else
		{
			std::stringstream errmsg;
			errmsg << "Line: " << linecount << " - Unknown Keyword \"" << keyword << "\"";
			throw std::runtime_error(errmsg.str());
		}
	}
}

void Simulation::vSimulieren(double dDauer, double dZeitschritt)
{
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
