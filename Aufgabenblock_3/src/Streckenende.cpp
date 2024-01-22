#include <Constants.h>
#include <iostream>
#include <iomanip>

#include "Fahrzeug.h"
#include "Weg.h"
#include "Streckenende.h"
#include "Kreuzung.h"

/**
 * Konstruktor für die Ausnahme Streckenende, wird benutzt wenn ein Fahrzeug am Ende von einem Weg angekommen ist.
 *
 * @param initFzg Fahrzeug auf das die Ausnahme angewendet werden soll
 * @param initWeg Weg auf dem sich das Fahrzeug befindet
 */
Streckenende::Streckenende(Fahrzeug& initFzg, Weg& initWeg)
	: Fahrausnahme(initFzg, initWeg)
{
}

/**
 * Destruktor für die Ausnahme Streckenende
 */
Streckenende::~Streckenende()
{
}

/**
 * Funktion um das Verhalten vom Fahrzeug beim Auftreten der Ausnahme zu ändern.
 * Wenn das Fahrzeug am Ende vom Weg angekommen ist wird es vom Weg entfernt.
 *
 */
void Streckenende::vBearbeiten()
{
	if (p_pWeg.getZielKreuzung() == nullptr)
	{
		p_pWeg.pAbgabe(p_pFahrzeug);
	}
	else
	{
		std::shared_ptr<Weg> tempNewWeg = p_pWeg.getZielKreuzung()->pZufaelligerWeg(p_pWeg);

		auto oldPrec = std::cout.precision();

		std::cout << "Streckenende-Ausnahme:" << std::endl;

		std::cout << std::left;
		std::cout << std::setw(LINKESPALTE_W) << "ZEIT";
		std::cout << std::setw(SEPERATOR_WIDTH) << ":";
		std::cout << std::setprecision(4) << dGlobaleZeit << std::setprecision(oldPrec) << std::endl;

		std::cout << std::setw(LINKESPALTE_W) << "KREUZUNG";
		std::cout << std::setw(SEPERATOR_WIDTH) << ":";
		std::cout << std::setw(NAME_WIDTH) << p_pWeg.getZielKreuzung()->getName() << std::setw(SEPERATOR_WIDTH) << " ";
		std::cout << std::setprecision(2) << p_pWeg.getZielKreuzung()->getTankstellenInhalt() << std::setprecision(oldPrec) << std::endl;

		std::cout << std::setw(LINKESPALTE_W) << "Wechsel";
		std::cout << std::setw(SEPERATOR_WIDTH) << ":";
		std::cout << std::setw(NAME_WIDTH) << p_pWeg.getName() << std::setw(SEPERATOR_WIDTH) << "->";
		std::cout << std::setw(NAME_WIDTH) << tempNewWeg->getName() << std::endl;

		std::cout << std::setw(LINKESPALTE_W) << "FAHRZEUG" << std::setw(SEPERATOR_WIDTH) << ":" << std::right << std::endl;

		Fahrzeug::vKopf();
		std::cout << p_pFahrzeug << std::endl;

		std::unique_ptr<Fahrzeug> tempFzg = p_pWeg.pAbgabe(p_pFahrzeug);
		p_pWeg.getZielKreuzung()->vTanken(p_pFahrzeug);
		tempNewWeg->vAnnahme(std::move(tempFzg));
	}
}
