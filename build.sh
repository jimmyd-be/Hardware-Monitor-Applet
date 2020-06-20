#! /bin/bash

set -x
set -e

rm -Rf build
mkdir build

BUILD_DIR=$(mktemp -d -p "build" appimage-build-XXXXXX)

# store repo root as variable
REPO_ROOT=$(readlink -f $(dirname $(dirname $0)))
OLD_CWD=$(readlink -f .)

# switch to build dir
cd "$BUILD_DIR"

# configure build files with qmake
# we need to explicitly set the install prefix, as CMake's default is /usr/local for some reason...
qmake "$REPO_ROOT"

# build project and install files into AppDir
make -j$(nproc)
make install INSTALL_ROOT=AppDir

# now, build AppImage using linuxdeploy and linuxdeploy-plugin-qt
# download linuxdeploy and its Qt plugin
wget https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage
wget https://github.com/linuxdeploy/linuxdeploy-plugin-qt/releases/download/continuous/linuxdeploy-plugin-qt-x86_64.AppImage
wget https://github.com/linuxdeploy/linuxdeploy-plugin-appimage/releases/download/continuous/linuxdeploy-plugin-appimage-x86_64.AppImage

# make them executable
chmod +x linuxdeploy*.AppImage

# make sure Qt plugin finds QML sources so it can deploy the imported files
export QML_SOURCES_PATHS="$REPO_ROOT"/src

# QtQuickApp does support "make install", but we don't use it because we want to show the manual packaging approach in this example
# initialize AppDir, bundle shared libraries, add desktop file and icon, use Qt plugin to bundle additional resources, and build AppImage, all in one command
./linuxdeploy-x86_64.AppImage --appdir AppDir -e Hardware-Monitor-Applet -i "$REPO_ROOT"/Resources/icon.png -d "$REPO_ROOT"/Hardware-Monitor-Applet.desktop --plugin qt --output appimage

# move built AppImage back into original CWD
mv Hardware_Monitor_Applet*.AppImage "$OLD_CWD"


#cleanup
rm -Rf build
