# Entity-Component System (ECS) Components

## Table of Contents
1. [animator_component](#animator_component)
2. [audio_emitter_component](#audio_emitter_component)
3. [audio_listener_component](#audio_listener_component)
4. [collider_component](#collider_component)
5. [drawable_component](#drawable_component)
6. [entity_id_component](#entity_id_component)
7. [input_component](#input_component)
8. [life_component](#life_component)
9. [logger_component](#logger_component)
10. [map_tag_component](#map_tag_component)
11. [move_component](#move_component)
12. [perspective_component](#perspective_component)
13. [player_id_component](#player_id_component)
14. [position_component](#position_component)
15. [sprite_component](#sprite_component)
## Components Table

| Component Name | Data Stored | Detailed Description |
|:--------------:|:-----------:|:--------------------:|
| [animator_component](#animator_component) | `sf::Rect`, `sf::Vector2i`, `sf::Vector2i` | Manages the animation for an entity's sprite. Holds information for sprite sheet dimensions, and the current frame index. |
| [audio_emitter_component](#audio_emitter_component) | Shared pointer to `sf::Sound`, `bool`, `bool` | Manages audio emission for an entity. Holds information for the sound to be played, and flags to indicate whether it's an active emitter or has spatial audio. |
| [audio_listener_component](#audio_listener_component) | `sf::Listener` | Holds an `sf::Listener` for an entity to manage audio listening capabilities. |
| [collider_component](#collider_component) | `sf::Rect`, Shared pointer to `sf::Sprite` | Manages collision for an entity. Holds a rectangle for basic collision and a shared pointer to a sprite for more precise collision detection. |
| [drawable_component](#drawable_component) | Reference to `sf::RenderTarget`, Reference to `sf::RenderStates` | Holds references to an `sf::RenderTarget` and `sf::RenderStates` for an entity, simplifying the rendering process by specifying where and how to draw the entity. |
| [entity_id_component](#entity_id_component) | `int` | Holds a unique ID for an entity to uniquely identify it. |
| [input_component](#input_component) | Reference to `sf::RenderWindow`, `bool` | Manages input functionalities for an entity, including keyboard and mouse inputs. |
| [life_component](#life_component) | `int`, `int` | Manages life or health-related information for an entity. Holds information for max and current health. |
| [logger_component](#logger_component) | `std::vector<Message>`, `int` | Manages logging functionalities for an entity. Holds a log ID and a vector of log messages. |
|[map_tag_component](https://chat.openai.com/c/29b872f5-c994-4cb7-9cb0-fc8d231eac1e#map_tag_component)|`std::string`, `int`|Tags an entity with a map identifier and map level.|
| [move_component](#move_component) | `sf::Vector3f`, `sf::Vector3f`, `float`,`float` | Manages the movement for an entity. Includes velocity, acceleration, and friction information. |
| [perspective_component](#perspective_component) | `sf::Vector3f`, `int`, `float`, `sf::Vector2f`, `sf::VertexArray` | Manages the 3D perspective rendering settings for an entity. Includes direction ray, field of view (FOV), maximum view distance, and plane vector for DDA rendering. The plane vector width can be calculated using the formula: planeWidth = tan(FOV / 2). |
| [player_id_component](#player_id_component) | `int` | Holds a unique ID for a player to uniquely identify them among other players. |
| [position_component](#position_component) | `sf::Vector3f`, `sf::Vector3i` | Manages the position for an entity. Includes literal position and grid position information. |
| [sprite_component](#sprite_component) | `sf::Sprite` | Holds an `sf::Sprite` for an entity. |


# Game Component Systems

### Movement System
- Processes the `Movable Component` to handle physics and movement logic.
- Applies friction, acceleration, and ensures objects stay within max speed.
### Control System
- Processes the `Controller Component` to manage input controls and AI behavior.
- Can switch between different control schemes.
### Life System
- Processes the `Life Component` to handle health and alive status.
- Manages damage, healing, and death events.
### Rendering System
- Processes the `Sprite Component` and `Camera Component` to render objects.
- Handles drawing logic, including visibility checks.
### Collision System
- Processes the `Collider Component` to manage collisions between objects.
- Handles collision responses, such as bouncing or sticking.
### Raycasting System
- Processes the `Raycasting Component` to perform raycasting operations.
- Used for vision, detection, or other line-of-sight calculations.
### Logging System
- Processes the `Logger Component` to log messages, warnings, or errors.
- Formats and displays log entries as needed.
### Audio System
- Processes the `Audio Emitter Component`, `Audio Listener Component`, and `Music Component` to manage sound effects and music.
- Handles audio playback, volume, and positioning.
### Map Association System
- Processes the `Map Association Component` to link objects to specific maps.
- Handles loading and unloading of map-related data.
### Trigger System
- Processes the `Trigger Component` to detect and respond to trigger events.
- Can initiate events like opening doors, starting cutscenes, etc.
---
## Detailed Descriptions

---

## animator_component
**Detailed Description**: Manages the animation for an entity's sprite. Holds information for sprite sheet dimensions, and the current frame index.

**Data Stored**: 
- `sf::Rect` for the source rectangle
- `sf::Vector2i` for current frame index
- `sf::Vector2i` for max dimensions (rows and columns)

---

## audio_emitter_component
**Detailed Description**: Manages audio emission for an entity. Holds information for the sound to be played, and a flag to indicate whether it's an active emitter or not. 

**Data Stored**: 
- Shared pointer to `sf::Sound`
- `bool` for active state
- `bool` for spatial audio

---

## audio_listener_component
**Detailed Description**: Holds an `sf::Listener` for an entity to manage audio listening capabilities.

**Data Stored**: 
- `sf::Listener`

---

## collider_component
**Detailed Description**: Manages collision for an entity. Holds a rectangle for basic collision and a shared pointer to a sprite for more precise collision detection.

**Data Stored**: 
- `sf::Rect` for collision bounds
- Shared pointer to `sf::Sprite`

---

## drawable_component
**Detailed Description**: Holds references to an `sf::RenderTarget` and `sf::RenderStates` for an entity, simplifying the rendering process by specifying where and how to draw the entity.

**Data Stored**: 
- Reference to `sf::RenderTarget`
- Reference to `sf::RenderStates`

---

## entity_id_component
**Detailed Description**: Holds a unique ID for an entity to uniquely identify it.

**Data Stored**: 
- `int` for Entity ID

---

## input_component
**Detailed Description**: Provides a reference to an `sf::RenderWindow` object and a boolean flag indicating if the input component is active or not. This allows the game developer to handle inputs directly.
**Data Stored**:

- Reference to `sf::RenderWindow`
- `bool` for `isActive`

---

## life_component
**Detailed Description**: Manages life or health-related information for an entity.

**Data Stored**: 
- `int` for max health
- `int` for current health

---

## logger_component
**Detailed Description**: Manages logging functionalities for an entity.

**Data Stored**: 
- `std::vector<Message>` for log messages
- `int` for log ID

---
## map_tag_component

**Detailed Description**: Tags an entity with a map identifier and map level. Useful for categorizing entities based on the map they are associated with.

**Data Stored**:

- `std::string` for map identifier
- `int` for map level

---
## move_component
**Detailed Description**: Manages the movement for an entity, includes velocity, acceleration, and friction information. The position of the entity can be updated using the formula:
\[ \text{New Position} = \text{Old Position} + (\text{Velocity} + 0.5 \times \text{Acceleration} \times \text{Delta Time}^2) \times \text{Delta Time} - \text{Friction} \times \text{Delta Time} \]

**Data Stored**: 
- `sf::Vector3f` for velocity
- `sf::Vector3f` for acceleration
- `float` for friction
- `float` for max speed

---

## perspective_component
**Detailed Description**: Manages the 3D perspective rendering settings for an entity. Includes direction ray, field of view (FOV), maximum view distance, and plane vector for DDA rendering. The plane vector width can be calculated using the formula: planeWidth = tan(FOV / 2).

**Data Stored**: 
- `sf::Vector3f` for direction ray
- `int` for FOV
- `float` for max view distance
- `sf::Vector2f` for plane vector
- `sf::VertexArray` for ray vertices

---

## player_id_component
**Detailed Description**: Holds a unique ID for a player to uniquely identify them among other players.

**Data Stored**: 
- `int` for Player ID

---

## position_component
**Detailed Description**: Manages the position for an entity, includes literal position and grid position information.

**Data Stored**: 
- `sf::Vector3f` for literal position
- `sf::Vector3i` for grid position

---

## sprite_component
**Detailed Description**: Holds an `sf::Sprite` for an entity.

**Data Stored**: 
- `sf::Sprite`

---
