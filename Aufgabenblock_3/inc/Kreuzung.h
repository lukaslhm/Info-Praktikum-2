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

	///Konstruktor für die Kreuzung mit Name und dem Tankvolumen der Kreuzung
	Kreuzung(std::string initName = "", double Tankstelle = 0.0);
	///Destruktor
	~Kreuzung();

	///Verbinden von Hin- und Rückweg mit den Kreuzungen und entsprechenden Parametern um ein zusammenhängendes Netz bauen zu können
	static void vVerbinde(
			std::string hinName,
			std::string rueckName,
			double weglaenge,
			std::weak_ptr<Kreuzung> startKreuzung,
			std::weak_ptr<Kreuzung> zielKreuzung,
			Tempolimit geschwindigkeitsbegrenzung,
			bool ueberholverbot
	);

	///Weg zur Kreuzung hinzufügen
	void addWeg(std::shared_ptr<Weg> newWeg);

	///Tanken von Fahrzeugen die bei der Kreuzung sind
	void vTanken(Fahrzeug& fzg);

	///Annahme von Fahrzeugen die von einem Weg auf die Kreuzung ankommen und weiterverarbeiten der Fahrzeuge
	void vAnnahme(std::unique_ptr<Fahrzeug> fzg, double startZeit);

	///Einlesen der Eigenschaften der Kreuzung aus einem Stream (Datei)
	void vEinlesen(std::istream& in) override;

	///Simulieren aller von der Kreuzung abgehenden Wege
	void vSimulieren();

	///Einen zufälligen Weg wählen auf dem das Fahrzug weiter fahren soll. Möglichst nicht den Ursprungsweg außer bei "Sackgassen"
	std::shared_ptr<Weg> pZufaelligerWeg(Weg& anfahrt);

	///Getterfunktion für den verbleibenden Inhalt in dem Tank der Tankstelle
	double getTankstellenInhalt() const;

private:
	///Wege die von der Kreuzung abgehenden
	std::vector<std::shared_ptr<Weg>> p_pWege;
	double p_dTankstelle;//Tankinhalt in Litern

	//Zufallgenerator für die Auswahl von einem zufälligen Weg
	static std::default_random_engine rng;
};
