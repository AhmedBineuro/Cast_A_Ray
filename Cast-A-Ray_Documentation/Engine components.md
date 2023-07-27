## Map Reader
- <b style="color:lightblue">Brief description</b>: A singleton class that is in charge of reading map files
- <b style="color:lightblue">Detailed description</b>:
	- The class will parse the map file into segments containing the tags and their contents _(see [[Cast-A-Ray Level File]] for information about tags)_ . The map reader will be deployed through the main thread and will read <b style="color:orange">one map at a time</b>.
	- The map reader should interact with the following classes
		- **Resource Manager**: should allow to export the resource list along with their names
		- **Map**: should allow to export layout information, color and texture mapping along with name information.
		- **Player**: should allow to export player spawn position and render distance
## Log
## Resource Manager
- <b style="color:lightblue">Brief description</b>: A singleton class that is in charge of loading and deleting resources
- <b style="color:lightblue">Detailed description</b>: The class will contain all the needed resources for the loaded map. The resource manager will take loading requests with a name and a URL and a set of flags and if the name already exists then we will assume it is already loaded. The resource manager will have 3 maps for each type of resource. The types of resources are: 1. Sounds 2.Textures and 3.Music. The resources will have a subscription system where if it has a subscription count of 0 it will automatically delete the item. To subscribe a map sends a loading request and the resource will be loaded if not already and an internal counter in the resource struct will containing an internal counter, and the actual resource. 