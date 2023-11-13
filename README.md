### cub3d

cub3d is a project from 42 school that uses raycasting to display a 3d rendered map.

The player should be abble to walk through the map and to turn his head to navigate freely.


https://github.com/JulesRF/cub3d/assets/51792641/910db615-9a77-4dde-8911-64e410b41e4a



  
The subject also asks you to render differents maps located in ".cub" extension files.
Those files can be created or modified by the user so the program needs to carefuly parse the input.

The user can draw his own map using "1" characters as wall and "0" characters as floor and "E" "N" "S" "O" characters as the players spawn (and his facing direction), the rest will be empty.
He can also choose the color of the floor, ceiling, and can add textures to render on the walls 
![image](https://github.com/JulesRF/cub3d/assets/51792641/e486a2a0-f20b-4df0-b7fb-c0a406204869)  


Here are some of the parsing checks that protects the program from crashing:
![image](https://github.com/JulesRF/cub3d/assets/51792641/59e57160-6e68-4e9d-b915-1d97f1e84050)
![image](https://github.com/JulesRF/cub3d/assets/51792641/fdae028a-bc90-46dc-94e6-57f5ecc7762b)
![image](https://github.com/JulesRF/cub3d/assets/51792641/740a6dbf-c748-4953-98f7-399b45307e19)  

The map cand be rendered with any texture as long as it is a .xpm file, here is a map with photos of me and my friend as walls
![image](https://github.com/JulesRF/cub3d/assets/51792641/ee2f8291-0d62-4fad-8fd1-1f1045b7a6b0)

