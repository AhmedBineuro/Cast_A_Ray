#include "Entity.h"
Entity::Entity() {
    Entity_Manager& em = Entity_Manager::getEntityManager();
    registry = em.getRegistry();
    handle = registry->create();
}