//
// Created by jasper on 1/7/22.
//

#ifndef PROJECT_2_ENTITYMANAGER_H
#define PROJECT_2_ENTITYMANAGER_H
#include <vector>
#include "Entity.h"
#include <map>
#include <string>
#include <memory>

typedef std::vector<std::shared_ptr<Entity>>     EntityVec;
typedef std::map   <std::string, EntityVec> EntityMap;
class EntityManager{
    EntityVec m_entities;
    EntityVec m_toAdd;
    EntityMap m_entityMap;
    size_t m_totalEntities = 0;
public:
    EntityManager();
    void update();
    std::shared_ptr<Entity> addEntity(const std::string& tag);
    EntityVec& getEntities();
    EntityVec& getEntities(const std::string& tag);
};


#endif //PROJECT_2_ENTITYMANAGER_H
