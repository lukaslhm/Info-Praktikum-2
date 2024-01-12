#pragma once
#include "Fahrausnahme.h"
class Losfahren : public Fahrausnahme
{
public:
	///Konstruktor für die Ausnahme Losfahren
	Losfahren(Fahrzeug& initFzg, Weg& initWeg);
	///Destruktor
	~Losfahren();

	///Bearbeiten von dem Fahrzeug beim Aufruf der Ausnahme
	void vBearbeiten() override;
};

