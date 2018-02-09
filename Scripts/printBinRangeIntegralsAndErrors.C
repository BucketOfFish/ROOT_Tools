float data = 0;
float diboson = 0;
float top = 0;
float fs = 0;
float zjets = 0;
float wjets = 0;
float other = 0;
float dataErr = 0;
float dibosonErr = 0;
float topErr = 0;
float fsErr = 0;
float zjetsErr = 0;
float wjetsErr = 0;
float otherErr = 0;
for(int i=3; i<=7; i++) {
data += hist_data->GetBinContent(i);
diboson += hist_Diboson->GetBinContent(i);
dibosonErr += pow(hist_Diboson->GetBinError(i),2);
//top += hist_Top->GetBinContent(i);
//topErr += pow(hist_Top->GetBinError(i),2);
fs += hist_Flav__Sym_->GetBinContent(i);
fsErr += pow(hist_Flav__Sym_->GetBinError(i),2);
zjets += hist_Zjets->GetBinContent(i);
zjetsErr += pow(hist_Zjets->GetBinError(i),2);
wjets += hist_Wjets->GetBinContent(i);
wjetsErr += pow(hist_Wjets->GetBinError(i),2);
other += hist_Other->GetBinContent(i);
otherErr += pow(hist_Other->GetBinError(i),2);
}
dibosonErr = pow(dibosonErr,0.5);
topErr = pow(topErr,0.5);
fsErr = pow(fsErr,0.5);
zjetsErr = pow(zjetsErr,0.5);
wjetsErr = pow(wjetsErr,0.5);
otherErr = pow(otherErr,0.5);
data
diboson
dibosonErr
top
topErr
fs
fsErr
zjets
zjetsErr
wjets
wjetsErr
other
otherErr
