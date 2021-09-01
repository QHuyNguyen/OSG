OpenSceneGraph Windows Visual C++ 2015 AVX2 Build

This is a 64-bit Visual C++ 2015 build of the OpenSceneGraph library
(http://www.openscenegraph.org/) provided by Objexx Engineering
(http://objexx.com) for use by the OSG community.

This "AVX2" build was built with the /arch:AVX2 compiler option, 
which may give somewhat higher performance on AVX2 (Haswell)
and later CPUs but will not run on per-AVX2 generation CPUs.

This was built with Qt 5.6 and osgQt is included.

The most recent versions of these 3rd party libraries are included:
curl
freetype
giflib
glut
libjpeg
libpng
minizip
tiff
zlib

The documentation and examples are not bundled in the build to save space.

The OSG headers are in the include directory.
The OSG static libraries are in the lib directory.
The bin directory needs to be on your PATH for applications to find the DLLs.

Objexx uses OSG and plans to build and post future OSG releases.
Custom builds and builds of non-release/git code may be possible upon request.
Objexx Engineering provides no warranty of any kind for this software.

For questions and support email support@objexx.com and we'll try to help.
