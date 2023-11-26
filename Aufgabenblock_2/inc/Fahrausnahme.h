#pragma once
#include <exception>

class Fahrzeug;
class Weg;

class Fahrausnahme : public std::exception
{
public:
	Fahrausnahme(Fahrzeug& initFzg, Weg& initWeg);
	virtual ~Fahrausnahme();

	virtual void vBearbeiten() = 0;

protected:
	Fahrzeug& p_pFahrzeug;
	Weg& p_pWeg;
};

