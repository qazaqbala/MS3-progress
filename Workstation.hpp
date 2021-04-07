//
//  Workstation.hpp
//  Assignment3
//
//  Created by Temirlan Tolen  on 2021-04-03.
//

#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

#include <iostream>
#include <deque>
#include <string>

//local file directives
#include "Station.h"
#include "CustomerOrder.h"

namespace sdds{

extern std::deque<CustomerOrder> pending;
extern std::deque<CustomerOrder> completed;
extern std::deque<CustomerOrder> incomplete;

class Workstation : public Station
{
private:
    std::deque<CustomerOrder> m_orders;
    Workstation* m_pNextStation;
public:
    Workstation(const std::string& str);
    void fill(std::ostream& os);
    bool attemptToMoveOrder();
    void setNextStation(Workstation* station);
    const Workstation* getNextStation();
    void display(std::ostream& os) const;
    Workstation& operator+=(CustomerOrder&& newOrder);
    
    Workstation(const Workstation& other) = delete;
    Workstation& operator=(const Workstation& other) = delete;
    Workstation(Workstation&& other) noexcept = delete;
    Workstation& operator=(Workstation&& other) noexcept = delete;
};
}
#endif /* SDDS_WORKSTATION_H */
