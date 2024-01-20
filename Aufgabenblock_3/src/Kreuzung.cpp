/*
 * Kreuzung.cpp
 *
 *  Created on: 20.01.2024
 *      Author: llohm
 */

#include <Kreuzung.h>
#include <iterator>
#include "Weg.h"
#include "Fahrzeug.h"

std::default_random_engine Kreuzung::rng;

Kreuzung::Kreuzung(std::string initName, double Tankstelle)
	: Simulationsobjekt(initName), p_dTankstelle(Tankstelle)
{
}

Kreuzung::~Kreuzung() {
}

void Kreuzung::vVerbinde(
		std::string hinName,
		std::string rueckName,
		double weglaenge,
		std::weak_ptr<Kreuzung> startKreuzung,
		std::weak_ptr<Kreuzung> zielKreuzung,
		Tempolimit geschwindigkeitsbegrenzung,
		bool ueberholverbot)
{
	auto tempHWeg = std::make_shared<Weg>(hinName, weglaenge, geschwindigkeitsbegrenzung, ueberholverbot, zielKreuzung);
	auto tempRWeg = std::make_shared<Weg>(rueckName, weglaenge, geschwindigkeitsbegrenzung, ueberholverbot, startKreuzung);

	tempHWeg->setRueckWeg((std::weak_ptr<Weg>) tempRWeg);
	tempRWeg->setRueckWeg((std::weak_ptr<Weg>) tempHWeg);

	startKreuzung.lock()->addWeg(tempHWeg);
	zielKreuzung.lock()->addWeg(tempRWeg);
}

void Kreuzung::addWeg(std::shared_ptr<Weg> newWeg)
{
	p_pWege.push_back(newWeg);
}

void Kreuzung::vTanken(Fahrzeug &fzg)
{
	if (p_dTankstelle > 0)
	{
		double tankMenge = fzg.dTanken();
		p_dTankstelle -= tankMenge;

		if (p_dTankstelle < 0) p_dTankstelle = 0;
	}
}

void Kreuzung::vAnnahme(std::unique_ptr<Fahrzeug> fzg, double startZeit)
{
	vTanken(*fzg.get());
	p_pWege.begin()->get()->vAnnahme(std::move(fzg), startZeit);
}

void Kreuzung::vSimulieren()
{
	for (auto& it : p_pWege)
	{
		it->vSimulieren();
	}
}

std::shared_ptr<Weg> Kreuzung::pZufaelligerWeg(Weg& anfahrt)
{
	if (p_pWege.size() == 0) return nullptr;
	else if (p_pWege.size() == 1) return *p_pWege.begin();

	std::uniform_int_distribution<int> dist(0, p_pWege.size() - 1);

	std::shared_ptr<Weg> result;
	do
	{
		result = p_pWege.at(dist(rng));
	} while(*result.get() == *anfahrt.getRuckWeg().get());

	return result;
}

double Kreuzung::getTankstellenInhalt() const
{
	return p_dTankstelle;
}
