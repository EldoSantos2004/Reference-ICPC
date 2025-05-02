point centroid(vector<point> & P){
	point num;
	ld den = 0;
	int n = P.size();
	for(int i = 0; i < n; ++i){
		ld cross = P[i].cross(P[(i + 1) % n]);
		num += (P[i] + P[(i + 1) % n]) * cross;
		den += cross;
	}
	return num / (3 * den);
}