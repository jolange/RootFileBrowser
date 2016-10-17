RootFileBrowser
==============

Small program to view a [CERN ROOT](http://root.cern.ch) *.root file in a TBrowser.

Uses [TAppKillManager](https://github.com/jolange/TAppKillManager).

&copy; 2014 [Johannes Lange](https://jolange.github.io)

Usage
-----

<pre><code># checkout and compile
git clone --recursive git@github.com:jolange/RootFileBrowser.git
cd RootFileBrowser
make
# run
./RootFileBrowser &lt;your-file&gt;.root </code></pre>

|Option                                       | Description                                |
|---------------------------------------------|--------------------------------------------|
|<code>-ns</code>                             | Don't show statistics window for histograms|
|<code>-s &lt;myStyle.C&gt;</code>            | Specify macro that sets your style. The function <code>&lt;myStyle&gt;()</code> is called.|
|<code>-d &lt;file.root&gt; &lt;KEY&gt;</code>| Deletes <code>&lt;KEY&gt;</code> from file. <code>-d</code> must be the first parameter. Only one file but several keys can be specified. To delete keys in subdirectories, type <code>&lt;subdir&gt;/&lt;KEY&gt;</code>. Wildcards work (e.g. <code>myHistograms/*</code>)|
 
