/*
 * Kreuzung.cpp
 *
 *  Created on: 20.01.2024
 *      Author: llohm
 */

#include "Kreuzung.h"
#include <iterator>
#include "Weg.h"
#include "Fahrzeug.h"

//Zufallsgenerator um zufällig einen Weg zum weiterfahren zu wählen
std::default_random_engine Kreuzung::rng;

/**
 * Konstruktor für eine Kreuzung
 *
 * @param initName Name für die Kreuzung
 * @param Tankstelle Volumen des Tanks der Tankstelle
 */
Kreuzung::Kreuzung(std::string initName, double Tankstelle)
	: Simulationsobjekt(initName), p_dTankstelle(Tankstelle)
{
}

/**
 * Destruktor
 */
Kreuzung::~Kreuzung() {
}

/**
 * Verbinden der Wege mit den Kreuzungen um ein zusammenhängendes Verkehrsnetz zu ermöglichen
 *
 * @param hinName Name des Hinwegs
 * @param rueckName Name des Rückwegs
 * @param weglaenge Länge des Weges (gilt für Hin- und Rückweg)
 * @param startKreuzung Pointer auf die Kreuzung bei der der Weg beginnen soll
 * @param zielKreuzung Pointer auf die Kreuzung bei der der Weg enden soll
 * @param geschwindigkeitsbegrenzung Geschwindigkeitsbegrenzung für den Weg (gilt für Hin- und Rückweg)
 * @param ueberholverbot Gilt ein Überholverbot auf Hin- und Rückweg
 */
void Kreuzung::vVerbinde(
		std::string hinName,
		std::string rueckName,
		double weglaenge,
		std::weak_ptr<Kreuzung> startKreuzung,
		std::weak_ptr<Kreuzung> zielKreuzung,
		Tempolimit geschwindigkeitsbegrenzung,
		bool ueberholverbot)
{
	//Temporäres erstellen von Hin- und Rückweg
	auto tempHWeg = std::make_shared<Weg>(hinName, weglaenge, geschwindigkeitsbegrenzung, ueberholverbot, zielKreuzung);
	auto tempRWeg = std::make_shared<Weg>(rueckName, weglaenge, geschwindigkeitsbegrenzung, ueberholverbot, startKreuzung);

	//Bei den Wegen den jeweiligen anderen Weg als Rückweg angeben. Weakptr da es sonst eine Ringreferenz ist
	tempHWeg->setRueckWeg((std::weak_ptr<Weg>) tempRWeg);
	tempRWeg->setRueckWeg((std::weak_ptr<Weg>) tempHWeg);

	//Bei der Start und Zielkreuzung den jeweils Abgehenden Weg als Referenz übergeben. Benuzten von lock() um den Inhalt der weak_ptr bearbeiten zu können
	startKreuzung.lock()->addWeg(tempHWeg);
	zielKreuzung.lock()->addWeg(tempRWeg);
}

/**
 * Einen Weg zu der Kreuzung hinzufügen
 * @param newWeg shared_prt auf den Weg
 */
void Kreuzung::addWeg(std::shared_ptr<Weg> newWeg)
{
	p_pWege.push_back(newWeg); // Weg zur Liste hinzufügen
}

/**
 * Tanken eines Fahrzeugs was bei der Kreuzung ist
 * @param fzg
 */
void Kreuzung::vTanken(Fahrzeug &fzg)
{

	if (p_dTankstelle > 0) //Nur Tanken wenn der Tank nicht leer ist
	{
		double tankMenge = fzg.dTanken();
		p_dTankstelle -= tankMenge; //Tank der Tankstelle um abgegebene Menge reduzieren

		if (p_dTankstelle < 0) p_dTankstelle = 0; //Wenn der Tank leer ist auf 0 setzen
	}
}

/**
 * Fahrzeug was bei der Kreuzung ankommt aufnehmen. Anschließend tanken und auf den ersten abgehenden Weg parken
 * @param fzg
 * @param startZeit
 */
void Kreuzung::vAnnahme(std::unique_ptr<Fahrzeug> fzg, double startZeit)
{
	vTanken(*fzg.get());//Tanken
	p_pWege.begin()->get()->vAnnahme(std::move(fzg), startZeit); //Auf dem ersten Weg parken
}

/**
 * Alle abgehenden Wege simulieren
 */
void Kreuzung::vSimulieren()
{
	//jeden Weg simulieren
	for (auto& it : p_pWege)
	{
		it->vSimulieren();
	}
}
/**
 * Zufällig einen Weg auswählen auf dem das Fahrzeug weiterfahren soll.
 * Es wird möglichst nicht der Weg gewählt auf dem das Fahrzeug ankam. Ausnahme sind Sackgassen
 *
 * @param anfahrt Weg auf dem das Fahrzeug angekommen ist
 * @return Weg auf dem das Fahrzeug weiterfahren soll
 */
std::shared_ptr<Weg> Kreuzung::pZufaelligerWeg(Weg& anfahrt)
{
	if (p_pWege.size() == 0) return nullptr; //Keine abgehenden Wege auf dem das Fahrzeug fahren kann
	else if (p_pWege.size() == 1) return *p_pWege.begin(); // Sackgasse -> Fahrzeug muss auf dem selben Weg zurückfahren

	std::uniform_int_distribution<int> dist(0, p_pWege.size() - 1); //Zufallsgenerierung für ganzzahlige Zahlen von 0 bis zur Anzahl der Wege -1 (da Liste) initialisieren

	std::shared_ptr<Weg> result;//Ergebnissweg, Weg auf dem das Fahrzeug weiterfahren soll
	//So lange neuen Weg auswählen bis der Weg nicht dem Anfahrtsweg entspricht
	do
	{
		result = p_pWege.at(dist(rng)); //Zufallszahl generieren und Weg aus Liste wählen
	} while(*result.get() == *anfahrt.getRuckWeg().get()); //Wenn der Weg dem Rückweg vom Anfahrtsweg entspricht neuen Weg auswählen

	return result;
}

/**
 * Einlesen der Eigenschaften der Kreuzung aus einem Stream (Dateieinlesen)
 * @param in Eingangsstream
 */
void Kreuzung::vEinlesen(std::istream &in)
{
	Simulationsobjekt::vEinlesen(in);
	in >> p_dTankstelle;
}
/**
 * Getterfunktion für den verbleibenden Tankstelleninhalt
 * @return Restlicher Tankstelleninhalt
 */
double Kreuzung::getTankstellenInhalt() const
{
	return p_dTankstelle;
}
