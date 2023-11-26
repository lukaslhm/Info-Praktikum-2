#pragma once
#include "Fahrausnahme.h"
class Losfahren : public Fahrausnahme
{
public:
	Losfahren(Fahrzeug& initFzg, Weg& initWeg);
	~Losfahren();

	void vBearbeiten() override;
};

