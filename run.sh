#taskset -c 6 ./l2_prefetcher_ev $1 &
#taskset -c 5 ./l2_prefetcher_ev $1 &
taskset -c 5 ./l2_prefetcher_ev &
taskset -c 4 ./l2_prefetcher_ac_s $1  &>> result2.log
