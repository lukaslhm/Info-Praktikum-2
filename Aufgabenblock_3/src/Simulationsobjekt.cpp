#include <Constants.h>
#include <stdexcept>

#include "Simulationsobjekt.h"


//Initialisierung der maximalen (nächsten) ID
int Simulationsobjekt::p_iMaxID = 0;

/**
 * Konstruktor für das Simulationsobjekt
 *
 * @param initName Name für das Simulationsobjekt, standardmäßig leer
 */
Simulationsobjekt::Simulationsobjekt(std::string initName)
	: p_sName(initName), p_dZeit(0), p_iID(p_iMaxID++)
{
	std::cout << "Simulationsobjekt erstellt: " << p_sName << " - " << p_iID << std::endl;
}

/**
 * Destruktor für das Simulationsobjekt
 */
Simulationsobjekt::~Simulationsobjekt()
{
	std::cout << "Simulationsobjekt gelöscht: " << p_sName << " - " << p_iID << std::endl;
}

/**
 * Ausgabefunktion für das Simulationsobjekt
 * Gibt ID und Name aus
 *
 * @param out Stream, in den die Ausgabe geschrieben werden soll
 */
void Simulationsobjekt::vAusgeben(std::ostream& out) const
{
	//Größe des Ausgabeterminals lesen, um die Ausgabe anzupassen
	auto oldWidth = out.width();
	auto oldPrec = out.precision();

	//Ausgabe
	out << std::setw(ID_WIDTH) << p_iID;
	out << std::setw(SEPERATOR_WIDTH) << ' ';
	out << std::setw(NAME_WIDTH) << std::setiosflags(std::ios::left) << p_sName << std::resetiosflags(std::ios::left);
	
	//Größe anpassen
	out << std::setw(oldWidth) << std::setprecision(oldPrec);
}

/**
 * Überladung des == Vergleichoperators, gibt true aus wenn die IDs der Objekte gleich sind. Sonst false.
 *
 * @param oprnd Simulationsobjekt mit dem aktuelles Objekt verglichen werden soll
 * @return Boolean, ob das übergebene Objekt die selbe ID hat
 */
bool Simulationsobjekt::operator==(const Simulationsobjekt& oprnd) const
{
	return p_iID == oprnd.p_iID;
}

/**
 * Ausgabe des Namen vom Simulationsobjekt
 *
 * @return Name des Simulationobjekts
 */
std::string Simulationsobjekt::getName() const
{
	return p_sName;
}

/**
 * Überladung des Ausgabeoperators
 *
 * @param out Ausgabestream in den die Ausgabe geladen werden soll
 * @param inst Simulationsobjekt, das ausgeben werden soll
 * @return Rückgabestream mit Ausgabe
 */
std::ostream& operator<<(std::ostream& out, const Simulationsobjekt& inst)
{
	inst.vAusgeben(out);
	return out;
}

void Simulationsobjekt::vEinlesen(std::istream &in)
{
	if (p_sName != "") throw std::runtime_error("Einleseobjekt nicht leer");
	in >> p_sName;
}

std::istream& operator>>(std::istream &in, Simulationsobjekt &inst)
{
	inst.vEinlesen(in);
	return in;
}
