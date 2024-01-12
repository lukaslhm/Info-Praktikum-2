#pragma once
#include "Fahrausnahme.h"

class Streckenende : public Fahrausnahme
{
public:
	///Konstruktor für die Ausnahme Streckenende
	Streckenende(Fahrzeug& initFzg, Weg& initWeg);
	///Destruktor
	~Streckenende();

	///Funktion um das Verhalten vom Fahrzeug beim Auftreten der Ausnahme zu verändern
	void vBearbeiten() override;
};

