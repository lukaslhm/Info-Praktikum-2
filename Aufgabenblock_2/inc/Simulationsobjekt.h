#pragma once

#include <string>
#include <iostream>
#include <iomanip>

class Simulationsobjekt
{
public:
	Simulationsobjekt(std::string initName = "");
	Simulationsobjekt(const Simulationsobjekt&) = delete;
	virtual ~Simulationsobjekt();

	virtual void vAusgeben(std::ostream& out) const;
	virtual void vSimulieren() = 0;

	bool operator==(const Simulationsobjekt& oprnd) const;

	std::string getName();

protected:
	double p_dZeit;
	std::string p_sName;
	int p_iID;

private:
	static int p_iMaxID;
};

std::ostream& operator<<(std::ostream& out, const Simulationsobjekt& inst);