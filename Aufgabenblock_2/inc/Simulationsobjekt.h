#pragma once

#include <string>
#include <iostream>
#include <iomanip>

class Simulationsobjekt
{
public:
	///Konstruktor
	Simulationsobjekt(std::string initName = "");

	///Löschen des Copy-Konstruktor
	Simulationsobjekt(const Simulationsobjekt&) = delete;

	///Destruktor
	virtual ~Simulationsobjekt();


	///Ausgabefunktion
	virtual void vAusgeben(std::ostream& out) const;
	///Simulationsfunktion, simuliert bis zur aktuellen Zeit. Rein virtuell
	virtual void vSimulieren() = 0;

	///Überladung des Vergleichoperators zum Vergleich der IDs
	bool operator==(const Simulationsobjekt& oprnd) const;

	///Ausgabefunktion für den Name des Simulationobjekts
	std::string getName() const;

protected:
	///Protected Variabeln die alle Simulationsobjekte besitzen
	double p_dZeit;
	std::string p_sName;
	int p_iID;

private:
	///Maximale ID, wird verwendet um doppelte IDs zu verhindern
	static int p_iMaxID;
};

///Überladung des Ausgabeoperators um Simulationsobjekte mit cout ausgeben zu können
std::ostream& operator<<(std::ostream& out, const Simulationsobjekt& inst);
