<div id="top"></div>

[![LinkedIn][linkedin-shield]][linkedin-url]


https://user-images.githubusercontent.com/46533519/168650641-39d46f7f-d6ee-4a16-8fc2-ccd35f4b05ab.mp4


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
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

A 2D "Mario Maker". 

This project explore :
  * advanced memory management,
  * optimization techniques (collision detection),
  * event-driven programming (timers, alarms),
  * parallelism.

<p align="right">(<a href="#top">back to top</a>)</p>



### Built With

* [CMake](https://cmake.org/)
* [Make](https://www.gnu.org/software/make/)
* [SDL](https://www.libsdl.org/index.php)

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

### Prerequisites

* Make
  ```sh
  sudo apt install make
  ```

* CMake
  ```sh
  sudo apt install cmake
  ```

* SDL2
  ```sh
  sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev
  ```

### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/Nhkp/Projet-Mario.git
   ```
2. Configure CMake
   ```sh
   cmake -S . -B build
   ```
3. Get into build directory
   ```sh
   cd build
   ```

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
## Usage

### Launch

```sh
./mario --load ../maps/demo_map
```

### Controls

* Left/Right arrows : Move to the left/right
* Up arrow : Jump
* X : Accelerate
* Space : Laser shot
* B : Put a bomb
* V : Put a landmine
* C : Activate the landmine
* E : Enter edit mode 
* Q : Quit edit mode
* Tab : Shift between decor elements
* Enter : Put a decor element
* S : Save the map
* Escape : Quit the game

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- CONTACT -->
## Contact

Clément Palézis - palezis.c@gmail.com

Project Link: [https://github.com/Nhkp/Projet-Mario](https://github.com/Nhkp/Projet-Mario)

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/cpalezis
[demo_movie]: demo.mp4
