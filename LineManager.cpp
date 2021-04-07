//
//  LineManager.cpp
//  Assignment3
//
//  Created by Temirlan Tolen  on 2021-04-04.
//
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <algorithm>
#include "LineManager.hpp"
#include "Utilities.h"

namespace sdds {
    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
    {
        
        std::ifstream strFile(file);
        std::string record;
        std::string firstColumn = "";
        std::string secondColumn = "";
        
        Utilities utility;
        size_t next_pos = 0u;
        bool more = true;
        
        if (!strFile)
            throw std::string("Cannot open file: ") + file + " file.";
        
        std::set <std::string> col1, col2, diff;
        
        while (!strFile.eof())
        {
            std::getline(strFile, record);
            if (!record.empty())
            {
                firstColumn = utility.extractToken(record, next_pos, more);
                //adding to col1 set for later comparison.
                col1.insert(firstColumn);
                if (more)
                {
                    secondColumn = utility.extractToken(record, next_pos, more);
                    //adding to col2 set for later comparison.
                    col2.insert(secondColumn);
                }
                else
                {
                    secondColumn = "";
                }
                
                for (size_t i = 0u; i < stations.size(); i++)
                {
                    if (stations[i]->getItemName() == firstColumn)
                    {
                        if(!secondColumn.empty())
                        {
                            for (size_t j = 0u; j < stations.size(); j++)
                            {
                                if (stations[j]->getItemName() == secondColumn && stations[j] != nullptr)
                                {
                                    stations[i]->setNextStation(stations[j]);
                                }
                            }
                        }
                    }
                }
                
            }
        }
        
        std::set_difference(col1.begin(), col1.end(), col2.begin(), col2.end(), std::inserter(diff, diff.end()));
        
        std::set <std::string>::iterator diffIter = diff.begin();
        std::string str = *diffIter;
        
        for(auto i = 0u; i < stations.size(); i++){
            if(stations[i]->getItemName() == str){
                m_firstStation = stations[i];
            }
        }
        
        // Pushing stations to activeLine obj.
        for (size_t i = 0u; i < stations.size(); i++)
        {
            activeLine.push_back(stations[i]);
        }
        
        m_cntCustomerOrder = pending.size();
    }

    void LineManager::linkStations()
    {
        Workstation* start = m_firstStation;
        std::vector<Workstation*> localActiveLine;
        
        while (start != nullptr){
            localActiveLine.push_back(start);
            start = (Workstation*)(start->getNextStation());
        }
        activeLine = localActiveLine;
        
    }

    bool LineManager::run(std::ostream& os)
    {
        static size_t track(1);
        os << "Line Manager Iteration: " << track << std::endl;
        track++;
        //bool check;
        
        if(!pending.empty()){
            
            *m_firstStation += std::move(pending.front());
            pending.pop_front();
        }
        for(auto i = 0; i < activeLine.size(); i++){
            activeLine[i]->fill(os);
        }
        
        return completed.size() == m_cntCustomerOrder;

    }

    void LineManager::display(std::ostream& os) const
    {
        for (std::size_t i = 0; i < activeLine.size(); ++i) {
                activeLine[i]->display(std::cout);
            }
    }
    
}
