/*
 * Simulation.h
 *
 *  Created on: 20.01.2024
 *      Author: llohm
 */
#pragma once

#include <iostream>
#include <map>
#include <string>
#include <memory>

#include "Kreuzung.h"

class Simulation
{
public:

	///Einlesen aus einem Eingabestream und Erzeugung von passendem Verkehrsnetz
	void vEinlesen(std::istream& in, bool bMitGrafik = false);

	///Simulieren des Verkehrsnetzes
	void vSimulieren(double dDauer, double dZeitschritt);

private:
	///Alle Kreuzungen des Verkehrsnetzes sowie die Namen um Dopplungen zu verhindern
	std::map<std::string, std::shared_ptr<Kreuzung>> p_pKreuzungen;
	bool p_bMitGrafik = false; //Soll eine Grafikansicht erzeugt werden
};
