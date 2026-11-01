#include <stdio.h>
#include <ap_int.h>
#define LEN 16
void bubble_sort(ap_int<16> in[LEN], ap_int<16> out[LEN]);
int main(){
    ap_int<16> din[LEN],dout[LEN],ref[LEN];
    for(int i=0;i<LEN;i++) din[i]=(LEN-i)%32;
    for(int i=0;i<LEN;i++) ref[i]=din[i];
    for(int i=0;i<LEN-1;i++){
        for(int j=0;j<LEN-1-i;j++){
            if(ref[j]>ref[j+1]){
                ap_int<16> t=ref[j];ref[j]=ref[j+1];ref[j+1]=t;
            }
        }
    }
    bubble_sort(din,dout);
    bool ok=true;
    for(int i=0;i<LEN;i++){
        if(dout[i]!=ref[i]){
            printf("Sort fail at %d exp=%d get=%d\n", i, (int)ref[i], (int)dout[i]);
            ok=false;
            break;
        }
    }
    if(ok) printf("All tests passed!\n");
    return ok?0:-1;
}