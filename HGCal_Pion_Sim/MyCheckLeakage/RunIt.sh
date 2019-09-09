cmsenv
make

# ./analyzeHGCOctTB file_list/sim_pion_100.txt TempOut.root data alpha 200
# ./analyzeHGCOctTB file_list/sim_pion_200.txt TempOut.root sim alpha 200

############### Just for testing
# ./analyzeHGCOctTB file_list/sim_pion_200.txt TempOut.root sim alpha 200

############### All energies
./analyzeHGCOctTB file_list/sim_pion_300.txt Pion_Sim_300_temp.root sim alpha 300
./analyzeHGCOctTB file_list/sim_pion_250.txt Pion_Sim_250_temp.root sim alpha 250
./analyzeHGCOctTB file_list/sim_pion_200.txt Pion_Sim_200_temp.root sim alpha 200
./analyzeHGCOctTB file_list/sim_pion_120.txt Pion_Sim_120_temp.root sim alpha 120
./analyzeHGCOctTB file_list/sim_pion_100.txt Pion_Sim_100_temp.root sim alpha 100
./analyzeHGCOctTB file_list/sim_pion_80.txt Pion_Sim_80_temp.root sim alpha 80
./analyzeHGCOctTB file_list/sim_pion_50.txt Pion_Sim_50_temp.root sim alpha 50
./analyzeHGCOctTB file_list/sim_pion_20.txt Pion_Sim_20_temp.root sim alpha 20
