#include "Constants.h"
#include <limits>

#include "Weg.h"
#include "Fahrzeug.h"
#include "Fahrausnahme.h"
#include "Kreuzung.h"


/**
 * Konstruktor für den Weg
 *
 * @param initName Name vom Weg
 * @param initLaenge Länge vom Weg
 * @param initTempolimit Tempolimit auf dem Weg, default ist ungebrezt
 * @param ueberholverbot Dürfen Fahrzeuge auf dem Weg überholen, standardmäßig nicht
 * @param zielKreuzung
 */
Weg::Weg(std::string initName, double initLaenge, Tempolimit initTempolimit, bool ueberholverbot, std::weak_ptr<Kreuzung> zielKreuzung)
	: Simulationsobjekt(initName), p_dLaenge(initLaenge), p_bUeberholverbot(ueberholverbot), p_eTempolimit(initTempolimit), p_dVirtuelleSchranke(std::numeric_limits<double>::infinity()), p_pZielKreuzung(zielKreuzung)
{
}

/**
 * Destruktor für den Weg
 */
Weg::~Weg()
{
}

/**
 * Ausgabe des Listenkopfs für die Ausgabe der Eigenschaften vom Weg
 * Liste von ID, Name, Länge und Fahrzeuge auf dem Weg
 */
void Weg::vKopf()
{
	//Anpassen an die Größe vom Terminal
	auto oldWidth = std::cout.width();
	auto oldFill = std::cout.fill();

	std::cout << std::setiosflags(std::ios::left);

	std::cout << std::setw(ID_WIDTH) << "ID";
	std::cout << std::setw(SEPERATOR_WIDTH) << " | ";
	std::cout << std::setw(NAME_WIDTH) << "Name";
	std::cout << std::setw(SEPERATOR_WIDTH) << " | ";
	std::cout << std::setw(LAENGE_WIDTH) << "Laenge";
	std::cout << std::setw(SEPERATOR_WIDTH) << " | ";
	std::cout << std::setw(FAHRZEUGLIST_WIDTH) << "Fahrzeuge";
	std::cout << std::endl;
	std::cout << std::setfill('-') << std::setw(WEG_WIDTH) << '-';
	std::cout << std::endl;

	std::cout << std::resetiosflags(std::ios::left);
	std::cout << std::setw(oldWidth) << std::setfill(oldFill);
}

/**
 * Simulieren der Fahrzeuge die auf dem Weg sind
 */
void Weg::vSimulieren()
{
	//Alle Fahrzeuge simulieren
	if (p_bUeberholverbot) p_dVirtuelleSchranke = std::numeric_limits<double>::infinity(); // Wenn kein Überholverbot gilt, soll die Schranke unbegrenzt sein
	p_pFahrzeuge.vAktualisieren();
	for (auto& it : p_pFahrzeuge)
	{
		//Mit Try catch um Ausnahmen fangen zu können
		try
		{
			it->vSimulieren();
			it->vZeichnen(*this);
		}
		catch (Fahrausnahme& ex)
		{
			//Fangen von Ausnahmen (Exceptions)
			it->vZeichnen(*this);
			ex.vBearbeiten();
		}
	}
	p_pFahrzeuge.vAktualisieren();
}

/**
 * Ausgabe der Eigenschaften vom Weg
 * Ausgabe von ID, Name, Länge und Fahrzeuge auf dem Weg
 *
 * @param out Stream für die Ausgabe mit den Informationen
 */
void Weg::vAusgeben(std::ostream& out) const
{
	//Anpassen an Terminalgröße
	auto oldWidth = out.width();
	auto oldPrec = out.precision();

	Simulationsobjekt::vAusgeben(out);

	out << std::setw(SEPERATOR_WIDTH) << ' ';
	out << std::setw(LAENGE_WIDTH) << std::setprecision(2) << std::setiosflags(std::ios::fixed) << p_dLaenge;
	out << std::setw(SEPERATOR_WIDTH) << ' ';
	out << std::setw(1) << '(';
	for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++)
	{
		out << it->get()->getName() <<  ' ';
	}
	out << std::setw(1) << ')';

	out << std::setw(oldWidth) << std::setprecision(oldPrec);
}

/**
 * Alle Fahrzeuge auf dem Weg ausgeben
 */
void Weg::vFahrzeugeAusgeben() const
{
	Fahrzeug::vKopf();
	for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++)
	{
		std::cout << *it->get() << std::endl;
	}
}

/**
 * Fahrendes Fahrzeug zum Weg hinzufügen
 * @param fzg Fahrzeug was fährt
 */
void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fzg)
{
	fzg->vNeueStrecke(*this);
	p_pFahrzeuge.push_back(std::move(fzg));
}

/**
 * Parkendes Fahrzeug zum Weg hinzufügen
 *
 * @param fzg Parkendes Fahrzeug
 * @param StartZeit Startzeit vom Fahrzeug
 */
void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fzg, double StartZeit)
{
	fzg->vNeueStrecke(*this, StartZeit);
	p_pFahrzeuge.push_front(std::move(fzg));
}

/**
 * Rückgabe der Länge vom Weg
 *
 * @return Länge vom Weg
 */
double Weg::getLaenge() const
{
	return p_dLaenge;
}

/**
 * Rückgabe vom Tempolimit auf dem Weg
 *
 * @return Tempolimit auf dem Weg
 */
double Weg::getTempolimit() const
{
	return (double) p_eTempolimit;
}

/**
 * Suchen von Fahrzeug in der Liste, löschen und zurückgeben
 *
 * @param fzg Fahrzeug, was gesucht wird
 * @return Fahrzeug aus der Liste. Wenn nicht verhanden wird ein leerer Pointer zurückgegeben.
 */
std::unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug &fzg)
{
	for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++)
	{
		if (*it == nullptr) continue;
		if (*it->get() == fzg)
		{
			std::unique_ptr<Fahrzeug> tempFzg = std::move(*it);
			p_pFahrzeuge.erase(it);
			return tempFzg;
		}
	}
	return std::unique_ptr<Fahrzeug>();
}

/**
 * Setzen der virtuellen Schranke
 * @param newValue Wert auf den die Schranke gesetzt werden soll. An dem Wert ist ein Fahrzeug
 */
void Weg::setVirtuelleSchranke(double newValue)
{
	p_dVirtuelleSchranke = newValue;
}
/**
 * Setzen des Rückwegs der zu diesem Weg gehört
 * @param rueckWeg Pointer auf den Rückweg
 */
void Weg::setRueckWeg(std::weak_ptr<Weg> rueckWeg)
{
	p_pRueckWeg = rueckWeg;
}
/**
 * Rückgabe der virtuellen Schranke unter berücksichtigung ob ein Überholverbot gilt
 * @return Wert der nach den Regeln des Wegs gefahren werden darf
 */
double Weg::getVirtuelleSchranke() const
{
	if (p_bUeberholverbot) return p_dVirtuelleSchranke;
	else return std::numeric_limits<double>::infinity(); //Gilt kein überholverbot ist die Schranke unbegrenzt
}

/**
 * Getterfunktion für die Kreuzung auf der der Weg endet
 * @return Kreuzung auf der dieser Weg endet
 */
std::shared_ptr<Kreuzung> Weg::getZielKreuzung() const
{
	return p_pZielKreuzung.lock();
}

/**
 * Getterfunktion für den Rückweg der zu diesem Weg gehört
 * @return Zu dem Weg zugehöriger Rückweg
 */
std::shared_ptr<Weg> Weg::getRuckWeg() const
{
	return p_pRueckWeg.lock();
}
