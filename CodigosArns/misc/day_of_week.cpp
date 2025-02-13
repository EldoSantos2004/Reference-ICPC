int dayOfWeek(int d, int m, lli y){
	if(m == 1 || m == 2){
		m += 12;
		--y;
	}
	int k = y % 100;
	lli j = y / 100;
	return (d + 13*(m+1)/5 + k + k/4 + j/4 + 5*j) % 7;
}
