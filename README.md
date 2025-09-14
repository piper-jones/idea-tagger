# idea-tagger
Run this CLI to write and save short notes, blurbs, quotes, etc. Then, get metrics on the similarity scores, find similar words, and generate a similarity graph of your notebook (coming soon).

Current run instructions (Windows Powershell):

**Installations**

Installed Golang from: https://go.dev/doc/install
Using C++: c++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 7.3.0

VCPKG Libraries:
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg.exe integrate install
.\vcpkg.exe install cli11
.\vcpkg install nlohmann-json

**Build & Run Commands**

mingw32-make
.\idea_tagger.exe

Old command before Makefile was added:
g++ -std=c++17 -Wall -Wextra -O2 *.cpp -o main.exe  

**Tesing Go Files:**
go mod init apimodule                 
go build -o wordmuse.exe .\cmd\wordmuse
.\wordmuse.exe --term pineapple+pizza
(pineapple+pizza is example of where any sstring can go, with "+" as space)
