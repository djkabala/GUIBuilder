GUI Builder for OpenSGToolbox
=============================

About
-----

This is a Graphical User Interface(GUI) builder for the
[OpenSGToolbox](http://www.opensgtoolbox.org "OpenSGToolbox") libraries. It
can be used to construct a GUI by creating GUI components in a visual editor,
arranging them, changing their properties, saving to a file, and loading saved
files.

This GUI Builder is similar to
[Interface Builder](http://en.wikipedia.org/wiki/Interface_Builder "Interface Builder")
on OS X and the [NetBeans IDE](http://netbeans.org/ "NetBeans IDE") for Java Swing.

License
-------
[Lesser General Public License](http://www.gnu.org/licenses/lgpl-3.0-standalone.html "Lesser General Public License")

Screen shots
-----------
![GUIBuilder Interface](https://github.com/djkabala/GUIBuilder/raw/master/Screenshots/ScreenShot01.jpg)

Building
--------
1. Get a build of [OpenSGToolbox](http://www.opensgtoolbox.org "OpenSGToolbox")
   for your platform.
2. Get [cmake](http://www.cmake.org/ "cmake")
3. Create a local directory for your local build
4. Run cmake in this directory
    1. Create the cmake entry `CMAKE_MODULE_PATH` and assign it the path to the
       cmake directory of your local install of OpenSGToolbox from (1.)
    2. Create the cmake entry `OpenSG_DIR` and assign it the path to the
       directory of your local install of OpenSGToolbox from (1.)
5. Build the binary using the build tool you selected with cmake
    * e.g. If you used the Makefile build tool: then run `make install` in the build
    directory
    * e.g. If you used the Visual Studio build tool: then open the Visual Studio
    project created by cmake.  Then build the "INSTALL" project.

Installation
------------
* Pre-built binaries

* From source
    1. Follow the previous Building instructions

Authors
-------
David Kabala

Reporting Errors
----------------
Ask a question on the OpenSGToolbox
[Google Group](http://groups.google.com/group/opensgtoolbox-users "Google Group").

If it is a bug, and is not already listed as one.  Then open a new Issue on the
GitHub page for GUIBuilder.

Contributing
------------

1. [Fork it](http://help.github.com/forking/ "Fork it")
2. Clone your forked repository (`git clone url/to/your/forked/repository`)
3. Create a branch (`git checkout -b cool_feature_x`)
4. Commit your changes (`git commit -am "Added Cool Feature X"`)
5. Push to the branch (`git push origin cool_feature_x`)
6. [Send a pull request](http://help.github.com/pull-requests/ "Send a pull request")
7. Enjoy a refreshing Mt. Dew and wait

