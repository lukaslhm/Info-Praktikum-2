#include "Fahrrad.h"
#include "Weg.h"
#include "SimuClient.h"

/**
 * Kostruktor ohne Eigenschaften
 */
Fahrrad::Fahrrad()
 : Fahrzeug()
{
}

/**
 * Konstruktor mit Name und maximaler Geschwindigkeit
 *
 * @param initName Name für das Fahrrad
 * @param initMaxVelo Maximale Geschwindigkeit des Fahrrads
 */
Fahrrad::Fahrrad(std::string initName, double initMaxVelo)
	: Fahrzeug(initName, initMaxVelo)
{
}

/**
 * Destruktor für das Fahrrad
 */
Fahrrad::~Fahrrad()
{
}

/**
 * Ausgabe der aktuellen Geschwindigkeit vom Fahrrad.
 * Die Geschwindigkeit nimmt alle 20km um 10% ab. Minimal ist die Geschwindigkeit 12km/h
 *
 * @return aktuelle Geschwindigkeit des Fahrrads
 */
double Fahrrad::dGeschwindigkeit() const
{
	//Das Fahrrad soll minimal nur 12 km/h fahren. Falls die Maximale Geschwindigkeit kleiner ist werden 12 km/h zurückgegeben.
	if (p_dMaxGeschwindigkeit < 12) return p_dMaxGeschwindigkeit;

	//Errechnen der Geschwindigkeitsabnahme
	double result = p_dMaxGeschwindigkeit * std::pow(0.9, p_dGesamtStrecke/20);

	//Prüfen, ob das Fahrrad noch schneller als 12 km/h ist.
	if (result < 12) return 12;
	else return result;
}

/**
 * Ausgabefunktion, verwendet die Ausgabe der Oberklasse
 *
 * @param out Stream, in den die Ausgabe geladen werden soll
 */
void Fahrrad::vAusgeben(std::ostream& out) const
{
	Fahrzeug::vAusgeben(out);
}

/**
 * Zeichenfunktion, um das Fahrrad auf der GUI anzuzeigen
 *
 * @param weg Weg auf dem sich das Fahrrad aktuell befindet
 */
void Fahrrad::vZeichnen(const Weg &weg)
{
	bZeichneFahrrad(getName(), weg.getName(), (double) p_dAbschnittStrecke / weg.getLaenge(), dGeschwindigkeit());
}
