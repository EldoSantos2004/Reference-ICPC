pair<ld, ld> diameterAndWidth(vector<point> & P){
	int n = P.size(), k = 0;
	auto dot = [&](int a, int b){return (P[(a+1)%n]-P[a]).dot(P[(b+1)%n]-P[b]);};
	auto cross = [&](int a, int b){return (P[(a+1)%n]-P[a]).cross(P[(b+1)%n]-P[b]);};
	ld diameter = 0;
	ld width = inf;
	while(ge(dot(0, k), 0)) k = (k+1) % n;
	for(int i = 0; i < n; ++i){
		while(ge(cross(i, k), 0)) k = (k+1) % n;
		//pair: (i, k)
		diameter = max(diameter, (P[k] - P[i]).length());
		width = min(width, distancePointLine(P[i], P[(i+1)%n] - P[i], P[k]));
	}
	return {diameter, width};
}