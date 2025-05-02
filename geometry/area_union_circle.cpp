struct circ{
	point c;
	ld r;
	circ() {}
	circ(const point & c, ld r): c(c), r(r) {}
	set<pair<ld, ld>> ranges;

	void disable(ld l, ld r){
		ranges.emplace(l, r);
	}

	auto getActive() const{
		vector<pair<ld, ld>> ans;
		ld maxi = 0;
		for(const auto & dis : ranges){
			ld l, r;
			tie(l, r) = dis;
			if(l > maxi){
				ans.emplace_back(maxi, l);
			}
			maxi = max(maxi, r);
		}
		if(!eq(maxi, 2*pi)){
			ans.emplace_back(maxi, 2*pi);
		}
		return ans;
	}
};

ld areaUnionCircles(const vector<circ> & circs){
	vector<circ> valid;
	for(const circ & curr : circs){
		if(eq(curr.r, 0)) continue;
		circ nuevo = curr;
		for(circ & prev : valid){
			if(circleInsideCircle(prev.c, prev.r, nuevo.c, nuevo.r)){
				nuevo.disable(0, 2*pi);
			}else if(circleInsideCircle(nuevo.c, nuevo.r, prev.c, prev.r)){
				prev.disable(0, 2*pi);
			}else{
				auto cruce = intersectionCircles(prev.c, prev.r, nuevo.c, nuevo.r);
				if(cruce.size() == 2){
					ld a1 = (cruce[0] - prev.c).ang();
					ld a2 = (cruce[1] - prev.c).ang();
					ld b1 = (cruce[1] - nuevo.c).ang();
					ld b2 = (cruce[0] - nuevo.c).ang();
					if(a1 < a2){
						prev.disable(a1, a2);
					}else{
						prev.disable(a1, 2*pi);
						prev.disable(0, a2);
					}
					if(b1 < b2){
						nuevo.disable(b1, b2);
					}else{
						nuevo.disable(b1, 2*pi);
						nuevo.disable(0, b2);
					}
				}
			}
		}
		valid.push_back(nuevo);
	}
	ld ans = 0;
	for(const circ & curr : valid){
		for(const auto & range : curr.getActive()){
			ld l, r;
			tie(l, r) = range;
			ans += curr.r*(curr.c.x * (sin(r) - sin(l)) - curr.c.y * (cos(r) - cos(l))) + curr.r*curr.r*(r-l);
		}
	}
	return ans/2;
};