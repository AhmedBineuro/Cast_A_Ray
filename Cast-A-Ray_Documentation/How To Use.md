- **Handy Shortcuts:**
	- ECS: Entity Component System
# What we will interact and modify
- `Entity.h`
	- Inherit from it to have the basic entity functions to interact with the ECS
- `Components.h`
	- Define structs that will behave as components for the ECS
- `Scene.h`
	- Inherit from it to have a basic structure of a Scene with a registry for ECS interactions and lifecycle methods _(like `onCreate()`,`onUpdate()`,and `onFixedUpdate()`)_ to be called by the **_Application_** class
- `Application.h`
	- Mostly adding and switching scenes but it is not outlandish to inherit and call super functions
	- Basically manages the Scenes it contains _(a vector of Scene pointers)_ and provides basic lifecycle method calling for the scenes
- `main.cpp`
	- Where you will call the _Application_ type object to run it