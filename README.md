# HLOH
Half-Life One Hit, based on the GTA V mod

## Install
- Get Metamod:Source [here](https://metamodsource.net/downloads.php).
- Get the released binaries [here](https://github.com/drunderscore/HLOH/releases).
- Extract the ZIP file contents into `hl2/addons`.

## Build
- Clone with `git clone --recursive https://github.com/drunderscore/HLOH`
  - Or if you already cloned it, be sure to `git submodule init` and `git submodule update`
- Clone https://github.com/alliedmodders/hl2sdk
  - You may need to patch `public/tier0/memalloc.h` line 385 to `#include <typeinfo>`
- `mkdir build`
- `cd build`
- `cmake ../`

## Other Source Games
This mod may well work for other Source games than Half-Life 2, but it's intent was not that.  
I will gladly accept pull requests to bring **compatible** support to other Source games.

## License and Credit
This repository is licensed under GNU GPL Version 3.

I believe that [DarkViperAU](https://youtube.com/c/DarkViperAU) is the first person I saw to have done this. Be sure to support his content on Youtube and Twitch.