#include <iostream>
#include <vector>

#include "TSystem.h"
#include "TApplication.h"
#include "TBrowser.h"
#include "TRootBrowser.h"
#include "TFile.h"
#include "TVirtualMutex.h"
#include "TStyle.h"
#include "TString.h"
#include "TROOT.h"

#include "3rdParty/TAppKillManager.hpp"

int main(int argc, char* argv[])
{
   std::vector<TFile*> vFiles;
   std::string optNoStats = "-ns";
   std::string optStyle = "-s";
   int iStyleArg = -1;
   for (int i=1; i<argc;i++){
      if (optNoStats.compare(argv[i]) == 0){
         gStyle->SetOptStat(0);
         continue;
      }
      if (optStyle.compare(argv[i]) == 0){
         iStyleArg = ++i;
         continue;
      }
      TFile* file = new TFile(argv[i],"READ");
      if (file->IsZombie()){
         std::cout << "File is not valid or does not exist:" << argv[i] << std::endl;
         return -1;
      }
      vFiles.push_back(file);
   }

   if (iStyleArg != -1 && !vFiles.empty()){ // otherwise strange errors, if no files
      if (iStyleArg >= argc){
         std::cout << "specify style file after '-s'!" << std::endl;
         return -1;      
      }
      gROOT->Macro(argv[iStyleArg]);
   }
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
