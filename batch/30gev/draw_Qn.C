void draw_Qn()
{
    TFile *file_RAW = TFile::Open("qn_13agev_raw.root");
    TFile *file_REC = TFile::Open("qn_13agev_rec.root");
    TFile *file_TWIST_RESCALE = TFile::Open("qn_13agev_tw_res.root");
    TTree *QnVectorTest_RAW = (TTree*)file_RAW->Get("QnVectorTest");
    TTree *QnVectorTest_REC = (TTree*)file_REC->Get("QnVectorTest");
    TTree *QnVectorTest_TWIST_RESCALE = (TTree*)file_TWIST_RESCALE->Get("QnVectorTest");

    TTree *DrawTree = QnVectorTest_TWIST_RESCALE;
    TCanvas *c1_CORR = new TCanvas("c1_CORR","c1_CORR",600,600);
    TProfile *corr_tpc_Y_bin6_Qy_psd_Qy_step1_TWIST_RESCALE = new TProfile("corr_tpc_Y_bin6_Qy_psd_Qy_step1_TWIST_RESCALE","corr_tpc_Y_bin6_Qy_psd_Qy_step1_TWIST_RESCALE",5,0,100);
    TProfile *corr_tpc_Y_bin6_Qx_psd_Qx_step1_TWIST_RESCALE = new TProfile("corr_tpc_Y_bin6_Qx_psd_Qx_step1_TWIST_RESCALE","corr_tpc_Y_bin6_Qx_psd_Qx_step1_TWIST_RESCALE",5,0,100);
    TProfile *corr_tpc_Y_bin6_Qx_psd_Qy_step1_TWIST_RESCALE = new TProfile("corr_tpc_Y_bin6_Qx_psd_Qy_step1_TWIST_RESCALE","corr_tpc_Y_bin6_Qx_psd_Qy_step1_TWIST_RESCALE",5,0,100);
    TProfile *corr_tpc_Y_bin6_Qy_psd_Qx_step1_TWIST_RESCALE = new TProfile("corr_tpc_Y_bin6_Qy_psd_Qx_step1_TWIST_RESCALE","corr_tpc_Y_bin6_Qy_psd_Qx_step1_TWIST_RESCALE",5,0,100);
    corr_tpc_Y_bin6_Qy_psd_Qy_step1_TWIST_RESCALE->SetLineColor(kRed);
    corr_tpc_Y_bin6_Qx_psd_Qx_step1_TWIST_RESCALE->SetLineColor(kBlue);
    corr_tpc_Y_bin6_Qx_psd_Qy_step1_TWIST_RESCALE->SetLineColor(kGreen+2);
    corr_tpc_Y_bin6_Qy_psd_Qx_step1_TWIST_RESCALE->SetLineColor(kMagenta);
    corr_tpc_Y_bin6_Qy_psd_Qy_step1_TWIST_RESCALE->SetMarkerColor(kRed);
    corr_tpc_Y_bin6_Qx_psd_Qx_step1_TWIST_RESCALE->SetMarkerColor(kBlue);
    corr_tpc_Y_bin6_Qx_psd_Qy_step1_TWIST_RESCALE->SetMarkerColor(kGreen+2);
    corr_tpc_Y_bin6_Qy_psd_Qx_step1_TWIST_RESCALE->SetMarkerColor(kMagenta);
    corr_tpc_Y_bin6_Qy_psd_Qy_step1_TWIST_RESCALE->SetMarkerStyle(20);
    corr_tpc_Y_bin6_Qx_psd_Qx_step1_TWIST_RESCALE->SetMarkerStyle(21);
    corr_tpc_Y_bin6_Qx_psd_Qy_step1_TWIST_RESCALE->SetMarkerStyle(22);
    corr_tpc_Y_bin6_Qy_psd_Qx_step1_TWIST_RESCALE->SetMarkerStyle(23);
    DrawTree->Draw("tpc_Y.fCorrectedVector[6].Qy(2)*psd.fCorrectedVector[2].Qy(2):fCentrality>>corr_tpc_Y_bin6_Qy_psd_Qy_step1_TWIST_RESCALE","tpc_Y.fCorrectedVector[6].fSumW!=0","profile,e1,p,X0");
    DrawTree->Draw("tpc_Y.fCorrectedVector[6].Qx(2)*psd.fCorrectedVector[2].Qx(2):fCentrality>>corr_tpc_Y_bin6_Qx_psd_Qx_step1_TWIST_RESCALE","tpc_Y.fCorrectedVector[6].fSumW!=0","profile,same,e1,p,X0");
    DrawTree->Draw("tpc_Y.fCorrectedVector[6].Qx(2)*psd.fCorrectedVector[2].Qy(2):fCentrality>>corr_tpc_Y_bin6_Qx_psd_Qy_step1_TWIST_RESCALE","tpc_Y.fCorrectedVector[6].fSumW!=0","profile,same,e1,p,X0");
    DrawTree->Draw("tpc_Y.fCorrectedVector[6].Qy(2)*psd.fCorrectedVector[2].Qx(2):fCentrality>>corr_tpc_Y_bin6_Qy_psd_Qx_step1_TWIST_RESCALE","tpc_Y.fCorrectedVector[6].fSumW!=0","profile,same,e1,p,X0");

    TProfile *corr_tpc_Y_bin6_Qx_step1_TWIST_RESCALE = new TProfile("corr_tpc_Y_bin6_Qx_step1_TWIST_RESCALE","corr_tpc_Y_bin6_Qx_step1_TWIST_RESCALE",5,0,100);
    TProfile *corr_tpc_Y_bin6_Qy_step1_TWIST_RESCALE = new TProfile("corr_tpc_Y_bin6_Qy_step1_TWIST_RESCALE","corr_tpc_Y_bin6_Qy_step1_TWIST_RESCALE",5,0,100);
    TProfile *corr_psd_Qx_step1_TWIST_RESCALE = new TProfile("corr_psd_Qx_step1_TWIST_RESCALE","corr_psd_Qx_step1_TWIST_RESCALE",5,0,100);
    TProfile *corr_psd_Qy_step1_TWIST_RESCALE = new TProfile("corr_psd_Qy_step1_TWIST_RESCALE","corr_psd_Qy_step1_TWIST_RESCALE",5,0,100);
    corr_tpc_Y_bin6_Qx_step1_TWIST_RESCALE->SetLineColor(kRed);
    corr_tpc_Y_bin6_Qy_step1_TWIST_RESCALE->SetLineColor(kBlue);
    corr_psd_Qx_step1_TWIST_RESCALE->SetLineColor(kGreen+2);
    corr_psd_Qy_step1_TWIST_RESCALE->SetLineColor(kMagenta);
    corr_tpc_Y_bin6_Qx_step1_TWIST_RESCALE->SetMarkerColor(kRed);
    corr_tpc_Y_bin6_Qy_step1_TWIST_RESCALE->SetMarkerColor(kBlue);
    corr_psd_Qx_step1_TWIST_RESCALE->SetMarkerColor(kGreen+2);
    corr_psd_Qy_step1_TWIST_RESCALE->SetMarkerColor(kMagenta);
    corr_tpc_Y_bin6_Qx_step1_TWIST_RESCALE->SetMarkerStyle(20);
    corr_tpc_Y_bin6_Qy_step1_TWIST_RESCALE->SetMarkerStyle(21);
    corr_psd_Qx_step1_TWIST_RESCALE->SetMarkerStyle(22);
    corr_psd_Qy_step1_TWIST_RESCALE->SetMarkerStyle(23);
    TCanvas *c1_REC = new TCanvas("c1_REC","c1_REC",600,600);
    DrawTree->Draw("tpc_Y.fCorrectedVector[6].Qx(2):fCentrality>>corr_tpc_Y_bin6_Qx_step1_TWIST_RESCALE","tpc_Y.fCorrectedVector[6].fSumW!=0","profile,e1,p,X0");
    DrawTree->Draw("tpc_Y.fCorrectedVector[6].Qy(2):fCentrality>>corr_tpc_Y_bin6_Qy_step1_TWIST_RESCALE","tpc_Y.fCorrectedVector[6].fSumW!=0","profile,same,e1,p,X0");
    DrawTree->Draw("psd.fCorrectedVector[2].Qx(2):fCentrality>>corr_psd_Qx_step1_TWIST_RESCALE","tpc_Y.fCorrectedVector[6].fSumW!=0","profile,same,e1,p,X0");
    DrawTree->Draw("psd.fCorrectedVector[2].Qy(2):fCentrality>>corr_psd_Qy_step1_TWIST_RESCALE","tpc_Y.fCorrectedVector[6].fSumW!=0","profile,same,e1,p,X0");


return;

    TCanvas *c1_TPC_6 = new TCanvas("c1_TPC_6","",1800,600);
    c1_TPC_6->Divide(3,1);
    file_RAW->cd();
    c1_TPC_6->cd(1);
    QnVectorTest_RAW->Draw("tpc_Y.fCorrectedVector[6].Qy(1):tpc_Y.fCorrectedVector[6].Qx(1)>>tpc_Y_bin6_Qx_Qy_cent_gt40_step1_RAW(1000,-1.1,1.1,1000,-1.1,1.1)","fCentrality<=20 && tpc_Y.fCorrectedVector[6].fSumW!=0","colz");

    file_REC->cd();
    c1_TPC_6->cd(2);
    QnVectorTest_REC->Draw("tpc_Y.fCorrectedVector[6].Qy(1):tpc_Y.fCorrectedVector[6].Qx(1)>>tpc_Y_bin6_Qx_Qy_cent_gt40_step1_REC(1000,-1.1,1.1,1000,-1.1,1.1)","fCentrality<=20 && tpc_Y.fCorrectedVector[6].fSumW!=0","colz");

    file_TWIST_RESCALE->cd();
    c1_TPC_6->cd(3);
    QnVectorTest_TWIST_RESCALE->Draw("tpc_Y.fCorrectedVector[6].Qy(1):tpc_Y.fCorrectedVector[6].Qx(1)>>tpc_Y_bin6_Qx_Qy_cent_gt40_step1_TWIST_RESCALE(1000,-1.1,1.1,1000,-1.1,1.1)","fCentrality<=20 && tpc_Y.fCorrectedVector[6].fSumW!=0","colz");


    TCanvas *c1_TPC_10 = new TCanvas("c1_TPC_10","",1800,600);
    c1_TPC_10->Divide(3,1);
    file_RAW->cd();
    c1_TPC_10->cd(1);
    QnVectorTest_RAW->Draw("tpc_Y.fCorrectedVector[10].Qy(1):tpc_Y.fCorrectedVector[10].Qx(1)>>tpc_Y_bin10_Qx_Qy_cent_gt40_step1_RAW(1000,-1.1,1.1,1000,-1.1,1.1)","fCentrality<=20 && tpc_Y.fCorrectedVector[10].fSumW!=0","colz");

    file_REC->cd();
    c1_TPC_10->cd(2);
    QnVectorTest_REC->Draw("tpc_Y.fCorrectedVector[10].Qy(1):tpc_Y.fCorrectedVector[10].Qx(1)>>tpc_Y_bin10_Qx_Qy_cent_gt40_step1_REC(1000,-1.1,1.1,1000,-1.1,1.1)","fCentrality<=20 && tpc_Y.fCorrectedVector[10].fSumW!=0","colz");

    file_TWIST_RESCALE->cd();
    c1_TPC_10->cd(3);
    QnVectorTest_TWIST_RESCALE->Draw("tpc_Y.fCorrectedVector[10].Qy(1):tpc_Y.fCorrectedVector[10].Qx(1)>>tpc_Y_bin10_Qx_Qy_cent_gt40_step1_TWIST_RESCALE(1000,-1.1,1.1,1000,-1.1,1.1)","fCentrality<=20 && tpc_Y.fCorrectedVector[10].fSumW!=0","colz");


    TCanvas *c1_PSD_1 = new TCanvas("c1_PSD_1","",1800,600);
    c1_PSD_1->Divide(3,1);
    file_RAW->cd();
    c1_PSD_1->cd(1);
    QnVectorTest_RAW->Draw("psd.fCorrectedVector[0].Qy(1):psd.fCorrectedVector[0].Qx(1)>>VCAL_Qx_Qy_cent_gt40_step1_RAW(1000,-1.1,1.1,1000,-1.1,1.1)","fCentrality<=20","colz");

    file_REC->cd();
    c1_PSD_1->cd(2);
    QnVectorTest_REC->Draw("psd.fCorrectedVector[0].Qy(1):psd.fCorrectedVector[0].Qx(1)>>VCAL_Qx_Qy_cent_gt40_step1_REC(1000,-1.1,1.1,1000,-1.1,1.1)","fCentrality<=20","colz");

    file_TWIST_RESCALE->cd();
    c1_PSD_1->cd(3);
    QnVectorTest_TWIST_RESCALE->Draw("psd.fCorrectedVector[0].Qy(1):psd.fCorrectedVector[0].Qx(1)>>VCAL_Qx_Qy_cent_gt40_step1_TWIST_RESCALE(1000,-1.1,1.1,1000,-1.1,1.1)","fCentrality<=20","colz");

    TCanvas *c1_PSD_2 = new TCanvas("c1_PSD_2","",1800,600);
    c1_PSD_2->Divide(3,1);
    file_RAW->cd();
    c1_PSD_2->cd(1);
    QnVectorTest_RAW->Draw("psd.fCorrectedVector[1].Qy(1):psd.fCorrectedVector[1].Qx(1)>>RCAL1_Qx_Qy_cent_gt40_step1_RAW(1000,-1.1,1.1,1000,-1.1,1.1)","fCentrality<=20","colz");

    file_REC->cd();
    c1_PSD_2->cd(2);
    QnVectorTest_REC->Draw("psd.fCorrectedVector[1].Qy(1):psd.fCorrectedVector[1].Qx(1)>>RCAL1_Qx_Qy_cent_gt40_step1_REC(1000,-1.1,1.1,1000,-1.1,1.1)","fCentrality<=20","colz");

    file_TWIST_RESCALE->cd();
    c1_PSD_2->cd(3);
    QnVectorTest_TWIST_RESCALE->Draw("psd.fCorrectedVector[1].Qy(1):psd.fCorrectedVector[1].Qx(1)>>RCAL1_Qx_Qy_cent_gt40_step1_TWIST_RESCALE(1000,-1.1,1.1,1000,-1.1,1.1)","fCentrality<=20","colz");


    TCanvas *c1_PSD_3 = new TCanvas("c1_PSD_3","",1800,600);
    c1_PSD_3->Divide(3,1);
    file_RAW->cd();
    c1_PSD_3->cd(1);
    QnVectorTest_RAW->Draw("psd.fCorrectedVector[2].Qy(1):psd.fCorrectedVector[2].Qx(1)>>RCAL2_Qx_Qy_cent_gt40_step1_RAW(1000,-1.1,1.1,1000,-1.1,1.1)","fCentrality<=20","colz");

    file_REC->cd();
    c1_PSD_3->cd(2);
    QnVectorTest_REC->Draw("psd.fCorrectedVector[2].Qy(1):psd.fCorrectedVector[2].Qx(1)>>RCAL2_Qx_Qy_cent_gt40_step1_REC(1000,-1.1,1.1,1000,-1.1,1.1)","fCentrality<=20","colz");

    file_TWIST_RESCALE->cd();
    c1_PSD_3->cd(3);
    QnVectorTest_TWIST_RESCALE->Draw("psd.fCorrectedVector[2].Qy(1):psd.fCorrectedVector[2].Qx(1)>>RCAL2_Qx_Qy_cent_gt40_step1_TWIST_RESCALE(1000,-1.1,1.1,1000,-1.1,1.1)","fCentrality<=20","colz");

    c1_TPC_6->SaveAs("data/NA61/figures/fig_TPC_6.C");
    c1_TPC_6->SaveAs("data/NA61/figures/fig_TPC_6.png");
    c1_TPC_6->SaveAs("data/NA61/figures/fig_TPC_6.pdf");

    c1_TPC_10->SaveAs("data/NA61/figures/fig_TPC_10.C");
    c1_TPC_10->SaveAs("data/NA61/figures/fig_TPC_10.png");
    c1_TPC_10->SaveAs("data/NA61/figures/fig_TPC_10.pdf");

    c1_PSD_1->SaveAs("data/NA61/figures/fig_PSD_1.C");
    c1_PSD_1->SaveAs("data/NA61/figures/fig_PSD_1.png");
    c1_PSD_1->SaveAs("data/NA61/figures/fig_PSD_1.pdf");
    c1_PSD_2->SaveAs("data/NA61/figures/fig_PSD_2.C");
    c1_PSD_2->SaveAs("data/NA61/figures/fig_PSD_2.png");
    c1_PSD_2->SaveAs("data/NA61/figures/fig_PSD_2.pdf");
    c1_PSD_3->SaveAs("data/NA61/figures/fig_PSD_3.C");
    c1_PSD_3->SaveAs("data/NA61/figures/fig_PSD_3.png");
    c1_PSD_3->SaveAs("data/NA61/figures/fig_PSD_3.pdf");
}
