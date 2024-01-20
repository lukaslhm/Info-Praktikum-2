#pragma once

/**
 * Globale Definition der Größen für die Ausgabe. Dadurch können die Konstanten in allen Klassen verwendet werden und die Ausgabe ist einheitlich.
 */

#define SEPERATOR_WIDTH 3

// Simulationsobjekt
#define ID_WIDTH 3
#define NAME_WIDTH 10
#define SIMUOBJ_WIDTH (ID_WIDTH + SEPERATOR_WIDTH + NAME_WIDTH)

// Fahrzeug
#define MAX_VELO_WIDTH 18
#define GESAMTSTRECKE_WIDTH 13
#define GESCHWINDIGKEIT_WIDTH 15
#define GESAMTVERBRAUCH_WIDTH 15
#define TANKINHALT_WIDTH 10
#define FAHRZEUG_WIDTH (SIMUOBJ_WIDTH + MAX_VELO_WIDTH + GESAMTSTRECKE_WIDTH + GESCHWINDIGKEIT_WIDTH + GESAMTVERBRAUCH_WIDTH + TANKINHALT_WIDTH + 5 * SEPERATOR_WIDTH)

// Weg
#define LAENGE_WIDTH 8
#define FAHRZEUGLIST_WIDTH 22
#define WEG_WIDTH (SIMUOBJ_WIDTH + LAENGE_WIDTH + FAHRZEUGLIST_WIDTH + 2 * SEPERATOR_WIDTH)

// Streckenende
#define LINKESPALTE_W 10

// file input Constants
#define INTERSECTION "KREUZUNG"
#define STREET "STRASSE"
#define CAR "PKW"
#define BIKE "FAHRRAD"
