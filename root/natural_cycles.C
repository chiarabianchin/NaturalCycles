#include <TTree.h>
#include <TH2F.h>
#include <TF2.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TLatex.h>
#include <TCut.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TPaveText.h>

void natural_cycles(){

  gStyle->SetPalette(kLightTemperature);
  
  TTree *db = new TTree(); db->ReadFile("anafile_challenge_170522.csv", "Country/C:Age/I:NumBMI/F:Pill/C:NCbefore:FPlength:Weight/F:CycleVar/C:TempLogFreq/F:SexLogFreq:DaysTrying/I:CyclesTrying:ExitStatus/C:AnovCycles/I");

  // general look
  TCanvas *c_country = new TCanvas("c_country", "Countries");
  c_country->cd();
  db->Draw("Country");
  TCanvas *c_days = new TCanvas("c_days", "Days Trying");
  c_days->cd();
  db->Draw("DaysTrying");
  TCanvas *c_cicles = new TCanvas("c_cicles", "Cycles Trying");
  c_cicles->cd();
  db->Draw("CyclesTrying");
  TCanvas *c_weight = new TCanvas("c_weight", "Weight");
  c_weight->cd();
  db->Draw("Weight");
  TCanvas *c_bmi = new TCanvas("c_bmi", "NumBMI");
  c_bmi->cd();
  db->Draw("NumBMI");

  TCanvas *c_fpl = new TCanvas("c_fpl", "FPlength");
  c_fpl->cd();
  db->Draw("FPlength");

  TCanvas *c_tlogf = new TCanvas("c_tlogf", "Temperature logging frequency");
  c_tlogf->cd();
  db->Draw("TempLogFreq");

  // distributions for pregnant and trying
  TCut preg = TCut("ExitStatus==\"Pregnant\"");
  TCut right = TCut("ExitStatus==\"Right\"");
  TCut dout = TCut("ExitStatus==\"Dropout\"");
  
  TCanvas *c_days_cut = new TCanvas("c_days_cut", "Days Trying");
  c_days_cut->cd();
  db->Draw("DaysTrying", preg);
  gPad->ls();
  TH1F *hdays_trying_preg = (TH1F*)gPad->GetPrimitive("htemp");
  cout<<"Pointer" << hdays_trying_preg;
  hdays_trying_preg->SetNameTitle("hdays_trying_preg", "DaysTrying;Days Trying; Fraction per day");
  hdays_trying_preg->Scale(1./ hdays_trying_preg->Integral());
  hdays_trying_preg->SetMarkerStyle(kFullCircle);
  hdays_trying_preg->SetMarkerSize(1.6);
  hdays_trying_preg->SetMarkerColor(kGreen+2);
  
  db->Draw("DaysTrying", right, "sames");
  TH1F *hdays_trying_right = (TH1F*)gPad->GetPrimitive("htemp");
  hdays_trying_right->SetName("hdays_trying_right");
  cout<<"Pointer" << hdays_trying_right;
  hdays_trying_right->Scale(1./ hdays_trying_right->Integral());
  hdays_trying_right->SetMarkerStyle(kFullStar);
  hdays_trying_right->SetMarkerSize(1.6);
  hdays_trying_right->SetMarkerColor(kRed);

  
  db->Draw("DaysTrying", dout, "sames");
  TH1F *hdays_trying_dout = (TH1F*)gPad->GetPrimitive("htemp");
  hdays_trying_dout->SetName("hdays_trying_dout");
  hdays_trying_dout->Scale(1./ hdays_trying_dout->Integral());
  hdays_trying_dout->SetMarkerStyle(kOpenCircle);
  hdays_trying_dout->SetMarkerSize(1.6);
  hdays_trying_dout->SetMarkerColor(kOrange);

  
  TLegend *leg = new TLegend(0.3, 0.7, 0.6, 0.9, "Normalized to integral");
  leg->AddEntry(hdays_trying_preg, "Pregnant");
  leg->AddEntry(hdays_trying_right, "Right");
  leg->AddEntry(hdays_trying_dout, "Dropout");
  
  leg->Draw();

  TCanvas *c_cycles_cut = new TCanvas("c_cycles_cut", "Cycles Trying");
  c_cycles_cut->cd();
  db->Draw("CyclesTrying", preg);
  gPad->ls();
  TH1F *hcycles_trying_preg = (TH1F*)gPad->GetPrimitive("htemp");
  cout<<"Pointer" << hcycles_trying_preg;
  hcycles_trying_preg->SetNameTitle("hcycles_trying_preg", "Cycles Trying; Cycles Trying; Fraction per cycle");
  hcycles_trying_preg->Scale(1./ hcycles_trying_preg->Integral());
  hcycles_trying_preg->SetMarkerStyle(kFullCircle);
  hcycles_trying_preg->SetMarkerSize(1.6);
  hcycles_trying_preg->SetMarkerColor(kGreen+2);
  
  db->Draw("CyclesTrying", right, "sames");
  TH1F *hcycles_trying_right = (TH1F*)gPad->GetPrimitive("htemp");
  hcycles_trying_right->SetName("hcycles_trying_right");
  cout<<"Pointer" << hcycles_trying_right;
  hcycles_trying_right->Scale(1./ hcycles_trying_right->Integral());
  hcycles_trying_right->SetMarkerStyle(kFullStar);
  hcycles_trying_right->SetMarkerSize(1.6);
  hcycles_trying_right->SetMarkerColor(kRed);

  
  db->Draw("CyclesTrying", dout, "sames");
  TH1F *hcycles_trying_dout = (TH1F*)gPad->GetPrimitive("htemp");
  hcycles_trying_dout->SetName("hcycles_trying_dout");
  hcycles_trying_dout->Scale(1./ hcycles_trying_dout->Integral());
  hcycles_trying_dout->SetMarkerStyle(kOpenCircle);
  hcycles_trying_dout->SetMarkerSize(1.6);
  hcycles_trying_dout->SetMarkerColor(kOrange);
  leg->Draw();

  TH1F* h_int_preg =new  TH1F(*hcycles_trying_preg);
  h_int_preg->SetNameTitle("h_int_preg", "Cumulative integral");
  TH1F* h_int_right =new  TH1F(*hcycles_trying_right);
  h_int_right->SetName("h_int_right");
  TH1F* h_int_dout =new  TH1F(*hcycles_trying_dout);
  h_int_dout->SetName("h_int_dout");

  // look at the integral of eache class for different cuts in cycles trying
  Double_t c_p = 0;
  Double_t c_r = 0;
  Double_t c_d = 0;
  for(Int_t i=0; i<hcycles_trying_preg->GetNbinsX(); i++){
    c_p += hcycles_trying_preg->GetBinContent(i);
    c_r += hcycles_trying_right->GetBinContent(i);
    c_d += hcycles_trying_dout->GetBinContent(i);
      
    h_int_preg->SetBinContent(i,c_p);
    h_int_right->SetBinContent(i,c_r);
    h_int_dout->SetBinContent(i,c_d);
  }
  TCanvas *c_integral = new  TCanvas("c_integral");
  c_integral->cd();
  h_int_preg->Draw();
  h_int_right->Draw("sames");
  h_int_dout->Draw("sames");
  leg->Draw();
  
  TH1F* h_intdays_dout =new  TH1F(*hdays_trying_dout);
  h_intdays_dout->SetNameTitle("h_intdays_dout", "Days Trying;Days Trying; Cumulative integral of drop outs");
  c_d = 0;
  for(Int_t i=0; i<hdays_trying_dout->GetNbinsX(); i++){
    c_d += hdays_trying_dout->GetBinContent(i);
    h_intdays_dout->SetBinContent(i, c_d);
    
  }

  TCanvas *c_integral_days = new  TCanvas("c_integral_days");
  c_integral_days->cd();
  h_intdays_dout->Draw();

  // time trying vs age for pregnant women, trying dropout
  TCanvas *c_cycle_vs_age_preg = new TCanvas("c_cycle_vs_age_preg");
  db->Draw("CyclesTrying:Age", preg, "colz");
  TH2F* hcycle_vs_age_preg = (TH2F*)gPad->GetPrimitive("htemp");
  hcycle_vs_age_preg->SetNameTitle("hcycle_vs_age_preg", "Pregnant");
  //projection selecting the fisrt two cycles
  TH1F* hproj_age_pred = (TH1F*)hcycle_vs_age_preg->ProjectionX("hproj_age_pred", 1, 2);
  hproj_age_pred->SetTitle("");
  TPad *pad_inset_pjx = new TPad("pad_inset_pjx", "", 0.6, 0.5, 0.9, 0.9);
  pad_inset_pjx->Draw();
  pad_inset_pjx->cd();
  hproj_age_pred->Draw();
  //TPad *stat_pjx = new TPad("stat_pjx", "", 0.6, 0.5, 0.9, 0.9);
  //stat_pjx->Draw();
  TPaveText *text_stat = new TPaveText(0.4, 0.6, 0.9,0.98, "NDC");
  text_stat->AddText(TString::Format("#splitline{N cycles = [1, 2]}{#splitline{#mu = %.1f y}{#sigma = %.1f y}}", hproj_age_pred->GetMean(), hproj_age_pred->GetRMS()));
  text_stat->SetFillStyle(0);
  text_stat->SetBorderSize(0);
  text_stat->DrawClone();
  
  
  TCanvas *c_cycle_vs_age_right = new TCanvas("c_cycle_vs_age_right");
  db->Draw("CyclesTrying:Age", right, "colz");
  TH2F* hcycle_vs_age_right = (TH2F*)gPad->GetPrimitive("htemp");
  hcycle_vs_age_right->SetNameTitle("hcycle_vs_age_right", "Right");
  //projection selecting the all cycles
  TH1F* hproj_age_right = (TH1F*)hcycle_vs_age_right->ProjectionX("hproj_age_right", 0, -1);
  hproj_age_right->SetTitle("");
  TPad *pad_inset_pjx_r = new TPad("pad_inset_pjx_r", "", 0.6, 0.5, 0.9, 0.9);
  pad_inset_pjx_r->Draw();
  pad_inset_pjx_r->cd();
  hproj_age_right->Draw();
  //TPad *stat_pjx = new TPad("stat_pjx", "", 0.6, 0.5, 0.9, 0.9);
  //stat_pjx->Draw();
  TPaveText *text_stat_r = new TPaveText(0.4, 0.6, 0.9,0.98, "NDC");
  text_stat_r->AddText(TString::Format("#splitline{N cycles = all}{#splitline{#mu = %.1f y}{#sigma = %.1f y}}", hproj_age_right->GetMean(), hproj_age_right->GetRMS()));
  text_stat_r->SetFillStyle(0);
  text_stat_r->SetBorderSize(0);
  text_stat_r->DrawClone();
  
  TCanvas *c_cycle_vs_age_dout = new TCanvas("c_cycle_vs_age_dout");
  db->Draw("CyclesTrying:Age", dout, "colz");
  TH2F* hcycle_vs_age_dout = (TH2F*)gPad->GetPrimitive("htemp");
  hcycle_vs_age_dout->SetNameTitle("hcycle_vs_age_dout", "Drop out");
  //projection selecting the the first cycle
  TH1F* hproj_age_dout = (TH1F*)hcycle_vs_age_dout->ProjectionX("hproj_age_dout", 0, -1);
  hproj_age_dout->SetTitle("");
  TPad *pad_inset_pjx_d = new TPad("pad_inset_pjx_d", "", 0.6, 0.5, 0.9, 0.9);
  pad_inset_pjx_d->Draw();
  pad_inset_pjx_d->cd();
  hproj_age_dout->Draw();
  //TPad *stat_pjx = new TPad("stat_pjx", "", 0.6, 0.5, 0.9, 0.9);
  //stat_pjx->Draw();
  TPaveText *text_stat_d = new TPaveText(0.4, 0.6, 0.9,0.98, "NDC");
  text_stat_d->AddText(TString::Format("#splitline{N cycles = all}{#splitline{#mu = %.1f y}{#sigma = %.1f y}}", hproj_age_dout->GetMean(), hproj_age_dout->GetRMS()));
  text_stat_d->SetFillStyle(0);
  text_stat_d->SetBorderSize(0);
  text_stat_d->DrawClone();
  
  // anovulary cycles
  TCut anov_g0 = TCut("AnovCycles>-1");
  TCanvas *c_anov = new TCanvas("c_anov");
  db->Draw("AnovCycles", preg+anov_g0);
  TH1F* hanov_preg = (TH1F*)gPad->GetPrimitive("htemp");
  hanov_preg->SetNameTitle("hanov_preg", "Anovulatory Cycles; # anovulatory cycles; fraction of the population");
  hanov_preg->Scale(1./ hanov_preg->Integral());
  hanov_preg->SetMarkerStyle(kFullCircle);
  hanov_preg->SetMarkerSize(1.6);
  hanov_preg->SetMarkerColor(kGreen+2);

  db->Draw("AnovCycles", right+anov_g0, "sames");
  TH1F* hanov_right = (TH1F*)gPad->GetPrimitive("htemp");
  hanov_right->SetNameTitle("hanov_right", "Anovulatory Cycles; # anovulatory cycles; fraction of the population");
  hanov_right->Scale(1./ hanov_right->Integral());
  hanov_right->SetMarkerStyle(kFullStar);
  hanov_right->SetMarkerSize(1.6);
  hanov_right->SetMarkerColor(kRed);

  db->Draw("AnovCycles", dout+anov_g0, "sames");
  TH1F* hanov_dout = (TH1F*)gPad->GetPrimitive("htemp");
  hanov_dout->SetNameTitle("hanov_dout", "Anovulatory Cycles; # anovulatory cycles; fraction of the population");
  hanov_dout->Scale(1./ hanov_dout->Integral());
  hanov_dout->SetMarkerStyle(kOpenCircle);
  hanov_dout->SetMarkerSize(1.6);
  hanov_dout->SetMarkerColor(kOrange);
  leg->Draw();
  
  
  
}
