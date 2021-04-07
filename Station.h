// Name: Temirlan Tolen
// Seneca Student ID: 104571187
// Seneca email: ttolen@myseneca.ca
// Date of completion: 01.04.2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <string>

namespace sdds {
	class Station
	{
	private:
		int m_id;
		std::string m_name;
		std::string m_description;
		size_t m_serialNumber;
		size_t m_currentlyStock;
		static size_t m_widthField;
		static int id_generator;
	public:
		Station(const std::string&);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}

#endif // !SDDS_STATION_H


