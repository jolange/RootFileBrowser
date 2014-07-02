#include <iostream>

#include "TApplication.h"
#include "TBrowser.h"
#include "TFile.h"

#include "3rdParty/TAppKillManager.hpp"

int main(int argc, char* argv[])
{
   if (argc == 1){
      std::cout << "Error: specifiy name of *.root file as parameter" << std::endl;
      return -1;
   }
   TFile file(argv[1],"READ");
   if (file.IsZombie()){
      std::cout << "File is not valid or does not exist!" << std::endl;
      //return -1;
   }

   TApplication app("RootFileBrowser",&argc,argv);
   TAppKillManager killer(app);
   TBrowser* browser=new TBrowser();
   std::cout << "start" << std::endl;
   app.Run();
   delete browser;
   file.Close();
   return 0;
}
