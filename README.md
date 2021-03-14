# Rubik
## General use
Program takes a mix as parameter

```
./rubik "F R U B L D"
```
The letter means turning a single turn, (90°), clockwise, the corresponding face.

**F (front)**: the face facing the solver.

**B (back)**: the back face.

**R (right)**: the right face.

**L (left)**: the left face.

**U (up)**: the upper face.

**D (down)**: the face opposite to the upper face.
Middle layer turns as well as cube rotations are not accepted

### Parameters
A mix is a sequence of moves to apply to a cube from a solved position
The notation for the moves used is the [international notation](http://www.rubiksplace.com/move-notations/)

### Modifiers
```
' (e.g. D')
```
Indicates turning the corresponding face a single turn, (90°), counter-clockwise. (known as "prime")
```
2 (e.g. R2)
```
Indicates turning the corresponding face 2 single turns (180°). The direction of the turning does not matter here.

Valid sequence example:
```
./rubik "R2 D' B' D F2 R F2 R2 U L' F2 U'"
```

### Return
The program will return on the standard output the move sequence to be applied to solve the mixed cube