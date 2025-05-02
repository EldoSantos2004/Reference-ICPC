pair<ld, ld> smallestEnclosingRectangle(vector<point> & P){
	int n = P.size();
	auto dot = [&](int a, int b){return (P[(a+1)%n]-P[a]).dot(P[(b+1)%n]-P[b]);};
	auto cross = [&](int a, int b){return (P[(a+1)%n]-P[a]).cross(P[(b+1)%n]-P[b]);};
	ld perimeter = inf, area = inf;
	for(int i = 0, j = 0, k = 0, m = 0; i < n; ++i){
		while(ge(dot(i, j), 0)) j = (j+1) % n;
		if(!i) k = j;
		while(ge(cross(i, k), 0)) k = (k+1) % n;
		if(!i) m = k;
		while(le(dot(i, m), 0)) m = (m+1) % n;
		//pairs: (i, k) , (j, m)
		point v = P[(i+1)%n] - P[i];
		ld h = distancePointLine(P[i], v, P[k]);
		ld w = distancePointLine(P[j], v.perp(), P[m]);
		perimeter = min(perimeter, 2 * (h + w));
		area = min(area, h * w);
	}
	return {area, perimeter};
}