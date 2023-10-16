/*
 * Fahrzeug.h
 *
 *  Created on: 15.10.2023
 *      Author: llohm
 */
#pragma once

#include <string>
#include <iostream>

#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_

class Fahrzeug {
public:
	Fahrzeug();
	Fahrzeug(std::string initName);
	Fahrzeug(std::string initName, double initMaxVelo);
	virtual ~Fahrzeug();


private:
	std::string p_sName;
	const int p_iID;
	static int p_iIDCnt;
	double p_dMaxGeschwindigkeit;
	double p_dGesamtZeit;
	double p_dZeit;

};

#endif /* FAHRZEUG_H_ */
