//
// Created by jasper on 1/7/22.
//
#include <string>
#ifndef PROJECT_2_ENTITY_H
#define PROJECT_2_ENTITY_H


class Entity {
    const size_t      m_id    = 0;
    const std::string m_tag   = "Default";
    bool              m_alive = true;
    Entity(const std::string& tag, size_t id):
            m_id(id),
            m_tag(tag)
    {}
public:
    friend class EntityManager;
//    std::shared_ptr<CTransform> cTransform;
//    std::shared_ptr<CName>      cName;
//    std::shared_ptr<CShape>     cShape;
//    std::shared_ptr<CBBox>      cBBox;
    const std::string& tag()    { return m_tag; };
    bool isAlive()              { return m_alive; };
    void destroy()              { m_alive = false; };
};


#endif //PROJECT_2_ENTITY_H
