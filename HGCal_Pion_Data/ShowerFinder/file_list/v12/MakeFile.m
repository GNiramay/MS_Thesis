## Script to change path of every text file availabel

OLD="/afs/cern.ch/work/s/spandey/public/hgcal/2018_TB/OctoberTB/hgcal_ahcal_samples/";
NEW="/eos/user/s/spandey/HGCalTB/OctTB/hgcal_ahcal_samples/v12_v2/";

ENR=[300,250,200,120,100,80,50,20];

## for ee = ENR
##   ee
##   F1=fopen(sprintf("OldFilePaths/pion%i_config1.txt",ee),'r'); # For All files
##   F2=fopen(sprintf("pion%i_config1.txt",ee),'w'); # For All files
##   while ~feof(F1)
##     AA=fgetl(F1);
##     PATH=sprintf("%s%s",NEW,AA(length(OLD):length(AA)));
##   fprintf(F2,"%s\n",PATH);
##   end
##   fclose(F1);
##   fclose(F2);
## end

ENR=[300,250,200,100,50,20];

for ee = ENR
  ee
  F1=fopen(sprintf("OldFilePaths/pion%i_config1_one_file.txt",ee),'r'); # For one file
  F2=fopen(sprintf("pion%i_config1_one_file.txt",ee),'w'); # For one file
  while ~feof(F1)
    AA=fgetl(F1)
    PATH=sprintf("%s%s",NEW,AA(length(OLD):length(AA)));
    fprintf(F2,"%s\n",PATH);
  end
  fclose(F1);
  fclose(F2);
  ee
end
