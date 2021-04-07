//
//  Workstation.cpp
//  Assignment3
//
//  Created by Temirlan Tolen  on 2021-04-03.
//

#include "Workstation.hpp"

namespace sdds{
//Testing
std::deque<CustomerOrder> pending;
std::deque<CustomerOrder> completed;
std::deque<CustomerOrder> incomplete;
//Testing


Workstation::Workstation(const std::string& str): Station(str){ m_pNextStation = nullptr;}

    void Workstation::fill(std::ostream& os){
        if(!m_orders.empty()){
            attemptToMoveOrder();
            m_orders.front().fillItem(*this, os);
        }
    }

    bool Workstation::attemptToMoveOrder(){
        bool result = false;
        //--------------------------------
//        bool check = !m_orders.empty() && m_orders.front().isItemFilled(getItemName());
//        if(!check){
//            if(m_pNextStation->getQuantity() < 0){
//
//            }
//        }
//
//        if (check) {
//
//            if(m_pNextStation == nullptr){
//                completed.push_back(std::move(m_orders.front()));
//                result = true;
//            }
//            else{
//                *m_pNextStation += std::move(m_orders.front());
//                m_orders.pop_front();
//                result = true;
//            }
//
//        }
        //--------------------------------
        if(!m_orders.empty()){
            if( m_orders.front().isItemFilled(getItemName()) ){
                if(m_pNextStation == nullptr){
                    completed.push_back(std::move(m_orders.front()) );
                    result = true;
                }
                else{
                    *m_pNextStation += std::move(m_orders.front());
                    m_orders.pop_front();
                    result = true;
                }
            }
            else if(m_pNextStation->getQuantity() <= 0){
                if(m_pNextStation == nullptr){
                    incomplete.push_back(std::move(m_orders.front()) );
                    result = true;
                }
                else{
                    *m_pNextStation += std::move(m_orders.front());
                    m_orders.pop_front();
                    result = true;
                }
            }
        }
        
        return result;
    }

    void Workstation::setNextStation(Workstation* station){
        m_pNextStation = station;
        //std::cout << " T E S T I N G: " << m_pNextStation->getItemName() << std::endl;
    }

    const Workstation* Workstation::getNextStation() { return m_pNextStation; }

    void Workstation::display(std::ostream& os) const{
        if (m_pNextStation == nullptr)
            os << getItemName() << " --> END OF LINE" << std::endl;
        else
            os << getItemName() << " --> " << m_pNextStation->getItemName() << std::endl;
    }

    Workstation& Workstation::operator+=(CustomerOrder&& newOrder){
        m_orders.push_back(std::move(newOrder));

        return *this;
    }
}
