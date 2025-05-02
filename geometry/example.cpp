int main(){
	/*vector<pair<point, point>> centers = {{point(-2, 5), point(-8, -7)}, {point(14, 4), point(18, 6)}, {point(9, 20), point(9, 28)},
										  {point(21, 20), point(21, 29)}, {point(8, -10), point(14, -10)}, {point(24, -6), point(34, -6)},
										  {point(34, 8), point(36, 9)}, {point(50, 20), point(56, 24.5)}};
	vector<pair<ld, ld>> radii = {{7, 4}, {3, 5}, {4, 4}, {4, 5}, {3, 3}, {4, 6}, {5, 1}, {10, 2.5}};
	int n = centers.size();
	for(int i = 0; i < n; ++i){
		cout << "\n" << centers[i].first << " " << radii[i].first << " " << centers[i].second << " " << radii[i].second << "\n";
		auto extLines = tangents(centers[i].first, radii[i].first, centers[i].second, radii[i].second, false);
		cout << "Exterior tangents:\n";
		for(auto par : extLines){
			for(auto p : par){
				cout << p << " ";
			}
			cout << "\n";
		}
		auto intLines = tangents(centers[i].first, radii[i].first, centers[i].second, radii[i].second, true);
		cout << "Interior tangents:\n";
		for(auto par : intLines){
			for(auto p : par){
				cout << p << " ";
			}
			cout << "\n";
		}
	}*/

	/*int n;
	cin >> n;
	vector<point> P(n);
	for(auto & p : P) cin >> p;
	auto triangulation = delaunay(P);
	for(auto triangle : triangulation){
		cout << get<0>(triangle) << " " << get<1>(triangle) << " " << get<2>(triangle) << "\n";
	}*/

	/*int n;
	cin >> n;
	vector<point> P(n);
	for(auto & p : P) cin >> p;
	auto ans = smallestEnclosingCircle(P);
	cout << ans.first << " " << ans.second << "\n";*/

	/*vector<point> P;
	srand(time(0));
	for(int i = 0; i < 1000; ++i){
		P.emplace_back(rand() % 1000000000, rand() % 1000000000);
	}
	point o(rand() % 1000000000, rand() % 1000000000), v(rand() % 1000000000, rand() % 1000000000);
	polarSort(P, o, v);
	auto ang = [&](point p){
		ld th = atan2(p.y, p.x);
		if(th < 0) th += acosl(-1)*2;
		ld t = atan2(v.y, v.x);
		if(t < 0) t += acosl(-1)*2;
		if(th < t) th += acosl(-1)*2;
		return th;
	};
	for(int i = 0; i < P.size()-1; ++i){
		assert(leq(ang(P[i] - o), ang(P[i+1] - o)));
	}*/
	return 0;
}