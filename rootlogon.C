{
    TString dir="build/";

     gSystem->Load( dir + "libBaseFlow.so");
     gSystem->Load( dir + "libdiffflow.so");
     gSystem->Load( dir + "libcorrelationflow.so");
     gSystem->Load( dir + "/QnCorrections/libqncorrflow.so");
//    gSystem->Load( "/lustre/nyx/cbm/users/klochkov/soft/DataTree/build/libDataTree.so");
}
