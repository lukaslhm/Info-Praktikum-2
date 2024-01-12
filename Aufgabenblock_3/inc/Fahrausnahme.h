#pragma once
#include <exception>

class Fahrzeug;
class Weg;

class Fahrausnahme : public std::exception
{
public:
	///Konstruktor für Fahrausnahmen (Exceptions)
	Fahrausnahme(Fahrzeug& initFzg, Weg& initWeg);
	///Destruktor
	virtual ~Fahrausnahme();

	///Bearbeitet das Fahrzeug bei auftreten der Ausnahme, rein virtuell
	virtual void vBearbeiten() = 0;

protected:
	Fahrzeug& p_pFahrzeug;
	Weg& p_pWeg;
};

