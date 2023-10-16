/*
 * Fahrzeug.cpp
 *
 *  Created on: 15.10.2023
 *      Author: llohm
 */

#include "Fahrzeug.h"

int Fahrzeug::p_iIDCnt = 0;

Fahrzeug::Fahrzeug()
	: p_sName(""), p_iID(p_iIDCnt++), p_dMaxGeschwindigkeit(0), p_dGesamtZeit(0), p_dZeit(0)
{
	std::cout << "New Fahrzeug generated: " << p_sName << " - " << p_iID << std::endl;

}

Fahrzeug::Fahrzeug(std::string initName)
	: p_sName(initName), p_iID(p_iIDCnt++), p_dMaxGeschwindigkeit(0), p_dGesamtZeit(0), p_dZeit(0)
{
	std::cout << "New Fahrzeug generated: " << p_sName << " - " << p_iID << std::endl;
}

Fahrzeug::Fahrzeug(std::string initName, double initMaxVelo)
	: p_sName(initName), p_iID(p_iIDCnt++), p_dMaxGeschwindigkeit(initMaxVelo >= 0 ? initMaxVelo : 0), p_dGesamtZeit(0), p_dZeit(0)
{
}

Fahrzeug::~Fahrzeug()
{
	std::cout << "Fahrzeug deleted: " << p_sName << " - " << p_iID << std::endl;
}


