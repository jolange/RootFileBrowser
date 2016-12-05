#include <iostream>
#include <vector>

#include "TApplication.h"
#include "TBrowser.h"
#include "TFile.h"
#include "TObjArray.h"
#include "TObjString.h"
#include "TRootBrowser.h"
#include "TROOT.h"
#include "TString.h"
#include "TStyle.h"
#include "TSystem.h"
#include "TVirtualMutex.h"

#include "3rdParty/TAppKillManager.hpp"


static int  browse(int argc, char* argv[]);
static void getPathAndFilename(TString fullName,TString& path,TString& fileName);
static int  del(int argc, char* argv[]);

int main(int argc, char* argv[])
{
   std::string optDelete = "-d";
   if (argc > 3 && optDelete.compare(argv[1]) == 0)
      return del(argc-2,&argv[2]);
   return browse(argc,argv);
}

int browse(int argc, char* argv[])
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
   TBrowser browser;
   TRootBrowser* imp=(TRootBrowser*)browser.GetBrowserImp();
   killer.KillOnSignal(imp,"CloseWindow()");
   app.Run();
   for (TFile *file: vFiles) {
      file->Close();
      delete file;
   }
   return 0;
}

void getPathAndFilename(TString fullName,TString& path,TString& fileName)
{
   path="";
   fileName="";
   TObjArray* tokens = fullName.Tokenize("/");
   int i;
   for (i=0; i<tokens->GetEntries() -1; i++){
      path += ((TObjString*)(tokens->At(i)))->GetString() + "/";
   }
   fileName=((TObjString*)(tokens->At(i)))->GetString();
}

int del(int argc, char* argv[])
{
   TFile file(argv[0],"UPDATE");
   if (file.IsZombie()){
      std::cout << "File is not valid or does not exist:" << argv[0] << std::endl;
      return -1;
   }
   TString path;
   TString name;
   for (int i=1; i< argc; i++){
      std::cout << "deleting " << argv[i] << std::endl;
      getPathAndFilename(TString(argv[i])+";*",path,name);
      file.cd(path);
      gDirectory->Delete(name);
   }
   file.Close();
   return 0;
}
