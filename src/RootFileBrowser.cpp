#include <iostream>
#include <vector>

#include "TApplication.h"
#include "TBrowser.h"
#include "TRootBrowser.h"
#include "TFile.h"
#include "TStyle.h"

#include "3rdParty/TAppKillManager.hpp"

int main(int argc, char* argv[])
{
   if (argc == 1){
      std::cout << "Error: specifiy name of *.root file as parameter" << std::endl;
      return -1;
   }
   std::vector<TFile*> vFiles;
   std::string optNoStats = "-ns";
   for (int i=1; i<argc;i++){
      if (optNoStats.compare(argv[i]) == 0){
         gStyle->SetOptStat(0);
         continue;
      }
      TFile* file = new TFile(argv[i],"READ");
      if (file->IsZombie()){
         std::cout << "File is not valid or does not exist:" << argv[i] << std::endl;
         return -1;
      }
      vFiles.push_back(file);
   }

   gStyle->SetOptFit(111);
   TApplication app("RootFileBrowser",&argc,argv);
   TAppKillManager killer(app);
   TBrowser* browser=new TBrowser();
   TRootBrowser* imp=(TRootBrowser*)browser->GetBrowserImp();
   killer.KillOnSignal(imp,"CloseWindow()");
   app.Run();
   delete browser;
   std::vector<TFile*>::iterator file = vFiles.begin();
   for (;file!=vFiles.begin(); file++){
      (*file)->Close();
      delete (*file);
   }
   return 0;
}
