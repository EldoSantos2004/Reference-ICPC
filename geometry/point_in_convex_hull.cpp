//point in convex polygon in O(log n)
//make sure that P is convex and in ccw
//before the queries, do the preprocess on P:
// rotate(P.begin(), min_element(P.begin(), P.end()), P.end());
// int right = max_element(P.begin(), P.end()) - P.begin();
//returns 0 if p is outside, 1 if p is inside, -1 if p is in the perimeter
int pointInConvexPolygon(const vector<point> & P, const point & p, int right){
	if(p < P[0] || P[right] < p) return 0;
	int orientation = sgn((P[right] - P[0]).cross(p - P[0]));
	if(orientation == 0){
		if(p == P[0] || p == P[right]) return -1;
		return (right == 1 || right + 1 == P.size()) ? -1 : 1;
	}else if(orientation < 0){
		auto r = lower_bound(P.begin() + 1, P.begin() + right, p);
		int det = sgn((p - r[-1]).cross(r[0] - r[-1])) - 1;
		if(det == -2) det = 1;
		return det;
	}else{
		auto l = upper_bound(P.rbegin(), P.rend() - right - 1, p);
		int det = sgn((p - l[0]).cross((l == P.rbegin() ? P[0] : l[-1]) - l[0])) - 1;
		if(det == -2) det = 1;
		return det;
	}
}
