# idxread

Program to read data and metadata from IDX files, such as those from Yann LeCun's handwritten numbers dataset.

```console
$ idxread --help
Usage: idxread [--help|-h]
Usage: idxread [--meta|-m] FILEPATH
Usage: idxread [OPTIONS] FILEPATH

    Read IDX-formatted data from a binary file located at FILEPATH.

    Options

    --nhead NELEMS

        Show the first NELEMS elements of the data in FILEPATH

    --meta, -m

        Show the metadata of the data in FILEPATH

    --ncolumns, -c NCOLUMNS

        Print the data using NCOLUMNS columns

    --ntail, -t NELEMS

        Show the last NELEMS elements of the data in FILEPATH

$ idxread --meta t10k-images.idx3-ubyte
path              : t10k-images.idx3-ubyte
type              : 0x08 (uint8)
ndims             : 3 
dimension lengths : 10000 28 28 
number of elements: 7840000
$ idxread --nhead 784 --ncolumns 28  t10k-images.idx3-ubyte
  0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
  0   0   0   0   0   0  84 185 159 151  60  36   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
  0   0   0   0   0   0 222 254 254 254 254 241 198 198 198 198 198 198 198 198 170  52   0   0   0   0   0   0
  0   0   0   0   0   0  67 114  72 114 163 227 254 225 254 254 254 250 229 254 254 140   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0   0  17  66  14  67  67  67  59  21 236 254 106   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0  83 253 209  18   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0  22 233 255  83   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0 129 254 238  44   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0  59 249 254  62   0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0 133 254 187   5   0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   9 205 248  58   0   0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0   0   0   0   0   0 126 254 182   0   0   0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0   0   0   0   0  75 251 240  57   0   0   0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0   0   0   0  19 221 254 166   0   0   0   0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0   0   0   3 203 254 219  35   0   0   0   0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0   0   0  38 254 254  77   0   0   0   0   0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0   0  31 224 254 115   1   0   0   0   0   0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0   0 133 254 254  52   0   0   0   0   0   0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0  61 242 254 254  52   0   0   0   0   0   0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0 121 254 254 219  40   0   0   0   0   0   0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0 121 254 207  18   0   0   0   0   0   0   0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
$ idxread --ntail 784 --ncolumns 28  t10k-images.idx3-ubyte
  0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   8 117 254 220  89   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0   0   0   0   0   0  13  95 212 253 253 253 157   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0   0   0   0  16  95 209 253 253 253 245 125  18   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0   0  40  96 206 253 254 253 253 198  64   0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0  44 182 240 253 253 253 254 253 198  24   0   0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0  15  60  60 168 253 253 254 200  23   0   0   0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0   0  70 247 253 253 245  21   0   0   0   0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0  75 207 253 253 207  92   0   0   0   0   0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0  79 219 253 253 253 138   0   0   0   0   0   0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0 105 250 253 253 253  34   1   0   0   0   0   0   0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0  95 254 254 254 254  94   0   0   0   0   0   3  13  13  13   8   0   0   0   0   0
  0   0   0   0   0   0   0 107 253 253 253 204  15   0   0   0   0  21 166 253 253 253 212  25   0   0   0   0
  0   0   0   0   0   0  33 217 253 253 132  64   0   0  18  43 157 171 253 253 253 253 253 160   2   0   0   0
  0   0   0   0   0   3 166 253 253 242  49  17  49 158 210 254 253 253 253 253 253 253 253 253  11   0   0   0
  0   0   0   0   0  10 227 253 253 207  15 172 253 253 253 254 247 201 253 210 210 253 253 175   4   0   0   0
  0   0   0   0   0  10 228 253 253 224  87 242 253 253 184  60  54   9  60  35 182 253 253  52   0   0   0   0
  0   0   0   0   0  13 253 253 253 253 231 253 253 253  93  86  86  86 109 217 253 253 134   5   0   0   0   0
  0   0   0   0   0   2 115 253 253 253 253 253 253 253 253 254 253 253 253 253 253 134   5   0   0   0   0   0
  0   0   0   0   0   0   3 166 253 253 253 253 253 253 253 254 253 253 253 175  52   5   0   0   0   0   0   0
  0   0   0   0   0   0   0   7  35 132 225 253 253 253 195 132 132 132 110   4   0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
```

## CMake

The project has been initialized with a [CMakeLists.txt](CMakeLists.txt)-based
configuration for building with CMake:

```console
# change into the build directory
$ cd build/

# generate the build files
$ cmake -DCMAKE_BUILD_TYPE=Debug ..

# build the project
$ cmake --build .

# install the project to <repo>/build/dist
$ cmake --install . --prefix dist/

# run the program to see if it works
$ ./dist/bin/idxread
```

## Acknowledgements

_This project was initialized using [Copier](https://pypi.org/project/copier) and the [copier-template-for-c-projects](https://github.com/jspaaks/copier-template-for-c-projects)._
