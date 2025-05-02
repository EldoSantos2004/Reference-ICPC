vector<point> intersectSegmentCircle(const point & a, const point & b, const point & c, ld r){
	//segment ab, circle with center c and radius r
	vector<point> P = intersectLineCircle(a, b - a, c, r), ans;
	for(const point & p : P){
		if(pointInSegment(a, b, p)) ans.push_back(p);
	}
	return ans;
}