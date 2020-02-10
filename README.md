# Flock Simulation

This is a practice C++ project implementing a flock simulation (also known as boid, swarm, school) using [SFML](https://www.sfml-dev.org/).

A flock simulation features **emergent behavior**, which is the behavior of a system that does not depend on its individual parts, but on their relationships to one another.

![](BOIDS.gif)

## Flocking behavior fundamentals

Each bird applies cohesion, alignment, and separation rules to its immediate neighbors within a limited range.

### Cohesion

Each bird tries to stay close to the other birds in the group. This rule causes each bird to go toward the center of it's neighbor's defined space. 
 **Does this mean the space between multiple neighbors, or the exact location of one neighbor?** 

**Cohesion vector**: the average direction between three neighbors ??

**Cohesion range**: the radius in which the bird applies cohesion ?? 

### Alignment

Each bird aligns its direction based on its immediate neighbor.

**Alignment vector**: the average direction neighbors are going ?? **do birds know which direction other birds are headed, or just their location?** 

**Alignment range**: the radius in which the bird applies alignment

### Separation

Each bird maintains enough space from its neighbors to avoid collision.

**Separation vector**: the average opposite direction neighbors are going ?? 

**Separation range**: the radius in which the bird applies separation.

## Pseudo code

Pseudo code for birds applying alignment, separation, and cohesion to simulate flocking behavior.

### Definitions

Establish a coordinate system... 

Define a class `Bird` with the following members

#### `vector Cohesion(neighbors)`

Each bird sets direction toward the center of it's neighbor's defined space.

1. If there are no neighbors, return `0`
2. For each neighbor, get the `neighbor_position`
3. Find the `center_position` of all `neighbor_position`
3. Find the `vector` from `this_position` to `center_position`
4. Return `vector`: `⟨distance, direction⟩`

#### `vector Separation(neighbors)`

Each bird maintains enough space from its neighbors to avoid collision.

1. If there are no neighbors, return `0`
2. For each neighbor, find the `vector` from `neighbor_position` to `this_position`: `vector` = `⟨this1 - neighbor1, this2 - neighbor2⟩`
    * If `vector` is greater than `0` (`vector > 0`), make `direction` inversely proportional to `distance`
3. Combine all neighbor `direction` values into `average_direction` // not sure about this..
4. Return `vector`: `⟨distance, average_direction`

#### **`vector Alignment(neighbors)`**

Each bird aligns its direction based on its immediate neighbor.

1. If there are no neighbors, return `0`
2. For each neighbor, get the `current_vector` (after all functions run each frame, what order??)
3. Combine all neighbor `current_vector` to find the `average_vector`
4. Return `average_vector` 

### Runtime

1. Initialize some number of `Bird` class objects

Each `Bird` does the following once per frame (is from the right word to use here?)

1. Run `Cohesion()` and get the `cohesion_vector` value
2. Run `Alignment()` and get the `alignment_vector` value
3. Run `Separation()` and get the `separation_vector` value
4. Combine `cohesion_vector`, `alignment_vector`, and `separation_vector` to get `acceleration`
5. Add acceleration to vector.
6. Move position with vector. 

## Vectors (math review)

We'll use the type `vector`, which represents `distance` (magnitude)) and `direction` like `⟨distance, direction⟩`, e.g. `⟨-2, 5⟩`.

A representation of vector `V` = `⟨A, B⟩` in 2D space is any line segment `AB` from the location `A` = `(x,y)` to the location `B` = `(x,y)`.

To find vector given two points, `A` = `(a1, a2)` and `B` = `(b1, b2)` take destination `b` coords and subtract the origin `a`: `AB` = `⟨b1 - a1, b2 - a2⟩`.

To find the vector of `B` to `A` (vector `BA`), use `V = ⟨a1 - b1, a2 - b2⟩`.

### Distance

The `distance` (magnitude) of a vector is the distance between the origin point and the end point. 

To find the distance given a vector `⟨a1, a2⟩`, square `a1` and `a2`, add them together, and then take square root of that, like `sqrt(a1^2 + a2^2)`. 

To find the distance given origin `A` = `(a1, b1)` and end `B` = `(b1, b2)`, find vector and then distance, like s`qrt((b1 - a1)^2 + (b2 - a2)^2)`.

For example, vector `PQ` with origin `P` at `(1,1)` and end `Q` at `(5,3)` distance is `sqrt((5 -1)^2 + (3 - 1)^2)` = `sqrt(4^2 + 2^2)` = `sqrt(16 + 4)` = `sqrt(20)` = `4.5`.

A `0` vector `⟨0, 0⟩` has no `distance`(and as a result, no `direction`).

### Direction

The `direction` (force) of a vector is the measure of the angle it makes with a horizontal line.

To find direction give a vector, find `tan` = `vertical_change`/`horizontal_change`

To find direction given given origin `A` = `(x1, y1)` and end `B` = `(x1, y2)`, find vector and then direction, `tan` = `(y2 - y1)/(x2 - x1)`, then maybe inverse `tan`?

For example, vector `PQ` with origin `P` at `(2,3)` and end `Q` at `(5,8)` direction is `tan` = `(8 - 3)/(5 - 2)` = `5/3`, find inverse tangent: `tan^-1(5/3)` = `59` degrees.

### Position

Position vector for a set of coords `(-90, 4)` is `⟨-90, 4⟩`.

## Visual Studio Setup 

Having linker issues on home PC, I think because I don't have compiler for 32 bit installed? 

Here's how to set up for 32 bit, assuming compiler is available (I think). 

1. Ensure the following settings in Project Properties
    * Configuration: Active (Debug/Release)
    * Platform: Win32
    * Configuration Manager > 
        * Active Solution Configuration: Debug/Release (set both)
        * Active Solution Platform: Win32 (both debug and release)
        * Project / Configuration / Platform / Build: sfml-flock-sim / Debug/Release / Win32 / True
    * C/C++ > General > Additional Include Directories > add Program Files(x86)\SFML-2.5.1\include
    * Linker > General > Additional Library Directories > add Program Files(x86)\SFML-2.5.1\lib
    * Linker > Input > Additional Dependencies > List of libs must match release/debug (below are debug)
        * `sfml-audio-d.lib`
        * `sfml-graphics-d.lib`
        * `sfml-window-d.lib`
        * `sfml-system-d.lib`
        * `sfml-main-d.lib`
        * `sfml-network-d.lib`
    * Linker > Advanced > Target Machine: MachineX86
2. Project > Rebuild (generates dir with executable).
3. Copy all .dlls from C:\Program Files (x86)\SFML-2.5.1\bin (32 bit versions) and paste into sfml-flock-sim/flock-sim/Debug