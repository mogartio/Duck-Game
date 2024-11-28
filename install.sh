#!/bin/bash

set -e  # Exit immediately if a command exits with a non-zero status.

print_text() {
    color=$1
    shift
    printf "\e[${color}m$@\e[0m\n"
}

MAG_WHI_BOLD="1;35;47"
INSTALL_MSG="1;5;32;45"

print_text $MAG_WHI_BOLD "--------- Installing utility packages ---------"

# Utility packages
sudo apt-get --yes update
sudo apt-get --yes install make
sudo apt-get --yes install cmake
sudo apt-get --yes install g++
sudo apt-get --yes install unzip
sudo apt-get --yes install wget
sudo apt-get --yes install build-essential

# Dependencies
print_text $MAG_WHI_BOLD "--------- Installing dependencies ---------"
sudo apt-get --yes install libsdl2-dev libopusfile-dev libfreetype6-dev libfluidsynth-dev libmodplug-dev

# SDL2
print_text $MAG_WHI_BOLD "--------- Installing SDL2 ---------"
mkdir -p "SDL2"

SDL2_IMAGE=https://github.com/libsdl-org/SDL_image/releases/download/release-2.6.3/SDL2_image-2.6.3.zip
SDL2_MIXER=https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.6.3/SDL2_mixer-2.6.3.zip
SDL2_TTF=https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.20.2/SDL2_ttf-2.20.2.zip

wget "$SDL2_IMAGE" -P "SDL2"
wget "$SDL2_MIXER" -P "SDL2"
wget "$SDL2_TTF" -P "SDL2"

unzip "SDL2/SDL2_image-2.6.3.zip" -d "SDL2"
unzip "SDL2/SDL2_mixer-2.6.3.zip" -d "SDL2"
unzip "SDL2/SDL2_ttf-2.20.2.zip" -d "SDL2"

# Install SDL2 components
(
    cd "SDL2/SDL2_image-2.6.3"
    mkdir build && cd build
    cmake ..
    make -j4
    sudo make install
)

(
    cd "SDL2/SDL2_mixer-2.6.3"
    mkdir build && cd build
    cmake ..
    make -j4
    sudo make install
)

(
    cd "SDL2/SDL2_ttf-2.20.2"
    mkdir build && cd build
    cmake ..
    make -j4
    sudo make install
)

# Qt installation
print_text $MAG_WHI_BOLD "--------- Installing QT ---------"
sudo apt-get --yes install qtbase5-dev qtmultimedia5-dev

# YAML installation
print_text $MAG_WHI_BOLD "--------- Installing YAML ---------"
sudo apt-get --yes install libyaml-cpp-dev

# Duck Game compilation
print_text $INSTALL_MSG "--------- Installing Duck Game ---------"
make clean
make

# Success message
print_text $INSTALL_MSG "--------- Duck Game Installation Complete ---------"


# Configure run_server and client scripts
print_text $MAG_WHI_BOLD "--------- Configuring Scripts ---------"

# Create run_server script
cat > run_server <<'EOF'
#!/bin/bash
cd build
./server $1
EOF

# Create client script
cat > run_client <<'EOF'
#!/bin/bash
cd build
./client
EOF

# Make scripts executable
chmod +x run_server
chmod +x run_client

print_text $MAG_WHI_BOLD "--------- Scripts Configured Successfully ---------"