# Components
### Movable Component
- Velocity Vector (size 3)
- Friction
- Max Speed
- Acceleration Vector
### Controller Component
- Control Type
- Active State
- Control System ID (referencing the type of control scheme)
### Life Component
- Health
- Max Health
- Alive (boolean)
### Sprite Component
- Sprite Attribute
- Drawable (boolean)
### Collider Component (for 2D space)
- Rect (representing bounds)
### Raycasting Component
- Origin (point from where the raycasting starts)
- Direction (angle or vector indicating the direction)
- Range (distance the ray can travel)
- Raycast Type (e.g., vision, detection, etc.)
### Camera Component
- FOV (Field of View)
- Plane
- Raycast ID (referencing the type of raycasting)
### Logger Component
- Log Reference (to main log or linked log)
### Audio Emitter Component
- Audio Attributes (using SFML Sound classes)

### Audio Listener Component
- Listener Attributes (using SFML Listener classes)

### Music Component
- Music Attributes (using SFML Music classes)

### Map Association Component
- Map ID

### Trigger Component
- Shape (2D initially, future-proof for 3D)
- Trigger Type (e.g., collision, proximity)
