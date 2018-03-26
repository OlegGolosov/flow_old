
{
    TString dir="/lustre/nyx/cbm/users/klochkov/FlowAnalysis/build/";

    gSystem->Load( dir + "QnCorrections/libQnCorrections.so");
    gSystem->Load( dir + "DataTree/libDataTree.so" );
//     gSystem->Load( dir + "QnAnalysisLukas/libQnAnalysisLukas.so");
    gSystem->Load( dir + "QnAnalysis/libQnAnalysis.so");
// 
}
