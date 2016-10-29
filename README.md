# ar-blackboard

## Installation guide

### Linux

#### Install **box2d** for the physical engine
sudo apt install libbox2d-dev

#### Install **sdl2** for graphics rendering
sudo apt install libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev

#### Install **opencv** for image analysis
In order to install opencv, follow the instructions on the official website: http://docs.opencv.org/2.4/doc/tutorials/introduction/linux_install/linux_install.html#linux-installation
*run this command after install opencv: ln -s /path/to/opencv/3rdparty/lib/libippicv.a /usr/local/lib*

#### Install dev tools*
sudo apt install qtcreator qt5-default qtdeclarative5-dev 
sudo apt install libboost-all-dev


*Right now we only support linux, soon we'll be releasing a windows version
