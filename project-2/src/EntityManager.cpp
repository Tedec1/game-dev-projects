//
// Created by jasper on 1/7/22.
//
#include "Entity.h"
#include "EntityManager.h"

std::shared_ptr<Entity> EntityManager::addEntity(const std::string &tag) {
    auto e = std::shared_ptr<Entity>(new Entity(tag, m_totalEntities++));
    m_toAdd.push_back(e);
    return e;
}

void EntityManager::update()
{
    auto it = m_entities.begin();
    while ((it != m_entities.end())) {
        if(!(*it)->isAlive()){
            m_entityMap[(*it)->tag()].erase(it);
            it = m_entities.erase(it);
        } else {
            it++;
        }
    }
    for (auto e: m_toAdd) {
        m_entities.push_back(e);
        m_entityMap[e->tag()].push_back(e);
    }
    m_toAdd.clear();
}