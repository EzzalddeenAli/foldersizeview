

REM build before run this script


cd build-release
cd release

rmdir /s /q dist
mkdir dist
copy FolderSizeView.exe dist\FolderSizeView.exe

cd dist
C:\Qt\5.13.0\msvc2017_64\bin\windeployqt.exe FolderSizeView.exe

cd ..
cd ..
cd ..

mkdir dist
rmdir dist\FolderSizeView_Windows
xcopy build-release\release\dist dist\FolderSizeView_Windows\ /s /e /c /y /h /r
