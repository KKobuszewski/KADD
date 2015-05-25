TH1F *hct10;
     TH1F *hmstw;
     TH1F *hnnpdf;
     TH1F *  hcteq;
..
..
..
..

     TH1F *herrorpos[7];
     TH1F *herrorneg[7];
     TH1F *h1[7];
     TH1F *h2[7];

     h1[1]= (TH1F*) hct10->Clone();
     h1[2]= (TH1F*) hct10->Clone();
     h1[3]= (TH1F*) hct10->Clone();
     h1[4]= (TH1F*) hmstw->Clone();
     h1[5]= (TH1F*) hmstw->Clone();
     h1[6]= (TH1F*) hnnpdf->Clone();

     h2[1]= (TH1F*) hmstw->Clone();
     h2[2]= (TH1F*) hnnpdf->Clone();
     h2[3]= (TH1F*) hcteq->Clone();
     h2[4]= (TH1F*) hnnpdf->Clone();
     h2[5]= (TH1F*) hcteq->Clone();
     h2[6]= (TH1F*) hcteq->Clone();

     for (int k=1 ; k<7 ; k++) // loop of array histogram
       {
      double er_pos[10];
           double er_neg[10];
           for (int i=1 ; i<10 ; i++) // loop of bin
       { 

          double Content1 = h1[k]->GetBinContent(i);
               double Content2 = h2[k]->GetBinContent(i);
               double diff = Content1-Content2 ;
               double Erreur_relatif = (diff/Content1)*100;

               er_pos= +Erreur_relatif;
               er_neg= - Erreur_relatif;
               cout << " + error  = " <<  er_pos << "%" <<endl;
               cout << " - error = " <<  er_neg << "%" <<endl;     
      // i want to fill and to plot the new histogram of the erreur relatif ....
               herrorpos[k]->SetBinContent(i,er_pos);
               herrorneg[k]->SetBinContent(i,er_neg);
              }
           
   herrorpos[k]->Draw("");
        herrorneg[k]->Draw("same");

       }