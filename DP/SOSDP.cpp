for(int i = 1; i < (1 << sz); i++){
    for(int j = 1; j <= sz; j++){
        if((i >> (j - 1)) & 1){
            dpOr[i][j] = dpOr[i][j - 1] + dpOr[i ^ (1 << (j - 1))][j - 1];  // ekhane j - 1 diye j - 1th bit sorache abar ager value theke ana hoche, ekhane j, 1 based ei jonne value soranor time a j - 1 kora hoise
        }
        else{dpOr[i][j] = dpOr[i][j - 1];}
    }
}
for(int i = (1 << sz) - 1; i > 0; i--){     // ekhane loop ulta dik diye cholse karon [i ^ (1 << (j - 1))] eta boro value te jeye value niye ashe, tai boro gulo age calculate korte hobe
    for(int j = 1; j <= sz; j++){
        if((i >> (j - 1)) & 1){dpAnd[i][j] = dpAnd[i][j - 1];}
        else{
            dpAnd[i][j] = dpAnd[i][j - 1] + dpAnd[i ^ (1 << (j - 1))][j - 1];  
        }
    }
}