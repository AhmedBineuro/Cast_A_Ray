# Entity-Component System (ECS) Components

## Table of Contents
1. [Transform Component](#transform-component)
2. [Sprite Component](#sprite-component)
3. [Render Component](#render-component)
4. [Camera Component](#camera-component)
5. [Collider Component](#collider-component)
6. [Audio Source Component](#audio-source-component)
7. [Audio Listener Component](#audio-listener-component)
8. [Entity Tag Component](#entity-tag-component)
9. [Actor Component](#actor-component)

## Components Table

| Component Name           | Data Stored                                         | Detailed Description                                             |
|--------------------------|-----------------------------------------------------|------------------------------------------------------------------|
| [Transform Component](#transform-component) | Two `sf::Vector2f`                                 | Holds rotation and position vectors for an entity.               |
| [Sprite Component](#sprite-component)       | `sf::Sprite`                                       | Contains the sprite representation for an entity.                |
| [Render Component](#render-component)       | `sf::RenderWindow`                                 | Handles rendering for an entity within a given window.           |
| [Camera Component](#camera-component)       | `int FOV`, `float render distance`, `sf::Vector2f plane`, `sf::VertexArray` | Manages the camera settings for rendering the scene from an entity's perspective. |
| [Collider Component](#collider-component)   | `sf::FloatRect`, `bool Solid`                      | Manages collision boundaries and solidity state for an entity.   |
| [Audio Source Component](#audio-source-component) | `shared_ptr<sf::Sound>`                          | Manages audio emission for an entity.                            |
| [Audio Listener Component](#audio-listener-component) | `sf::Listener`                               | Manages audio reception for an entity.                           |
| [Entity Tag Component](#entity-tag-component) | `std::string`                                     | Tags an entity with a string identifier.                         |
| [Actor Component](#actor-component)         | Lifecycle event methods                            | Defines a base class for entities with lifecycle events like `OnCreate`, `OnDestroy`, etc. |

---

## Detailed Descriptions

### Transform Component
**Detailed Description**: Manages the position and rotation for an entity.
**Data Stored**: 
- Two `sf::Vector2f` for position and rotation

### Sprite Component
**Detailed Description**: Contains the `sf::Sprite` for an entity.
**Data Stored**: 
- `sf::Sprite`

### Render Component
**Detailed Description**: Handles rendering of an entity within an `sf::RenderWindow`.
**Data Stored**: 
- `sf::RenderWindow`

### Camera Component
**Detailed Description**: Manages the camera settings for an entity, including field of view and render distance.
**Data Stored**: 
- `int FOV`
- `float render distance`
- `sf::Vector2f plane`
- `sf::VertexArray` for rays

### Collider Component
**Detailed Description**: Manages the collision boundaries for an entity and whether it is solid.
**Data Stored**: 
- `sf::FloatRect` for collision bounds
- `bool Solid` indicating if collisions are considered

### Audio Source Component
**Detailed Description**: Manages the audio that an entity emits.
**Data Stored**: 
- `shared_ptr<sf::Sound>`

### Audio Listener Component
**Detailed Description**: Manages the audio reception for an entity.
**Data Stored**: 
- `sf::Listener`

### Entity Tag Component
**Detailed Description**: A simple string tag to identify entities, which can be used for grouping or searching.
**Data Stored**: 
- `std::string` tag

### Actor Component
**Detailed Description**: A virtual base class for entities that defines common lifecycle events.
**Data Stored**: 
- Lifecycle event methods such as `OnCreate`, `OnDestroy`, `OnStart`, `OnUpdate`, `OnFixedUpdate`, `OnEnable`, `OnDisable`
