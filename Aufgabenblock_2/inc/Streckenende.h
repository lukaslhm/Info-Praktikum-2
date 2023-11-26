#pragma once
#include "Fahrausnahme.h"

class Streckenende : public Fahrausnahme
{
public:
	Streckenende(Fahrzeug& initFzg, Weg& initWeg);
	~Streckenende();

	void vBearbeiten() override;
};

