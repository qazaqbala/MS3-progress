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
#include "CustomerOrder.h"
#include "Utilities.h"
#include "Station.h"

namespace sdds {
	size_t CustomerOrder::m_widthField = 0u;

	CustomerOrder::CustomerOrder() {
		m_name = "";
		m_product = "";
		m_cntItem = 0u;
		m_lstItem = nullptr;
	}
	CustomerOrder::CustomerOrder(const std::string& str) {
		Utilities utl;
		size_t next_pos = 0u;
		bool more = true;

		m_cntItem = 0u;
		m_lstItem = nullptr;
		Item* lst[1000];

		try {
			m_name = utl.extractToken(str, next_pos, more);
			m_product = utl.extractToken(str, next_pos, more);

			while (more) {
				std::string item;
				item = utl.extractToken(str, next_pos, more);
				lst[m_cntItem] = new Item (item);
				m_cntItem++;
			}
			m_lstItem = new Item * [m_cntItem];
			for (size_t i = 0; i < m_cntItem; i++)
			{
				m_lstItem[i] = lst[i];
			}
			m_widthField = std::max(m_widthField, utl.getFieldWidth());
		}
		catch (std::string& err) { std::cout << err; }
	}
	
	CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept {
        m_name = other.m_name;
        m_product = other.m_product;
        m_cntItem = other.m_cntItem;

        m_lstItem = other.m_lstItem;
        
        other.m_name = "";
        other.m_product = "";
        other.m_cntItem = 0u;
        other.m_lstItem = nullptr;
        //*this = std::move(other);
        
	}
	CustomerOrder& CustomerOrder::operator= (CustomerOrder&& other) noexcept {
		if (&other == this)
			return *this;

		if (m_lstItem != nullptr) {
			for (auto i = 0u; i < m_cntItem; i++) {
				delete m_lstItem[i];
			}
		}
        delete [] m_lstItem;
		

		m_name = other.m_name;
		m_product = other.m_product;
		m_cntItem = other.m_cntItem;
		m_lstItem = other.m_lstItem;

		other.m_name = "";
		other.m_product = "";
		other.m_cntItem = 0u;
		other.m_lstItem = nullptr;

		return *this;
	}
	
	CustomerOrder::~CustomerOrder() {
		//if (m_lstItem == nullptr) return;
		for (auto i = 0u; i < m_cntItem; i++) {
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
	}
	bool CustomerOrder::isFilled() const {
		for (auto i = 0u; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_isFilled != true)
				return false;
		}
		return true;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
	
		for (auto i = 0u; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == itemName) {
				if(!m_lstItem[i]->m_isFilled)
                    return false;
			}
		}
		return true;
	}
	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		for (auto i = 0u; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == station.getItemName()) {
				if (station.getQuantity() > 0) {
					
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = 1;

					os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
				else
					os << "Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
			}
		}
	}
	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_product << std::endl;
		for (auto i = 0u; i < m_cntItem; i++) {
			os << "[" << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] "
				<< std::setfill(' ') << std::setw(static_cast<int>(m_widthField)) << m_lstItem[i]->m_itemName << " - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
		}
	}
}
