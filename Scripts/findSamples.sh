#declare -a arr=("Sherpa_CT10_eegammaPt10_35" "Sherpa_CT10_mumugammaPt10_35" "Sherpa_CT10_enugammaPt35_70" "Sherpa_CT10_enugammaPt70_140" "Sherpa_CT10_enugammaPt140" "Sherpa_CT10_munugammaPt35_70" "Sherpa_CT10_munugammaPt70_140" "Sherpa_CT10_munugammaPt140" "Sherpa_CT10_taunugammaPt35_70" "Sherpa_CT10_taunugammaPt70_140" "Sherpa_CT10_taunugammaPt140" "Sherpa_CT10_eegammaPt35_70" "Sherpa_CT10_eegammaPt70_140" "Sherpa_CT10_eegammaPt140" "Sherpa_CT10_mumugammaPt35_70" "Sherpa_CT10_mumugammaPt70_140" "Sherpa_CT10_mumugammaPt140" "Sherpa_CT10_tautaugammaPt35_70" "Sherpa_CT10_tautaugammaPt70_140 0.38482" "Sherpa_CT10_tautaugammaPt140" "Sherpa_CT10_nunugammaPt35_70" "Sherpa_CT10_nunugammaPt70_140" "Sherpa_CT10_nunugammaPt140")

declare -a arr=()
for i in {363364..363387}; do arr+=($i); done
for i in {363388..363411}; do arr+=($i); done
for i in {363102..363122}; do arr+=($i); done

for i in "${arr[@]}"
do
	rucio list-dids "mc15_13TeV:*$i*SUSY2*p2470"
done
