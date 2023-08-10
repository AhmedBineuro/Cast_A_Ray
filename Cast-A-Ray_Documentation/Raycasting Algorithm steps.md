# DDA Raycasting Algorithm

## 1. Normalize Direction Vector
First, normalize the direction vector to ensure it has a length of 1.

$$
\text{length} = \sqrt{dx^2 + dy^2}
$$
$$
\text{normalized direction} = \left( \frac{dx}{\text{length}}, \frac{dy}{\text{length}} \right)
$$

## 2. Determine Step Size
The step size for each axis can be determined by the sign of the direction vector components.

$$
\text{step} = (\text{sign}(dx), \text{sign}(dy))
$$

## 3. Calculate Delta Distances
Delta distances represent the distance the ray must travel along each axis to cross a grid line.

$$
\text{delta distance} = \left( \frac{1}{\left| \text{normalized direction}_x \right|}, \frac{1}{\left| \text{normalized direction}_y \right|} \right)
$$

## 4. Calculate Side Distances
Calculate the distance from the start position to the next grid line along each axis.

$$
\text{side distance}_x = (\text{next integer x} - \text{start}_x) \times \text{normalized direction}_x
$$
$$
\text{side distance}_y = (\text{next integer y} - \text{start}_y) \times \text{normalized direction}_y
$$

## 5. Loop Through Grid
Loop through the grid, incrementing the side distances by the delta distances and taking steps accordingly.

- Compare \(\text{side distance}_x\) and \(\text{side distance}_y\)
- If \(\text{side distance}_x < \text{side distance}_y\):
  - Increment \(\text{side distance}_x\) by \(\text{delta distance}_x\)
  - Step in x direction
- Else:
  - Increment \(\text{side distance}_y\) by \(\text{delta distance}_y\)
  - Step in y direction
- Check for wall collision and continue until a wall is hit or a maximum distance is reached

## 6. Calculate Perpendicular Distance
Calculate the perpendicular distance to the wall to avoid the fisheye effect.

$$
\text{perpendicular distance} = \frac{\text{side distance}_x \times \text{step}_x - \text{start}_x}{\text{normalized direction}_x}
$$

or

$$
\text{perpendicular distance} = \frac{\text{side distance}_y \times \text{step}_y - \text{start}_y}{\text{normalized direction}_y}
$$

depending on the axis used to hit the wall.

## 7. Render the Wall Slice
Use the perpendicular distance to calculate the wall height and render the wall slice with appropriate shading.

Feel free to use this guide for your raycasting renderer! 😃
