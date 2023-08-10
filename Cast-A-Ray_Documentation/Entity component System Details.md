# Components
### Movable Component
- **Velocity Vector** (size 3): Determines the object's speed and direction.
- **Friction**: Affects how quickly the object slows down.
- **Max Speed**: Limits the object's speed.
- **Acceleration Vector**: Determines the object's rate of change of velocity.
### Controller Component
- **Control Type**: Defines the method of control (e.g., AI, player, etc.).
- **Active State**: Whether the control is currently active.
- **Control System ID**: Reference to the specific control scheme used.
### Life Component
- **Health**: Current health points.
- **Max Health**: Maximum health points.
- **Alive** (boolean): Indicates if the object is alive.

### Sprite Component
- **Sprite Attribute**: Visual representation.
- **Drawable** (boolean): Whether the object is currently drawn.
### Collider Component (for 2D space)
- **Rect**: Represents the object's bounds for collision detection.
### Raycasting Component
- **Origin**: Point from where the raycasting starts.
- **Direction**: Angle or vector indicating the direction.
- **Range**: Distance the ray can travel.
- **Raycast Type**: The purpose of the raycast (e.g., vision, detection, etc.).
### Camera Component
- **FOV** (Field of View): The viewable area.
- **Plane**: Used for rendering.
- **Raycast ID**: Reference to the specific raycasting type.
### Logger Component
- **Log Reference**: Link to the main log or specific linked log for error reporting.
### Audio Emitter Component
- **Audio Attributes**: Controls audio output using SFML Sound classes.
### Audio Listener Component
- **Listener Attributes**: Receives audio using SFML Listener classes.
### Music Component
- **Music Attributes**: Manages music playback using SFML Music classes.
### Map Association Component
- **Map ID**: Associates the object with a specific map.
### Trigg er Component
- **Shape**: Defines the shape (2D initially, future-proof for 3D).
- **Trigger Type**: Determines the trigger's purpose (e.g., collision, proximity).
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