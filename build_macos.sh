
rm -rf build-macos
mkdir build-macos
cd build-macos

# compile
$HOME/Qt/5.13.0/clang_64/bin/qmake "CONFIG+=hide_symbols" ../foldersizeview/foldersizeview.pro
make

# create temp dmg
$HOME/Qt/5.13.0/clang_64/bin/macdeployqt ./FolderSizeView.app -dmg


# repack dmg
rm -rf dist
mkdir dist
hdiutil detach /Volumes/FolderSizeView
hdiutil attach FolderSizeView.dmg
cp -R /Volumes/FolderSizeView/FolderSizeView.app ./dist/FolderSizeView.app
hdiutil detach /Volumes/FolderSizeView

# remove 

cd dist
cp ../../pack/appdmg.json ./
cp ../../pack/background.png ./
appdmg appdmg.json ./FolderSizeView.dmg

cd ..
cd .. 

rm -rf dist
mkdir dist
rm dist/FolderSizeView.dmg
cp -f build-macos/dist/FolderSizeView.dmg dist/

#cp -R dist/* ../release/

echo "---------"
echo "done :)"
echo "---------"
