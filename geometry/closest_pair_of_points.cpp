bool comp1(const point & a, const point & b){
	return le(a.y, b.y);
}
pair<point, point> closestPairOfPoints(vector<point> P){
	sort(P.begin(), P.end(), comp1);
	set<point> S;
	ld ans = inf;
	point p, q;
	int pos = 0;
	for(int i = 0; i < P.size(); ++i){
		while(pos < i && geq(P[i].y - P[pos].y, ans)){
			S.erase(P[pos++]);
		}
		auto lower = S.lower_bound({P[i].x - ans - eps, -inf});
		auto upper = S.upper_bound({P[i].x + ans + eps, -inf});
		for(auto it = lower; it != upper; ++it){
			ld d = (P[i] - *it).length();
			if(le(d, ans)){
				ans = d;
				p = P[i];
				q = *it;
			}
		}
		S.insert(P[i]);
	}
	return {p, q};
}