for(int i = 0; i < 200 && r - l > 1e-9; i++){
    double mid = l + (r - l) / (double)2;
    if(check(mid, obj, scores)) l = mid;
    else r = mid;
  }
