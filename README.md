# Cast-A-Ray Engine

## Table of Contents

1. [What is it?](#what-is-it)
2. [Current State](#current-state)
3. [Project plans and goals](#project-plans-and-goals)
4. [Known bugs](#known-bugs)
5. [Libraries used](#libraries-used)
6. [Current todo's](#curren-todos)

---

## What is it?

- Cast-A-Ray is a game engine built to create games that utilize a [DDA renderer](https://en.wikipedia.org/wiki/Ray_casting) similar to how [Wolfenstein 3D](https://en.wikipedia.org/wiki/Wolfenstein_3D). The engine hopes to integrate the classical rendering style in a more modern setting and give it capabilities that similar to a modern game engine. The project is currently maintained by one person and that is me but hopefully in the future I will get some assisstance developing and refining  the engine.
- Future engine updates will be uploaded over on [YouTube](https://www.youtube.com/channel/UCXIKU9kHYKOm27ZqwLc2n7w) and hopefully they will be less sparse than before.  

## Current State

- First off before we talk about the engine itself I have to give a huge warning **THE DOCUMENTATION IN THE REPO IS VERY OUT OF DATE DO NOT CONSULT AT ALL** and now that _that_ is out of the way we can talk about the engine!

- The engine currently has a simple editor and viewport interface that allows the user to dynamically create, edit, and delete entities and their components. Speaking of which, the engine exposes an entity component system through a simple `Entity` class that allows the user to create very flexible entities and tweak them easily. Moving on to the viewport, the viewport currently showcases a scene's 'main' texture which can be selected in the interface.

- Currently the renderer is able to draw textured walls, floors, and ceilings. Additionally the player is not bound by the  borders of the maps, they can simply step outside and the renderer will continue rendering allowing the player to see the map from the outside. The current engine performance leaves alot to be desired but that is mainly due to the fact that the engine currently load each texture separately and not just a texture atlas. 

## Project plans and goals

- The main goal of the project is to spruce up and revive the rendering style in a package that is ready for modern use.
- Some future plans for the engine include
  - [ ] Vertical movement and 3D collision detection
  - [ ] Runtime environment
  - [ ] Serialization for editor and runtime programs
  - [ ] External scripting using Lua or Python
  - [ ] Dynamic and static lighting
  - [ ] In engine map editor
  - [ ] Scene and map transitions
  - [ ] Post processing effects and shaders
  - [ ] Hardware accelerated version
## Known bugs
- Currently there is a bug I have only encountered on one computer and that is my laptop where the program runs perfectly but the window is blank and white. Why is that? I don't know but for some reason if I copy the texture into an image (I don't use or touch in any way) after I draw it, it gets fixed. So yeah definitly need investigation
- There is also a collision bug cause by faulty collision detection code but at the moment it is not at the top of my list since it is working well enough at the moment.  
## Libraries used
- For multimedia and graphics: [SFML](https://www.sfml-dev.org/)
  - With a personally modified version of [SFML Math](https://github.com/wagnrd/SFMLMath) library   
- For GUI: [ImGui](https://github.com/ocornut/imgui)
  - Additions:
    - [SFML ImGui Backend](https://github.com/SFML/imgui-sfml)
    - [ImGui Knobs](https://github.com/altschuler/imgui-knobs)
    - [ImGui Text editor](https://github.com/BalazsJako/ImGuiColorTextEdit) (Very bugged at the moment)
- For the entity component system: [EnTT](https://github.com/skypjack/entt)
## Current todo's
- [ ] Implement billboard sprites
- [ ] Implement 360 sprite
- [ ] Implement skybox
- [ ] Update Documentation (It is severely out of date)
- [ ] Add pictures, videos, and gifs of the engine here!
