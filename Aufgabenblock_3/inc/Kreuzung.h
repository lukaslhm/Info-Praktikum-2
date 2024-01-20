/*
 * Kreuzung.h
 *
 *  Created on: 20.01.2024
 *      Author: llohm
 */

#pragma once
#include <vector>
#include <memory>
#include <string>
#include <random>
#include "Simulationsobjekt.h"
#include "Tempolimit.h"

class Weg;
class Fahrzeug;

class Kreuzung : public Simulationsobjekt
{
public:
	Kreuzung(std::string initName, double Tankstelle = 0.0);
	~Kreuzung();

	static void vVerbinde(
			std::string hinName,
			std::string rueckName,
			double weglaenge,
			std::weak_ptr<Kreuzung> startKreuzung,
			std::weak_ptr<Kreuzung> zielKreuzung,
			Tempolimit geschwindigkeitsbegrenzung,
			bool ueberholverbot
	);

	void addWeg(std::shared_ptr<Weg> newWeg);

	void vTanken(Fahrzeug& fzg);

	void vAnnahme(std::unique_ptr<Fahrzeug> fzg, double startZeit);

	void vSimulieren();

	std::shared_ptr<Weg> pZufaelligerWeg(Weg& anfahrt);

	double getTankstellenInhalt() const;

private:
	std::vector<std::shared_ptr<Weg>> p_pWege;
	double p_dTankstelle;

	static std::default_random_engine rng;
};
