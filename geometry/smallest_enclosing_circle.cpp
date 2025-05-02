pair<point, ld> mec2(vector<point> & S, const point & a, const point & b, int n){
	ld hi = inf, lo = -hi;
	for(int i = 0; i < n; ++i){
		ld si = (b - a).cross(S[i] - a);
		if(eq(si, 0)) continue;
		point m = getCircle(a, b, S[i]).first;
		ld cr = (b - a).cross(m - a);
		if(le(si, 0)) hi = min(hi, cr);
		else lo = max(lo, cr);
	}
	ld v = (ge(lo, 0) ? lo : le(hi, 0) ? hi : 0);
	point c = (a + b) / 2 + (b - a).perp() * v / (b - a).norm();
	return {c, (a - c).norm()};
}

pair<point, ld> mec(vector<point> & S, const point & a, int n){
	random_shuffle(S.begin(), S.begin() + n);
	point b = S[0], c = (a + b) / 2;
	ld r = (a - c).norm();
	for(int i = 1; i < n; ++i){
		if(ge((S[i] - c).norm(), r)){
			tie(c, r) = (n == S.size() ? mec(S, S[i], i) : mec2(S, a, S[i], i));
		}
	}
	return {c, r};
}

pair<point, ld> smallestEnclosingCircle(vector<point> S){
	assert(!S.empty());
	auto r = mec(S, S[0], S.size());
	return {r.first, sqrt(r.second)};
}
