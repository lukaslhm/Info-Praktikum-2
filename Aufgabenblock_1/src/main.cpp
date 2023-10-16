#include <vector>
#include <memory>

#include "Fahrzeug.h"

void vAufgabe_1()
{
	Fahrzeug F1;
	Fahrzeug* F2 = new Fahrzeug("PKW");
	delete F2; // destruction of F2

	std::unique_ptr<Fahrzeug> p1 = std::make_unique<Fahrzeug>();
	std::unique_ptr<Fahrzeug> p2 = std::make_unique<Fahrzeug>("PKW");
	std::shared_ptr<Fahrzeug> p3 = std::make_shared<Fahrzeug>();
	std::shared_ptr<Fahrzeug> p4 = std::make_shared<Fahrzeug>("PKW");

	std::cout << "p3.use_count: " << p3.use_count() << std::endl;
	std::shared_ptr<std::shared_ptr<Fahrzeug>> p5 = std::make_shared<std::shared_ptr<Fahrzeug>>(p3);
	std::cout << "p3.use_count: " << p3.use_count() << std::endl;

	std::cout << std::endl << "Vector: " << std::endl;

	std::vector<std::unique_ptr<Fahrzeug>> vec;

	vec.push_back(move(p1));
	vec.push_back(move(p2));

	vec.clear(); //destruct p1, p2

	std::cout << std::endl << "2nd Vector" << std::endl;

	std::cout << "use_counts: " << "p3: " << p3.use_count() << " p4: " << p4.use_count() << std::endl;

	std::vector<std::shared_ptr<Fahrzeug>> vec2;
	vec2.push_back(p3);
	vec2.push_back(move(p4));

	std::cout << "use_counts: " << "p3: " << vec2.at(0).use_count() << " p4: " << vec2.at(1).use_count() << std::endl;

	std::cout << std::endl << "Finish function" << std::endl;
} // destruction of everything else

int main()
{
	vAufgabe_1();
	return 0;
}
