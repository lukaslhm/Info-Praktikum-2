#pragma once

#include "vertagt_aktion.h"
#include <list>
#include <memory>

namespace vertagt
{
	template <class T>
	class VListe
	{
	private:
		std::list<T> p_objekte;
		std::list<std::unique_ptr<VAktion<T>>> p_aktionen;

	public:
		// Typdefinitionen
		using iterator = typename std::list<T>::iterator;
		using const_iterator = typename std::list<T>::const_iterator;

		// Konstruktoren
		VListe() = default; //Als Standardkonstruktor wird der default genutzt
		// Destruktor
		~VListe()
		{
			vAktualisieren();
			p_objekte.clear();
		}

		void clear()
		{
			//Alle Objekte aus der Liste löschen
			vAktualisieren();
			p_objekte.clear();
		}

		// Lesefunktionen
		const_iterator begin() const
		{
			return p_objekte.begin();
		}
		const_iterator end() const
		{
			//Letztes Objekt aus der Liste als const iterator zurückgeben
			return p_objekte.end();
		}
		iterator begin()
		{
			return p_objekte.begin();
		}
		iterator end()
		{
			//Letztes Objekt aus der Liste als iterator zurückgeben
			return p_objekte.end();
		}
		bool empty() const
		{
			//Prüfen ob die Liste leer ist
			return p_objekte.empty();
		}

		// Schreibfunktionen
		void push_back(T obj)
		{
			// Aktionselement für PushBack auf Liste erzeugen
			p_aktionen.push_back(std::make_unique<VPushBack<T>>(p_objekte, std::move(obj))); //Unique pointer vom Typ PushBack mit Objekt erstellen um PushBack durchführen zu können
		}

		void push_front(T obj)
		{
			// Aktionselement für PushBack auf Liste erzeugen
			p_aktionen.push_back(std::make_unique<VPushFront<T>>(p_objekte, std::move(obj))); //Push back mit Pointer vom Typ PushFront ausführen, damit das Objekt vorne eingefügt wird
		}

		void erase(iterator it)
		{
			// Aktionselement für PushBack auf Liste erzeugen (hier Iterator statt Objekt !)
			p_aktionen.push_back(std::make_unique<VErase<T>>(p_objekte, it)); //Push back mit dem uniquePointer vom Typ Erase ausführen, um das Objekt aus der Liste zu löschen
		}

		// Änderungen auf Objektliste übertragen
		void vAktualisieren()
		{
			// Änderungen auf Objektliste übertragen
			for (auto& pAktion : p_aktionen)
			{
				// Aktion ausführen
				pAktion->vAusfuehren();
			}
			// Aktionsliste löschen
			p_aktionen.clear();
		}
	};
} // namespace vertagt
