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

|Option                                       | Description                                |
|---------------------------------------------|--------------------------------------------|
|<code>-ns</code>                             | Don't show statistics window for histograms|
|<code>-s &lt;myStyle.C&gt;</code>            | Specify macro that sets your style. The function <code>&lt;myStyle&gt;()</code> is called.|
|<code>-d &lt;file.root&gt; &lt;KEY&gt;</code>| Deletes <code>&lt;KEY&gt;</code> from file. <code>-d</code> must be the first parameter, only one file but several keys can be specified. To delete keys in subdirectories, type <code>&lt;subdir&gt;/&lt;KEY&gt;</code>. Wildcards work (e.g. <code>myHistograms/*</code>)|
 
