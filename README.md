Bender
======

:robot: Find Bender's suicidal path :skull:

With this software and a map you can predict where is Bender and preventing him from reaching the suicidal booth.

Usage
-----

**Build & Running**
```
$ mkdir build && cd build
$ cmake ../
$ make
$ ./bender <map file> 
```

Maps
----

You should have a map like the examples in the maps directory.
First line of the file with the dimensions of the map separated by whitespace.
Next lines an ascii representation of the map.

```
5 6         10 10
######      ##########
#@E $#      #        #
# N  #      #  S   W #
#X   #      #        #
######      #  $     #
            #        #
            #@       #
            #        #
            #E     N #
            ##########
```

The smallest map we could have is a 3x4 or 4x3 matrix like below. 

```
####   ###
#@$#   #@#
####   #$#
       ###
```

This software expects a map with exactly one starting point (@) and a finish point($) a.k.a suicide booth.

Because of that the minimal dimension of a map is a 4x4 matrix. In such small map don't even send the rescue team.
Bender is probably already dead :skull:. 
 

Changelog
---------

 - 0.1 - File map parser and release to show in Master
 
