#pragma once

#include <list>

namespace vertagt
{
	// Oberklasse VAktion
	template <class T>
	class VAktion
	{
	protected:
		std::list<T>& p_pListe;  // Zeiger auf Liste der Objekte

	public:
		//Es wird kein Standardkonstruktor benötigt
		VAktion(std::list<T>& ptListe) : p_pListe(ptListe){}
		virtual ~VAktion() = default;
		virtual void vAusfuehren() = 0;
	};

	// PushBack
	template <class T>
	class VPushBack : public VAktion<T>
	{
	private:
		T p_objekt;

	public:
		VPushBack(std::list<T>& liste, T obj) : VAktion<T>(liste), p_objekt(std::move(obj))	{}
		virtual ~VPushBack() = default;
		void vAusfuehren() override
		{
			VAktion<T>::p_pListe.push_back(std::move(p_objekt));
		}
	};

	// PushFront
	template<class T>
	class VPushFront: public VAktion<T>
	{
	public:
		//Konstruktor mit Liste und Objekt das hinzugefügt werden soll
		VPushFront(std::list<T>& liste, T obj): VAktion<T>(liste), p_objekt(std::move(obj)) {}
		//Destruktor
		virtual ~VPushFront() = default;

		//Ausführen der vPushFront Aktion
		void vAusfuehren() override
		{
			//Objekt vorne in der Liste einfügen
			VAktion<T>::p_pListe.push_front(std::move(p_objekt));
		}

	private:
		T p_objekt;
	};

	// Erase
	template <class T>
	class VErase : public VAktion<T>
	{
	public:
		using iterator = typename std::list<T>::iterator;

	private:
		iterator p_it;  // bei erase Iterator speichern

	public:
		//Konstruktor um ein Element aus der Liste zu Löschen
		VErase(std::list<T>& liste, typename std::list<T>::iterator it) : VAktion<T>(liste), p_it(it) {}
		virtual ~VErase() = default;
		void vAusfuehren() override
		{
			//Das im Iterator übergebene Objekt aus der Liste löschen
			VAktion<T>::p_pListe.erase(p_it);
		}
	};
}  // namespace vertagt
