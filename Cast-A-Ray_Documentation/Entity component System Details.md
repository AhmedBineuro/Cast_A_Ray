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