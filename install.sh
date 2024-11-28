#!/bin/bash

print_text() {
	color=$1
	shift
	printf "\e[${color}m$@\e[0m\n"
}

MAG_WHI_BOLD="1;35;47";
print_text $MAG_WHI_BOLD "--------- Installing utility packages ---------"


sudo apt-get --yes install update
sudo apt-get --yes install make
sudo apt-get --yes install cmake
sudo apt-get --yes install g++
sudo apt-get --yes install unzip
sudo apt-get --yes install wget
sudo apt-get --yes install build-essential


SDL2_IMAGE=https://github.com/libsdl-org/SDL_image/releases/download/release-2.6.3/SDL2_image-2.6.3.zip
SDL2_MIXER=https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.6.3/SDL2_mixer-2.6.3.zip
SDL2_TTF=https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.20.2/SDL2_ttf-2.20.2.zip

mkdir -p "SDL2"

MAG_WHI_BOLD="1;35;47";
print_text $CYAN "--------- Installing dependencies ---------"

sudo apt-get --yes install libsdl2-dev     		\
                           libopusfile-dev 		\
						   libfreetype6-dev 	\
						   libfluidsynth-dev 	\
						   libmodplug-dev		\

MAG_WHI_BOLD="1;35;47";
print_text $CYAN "--------- Installing SDL2 ---------"

wget "$SDL2_IMAGE" -P "SDL2"
wget "$SDL2_MIXER" -P "SDL2"
wget "$SDL2_TTF" -P "SDL2"
unzip "SDL2/SDL2_image-2.6.3.zip" -d "SDL2"
unzip "SDL2/SDL2_mixer-2.6.3.zip" -d "SDL2"
unzip "SDL2/SDL2_ttf-2.20.2.zip" -d "SDL2"

cd "SDL2/SDL2_image-2.6.3"
mkdir build
cd build
cmake ..
make -j4
sudo make install

cd ../../SDL2_mixer-2.6.3
mkdir build
cd build
cmake ..
make -j4
sudo make install

cd ../../SDL2_ttf-2.20.2
mkdir build
cd build
cmake ..
make -j4
sudo make install

cd ../../../

MAG_WHI_BOLD="1;35;47";
print_text $CYAN "--------- Installing QT ---------"

sudo apt-get --yes install qtbase5-dev
sudo apt-get --yes install qtmultimedia5-dev

MAG_WHI_BOLD="1;35;47";
print_text $CYAN "--------- Installing YAML ---------"
sudo apt-get --yes install libyaml-cpp-dev

MAG_WHI_BOLD="1;35;47";
print_text $CYAN "--------- Installing GoogleTest ---------"
git clone https://github.com/google/googletest.git
cd googletest
mkdir build
cd build
cmake ..
make
sudo make install
cd ../../

INSTALL_MSG="1;5;32;45";
print_text $INSTALL_MSG "--------- Installing Duck Game ---------"

make clean
make

# Print completion message
print_text $INSTALL_MSG "--------- Duck Game Installation Complete ---------"
