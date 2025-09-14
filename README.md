idea-tagger

A command-line notebook for short notes, blurbs, and quotes. Compute similarity metrics between entries, fetch similar words (via a small Go helper), and (soon) generate a similarity graph of your notebook.

**Features**

Add and persist blurbs/quotes

Compute Cosine and Jaccard similarity between recent entries

Get similar words for the latest blurb (via a bundled Go binary)

Graph generation coming soon

**Prerequisites (Windows / PowerShell)**

C++ toolchain: MinGW-w64 (e.g., g++ (x86_64-posix-seh) 7.3.0)
Go: Install from the official guide → https://go.dev/doc/install
vcpkg (for C++ deps): CLI11 and nlohmann-json

**Setup**
1) Install vcpkg and libraries
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg.exe integrate install

2) Libraries
.\vcpkg.exe install cli11
.\vcpkg.exe install nlohmann-json

*vcpkg currently a submodule

**Build & Run (C++ CLI)**

From the project root:

mingw32-make

.\idea_tagger.exe

The Makefile builds idea_tagger.exe.
(Legacy one-liner without Makefile:
g++ -std=c++17 -Wall -Wextra -O2 *.cpp -o main.exe)
