struct plane{
	point a, v;
	plane(): a(), v(){}
	plane(const point& a, const point& v): a(a), v(v){}

	point intersect(const plane& p) const{
		ld t = (p.a - a).cross(p.v) / v.cross(p.v);
		return a + v*t;
	}

	bool outside(const point& p) const{ // test if point p is strictly outside
		return le(v.cross(p - a), 0);
	}

	bool inside(const point& p) const{ // test if point p is inside or in the boundary
		return geq(v.cross(p - a), 0);
	}

	bool operator<(const plane& p) const{ // sort by angle
		auto lhs = make_tuple(v.half({1, 0}), ld(0), v.cross(p.a - a));
		auto rhs = make_tuple(p.v.half({1, 0}), v.cross(p.v), ld(0));
		return lhs < rhs;
	}

	bool operator==(const plane& p) const{ // paralell and same directions, not really equal
		return eq(v.cross(p.v), 0) && ge(v.dot(p.v), 0);
	}
};

vector<point> halfPlaneIntersection(vector<plane> planes){
	planes.push_back({{0, -inf}, {1, 0}});
	planes.push_back({{inf, 0}, {0, 1}});
	planes.push_back({{0, inf}, {-1, 0}});
	planes.push_back({{-inf, 0}, {0, -1}});
	sort(planes.begin(), planes.end());
	planes.erase(unique(planes.begin(), planes.end()), planes.end());
	deque<plane> ch;
	deque<point> poly;
	for(const plane& p : planes){
		while(ch.size() >= 2 && p.outside(poly.back())) ch.pop_back(), poly.pop_back();
		while(ch.size() >= 2 && p.outside(poly.front())) ch.pop_front(), poly.pop_front();
		if(p.v.half({1, 0}) && poly.empty()) return {};
		ch.push_back(p);
		if(ch.size() >= 2) poly.push_back(ch[ch.size()-2].intersect(ch[ch.size()-1]));
	}
	while(ch.size() >= 3 && ch.front().outside(poly.back())) ch.pop_back(), poly.pop_back();
	while(ch.size() >= 3 && ch.back().outside(poly.front())) ch.pop_front(), poly.pop_front();
	poly.push_back(ch.back().intersect(ch.front()));
	return vector<point>(poly.begin(), poly.end());
}

vector<point> halfPlaneIntersectionRandomized(vector<plane> planes){
	point p = planes[0].a;
	int n = planes.size();
	random_shuffle(planes.begin(), planes.end());
	for(int i = 0; i < n; ++i){
		if(planes[i].inside(p)) continue;
		ld lo = -inf, hi = inf;
		for(int j = 0; j < i; ++j){
			ld A = planes[j].v.cross(planes[i].v);
			ld B = planes[j].v.cross(planes[j].a - planes[i].a);
			if(ge(A, 0)){
				lo = max(lo, B/A);
			}else if(le(A, 0)){
				hi = min(hi, B/A);
			}else{
				if(ge(B, 0)) return {};
			}
			if(ge(lo, hi)) return {};
		}
		p = planes[i].a + planes[i].v*lo;
	}
	return {p};
}