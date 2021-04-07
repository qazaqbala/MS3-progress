//
//  LineManager.hpp
//  Assignment3
//
//  Created by Temirlan Tolen  on 2021-04-04.
//

#ifndef LineManager_hpp
#define LineManager_hpp

#include <iostream>
#include <vector>
#include "Workstation.hpp"

namespace sdds {
class LineManager{
private:
    std::vector<Workstation*> activeLine;
    size_t m_cntCustomerOrder;
    Workstation* m_firstStation;
public:
    LineManager(const std::string& file, const std::vector<Workstation*>& stations);
    void linkStations();
    bool run(std::ostream& os);
    void display(std::ostream& os) const;
};
}

#endif /* LineManager_hpp */
