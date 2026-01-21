<div id="top"></div>


<!-- PROJECT LOGO -->
<br />
<div align="center">
  <h3 align="center">Raycasting Video Game</h3>

  <p align="center">
    Implementation of raycasting video game in the same style of Doom or Wolfenstein 3D.
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

![Product Name Screen Shot][schema-network]

A simple FPS video game with several type of enemies.
The goal is to kill all enemies, with different weapons, without the player's life reaching zero. But after 5sec during which the player has not been hit he recovers 1 life point per second.

The player move by using Z, Q, S, D keys (azerty keyboard), shoot by using left click, display pause menu thanks to H key and close pause menu with Q and change the settings by using arrows.

In the game everything is editable, the number of enemies, weapons, type of enemies and their stats, and the map.

![Product Name Screen Shot][loss-function]

I use raycasting algorithm and DDA algorithm to optimize that. The player projects lots of vectors that determine where the nearest wall is in order to return the distance.

And thanks to the distances I was able to display more or less large rectangles in order to create a perspective.

![Product Name Screen Shot][less-texture]

A little preview on Youtube :
  https://www.youtube.com/watch?v=Whu1s6VjVgY


<p align="right">(<a href="#top">back to top</a>)</p>



### Built With


* [C Language](https://fr.wikipedia.org/wiki/C_(langage))
* [Allegro 4.4](https://www.allegro.cc/manual/4/api/)

<p align="right">(<a href="#top">back to top</a>)</p>


<!-- USAGE EXAMPLES -->
## Usage

### On Windows

Download [Allegro 4.4](https://liballeg.org/old.html) and 

Use the 

`CMakeLists.txt` (and put exe file to root)

or 

`gcc ./src/*.c -lm -lalleg44 -lmingw32 -lwinmm -I./includes`


The conf input file should be as follows:

For enemies:

      numberOfEnemies
      filepath
      width to cut the sprite
      height to cut the sprite
      number sprite for walk anim
      number sprite for attack anim
      number sprite for death anim
      life
      dps
      speed
      points
      ...

For guns:

      numberOfGuns
      filepath
      number shoot sprite
      number reload sprite
      bullet number
      filepath reload sound
      filepath shoot sound
      ...


For map:

      number column
      number raw
      ...

It's possible to add/remove textures by adding/removing them in the file `./assets/texture.bmp`

<p align="right">(<a href="#top">back to top</a>)</p>


<!-- CONTACT -->
## Contact

Gabriel GUIET-DUPRE - [in: gabriel-guiet-dupre](https://linkedin.com/in/gabriel-guiet-dupre) - gabriel.guietdupre@edu.ece.fr

Project Link: [https://github.com/gab_gdp/rayCastingVideoGame](https://github.com/Gab404/my_perceptron)

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[linkedin-url]: https://linkedin.com/in/gabriel-guiet-dupre
[schema-network]: ./assets/gameplay.png
[loss-function]: ./assets/raycastingDisplay.PNG
[less-texture]: ./assets/lessTexture.png
