#pragma once

#include <list>
#include <string>
#include <iostream>
#include <memory>

#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include "vertagt_liste.h"

class Fahrzeug;
class Kreuzung;

class Weg : public Simulationsobjekt
{
public:
	///Default konstruktor
	Weg() = default;
	///Konstruktor mit Name, Länge und Tempolimit. Tempolimit ist als default unbegrenzt. Überholen ist als default true. Kreuzung an der die Straße endet
	Weg(std::string initName, double initLaenge, Tempolimit initTempolimit = Tempolimit::Autobahn, bool ueberholverbot = true, std::weak_ptr<Kreuzung> zielKreuzung = std::weak_ptr<Kreuzung>());
	///Destruktor
	~Weg();

	///Ausgabe des Tabellenkopfs für die Ausgabe der Wege als Liste im Terminal
	static void vKopf();

	///Simulieren vom Weg und den zugehörigen Fahrzeugen
	void vSimulieren() override;
	///Ausgabe vom Weg und den aktuellen Fahrzeugen
	void vAusgeben(std::ostream& out) const override;
	///Alle Fahrzeuge vom Weg ausgeben
	void vFahrzeugeAusgeben() const;

	///Neues Fahrzeug auf den Weg aufnehmen
	void vAnnahme(std::unique_ptr<Fahrzeug> fzg);
	///Neues parkendes Fahrzeug auf den Weg aufnehmen
	void vAnnahme(std::unique_ptr<Fahrzeug> fzg, double StartZeit);

	///Fahrzeug in der Liste der aktuellen Fahrzeuge suchen, löschen und zurückgeben
	std::unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug& fzg);

	void setVirtuelleSchranke(double newValue);

	void setRueckWeg(std::weak_ptr<Weg> rueckWeg);
	///Rückgabe des Tempolimits auf der Straße
	double getTempolimit() const;
	///Rückgabe von der Straßenlänge
	double getLaenge() const;

	///Virtuelle Schranke um bei Überholverboten die Position des vorherigen Fahrzeugs zu speichern
	double getVirtuelleSchranke() const;

	///Getterfunktion für die Kreuzung auf die der Weg endet
	std::shared_ptr<Kreuzung> getZielKreuzung() const;
	///Getterfunktion für den Rückweg der zu diesem Weg gehört
	std::shared_ptr<Weg> getRuckWeg() const;

private:
	///Eigenschaften vom Weg
	double p_dLaenge = 0;
	vertagt::VListe<std::unique_ptr<Fahrzeug>> p_pFahrzeuge;
	bool p_bUeberholverbot = true; //Standardmäßig ist überholen verboten
	Tempolimit p_eTempolimit = Tempolimit::Autobahn;
	double p_dVirtuelleSchranke = 0;

	//Rückweg der zu dem Weg gehört, weakpointer da es sich sonst um eine Ringreferenzierung handelt
	std::weak_ptr<Weg> p_pRueckWeg;
	//Kreuzung auf die der Weg endet, ändert sich nicht also const
	const std::weak_ptr<Kreuzung> p_pZielKreuzung = std::weak_ptr<Kreuzung>();

};

