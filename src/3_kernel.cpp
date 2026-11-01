#include <ap_int.h>
#define LEN 16
void bubble_sort(ap_int<16> in[LEN], ap_int<16> out[LEN]){
#pragma HLS ARRAY_PARTITION variable=in block factor=4 dim=0
#pragma HLS ARRAY_PARTITION variable=out block factor=4 dim=0
    ap_int<16> tmp[LEN];
    for(int i=0;i<LEN;i++) tmp[i]=in[i];
    for(int i=0;i<LEN-1;i++){
        for(int j=0;j<LEN-1-i;j++){
#pragma HLS PIPELINE II=1
            if(tmp[j]>tmp[j+1]){
                ap_int<16> t=tmp[j];
                tmp[j]=tmp[j+1];
                tmp[j+1]=t;
            }
        }
    }
    for(int i=0;i<LEN;i++) out[i]=tmp[i];
}