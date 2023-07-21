## Syntax
### Tag and comment
```
/This is how you comment
/The spaces are required in tag declarations for optimal safety
# Tag Name :
#
/The closing tag needs to be on a new line or you can chain them like this
# Tag1 :
# Tag2 :
#
/Here the opening tag for Tag2 is the closing tag for Tag1
```
- A tag is a container for map information
- Each tag has attributes and values
### Attributes and attribute assignment
```
/An attribute-value pair looks like this
attribute:value
/Sometimes attributes have multiple values like this
atrribute:value1,value2,value3
```
- Attributes represent the data for each tag
	- _For Example the wall tiles tag takes one attribute-value pair for each tile type and it will look something like this `1:special Name`_ 
- <b style="color:red;">IMPORTANT</b> you <b style="color:red;">CANNOT</b> have spaces around the ':' with the attribute value pair 
## Tags  And their contents
 - `width` :tile width. See [[#Single value tags]]
 - `height` :tile height. See [[#Single value tags]]
 - `floor layout` :the floor layout array. See [[#Layout tags]]
 - `wall layout` :the wall layout array. See [[#Layout tags]]
 - `ceiling layout` :the ceiling layout array. See [[#Layout tags]]
 - `wall tiles` :the name of the wall tiles with a given index. See [[#Tile name mapping tags]]
 - `floor tiles` :the name of the floor tiles with a given index. See [[#Tile name mapping tags]]
 - `ceiling tiles` :the name of the ceiling tiles with a given index. See [[#Tile name mapping tags]]
 - `textures` :a list of all necessary images to load _(Used for resource manager)_. See [[#Resource tags]]
 - `sounds` :a list of all necessary sounds to load _(Used for resource manager)_. See [[#Resource tags]]
 - `debug colors` :the color of the tile on the debug mini-map _(the tiles referred to here are the wall tiles)_. See [[#Tile-resource mapping tags]]
 - `wall textures` :the texture mapping to wall tiles _(Attributes and values are referred to by name and not by index)_. See [[#Tile-resource mapping tags]]
 - `floor textures` :the texture mapping to floor tiles _(Attributes and values are referred to by name and not by index)_. See [[#Tile-resource mapping tags]]
 - `ceiling textures` :the texture mapping to ceiling tiles _(Attributes and values are referred to by name and not by index)_. See [[#Tile-resource mapping tags]]
## Special tag inputs
### Single value tags
- The single input tags are `width` and `height`
- The input is just a numerical value
```
/Example
# width :
50
#
```
### Layout tags
- Layout tags are `wall layout` , `floor layout` , and `ceiling layout`   
-  The input is a vector of integers separated by commas. Each new vector is written on a new line. That way, the vectors create a 2D top down view of the map where each number is a tile. There is no limit on the amount of digits for each tile index and negative numbers are allowed!
- This tag helps us assign block indexes to specific tiles so later we can rename them to something more intuitive and easier to remember in the  
```
/Example
0,0,0,0,0,0,0,0,0,0,0,0,0
0,1,1,1,1,1,1,1,1,1,1,1,0,0
0,1,1,4,1,1,1,1,1,1,1,3,1,0,0,0
0,1,1,1,1,1,1,1,1,4,1,1,1,1,0,0
0,1,1,1,1,1,1,1,1,4,1,1,1,0,0,0
0,1,1,1,1,1,1,1,1,1,1,1,0,0
0,0,0,0,0,0,0,0,0,0,0,0,0
```
### Tile name mapping tags
- Name mapping tags are `wall tiles` , `floor tiles`, and `ceiling tiles`
- The input is the tile index followed by the the name we want to give it
```
/Example
1:door
```
### Resource tags
- Resource tags are `sounds` and `textures` tags
- The input is the name we want to give to the tile, followed by the URL of the file
```
/Example
cobble:media/textures/cobble.jpg,0
```
### Tile-resource mapping tags
- Tile-resource mapping tags are  `wall textures`, `ceiling textures`,`floor textures`, and `debug colors`
- The input is simply the name of the tile followed by the name of the resource
```
/Example
wall:cobble
```
- It is okay for two different resources to have a different name like the following 
```
/Example
# textures :
name1:some\url\to\a\texure
# sounds :
name1:some\url\to\a\sound
# floor tiles :
3:name1
#
```
- This in turn means if you were to assign the floor tiles with tile index 3 to the texture, the assignment will look like this _(given we perform the previous name bindings)_ 
```
/This is perfectly fine since the two are accessed inside different containers
# tile textures :
name1:name1
#
```
- The only exception is the `debug colors` tag where we replace the name of the resource to an RGB value
```
/Example
door:0,255,0
```