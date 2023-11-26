#include "Weg.h"
#include "Fahrzeug.h"
#include "AusgabeKonstanten.h"
#include "Fahrausnahme.h"

Weg::Weg(std::string initName, double initLaenge, Tempolimit initTempolimit)
	: Simulationsobjekt(initName), p_dLaenge(initLaenge), p_eTempolimit(initTempolimit)
{
}

Weg::~Weg()
{
}

void Weg::vKopf()
{
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

void Weg::vSimulieren()
{
	for (auto& it : p_pFahrzeuge)
	{
		try
		{
			it->vSimulieren();
		}
		catch (Fahrausnahme& ex)
		{
			ex.vBearbeiten();
		}
		it->vZeichnen(*this);
	}
}

void Weg::vAusgeben(std::ostream& out) const
{
	auto oldWidth = out.width();
	auto oldPrec = out.precision();

	Simulationsobjekt::vAusgeben(out);

	out << std::setw(SEPERATOR_WIDTH) << ' ';
	out << std::setw(LAENGE_WIDTH) << std::setprecision(2) << std::setiosflags(std::ios::fixed) << p_dLaenge;
	out << std::setw(SEPERATOR_WIDTH) << ' ';
	out << std::setw(1) << '(';
	int fahrzeugAmount = p_pFahrzeuge.size();
	for (auto& it : p_pFahrzeuge)
	{
		out << it->getName();
		if (--fahrzeugAmount > 0)
			out << std::setw(2) << ", ";
	}
	out << std::setw(1) << ')';

	out << std::setw(oldWidth) << std::setprecision(oldPrec);
}

void Weg::vFahrzeugeAusgeben() const
{
	Fahrzeug::vKopf();
	for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++)
	{
		std::cout << *it->get() << std::endl;
	}
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fzg)
{
	fzg->vNeueStrecke(*this);
	p_pFahrzeuge.push_back(move(fzg));
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fzg, double StartZeit)
{
	fzg->vNeueStrecke(*this, StartZeit);
	p_pFahrzeuge.push_front(move(fzg));
}

double Weg::getLaenge() const
{
	return p_dLaenge;
}

double Weg::getTempolimit() const
{
	return (double) p_eTempolimit;
}
