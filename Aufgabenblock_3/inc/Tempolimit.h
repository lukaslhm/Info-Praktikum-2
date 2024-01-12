#pragma once

#include <limits>

/**
 * Definition von Tempolimits für die unterschiedlichen Wegtypen
 */
enum class Tempolimit
{
	Innerorts = 50,                           /**< Innerorts: Die maximale Geschwindigkeit beträgt 50 km/h*/
	Landstrasse = 100,                        /**< Landstrasse: Die maximale Geschwindigkeit beträgt 100 km/h */
	Autobahn = std::numeric_limits<int>::max()/**< Autobahn: Auf der Autobahn ist keine Geschwindigkeitsbegrenzung */
};
