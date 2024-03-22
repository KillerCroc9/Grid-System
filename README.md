Unreal Engine Hexagonal Grid System
Introduction
This project introduces a comprehensive grid system tailored for Unreal Engine, focusing on hexagonal tiles. It's designed to facilitate game developers in implementing advanced grid-based mechanics, such as neighbor finding and distance calculations between hexes. Initially prototyped using Blueprints (BP), the system has been transitioned to Conventional C++ to enhance performance and enable more complex data handling.

Features
Hexagonal Grid Generation: Dynamically creates a hexagonal grid within the Unreal Engine environment, suitable for a wide range of grid-based games.
Neighbor Finding: Efficiently identifies adjacent hexes, enabling gameplay mechanics like movement and area-of-effect abilities.
Distance Calculation: Implements algorithms to calculate distances between hexes, crucial for pathfinding and strategic planning.
Data Storage: Each hexagon can store and retrieve gameplay-relevant data, offering developers the flexibility to adapt the grid system to various game types.
Technical Approach
Blueprint Prototyping: Initially, the grid system was prototyped using Unreal Engine's visual scripting system (Blueprints), allowing for rapid iteration and testing.
C++ Integration: To maximize efficiency and scalability, the system was migrated to Conventional C++. This transition enables complex data management and high-performance calculations, which are essential for real-time strategy games and simulations. I made a few wrapper classes so we could efficiently use BP with C++ since using vectors meant that we couldn't communicate between BP and C++ directly.
Hexagon Class: A custom Hex class has been developed in C++, encapsulating properties and methods related to individual hexes, such as coordinates. The early approach was to use the actor BP. The problem is if we wanted to select say a hex we would not know where on the grid it is without further calculations. So I switched to C++ Actor class.
Future Enhancements
I started Working on Flood Fill and wall generation.


