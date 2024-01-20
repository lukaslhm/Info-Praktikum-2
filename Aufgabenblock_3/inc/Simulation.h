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

	void vEinlesen(std::istream& in);

	void vSimulieren(double dDauer, double dZeitschritt);

private:
	std::map<std::string, std::shared_ptr<Kreuzung>> p_pKreuzungen;
};

std::istream& operator>>(std::istream& in, Simulation& simu);

