// Name: Temirlan Tolen
// Seneca Student ID: 104571187
// Seneca email: ttolen@myseneca.ca
// Date of completion: 01.04.2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"


namespace sdds {
	size_t Station::m_widthField = 0u;
	int Station::id_generator = 0; 

	Station::Station(const std::string& str) {
		Utilities utl;
		m_id = id_generator;
		size_t next_pos(0u);
		bool more = true;

		try {
			m_name = utl.extractToken(str, next_pos, more);
			m_serialNumber = std::stoul(utl.extractToken(str, next_pos, more));
			m_currentlyStock = std::stoul(utl.extractToken(str, next_pos, more));

			m_widthField = std::max(utl.getFieldWidth(), m_widthField);
			m_description = utl.extractToken(str, next_pos, more);
		}
		catch(std::string& msg){
			std::cout << msg;
		}
		id_generator++;
	}

	const std::string& Station::getItemName() const { return m_name; }

	size_t Station::getNextSerialNumber() {
        m_serialNumber++;
        return m_serialNumber-1;
    }

	size_t Station::getQuantity() const { return m_currentlyStock; }

	void Station::updateQuantity() {
		m_currentlyStock--;
		if (m_currentlyStock < 0u) m_currentlyStock = 0u;
	}

	void Station::display(std::ostream& os, bool full) const {
		os << "[" <<std::right << std::setw(3) << std::setfill('0') << m_id +1 << "]";
		os << " Item: " << std::left << std::setw(static_cast<int>(m_widthField)) << std::setfill(' ') << m_name;
		os << " [" << std::setw(6) <<std::right << std::setfill('0')<< m_serialNumber << "]";
		os << std::setfill(' ');
		if (full != false) {
			os << " Quantity: " << std::left << std::setw(static_cast<int>(m_widthField)) << m_currentlyStock << " Description: " << m_description << std::endl;
		}
		else { os << std::endl; }
	}
}
