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
#include "Utilities.h"

namespace sdds {
	char Utilities::m_delimiter = ' ';

	void Utilities::setFieldWidth(size_t newWidth) { m_widthField = newWidth; }
	size_t Utilities::getFieldWidth() const { return m_widthField; }
	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
		std::string strl = "";
		size_t start_pos = next_pos;
		next_pos = str.find(m_delimiter, start_pos);
		if (next_pos == std::string::npos) {
			strl = str.substr(start_pos);
			m_widthField = std::max(m_widthField, strl.length());
			more = false;
		}
		else if (start_pos == next_pos) {
			more = false;
			throw "Delimeter not found, next_pos is incorrect!";
		}
		else {
			strl = str.substr(start_pos, next_pos - start_pos);
			m_widthField = std::max(m_widthField, strl.length());
			more = true;
		}
		next_pos++;

		return strl;
	}

	void Utilities::setDelimiter(char newDelimiter) { m_delimiter = newDelimiter; }
	char Utilities::getDelimiter() { return m_delimiter; }
}
