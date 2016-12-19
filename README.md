RootFileBrowser
==============

Small program to view a [CERN ROOT](http://root.cern.ch) *.root file in a TBrowser.

Uses [TAppKillManager](https://github.com/jolange/TAppKillManager).

&copy; 2014 [Johannes Lange](https://jolange.github.io)

Usage
-----
```
# checkout and compile
git clone --recursive git@github.com:jolange/RootFileBrowser.git
cd RootFileBrowser
make
# run
./RootFileBrowser <your-file>.root
```

|Option                 | Description                                |
|-----------------------|--------------------------------------------|
|`-ns`                  | Don't show statistics window for histograms|
|`-s <myStyle.C>`       | Specify macro that sets your style. The function `<myStyle>()` is called. Can be used multiple times.|
|`-d <file.root> <KEY>` | Deletes `<KEY>` from file. `-d` must be the first parameter. Only one file but several keys can be specified. To delete keys in subdirectories, type `<subdir>/<KEY>`. Wildcards work (e.g. `myHistograms/*`)|
|`-c <command>`         | Executes a single root command (e.g `"gStyle->SetGridStyle(1)"`). Can be used multiple times. **Caution:** this option randomly causes crashes. |

