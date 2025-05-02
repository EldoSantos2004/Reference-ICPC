vector<point> cutPolygon(const vector<point> & P, const point & a, const point & v){
	//returns the part of the convex polygon P on the left side of line a+tv
	int n = P.size();
	vector<point> lhs;
	for(int i = 0; i < n; ++i){
		if(geq(v.cross(P[i] - a), 0)){
			lhs.push_back(P[i]);
		}
		if(intersectLineSegmentInfo(a, v, P[i], P[(i+1)%n]) == 1){
			point p = intersectLines(a, v, P[i], P[(i+1)%n] - P[i]);
			if(p != P[i] && p != P[(i+1)%n]){
				lhs.push_back(p);
			}
		}
	}
	return lhs;
}
