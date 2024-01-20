/*
 * Simulation.cpp
 *
 *  Created on: 20.01.2024
 *      Author: llohm
 */
#include <stdexcept>
#include <sstream>

#include "Simulation.h"
#include "Kreuzung.h"
#include "Weg.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "Constants.h"

void Simulation::vEinlesen(std::istream &in)
{
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
		}

		else if (keyword == STREET)
		{
			std::string NameQ;
			std::string NameZ;
			std::string NameW1;
			std::string NameW2;
			double Laenge;
			int TLimitInt;
			bool Ueberholverbot;
			Tempolimit TLimit = Tempolimit::Autobahn;

			in >> NameQ >> NameZ >> NameW1 >> NameW2 >> Laenge >> TLimitInt >> Ueberholverbot;

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
		std::cout << "Zeit: " << dGlobaleZeit << std::endl;
		for (auto& it : p_pKreuzungen)
		{
			it.second->vSimulieren();
		}
	}
}

std::istream& operator>>(std::istream &in, Simulation& simu)
{
	simu.vEinlesen(in);
	return in;
}
