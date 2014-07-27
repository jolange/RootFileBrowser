RootFileBrowser
==============

Small program to view a [CERN ROOT](http://root.cern.ch) *.root file in a TBrowser.

Uses [TAppKillManager](https://github.com/johannes-lange/TAppKillManager).

&copy; 2014 [Johannes Lange](https://johannes-lange.github.io)

Usage
-----

<pre><code>$ git clone https://github.com/johannes-lange/RootFileBrowser.git
$ git submodule init
$ git submodule update
$ make
$ ./RootFileBrowser &lt;your-file&gt;.root </code></pre>

|Option | Description                                |
|-------|--------------------------------------------|
|-ns    | Don't show statistics window for histograms|
 
