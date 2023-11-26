#include "Simulationsobjekt.h"
#include "AusgabeKonstanten.h"

int Simulationsobjekt::p_iMaxID = 0;

Simulationsobjekt::Simulationsobjekt(std::string initName)
	: p_sName(initName), p_iID(p_iMaxID++), p_dZeit(0)
{
	std::cout << "Simulationsobjekt generated: " << p_sName << " - " << p_iID << std::endl;
}

Simulationsobjekt::~Simulationsobjekt()
{
	std::cout << "Simulationsobjekt deleted: " << p_sName << " - " << p_iID << std::endl;
}

void Simulationsobjekt::vAusgeben(std::ostream& out) const
{
	auto oldWidth = out.width();
	auto oldPrec = out.precision();

	out << std::setw(ID_WIDTH) << p_iID;
	out << std::setw(SEPERATOR_WIDTH) << ' ';
	out << std::setw(NAME_WIDTH) << std::setiosflags(std::ios::left) << p_sName << std::resetiosflags(std::ios::left);
	
	out << std::setw(oldWidth) << std::setprecision(oldPrec);
}

bool Simulationsobjekt::operator==(const Simulationsobjekt& oprnd) const
{
	return p_iID == oprnd.p_iID;
}

std::string Simulationsobjekt::getName()
{
	return p_sName;
}

std::ostream& operator<<(std::ostream& out, const Simulationsobjekt& inst)
{
	inst.vAusgeben(out);
	return out;
}
